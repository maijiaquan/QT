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
private:
    Ui::MainWindow *ui;
    int a[15][15];

    struct snake{
        int x;
        int y;
    }s1;
};

#endif // MAINWINDOW_H
