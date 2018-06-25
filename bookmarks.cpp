#include "bookmarks.h"
#include "ui_bookmarks.h"
#include <QtXml>
#include <QDebug>
#include <QLabel>
#include <QKeyEvent>
#include "utils.h"

Bookmarks::Bookmarks(QWidget *parent, QString filename) :
    QDialog(parent),
    bookmarksFile(new QFile(filename)),
    labels(QList<QLabel*>()),
    pageNumbers(QList<qint16>()),
    ui(new Ui::Bookmarks)
{
    ui->setupUi(this);
    Utils::checkBookmarksFile(bookmarksFile);
    QDomDocument doc;
    Utils::readDocFromFile(doc, bookmarksFile);
    QDomNodeList bms = doc.elementsByTagName("bookmark");
    for (int i=0; i< bms.size(); i++) {
        QDomNode bm = bms.item(i);
        QDomNamedNodeMap attrs = bm.attributes();
        QDomNode p = attrs.namedItem(QString("page"));
        QDomText t = bm.firstChild().toText();
        QLabel* l = new QLabel(this);
        QString pnumStr = QString(p.firstChild().toText().data());
        int pnum = pnumStr.toInt();
        l->setText(QString(QChar('a' + i)) + QString(" -> ") + t.data() + QString(" -> ") + QString::number(pnum + 1));
        labels.append(l);
        pageNumbers.append(pnum);
        ui->verticalLayout->findChild<QVBoxLayout*>(QString("bmlistLayout"))->addWidget(l);
        l->show();
    }
}

void Bookmarks::keyPressEvent(QKeyEvent *k){
    QString ktxt = k->text();
    if (ktxt == "") {
        k->ignore();
    } else {
        QChar c = ktxt.at(0);
        int p = c.unicode() - ((k->modifiers() & Qt::ShiftModifier) ? 'A' : 'a');
        if ( p >= 0 && p < pageNumbers.size()) {
            if (k->modifiers() & Qt::ShiftModifier) {
                QDomDocument doc;
                Utils::readDocFromFile(doc,bookmarksFile);
                QDomNode root = doc.firstChild();
                QDomNodeList underRoot = root.childNodes();
                for (int i =0; i < underRoot.size(); i++) {
                    QDomNode nd = underRoot.item(i);
                    if (nd.nodeName() == QString("bookmarks")) {
                        nd.removeChild(nd.childNodes().item(p));
                    }
                }
                Utils::writeDocToFile(doc, bookmarksFile);
            } else {
                emit openPage(pageNumbers[p]);
            }
        }
        accept();
    }
}

void Bookmarks::Exit(){
    accept();
}

Bookmarks::~Bookmarks()
{
    delete ui;
    delete bookmarksFile;
    for (int i = 0; i<labels.size(); i++) { delete labels[i];}

}
