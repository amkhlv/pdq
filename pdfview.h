#ifndef PDFVIEW_H
#define PDFVIEW_H

#include <QGraphicsView>
#include <poppler-qt5.h>
#include <pdqmainwindow.h>
#include "note.h"


class PDFView : public QGraphicsView
{
public:
    explicit PDFView(QWidget *parent = 0);
    ~PDFView();
    PdQMainWindow* mainwin;
    QScrollBar* hbar;
    QScrollBar* vbar;
    QPoint oldCursorPos;

private:
    void mouseMoveEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent *m);
    QList<Note> notesToEdit;


};

#endif // PDFVIEW_H
