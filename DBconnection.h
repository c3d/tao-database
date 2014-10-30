#ifndef DBCONNECTION_H
#define DBCONNECTION_H
// ****************************************************************************
//  DBconnection.h                                                 Tao project
// ****************************************************************************
//
//   File Description:
//
//      Tool file for db connection.
//
//
//
//
//
// ****************************************************************************
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include <iostream>
#include <QString>
#include <QStringList>
#include "tree.h"
#include <QSqlQuery>
#include <QTimer>

//-----------------------------------------------------------------------------
// Returns the Qt driver name from the SGBD type.
//-----------------------------------------------------------------------------
QString getDriverName(QString name);

//-----------------------------------------------------------------------------
// Builds Qt driver name - SGBD type table
//-----------------------------------------------------------------------------
void fillDrivers();

//-----------------------------------------------------------------------------
// Debug trace
//-----------------------------------------------------------------------------
std::ostream& debug();

//--------------------------------------------------------------------------
// Test db connection availability
//--------------------------------------------------------------------------
bool testConnection(QSqlDatabase &conn);


//---------------------------------------------------------------------------
// Return a list of list of value.
//---------------------------------------------------------------------------
XL::Tree_p buildAnswer(QSqlQuery query);

extern "C++" XL::Tree_p closeAllConnections (XL::Tree_p /*self*/);

#endif // DBCONNECTION_H
