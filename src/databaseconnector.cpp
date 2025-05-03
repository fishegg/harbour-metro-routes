#include "databaseconnector.h"
//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <qdebug.h>
//#include <QStringList>

DatabaseConnector::DatabaseConnector(QObject *parent)
{
    openconnection();
}

DatabaseConnector::~DatabaseConnector()
{
    db.close();
}

bool DatabaseConnector::openconnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE","DatabaseConnector");
    QString database = settings.get_database();
    db.setDatabaseName(database);
//    db.setDatabaseName("/usr/share/harbour-metro-routes/guangzhou_foshan_20241228.sqlite");
//    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/guangzhou_foshan_20241228.sqlite");
    if(db.open())
    {
        qDebug() << "connection opened" << endl;
        return true;
    }
    else
    {
        qDebug() << "connection open failed" << endl;
        return false;
    }
}

QStringList DatabaseConnector::getlist()
{
    return names_list;
}

int DatabaseConnector::getlistsize()
{
    return names_list.size();
}

QString DatabaseConnector::getlistelement(int i)
{
    return names_list.at(i);
}

