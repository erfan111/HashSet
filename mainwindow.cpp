#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidgetItem>
#include <QDebug>
#include <string>
#include <QString>
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter1 = 65535;
    counter2= 65535;
    set1 = hashset_create();
    set2 = hashset_create();
    //hash = new QHash<char *, unsigned int>();
    this->setFixedSize(600,600);
    this->adjustSize();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertBtn1_clicked()
{
    QString  foo =  ui->input1->text();
    if (foo.length())
    {
        char * input1 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input1[i] = mystring[i];
        }


        int inputHash = atoi(input1);
        int result_of_insertion = checkInputHash1(inputHash, input1);
        if(result_of_insertion == 1)
        {
            visual_set1.append(foo);
        }
         visualize1();

    }
    ui->input1->clear();
}

void MainWindow::on_memberBtn1_clicked()
{
    QString  foo =  ui->input1->text();
    if (foo.length())
    {
        char * input1 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input1[i] = mystring[i];
        }
        int inputHash = atoi(input1);
        int result = 0;
        if(inputHash)
            result = hashset_is_member(set1,(void*) inputHash);
        else
        {
            QHashIterator<char *, unsigned int> i(hash1);
            while (i.hasNext()) {
                i.next();
                qDebug()<< input1 << " " << i.key();
                if(strcmp (input1, i.key()) == 0)
                {
                    qDebug()<< "key" << i.key();
                    result = 1;
                    break;
                }
            }

        }

        if(result)
            ui->mgbox1->setText("Is in set");
        else
            ui->mgbox1->setText("Not in set");

    }
    ui->input1->clear();

}

void MainWindow::on_removeBtn1_clicked()
{
    QString  foo =  ui->input1->text();
    int result = 0;
    if (foo.length())
    {
        char * input1 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input1[i] = mystring[i];
        }
        int inputHash = atoi(input1);

        if(inputHash)
        {

            result = hashset_remove(set1,(void*) inputHash);
            qDebug() << "removing number: "  <<visual_set1.removeOne(input1) <<visual_set1 ;
        }

        else
        {
            QHashIterator<char *, unsigned int> i(hash1);
            while (i.hasNext()) {
                i.next();
                if(strcmp (input1, i.key()) == 0)
                {
                    result = hashset_remove(set1,(void*) i.value());
                    qDebug() << hash1.remove(i.key()) << " removing from hash: " << i.key() << " ";
                    QHashIterator<char *, unsigned int> j(hash1);
                    while (j.hasNext()) {
                        j.next();
                        qDebug() << i.key() << " " ;
                    }
                    visual_set1.removeOne(i.key());
                    break;
                }
            }
        }

    }

    else
    {
        if(item_for_remove.length())
        {
            for(int j=0; j<visual_set1.length(); j++)
            {
                if(item_for_remove == visual_set1[j])
                {
                    QByteArray temp = item_for_remove.toLatin1();
                    const char * remove = temp.data();
                    visual_set1.removeOne(visual_set1[j]);
                    int selected = atoi(remove);
                    if(selected)
                    {

                        result = hashset_remove(set1,(void*) selected);
                        qDebug() << "removing number: "  <<visual_set1.removeOne(remove) <<visual_set1 ;
                    }

                    else
                    {
                        QHashIterator<char *, unsigned int> x(hash1);
                        while (x.hasNext()) {
                            x.next();
                            if(strcmp (remove, x.key()) == 0)
                            {
                                result = hashset_remove(set1,(void*) x.value());
                                qDebug() << hash1.remove(x.key()) << " removing from hash: " << x.key() << " ";
                                QHashIterator<char *, unsigned int> y(hash1);
                                while (y.hasNext()) {
                                    y.next();
                                    qDebug() << x.key() << " " ;
                                }
                                break;
                            }
                        }
                    }
                }
            }

        }
    }

    if(result)
        ui->mgbox1->setText("Successfully removed");
    else
        ui->mgbox1->setText("Value Not in set");

    ui->input1->clear();
    visualize1();

}


int MainWindow::checkInputHash1(int key, char * input)
{
    int a= 0;
    if(key)
    {
        a = hashset_add(set1, (void *) key);
        if(a == 1)
            address_tracker1.append(QString::number(hashset_member_address(set1,(void *) key)));


    }
    else
    {
        QHashIterator<char *, unsigned int> i(hash1);
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
            hash1.insert(input, counter1);
            a = hashset_add(set1, (void *) counter1);
            if(a == 1)
                address_tracker1.append(QString::number(hashset_member_address(set1, (void *)counter1)));
            counter1 --;
        }


    }
    switch (a){
    case -1:
        ui->mgbox1->setText("Not a valid value to insert");
        break;
    case 0:
        ui->mgbox1->setText("Already in set");
        break;
    case 1:
        ui->mgbox1->setText("Successfully inserted");
        break;
    default:
        ui->mgbox1->setText("");
    }
    return(a);
}

