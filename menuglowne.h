    #ifndef MENUGLOWNE_H
#define MENUGLOWNE_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <fstream>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "bazadanych.h"


namespace Ui {
class MenuGlowne;
}

class MenuGlowne : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuGlowne(QWidget *parent = nullptr);
    int g=0;

    ~MenuGlowne();

private slots:

    void on_pushButton_zarezerwuj_clicked();

    void on_pushButton_pokaz_clicked();

    void on_pushButton_sprawdz_clicked();

    void on_pushButton_clicked();

    void on_pushButton_usun_clicked();

private:
    BazaDanych r;
    Ui::MenuGlowne *ui;
    QString src;

};

#endif // MENUGLOWNE_H
