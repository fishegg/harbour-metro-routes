#include <qdebug.h>
#include "stationmodel.h"
#include "station.h"

StationModel::StationModel(QObject *parent) : QAbstractListModel(parent)
{
    //getdata();
    /*station_name_language = settings.get_currentIndex_language();
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString database = settings.get_db_name();
    db.setDatabaseName(database);*/
//    db.setDatabaseName("/usr/share/harbour-metro-routes/guangzhou_foshan_20241228.sqlite");
//    db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+"/guangzhou_foshan_20241228.sqlite");
    /*if(db.open())
    {
        qDebug() << "connection opened" << endl;
        QSqlQuery query("SELECT city_zh, name_zh, version, station_count FROM data_information");
        query.next();
        station_count = query.value("station_count").toInt();*/
//        station_count = query.value(5).toInt();
        /*qDebug() << "station count" << station_count;*/

        //station_index = new int[station_count];
        //for(int i=0;i<station_count;i++)
            //station_index[i]=-1;
        /*station_index.fill(-1, station_count);
    }
    getfulllistdata();
    getmapdata();*/
}

StationModel::~StationModel()
{
    db.close();
    //delete [] station_index;
    //qDebug() << "delete station index";
    //station_index = nullptr;
}

void StationModel::open_current_database(){
    station_name_language = settings.get_currentIndex_language();
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString db_name = settings.get_db_name();
//    qDebug() << "db_name" << db_name << endl;
    db.setDatabaseName(db_name);
    qDebug() << db.databaseName();
    if(db.open()){
        qDebug() << "stationmodel current database opened" << endl;
        QSqlQuery query("SELECT city_zh, name_zh, version, station_count FROM data_information");
        query.next();
        station_count = query.value("station_count").toInt();
        qDebug() << "station count" << station_count;
        station_index.fill(-1, station_count);
    }
    getfulllistdata();
    getmapdata();
}

