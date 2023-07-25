#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int port, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  TcpServerWidget *tcpServerWidget =
      new TcpServerWidget(port, ui->centralwidget);
  ui->verticalLayout->addWidget(tcpServerWidget);
}

MainWindow::~MainWindow() { delete ui; }
