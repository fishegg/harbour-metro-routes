#ifndef APPSETTINGS_H
#define APPSETTINGS_H


#include<QSettings>
#include<QString>
#include<QStandardPaths>
#include<QCoreApplication>
#include <QSqlQuery>
#include <QLocale>

class AppSettings: public QObject {
    Q_OBJECT
private:
    QSettings* settings;
    const QString settingsPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation)+ "/" + QCoreApplication::applicationName() + ".conf";
    QLocale locale = QLocale::system();
    QString lang = locale.name().mid(0,2);
    QSqlDatabase db;
    QSqlDatabase db_test;
public:
    explicit AppSettings(QObject* parent = 0);
    ~AppSettings();
    Q_INVOKABLE void open_current_database();
    Q_INVOKABLE void open_selected_database(const QString &db_name);
    Q_INVOKABLE void close_current_database();
    Q_INVOKABLE void clean_conf();
    Q_INVOKABLE void set_accepted_status(const bool &accepted);
    Q_INVOKABLE bool get_accepted_status();
    Q_INVOKABLE void set_version(const QString &version);
    Q_INVOKABLE QString get_version();
    Q_INVOKABLE bool is_updated(const QString &conf_version, const QString &curr_version);
    Q_INVOKABLE void set_db_name(const QString &db_name);
    Q_INVOKABLE QString get_db_name();
    Q_INVOKABLE void set_currentIndex(const int &index);
    Q_INVOKABLE int get_currentIndex();
    Q_INVOKABLE void set_currentIndex_language(const int &index);
    Q_INVOKABLE int get_currentIndex_language();
    Q_INVOKABLE QString get_database_city();
    Q_INVOKABLE QString get_database_name();
    Q_INVOKABLE QString get_database_version();
    Q_INVOKABLE QString test_database(const QString &database_test);
};

#endif // APPSETTINGS_H