void StationModel::open_selected_database(const QString &db_name){
    station_name_language = settings.get_currentIndex_language();
    if(station_name_language == 1){
        lang = "zh";
    }
    else if (station_name_language == 2){
        lang = "en";
    }
    else{
        lang = locale.name().mid(0,2);
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "db_name" << db_name;
    db.setDatabaseName(db_name);
    if(db.open()){
        qDebug() << "stationmodel selected database opened";
        QSqlQuery query("SELECT city_zh, name_zh, version, station_count FROM data_information");
        query.next();
        station_count = query.value("station_count").toInt();
        qDebug() << "station count" << station_count;
        station_index.fill(-1, station_count);
    }
    getfulllistdata();
    getmapdata();
}

void StationModel::close_current_database(){
    db.close();
}

int StationModel::getfulllistdata()
{
    //int i;//, j;
    if(db.open())
    {
        qDebug() << "get full list connection opened" << endl;
        fullstationlist.clear();
        int number = 0, line_count, interchange[5], line_id, unpaid_interchange[5];
        QString station_name, station_number, line_name, line_colour;
        //QString serial_distance;
        bool is_interchange, in_use;

        /*beginResetModel();
        stationlist.clear();
        endResetModel();*/
        //resetmodel();

        QSqlQuery query("SELECT no_, station_no_, station_name_zh, station_name_en, is_interchange, line_count, line_id, interchange_1, interchange_2, interchange_3, interchange_4, interchange_5, unpaid_interchange_1, unpaid_interchange_2, unpaid_interchange_3, unpaid_interchange_4, unpaid_interchange_5, in_use FROM stations_list");
        QSqlQuery queryline;
        while(query.next())
        {
            in_use = query.value("in_use").toBool();
//            in_use = query.value(12).toBool();
            if(in_use != false)
            {
                /*station_number = query.value("station_no_").toString();
                number = query.value("no_").toInt();
                station_name = query.value("station_name_zh").toString();
                is_interchange = query.value("is_interchange").toBool();
                line_count = query.value("line_count").toInt();
                line_id = query.value("line_id").toInt();
                interchange[0] = query.value("interchange_1").toInt();
                interchange[1] = query.value("interchange_2").toInt();
                interchange[2] = query.value("interchange_3").toInt();
                unpaid_interchange[0] = query.value("unpaid_interchange_1").toInt();
                unpaid_interchange[1] = query.value("unpaid_interchange_2").toInt();
                unpaid_interchange[2] = query.value("unpaid_interchange_3").toInt();*/
                if(query.isValid())
                {
                    station_number = query.value("station_no_").toString();
                    number = query.value("no_").toInt();
                    if(lang == "zh"){
                        station_name = query.value("station_name_zh").toString();
                    }
                    else{
                        station_name = query.value("station_name_en").toString();
                    }
                    is_interchange = query.value("is_interchange").toBool();
                    line_count = query.value("line_count").toInt();
                    line_id = query.value("line_id").toInt();
                    interchange[0] = query.value("interchange_1").toInt();
                    interchange[1] = query.value("interchange_2").toInt();
                    interchange[2] = query.value("interchange_3").toInt();
                    interchange[3] = query.value("interchange_4").toInt();
                    interchange[4] = query.value("interchange_5").toInt();
                    unpaid_interchange[0] = query.value("unpaid_interchange_1").toInt();
                    unpaid_interchange[1] = query.value("unpaid_interchange_2").toInt();
                    unpaid_interchange[2] = query.value("unpaid_interchange_3").toInt();
                    unpaid_interchange[3] = query.value("unpaid_interchange_4").toInt();
                    unpaid_interchange[4] = query.value("unpaid_interchange_5").toInt();
//                    station_number = query.value(1).toString();
//                    number = query.value(0).toInt();
//                    station_name = query.value(2).toString();
//                    is_interchange = query.value(3).toBool();
//                    line_count = query.value(4).toInt();
//                    line_id = query.value(5).toInt();
//                    interchange[0] = query.value(6).toInt();
//                    interchange[1] = query.value(7).toInt();
//                    interchange[2] = query.value(8).toInt();
//                    unpaid_interchange[0] = query.value(9).toInt();
//                    unpaid_interchange[1] = query.value(10).toInt();
//                    unpaid_interchange[2] = query.value(11).toInt();
                }
                else
                {
                    qDebug() << "query last error" << query.lastError();
                    return Error;
                }

                /*queryline.clear();*/queryline.finish();
                queryline.prepare("SELECT line_name_zh, line_name_en, line_colour FROM lines_list WHERE line_id=:line_id");
                queryline.bindValue(":line_id",line_id);
                queryline.exec();
                queryline.first();
                /*line_name = queryline.value("line_name_zh").toString();
                line_colour = queryline.value("line_colour").toString();*/
                if(queryline.isValid())
                {
                    if(lang == "zh"){
                        line_name = queryline.value("line_name_zh").toString();
                    }
                    else{
                        line_name = queryline.value("line_name_en").toString();
                    }
                    line_colour = queryline.value("line_colour").toString();
//                    line_name = queryline.value(0).toString();
//                    line_colour = queryline.value(1).toString();
                }
                else
                {
                    qDebug() << "queryline last error" << queryline.lastError();
                    return Error;
                }

                Station station(number,line_count,interchange[0],interchange[1],interchange[2],interchange[3],interchange[4],unpaid_interchange[0],unpaid_interchange[1],unpaid_interchange[2],unpaid_interchange[3],unpaid_interchange[4],station_number,station_name,line_id,line_name,line_colour,is_interchange);
                //addstation(station);
                fullstationlist << station;
                station_index[number] = fullstationlist.size() - 1;
            }
            /**/
            //Station station(number,lines_count,same_station[0],same_station[1],same_station[2],station_number,station_name,line_name,interchange);
            //addstation(station);
            //qDebug() << query.value("station_no_").toString() + query.value("station_name").toString();
        }
        //station_count = number + 1;
        if(station_count != number + 1)
        {
            return Error;
        }

        /*query.clear();
        systemmap.Init(station_count);
        query.exec("SELECT weight FROM graph_weights_list");
        query.first();
        i = 0;
        do
        {
            int cost;//, row = i*station_count;
            int row = i / station_count, column = i % station_count;
            //serial_distance = query.value("weight").toString();//.toUtf8().data();
            cost = query.value("weight").toInt();
            //qDebug() << "station count" << station_count;
            //qDebug() << serial_distance << endl;
            /*for(j=0; j<station_count; j++)
            {
                cost = serial_distance.section(' ',j,j).toInt();
                systemmap.setedge(i,j,cost);
                qDebug() << "i*j" << row+j << systemmap.weight(i,j);
            }*/
            //systemmap.setedge(row,column,cost);
            //qDebug() << i << row << column << systemmap.weight(row,column);
            //i++;
        //}while(query.next());
        //systemmap.qdebugwholegraph();
        qDebug() << "get full list data finished";
        return Ready;
    }
    else
    {
        qDebug() << "connection open failed";
        return Error;
    }
    //db.close();
}

int StationModel::getmapdata()
{
    int i;//, j;
    if(db.open())
    {
        qDebug() << "get map connection opened";
        qDebug() << "station count" << station_count;

        if(station_count == 0)
        {
            return Error;
        }

        systemmap.Init(station_count);
        QSqlQuery query("SELECT weight FROM graph_weights_list");
        i = 0;
        while(query.next())
        {
            int cost;//, row = i*station_count;
            int row = i / station_count, column = i % station_count;
            //serial_distance = query.value("weight").toString();//.toUtf8().data();
            if(query.isValid())
            {
                cost = query.value("weight").toInt();
            }
            else
            {
                qDebug() << "query map last error" << query.lastError();
                return Error;
            }
            //qDebug() << "station count" << station_count;
            //qDebug() << serial_distance << endl;
            /*for(j=0; j<station_count; j++)
            {
                cost = serial_distance.section(' ',j,j).toInt();
                systemmap.setedge(i,j,cost);
                qDebug() << "i*j" << row+j << systemmap.weight(i,j);
            }*/
            systemmap.setedge(row,column,cost);
            //qDebug() << i << row << column << systemmap.weight(row,column);
            i++;
        }
        /*query.exec("SELECT weight FROM graph_weights_list");
        query.first();
        i = 0;
        do
        {
            int cost;//, row = i*station_count;
            int row = i / station_count, column = i % station_count;
            //serial_distance = query.value("weight").toString();//.toUtf8().data();
            cost = query.value("weight").toInt();
            //qDebug() << "station count" << station_count;
            //qDebug() << serial_distance << endl;
            /*for(j=0; j<station_count; j++)
            {
                cost = serial_distance.section(' ',j,j).toInt();
                systemmap.setedge(i,j,cost);
                qDebug() << "i*j" << row+j << systemmap.weight(i,j);
            }*/
            //systemmap.setedge(row,column,cost);
            //qDebug() << i << row << column << systemmap.weight(row,column);
            /*i++;
        }while(query.next());*/
        //systemmap.qdebugwholegraph();
        qDebug() << "get map data finished";
        return Ready;
    }
    else
    {
        qDebug() << "connection open failed";
        return Error;
    }
    //db.close();
}

int StationModel::getroutelistdata()
{
    //int i;//, j;
    if(db.open())
    {
        //qDebug() << "connection opened" << endl;
        int number = 0, line_count, interchange[5], line_id, unpaid_interchange[5];
        QString station_name, station_number, line_name, line_colour;
        bool is_interchange, is_circle;
        QString /*action(""), */towards("");
        int action = OnTrain;
        int number_temp = 0;
        QSqlQuery query;
        QSqlQuery queryline;
        int transfer_type = -1, towards_large, towards_little;
        int circle_line_direction = InnerCircle;

        /*beginResetModel();
        stationlist.clear();
        endResetModel();*/
        resetmodel();

        int route_station_count = routelistrowcount();
        int i = 0;

        //qDebug() << "while(!routestationlist.isEmpty())";
        //qDebug() << "routestationlist.size() = " << routestationlistrowcount();
        if(routelistrowcount() == 1)
        {
            return Error;
        }
        qDebug() << "routestationlist:" << routestationlist.size() << endl;
        while(!routestationlist.isEmpty())
        {
            i++;
            number_temp = routestationlist.constFirst();
            routestationlist.removeFirst();
            /*query.clear();*/query.finish();
            query.prepare("SELECT no_, station_no_, station_name_zh, station_name_en, is_interchange, line_count, line_id, interchange_1, interchange_2, interchange_3, interchange_4, interchange_5, unpaid_interchange_1, unpaid_interchange_2, unpaid_interchange_3, unpaid_interchange_4, unpaid_interchange_5 FROM stations_list WHERE no_=:number");
            query.bindValue(":number",number_temp);
            query.exec();
            query.first();
//            station_number = query.value("station_no_").toString();
//            number = query.value("no_").toInt();
//            station_name = query.value("station_name_zh").toString();
//            is_interchange = query.value("is_interchange").toBool();
//            line_count = query.value("line_count").toInt();
//            line_id = query.value("line_id").toInt();
//            interchange[0] = query.value("interchange_1").toInt();
//            interchange[1] = query.value("interchange_2").toInt();
//            interchange[2] = query.value("interchange_3").toInt();
//            unpaid_interchange[0] = query.value("unpaid_interchange_1").toInt();
//            unpaid_interchange[1] = query.value("unpaid_interchange_2").toInt();
//            unpaid_interchange[2] = query.value("unpaid_interchange_3").toInt();
            if(query.isValid())
            {
                station_number = query.value("station_no_").toString();
                number = query.value("no_").toInt();
                if(lang == "zh"){
                    station_name = query.value("station_name_zh").toString();
                }
                else{
                    station_name = query.value("station_name_en").toString();
                }
                is_interchange = query.value("is_interchange").toBool();
                line_count = query.value("line_count").toInt();
                line_id = query.value("line_id").toInt();
                interchange[0] = query.value("interchange_1").toInt();
                interchange[1] = query.value("interchange_2").toInt();
                interchange[2] = query.value("interchange_3").toInt();
                interchange[4] = query.value("interchange_5").toInt();
                unpaid_interchange[0] = query.value("unpaid_interchange_1").toInt();
                unpaid_interchange[1] = query.value("unpaid_interchange_2").toInt();
                unpaid_interchange[2] = query.value("unpaid_interchange_3").toInt();
                unpaid_interchange[3] = query.value("unpaid_interchange_4").toInt();
                unpaid_interchange[4] = query.value("unpaid_interchange_5").toInt();
//                station_number = query.value(1).toString();
//                number = query.value(0).toInt();
//                station_name = query.value(2).toString();
//                is_interchange = query.value(3).toBool();
//                line_count = query.value(4).toInt();
//                line_id = query.value(5).toInt();
//                interchange[0] = query.value(6).toInt();
//                interchange[1] = query.value(7).toInt();
                interchange[3] = query.value("interchange_4").toInt();
//                interchange[2] = query.value(8).toInt();
//                unpaid_interchange[0] = query.value(9).toInt();
//                unpaid_interchange[1] = query.value(10).toInt();
//                unpaid_interchange[2] = query.value(11).toInt();
            }
            else
            {
                qDebug() << "getroutelistdata query last error" << query.lastError();
                return Error;
            }

            /*queryline.clear();*/queryline.finish();
            queryline.prepare("SELECT line_name_zh, line_name_en, line_colour, towards_little, towards_large, is_circle FROM lines_list WHERE line_id=:line_id");
            queryline.bindValue(":line_id",line_id);
            queryline.exec();
            queryline.first();
            /*line_name = queryline.value("line_name_zh").toString();
            line_colour = queryline.value("line_colour").toString();*/
            if(queryline.isValid())
            {
                if(lang == "zh"){
                    line_name = queryline.value("line_name_zh").toString();
                }
                else{
                    line_name = queryline.value("line_name_en").toString();
                }
                line_colour = queryline.value("line_colour").toString();
                towards_little = queryline.value("towards_little").toInt();
                towards_large = queryline.value("towards_large").toInt();
                is_circle = queryline.value("is_circle").toBool();
//                qDebug()<<towards_little<<towards_large<<queryline.value(2).toInt()<<queryline.value(3).toInt();
            }
            else
            {
                qDebug() << "getroutelistdata queryline last error" << queryline.lastError();
                return Error;
            }

            if(i == 1)
            {
                action = Depart;
                number_temp = routestationlist.constFirst();
                qDebug()<<number_temp<<towards_large<<number<<towards_little;
                if(number_temp > number)
                {
                    //number_temp = queryline.value("towards_large").toInt();
                    if(queryline.isValid())
                    {
                        if(is_circle == false){
                            number_temp = queryline.value("towards_large").toInt();
//                            qDebug()<<number_temp;
                        }
                        else{
                            circle_line_direction = OuterCircle;
                            if(number_temp == towards_large && number == towards_little){
                                circle_line_direction = InnerCircle;
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " queryline last error" << queryline.lastError();
                        //return Error;
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        towards = query.value(0).toString();
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                else
                {
                    //number_temp = queryline.value("towards_little").toInt();
                    qDebug()<<number_temp<<towards_large<<number<<towards_little;
                    if(queryline.isValid())
                    {
                        if(is_circle == false){
                            number_temp = queryline.value("towards_little").toInt();
                        }
                        else{
                            circle_line_direction = InnerCircle;
                            if(number_temp == towards_little && number == towards_large){
                                circle_line_direction = OuterCircle;
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " queryline last error" << queryline.lastError();
                        //return Error;
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        towards = query.value(0).toString();
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                //direction = "方向";
            }
            else if(i == route_station_count)
            {
                action = Arrive;
            }
            else if(transfer_type == Transfer)
            {
                action = Transfer;
                number_temp = routestationlist.constFirst();
                qDebug()<<number_temp<<towards_large<<number<<towards_little;
                if(number_temp > number)
                {
                    if(is_circle == false){
                        number_temp = queryline.value("towards_large").toInt();
                    }
                    else{
                        circle_line_direction = OuterCircle;
                        if(number_temp == towards_large && number == towards_little){
                            circle_line_direction = InnerCircle;
                        }
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        towards = query.value(0).toString();
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                else
                {
                    qDebug()<<number_temp<<towards_large<<number<<towards_little;
                    if(is_circle == false){
                        number_temp = queryline.value("towards_little").toInt();
                    }
                    else{
                        circle_line_direction = InnerCircle;
                        if(number_temp == towards_little && number == towards_large){
                            circle_line_direction = OuterCircle;
                        }
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        towards = query.value(0).toString();
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                //direction = "方向";
                transfer_type = -1;
            }
            else if(transfer_type == ExitTransfer)
            {
                action = ExitTransfer;
                number_temp = routestationlist.constFirst();
                qDebug()<<number_temp<<towards_large<<number<<towards_little;
                if(number_temp > number)
                {
                    if(is_circle == false){
                        number_temp = queryline.value("towards_large").toInt();
                    }
                    else{
                        circle_line_direction = OuterCircle;
                        if(number_temp == towards_large && number == towards_little){
                            circle_line_direction = InnerCircle;
                        }
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        if(lang == "zh"){
                            towards = query.value("station_name_zh").toString();
                        }
                        else{
                            towards = query.value("station_name_en").toString();
                        }
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                else
                {
                    qDebug()<<number_temp<<towards_large<<number<<towards_little;
                    if(is_circle == false){
                        number_temp = queryline.value("towards_little").toInt();
                    }
                    else{
                        circle_line_direction = InnerCircle;
                        if(number_temp == towards_little && number == towards_large){
                            circle_line_direction = OuterCircle;
                        }
                    }
                    /*query.clear();*/query.finish();
                    if(lang == "zh"){
                        query.prepare("SELECT station_name_zh FROM stations_list WHERE no_=:number");
                    }
                    else{
                        query.prepare("SELECT station_name_en FROM stations_list WHERE no_=:number");
                    }
                    query.bindValue(":number",number_temp);
                    query.exec();
                    query.first();
                    //towards = query.value("station_name_zh").toString();
                    if(query.isValid())
                    {
                        if(lang == "zh"){
                            towards = query.value("station_name_zh").toString();
                        }
                        else{
                            towards = query.value("station_name_en").toString();
                        }
                        if(is_circle == true&&circle_line_direction == OuterCircle){
                            if(lang == "zh"){
                                towards = towards + "/外环";
                            }
                            else{
                                towards = towards + "/Outer Circle";
                            }
                        }
                        if(is_circle == true&&circle_line_direction == InnerCircle){
                            if(lang == "zh"){
                                towards = towards + "/内环";
                            }
                            else{
                                towards = towards + "/Inner Circle";
                            }
                        }
                    }
                    else
                    {
                        qDebug() << "getroutelistdata " << i << " query last error" << queryline.lastError();
                        //return Error;
                    }
                }
                //direction = "方向";
                transfer_type = -1;
            }
            else if(is_interchange)
            {
                number_temp = routestationlist.constFirst();
                if(interchange[0] == number_temp ||
                        interchange[1] == number_temp ||
                        interchange[2] == number_temp ||
                        interchange[3] == number_temp ||
                        interchange[4] == number_temp)
                {
                    transfer_type = Transfer;
                    action = GetOff;
                }
                else if(unpaid_interchange[0] == number_temp ||
                        unpaid_interchange[1] == number_temp ||
                        unpaid_interchange[2] == number_temp ||
                        unpaid_interchange[3] == number_temp ||
                        unpaid_interchange[4] == number_temp)
                {
                    transfer_type = ExitTransfer;
                    action = Exit;
                }
            }
            else {
                action = OnTrain;
            }
            Station station(number,line_count,interchange[0],interchange[1],interchange[2],interchange[3],interchange[4],unpaid_interchange[0],unpaid_interchange[1],unpaid_interchange[2],unpaid_interchange[3],unpaid_interchange[4],station_number,station_name,line_id,line_name,line_colour,is_interchange);
            /*if(action != -1 || direction != "")
            {
                station.setactiondirection(action,direction);
                action = -1;
                direction = "";
            }*/
            station.setactiontowards(action,towards);
            action = OnTrain;
            towards = "";
            addstation(station);
        }

        qDebug() << "get route list data finished";
        return Ready;
    }
    else
    {
        qDebug() << "connection open failed";
        return Error;
    }
    //db.close();
}

void StationModel::addstation(const Station &station)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    stationlist << station;
    endInsertRows();
}

void StationModel::resetmodel()
{
    beginResetModel();
    stationlist.clear();
    endResetModel();
}

int StationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stationlist.count();
}

int StationModel::fulllistrowcount() const
{
    return fullstationlist.count();
}

QVariant StationModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << "index.row" << index.row() << endl;
    if(index.row() < 0 || index.row() > stationlist.count())
    {
        return QVariant();
    }
//    qDebug() << "data() role" << role << endl;
//    qDebug() << "data() index.row() = " << index.row() << " index.column() = " << index.column() << endl;

    const Station &station = stationlist[index.row()];
    if(role == NumRole)
    {
        return station.number();
    }
    else if(role == CountRole)
    {
        return station.linecount();
    }
    else if(role == Interchange1Role)
    {
        return station.interchangeat(1);
    }
    else if(role == Interchange2Role)
    {
        return station.interchangeat(2);
    }
    else if(role == Interchange3Role)
    {
        return station.interchangeat(3);
    }
    else if(role == Interchange4Role)
    {
        return station.interchangeat(4);
    }
    else if(role == Interchange5Role)
    {
        return station.interchangeat(5);
    }
    else if(role == UnpaidInterchange1Role)
    {
        return station.unpaidinterchangeat(1);
    }
    else if(role == UnpaidInterchange2Role)
    {
        return station.unpaidinterchangeat(2);
    }
    else if(role == UnpaidInterchange3Role)
    {
        return station.unpaidinterchangeat(3);
    }
    else if(role == UnpaidInterchange4Role)
    {
        return station.unpaidinterchangeat(4);
    }
    else if(role == UnpaidInterchange5Role)
    {
        return station.unpaidinterchangeat(5);
    }
    else if(role == StnNumRole)
    {
        return station.stationnumber();
    }
    else if(role == StnNameRole)
    {
        return station.stationname();
    }
    else if(role == LineRole)
    {
        return station.linename();
    }
    else if(role == LineColourRole)
    {
        return station.linecolour();
    }
    else if(role == InterchangeRole)
    {
        return station.isinterchange();
    }
    else if(role == ActionRole)
    {
        return station.action();
    }
    else if(role == TowardsRole)
    {
        return station.towards();
    }
    else if(role == StnNumLeftRole)
    {
        return station.stationnumberleft();
    }
    else if(role == StnNumRightRole)
    {
        return station.stationnumberright();
    }

    return QVariant();
}

QVariant StationModel::data(const int &row, int role) const
{
    if(row < 0 || row > stationlist.count())
    {
        return QVariant();
    }
    QModelIndex index = createIndex(row,0);
    return data(index,role);
}

QVariant StationModel::fulllistdata(const int &row, int role) const
{
    if(row < 0 || row > fullstationlist.count())
    {
        //qDebug() << "sigledata get failed" << endl;
        return QVariant();
    }
    const Station &station = fullstationlist[row];
    if(role == NumRole)
    {
        return station.number();
    }
    else if(role == CountRole)
    {
        return station.linecount();
    }
    else if(role == Interchange1Role)
    {
        return station.interchangeat(1);
    }
    else if(role == Interchange2Role)
    {
        return station.interchangeat(2);
    }
    else if(role == Interchange3Role)
    {
        return station.interchangeat(3);
    }
    else if(role == StnNumRole)
    {
        return station.stationnumber();
    }
    else if(role == StnNameRole)
    {
        return station.stationname();
    }
    else if(role == LineRole)
    {
        return station.linename();
    }
    else if(role == LineColourRole)
    {
        return station.linecolour();
    }
    else if(role == InterchangeRole)
    {
        return station.isinterchange();
    }
    else if(role == ActionRole)
    {
        return station.action();
    }
    else if(role == TowardsRole)
    {
        return station.towards();
    }
    //QModelIndex index = createIndex(row,0);
    //qDebug() << "singledata() role" << role << endl;
    //qDebug() << "singledata() index.row() = " << index.row() << " index.column() = " << index.column() << endl;
    //QVariant d = data(index,role);
    //qDebug() << "single data d = " << d.toString() << endl;
    //return d;
    //return data(index,role);
}

QString StationModel::linecolourat(const int &row)
{
    if(row < 0 || row > stationlist.count())
    {
        return QString();
    }
    QModelIndex index = createIndex(row,0);
    QString colour = data(index,LineColourRole).toString();
    return colour;
}

QHash<int, QByteArray> StationModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NumRole] = "number";
    roles[CountRole] = "line_count";
    roles[Interchange1Role] = "interchange_1";
    roles[Interchange2Role] = "interchange_2";
    roles[Interchange3Role] = "interchange_3";
    roles[Interchange4Role] = "interchange_4";
    roles[Interchange5Role] = "interchange_5";
    roles[StnNumRole] = "station_number";
    roles[StnNameRole] = "station_name";
    //roles[LineRole] = "line_name";
    roles[LineRole] = "line_name";
    roles[LineColourRole] = "line_colour";
    roles[InterchangeRole] = "is_interchange";
    roles[ActionRole] = "action";
    roles[TowardsRole] = "towards";
    return roles;
}

bool StationModel::search(const int &s, const int &d, const int &p, const int &multiple)
{
    RouteSearch routesearch(station_count);
    if(!routesearch.search(systemmap_ptr,fullstationlist,station_index,station_count,s,d,p,multiple))
        return false;
    if(!routesearch.getresult(routestationlist_ptr))//,fullstationlist);
        return false;
    return true;
}

int StationModel::routedata(const int &index) const
{
    return routestationlist.at(index);
}

int StationModel::routelistrowcount() const
{
    return routestationlist.count();
}

QString StationModel::getcity() const
{
    QSqlQuery query;
    if(lang == "zh"){
        query.exec("SELECT city_zh FROM data_information");
    }
    else{
        query.exec("SELECT city_en FROM data_information");
    }
    query.first();
    QString city;
    city = query.value(0).toString();
    query.finish();
    return city;
}
