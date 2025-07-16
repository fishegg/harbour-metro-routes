#include "linemodel.h"

LineModel::LineModel(QObject *parent) : QAbstractListModel(parent){
    db = QSqlDatabase::addDatabase("QSQLITE", "Line");
    QString database = settings.get_db_name();
    db.setDatabaseName(database);
    if(db.open()){
        qDebug() << "line model database opened" << endl;
    }
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    get_full_list();
}

LineModel::~LineModel(){
    db.close();
    qDebug() << "line model database closed" << endl;
}

void LineModel::open_current_database(){
    db = QSqlDatabase::addDatabase("QSQLITE", "Line");
    QString db_name = settings.get_db_name();
    qDebug() << "line model db_name" << db_name;
    db.setDatabaseName(db_name);
    if(db.open()){
        qDebug() << "line model database opened" << endl;
    }
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    get_full_list();
}

void LineModel::open_selected_database(const QString &db_name){
    db = QSqlDatabase::addDatabase("QSQLITE", "Line");
    db.setDatabaseName(db_name);
    if(db.open()){
        qDebug() << "line model database opened" << endl;
    }
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    get_full_list();
}

void LineModel::close_current_database(){
    db.close();
}

int LineModel::get_full_list(){
    if(db.open()){
        qDebug() << "get full list start" << endl;
        lines_list.clear();
        int line_id = 0, towards_little, towards_large;
        QString line_name_zh, line_name_en, line_colour;
        bool is_circle;

        QSqlQuery query("SELECT line_id, line_name_zh, line_name_en, towards_little, towards_large, line_colour, is_circle FROM lines_list");
        while(query.next()){
            if(query.isValid()){
//                qDebug() << query.isValid();
                line_id = query.value("line_id").toInt();
                line_name_zh = query.value("line_name_zh").toString();
                line_name_en = query.value("line_name_en").toString();
                towards_little = query.value("towards_little").toInt();
                towards_large = query.value("towards_large").toInt();
                line_colour = query.value("line_colour").toString();
                is_circle = query.value("is_circle").toBool();
//                qDebug() << line_id << line_name_zh << line_colour << endl;
            }
            else{
                qDebug() << "query error" << query.lastError();
                return Error;
            }
            Line line(line_id,towards_little,towards_large,line_name_zh,line_name_en,line_colour,is_circle);
            lines_list << line;
//            line_index[line_id] = lines_list.size() - 1;
        }
        qDebug() << "get lines list finished" << endl;
        return Ready;
    }
    else{
        qDebug() << "connection open failed" << endl;
        return Error;
    }
}

void LineModel::add_line(const Line &line){
    qDebug() << "line model add line" << endl;
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    lines_list << line;
    endInsertRows();
}

void LineModel::reset_model(){
    beginResetModel();
    lines_list.clear();
    endResetModel();

}

int LineModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return lines_list.count();
}

QVariant LineModel::data(const QModelIndex &index, int role) const {
//    qDebug() << "data" << endl;
    if(index.row() < 0 || index.row() > lines_list.count()){
        return QVariant();
    }
    const Line &line = lines_list[index.row()];
    if(role == LineIdRole){
        return line.get_line_id();
    }
    else if(role == LineNameZhRole){
        return line.get_line_name_zh();
    }
    else if(role == LineNameEnRole){
        return line.get_line_name_en();
    }
    else if(role == LineNameRole){
        if(lang == "zh"){
            return line.get_line_name_zh();
        }
        else{
            return line.get_line_name_en();
        }
    }
    else if(role == TowardsLittleRole){
        return line.get_towards_litte();
    }
    else if(role == TowardsLargeRole){
        return line.get_towards_large();
    }
    else if(role == LineColourRole){
        return line.get_line_colour();
    }
    else if(role == IsCircleRole){
        return line.get_is_circle();
    }
    return QVariant();
}

QVariant LineModel::data(const int &row, int role) const {
    if(row < 0 || row > lines_list.count()){
        return QVariant();
        QModelIndex index = createIndex(row,0);
        return data(index, role);
    }
    return QVariant();
}

QHash<int, QByteArray> LineModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[LineIdRole] = "line_id";
    roles[LineNameZhRole] = "line_name_zh";
    roles[LineNameEnRole] = "line_name_en";
    roles[LineNameRole] = "line_name";
    roles[TowardsLittleRole] = "towards_little";
    roles[TowardsLargeRole] = "towards_large";
    roles[LineColourRole] = "line_colour";
    roles[IsCircleRole] = "is_circle";
    return roles;
}

QString LineModel::get_lang() const {
    return lang;
}
