#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
//    void onReadyRead();

private slots:
    void on_m_connectPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QTcpSocket*> m_sockets;
};
#endif // MAINWINDOW_H
