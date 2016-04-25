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

    void moveTail();
private:
    Ui::MainWindow *ui;

    struct snake{
        int x;
        int y;
        snake *next;
    }*head;
};

#endif // MAINWINDOW_H
