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
//    first_x = 20;
//    first_y = 20;

   head->x = 20;
   head->y = 20;

    snake *s1 = new snake;

    head->next = s1;
    s1->x = head->x + 40;
    s1->y = head->y;
    s1->next = NULL;

    snake *s2 = new snake;
    s1->next = s2;
    s2->x = s1->x + 40;
    s2->y = s1->y;
    s2->next = NULL;



//    second_x = 0 ;
//    second_y =0;
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

    snake * temp = new snake;
    temp = head;

    while(temp != NULL){
        p.drawRect(temp->x, temp->y, 40, 40);
        temp = temp->next;
    }


}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if(keyValue == Qt::Key_Left ){
        head->x -= 40;
        update();
    }

    if(keyValue == Qt::Key_Right){
        head->x += 40;
        update();
    }

    if(keyValue == Qt::Key_Up){
        head->y -= 40;
        update();
    }

    if(keyValue == Qt::Key_Down){
        head->y += 40;
        update();
    }
}

//void MainWindow::moveTail(){
//    snake *temp = new snake;
//    temp = head->next;
//    while(temp != NULL){
//        second_x = temp->x;
//        second_y = temp->y;

//        temp->x = first_x;
//        temp->y = first_y;

//        temp = temp->next;
//    }
//}
