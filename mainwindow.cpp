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

    /*初始化方向*/
    DIR_RIGHT = 1;
    DIR_LEFT = 2;
    DIR_DOWN = 3;
    DIR_UP =4;
    CURR_DIR = DIR_DOWN;




    head = new snake;
    /*食物*/
    food = new snake;
    food->y = 5;
    food->x = 5;
    food->next = NULL;

    /*初始化全局变量*/
    LINE_WIDTH = 40;   //设置线宽

    /*默认游戏开始时就存在的蛇*/



    head->x = 0;
    head->y = 0;



    snake *s1 = new snake;

    head->next = s1;
    s1->x = head->x + 1;
    s1->y = head->y;
    s1->next = NULL;

    snake *s2 = new snake;

    s1->next = s2;
    s2->x = s1->x + 1;
    s2->y = s1->y;
    s2->next = NULL;

    snake *s3 = new snake;
    s2->next = s3;
    s3->x = s2->x + 1;
    s3->y = s2->y;
    s3->next = NULL;



    ////////////////////////
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

    /*遍历链表，画蛇*/
    while(temp != NULL){
        p.drawRect(temp->x * LINE_WIDTH + 20, temp->y * LINE_WIDTH + 20, LINE_WIDTH, LINE_WIDTH);
        temp = temp->next;
    }

    /*画食物*/
    p.drawRect(food->x * LINE_WIDTH + 20, food->y * LINE_WIDTH + 20, LINE_WIDTH, LINE_WIDTH);

}

/*接收键盘事件，移动蛇头*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if(keyValue == Qt::Key_Left ){
        head->x -= 1;
        moveTail(1);
    }

    if(keyValue == Qt::Key_Right){
        head->x += 1;
        moveTail(2);
    }

    if(keyValue == Qt::Key_Up){
        head->y -= 1;
        moveTail(3);
    }

    if(keyValue == Qt::Key_Down){
        head->y += 1;
        moveTail(4);
    }
    cout<<head->x<<" "<<head->y<<endl;
    eat();
    update();
}

/*移动蛇的尾部*/
void MainWindow::moveTail(int direction){

    /*first用于保存蛇头移动前的坐标*/
    int first_x;
    int first_y;

    if(direction == 1){   //右
        CURR_DIR = DIR_LEFT;
        first_x = head->x + 1;
        first_y = head->y;
    }

    if(direction == 2){   //左
        CURR_DIR = DIR_RIGHT;
        first_x = head->x - 1;
        first_y = head->y;
    }

    if(direction == 3){   //上
        CURR_DIR = DIR_UP;
        first_x = head->x;
        first_y = head->y + 1;
    }

    if(direction == 4){   //
        CURR_DIR = DIR_DOWN;
        first_x = head->x;
        first_y = head->y - 1;
    }

    int second_x;
    int second_y;

    snake *temp = new snake;
    temp = head->next;    //temp指向 蛇尾 的第一节

    while(temp != NULL){
        /*保存该蛇节的坐标至second*/
        second_x = temp->x;
        second_y = temp->y;


        /*将该a蛇节坐标修改为上一节的坐标first*/
        temp->x = first_x;
        temp->y = first_y;

        /*first是下一趟循环中，蛇节的上一节的坐标*/
        first_x = second_x;
        first_y = second_y;

        temp = temp->next;
    }
}

void MainWindow::eat(){
    if(CURR_DIR == DIR_LEFT && food->x == head->x - 1){
        cout<<"left"<<endl;

        snake *temp = new snake;
        temp->x = food->x;
        temp->y = food->y;
        temp->next = NULL;


    }


}
