#ifndef TEXTEXTRACT_H
#define TEXTEXTRACT_H

#include <QDialog>

namespace Ui {
class TextExtract;
}

class TextExtract : public QDialog
{
    Q_OBJECT

public:
    explicit TextExtract(QWidget *parent = 0, QString text = "");
    ~TextExtract();

private:
    Ui::TextExtract *ui;
};

#endif // TEXTEXTRACT_H
