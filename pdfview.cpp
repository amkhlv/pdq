﻿#include "pdfview.h"
#include "utils.h"
#include "addnote.h"
#include <QDebug>
#include <poppler-qt5.h>
#include <QEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsScale>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QRect>
#include <QRectF>
#include <QScrollBar>

PDFView::PDFView(QWidget *parent) :
    QGraphicsView(parent),
    hbar(horizontalScrollBar()),
    vbar(verticalScrollBar()),
    notesToEdit(QList<Note>())
{

}
PDFView::~PDFView() {

}

void PDFView::mouseMoveEvent(QMouseEvent *m){
    hbar->setValue(hbar->value() - m->x() + oldCursorPos.x());
    vbar->setValue(vbar->value() - m->y() + oldCursorPos.y());
    oldCursorPos = m->pos();
}

void PDFView::mousePressEvent(QMouseEvent *m){
    oldCursorPos = m->pos();
    Qt::MouseButton btn = m->button();

    int corrX = (this->width() - mainwin->pageSizeX - vbar->width())/2;
    int corrY = (this->height() - mainwin->pageSizeY - hbar->height())/2;
    int cy = oldCursorPos.y() + vbar->value() - ((corrY > 0)? corrY : 0);
    int cx = oldCursorPos.x() + hbar->value() - ((corrX > 0)? corrX : 0);
    if (btn == Qt::LeftButton) {
        QList <Poppler::Link*> links = mainwin->links;
        QList<Note>* notes = mainwin->notes  ;
        for (int j=0; j < notes->length(); j++) {
            qreal xx = notes->at(j).x * static_cast<float>(mainwin->pageSizeX);
            qreal yy = notes->at(j).y * static_cast<float>(mainwin->pageSizeY);
            if ( (qAbs(cx -xx) < 10) && (qAbs(cy - yy) < 10) && (notes->at(j).p == mainwin->currentPageNum) ) {
                QMessageBox* mb = new QMessageBox(mainwin);
                mb->setWindowModality(Qt::NonModal);
                mb->setText(mainwin->notes->at(j).text);
                mb->show();
            }
        }
        for (int j=0; j < links.length(); j++) {
            QRectF larea = links[j]->linkArea();
            int leftX = (mainwin->pageSizeX) * larea.topLeft().x();
            int upY = (mainwin->pageSizeY) * larea.bottomLeft().y();
            int rightX = (mainwin->pageSizeX) * larea.topRight().x();
            int downY = (mainwin->pageSizeY) * larea.topRight().y();
            if ((cx > leftX) && (cx < rightX) && (cy > upY) && (cy < downY)) {
                if (links[j]->linkType() == Poppler::Link::Goto) {
                    //qDebug() << "GOTO" ;
                    const Poppler::LinkGoto *link = static_cast<const Poppler::LinkGoto*>(links[j]);
                    Poppler::LinkDestination dest = link->destination();
                    mainwin->beforeJump.push(mainwin->currentPageNum);
                    mainwin->preparePage(dest.pageNumber() - 1);
                }
                else if (links[j]->linkType() == Poppler::Link::Browse) {
                    const Poppler::LinkBrowse *popplerLinkBrowse = static_cast<const Poppler::LinkBrowse*>(links[j]);
                    //qDebug() << "BROWSE: " + popplerLinkBrowse->url() ;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(
                                this,
                                "Should I follow the link?",
                                popplerLinkBrowse->url(),
                                QMessageBox::Yes|QMessageBox::No
                                );
                    if (reply == QMessageBox::Yes) {
                        QDesktopServices::openUrl(QUrl(popplerLinkBrowse->url()));
                    }
                }
            }
        }
    } else if (btn == Qt::RightButton) {
        bool clicked_on_white = true;
        QList<Note>* notes = mainwin->notes  ;
        int nlength = notes->length();
        for (int j=0; j < nlength; j++) {
            qreal xx = notes->at(j).x * static_cast<float>(mainwin->pageSizeX);
            qreal yy = notes->at(j).y * static_cast<float>(mainwin->pageSizeY);
            if ( (qAbs(cx -xx) < 10) && (qAbs(cy - yy) < 10) && (notes->at(j).p == mainwin->currentPageNum) ) {
                clicked_on_white = false;
                notesToEdit.prepend(notes->at(j));
                QDomDocument doc;
                QFile* pdqFile = new QFile(Utils::bookmarksFileName(mainwin->filename));
                Utils::readDocFromFile(doc, pdqFile);
                QDomNode oldnotes = doc.elementsByTagName("notes").at(0);
                QDomNode root = doc.documentElement();
                QDomElement newnotes = doc.createElement(QString("notes"));
                for (int k=0; k < nlength; k++) {
                    if (k != j) {
                        Note n = notes->at(k);
                        newnotes.appendChild(n.asElementOf(doc));
                    }
                }
                j = nlength;
                root.replaceChild(newnotes,oldnotes);
                Utils::writeDocToFile(doc, pdqFile);
                delete pdqFile;
                mainwin->ReloadFile();
            }
        }
        if (clicked_on_white) {
            bool noteEditingInProcess = !notesToEdit.isEmpty();
            int r = noteEditingInProcess ? notesToEdit.first().r : 250;
            int g = noteEditingInProcess ? notesToEdit.first().g : 250;
            int b = noteEditingInProcess ? notesToEdit.first().b : 0;
            QString txt = noteEditingInProcess ? notesToEdit.first().text : "";
            if (noteEditingInProcess)  notesToEdit.removeFirst();
            AddNote* dialog = new AddNote(
                        this,
                        mainwin->currentPageNum,
                        static_cast<float>(cx)/static_cast<float>(mainwin->pageSizeX),
                        static_cast<float>(cy)/static_cast<float>(mainwin->pageSizeY),
                        r,
                        g,
                        b,
                        txt
                        );
            connect(dialog,
                    SIGNAL(saveNewNote(int, qreal, qreal, int, int, int, QString)),
                    mainwin,
                    SLOT(AddNewNote(int, qreal, qreal, int, int, int, QString))
                    );
            dialog->show();
        }
    }
}

