#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "pdqmainwindow.h"
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent, bool rvrs) :
    QDialog(parent),
    reverse(rvrs),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::DoSearch()
{
    QString term = ui->lineEdit->text();
    emit search(term, reverse);
    accept();
}
