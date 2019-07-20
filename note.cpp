#include "note.h"
#include <QDomDocument>

Note::Note(int p, qreal x, qreal y, int r, int g, int b, QString txt):
    p(p), x(x), y(y), r(r), g(g), b(b), text(txt)
{

}
QDomElement Note::asElementOf(QDomDocument doc) {
    QDomElement n = doc.createElement(QString("note"));
    n.setAttribute("page", QString::number(p));
    n.setAttribute("x", QString::number(x));
    n.setAttribute("y", QString::number(y));
    n.setAttribute("r", QString::number(r));
    n.setAttribute("g", QString::number(g));
    n.setAttribute("b", QString::number(b));
    QDomText t = doc.createTextNode(text);
    n.appendChild(t);
    return n;
}

