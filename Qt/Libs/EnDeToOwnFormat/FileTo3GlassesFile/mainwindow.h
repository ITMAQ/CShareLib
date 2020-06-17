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

public slots:
    void onEncodeFile(bool b);
    void onDecodeFile(bool b);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
