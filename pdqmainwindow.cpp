#include <QDebug>
#include "pdqmainwindow.h"
#include "ui_pdqmainwindow.h"
#include "searchstate.h"
#include "searchdialog.h"
#include "bookmarks.h"
#include "addbookmark.h"
#include "navdialog.h"
#include "textextract.h"
#include "utils.h"
#include <poppler-qt5.h>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsScale>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QRect>
#include <QRectF>
#include <QScrollBar>
#include <QKeyEvent>
#include <QClipboard>

PdQMainWindow::PdQMainWindow(QWidget *parent) :
    QMainWindow(parent),
    pageScene(new QGraphicsScene(this)),
    beforeJump(QStack<int>()),
    pageNumLabel(new QLabel(this)),
    totalPagesLabel(new QLabel(this)),
    resolutionLabel(new QLabel(this)),
    ui(new Ui::PdQMainWindow),
    searchState(SearchState()),
    notes(new QList<Note>())
{
    ui->setupUi(this);
    pageNumLabel->setAlignment(Qt::AlignCenter);
    QFont pageLabelFont("Sans Serif", 10, QFont::Bold);
    pageNumLabel->setFont(pageLabelFont);
    pageNumLabel->setStyleSheet("QLabel { background-color : white; }");
    QFont resolutionLabelFont("Sans Serif", 8);
    ui->toolBar->addWidget(pageNumLabel);
    totalPagesLabel->setAlignment(Qt::AlignCenter);
    totalPagesLabel->setFont(pageLabelFont);
    ui->toolBar->addWidget(totalPagesLabel);
    ui->toolBar->addSeparator();
    resolutionLabel->setAlignment(Qt::AlignCenter);
    resolutionLabel->setFont(resolutionLabelFont);
    ui->toolBar->addWidget(resolutionLabel);
}

PdQMainWindow::~PdQMainWindow()
{
    delete ui;
    delete pageScene;
    delete pageNumLabel;
    delete totalPagesLabel;
    delete resolutionLabel;
    delete pdqFile;
    delete notes;
}

void PdQMainWindow::loadFile()
{
    document = Poppler::Document::load(filename);
    document->setRenderHint(Poppler::Document::Antialiasing , true);
    document->setRenderHint(Poppler::Document::TextAntialiasing, true);
    numPages = document->numPages();
    QDomDocument d;
    pdqFile = new QFile(Utils::bookmarksFileName(filename));
    Utils::checkBookmarksFile(pdqFile);
    Utils::readDocFromFile(d, pdqFile);
    delete notes;
    notes = Utils::getNotesFromDoc(d);
    QDomDocument dconf;
    Utils::readConfigFromFile(dconf);
    willInvert = Utils::shouldInvert(dconf);
}

