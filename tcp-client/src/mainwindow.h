#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHostAddress>
#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void onConnected(); // поменять состояние формы при отключении
  void onDisconnected(); // поменять состояние формы при подключении

private slots:
  void on_m_connectPushButton_clicked(); // подключение / отключение

  void on_m_sendMessageButton_clicked(); // отправка данных на сервер

private:
  Ui::MainWindow *ui;
  QTcpSocket *m_socket; // ссылка на текущий сокет
  bool isConnected = false; // флаг состояния подключения
};
#endif // MAINWINDOW_H
