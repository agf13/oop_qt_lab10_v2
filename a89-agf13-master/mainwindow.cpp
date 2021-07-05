#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    toAdmin = new QPushButton();
    toClient = new QPushButton();

    horizontal = new QHBoxLayout(this);
    vertical = new QVBoxLayout();

    vertical->addWidget(toAdmin);
    vertical->addWidget(toClient);

    horizontal->addItem(vertical);
}

MainWindow::~MainWindow()
{
    delete ui;
}

