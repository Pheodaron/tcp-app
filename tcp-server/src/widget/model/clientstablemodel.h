#ifndef CLIENTSTABLEMODEL_H
#define CLIENTSTABLEMODEL_H

#include <QAbstractTableModel>
#include <QTcpServer>
#include <src/widget/entity/client.h>

class ClientsTableModel : public QAbstractTableModel {
  Q_OBJECT

public:
  explicit ClientsTableModel(QTcpServer *server, QObject *parent = nullptr);

  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void addClient(QTcpSocket *socket);
  void deleteClient(int descriptor);
  void disconnectClient(int descriptor);
  int getDescriptorByRow(int row);
  void saveMessage(int port, QString message);
  bool containsSocket(int descriptor);

private:
  QMap<int, QPair<QTcpSocket *, QString>> m_data;
  int count = 0;
};

#endif // CLIENTSTABLEMODEL_H
