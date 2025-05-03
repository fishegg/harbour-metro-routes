#ifndef STATION_H
#define STATION_H
#include <QString>


class Station
{
private:
    int num, count, interchange[5], line_id, unpaid_interchange[5];
    QString stn_num, stn_name, line_name;
    bool is_interchange;
    QString /*_action, */_towards;
    QString line_colour;
    int _action;
public:
    Station();
    Station(int n, int c, int i1, int i2, int i3, int i4, int i5, int ui1, int ui2, int ui3, int ui4, int ui5, QString snum, QString sname, int lid, QString lname, QString lcolour, bool i);
    void setactiontowards(int a,QString t);
    int number() const;
    QString stationnumber() const;
    QString stationname() const;
    bool isinterchange() const;
    int linecount() const;
    QString linename() const;
    int lineid() const;
    int interchangeat(int i) const;
    int unpaidinterchangeat(int i) const;
    int action() const;
    QString towards() const;
    QString linecolour() const;
    QString stationnumberleft() const;
    QString stationnumberright() const;
};

#endif // STATION_H
