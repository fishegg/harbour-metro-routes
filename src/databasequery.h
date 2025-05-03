#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H

#include <QObject>
#include <QSqlQuery>
#include <QStringList>
#include <QString>
#include <QLocale>
#include <qdebug.h>
#include "databaseconnector.h"

class DatabaseQuery : public QObject
{
    Q_OBJECT
private:
    QStringList names_list;
    QLocale locale = QLocale::system();
    QString lang = locale.name().mid(0,2);
public:
    explicit DatabaseQuery(QObject *parent = 0);
    void getdata();
    Q_INVOKABLE QString getcity();
    Q_INVOKABLE QString getname();
    Q_INVOKABLE QString getversion();

signals:

public slots:
};

#endif // DATABASEQUERY_H
