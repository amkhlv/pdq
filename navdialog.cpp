#include "navdialog.h"
#include "ui_navdialog.h"
#include "pdqmainwindow.h"
#include <QMessageBox>
#include <QDebug>

NavDialog::NavDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NavDialog)
{
    ui->setupUi(this);
}

void NavDialog::Navigate(){
    QString page = ui->lineEdit->text();
    try {
        int p = page.toInt();
        if (p >=1) {
            emit pushCurrentPage();
            emit showPage(p - 1);
        }
    }
    catch(int e) {
        QMessageBox mb;
        mb.setText("not a valid page number");
        mb.exec();
    }
    accept();
}

NavDialog::~NavDialog()
{
    delete ui;
}

