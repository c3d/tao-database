// *****************************************************************************
// database.h                                                      Tao3D project
// *****************************************************************************
//
// File description:
//
//      Database connection.
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
