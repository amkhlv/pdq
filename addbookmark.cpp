#include "addbookmark.h"
#include "ui_addbookmark.h"
#include <QtXml>
#include <QFileInfo>
#include "utils.h"

AddBookmark::AddBookmark(QWidget *parent, QString filename, quint16 page):
    QDialog(parent),
    bookmarksFile(new QFile(filename)),
    page(page),
    ui(new Ui::AddBookmark)
{
    ui->setupUi(this);
    Utils::checkBookmarksFile(bookmarksFile);
}

AddBookmark::~AddBookmark()
{
    delete ui;
}

void AddBookmark::AddNewBookmark() {
    QString description = ui->lineEdit->text();
    QDomDocument doc;
    Utils::readDocFromFile(doc, bookmarksFile);
    QDomElement newbm = doc.createElement("bookmark");
    newbm.setAttribute("page", QString::number(page));
    newbm.appendChild(doc.createTextNode(description));
    QDomNode root = doc.firstChild();
    QDomNodeList underRoot = root.childNodes();
    for (int i =0; i < underRoot.size(); i++) {
        QDomNode nd = underRoot.item(i);
        if (nd.nodeName() == QString("bookmarks")) {
            nd.appendChild(newbm);
        }
    }
    Utils::writeDocToFile(doc, bookmarksFile);
    accept();
}


