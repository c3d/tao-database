#ifndef DBCONNECTION_H
#define DBCONNECTION_H
// *****************************************************************************
// DBconnection.h                                                  Tao3D project
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
// (C) 2013, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2012-2013, Catherine Burvelle <catherine@taodyne.com>
// (C) 2013-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2013, Jérôme Forissier <jerome@taodyne.com>
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
