import QtQuick 2.0
import Sailfish.Silica 1.0

Label {

    property string tutorialtext: "Scroll down for English tutorial.
如果你想为自己城市的地铁制作数据库，使用本程序进行查询，以下是一些制作数据库的步骤。开始之前，你需要有一些文本处理和SQL的知识。
第1步，创建一个SQLite数据库；
第2步，使用语句创建四张表：
CREATE TABLE data_information(city_zh TEXT,city_en TEXT,name_zh TEXT,name_en TEXT,version TEXT,station_count INTEGER);
CREATE TABLE graph_weights_list(weight INTEGER);
CREATE TABLE lines_list(line_id INTEGER,line_name_zh TEXT,line_name_en TEXT,towards_little INTEGER,towards_large INTEGER,line_colour TEXT, is_circle INTEGER DEFAULT 0);
CREATE TABLE stations_list(no_ INTEGER,station_no_ TEXT,station_name_zh TEXT,station_name_en TEXT,is_interchange INTERGER,line_count INTEGER,line_id TEXT,interchange_1 INTEGER,interchange_2 INTEGER,interchange_3 INTEGER,interchange_4 INTEGER,interchange_5 INTEGER,unpaid_interchange_1 INTEGER,unpaid_interchange_2 INTEGER,unpaid_interchange_3 INTEGER,unpaid_interchange_4 INTEGER,unpaid_interchange_5 INTEGER,in_use INTEGER);
data_information存放的是表的信息，分别是中文城市名、英文城市名、中文地铁营运方名称、英文地铁营运方名称、数据库版本、车站数量，车站数量一定要正确，否则会出错。
graph_weights_list存放的是地铁图，下面再介绍。
lines_list存放的是线路信息，分别是线路id、中文线路名、英文线路名、线路总站（往id小的方向）、线路总站（往id大的方向）、线路颜色（RGB）、是否环线。
stations_list存放的是车站信息，分别是id、车站编号、中文车站名、英文车站名、是否换乘站、车站经过的线路数量、车站属于的线路id、当前车站其他付费区内换乘的线路相同车站的id共5个、当前车站其他非付费区内换乘的线路相同车站的id共5个、是否使用中；
第3步，导入数据；
第4步，在应用程序设置中更改数据库为你自己的数据库，重启程序。
数据示例：
data_information：广州/佛山|Guangzhou/Foshan|广州地铁/佛山地铁/广佛地铁/南海有轨|Guangzhou Metro/Foshan Metro/Guangfo Metro/Nanhai Tram|20241228|465
lines_list：0|1号线|Line 1|0|15|#edcf3d|0
stations_list：0|101|西塱|Xilang|1|2|0|259|-1|-1|-1|-1|-1|-1|-1|-1|-1|1，259表示广佛线的西塱站，1号线和广佛线可以在西塱站换乘
graph_weights_list：使用一个二维数组表示地铁线网图，从(0,0)开始，如果有10个车站，则将10*10共100个格子填上0，然后在地铁线路经过或换乘的位置改为距离，地铁线路站距范围为(300,99999999)，换乘距离范围为(0,300]，建议使用Excel制作数据，然后复制整个表到文本处理软件，将所有制表符“\\t”替换成换行符“\\n”，再导入到graph_weights_list。

If you want to make database for your city metro and use this app to query, below are some steps to make database. Before start, you need some text processing and SQL knowledge.
Step 1, create a SQLite database.
Step 2, use SQL create 4 tables:
CREATE TABLE data_information(city_zh TEXT,city_en TEXT,name_zh TEXT,name_en TEXT,version TEXT,station_count INTEGER);
CREATE TABLE graph_weights_list(weight INTEGER);
CREATE TABLE lines_list(line_id INTEGER,line_name_zh TEXT,line_name_en TEXT,towards_little INTEGER,towards_large INTEGER,line_colour TEXT, is_circle INTEGER DEFAULT 0);
CREATE TABLE stations_list(no_ INTEGER,station_no_ TEXT,station_name_zh TEXT,station_name_en TEXT,is_interchange INTERGER,line_count INTEGER,line_id TEXT,interchange_1 INTEGER,interchange_2 INTEGER,interchange_3 INTEGER,interchange_4 INTEGER,interchange_5 INTEGER,unpaid_interchange_1 INTEGER,unpaid_interchange_2 INTEGER,unpaid_interchange_3 INTEGER,unpaid_interchange_4 INTEGER,unpaid_interchange_5 INTEGER,in_use INTEGER);
data_information holds the information of the table. Those are city name Chinese, city name English, metro operator Chinese, metro operator English, database version, count of stations.
graph_weights_list holds the map of metro. Below will introduce.
lines_list holds the information of metro lines. Those are line id, line name Chinese, line name English, terminal (towards station with little id), terminal (towards station with large id), line colour in RGB, if it is circle line.
stations_list holds the information of metro stations. Those are id, station id, station name Chinese, station name English, if it is interchange, count of lines via this station, line id of this station, 5 id of same stations of other lines (paid area interchange), 5 id of same stations of other lines (unpaid area interchange), if it is in use.
Step 3, import data.
Step 4, change database setting in the app, restart the app.
Data example:
data_information：广州/佛山|Guangzhou/Foshan|广州地铁/佛山地铁/广佛地铁/南海有轨|Guangzhou Metro/Foshan Metro/Guangfo Metro/Nanhai Tram|20241228|465
lines_list：0|1号线|Line 1|0|15|#edcf3d|0
stations_list：0|101|西塱|Xilang|1|2|0|259|-1|-1|-1|-1|-1|-1|-1|-1|-1|1，259 is Xilang station of Guangfo Line，Xilang is interchange of Line 1 and Guangfo Line
graph_weights_list：using a 2 dimension array to represent metro map, start from (0,0), if there are 10 stations, fill the square of 100 (10*10) with 0, then change the digit to distance in the square where metro lines goes through, distance range of station and station is (300,99999999), and interchange walking distance range is (0,300].
It's suggested to use Excel to make the data, then copy the whole sheet to text processing software, replace all \"\\t\" with \"\\n\", then import to graph_weights_list."

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width - Theme.paddingMedium * 2
    wrapMode: Text.WordWrap
    text: tutorialtext
}
