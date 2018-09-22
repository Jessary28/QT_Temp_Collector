#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "file_worker.h"





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = nullptr);
    File_Worker t;
    QStringList Data_List;
    QStringList Create_Settings_List();
    QString Setting_dat_from_file;
    QStringList Setting_dat_list;
    void Run();
    void EventLogger(QString Log_Data);
    void correcttempscale(QString TempScale);
    ~MainWindow();

private slots:
    void on_browse_clicked();

    void on_Change_clicked();

    void on_pushButton_clicked();

    void on_SENUNITS_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
