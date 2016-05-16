#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashset.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <QHash>
#include <QListWidgetItem>
#include <QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    hashset_t set1;
    QHash<char *, unsigned int> hash1;
    QList<QString> visual_set1;
    QList<QString> address_tracker1;
    unsigned int counter1;

    hashset_t set2;
    QHash<char *, unsigned int> hash2;
    QList<QString> visual_set2;
    QList<QString> address_tracker2;
    unsigned int counter2;
    QString item_for_remove;
    ~MainWindow();

private slots:
    void on_insertBtn1_clicked();

    void on_memberBtn1_clicked();

    void on_removeBtn1_clicked();

    int checkInputHash1(int key, char * input);
    void visualize1();

    void on_insertBtn2_clicked();

    void on_memberBtn2_clicked();

    void on_removeBtn2_clicked();

    int checkInputHash2(int key, char * input);
    void visualize2();

    void on_equalBtn_clicked();

    void on_intersectionBtn_clicked();

    void on_unioBtn_clicked();

    void on_setViewer2_clicked(const QModelIndex &index);

    void on_setViewer1_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
