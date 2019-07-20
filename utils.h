#ifndef UTILS_H
#define UTILS_H

#include <QFile>
#include <QtXml>
#include "note.h"

namespace Utils {
void checkBookmarksFile(QFile* f) ;
QString bookmarksFileName(QString filename) ;
void writeDocToFile(QDomDocument &doc, QFile* f);
void readDocFromFile(QDomDocument &doc, QFile* f);
QList<Note>* getNotesFromDoc(QDomDocument &doc);
}


#endif // UTILS_H
