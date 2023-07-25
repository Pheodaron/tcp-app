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

  void onConnected();
  void onDisconnected();

private slots:
  void on_m_connectPushButton_clicked();

  void on_m_sendMessageButton_clicked();

private:
  Ui::MainWindow *ui;
  QTcpSocket *m_socket;
  QDataStream out;
  bool isConnected = false;
};
#endif // MAINWINDOW_H
