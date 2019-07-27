#include "menuglowne.h"
#include "ui_menuglowne.h"
#include "dodaj.h"
#include "pokaz.h"
#include "sprawdz.h"
#include "usun.h"
#include "zmien.h"
#include "bazadanych.h"


MenuGlowne::MenuGlowne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuGlowne)
{
    ui->setupUi(this);

    BazaDanych r;
    r.show();
    r.exec();
    src=r.sciezka;

    QTimer *t = new QTimer(this);
    t->setInterval(1000);
    QString time1 = QTime::currentTime().toString();
    ui->label_clock->setText(time1);
    connect(t, &QTimer::timeout, [&]() {
       QString time1 = QTime::currentTime().toString();
       ui->label_clock->setText(time1);
    } );

    t->start();

    QTimer *d = new QTimer(this);
    d->setInterval(60000);
    QString date1 = QDate::currentDate().toString();
    ui->label_date->setText(date1);
    connect(d, &QTimer::timeout, [&]() {
       QString date1 = QDate::currentDate().toString();
       ui->label_date->setText(date1);
    } );
    d->start();

    //sql
    if(!r.BazaOpen(src))
        ui->label_baza->setText("Blad polaczenia z baza danych");
    else
        ui->label_baza->setText("Połączono z bazą danych...");

}




MenuGlowne::~MenuGlowne()
{
    delete ui;
}



void MenuGlowne::on_pushButton_zarezerwuj_clicked()
{
    Dodaj r(this);
    r.src=src;
    r.show();
    r.exec();
}



void MenuGlowne::on_pushButton_pokaz_clicked()
{
    Pokaz r(this);
    r.src=src;
    r.show();
    r.exec();
}

void MenuGlowne::on_pushButton_sprawdz_clicked()
{
    Sprawdz r(this);
    r.src=src;
    r.show();
    r.exec();
}

void MenuGlowne::on_pushButton_clicked()
{
    Zmien r(this);
    r.src=src;
    r.show();
    r.exec();
}

void MenuGlowne::on_pushButton_usun_clicked()
{
    Usun r(this);
    r.src=src;
    r.show();
    r.exec();
}