void PdQMainWindow::preparePage(int pagenum)
{
    totalPagesLabel->setText(QString::number(numPages));
    resolutionLabel->setText(QString::number(dpi));
    pageNumLabel->setText(QString::number(pagenum + 1)+"/");
    Poppler::Page* pdfPage = document->page(pagenum);
    currentPage = pdfPage;
    currentPageNum = pagenum;
    QSize sz = pdfPage->pageSize();
    pageSizeX = (sz.width()*dpi)/72;
    pageSizeY = (sz.height()*dpi)/72;
    QImage image = pdfPage->renderToImage(dpi,dpi,0,0,pageSizeX,pageSizeY);
    if (willInvert) {
        pageScene->setBackgroundBrush(Qt::black);
        //image.invertPixels();
        image.invertPixels(QImage::InvertRgba);
    }
    QPixmap ipix = QPixmap::fromImage(image);
    QGraphicsPixmapItem *pageItem = pageScene->addPixmap(ipix);
    ui->graphicsView->setScene(pageScene);
    ui->graphicsView->mainwin = this;
    pageItem->show();
    hbar = ui->graphicsView->horizontalScrollBar();
    vbar = ui->graphicsView->verticalScrollBar();
    links = pdfPage->links();
    for (int n=0; n < notes->size() ; n++) {
        if (notes->at(n).p == currentPageNum) {
            qDebug() << notes->at(n).x ;
            qDebug() << notes->at(n).y ;
            int x = static_cast<int>((static_cast<float>(pageSizeX)) * notes->at(n).x) ;
            int y = static_cast<int>((static_cast<float>(pageSizeY)) * notes->at(n).y) ;
            qDebug() << x ;
            qDebug() << y ;
            QRectF loc = QRectF(x - 8, y - 8, 16, 16);
            QGraphicsEllipseItem *ellipse = pageScene->addEllipse(
                        loc,
                        QPen(),
                        QBrush(QColor(notes->at(n).r, notes->at(n).g, notes->at(n).b, 255))
                        );
            ellipse->show();
        }
    }

}
void PdQMainWindow::keyPressEvent(QKeyEvent *k){
    qint8 s = (k->modifiers() & Qt::ShiftModifier) ? 10 : 3;
    if (k->key() == Qt::Key_J) {
        vbar->setValue(vbar->value() + s);
    }
    else if (k->key() == Qt::Key_K) {
        vbar->setValue(vbar->value() - s);
    }
    else if (k->key() == Qt::Key_H) {
        hbar->setValue(hbar->value() - s);
    }
    else if (k->key() == Qt::Key_L) {
        hbar->setValue(hbar->value() + s);
    }
}
void PdQMainWindow::ReloadFile()
{
    loadFile();
    if (currentPageNum < numPages)
        preparePage(currentPageNum);
    else
        preparePage(numPages - 1);
}
void PdQMainWindow::PrevPage(){
    if (currentPageNum > 0) preparePage(currentPageNum - 1);
}
void PdQMainWindow::NextPage(){
    if ((currentPageNum + 1) < numPages) preparePage(currentPageNum + 1);
}
void PdQMainWindow::ZoomIn(){
    int v = vbar->value();
    int h = hbar->value();
    delete pageScene;
    pageScene = new QGraphicsScene(this);
    dpi = dpi + 4;
    preparePage(currentPageNum);
    hbar->setValue(dpi * h / (dpi - 4));
    vbar->setValue(dpi * v / (dpi - 4));
}
void PdQMainWindow::ZoomOut(){
    int v = vbar->value();
    int h = hbar->value();
    delete pageScene;
    pageScene = new QGraphicsScene(this);
    if (dpi > 4) dpi = dpi - 4;
    preparePage(currentPageNum);
    hbar->setValue(dpi * h / (dpi + 4));
    vbar->setValue(dpi * v / (dpi + 4));
}
void PdQMainWindow::GoBack(){
    if (!beforeJump.isEmpty()) {
        preparePage(beforeJump.pop());
    }
}



void PdQMainWindow::pushCurrentPage(){
    beforeJump.push(currentPageNum);
}


bool PdQMainWindow::search(int pagenumber)
{
    qreal r = dpi / 72.0;
    Poppler::Page* pdfPage = document->page(pagenumber);
    QList<QRectF> locations = pdfPage->search(searchState.searchTerm, Poppler::Page::IgnoreCase);
    int s = locations.size();
    if (searchState.justReversed) {
        //qDebug() << "-- reversed --";
        searchState.searchResultsShown = s + 1 - searchState.searchResultsShown;
    }
    int n = ((searchState.isOnReverse) ? (s - 1 - searchState.searchResultsShown) : searchState.searchResultsShown) ;
    if ((n >= 0) && (n < s)) {
        preparePage(pagenumber);
        QRectF loc = QRectF(r * (locations[n].x()), r * (locations[n].y()), r * (locations[n].width()), r * (locations[n].height()));
        QGraphicsEllipseItem *ellipse = pageScene->addEllipse(loc, QPen(), QBrush(QColor(255, 255, 0, 64)));
        ellipse->show();
        searchState.searchResultsShown++;
        return true;
    }
    else {
        searchState.searchResultsShown = 0;
        return false;
    }
}
void PdQMainWindow::searchForward()
{
    int pageNow = currentPageNum;
    searchState.searching = true;
    searchState.justReversed = searchState.isOnReverse;
    searchState.isOnReverse = false;
    int n = 0;
    while (n < numPages) {
       if (search((pageNow + n) % numPages)) { break ; }
       searchState.justReversed = false;
       n++ ;
    }
    if (n == numPages) { searchState.searching = false ; }
}
void PdQMainWindow::searchBack()
{
    int pageNow = currentPageNum;
    searchState.searching = true;
    searchState.justReversed = !searchState.isOnReverse;
    searchState.isOnReverse = true;
    int n = 0;
    while (n < numPages) {
        int m = pageNow - n;
        if (search(( m >= 0 )? m : (numPages + m))) { break ; }
        searchState.justReversed = false;
        n++ ;
    }
    if (n == numPages) { searchState.searching = false ; }
}

