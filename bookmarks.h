#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include <QObject>
#include <QDialog>
#include <QFile>
#include <QLabel>

namespace Ui {
class Bookmarks;
}

class Bookmarks : public QDialog
{
    Q_OBJECT

public:
    explicit Bookmarks(QWidget *parent, QString filename);
    ~Bookmarks();
    QFile* bookmarksFile;
    QList<QLabel*> labels;
    QList<qint16> pageNumbers;

private:
    Ui::Bookmarks *ui;
    void keyPressEvent(QKeyEvent *k);

public slots:
    void Exit();

signals:
    void openPage(int n);

};

#endif // BOOKMARKS_H
