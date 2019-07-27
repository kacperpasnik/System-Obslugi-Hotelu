#ifndef ZMIEN_H
#define ZMIEN_H

#include <QDialog>
#include <qmessagebox.h>
#include <QSqlQuery>
#include "menuglowne.h"
#include "dodaj.h"


namespace Ui {
class Zmien;
}

class Zmien : public QDialog
{
    Q_OBJECT

public:
    QString src;
    explicit Zmien(QWidget *parent = nullptr);
    ~Zmien();

private slots:




    void on_comboBox_zmien_currentIndexChanged(int index);

    void on_pushButton_zmien_clicked();

private:
    Ui::Zmien *ui;
    Dodaj funkcje;

};

#endif // ZMIEN_H
