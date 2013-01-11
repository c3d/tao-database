// ****************************************************************************
//  database.cpp                                               Tao project
// ****************************************************************************
//
//   File Description:
//
//      Database connection.
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriete de Taodyne SAS - Confidentiel
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include <QtGui>
#include <QtSql>
#include <iostream>
#include "database.h"
#include "runtime.h"
#include "tree.h"
#include <QStringList>
#include <QMessageBox>
#include <QVariant>
#include "DBconnection.h"
#include "tao_utf8.h"
#include "tao/module_api.h"
using namespace std;
using namespace XL;
using namespace Tao;

XL_DEFINE_TRACES

static LicenseTimer lic;



Tree_p setConnection(Tree_p /* self */,
                     Text_p SGBD, Text_p setHostName,
                     Text_p setDatabaseName, Text_p setUserName,
                     Text_p setPassword, Integer_p setPort)
//-----------------------------------------------------------------------------
// set the database connection
//-----------------------------------------------------------------------------
{
    IFTRACE(dbconnector_I)
            debug() << "INFO: setConnection \n"
                    << "\tSGBD ["<< SGBD->value << "]\n"
                    << "\tsetHostName [" << setHostName->value  << "]\n"
                    << "\tsetDatabaseName [" << setDatabaseName->value  << "]\n"
                    << "\tsetUserName [" <<  setUserName->value << "]\n"
                    << "\tsetPassword [" <<  setPassword->value << "]\n"
                    << "\tsetPort [" <<  setPort->value << "]\n";
    if (! lic.isConnectionAuthorized())
    {
        IFTRACE(dbconnector_W)
                debug() << "WARNING: unlicensed module. Trial time as expired.\n";
        return XL::xl_false;
    }
    QString sgbd = +SGBD->value;
    QString HostName = +setHostName->value;
    QString DatabaseName = +setDatabaseName->value;
    QString UserName = +setUserName->value;
    QString Password = +setPassword->value;
    int Port = setPort->value;

    if (sgbd.isEmpty() || HostName.isEmpty() || DatabaseName.isEmpty()
            || UserName.isEmpty() || Password.isEmpty()
            || setPort->value <= 0)
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: at least one parameter is empty. \n"
                        << "\tSGBD ["<< SGBD->value << "]\n"
                        << "\tsetHostName [" << setHostName->value  << "]\n"
                        << "\tsetDatabaseName [" << setDatabaseName->value  << "]\n"
                        << "\tsetUserName [" <<  setUserName->value << "]\n"
                        << "\tsetPassword [" <<  setPassword->value << "]\n"
                        << "\tsetPort [" <<  Port << "]\n";

        return XL::xl_false;
    }
    QString driverName = getDriverName(sgbd);

    if (driverName.isEmpty())
    {
        IFTRACE(dbconnector_E)
                debug() <<"ERROR: Unable to find driver name associated with "
                        << SGBD->value << std::endl;
        return XL::xl_false;
    }

    /* We assume that databases have a unique name.
     * If DSN was used to set up the connection,
     * it would have the same name as the database.
     */
    QSqlDatabase SqlDB = QSqlDatabase::addDatabase(driverName, DatabaseName);
    SqlDB.setHostName(HostName);
    SqlDB.setDatabaseName(DatabaseName);
    SqlDB.setUserName(UserName);
    SqlDB.setPassword(Password);
    SqlDB.setPort(Port);

    if ( ! SqlDB.open())
    {
        IFTRACE(dbconnector_E)
                debug() <<"Unable to open database connection associated with "
                        << SGBD->value << " because "
                        << SqlDB.lastError().text().toStdString() << std::endl;
        return  XL::xl_false;
    }

    return XL::xl_true;
}


Tree_p closeConnection (Tree_p /*self*/, Text_p DatabaseName)
//-----------------------------------------------------------------------------
// Closes and removes the named database connection
//-----------------------------------------------------------------------------
{
    QString dbName = +DatabaseName->value;
    if ( !QSqlDatabase::contains(dbName))
    {
        IFTRACE(dbconnector_E)
                debug() << "No connection of this name was established.\n";
        return XL::xl_false ;
    }

    QSqlDatabase::database(dbName).close();
    QSqlDatabase::removeDatabase(dbName);
    return XL::xl_true;
}


