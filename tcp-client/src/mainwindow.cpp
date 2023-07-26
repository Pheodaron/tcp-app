#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_socket(new QTcpSocket(this)) {
  ui->setupUi(this);
  connect(m_socket, &QTcpSocket::disconnected, [this]() { onConnected(); });

  ui->m_portLineEdit->setText("4242");
  ui->m_sendMessageButton->setEnabled(false);
  ui->m_messageLineEdit->setEnabled(false);
}

MainWindow::~MainWindow() {
    // закрыть подключение при выходе из программы
    m_socket->close();
    m_socket->deleteLater();
    delete ui;
}

void MainWindow::on_m_connectPushButton_clicked() {
  if (isConnected) {
    onConnected();
  } else {
    int port = ui->m_portLineEdit->text().toInt();
    m_socket->connectToHost(QHostAddress("127.0.0.1"), port);
    if (m_socket->waitForConnected()) {
      onDisconnected();
    } else {
      std::cout << "Проблемы при подключении" << std::endl;
    }
  }
}

void MainWindow::onConnected() {
  m_socket->abort();
  ui->m_connectPushButton->setText("Подключиться");
  ui->m_sendMessageButton->setEnabled(false);
  ui->m_messageLineEdit->setEnabled(false);
  isConnected = false;
}

void MainWindow::onDisconnected() {
  isConnected = true;
  ui->m_connectPushButton->setText("Отключиться");
  ui->m_sendMessageButton->setEnabled(true);
  ui->m_messageLineEdit->setEnabled(true);
}

void MainWindow::on_m_sendMessageButton_clicked() {
  if (m_socket->isOpen()) {
    QString str = ui->m_messageLineEdit->text();

    QDataStream socketStream(m_socket);
    socketStream.setVersion(QDataStream::Qt_5_12);

    QByteArray message = str.toUtf8();

    socketStream << message;

    ui->m_messageLineEdit->clear();
  } else {
    QMessageBox::critical(this, "tcp-client", "Сокет не открыт");
  }
}
