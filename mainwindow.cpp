#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "file_worker.h"
#include "QStringList"
#include "cbw.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Sets up ui parameters and calls settings file to be read into program
    ui->setupUi(this);
    ui->statusBar->showMessage("System Boot...",10000);
    ui->tabWidget->autoFillBackground();
    //Retreives Settings Data from file
    QString Main_Setting_Dir = t.Check_Setting_Dir();
    Main_Setting_Dir.append("/Settings.txt");
    Setting_dat_from_file = t.Create_Setting_Dir(Main_Setting_Dir);
    if(!(Setting_dat_from_file == "Err")){
        if(!(Setting_dat_from_file == "")){
            Setting_dat_list = Setting_dat_from_file.split(",");
        }
    }
    //Sets Object values setting file saved settings
    ui->Directory_txt->setPlainText(Setting_dat_list[0]);
    ui->Report_name->setPlainText(Setting_dat_list[1]);
    ui->S1GAIN->setPlainText(Setting_dat_list[2]);
    ui->S2GAIN->setPlainText(Setting_dat_list[3]);
    ui->S3GAIN->setPlainText(Setting_dat_list[4]);
    for(int i = 0 ; i<= ui->AVGMIN->count() ; i++){
        ui->AVGMIN->setCurrentIndex(i);
        if((ui->AVGMIN->currentText()) == Setting_dat_list[5]){
            break;
        }
    }
    for(int i = 0 ; i<= ui->SENUNITS->count() ; i++){
        ui->SENUNITS->setCurrentIndex(i);
        if((ui->SENUNITS->currentText()) == Setting_dat_list[6]){
            break;
        }
    }
    //Set up Chart Display for Temp sensors. Hooray!
    ui->qplot->xAxis->setLabel("Time:Hours");
    QCPRange k(0,24);
    ui->qplot->xAxis->setRange(k);
    ui->qplot->yAxis->setLabel("Temperature!");
    QString temp_scale = ui->SENUNITS->currentText();


    //event log trial
    EventLogger("Some Test Data");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browse_clicked()
{
    //Opens a browser to select directory t is an instance of file_worker, which in turn calls the dialog class for the browser and returns a string of the directory
    ui->Directory_txt->setPlainText(t.Select_Dir(ui->Directory_txt->toPlainText()));
}



void MainWindow::on_Change_clicked()
{
    //Saves the current program settings and directory reference to a txt file in C:/EpoxyTemp/Settings.txt
    Create_Settings_List();
    ui->statusBar->showMessage(t.Save_Data(t.Check_Setting_Dir(), "/Settings.txt", Data_List));

}

QStringList MainWindow::Create_Settings_List(){
   Data_List.clear();
    //Creates a settings list to write to file
   Data_List.append(ui->Directory_txt->toPlainText());
   Data_List.append(ui->Report_name->toPlainText());
   Data_List.append(ui->S1GAIN->toPlainText());
   Data_List.append(ui->S2GAIN->toPlainText());
   Data_List.append(ui->S3GAIN->toPlainText());
   Data_List.append(ui->AVGMIN->currentText());
   Data_List.append(ui->SENUNITS->currentText());
   return Data_List;
}



void MainWindow::on_pushButton_clicked()
{
    //cbFlashLED(0);
    cbDConfigPort(0,FIRSTPORTA,DIGITALIN);
    USHORT D;
    cbDIn(0,FIRSTPORTA,&D);
    int w = (D >> 0) & 1;
    int k = (D >> 1) & 1;
    ui->H_ON->setPlainText(QString::number(w));
    ui->D_OPEN->setPlainText(QString::number(k));
    if(w == 0){
        ui->H_ON->setStyleSheet("background-color:green;");
    }
    else{
        ui->H_ON->setStyleSheet("background-color:red;");
    }

}

void MainWindow::Run(){
    while(true){
        cbDConfigPort(0,FIRSTPORTA,DIGITALIN);
        USHORT D;
        cbDIn(0,FIRSTPORTA,&D);
        int w = (D >> 0) & 1;
        int k = (D >> 1) & 1;
        ui->H_ON->setPlainText(QString::number(w));
        ui->D_OPEN->setPlainText(QString::number(k));
        if(w == 0){
            ui->H_ON->setStyleSheet("background-color:green;");
        }
        else{
            ui->H_ON->setStyleSheet("background-color:red;");
        }

    }

}

void MainWindow::EventLogger(QString Log_Data){
    QTime t = t.currentTime();
    ui->EventLog->append(Log_Data + " " + t.toString() + "\n");
}

//resets the scale to match the scale selected
void MainWindow::correcttempscale(QString TempScale){
    QCPRange tmprange(0,20);
    if(TempScale == "K"){
       tmprange.lower = 180;
       tmprange.upper = 300;
       ui->qplot->yAxis->setRange(tmprange);
    }
    else if(TempScale == "C"){
        tmprange.lower = 0;
        tmprange.upper = 500;
        ui->qplot->yAxis->setRange(tmprange);
    }
    else if(TempScale == "F"){
        tmprange.lower = 32;
        tmprange.upper = 600;
        ui->qplot->yAxis->setRange(tmprange);
    }
}

void MainWindow::on_SENUNITS_currentIndexChanged(const QString &arg1)
{
    correcttempscale(arg1);
}
