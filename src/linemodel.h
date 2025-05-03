#ifndef LINEMODEL_H
#define LINEMODEL_H
#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlError>
#include <QStandardPaths>
#include <QLocale>
#include <qdebug.h>
#include "line.h"
#include "appsettings.h"


class LineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(LineRoles)
    Q_ENUMS(LoadStatus)
public:
    enum LineRoles {
        LineIdRole = Qt::UserRole + 1,
        TowardsLittleRole,
        TowardsLargeRole,
        LineNameZhRole,
        LineNameEnRole,
        LineNameRole,
        LineColourRole,
        IsCircleRole
    };

    enum LoadStatus {
        Null,
        Ready,
        Error
    };

    LineModel(QObject *parent = 0);
    ~LineModel();
    Q_INVOKABLE int get_full_list();
    void add_line(const Line &line);
    void reset_model();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QVariant data(const int &row, int role = Qt::DisplayRole) const;
    Q_INVOKABLE QString get_lang() const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Line> lines_list;
//    QVector<int> line_index;
    QSqlDatabase db;
    QLocale locale = QLocale::system();
    QString lang = locale.name().mid(0,2);
    AppSettings settings;
    int station_name_language = settings.get_currentIndex_language();
};

#endif // LINEMODEL_H
