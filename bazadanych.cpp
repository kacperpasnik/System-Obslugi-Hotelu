#include "bazadanych.h"
#include "ui_bazadanych.h"

BazaDanych::BazaDanych(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BazaDanych)
{
    ui->setupUi(this);
}

BazaDanych::~BazaDanych()
{
    BazaClose();
    delete ui;
}

void BazaDanych::on_pushButton_OK_clicked()
{
    sciezka=ui->lineEdit_sciezka->text();
    if(sciezka.isEmpty())
        QMessageBox::critical(this,"Baza danych","Pole nie moze byc puste");
    else
        accept();
}



void BazaDanych::on_pushButton_anuluj_clicked()
{
    reject();
}

bool BazaDanych::BazaOpen(QString src)
{
    MojDB= QSqlDatabase::addDatabase("QSQLITE");
    MojDB.setDatabaseName(src);
    MojDB.open();
    QFileInfo check_file(src);
    if(check_file.exists() && check_file.isFile())
    {
        qDebug()<<("Połączono z bazą danych...");

        return true;
    }
    else
    {
        qDebug()<<("Blad polaczenia z baza danych");

        return false;
    }
}

void BazaDanych::BazaClose()
{
    MojDB.close();
    MojDB.removeDatabase(QSqlDatabase::defaultConnection);
}
