#include "zmien.h"
#include "ui_zmien.h"
#include "bazadanych.h"

Zmien::Zmien(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zmien)
{
    ui->setupUi(this);
    ui->comboBox_zmien->addItem("Imię");
    ui->comboBox_zmien->addItem("Nazwisko");
    ui->comboBox_zmien->addItem("Datę");
    ui->comboBox_zmien->addItem("Pokój");
    ui->dateEdit_od->setDate(QDate::currentDate());
    ui->dateEdit_do->setDate(QDate::currentDate());
    ui->groupBox_2->hide();
}

Zmien::~Zmien()
{

    delete ui;
}


void Zmien::on_comboBox_zmien_currentIndexChanged(int index)
{
    if(index==2)
    {
        ui->groupBox_2->show();
        ui->lineEdit_zmien->setEnabled(false);
    }
    else if(index==0 ||index==1 || index==3)
    {
         ui->groupBox_2->hide();
         ui->lineEdit_zmien->setEnabled(true);
    }
}








void Zmien::on_pushButton_zmien_clicked()
{
    QString id,sprawdzanie_string,wprowadzenie;
    QString data_od,data_do;
    int nr_pokoju=-1;
    BazaDanych conn;
    conn.BazaOpen(src);
    id=this->ui->spinBox_zmien->text();
    QSqlQuery sprawdzenie_query;
    sprawdzenie_query.prepare("select dzien_rezerwacji from pokoje where Id_klient='"+id+"'");
    sprawdzenie_query.exec();
    sprawdzenie_query.next();
    sprawdzanie_string=sprawdzenie_query.value(0).toString();
    sprawdzenie_query.prepare("select Pokoj from klient where id='"+id+"'");
    sprawdzenie_query.exec();
    sprawdzenie_query.next();
    nr_pokoju=sprawdzenie_query.value(0).toInt();
    if(sprawdzanie_string!=NULL)
    {

        QMessageBox::StandardButton msgBox;

        msgBox= QMessageBox::question(this," ","Czy na pewno chcesz zmienić dane rezerwacji?",
                                      QMessageBox::Ok|QMessageBox::Cancel);
        if(msgBox==QMessageBox::Ok)
        {

            switch (ui->comboBox_zmien->currentIndex())
            {
                case 0:
                {
                    wprowadzenie=ui->lineEdit_zmien->text();
                    QSqlQuery klient("update klient set imie = '"+wprowadzenie+"' where id = '"+id+"' ");
                    if(!klient.exec())
                        QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                    else
                        QMessageBox::information(this," ","Rezerwacja została zmieniona pomyślnie.");
                    break;
                }
                case 1:
                {
                    wprowadzenie=ui->lineEdit_zmien->text();
                    QSqlQuery klient("update klient set nazwisko = '"+wprowadzenie+"' where id = '"+id+"' ");
                    if(!klient.exec())
                        QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                    else
                        QMessageBox::information(this," ","Rezerwacja została zmieniona pomyślnie.");
                    break;
                }
                case 2:
                {
                    data_od=ui->dateEdit_od->text();
                    data_do=ui->dateEdit_do->text();
                    funkcje.NaInta_NaStringa(data_od,data_do);
                    if(funkcje.rezerwacje.size()>0)
                    {
                        if(funkcje.sprawdz_rezerwacje(nr_pokoju,id))
                        {
                            bool poprawnie_dodane=false;
                            QSqlQuery klient;
                            klient.prepare("update klient set data_od='"+data_od+"' where id= '"+id+"'");
                            if(!klient.exec())
                                QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                            else
                                poprawnie_dodane=true;
                            klient.prepare("update klient set data_do='"+data_do+"' where id= '"+id+"'");
                            if(!klient.exec())
                                QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                            else
                                poprawnie_dodane=true;
                            klient.prepare("delete from pokoje where id_klient='"+id+"'");
                            if(!klient.exec())
                                QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                            else
                                poprawnie_dodane=true;
                            for(unsigned int i=0;i<funkcje.rezerwacje.size();i++)
                            {
                                    klient.prepare("insert into Pokoje (id_pokoju, dzien_rezerwacji, Id_klient) values('"+QString::number(nr_pokoju) +
                                                   "','"+funkcje.rezerwacje[i]+"','"+id+"')");
                                    if(!klient.exec())
                                    {
                                        QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                                        poprawnie_dodane=false;
                                    }
                            }
                           if(poprawnie_dodane)
                           {
                                  QMessageBox::information(this,"Edycja","Rezerwacja została zmieniona pomyślnie.");
                                  conn.BazaClose();
                                  funkcje.rezerwacje.clear();
                            }
                            else
                            {
                                  QMessageBox::critical(this,"Edycja","Wystąpił błąd podczas edycji rezerwacji.");
                                  funkcje.rezerwacje.clear();
                            }
                        }
                        else
                        {
                            QMessageBox::warning(this,"Edycja","Podana data jest już zarezerwowana!");
                            funkcje.rezerwacje.clear();
                        }
                    }
                    else
                    {
                        QMessageBox::warning(this,"Edycja","Podana data jest nieprawidłowa!");
                        funkcje.rezerwacje.clear();
                    }
                    break;
                }
                case 3:
                {
                wprowadzenie=ui->lineEdit_zmien->text();
                QSqlQuery klient;
                klient.prepare("update klient set Pokoj = '"+wprowadzenie+"' where id = '"+id+"' ");
                if(!klient.exec())
                    QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                else
                {
                    wprowadzenie=QString::number(wprowadzenie.toInt()-1);
                    klient.prepare("update pokoje set id_pokoju = '"+wprowadzenie+"' where Id_klient = '"+id+"' ");
                    if(!klient.exec())
                        QMessageBox::critical(this,tr("Edycja"),klient.lastError().text());
                    else
                    QMessageBox::information(this," ","Rezerwacja została zmieniona pomyślnie.");
                }
                break;
                }

            }


        }
    }
    else
        QMessageBox::critical(this," ","Brak rezerwacji o podanym ID!");
}
