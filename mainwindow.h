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
    hashset_t set;
    QHash<char *, unsigned int> hash;
    QList<QString> visual_set;
    unsigned int counter;
    ~MainWindow();

private slots:
    void on_insertBtn_clicked();

    void on_memberBtn_clicked();

    void on_removeBtn_clicked();

    int checkInputHash(int key, char * input);
    void visualize();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
