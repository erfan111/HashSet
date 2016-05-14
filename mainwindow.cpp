#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>
#include <QDebug>
#include <string>
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 65535;
    set = hashset_create();
    //hash = new QHash<char *, unsigned int>();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertBtn_clicked()
{
    QString  foo =  ui->input->text();
    if (foo.length())
    {
        char * input = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input[i] = mystring[i];
        }


        int inputHash = atoi(input);

        int result_of_insertion = checkInputHash(inputHash, input);
        if(result_of_insertion)
        {
            visual_set.append(foo);
        }
         visualize();

    }
    ui->input->clear();
}

void MainWindow::on_memberBtn_clicked()
{
    QString  foo =  ui->input->text();
    if (foo.length())
    {
        char * input = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input[i] = mystring[i];
        }
        int inputHash = atoi(input);
        int result = 0;
        if(inputHash)
            result = hashset_is_member(set,(void*) inputHash);
        else
        {
            QHashIterator<char *, unsigned int> i(hash);
            while (i.hasNext()) {
                i.next();
                qDebug()<< input << " " << i.key();
                if(strcmp (input, i.key()) == 0)
                {
                    qDebug()<< "key" << i.key();
                    result = 1;
                    break;
                }
            }

        }

        if(result)
            ui->mgbox->setText("Is in set");
        else
            ui->mgbox->setText("Not in set");

    }
    ui->input->clear();

}

void MainWindow::on_removeBtn_clicked()
{
    QString  foo =  ui->input->text();
    if (foo.length())
    {
        char * input = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input[i] = mystring[i];
        }
        int inputHash = atoi(input);
        int result = 0;
        if(inputHash)
        {

            result = hashset_remove(set,(void*) inputHash);
            qDebug() << "removing number: "  <<visual_set.removeOne(input) <<visual_set ;
        }

        else
        {
            QHashIterator<char *, unsigned int> i(hash);
            while (i.hasNext()) {
                i.next();
                if(strcmp (input, i.key()) == 0)
                {
                    result = hashset_remove(set,(void*) i.value());
                    qDebug() << hash.remove(i.key()) << " removing from hash: " << i.key() << " ";
                    QHashIterator<char *, unsigned int> j(hash);
                    while (j.hasNext()) {
                        j.next();
                        qDebug() << i.key() << " " ;
                    }
                    visual_set.removeOne(i.key());
                    break;
                }
            }
        }
        if(result)
            ui->mgbox->setText("Successfully removed");
        else
            ui->mgbox->setText("Value Not in set");

    }
    ui->input->clear();
    visualize();

}


int MainWindow::checkInputHash(int key, char * input)
{
    int a= 0;
    if(key)
    {
        a = hashset_add(set, (void *) key);

    }
    else
    {
        QHashIterator<char *, unsigned int> i(hash);
        int flag = 0;
        while (i.hasNext()) {
            i.next();
            qDebug()<< input << " " << i.key();
            if(strcmp (input, i.key()) == 0)
            {
                a = 0;
                flag = 1;
                break;
            }
        }

        if(! flag)
        {
            a = 1;
            hash.insert(input, counter);
            a = hashset_add(set, (void *) counter);
            counter --;
        }


    }
    switch (a){
    case -1:
        ui->mgbox->setText("Not a valid value to insert");
        break;
    case 0:
        ui->mgbox->setText("Already in set");
        break;
    case 1:
        ui->mgbox->setText("Successfully inserted");
        break;
    default:
        ui->mgbox->setText("fucked");
    }
    return(a);
}

void MainWindow::visualize(){
    ui->setViewer->clear();
    for(int i = 0;i < visual_set.size();i++){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set.at(i));
        ui->setViewer->addItem(listWidgetItem);
    }
}


