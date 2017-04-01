#ifndef ADDBOOKMARK_H
#define ADDBOOKMARK_H

#include <QObject>
#include <QDialog>
#include <QFile>

namespace Ui {
class AddBookmark;
}

class AddBookmark : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookmark(QWidget *parent, QString filename, quint16 page);
    ~AddBookmark();
    QFile* bookmarksFile;
    quint16 page;

public slots:
    void AddNewBookmark();

private:
    Ui::AddBookmark *ui;
};

#endif // ADDBOOKMARK_H
