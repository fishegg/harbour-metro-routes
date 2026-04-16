#ifndef STATIONMODEL_H
#define STATIONMODEL_H
#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QStandardPaths>
#include <QLocale>
//#include <QVector>
#include "station.h"
#include "routesearch.h"
#include "appsettings.h"


class StationModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(StationRoles)
    Q_ENUMS(LoadStatus)
    Q_ENUMS(Action)
    Q_ENUMS(Preference)
    Q_ENUMS(CircleLineDirection)
public:
    enum StationRoles {
        NumRole = Qt::UserRole + 1,
        CountRole,
        Interchange1Role,
        Interchange2Role,
        Interchange3Role,
        Interchange4Role,
        Interchange5Role,
        UnpaidInterchange1Role,
        UnpaidInterchange2Role,
        UnpaidInterchange3Role,
        UnpaidInterchange4Role,
        UnpaidInterchange5Role,
        StnNumRole,
        StnNameRole,
        LineRole,
        LineColourRole,
        InterchangeRole,
        ActionRole,
        TowardsRole,
        StnNumLeftRole,
        StnNumRightRole
    };
    enum LoadStatus {
        Null,
        Ready,
        Error
    };
    enum Action {
        OnTrain,
        Depart,
        Arrive,
        GetOff,
        Exit,
        Transfer,
        ExitTransfer
    };
    enum Preference {
        ConvenientlyTransfer = RouteSearch::ConvenientlyTransfer,
        LessTimeTransfer,
        ShortDistance,
        Balance
    };
    enum CircleLineDirection {
        InnerCircle,
        OuterCircle
    };

    StationModel(QObject *parent = 0);
    ~StationModel();
    Q_INVOKABLE void open_current_database();
    Q_INVOKABLE void open_current_database(const QString &connection_name);
    Q_INVOKABLE void open_selected_database(const QString &db_name, const QString &connection_name);
    Q_INVOKABLE void close_current_database();
    Q_INVOKABLE int getfulllistdata();
    Q_INVOKABLE int getmapdata();
    Q_INVOKABLE int getroutelistdata();
    Q_INVOKABLE int get_stations_count_pass_by();
    Q_INVOKABLE int get_interchanges_count_pass_by();
    Q_INVOKABLE int get_unpaid_interchanges_count_pass_by();
    void addstation(const Station &station);
    void resetmodel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int fulllistrowcount() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant data(const int &row, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant fulllistdata(const int &row, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QString linecolourat(const int &row);
    Q_INVOKABLE bool search(const int &s, const int &d, const int &p, const int &multiple = 10);
    Q_INVOKABLE int routedata(const int &index) const;
    Q_INVOKABLE int routelistrowcount() const;
    Q_INVOKABLE QString getcity() const;
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Station> stationlist;
    QList<Station> fullstationlist;
    //int* station_index;
    //QList<int> station_index;
    QVector<int> station_index;
    QList<int> routestationlist;
    int stations_count_pass_by = -1;
    int interchanges_count_pass_by = -1;
    int unpaid_interchanges_count_pass_by = -1;
    Graphm systemmap;
    int station_count;
    QList<int>* routestationlist_ptr = &routestationlist;
    Graphm* systemmap_ptr = &systemmap;
    QSqlDatabase db;
    QLocale locale = QLocale::system();
    QString lang = locale.name().mid(0,2);
    AppSettings settings;
    int station_name_language;
signals:
    void getRouteListDataFinished();
};

#endif // STATIONMODEL_H
