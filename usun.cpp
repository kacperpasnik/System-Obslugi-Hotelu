#include "usun.h"
#include "ui_usun.h"
#include "bazadanych.h"

Usun::Usun(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usun)
{
    ui->setupUi(this);
}

Usun::~Usun()
{
    delete ui;
}



void Usun::on_pushButton_clicked()
{
    QString id,sprawdzanie;
    BazaDanych conn;
    conn.BazaOpen(src);
    id=this->ui->spinBox->text();
    QMessageBox::StandardButton msgBox;
    msgBox= QMessageBox::question(this," ","Czy na pewno chcesz usunąć daną rezerwację?",
                                  QMessageBox::Ok|QMessageBox::Cancel);

    if(msgBox==QMessageBox::Ok)
    {

        QSqlQuery klient("delete from klient where id='"+id+"'");
        QSqlQuery pokoje("select dzien_rezerwacji from pokoje where Id_klient='"+id+"'");
        pokoje.next();
        sprawdzanie=pokoje.value(0).toString();
        if(sprawdzanie==NULL)
            QMessageBox::critical(this," ","Brak rezerwacji o podanym ID!");
        else
        {
            QSqlQuery pokoje2("delete from pokoje where id_klient='"+id+"'");
            if(!pokoje.exec())
                QMessageBox::critical(this,tr("Rezerwacja"),pokoje2.lastError().text());
            else
                QMessageBox::information(this," ","Rezerwacja została usunięta pomyślnie.");
        }
    }



}
