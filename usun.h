#ifndef USUN_H
#define USUN_H

#include <QDialog>
#include <qmessagebox.h>
#include <QSqlQuery>
#include "menuglowne.h"

namespace Ui {
class Usun;
}

class Usun : public QDialog
{
    Q_OBJECT

public:
    QString src;
    explicit Usun(QWidget *parent = nullptr);
    ~Usun();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Usun *ui;

};

#endif // USUN_H
