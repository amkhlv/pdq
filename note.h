#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QtXml>
#include <QDomDocument>

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
    QDomElement asElementOf(QDomDocument doc);
};

#endif // NOTE_H
