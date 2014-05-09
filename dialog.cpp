#include "dialog.h"
#include "ui_dialog.h"
//#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    proxconf = (QDir::homePath()+"/.proxychains/proxychains.conf");

    QFile confF(proxconf);
    if(!confF.exists())
    {
        confF.open(QIODevice::WriteOnly);
        QTextStream tulis(&confF);
        tulis.operator <<("# Created by Editsox on "+QDate::currentDate().toString("dddd, dd MMMM yyyy")+"\n\n");
        tulis.operator <<("strict_chain\n");
        tulis.operator <<("proxy_dns\n");
        tulis.operator <<("tcp_read_time_out 15000\n");
        tulis.operator <<("tcp_connect_time_out 8000\n");
        tulis.operator <<("[ProxyList]\n");
        tulis.operator <<("socks5\t127.0.0.1 1080\n");
        ui->spinBox->setValue(1080);
        confF.close();
    }
    else
    {
        ui->spinBox->setValue(bacaFile(0).toInt());
        confF.close();
    }

}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::bacaFile(int enume)
{
    //enume 0 = port
    //enume 1 = all text
    QFile confG(proxconf);
    QString prott;
    QString tekst;
    if(enume == 0)
    {
        if(confG.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream baca(&confG);

            while(!baca.atEnd())
            {
                baris = baca.readLine();
                if(!baris.contains("#") && baris.contains("socks5"))
                {
                    QStringList larik(baris.split(" "));
                    prott = larik.at(1);
                }
            }
            return(prott);
            confG.close();

            ui->labelStatus->setText("File Terbuka");
        }

        else
        {
            ui->labelStatus->setText("Ada Kesalahan");
        }
    }
    else if(enume == 1)
    {
        if(confG.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream baca(&confG);
            tekst = baca.readAll();
            return(tekst);
            confG.close();
        }
    }
    return(0);
}


void Dialog::editFile(int nilai)
{
    QFile confH(proxconf);
    QString isi = bacaFile(1);
    QString ganti = isi.replace(bacaFile(0),QString::number(nilai));
    //qDebug() << ganti;
    if(confH.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //QTextStream alir(&isi);
        //QString isiAlir(alir.readAll());

        confH.write(ganti.toLatin1());
        confH.close();
        ui->labelStatus->setText("Berhasil disimpan");

    }
    else
    {
        ui->labelStatus->setText("Gagal disimpan");
    }
}


void Dialog::on_btnKeluar_clicked()
{
    qApp->quit();
}

void Dialog::on_btnSimpan_clicked()
{
    editFile(ui->spinBox->value());
}
