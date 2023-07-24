#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QHostAddress>
#include <QMenu>
#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <src/widget/model/clientstablemodel.h>

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget {
  Q_OBJECT

public:
  explicit TcpServerWidget(QWidget *parent = nullptr);
  ~TcpServerWidget();

public slots:
  //    void onReadyRead();
  void onSocketStateChanged(QAbstractSocket::SocketState socketState);
  void onNewConnection();
  void onCustomMenuRequested(QPoint pos);

private:
  Ui::TcpServerWidget *ui;
  QTcpServer m_server;
  ClientsTableModel m_model;
};

#endif // TCPSERVERWIDGET_H