void MainWindow::visualize1(){
    ui->setViewer1->clear();
    QListWidgetItem *listWidgetItem = new QListWidgetItem("ITEM \t ADDRESS" );
    ui->setViewer1->addItem(listWidgetItem);
    for(int i = 0;i < visual_set1.size();i++){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set1.at(i) + "\t" + address_tracker1.at(i));
        ui->setViewer1->addItem(listWidgetItem);
    }
}


////////////////////////////////////////// SET 2
///


void MainWindow::on_insertBtn2_clicked()
{
    QString  foo =  ui->input2->text();
    if (foo.length())
    {
        char * input2 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input2[i] = mystring[i];
        }


        int inputHash = atoi(input2);

        int result_of_insertion = checkInputHash2(inputHash, input2);
        if(result_of_insertion == 1)
        {
            visual_set2.append(foo);
        }
         visualize2();

    }
    ui->input2->clear();
}

void MainWindow::on_memberBtn2_clicked()
{
    QString  foo =  ui->input2->text();
    if (foo.length())
    {
        char * input2 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input2[i] = mystring[i];
        }
        int inputHash = atoi(input2);
        int result = 0;
        if(inputHash)
            result = hashset_is_member(set2,(void*) inputHash);
        else
        {
            QHashIterator<char *, unsigned int> i(hash2);
            while (i.hasNext()) {
                i.next();
                qDebug()<< input2 << " " << i.key();
                if(strcmp (input2, i.key()) == 0)
                {
                    qDebug()<< "key" << i.key();
                    result = 2;
                    break;
                }
            }

        }

        if(result)
            ui->mgbox2->setText("Is in set");
        else
            ui->mgbox2->setText("Not in set");

    }
    ui->input2->clear();

}

void MainWindow::on_removeBtn2_clicked()
{
    QString  foo =  ui->input2->text();
    int result = 0;
    if (foo.length())
    {
        char * input2 = new char[foo.length()];

        std::string mystring = foo.toStdString();

        for(int i = 0; i < foo.length(); i++)
        {
            input2[i] = mystring[i];
        }
        int inputHash = atoi(input2);

        if(inputHash)
        {

            result = hashset_remove(set2,(void*) inputHash);
            qDebug() << "removing number: "  <<visual_set2.removeOne(input2) <<visual_set2 ;
        }

        else
        {
            QHashIterator<char *, unsigned int> i(hash2);
            while (i.hasNext()) {
                i.next();
                if(strcmp (input2, i.key()) == 0)
                {
                    result = hashset_remove(set2,(void*) i.value());
                    qDebug() << hash2.remove(i.key()) << " removing from hash: " << i.key() << " ";
                    QHashIterator<char *, unsigned int> j(hash2);
                    while (j.hasNext()) {
                        j.next();
                        qDebug() << i.key() << " " ;
                    }
                    visual_set2.removeOne(i.key());
                    break;
                }
            }
        }

    }
    else
    {
        if(item_for_remove.length())
        {
            for(int j=0; j<visual_set2.length(); j++)
            {
                if(item_for_remove == visual_set2[j])
                {
                    QByteArray temp = item_for_remove.toLatin1();
                    const char * remove = temp.data();
                    visual_set2.removeOne(visual_set2[j]);
                    int selected = atoi(remove);
                    if(selected)
                    {

                        result = hashset_remove(set2,(void*) selected);
                        qDebug() << "removing number: "  <<visual_set2.removeOne(remove) <<visual_set2 ;
                    }

                    else
                    {
                        QHashIterator<char *, unsigned int> x(hash2);
                        while (x.hasNext()) {
                            x.next();
                            if(strcmp (remove, x.key()) == 0)
                            {
                                result = hashset_remove(set2,(void*) x.value());
                                qDebug() << hash2.remove(x.key()) << " removing from hash: " << x.key() << " ";
                                QHashIterator<char *, unsigned int> y(hash2);
                                while (y.hasNext()) {
                                    y.next();
                                    qDebug() << x.key() << " " ;
                                }
                                break;
                            }
                        }
                    }
                }
            }

        }
    }

    if(result)
        ui->mgbox2->setText("Successfully removed");
    else
        ui->mgbox2->setText("Value Not in set");

    ui->input2->clear();
    visualize2();

}


