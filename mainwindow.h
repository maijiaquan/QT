#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QKeyEvent>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()% (x + 1))

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    isPause = false;
    canPlay = true;

    speed = 100;
    /*初始化方向*/
    DIR_RIGHT = 1;
    DIR_LEFT = 2;
    DIR_DOWN = 3;
    DIR_UP =4;
    CURR_DIR = DIR_DOWN;
    snake_dir = DIR_DOWN;

    head = new snake;
    /*食物*/
    food = new snake;
    food->y = 5;
    food->x = 5;
    food->next = NULL;

    /*初始化全局变量*/
    LINE_WIDTH = 15;   //设置线宽
    LINE_NUMBER = 20;   //设置线条数——游戏面板大小

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

    snake *temp = new snake;
    temp = s3;

    /*自定义测试长度*/
    int initialSnake = 6;
    while(initialSnake > 0){
        snake *newsnake = new snake;
        temp->next = newsnake;
        newsnake->x = temp->x + 1;
        newsnake->y = temp->y;
        newsnake->next = NULL;

        temp = temp->next;
        initialSnake --;
    }


    startTimer(speed);  //定时器


    ////////////////////////
    ui->setupUi(this);
    resize(320, 320);
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
        p.drawLine(LINE_WIDTH, LINE_WIDTH + i * LINE_WIDTH, LINE_NUMBER * LINE_WIDTH, LINE_WIDTH + i * LINE_WIDTH);
        p.drawLine(LINE_WIDTH + i * LINE_WIDTH, LINE_WIDTH, LINE_WIDTH + i * LINE_WIDTH, LINE_WIDTH * LINE_NUMBER);
    }


    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    p.setBrush(brush);

    snake * temp = new snake;
    temp = head;

    int i = 20;

    /*遍历链表，画蛇*/
    while(temp != NULL){

        brush.setColor(QColor(0,i,0));
        p.setBrush(brush);
        p.drawRect(temp->x * LINE_WIDTH + LINE_WIDTH, temp->y * LINE_WIDTH + LINE_WIDTH, LINE_WIDTH, LINE_WIDTH);
        if(i <= 250 ){
            i += 5;
        }


        temp = temp->next;
    }

    /*画食物*/
    brush.setColor(QColor(170,4,0));
    p.setBrush(brush);
    p.drawRect(food->x * LINE_WIDTH + LINE_WIDTH, food->y * LINE_WIDTH + LINE_WIDTH, LINE_WIDTH, LINE_WIDTH);

}

/*接收键盘事件，移动蛇头 + 移动蛇尾，重绘*/
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int keyValue = event->key();
    if(keyValue == Qt::Key_Left && snake_dir != DIR_RIGHT){
        CURR_DIR = DIR_LEFT;
    }

    if(keyValue == Qt::Key_Right && snake_dir != DIR_LEFT){
        CURR_DIR = DIR_RIGHT;
    }

    if(keyValue == Qt::Key_Up && snake_dir != DIR_DOWN){
        CURR_DIR = DIR_UP;
    }

    if(keyValue == Qt::Key_Down && snake_dir != DIR_UP){
        CURR_DIR = DIR_DOWN;

    }

    if(keyValue == Qt::Key_0){
        isPause = true;
    }

    if(keyValue == Qt::Key_1){
        isPause = false;
    }

    if(keyValue == Qt::Key_2){
        canPlay = true;
    }

    // cout<<head->x<<" "<<head->y<<endl;
    update();
}

