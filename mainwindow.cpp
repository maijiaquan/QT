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
    LINE_WIDTH = 40;   //设置线宽
    head->x = 20;
    head->y = 20;

    snake *s1 = new snake;

    head->next = s1;
    s1->x = head->x + 40;
    s1->y = head->y;
    s1->next = NULL;
    cout<<"s1"<<s1->x<<s1->y<<endl;

    snake *s2 = new snake;

    s1->next = s2;
    s2->x = s1->x + 40;
    s2->y = s1->y;
    s2->next = NULL;

    snake *s3 = new snake;
    s2->next = s3;
    s3->x = s2->x + 40;
    s3->y = s2->y;
    s3->next = NULL;

    cout<<"s2"<<s2->x<<s2->y<<endl;

    ui->setupUi(this);
    resize(640, 640);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//////////////////////////////////////
void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);


    /*画背景网格线*/
    for (int i = 0; i < 16; i++)
    {
        p.drawLine(20, 20 + i * LINE_WIDTH, 620, 20 + i * LINE_WIDTH);
        p.drawLine(20 + i * LINE_WIDTH, 20, 20 + i * LINE_WIDTH, 620);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    p.setBrush(brush);

    snake * temp = new snake;
    temp = head;

    while(temp != NULL){
        p.drawRect(temp->x, temp->y, LINE_WIDTH, LINE_WIDTH);
        temp = temp->next;
    }


}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if(keyValue == Qt::Key_Left ){
        head->x -= LINE_WIDTH;
        moveTail(1);
        update();
    }

    if(keyValue == Qt::Key_Right){
        head->x += LINE_WIDTH;
        moveTail(2);
        update();
    }

    if(keyValue == Qt::Key_Up){
        head->y -= LINE_WIDTH;
        moveTail(3);
        update();
    }

    if(keyValue == Qt::Key_Down){
        head->y += LINE_WIDTH;
        moveTail(4);
        update();
    }
}

/*移动蛇的尾部*/
void MainWindow::moveTail(int direction){
    int first_x;
    int first_y;

    if(direction == 1){
        first_x = head->x + LINE_WIDTH;
        first_y = head->y;
    }

    if(direction == 2){
        first_x = head->x - LINE_WIDTH;
        first_y = head->y;
    }

    if(direction == 3){
        first_x = head->x;
        first_y = head->y + LINE_WIDTH;
    }

    if(direction == 4){
        first_x = head->x;
        first_y = head->y - LINE_WIDTH;
    }


    int second_x;
    int second_y;

    snake *temp = new snake;
    temp = head->next;

    while(temp != NULL){
        /*保存该蛇节的坐标至second*/
        second_x = temp->x;
        second_y = temp->y;


        /*将该a蛇节坐标修改为上一节的坐标first*/
        temp->x = first_x;
        temp->y = first_y;

        /*first是下一个循环的蛇节的上一节的坐标*/
        first_x = second_x;
        first_y = second_y;

        temp = temp->next;
    }
}
