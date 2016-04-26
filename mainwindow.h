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
    void eat();  //吃食物变长

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


};

#endif // MAINWINDOW_H
