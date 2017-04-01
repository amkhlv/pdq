#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <pdqmainwindow.h>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

   public:
       explicit SearchDialog(QWidget *parent, bool rvrs);
       bool reverse;
       ~SearchDialog();

   public slots:
       void DoSearch();

   signals:
       void search(QString term, bool directionIsBackwards);

   private:
       Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
