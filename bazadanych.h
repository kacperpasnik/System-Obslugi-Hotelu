#ifndef BAZADANYCH_H
#define BAZADANYCH_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>

namespace Ui {
class BazaDanych;
}

class BazaDanych : public QDialog
{
    Q_OBJECT

public:
    QString sciezka;
    QSqlDatabase MojDB;
    bool BazaOpen(QString);
    void BazaClose();
    explicit BazaDanych(QWidget *parent = nullptr);
    ~BazaDanych();

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_anuluj_clicked();

private:
    Ui::BazaDanych *ui;
};

#endif // BAZADANYCH_H
