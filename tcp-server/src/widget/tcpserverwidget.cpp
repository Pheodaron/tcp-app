#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TcpServerWidget), m_server(this),
      m_model(&m_server, this) {
  ui->setupUi(this);

  connect(&m_server, &QTcpServer::newConnection, this,
          &TcpServerWidget::onNewConnection);
  int port = 4242;
  ui->m_currentPortValueLabel->setText(QString::number(port));
  if (!m_server.listen(QHostAddress::AnyIPv4, port)) {
    qDebug() << QString("Unable to start the server: %1.")
                    .arg(m_server.errorString());
  } else {
    qDebug() << "Сервер запущен!";
  }

  ui->m_clientsTableView->setModel(&m_model);
  ui->m_clientsTableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->m_clientsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->m_clientsTableView->horizontalHeader()->setHighlightSections(false);
  ui->m_clientsTableView->horizontalHeader()->setStretchLastSection(true);
  ui->m_clientsTableView->verticalHeader()->hide();
  ui->m_clientsTableView->setColumnWidth(0, 200);
  ui->m_clientsTableView->setColumnWidth(1, 100);
  ui->m_clientsTableView->setMinimumWidth(500);

  ui->m_clientsTableView->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->m_clientsTableView, &QTableView::customContextMenuRequested, this,
          &TcpServerWidget::onCustomMenuRequested);
}

TcpServerWidget::~TcpServerWidget() { delete ui; }

void TcpServerWidget::onNewConnection() {
  QTcpSocket *clientSocket = m_server.nextPendingConnection();
  m_model.addClient(clientSocket);

  connect(clientSocket, &QTcpSocket::stateChanged, this,
          &TcpServerWidget::onSocketStateChanged);

  connect(clientSocket, &QTcpSocket::readyRead, [&]() {
    QByteArray buffer;
    QDataStream socketStream(clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_13);

    socketStream.startTransaction();
    socketStream >> buffer;

    if (!socketStream.commitTransaction()) {
      m_model.saveMessage(clientSocket->peerPort(),
                          QString::fromStdString(buffer.toStdString()));
    }

    //    QByteArray data = clientSocket->readAll();
    //    m_model.saveMessage(clientSocket->peerPort(), QString(data));
  });
}

void TcpServerWidget::onSocketStateChanged(
    QAbstractSocket::SocketState socketState) {
  if (socketState == QAbstractSocket::ClosingState ||
      socketState == QAbstractSocket::UnconnectedState) {
    QTcpSocket *sender = static_cast<QTcpSocket *>(QObject::sender());
    if (m_model.containsSocket(sender->peerPort())) {
      m_model.deleteClient(sender->peerPort());
    }
  }
}

void TcpServerWidget::onCustomMenuRequested(QPoint pos) {
  int row = ui->m_clientsTableView->indexAt(pos).row();
  QMenu *menu = new QMenu(this);

  QAction *disconnectClient = new QAction("Отключить", this);
  connect(disconnectClient, &QAction::triggered, [this, row]() {
    int descriptor = m_model.getDescriptorByRow(row);
    m_model.disconnectClient(descriptor);
  });
  menu->addAction(disconnectClient);
  menu->popup(ui->m_clientsTableView->viewport()->mapToGlobal(pos));
}
