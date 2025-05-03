#include "line.h"

Line::Line()
{
    line_id = -1;
    towards_little = -1;
    towards_large = -1;
    line_name_zh = "null";
    line_name_en = "null";
    line_colour = "null";
    is_circle = false;
}

Line::Line(int li, int tli, int tla, QString lnz, QString lne, QString lc, bool ic){
    line_id = li;
    towards_little = tli;
    towards_large = tla;
    line_name_zh = lnz;
    line_name_en = lne;
    line_colour = lc;
    is_circle = ic;
}

int Line::get_line_id() const{
    return line_id;
}

int Line::get_towards_litte() const{
    return towards_little;
}

int Line::get_towards_large() const{
    return towards_large;
}

QString Line::get_line_name_zh() const{
    return line_name_zh;
}

QString Line::get_line_name_en() const{
    return line_name_en;
}

QString Line::get_line_colour() const{
    return line_colour;
}

bool Line::get_is_circle() const{
    return is_circle;
}
