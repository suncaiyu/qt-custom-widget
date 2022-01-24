#ifndef UTILS_H
#define UTILS_H
#include <QString>
#include <QRgb>
struct ColorString {
    int r = -1;
    int g = -1;
    int b = -1;
    QRgb rgb;
    void setValue(QRgb rgb) {
        r = qRed(rgb);
        g = qGreen(rgb);
        b = qBlue(rgb);
        this->rgb = rgb;
    }
    QString toRGB() {
        QString rgb = "RGB(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ")";
        return rgb;
    }
    QString toHex1() {
        QString hex = "#" + QString::number(r, 16) + QString::number(g, 16) + QString::number(b, 16);
        return hex;
    }
    QString toHex() {
        QString ra, rb, ga, gb, ba, bb;
        div16(r, ra, rb);
        div16(g, ga, gb);
        div16(b, ba, bb);
        return "#" + ra +rb + ga + gb + ba + bb;
    }

private:
    void div16(int value, QString &a, QString &b) {
        int v1 = value / 16;
        int v2 = value % 16;
        a = int2string(v1);
        b = int2string(v2);
    }

    QString int2string(int value) {
        if (value < 10) {
            return QString::number(value);
        } else {
            switch (value) {
            case 10:
                return "A";
            case 11:
                return "B";
            case 12:
                return "C";
            case 13:
                return "D";
            case 14:
                return "E";
            default:
                return "F";
            }
        }
    }
};
#endif // UTILS_H
