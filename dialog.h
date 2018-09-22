#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QObject>
#include <QTreeWidgetItem>
#include <QList>



namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void NewChildRoot(QTreeWidgetItem *itm, QString File_name);
    void NewChild(QTreeWidgetItem *ch, QString dirpy);
    void Get_Curr_Dir(QString Report_Dir);
    QString Return_Dir();
    QDir *dir = new QDir;
    QDir *dirp = new QDir;
    QString Dialog_Report_Dir;
    QFileInfo *file = new QFileInfo;
    QList<QTreeWidgetItem*> Dir_List;
    QList<QString> list;


    ~Dialog();

private slots:
    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_pushButton_clicked();

    void on_Cancel_clicked();

    void on_Select_clicked();

private:
    Ui::Dialog *ui;

    QStringList root;

};

#endif // DIALOG_H
