#include "utils.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include "note.h"
#include <QtXml>

namespace Utils {
void checkBookmarksFile(QFile* f){
    QFileInfo fi(*f);
    if (!fi.exists()) {
        if (!f->open(QIODevice::WriteOnly)) {
            qDebug() << "Unable to open the XML file for writing";
        }
        QTextStream stream(f);
        stream << "<root>\n  <bookmarks>\n  </bookmarks>\n  <notes>\n  </notes>\n</root>"  << endl;
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

QList<Note>* getNotesFromDoc(QDomDocument &doc) {
    QDomNodeList notes = doc.elementsByTagName("note");
    QList<Note>* a = new QList<Note>();
    for (int i=0; i< notes.size(); i++) {
        QDomNode nt = notes.item(i);
        QDomNamedNodeMap attrs = nt.attributes();
        QString xstr(attrs.namedItem(QString("x")).nodeValue());
        QString ystr(attrs.namedItem(QString("y")).nodeValue());
        qreal xr = xstr.toFloat();
        qreal yr = ystr.toFloat();
        //qDebug() << xstr << xr ;
        //qDebug() << ystr << yr ;
        a->append(Note(
                     attrs.namedItem(QString("page")).nodeValue().toInt(),
                     xr,
                     yr,
                     attrs.namedItem(QString("r")).nodeValue().toInt(),
                     attrs.namedItem(QString("g")).nodeValue().toInt(),
                     attrs.namedItem(QString("b")).nodeValue().toInt(),
                     nt.firstChild().toText().data()
                     )
                 );
    }
    return a;
}


}