void PdQMainWindow::Search(QString term, bool directionIsBackwards){
    searchState.searchTerm = term;
    searchState.searchStartPage = currentPageNum;
    searchState.searchResultsShown = 0;
    searchState.isOnReverse = directionIsBackwards;
    searchState.justReversed = false;
    if (directionIsBackwards)  { searchBack(); } else { searchForward(); }
}

void PdQMainWindow::StartSearching(){
    if (searchState.searching) {
        searchForward();
    } else {
        //qDebug() << "Starting Searching";
        SearchDialog* dialog = new SearchDialog(this, false);
        connect(dialog, SIGNAL(search(QString,bool)), this, SLOT(Search(QString,bool)));
        dialog->show();
    }
}
void PdQMainWindow::StartSearchingInReverse(){
    if (searchState.searching) {
        searchBack();
    } else {
        //qDebug() << "Start Searching in reverse";
        SearchDialog* dialog = new SearchDialog(this, true);
        connect(dialog, SIGNAL(search(QString,bool)), this, SLOT(Search(QString,bool)));
        dialog->show();
    }
}
void PdQMainWindow::StopSearching(){
    if (searchState.searching) {
    searchState.searching = false;
    preparePage(searchState.searchStartPage);
    }
}
void PdQMainWindow::GotIt(){
    searchState.searching = false;
    beforeJump.push(searchState.searchStartPage);
    preparePage(currentPageNum);
}


void PdQMainWindow::OpenBookmarks(){
    Bookmarks* bm = new Bookmarks(this, Utils::bookmarksFileName(filename));
    QObject::connect(bm, SIGNAL(openPage(int)), this, SLOT(GoToBookmark(int)));
    bm->show();
}

void PdQMainWindow::GoToBookmark(int n){
    beforeJump.push(currentPageNum);
    if (n < numPages)  preparePage(n);
}

void PdQMainWindow::AddNewBookmark(){
    AddBookmark* abm = new AddBookmark(this, Utils::bookmarksFileName(filename), currentPageNum);
    abm->show();
}

void PdQMainWindow::Navigate(){
    NavDialog* dialog = new NavDialog(this);
    connect(dialog, SIGNAL(showPage(int)), this, SLOT(ShowPage(int)));
    connect(dialog, SIGNAL(pushCurrentPage()), this, SLOT(PushCurrentPage()));
    dialog->show();
}

void PdQMainWindow::PushCurrentPage(){
    beforeJump.push(currentPageNum);
}

void PdQMainWindow::ShowPage(int pagenumber){
    if (pagenumber < numPages) {
        preparePage(pagenumber);
    }
}

void PdQMainWindow::ShowTextExtract(){
    TextExtract* txtxtr = new TextExtract(this, currentPage->text(QRectF()));
    txtxtr->show();
}

void PdQMainWindow::AddNewNote(int p, qreal x, qreal y, int r, int g, int b, QString txt) {
    QDomDocument doc;
    Utils::readDocFromFile(doc, pdqFile);
    QDomElement newnote = doc.createElement("note");
    newnote.setAttribute("page", QString::number(p));
    newnote.setAttribute("x", QString::number(x));
    newnote.setAttribute("y", QString::number(y));
    newnote.setAttribute("r", QString::number(r));
    newnote.setAttribute("g", QString::number(g));
    newnote.setAttribute("b", QString::number(b));
    newnote.appendChild(doc.createTextNode(txt));
    QDomNode root = doc.firstChild();
    QDomNodeList underRoot = root.childNodes();
    if (doc.elementsByTagName("notes").length() == 0) root.appendChild(doc.createElement("notes"));

    for (int i =0; i < underRoot.size(); i++) {
        QDomNode nd = underRoot.item(i);
        if (nd.nodeName() == QString("notes")) {
            nd.appendChild(newnote);
        }
    }
    Utils::writeDocToFile(doc, pdqFile);
    ReloadFile();
}

void PdQMainWindow::CopyPathToPDF() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(filename);

}


