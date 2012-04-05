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

class LicenseTimer : public QTimer
{
    Q_OBJECT
 public:

    LicenseTimer()
    {
        LicenceOK = true;
        setSingleShot(true);
        connect(this, SIGNAL(timeout()), this, SLOT(timedout()));
    }
    bool isConnectionAuthorized()
    {
        return LicenceOK;
    }

public slots:
    void timedout()
    {
        LicenceOK = false;
        closeAllConnections(NULL);
    }
protected :
    bool LicenceOK;
};

#endif // DBCONNECTION_H
