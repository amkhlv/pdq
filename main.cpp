#include "pdqmainwindow.h"
#include "utils.h"
#include <QApplication>
#include <poppler-qt5.h>
#include <QDebug>
#include <unistd.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Config* conf = new Config();
    PdQMainWindow* w = new PdQMainWindow(0, conf);
    int startpage = 0;
    int opt;
    while ((opt = getopt(argc,argv,"p:")) != EOF)
        switch(opt)
        {
        case 'p': startpage = QString(optarg).toInt();
        }
    QString f = argv[optind];
    w->filename = f;
    w->loadFile();
    QDomDocument dconf;
    w->setWindowTitle(f);
    w->preparePage(startpage);

    w->show();

    return a.exec();
}
