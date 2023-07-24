#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_portLineEdit->setText("4242");
//    int port = ui->m_portLineEdit->text().toInt();
//    m_socket.connectToHost(QHostAddress("127.0.0.1"), port);
//    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::onReadyRead()
//{
//    QByteArray datas = m_socket.readAll();
//    qDebug() << datas;
//    m_socket.write(QByteArray("ok !\n"));
//}

void MainWindow::on_m_connectPushButton_clicked()
{
    QTcpSocket *socket = new QTcpSocket(this);
    int port = ui->m_portLineEdit->text().toInt();
    socket->connectToHost(QHostAddress("127.0.0.1"), port);
    m_sockets.append(socket);
//    connect(socket, &QTcpSocket::readyRead, this, );
}
