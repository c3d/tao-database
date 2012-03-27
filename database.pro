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

QT       += core

QT       += gui

QT       += sql

HEADERS     = \
    database.h \
    DBconnection.h

SOURCES     = database.cpp \
    DBconnection.cpp
TBL_SOURCES = database.tbl
OTHER_FILES = database.xl database.tbl traces.tbl
