#include "config.h"

Config::Config():
    invert(false), dpi(96)
{
    QFile *f = new QFile(QDir::homePath() + "/.config/pdq.xml");
    if (!f->open(QIODevice::ReadOnly) || !doc.setContent(f)) {
    }
    f->close();
    delete f;

    QDomNodeList ress = doc.elementsByTagName(QString("dpi"));
    if (!ress.isEmpty()) {
        QString res = ress.at(0).toElement().text() ;
        dpi = res.toInt();
    }

    invert = !doc.elementsByTagName(QString("invert")).isEmpty();

}