/*蛇移动函数，以speed的时间间隔调用*/
void MainWindow::moveSnake(){
    if(!isPause && canPlay){
        if(isHitWall() != -1){
            canPlay = false;
        }
        else if(isBodyAhead() != -1){
            cout<<"isBodyAhead() =="<<isBodyAhead()<<endl;
            canPlay = false;
        }
        else{
            snake_dir = CURR_DIR;
            if(snake_dir == DIR_DOWN){
                if(foodAhead() == DIR_DOWN){   //情景1：进食
                    cout<<foodAhead()<<"DIR_DOWN"<<endl;
                    eat();
                }
                else{                         //情景2：正常移动
                    head->y += 1;
                    moveTail(DIR_DOWN);
                  //  snake_dir = DIR_DOWN;
                }
            }

            if(snake_dir == DIR_LEFT){
                if(foodAhead() == DIR_LEFT){
                    cout<<foodAhead()<<"DIR_LEFT"<<endl;
                    eat();
                }
                else{
                    head->x -= 1;     //要写成函数走一步，
                    moveTail(DIR_LEFT);
                  //  snake_dir = DIR_LEFT;
                }
            }

            if(snake_dir == DIR_RIGHT){
                if(foodAhead() == DIR_RIGHT){
                    cout<<foodAhead()<<"DIR_RIGHT"<<endl;
                    eat();
                }
                else{
                    head->x += 1;
                    moveTail(DIR_RIGHT);
                 //   snake_dir = DIR_RIGHT;

                }
            }

            if(snake_dir == DIR_UP){
                if(foodAhead() == DIR_UP){
                    eat();
                    cout<<foodAhead()<<"DIR_UP"<<endl;
                }
                else{
                    head->y -= 1;
                    moveTail(DIR_UP);
                  //  snake_dir = DIR_UP;
                }
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



/*判断是否游戏结束*/
bool MainWindow::isGameover(){
    return false;
}

/*判断是否到达墙边，返回-1表示还没撞墙*/
int MainWindow::isHitWall(){
    if(head->y == 0 && CURR_DIR == DIR_UP){
        return DIR_UP;
    }
    else if(head->y == LINE_NUMBER - 2 && CURR_DIR == DIR_DOWN){
        return DIR_DOWN;
    }
    else if(head->x == 0 && CURR_DIR == DIR_LEFT){
        return DIR_LEFT;
    }
    else if(head->x == LINE_NUMBER - 2 && CURR_DIR == DIR_RIGHT){
        return DIR_RIGHT;
    }
    else{
        return -1;
    }
}

/*判断食物是否在前方，返回方向值，否则返回-1*/
int MainWindow::foodAhead(){
    if(CURR_DIR == DIR_LEFT && food->x == head->x - 1 && food->y == head->y){
        return DIR_LEFT;

    }
    else if(CURR_DIR == DIR_RIGHT && food->x == head->x + 1 && food->y == head->y){
        return DIR_RIGHT;

    }

    else if(CURR_DIR == DIR_UP && food->y == head->y - 1 && food->x == head->x){
        return DIR_UP;

    }

    else if(CURR_DIR == DIR_DOWN && food->y == head->y + 1 && food->x == head->x){
        return DIR_DOWN;

    }
    else return -1;
}

/*进食后变长*/
void MainWindow::eat(){
    cout<<"eat"<<endl;
    snake *temp = new snake;
    temp->x = food->x;
    temp->y = food->y;
    temp->next = head;
    head = temp;

    //cout<<"准备resetfood"<<endl;
    resetFood();
    cout<<"food-----"<<food->x<<" "<<food->y<<endl;
}


/*定时器事件*/
void MainWindow::timerEvent(QTimerEvent *t)//定时器时间
{
    moveSnake();
    update();
    //cout<<"score = "<<score()<<endl;
}

/*显示蛇的长度（分数）*/
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

/*重置食物坐标*/
void MainWindow::resetFood(){

    int x = 0;
    int y = 0;
    bool isOverlap = false;


    snake *temp = new snake;
    temp = head;
    int n = score();
    int **p = new int* [n];
    for(int i = 0; i < n ; i++){
        p[i] = new int [2];
    }

    /*填充数组*/
    int i = 0;
    while(temp != NULL){
        //cout<<i<<temp->x<<" "<<temp->y<<endl;
        p[i][0] = temp->x;
        p[i][1] = temp->y;
        // cout<<i<<p[i][0]<<" "<<p[i][1]<<endl;
        i++;
        temp = temp->next;
    }

    /*只要重叠*/
    do{
        isOverlap = false;

        //srand((int)time(0));
        x = random(LINE_NUMBER - 2);
        //srand((int)time(0));
        y = random(LINE_NUMBER - 2);

        for(int i = 0; i < n ; i++){
            if(p[i][0] == x && p[i][1] == y){
                isOverlap = true;
                break;
            }
        }
    }while(isOverlap == true);

    food->x = x;
    food->y = y;
}


/*若身体在前方XXXXX，若不在前方，可以继续游戏，返回-1*/
int MainWindow::isBodyAhead(){
    snake *temp = new snake;
    temp = head;
    int n = score();
    int **p = new int* [n];
    for(int i = 0; i < n ; i++){
        p[i] = new int [2];
    }

    /*填充数组*/
    int i = 0;
    while(temp != NULL){
        p[i][0] = temp->x;
        p[i][1] = temp->y;
        i++;
        temp = temp->next;
    }

    /*遍历数组*/
    for(int i = 0; i < n; i++){
        bool isRight = head->y == p[i][1] && head->x + 1 == p[i][0] && CURR_DIR == DIR_RIGHT;
        bool isLeft = head->y == p[i][1] && head->x - 1 == p[i][0] && CURR_DIR == DIR_LEFT;
        bool isUp = head->x == p[i][0] && head->y - 1 == p[i][1] && CURR_DIR== DIR_UP;
        bool isDown = head->x == p[i][0] && head->y + 1 == p[i][1] && CURR_DIR== DIR_DOWN;
        if(isRight){
            return DIR_RIGHT;
        }
        else if(isLeft){
            return DIR_LEFT;
        }
        else if(isUp){
            return DIR_UP;
        }
        else if(isDown){
            return DIR_DOWN;
        }
    }
    return -1;
}
