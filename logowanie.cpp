#include "logowanie.h"
#include "ui_logowanie.h"


Logowanie::Logowanie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logowanie)
{
    ui->setupUi(this);

}

Logowanie::~Logowanie()
{
    delete ui;
}
void Logowanie::on_pushButton_login_clicked()
{
    login = ui->lineEdit_login->text();
    haslo = ui->lineEdit_haslo->text();

    if(login=="a" && haslo=="a")
    {
        hide();
        menuGlowne = new MenuGlowne(this);
        menuGlowne->show();
    }
    else
    {
        QMessageBox::warning(this,"Logowanie","Login lub hasło jest nieprawidłowe");
    }
}
