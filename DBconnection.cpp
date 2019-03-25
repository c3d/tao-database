// *****************************************************************************
// DBconnection.cpp                                                Tao3D project
// *****************************************************************************
//
// File description:
//
//      Tool file for db connection.
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2012, Catherine Burvelle <catherine@taodyne.com>
// (C) 2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// *****************************************************************************
// This file is part of Tao3D
//
// Tao3D is free software: you can r redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tao3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tao3D, in a file named COPYING.
// If not, see <https://www.gnu.org/licenses/>.
// *****************************************************************************
#include "DBconnection.h"
#include "runtime.h"
#include "tao_utf8.h"

#undef record
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QMap>

using namespace XL;
using namespace Tao;


static QMap<QString, QString> drivers;

QString getDriverName(QString SGBD)
//-----------------------------------------------------------------------------
// Returns the Qt driver name from the SGBD type.
//-----------------------------------------------------------------------------
{
    return drivers[SGBD.toUpper()];
}


void fillDrivers()
//-----------------------------------------------------------------------------
// Builds Qt driver name, SGBD type table
//-----------------------------------------------------------------------------
{
    if ( ! drivers.isEmpty())
        return;
    //------------------------------------------------
    /* driver for DB2 database version 7.1 and above*/
    //------------------------------------------------
    QString dr("QDB2");
    drivers["DB2"] = dr;
    drivers["IBM DB2"] = dr;

    //------------------------------------------------
    /* driver for Borland InterBase/firebird  version ? */
    //------------------------------------------------
    dr = "QIBASE";
    drivers[QString("InterBase").toUpper()] = dr;
    drivers[QString("Borland InterBase").toUpper()] = dr;
    drivers[QString("Firebird").toUpper()] = dr;

    //-------------------------------------------------
    /* driver for Sybase Adaptive Server */
    /* QTDS obsolete from Qt 4.7 */
    //-------------------------------------------------
    dr = "QODBC";
    drivers[QString("Sybase").toUpper()] = dr;
    drivers[QString("Sybase Adaptive Server").toUpper()] = dr;
    drivers[QString("ODBC").toUpper()] = dr;

    //------------------------------------------------
    /*driver for MySQL version ?  */
    //------------------------------------------------
    drivers[QString("MySQL").toUpper()] = "QMYSQL";

    //---------------------------------------------------
    /*driver for Oracle Call Interface Driver version ?*/
    //---------------------------------------------------
    dr = "QOCI";
    drivers[QString("Oracle Call Interface Driver").toUpper()] = dr;
    drivers[QString("Oracle").toUpper()] = dr;
    drivers["OCI"] = dr;

    //-------------------------------------------------
    /*driver for Microsoft SQL Server version ?*/
    //-------------------------------------------------
    dr ="QODBC3";
    drivers[QString("Microsoft SQL Server").toUpper()] = dr;
    drivers[QString("SQL Server").toUpper()] = dr;
    drivers[QString("ODBC3").toUpper()] = dr;

    //---------------------------------------------------
    /*driver for  PostgreSQL (versions 7.3 and above)*/
    //---------------------------------------------------
    drivers[QString("PostgreSQL").toUpper()] = "QPSQL";

    //-------------------------------------------------
    /*driver for SQLite version 2 */
    //-------------------------------------------------
    dr = "SQLITE2";
    drivers[QString("SQLite version 2").toUpper()] = dr;
    drivers[QString("SQLite2").toUpper()] = dr;

    //-------------------------------------------------
    /*driver for SQLite version 3 */
    //-------------------------------------------------
    dr = "SQLITE";
    drivers[QString("SQLite").toUpper()] = dr;
    drivers[QString("SQLite3").toUpper()] = dr;
    drivers[QString("SQLite version 3").toUpper()] = dr;
}


std::ostream& debug()
// ----------------------------------------------------------------------------
//   Convenience method to log with a common prefix
// ----------------------------------------------------------------------------
{
    std::cerr << "[DBconnector] ";
    return std::cerr;
}


bool testConnection(QSqlDatabase &conn)
//--------------------------------------------------------------------------
// Test db connection availability
//--------------------------------------------------------------------------
{
    if (!conn.isValid())
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: No database named \"" << +conn.databaseName()
                         << "\" found.\n";
        return false;
    }

    if (!conn.isOpen())
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: Cannot open database named \""
                        << +conn.databaseName() << "\"\n"
                        << +conn.lastError().text() << std::endl;
        /* Cleanup database */
        QSqlDatabase::removeDatabase(conn.databaseName());
        return false;
    }

    return true;
}


#define PUSH_ROW    \
    nbRow->value++; \
    queryResult.push_back(xl_list_to_tree(rowResult,",")); \
    rowResult.clear()

XL::Tree_p buildAnswer(QSqlQuery query)
//---------------------------------------------------------------------------
// Return a list of list of value.
//---------------------------------------------------------------------------
// Returned values are as :
// ( (number of row,  number of col),
//   (column-1 name, column-2 name, column-3 name, ...),
//   (row-1-col-1 value, row-1-col-2 value, row-1-col-3 value, ...),
//   (row-2-col-1 value, row-2-col-2 value, row-2-col-3 value, ...),
//   ... )
{
    if (!query.isActive()) return XL::xl_nil;

    int nbCol = query.record().count();
    // The following Integer_p is the number of rows in the answer.
    // It's value must be updated once the actual number of row will be known.
    Integer_p nbRow = new Integer(-1, Tree::NOWHERE);

    TreeList rowResult, queryResult;

    // First part of the answer is the number of row and column in the answer
    rowResult.push_back(nbRow);
    rowResult.push_back(new Integer(nbCol));
    PUSH_ROW;
    if (nbCol <= 0)
        return xl_list_to_tree(queryResult, ",");

    // Second part of the answer is column name
    for (int i=0; i<query.record().count();i++)
    {
        QString fieldName = query.record().fieldName(i);
        rowResult.push_back(new Text(+fieldName));
    }
    PUSH_ROW;

    // Third part of the answer is query result itself
    while (query.next()) // Each row of the result
    {
        for (int i=0; i< nbCol; i++)// Each field in the row
        {
            QVariant value = query.value(i);
            if (! value.isValid())
            {
                rowResult.push_back(XL::xl_nil);
                continue;
            }
            switch(value.type()) {
            case QVariant::Int:
            case QVariant::UInt:
                rowResult.push_back(new Integer(value.toInt()));
                break;
            case QVariant::Double:
                rowResult.push_back(new Real(value.toReal()));
                break;
            case QVariant::String:
                rowResult.push_back(new Text(+value.toString()));
                break;
            case QVariant::Bool:
                rowResult.push_back(value.toBool() ? xl_true : xl_false);
                break;
            default:
                rowResult.push_back(new Text(+value.toString()));
            } // switch
        } // for
        PUSH_ROW;
    } // while

    return xl_list_to_tree(queryResult, ",");
}
