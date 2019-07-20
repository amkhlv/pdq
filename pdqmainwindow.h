#ifndef PDQMAINWINDOW_H
#define PDQMAINWINDOW_H

#include <QMainWindow>
#include <poppler-qt5.h>
#include <QLabel>
#include <QScrollBar>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSize>
#include <QStack>
#include <searchstate.h>
#include <QFile>
#include <QClipboard>
#include "note.h"
#include "config.h"

namespace Ui {
class PdQMainWindow;
}

class PdQMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PdQMainWindow(QWidget *parent = 0, Config *conf = new Config());
    ~PdQMainWindow();
    Poppler::Document* document;
    int numPages;
    void loadFile();
    void preparePage(int pagenumber);
    QString filename;
    QGraphicsScene *pageScene;
    quint16 currentPageNum;
    Poppler::Page* currentPage;
    QScrollBar* hbar;
    QScrollBar* vbar;
    QList <Poppler::Link*> links;
    qint32 pageSizeX;
    qint32 pageSizeY;
    QStack <int> beforeJump;
    QLabel *pageNumLabel;
    QLabel *totalPagesLabel;
    QLabel *resolutionLabel;
    QList<Note> *notes;
    Config *conf;



public slots:
    void ReloadFile();
    void PrevPage();
    void NextPage();
    void ZoomIn();
    void ZoomOut();
    void GoBack();
    void StartSearching();
    void StartSearchingInReverse();
    void StopSearching();
    void Search(QString term, bool directionIsBackwards);
    void GotIt();
    void OpenBookmarks();
    void GoToBookmark(int n);
    void AddNewBookmark();
    void Navigate();
    void ShowPage(int pagenumber);
    void PushCurrentPage();
    void ShowTextExtract();
    void AddNewNote(int p, qreal x, qreal y, int r, int g, int b, QString txt);
    void CopyPathToPDF();

private:
    Ui::PdQMainWindow *ui;
    void keyPressEvent(QKeyEvent *k);
    void pushCurrentPage();
    bool search(int pagenumber);
    void searchForward();
    void searchBack();
    SearchState searchState;
};

#endif // PDQMAINWINDOW_H
