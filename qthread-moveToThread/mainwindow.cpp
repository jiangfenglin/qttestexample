/*
 * 1. 由于my调用了movetothread函数，那么它所有的槽函数都是执行在新开辟的线程里面。
 *
 * 2. 如果去掉moveToThread函数，那么所有的函数都将执行在gui线程里面。
 *
 * 3. 在connect的时候可以将Qt::QueuedConnection修改为Qt::DirectConnection，
 *    这样所有的槽函数也将在主线程里面执行。
 *
 * 4. 如果connect的时候连接的是this的onXXXXXX槽函数再来调用的my的槽函数的话，
 *    那么这些槽函数也将执行在onXXXXX槽函数所在的线程，这里是主线程。
 *
 *
 * 5. 在使用线程的时候，可以将一个类派生自QObject，然后实现所有的signal/slot，
 *    然后通过调用movetothread函数来使他们执行在新的线程里面，而不是每次都要重新派生QThread，
 *    并且派生QThread函数的另外一个不好的地方是只有run函数内部的代码才会执行在新线程里面，
 *    相比起来，派生QObject并使用movetothread函数更具有灵活性。
 *
 */


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    my = new MyObject;
    firstButton = new QPushButton(tr("first"), 0);
    secondButton = new QPushButton(tr("second"), 0);
    threeButton = new QPushButton(tr("three"), 0);
    selfButton = new QPushButton(tr("self"), 0);
    exitButton = new QPushButton(tr("exit"), 0);

    connect(firstButton, SIGNAL(clicked()), my, SLOT(first()), Qt::QueuedConnection);
    connect(secondButton, SIGNAL(clicked()), my, SLOT(second()), Qt::QueuedConnection);
    connect(threeButton, SIGNAL(clicked()), my, SLOT(three()), Qt::QueuedConnection);
    connect(selfButton, SIGNAL(clicked()), this, SLOT(onSelfPushed()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(onExitPushed()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(firstButton);
    layout->addWidget(secondButton);
    layout->addWidget(threeButton);
    layout->addWidget(selfButton);
    layout->addWidget(exitButton);

    QWidget *p = new QWidget;
    p->setLayout(layout);

    QThread *thread = new QThread;
    my->moveToThread(thread);

    thread->start();
    connect(thread, SIGNAL(started()), my, SLOT(first()));

    setCentralWidget(p);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onFirstPushed() {
    my->first();
}

void MainWindow::onSecondPushed() {
    my->second();
}

void MainWindow::onThreePushed() {
    my->three();
}

void MainWindow::onSelfPushed() {
    qDebug() << QThread::currentThreadId();
}

void MainWindow::onExitPushed() {
    close();
}
