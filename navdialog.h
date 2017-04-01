#ifndef NAVDIALOG_H
#define NAVDIALOG_H

#include <QDialog>
#include <pdqmainwindow.h>
#include <QObject>

namespace Ui {
class NavDialog;
}

class NavDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NavDialog(QWidget *parent);
    PdQMainWindow *mainwin;
    ~NavDialog();

public slots:
    void Navigate();

signals:
    void showPage(int n);
    void pushCurrentPage();

private:
    Ui::NavDialog *ui;
};

#endif // NAVDIALOG_H
