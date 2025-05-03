#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QStringList>
#include <QStandardPaths>
#include "appsettings.h"


class DatabaseConnector : public QObject
{
    Q_OBJECT
private:
    QStringList names_list;
    QSqlDatabase db;
    AppSettings settings;
public:
    explicit DatabaseConnector(QObject *parent = 0);
    ~DatabaseConnector();
    bool openconnection();
    void getdata();
    Q_INVOKABLE QStringList getlist();
    Q_INVOKABLE int getlistsize();
    Q_INVOKABLE QString getlistelement(int i);

signals:

public slots:
};

#endif // DATABASECONNECTOR_H
