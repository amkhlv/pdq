#ifndef NOTE_H
#define NOTE_H

#include <QString>

class Note
{
public:
    Note(int p, qreal x, qreal y, int r, int g, int b, QString txt);
    int p;
    qreal x;
    qreal y;
    int r;
    int g;
    int b;
    QString text;
};

#endif // NOTE_H
