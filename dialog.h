#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDate>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();


private slots:
    void on_btnKeluar_clicked();
    void on_btnSimpan_clicked();
    QString bacaFile(int enume=0);
    void editFile(int nilai);
    //QString port();

private:
    Ui::Dialog *ui;
    QString baris;
    QString proxconf;

};

#endif // DIALOG_H
