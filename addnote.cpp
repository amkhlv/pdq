#include "addnote.h"
#include "ui_addnote.h"
#include <QColorDialog>

AddNote::AddNote(QWidget *parent, int page, qreal x, qreal y) :
    QDialog(parent),
    page(page),
    x(x),
    y(y),
    r(250),
    g(250),
    b(0),
    ui(new Ui::AddNote)
{
    ui->setupUi(this);
}

void AddNote::save() {
    emit saveNewNote(page, x, y, r, g, b, ui->textEdit->toPlainText());
    accept();
}

void AddNote::chooseColor() {
    QColorDialog* cd = new QColorDialog(this);
    connect(cd, SIGNAL(colorSelected(QColor)), this, SLOT(setColor(QColor)));
    cd->show();
}

void AddNote::setColor(QColor qc) {
    r = qc.red() ; g = qc.green() ; b = qc.blue();
    ui->pushButtonColor->setStyleSheet("color: rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ")");
}

AddNote::~AddNote()
{
    delete ui;
}