Tree_p closeAllConnections (Tree_p /*self*/)
//-----------------------------------------------------------------------------
// Closes and removes all database connections
//-----------------------------------------------------------------------------
{
    if (QSqlDatabase::connectionNames().isEmpty())
        return XL::xl_false;

    foreach (const QString &str, QSqlDatabase::connectionNames())
    {
        QSqlDatabase::database(str).close();
        QSqlDatabase::removeDatabase(str);
    }
    return XL::xl_true;
}


Tree_p simpleQuery (Tree_p self, Text_p databasename, Text_p queryString)
//-----------------------------------------------------------------------------
// Execute an sql query
//-----------------------------------------------------------------------------
{
    IFTRACE(dbconnector_I)
            debug() << "INFO: simpleQuery.\n"
                    << "\t databasename " << databasename->value << std::endl
                    << "\t queryString " << queryString->value << std::endl;
    QString dbName = +databasename->value;
    QString queryStr = +queryString->value;

    if ( queryStr.isEmpty() ||dbName.isEmpty() )
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: Empty query string or db name.\n";
        return XL::xl_nil;
    }

    QSqlDatabase conn = QSqlDatabase::database(dbName);
    if ( ! testConnection(conn))
        return XL::xl_nil;

    QSqlQuery query(conn);

    // Execute the query
    if (!query.exec(queryStr))
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: query ["<< +queryStr
                        << "] execution error :\n\t"
                        << query.lastError().text().toStdString() << std::endl;
        return XL::xl_nil;
    }

    Tree * res = buildAnswer(query);
    res->SetSymbols(self->Symbols());
    return res;
}



Tree_p getTableList(Tree_p self ,Text_p dbName)
//-----------------------------------------------------------------------------
// Returns table list
//-----------------------------------------------------------------------------
{
    QString DatabaseName = +dbName->value;
    TreeList rowResult, result;

    QStringList list;
    if (DatabaseName.isEmpty() )
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR: Empty db name.\n";
        return XL::xl_nil;
    }

    QSqlDatabase conn = QSqlDatabase::database(DatabaseName);

    if (!testConnection(conn))
        return XL::xl_nil;

    // Get DB table list
    list = conn.tables();

    //number of line = nb of tables + header
    rowResult.push_back (new Integer(list.length()+1));
    // Par default le nombre de colonnes est égale a 1
    rowResult.push_back (new Integer(1));
    result.push_back(xl_list_to_tree(rowResult, ","));

    // Inserer le titre de la colonne
    result.push_back (new Text("Table list"));
    foreach (const QString &str, list)
    {
        result.push_back (new Text(+str));
    }

    Tree * res = xl_list_to_tree(result,",");
    res->SetSymbols(self->Symbols());
    return res;
}


XL::Tree_p getFieldList(Tree_p self, Text_p dbName, Text_p tblName)
//-----------------------------------------------------------------------------
// Returns field list
//-----------------------------------------------------------------------------
{
    QString databaseName = +dbName->value;
    QString tableName = +tblName->value;
    TreeList rowResult, result;

    QSqlDatabase conn = QSqlDatabase::database(databaseName);
    QSqlRecord fields = conn.record(tableName);

    // number of line = nb of field + header
    rowResult.push_back (new Integer(fields.count()+1));
    // Only one column
    rowResult.push_back (new Integer(1));
    result.push_back(xl_list_to_tree(rowResult, ","));

    // Insert column title
    result.push_back (new Text("Field name"));

    for (int i =0; i< fields.count(); i++)
    {
        QString name = fields.fieldName(i);
        result.push_back (new Text(+name));
    }

    Tree * res = xl_list_to_tree(result,",");
    res->SetSymbols(self->Symbols());
    return res;
}


Tree_p filterQuery (Tree_p self, Text_p DatabaseName, Text_p TableName,
                    Text_p FilterString)
