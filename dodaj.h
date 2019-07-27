#ifndef DODAJ_H
#define DODAJ_H

#include <QWidget>
#include <QDialog>
#include <menuglowne.h>
#include <QMessageBox>




namespace Ui {
class Dodaj;
}

class Dodaj :  public QDialog
{
    Q_OBJECT

public:
    QString src;
    explicit Dodaj(QWidget *parent = nullptr);
    QDateTime zerowa_data = QDateTime::fromString("01.01.2000", "dd.MM.yyyy");
    QString data_od="01.01.2000";
    QString data_do="01.01.2000";
    std::vector<QString> rezerwacje;
    void NaInta_NaStringa(QString, QString);
    bool sprawdz_rezerwacje(int);
    bool sprawdz_rezerwacje(int nr_pokoju,QString id);

    ~Dodaj();

private slots:
    void on_pushButton_anuluj_clicked();

    void on_pushButton_dodaj_clicked();


protected:
    void closeEvent(QCloseEvent *e) override;


private:
    Ui::Dodaj *ui;
    MenuGlowne *menuGlowne;
    QString id;
    QString imie;
    QString nazwisko;



};

#endif // DODAJ_H
