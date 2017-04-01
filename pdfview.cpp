#include "pdfview.h"
#include <QDebug>
#include <poppler-qt5.h>
#include <QEvent>
#include <QMouseEvent>
#include <QScrollBar>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

PDFView::PDFView(QWidget *parent) :
    QGraphicsView(parent),
    hbar(horizontalScrollBar()),
    vbar(verticalScrollBar())
{

}

void PDFView::mouseMoveEvent(QMouseEvent *m){
    hbar->setValue(hbar->value() - m->x() + oldCursorPos.x());
    vbar->setValue(vbar->value() - m->y() + oldCursorPos.y());
    oldCursorPos = m->pos();
}

void PDFView::mousePressEvent(QMouseEvent *m){
    oldCursorPos = m->pos();
    int corrX = (this->width() - mainwin->pageSizeX - vbar->width())/2;
    int corrY = (this->height() - mainwin->pageSizeY - hbar->height())/2;
    int cy = oldCursorPos.y() + vbar->value() - ((corrY > 0)? corrY : 0);
    int cx = oldCursorPos.x() + hbar->value() - ((corrX > 0)? corrX : 0);
    QList <Poppler::Link*> links = mainwin->links;
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
                  reply = QMessageBox::question(this, "Test", popplerLinkBrowse->url(),
                                                QMessageBox::Yes|QMessageBox::No);
                  if (reply == QMessageBox::Yes) {
                    QDesktopServices::openUrl(QUrl(popplerLinkBrowse->url()));
                  }
            }

        }
    }
}