//-----------------------------------------------------------------------------
// Filters a specified table in a database
//-----------------------------------------------------------------------------
{
    QString dbName = +DatabaseName->value;
    QString tblName = +TableName->value;
    QString filter = +FilterString->value;

    if ( dbName.isEmpty() || tblName.isEmpty() || filter.isEmpty())
        return XL::xl_nil;

    QSqlDatabase conn = QSqlDatabase::database(dbName);
    if (! testConnection(conn))
        return XL::xl_nil;

    QSqlTableModel model(0, conn);
    model.setTable(tblName);
    if (model.lastError().isValid())
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR : No table " << TableName->value
                        << " in database " << DatabaseName->value << std::endl
                        << +model.lastError().text()<< std::endl;
        return XL::xl_nil;
    }

    model.setFilter(filter);
    if (model.lastError().isValid())
    {
        IFTRACE(dbconnector_E)
                debug() << "ERROR : Bad filter " << FilterString->value
                        << std::endl
                        << +model.lastError().text()<< std::endl;
        return XL::xl_nil;
    }

    if (!model.select())
    {
        IFTRACE(dbconnector_E)
        {
            debug() << "Select error \n" ;
            if (model.lastError().isValid())
                debug() << +model.lastError().text()<< std::endl;
        }
        return XL::xl_nil;
    }

    Tree * res = buildAnswer(model.query());
    res->SetSymbols(self->Symbols());
    return res;
}


//////////////////  TO BE REWORKED ??? //////////////////
//-----------------------------------------------------------------------------
/* replace a foreigne key by another fields from the source table */
//-----------------------------------------------------------------------------

/* TableName01: table to display
   place_id : the index(it start by 0) of the foreigne key in TableName01 that
refer to the primary key
   of the Table02 but they may not have the same name.
   TableName02: table (that have sql relation with TableName01)
   primary_key: primary_key of the TableName02
   field_needs: the field that will replace the foreigne key in Table01 to have
human-readable value */

Tree_p relationalQuery(Tree_p self, Text_p DatabaseName,
                       Text_p TableName01, Text_p filter, Text_p TableName02,
                       Text_p primary_key, Text_p field_need,int place_id)
//-----------------------------------------------------------------------------
// Returns table 1 with field.
//-----------------------------------------------------------------------------
{
    QString dbName = +DatabaseName->value;
    QString tbl1 = +TableName01->value;
    QString tbl2 = +TableName02->value;
    QString flt = +filter->value;

    QSqlDatabase conn = QSqlDatabase::database(dbName);
    if ( ! testConnection(conn))
        return XL::xl_nil;
    QSqlRelationalTableModel model(0, conn);
    model.setTable(tbl1);
    IFTRACE(dbconnector_I)
    {
        debug() << "tbl1 " <<  +tbl1 << std::endl;
        debug() << "tbl2 " <<  +tbl2 << std::endl;
        debug() << "primary_key " <<  primary_key->value << std::endl;
    }
    if ( ! flt.isEmpty())
        model.setFilter(flt);
    model.setRelation(place_id, QSqlRelation(tbl2, +primary_key->value,
                                              +field_need->value ));

    if( !model.select())
    {
        IFTRACE(dbconnector_E)
        {
            debug() << "Query [" <<  +model.query().lastQuery() << "]\n";
            debug() << "Select error \n" ;
            if (model.lastError().isValid())
                debug() << +model.lastError().text()<< std::endl;
        }
        return XL::xl_nil;
    }

    Tree * res = buildAnswer(model.query());
    res->SetSymbols(self->Symbols());
    return res;

}
int module_init(const Tao::ModuleApi *api, const Tao::ModuleInfo *)
// ----------------------------------------------------------------------------
//   Initialize the Tao module
// ----------------------------------------------------------------------------
{
    XL_INIT_TRACES();

    // Module available for Impress version so silently check it before
    // checking with potential warning window "dbConnector" license.
    if ( ! api->hasLicense("Tao Presentations Impress 1.001") &&
         ! api->checkLicense("dbConnector 1.0", false) )
    {
        lic.start(5 * 60 * 1000);
        IFTRACE(dbconnector_W)
                debug() << "WARNING: No license available."
                        << " Connections available for "
                        << lic.interval() << " msec. \n";
    }
    fillDrivers();

    return no_error;
}


int module_exit()
// ----------------------------------------------------------------------------
//   Uninitialize the Tao module
// ----------------------------------------------------------------------------
{
    return 0;
}
