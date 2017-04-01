#include "pdqmainwindow.h"
#include <QApplication>
#include <poppler-qt5.h>
#include <QDebug>
#include <unistd.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PdQMainWindow w;
    int startpage = 0;
    int opt;
    while ((opt = getopt(argc,argv,"p:")) != EOF)
        switch(opt)
        {
        case 'p': startpage = QString(optarg).toInt();
        }
    QString f = argv[optind];
    w.loadFile(f);
    w.dpi = 100;
    w.setWindowTitle(f);
    w.preparePage(startpage);

    w.show();

    return a.exec();
}
