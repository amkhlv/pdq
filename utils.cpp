#include "utils.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace Utils {
void checkBookmarksFile(QFile* f){
    QFileInfo fi(*f);
    if (!fi.exists()) {
        if (!f->open(QIODevice::WriteOnly)) {
            qDebug() << "Unable to open the XML file for writing";
        }
        QTextStream stream(f);
        stream << "<root>\n  <bookmarks>\n  </bookmarks>\n</root>"  << endl;
        f->close();
    }
}

QString bookmarksFileName(QString filename) {
    return filename.replace(QRegExp("\\.pdf$"), QString("")) + QString(".pdq");
}

void writeDocToFile(QDomDocument &doc, QFile *f) {
    if (!f->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Unable to open the XML file for writing";
    }
    QTextStream stream(f);
    stream << doc.toString()  << endl;
    f->close();
}

void readDocFromFile(QDomDocument &doc, QFile *f) {
    if (!f->open(QIODevice::ReadOnly) || !doc.setContent(f)) {
        qDebug() << "Unable to open the XML file for reading";
    }
    f->close();
}
}
