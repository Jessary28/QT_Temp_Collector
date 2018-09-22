#include "dialog.h"
#include "ui_dialog.h"
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTreeWidget>
#include <QList>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Directories");
    //Create parameters for tree widget
    QTreeWidgetItem *tree_root = new QTreeWidgetItem(ui->treeWidget);
    ui->Select_txt->setReadOnly(true);
    //Create Directory Children For Tree Widget
    foreach(*file, dir->drives()){
        if(file->absolutePath() != ""){
             NewChildRoot(tree_root,file->absolutePath());
        }
    }
    ui->treeWidget->addTopLevelItem(tree_root);
}

Dialog::~Dialog()
{
    delete ui;
}

//Add root directories to tree widget top level item
void Dialog::NewChildRoot(QTreeWidgetItem *itm, QString File_name){
    QTreeWidgetItem *child = new QTreeWidgetItem(ui->treeWidget);
    child->setText(0, File_name);
    itm->addChild(child);
    NewChild(child, File_name);
}

//Add sub directories to root directories
void Dialog::NewChild(QTreeWidgetItem *ch, QString dirpy){
    QFileInfo* F = new QFileInfo;
    QDir dirp(dirpy);
    foreach(*F, dirp.entryInfoList(QDir::Dirs,QDir::DirsFirst)){
        QTreeWidgetItem *SubDir = new QTreeWidgetItem();
        SubDir->setText(0, F->fileName());
        //Correct Static file path issue.
        SubDir->setIcon(0,QIcon("C:/Users/LEssary/Documents/Epoxy_Temp_Project/Documents-icon.png"));
        ch->addChild(SubDir);
    }
}

void Dialog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
   //Set the Select Text to Current Index

   if(!(current->parent() == NULL)){
        ui->Select_txt->setPlainText(current->text(0));
        QTreeWidgetItem *par = current;
        while(!(par->parent() == NULL)){
        ui->Select_txt->moveCursor(QTextCursor::StartOfLine);
        ui->Select_txt->insertPlainText(par->parent()->text(0));
        ui->Select_txt->insertPlainText("/");
        par = par->parent();
        }

   }
   else{
        ui->Select_txt->setPlainText(current->text(0));
   }


   NewChild(current,ui->Select_txt->toPlainText());  //Add in functionality for multiple layers of browser
}

void Dialog::on_Select_clicked()
{
     //Finish selection and return new populated text
     this->close();
}


void Dialog::on_Cancel_clicked()
{
 //Canceled selection, resets data to previous, and closes window
 ui->Select_txt->setPlainText(Dialog_Report_Dir);
 this->close();
}


QString Dialog::Return_Dir(){
    //Passes selection back to File_worker class and then to main_window
    return ui->Select_txt->toPlainText();
}

void Dialog::Get_Curr_Dir(QString Report_Dir){
    Dialog_Report_Dir = Report_Dir;
}


