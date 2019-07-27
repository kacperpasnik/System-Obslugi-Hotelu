#ifndef SPRAWDZ_H
#define SPRAWDZ_H

#include <QDialog>
#include "menuglowne.h"
#include "dodaj.h"

namespace Ui {
class Sprawdz;
}

class Sprawdz : public QDialog
{
    Q_OBJECT

public:
    QString src;
    explicit Sprawdz(QWidget *parent = nullptr);
    ~Sprawdz();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_usun_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_zmien_clicked();

private:
    Ui::Sprawdz *ui;
    int NrIdKlienta(std::vector<QString>,int);
    QModelIndex indeks_tabeli;

};

#endif // SPRAWDZ_H
