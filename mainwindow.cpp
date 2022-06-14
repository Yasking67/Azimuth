#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_get, SIGNAL(clicked()), this, SLOT(ShowAzimuth()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

float MainWindow::GetAzimuth()
{
    //Optional
    QString starlat, starlon, soslat, soslon;
    float TargetLat, TargetLon, OSLat, OSLon;
    starlat = ui->ledit_TarLat->text();
    starlon = ui->ledit_TarLon->text();
    soslat = ui->ledit_OSLat->text();
    soslon = ui->ledit_OSLon->text();
    TargetLat = starlat.toFloat();
    TargetLon = starlon.toFloat();
    OSLat = soslat.toFloat();
    OSLon = soslon.toFloat();

    //Required
    float longitudinalDifference = TargetLon - OSLon;
    float latitudinalDifference = TargetLat - OSLat;
    float azimuth = (M_PI * 0.5) - qAtan(latitudinalDifference / longitudinalDifference);
    if (longitudinalDifference > 0) return azimuth;
    else if (longitudinalDifference < 0) return azimuth + M_PI;
    else if (latitudinalDifference < 0) return M_PI;
    return 0;
}

void MainWindow::ShowAzimuth()
{
    QString sazimuth;
    float azimuth = GetAzimuth();
    float degazimuth = qRadiansToDegrees(azimuth);
    sazimuth.clear();
    sazimuth.append(QString::number(degazimuth,'g',4));
    ui->ledit_azimuth->setText(sazimuth);
}
