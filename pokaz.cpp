#include "pokaz.h"
#include "ui_pokaz.h"
#include "zmien.h"
#include "usun.h"
#include "bazadanych.h"

Pokaz::Pokaz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pokaz)
{
    ui->setupUi(this);
    for(int i=0;i<10;i++)
    {
        ui->comboBox_pokaz->addItem("Pokój nr " + QString::number(i+1));
    }
}

Pokaz::~Pokaz()
{
    delete ui;
}

void Pokaz::on_pushButton_pokaz_clicked()
{
    QString nazwisko;
    BazaDanych conn;
    int nr_pokoju=ui->comboBox_pokaz->currentIndex()+1;
    QSqlQueryModel* modal=new QSqlQueryModel();
    conn.BazaOpen(src);
    QSqlQuery* query = new QSqlQuery(conn.MojDB);
    nr_pokoju=ui->comboBox_pokaz->currentIndex()+1;
    if(ui->checkBox_pokaz->isChecked()==true)
    {
        nazwisko=ui->lineEdit_pokaz->text();
        query->prepare("select id,imie,nazwisko,data_od,data_do,pokoj from Klient where Pokoj='"+QString::number(nr_pokoju)+"' and nazwisko='"+nazwisko+"'");
    }
    else
        query->prepare("select id,imie,nazwisko,data_od,data_do,pokoj from Klient where Pokoj='"+QString::number(nr_pokoju)+"'");
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);

    qDebug()<<(modal->rowCount());
    conn.BazaClose();
}



void Pokaz::on_pushButton_zmien_clicked()
{
    Zmien r(this);
    r.src=src;
    r.show();
    r.exec();
}



void Pokaz::on_pushButton_usun_clicked()
{
    QMessageBox::StandardButton msgBox;
    msgBox= QMessageBox::question(this," ","Czy na pewno chcesz usunąć daną rezerwację?",
                                  QMessageBox::Ok|QMessageBox::Cancel);

    if(msgBox==QMessageBox::Ok)
    {
        BazaDanych conn;
        conn.BazaOpen(src);
        QString x;
        x=ui->tableView->model()->data(indeks_tabeli).toString();
        QSqlQuery qry;
        qry.prepare("delete from klient where id='"+x+"'");
        if(!qry.exec())
            QMessageBox::critical(this,tr("Rezerwacja"),qry.lastError().text());
        else
        {
            qry.prepare("delete from pokoje where Id_klient='"+x+"'");
            if(!qry.exec())
                QMessageBox::critical(this,tr("Rezerwacja"),qry.lastError().text());
            else
                QMessageBox::information(this," ","Rezerwacja została usunięta pomyślnie.");
        }
        conn.BazaClose();
    }

}

void Pokaz::on_tableView_clicked(const QModelIndex &index)
{
    indeks_tabeli=index;
}


