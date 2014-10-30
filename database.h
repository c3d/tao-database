// ****************************************************************************
//  database.h                                                 Tao project
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
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include "tree.h"
#include <QStringList>
#include <QSqlDatabase>
using namespace std;
using namespace XL;

XL::Tree_p setConnection(Tree_p /* self */, Text_p SGBD, Text_p setHostName,
                         Text_p setDatabaseName, Text_p setUserName,
                         Text_p setPassword, Integer_p setPort);
XL::Tree_p closeConnection (Tree_p /*self*/, Text_p DatabaseName);
XL::Tree_p closeAllConnections (Tree_p /*self*/);
XL::Tree_p getTableList(Tree_p self, Text_p dbName);
XL::Tree_p getFieldList(Tree_p self, Text_p dbName, Text_p tblName);
XL::Tree_p simpleQuery (Tree_p self, Text_p databasename, Text_p query_string);
XL::Tree_p filterQuery (Tree_p self, Text_p DatabaseName, Text_p TableName,
                         Text_p FilterString);
XL::Tree_p relationalQuery (Tree_p self, Text_p DatabaseName, Text_p TableName01,
                            Text_p filter, Text_p TableName02,
                            Text_p primary_key,Text_p field_need, int place_id);
