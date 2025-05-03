#include "databasequery.h"

DatabaseQuery::DatabaseQuery(QObject *parent) : QObject(parent)
{
    DatabaseConnector db;
}

void DatabaseQuery::getdata()
{
    QString full_string;
    QSqlQuery query("SELECT * FROM stations_list");
    while(query.next())
    {
        if(lang == "zh"){
            full_string = query.value("station_name_zh").toString();
        }
        else{
            full_string = query.value("station_name_en").toString();
        }
        if(full_string != "无")
        {
            full_string = query.value("station_no_").toString() + " " + full_string;
            names_list << full_string;
        }
        qDebug() << query.value("station_no_").toString() + query.value("station_name_zh").toString();
    }
}

QString DatabaseQuery::getcity()
{
    QString city;
    QSqlQuery query;
    if(lang == "zh"){
        query.exec("SELECT city_zh from data_information");
    }
    else{
        query.exec("SELECT city_en from data_information");
    }
    query.first();
    city = query.value(0).toString();
    query.finish();
    return city;
}

QString DatabaseQuery::getname()
{
    QString name;
    QSqlQuery query;
    if(lang == "zh"){
        query.exec("SELECT name_zh FROM data_information");
    }
    else{
        query.exec("SELECT name_en FROM data_information");
    }
    query.first();
    name = query.value(0).toString();
    query.finish();
    return name;
//    return name+QStandardPaths::writableLocation(QStandardPaths::DataLocation)+"/guangzhou_foshan_20241228.sqlite";
}

QString DatabaseQuery::getversion()
{
    QString version;
    QSqlQuery query("SELECT version FROM data_information");
    query.first();
    version = query.value(0).toString();
    query.finish();
    return version;
}
