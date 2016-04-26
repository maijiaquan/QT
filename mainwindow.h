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

    void moveTail(int a);
private:
    Ui::MainWindow *ui;


    struct snake{
        int x;
        int y;
        snake *next;
    }*head;

    int LINE_WIDTH;

    int TOP_LEFT_X;
    int TOP_LEFT_Y;

    //    int first_x;
//    int first_y;
//    int second_x;
//    int second_y;
};

#endif // MAINWINDOW_H
