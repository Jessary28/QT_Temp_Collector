#ifndef FILE_WORKER_H
#define FILE_WORKER_H

#include <QMainWindow>
#include <QString>
#include "dialog.h"
#include <QDir>


class File_Worker
{
public:
    File_Worker();
    Dialog *browse = new Dialog;
    QDir *direct = new QDir;
    QString Select_Dir(QString Report_Curr_Dir);
    QString *Save_Dir;
    QString Save_Data(QString Directory, QString File_Name, QStringList Data_Written);
    QString Create_Setting_Dir(QString Setting_Dir);
    QString Check_Setting_Dir();

    QStringList open_data_list;

};

#endif // FILE_WORKER_H
