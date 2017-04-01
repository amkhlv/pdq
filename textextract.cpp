#include "textextract.h"
#include "ui_textextract.h"

TextExtract::TextExtract(QWidget *parent, QString text) :
    QDialog(parent),
    ui(new Ui::TextExtract)
{
    ui->setupUi(this);
    ui->textBrowser->setText(text);
}

TextExtract::~TextExtract()
{
    delete ui;
}
