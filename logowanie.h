#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QDialog>
#include "menuglowne.h"
#include <QMessageBox>

namespace Ui {
class Logowanie;
}

class Logowanie : public QDialog
{
    Q_OBJECT

public:
    explicit Logowanie(QWidget *parent = nullptr);
    ~Logowanie();

private slots:
        void on_pushButton_login_clicked();


private:
    Ui::Logowanie *ui;
    QString login;
    QString haslo;
    MenuGlowne *menuGlowne;
};

#endif // LOGOWANIE_H
