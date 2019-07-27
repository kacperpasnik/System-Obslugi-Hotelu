#include "sprawdz.h"
#include "ui_sprawdz.h"
#include "zmien.h"
#include "bazadanych.h"

Sprawdz::Sprawdz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sprawdz)
{
    ui->setupUi(this);
    ui->dateEdit_od->setDate(QDate::currentDate());
    ui->dateEdit_do->setDate(QDate::currentDate());
    for(int i=0;i<10;i++)
    {
        ui->comboBox_sprawdz->addItem("Pokój nr " + QString::number(i+1));
    }


}

Sprawdz::~Sprawdz()
{
    delete ui;
}

int Sprawdz::NrIdKlienta(std::vector<QString> wektor,int nr_pokoju)
{
    std::vector<QString> x;
    int wynik=0;
    QSqlQuery qry_odczyt("select dzien_rezerwacji from Pokoje where id_pokoju= '"+QString::number(nr_pokoju)+"' ") ;
    do
    {
         qry_odczyt.next();
         x.push_back(qry_odczyt.value(0).toString());

    }while(x[x.size()-1]!=NULL);
    x.pop_back();
    for(unsigned int i=0;i<wektor.size();i++)
    {
        for(unsigned int j=0;j<x.size();j++)
        {
            if(wektor[i]==x[j])
            {
                QSqlQuery Id_klienta("select Id_klient from Pokoje where dzien_rezerwacji= '"+wektor[i]+"' and id_pokoju= '"+QString::number(nr_pokoju)+"' ");
                Id_klienta.next();
                wynik=Id_klienta.value(0).toInt();
                return wynik;
            }
        }
    }

    return wynik;
}

void Sprawdz::on_pushButton_clicked()
{
    int id_klient=0;
    QString nazwisko;
    BazaDanych conn;
    int nr_pokoju=ui->comboBox_sprawdz->currentIndex()+1;
    QSqlQueryModel* modal=new QSqlQueryModel();
    Dodaj info;
    info.data_od=ui->dateEdit_od->text();
    info.data_do=ui->dateEdit_do->text();
    info.NaInta_NaStringa(info.data_od,info.data_do);
    std::vector<QString> wektor=info.rezerwacje;
    conn.BazaOpen(src);
    QSqlQuery* query = new QSqlQuery(conn.MojDB);
    nr_pokoju=ui->comboBox_sprawdz->currentIndex()+1;
    id_klient=NrIdKlienta(wektor,nr_pokoju-1);
    if(id_klient<=0)
        QMessageBox::information(this,"Rezerwacja","Brak rezerwacji w danym pokoju i w wybranym terminie");
    else
    {


        query->prepare("select id,imie,nazwisko,data_od,data_do,pokoj from Klient where Pokoj='"+QString::number(nr_pokoju)+"' and id='"+QString::number(id_klient)+"'");
    }
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    conn.BazaClose();

}


void Sprawdz::on_pushButton_usun_clicked()
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

void Sprawdz::on_tableView_clicked(const QModelIndex &index)
{
    indeks_tabeli=index;
}

void Sprawdz::on_pushButton_zmien_clicked()
{
    Zmien r(this);
    r.src=src;
    r.show();
    r.exec();
}
