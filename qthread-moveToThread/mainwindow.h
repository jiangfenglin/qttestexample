#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MyObject : public QObject {
    Q_OBJECT
public:
    MyObject() {}
    ~MyObject() {}

public slots:
    void first() {
        qDebug() << QThread::currentThreadId();
    }
    void second() {
        qDebug() << QThread::currentThreadId();
    }
    void three() {
        qDebug() << QThread::currentThreadId();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onSecondPushed();
    void onFirstPushed();
    void onThreePushed();
    void onSelfPushed();
    void onExitPushed();

private:
    MyObject *my;
    QPushButton *firstButton;
    QPushButton *secondButton;
    QPushButton *threeButton;
    QPushButton *selfButton;
    QPushButton *exitButton;
};


#endif // MAINWINDOW_H
