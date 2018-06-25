#include "addnote.h"
#include "ui_addnote.h"

AddNote::AddNote(QWidget *parent, int page, qreal x, qreal y) :
    QDialog(parent),
    page(page),
    x(x),
    y(y),
    ui(new Ui::AddNote)
{
    ui->setupUi(this);
}

void AddNote::save() {
    emit saveNewNote(page, x, y, 250, 250, 0, ui->textEdit->toPlainText());
    accept();
}

AddNote::~AddNote()
{
    delete ui;
}
