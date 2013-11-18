# ******************************************************************************
#  database.pro                                                  Tao project
# ******************************************************************************
# File Description:
# Qt build file for the Data base module
# ******************************************************************************
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Taodyne SAS
# ******************************************************************************

MODINSTDIR = database

include(../modules.pri)

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4) { QT += widgets }

HEADERS     = \
    database.h \
    DBconnection.h \
    doc/dbConnector.doxy.h

SOURCES     = database.cpp \
    DBconnection.cpp
TBL_SOURCES = database.tbl
OTHER_FILES = database.xl database.tbl traces.tbl \
    db_connector.taokey.notsigned \
    doc/Doxyfile.in

INSTALLS    += thismod_icon

QMAKE_SUBSTITUTES = doc/Doxyfile.in
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(../modules_doc.pri)
