#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QKeyEvent>
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    s1.x = 20;
    s1.y = 20;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//////////////////////////////////////
void MainWindow::paintEvent(QPaintEvent *)  //画背景
{

    QPainter p(this);

    p.setRenderHint(QPainter::Antialiasing, true);
    for (int i = 0; i < 16; i++)
    {
        p.drawLine(20, 20 + i * 40, 620, 20 + i * 40);
        p.drawLine(20 + i * 40, 20, 20 + i * 40, 620);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    p.setBrush(brush);
    p.drawRect(20,60,40,40);
    p.drawRect(s1.x,s1.y,40,40);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();

    if(keyValue == Qt::Key_Left ){
        cout<<"left"<<endl;
        s1.y += 40;
        cout<< s1.y;
        update();
        cout<< s1.y;
    }
}
