#ifndef LINE_H
#define LINE_H
#include <QString>


class Line
{
private:
    int line_id, towards_little, towards_large;
    QString line_name_zh, line_name_en, line_colour;
    bool is_circle;
public:
    Line();
    Line(int li, int tli, int tla, QString lnz, QString lne, QString lc, bool ic);
    int get_line_id() const;
    int get_towards_litte() const;
    int get_towards_large() const;
    QString get_line_name_zh() const;
    QString get_line_name_en() const;
    QString get_line_colour() const;
    bool get_is_circle() const;
};

#endif // LINE_H
