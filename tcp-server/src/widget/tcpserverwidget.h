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
  explicit TcpServerWidget(int port, QWidget *parent = nullptr);
  ~TcpServerWidget();

public slots:
  void onNewConnection(); // слот обрабатывающий новое подключение
  void onCustomMenuRequested(QPoint pos); // слот обрабатывающий вызов контекстного меню
  void onReadyRead(QTcpSocket *clientSocket); // слот обрабатывающий сообщения от клиентов

private:
  Ui::TcpServerWidget *ui;
  QTcpServer *m_server; // ссылка на текущий tcp - сервер
  ClientsTableModel m_model; // модель данных таблицы клиентов
};

#endif // TCPSERVERWIDGET_H
