#include <QSettings>
#include "appsettings.h"
#include <qdebug.h>

AppSettings::AppSettings(QObject* parent) {
    settings = new QSettings(settingsPath, QSettings::NativeFormat);

    db = QSqlDatabase::addDatabase("QSQLITE", "Settings");
    QString database = get_database();
    db.setDatabaseName(database);
    if(db.open()){
        qDebug() << "settings database opened" << endl;
    }
    db_test = QSqlDatabase::addDatabase("QSQLITE", "Test");
}

AppSettings::~AppSettings(){
    db.close();
}

void AppSettings::clean_conf() {
    if(settings->contains(QString("accepted")))
        settings->remove(QString("accepted"));
}

void AppSettings::set_accepted_status(const bool &accepted) {
    settings->setValue(QString("disclaimer/accepted"),QVariant(accepted).toString());
    qDebug()<<"set accepted success"<<accepted;
}

bool AppSettings::get_accepted_status() {
    return settings->value(QString("disclaimer/accepted"),QVariant(false)).toBool();
}

void AppSettings::set_version(const QString &version) {
    settings->setValue(QString("application/version"),version);
}

QString AppSettings::get_version() {
    return settings->value(QString("application/version"),QString("")).toString();
}

bool AppSettings::is_updated(const QString &conf_version, const QString &curr_version) {
    return conf_version == curr_version ? false : true;
}

void AppSettings::set_database(const QString &database) {
    settings->setValue(QString("application/database"),database);
}

QString AppSettings::get_database() {
    return settings->value(QString("application/database"),QString("/usr/share/harbour-metro-routes/guangzhou_foshan_20241228.sqlite")).toString();
//    return settings->value(QString("application/database"),QString("")).toString();
}

void AppSettings::set_currentIndex(const int &index){
    settings->setValue(QString("application/currentIndex"),index);
}

int AppSettings::get_currentIndex(){
    return settings->value(QString("application/currentIndex"),QVariant(0)).toInt();
}

void AppSettings::set_currentIndex_language(const int &index){
    settings->setValue(QString("application/station_name_language"),index);
}

int AppSettings::get_currentIndex_language(){
    return settings->value(QString("application/station_name_language"),QVariant(0)).toInt();
}

QString AppSettings::get_database_city(){
    QString city;
    QSqlQuery query(db);
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

QString AppSettings::get_database_name(){
    QString name;
    QSqlQuery query(db);
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
}

QString AppSettings::get_database_version(){
    QString version;
    QSqlQuery query(db);
    query.exec("SELECT version FROM data_information");
    query.first();
    version = query.value(0).toString();
    query.finish();
    return version;
}

QString AppSettings::test_database(const QString &database_test){
    qDebug() << database_test;
    db_test.setDatabaseName(database_test);
    QString city;
    QSqlQuery query_test(db_test);
    if(db_test.open()){
        qDebug() << "db_test opened";
        if(lang == "zh"){
            qDebug() << "zh";
            query_test.exec("SELECT city_zh FROM data_information");
        }
        else{
            query_test.exec("SELECT city_en FROM data_information");
        }
    }
    query_test.first();
    city = query_test.value(0).toString();
    query_test.finish();
    db_test.close();
    return city;
}
