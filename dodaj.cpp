#include "dodaj.h"
#include "ui_dodaj.h"
#include "bazadanych.h"

Dodaj::Dodaj(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dodaj)
{
    ui->setupUi(this);
    ui->dateEdit_od->setDate(QDate::currentDate());
    ui->dateEdit_do->setDate(QDate::currentDate());
    for(int i=0;i<10;i++)
    {
        ui->comboBox_pokoje->addItem("Pokój nr " + QString::number(i+1));
    }


}



Dodaj::~Dodaj()
{

    delete ui;

}

void Dodaj::closeEvent(QCloseEvent *e){
    accept();
}

void Dodaj::NaInta_NaStringa(QString from, QString to)
{
    QDateTime od_kiedy=QDateTime::fromString(from, "dd.MM.yyyy");
    QDateTime do_kiedy=QDateTime::fromString(to, "dd.MM.yyyy");
    int liczba_dni=od_kiedy.daysTo(do_kiedy);
    int zarezerwowane_dni=0;
    zarezerwowane_dni=zerowa_data.daysTo(od_kiedy);
    for(int i=0;i<=liczba_dni;i++)
         rezerwacje.push_back(QString::number(zarezerwowane_dni+i));

}

bool Dodaj::sprawdz_rezerwacje(int nr_pokoju)
{
    std::vector<QString> x;
    QSqlQuery qry_odczyt("select dzien_rezerwacji from Pokoje where id_pokoju= '"+QString::number(nr_pokoju)+"' ") ;
    do
    {
         qry_odczyt.next();
         x.push_back(qry_odczyt.value(0).toString());

    }while(x[x.size()-1]!=NULL);
    x.pop_back();
    for(unsigned int i=0;i<rezerwacje.size();i++)
    {
        for(unsigned int j=0;j<x.size();j++)
        {
            if(rezerwacje[i]==x[j])
                return false;
        }
    }


   /* QSqlQuery qry_odczyt ;                                                         //też działa
    qry_odczyt.prepare("select dzien_rezerwacji from Pokoje where id_pokoju=?");
    qry_odczyt.addBindValue(nr_pokoju);
    qry_odczyt.exec();
    qry_odczyt.next();
    x.push_back(qry_odczyt.value(0).toString());
    odczyt=qry_odczyt.value(0).toString(); */                                      //też działa

    return true;
}

bool Dodaj::sprawdz_rezerwacje(int nr_pokoju,QString id)
{
    std::vector<QString> x;
    QSqlQuery zapasowe;
    QSqlQuery qry_odczyt("select dzien_rezerwacji from Pokoje where id_pokoju= '"+QString::number(nr_pokoju)+"' ") ;
    do
    {
         qry_odczyt.next();
         x.push_back(qry_odczyt.value(0).toString());

    }while(x[x.size()-1]!=NULL);
    x.pop_back();
    for(unsigned int i=0;i<rezerwacje.size();i++)
    {
        for(unsigned int j=0;j<x.size();j++)
        {
            if(rezerwacje[i]==x[j])
            {
                zapasowe.prepare("select Id_klient from Pokoje where dzien_rezerwacji='"+rezerwacje[i]+"'");
                zapasowe.exec();
                zapasowe.next();
                if(id!=zapasowe.value(0).toString())
                    return false;
            }
        }
    }

    return true;
}

void Dodaj::on_pushButton_anuluj_clicked()
{
    accept();
}

void Dodaj::on_pushButton_dodaj_clicked()
{

    BazaDanych conn;
    imie=ui->lineEdit_imie->text();
    nazwisko=ui->lineEdit_nazwisko->text();
    data_od=ui->dateEdit_od->text();
    data_do=ui->dateEdit_do->text();
    int nr_pokoju=ui->comboBox_pokoje->currentIndex();
    if(imie!=NULL && nazwisko!=NULL )
    {

      if(!conn.BazaOpen(src))
      {
          qDebug()<<"Błąd połączenia z bazą danych";
          accept();
          return;
      }

      NaInta_NaStringa(data_od,data_do);
      if(rezerwacje.size()>0)
      {
         QString zastepczy_string;
         conn.BazaOpen(src);
         QSqlQuery qry2;
         nr_pokoju=ui->comboBox_pokoje->currentIndex();

         if(sprawdz_rezerwacje(nr_pokoju))
         {
             bool poprawnie_dodane=false;
             QSqlQuery qry;
             qry.prepare("insert into Klient (imie, nazwisko, data_od, data_do, Pokoj) values(?,?,?,?,?)");
             qry.addBindValue(imie);
             qry.addBindValue(nazwisko);
             qry.addBindValue(data_od);
             qry.addBindValue(data_do);
             qry.addBindValue(nr_pokoju+1);
             if(!qry.exec())
                 QMessageBox::critical(this,tr("Rezerwacja"),qry.lastError().text());
             else
                 poprawnie_dodane=true;

            for(unsigned int i=0;i<rezerwacje.size();i++)
            {
                    qry2.prepare("insert into Pokoje (id_pokoju, dzien_rezerwacji, Id_klient) values('"+QString::number(nr_pokoju) +"','"+rezerwacje[i]+"',(select id from Klient where nazwisko='"+nazwisko+"'))");
                   // qry2.addBindValue(nr_pokoju);
                   // qry2.addBindValue(rezerwacje[i]);
                    if(!qry2.exec())
                    {
                        QMessageBox::critical(this,tr("Rezerwacja"),qry2.lastError().text());
                        poprawnie_dodane=false;
                    }
            }



            if(poprawnie_dodane)
           {
                  QMessageBox::information(this,"Rezerwacja","Rezerwacja została dodana pomyślnie.");
                  conn.BazaClose();
                  rezerwacje.clear();
                  accept();
            }
            else
            {
                  QMessageBox::critical(this,"Rezerwacja","Wystąpił błąd w dodawaniu rezerwacji.");
                  rezerwacje.clear();
            }
         }
         else
         {
             QMessageBox::warning(this,"Rezerwacja","Podana data jest już zarezerwowana!");
             rezerwacje.clear();
         }
      }
      else
      {
          QMessageBox::warning(this,"Rezerwacja","Podana data jest nieprawidłowa!");
          rezerwacje.clear();
      }
    }
    else
    {
        QMessageBox::warning(this,"Rezerwacja","Podane dane są puste!");
        rezerwacje.clear();
    }

}




