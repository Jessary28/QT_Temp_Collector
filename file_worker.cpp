#include "file_worker.h"
#include "dialog.h"
#include <QString>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QtWidgets>
#include <QPushButton>
#include <QObject>

File_Worker::File_Worker()
{

}



QString File_Worker::Select_Dir(QString Report_Curr_Dir){

    //Show Browser to Select Directory
    browse->Get_Curr_Dir(Report_Curr_Dir);
    browse->setFixedSize(610,482);
    browse->setModal(true);
    browse->exec();



    //Return Directory String to be Placed in Text Box Display
    QString Save_Dir = browse->Return_Dir();
    return Save_Dir;

}

QString File_Worker::Save_Data(QString Directory, QString File_Name, QStringList Data_Written){
    QString file_maker;
    file_maker.append(Directory);
    file_maker.append("/");
    file_maker.append(File_Name);
    QFile *mfile = new QFile(file_maker);

    if(mfile->open(QIODevice::ReadWrite) == true){
       QTextStream out(mfile);
       for(int i = 0; i <= Data_Written.length()-1; i++){
           //code broken. Please fix me!
           out << Data_Written[i];
           out << ",";
       }

       return "Winning: File Write Successful!";
    }
    else{
       return "Error: File Could Not Be Written!";
    }
    mfile->close();
    mfile->flush();
}

QString File_Worker::Create_Setting_Dir(QString Setting_Dir){
        QFile *setfile = new QFile(Setting_Dir);
        QString Settings_Data;
        if(setfile->open(QIODevice::ReadWrite)){
           Settings_Data = setfile->readAll();
           return Settings_Data;
        }
        else{
            if(setfile->open(QIODevice::ReadOnly)){
                return "";
            }
            return "Err";
        }
        setfile->close();
        setfile->flush();

}

//Checks to make sure the setting folder exsists before saving or attempting read settings
QString File_Worker::Check_Setting_Dir(){
    QString Setting_dir = "C:/EpoxyTemp/Settings" ;
    QDir setting(Setting_dir);
    if(!(setting.exists())){
        setting.mkpath(Setting_dir);
    }

    return Setting_dir;

}
