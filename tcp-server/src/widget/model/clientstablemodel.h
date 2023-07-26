#ifndef CLIENTSTABLEMODEL_H
#define CLIENTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QTcpServer>
#include <src/widget/entity/client.h>

class ClientsTableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit ClientsTableModel(QTcpServer *server, QObject *parent = nullptr);
  ~ClientsTableModel();

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addClient(QTcpSocket *socket); // добавить клиента
  void deleteClient(int descriptor); // удалить клиента
  void disconnectClient(int descriptor); // отключить клиента
  int getDescriptorByRow(int row); // получить дескриптор по строке
  void saveMessage(int descriptor, QString message); // сохранить новое сообщение
  bool containsSocket(int descriptor); // проверить есть ли такой сокет по дескриптору

private:
  QMap<int, QPair<QTcpSocket *, QString>> m_data; // мапа которая хранит дескриптор против пары <Ссылка на tcp сокет, последнее сообщение>
  int count = 0;
};

#endif // CLIENTSTABLEMODEL_H
