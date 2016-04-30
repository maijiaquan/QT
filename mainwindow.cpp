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
    isPause = false;

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
    LINE_WIDTH = 20;   //设置线宽
    LINE_NUMBER = 50;

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

    startTimer(200);  //定时器


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
    for (int i = 0; i < LINE_NUMBER; i++)
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

/*接收键盘事件，移动蛇头 + 移动蛇尾，重绘*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if(keyValue == Qt::Key_Left ){
        CURR_DIR = DIR_LEFT;
    }

    if(keyValue == Qt::Key_Right){
        CURR_DIR = DIR_RIGHT;
    }

    if(keyValue == Qt::Key_Up){
        CURR_DIR = DIR_UP;
    }

    if(keyValue == Qt::Key_Down){
        CURR_DIR = DIR_DOWN;

    }

    if(keyValue == Qt::Key_0){
        isPause = true;
    }

    if(keyValue == Qt::Key_1){
        isPause = false;
    }

    cout<<head->x<<" "<<head->y<<endl;
    update();
}

void MainWindow::moveSnake(){
    if(!isPause){
        if(CURR_DIR == DIR_DOWN){
            if(foodAhead() == DIR_DOWN){
                cout<<foodAhead()<<"DIR_DOWN"<<endl;
                eat();
            }
            else{
                head->y += 1;
                moveTail(DIR_DOWN);
            }
        }

        if(CURR_DIR == DIR_LEFT){
            if(foodAhead() == DIR_LEFT){
                cout<<foodAhead()<<"DIR_LEFT"<<endl;
                eat();
            }
            else{
                head->x -= 1;     //要写成函数走一步，
                moveTail(DIR_LEFT);
            }
        }

        if(CURR_DIR == DIR_RIGHT){
            if(foodAhead() == DIR_RIGHT){
                cout<<foodAhead()<<"DIR_RIGHT"<<endl;
                eat();
            }
            else{
                head->x += 1;
                moveTail(DIR_RIGHT);
            }
        }

        if(CURR_DIR == DIR_UP){
            if(foodAhead() == DIR_UP){
                eat();
                cout<<foodAhead()<<"DIR_UP"<<endl;
            }
            else{
                head->y -= 1;
                moveTail(DIR_UP);
            }
        }
    }



}

/*移动蛇的尾部*/
void MainWindow::moveTail(int direction){

    /*first用于保存蛇头移动前的坐标*/
    int first_x;
    int first_y;

    if(direction == DIR_LEFT){   //右
        first_x = head->x + 1;
        first_y = head->y;
    }

    if(direction == DIR_RIGHT){   //左
        first_x = head->x - 1;
        first_y = head->y;
    }

    if(direction == DIR_UP){   //上
        first_x = head->x;
        first_y = head->y + 1;
    }

    if(direction == DIR_DOWN){   //
        first_x = head->x;
        first_y = head->y - 1;
    }

    int second_x;
    int second_y;

    snake *temp = new snake; //temp相当于一个游标，指向蛇尾从头到尾的每一节
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

int MainWindow::foodAhead(){
    if(CURR_DIR == DIR_LEFT && food->x == head->x - 1 && food->y == head->y){
        // cout<<"left"<<endl;
        return DIR_LEFT;

        //        snake *temp = new snake;
        //        temp->x = food->x;
        //        temp->y = food->y;
        //        temp->next = NULL;
    }
    else if(CURR_DIR == DIR_RIGHT && food->x == head->x + 1 && food->y == head->y){
        // cout<<"right"<<endl;
        return DIR_RIGHT;

    }

    else if(CURR_DIR == DIR_UP && food->y == head->y - 1 && food->x == head->x){
        //   cout<<"up"<<endl;
        return DIR_UP;

    }

    else if(CURR_DIR == DIR_DOWN && food->y == head->y + 1 && food->x == head->x){
        //  cout<<"down"<<endl;
        return DIR_DOWN;

    }
    else return -1;
}


void MainWindow::eat(){
    cout<<"eat"<<endl;
    snake *temp = new snake;
    temp->x = food->x;
    temp->y = food->y;
    temp->next = head;
    head = temp;
}


void MainWindow::timerEvent(QTimerEvent *t)//定时器时间
{
    moveSnake();
    update();
    cout<<"score = "<<score()<<endl;
}

int MainWindow::score(){
    snake *temp = new snake;
    temp = head;
    int i = 0;
    while(temp != NULL){
        i++;
        temp = temp->next;
    }
    return i;
}
