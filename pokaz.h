#ifndef POKAZ_H
#define POKAZ_H

#include <QDialog>
#include "menuglowne.h"

namespace Ui {
class Pokaz;
}

class Pokaz : public QDialog
{
    Q_OBJECT

public:
    QString src;
    explicit Pokaz(QWidget *parent = nullptr);
    ~Pokaz();

private slots:
    void on_pushButton_pokaz_clicked();



    void on_pushButton_zmien_clicked();

    void on_pushButton_usun_clicked();

    void on_tableView_clicked(const QModelIndex &index);


private:
    Ui::Pokaz *ui;
    QModelIndex indeks_tabeli;

};

#endif // POKAZ_H
