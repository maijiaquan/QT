#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //////////////////////////////////////

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);


    void moveTail(int a);  //移动蛇尾
    int foodAhead();  //判断食物是否在前方
    void moveSnake();
    void eat();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;

    struct snake{
        int x;
        int y;
        snake *next;
    };
    snake *head;
    snake *food;

    int LINE_WIDTH;

    int TOP_LEFT_X;
    int TOP_LEFT_Y;

    /*四个方向*/
    int DIR_UP;
    int DIR_DOWN;
    int DIR_LEFT;
    int DIR_RIGHT;
    int CURR_DIR;
};

#endif // MAINWINDOW_H
