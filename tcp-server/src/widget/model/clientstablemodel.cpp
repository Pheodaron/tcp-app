#include "clientstablemodel.h"

ClientsTableModel::ClientsTableModel(QTcpServer *server, QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant ClientsTableModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const {
  if (role == Qt::DisplayRole) {
    if (orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return QString("Ip-адресс");
      case 1:
        return QString("Порт");
      case 2:
        return QString("Последнее сообщение");
      }
    }
  }
  return QVariant();
}

int ClientsTableModel::rowCount(const QModelIndex &parent) const {
  return count;
}

int ClientsTableModel::columnCount(const QModelIndex &parent) const {
  return 3;
}

QVariant ClientsTableModel::data(const QModelIndex &index, int role) const {
  QVariant variant;
  QPair<QTcpSocket *, QString> row =
      m_data.value(m_data.keys().at(index.row()));
  const int column = index.column();
  if (role == Qt::DisplayRole || role == Qt::EditRole) {
    switch (column) {
    case 0: {
      variant = row.first->peerAddress().toString();
      break;
    }
    case 1: {
      variant = row.first->peerPort();
      break;
    }
    case 2: {
      variant = row.second;
      break;
    }
    }
  }
  return variant;
}

void ClientsTableModel::addClient(QTcpSocket *socket) {
  beginResetModel();
  m_data.insert(socket->peerPort(),
                QPair<QTcpSocket *, QString>(socket, QString()));
  count++;
  endResetModel();
}

void ClientsTableModel::deleteClient(int descriptor) {
  beginResetModel();
  m_data.remove(descriptor);
  count--;
  endResetModel();
}

void ClientsTableModel::disconnectClient(int descriptor) {
  QTcpSocket *socket = m_data.value(descriptor).first;
  socket->close();
}

void ClientsTableModel::saveMessage(int port, QString message) {
  QPair<QTcpSocket *, QString> value = m_data.value(port);
  value.second = message;
  beginResetModel();
  m_data.insert(port, value);
  endResetModel();
}

int ClientsTableModel::getDescriptorByRow(int row) {
  return m_data.keys().at(row);
}

bool ClientsTableModel::containsSocket(int descriptor) {
  return m_data.contains(descriptor);
}