int MainWindow::checkInputHash2(int key, char * input)
{
    int a= 0;
    if(key)
    {
        a = hashset_add(set2, (void *) key);
        if(a == 1)
            address_tracker2.append(QString::number(hashset_member_address(set2,(void *) key)));

    }
    else
    {
        QHashIterator<char *, unsigned int> i(hash2);
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
            hash2.insert(input, counter2);
            a = hashset_add(set2, (void *) counter2);
            if(a == 1)
                address_tracker2.append(QString::number(hashset_member_address(set2,(void *) counter2)));
            counter2 --;
        }


    }
    switch (a){
    case -1:
        ui->mgbox2->setText("Not a valid value to insert");
        break;
    case 0:
        ui->mgbox2->setText("Already in set");
        break;
    case 1:
        ui->mgbox2->setText("Successfully inserted");
        break;
    default:
        ui->mgbox2->setText("");
    }
    return(a);
}

void MainWindow::visualize2(){
    ui->setViewer2->clear();
    QListWidgetItem *listWidgetItem = new QListWidgetItem("ITEM \t ADDRESS" );
    ui->setViewer2->addItem(listWidgetItem);
    for(int i = 0;i < visual_set2.size();i++){
        QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set2.at(i) + "\t" + address_tracker2.at(i));
        ui->setViewer2->addItem(listWidgetItem);
    }
}



void MainWindow::on_equalBtn_clicked()
{
    ui->resultViewer->clear();
    if(visual_set1.size()> visual_set2.size())
    {
        for(int i=0;i< visual_set1.size();i++)
        {
            if(!visual_set2.contains(visual_set1.at(i)))
            {
                QListWidgetItem *listWidgetItem = new QListWidgetItem("TWO SETS ARE NOT EQUAL");
                ui->resultViewer->addItem(listWidgetItem);
                return;
            }
        }
        QListWidgetItem *listWidgetItem = new QListWidgetItem("TWO SETS ARE EQUAL");
        ui->resultViewer->addItem(listWidgetItem);
        return;
    }
    else{
        for(int i=0;i< visual_set2.size();i++)
        {
            if(!visual_set1.contains(visual_set2.at(i)))
            {
                QListWidgetItem *listWidgetItem = new QListWidgetItem("TWO SETS ARE NOT EQUAL");
                ui->resultViewer->addItem(listWidgetItem);
                return;
            }
        }
        QListWidgetItem *listWidgetItem = new QListWidgetItem("TWO SETS ARE EQUAL");
        ui->resultViewer->addItem(listWidgetItem);
        return;
    }


}

void MainWindow::on_intersectionBtn_clicked()
{
    ui->resultViewer->clear();
    bool flag = 0;
    for(int i=0;i< visual_set1.size();i++)
    {
        if(visual_set2.contains(visual_set1.at(i)))
        {
            QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set1.at(i));
            ui->resultViewer->addItem(listWidgetItem);
            flag = 1;
        }

    }
    if(!flag)
    {
        QListWidgetItem *listWidgetItem = new QListWidgetItem("TWO SETS DONT HAVE INTERSECTION");
        ui->resultViewer->addItem(listWidgetItem);
    }

}

void MainWindow::on_unioBtn_clicked()
{
    ui->resultViewer->clear();
    for(int i=0;i< visual_set2.size();i++)
    {
        QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set2.at(i));
        ui->resultViewer->addItem(listWidgetItem);
    }
    for(int i=0;i< visual_set1.size();i++)
    {
        if(!visual_set2.contains(visual_set1.at(i)))
        {
            QListWidgetItem *listWidgetItem = new QListWidgetItem(visual_set1.at(i));
            ui->resultViewer->addItem(listWidgetItem);
        }

    }


}


void MainWindow::on_setViewer1_clicked(const QModelIndex &index)
{
    item_for_remove.clear();
    ui->mgbox1->setText("Press 'Remove Item' button to remove this item");

    for(int i=0; i<index.data().toString().length(); i++)
    {
        if (index.data().toString()[i] != '\t')
            item_for_remove += index.data().toString()[i];
        else
            break;
    }
}



void MainWindow::on_setViewer2_clicked(const QModelIndex &index)
{
    item_for_remove.clear();
    ui->mgbox2->setText("Press 'Remove Item' button to remove this item");

    for(int i=0; i<index.data().toString().length(); i++)
    {
        if (index.data().toString()[i] != '\t')
            item_for_remove += index.data().toString()[i];
        else
            break;
    }

}







