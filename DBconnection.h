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
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriete de Taodyne SAS - Confidentiel
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include <iostream>
#include <QString>
#include <QStringList>
#include "tree.h"
#include <QSqlQuery>


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


#endif // DBCONNECTION_H
