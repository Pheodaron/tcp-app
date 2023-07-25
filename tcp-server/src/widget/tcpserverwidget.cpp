#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"

TcpServerWidget::TcpServerWidget(int port, QWidget *parent)
    : QWidget(parent), ui(new Ui::TcpServerWidget), m_server(this),
      m_model(&m_server, this) {
  ui->setupUi(this);

  if (!m_server.listen(QHostAddress::AnyIPv4, port)) {
    qDebug() << QString("Unable to start the server: %1.")
                    .arg(m_server.errorString());
    exit(0);
  } else {
    qDebug() << "Сервер запущен!";
  }

  connect(&m_server, &QTcpServer::newConnection, this,
          &TcpServerWidget::onNewConnection);

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
  ui->m_currentPortValueLabel->setText(QString::number(port));
  connect(ui->m_clientsTableView, &QTableView::customContextMenuRequested, this,
          &TcpServerWidget::onCustomMenuRequested);
}

TcpServerWidget::~TcpServerWidget() { delete ui; }

void TcpServerWidget::onNewConnection() {
  QTcpSocket *clientSocket = m_server.nextPendingConnection();
  m_model.addClient(clientSocket);

  connect(clientSocket, &QTcpSocket::readyRead,
          [this, clientSocket]() { onReadyRead(clientSocket); });

  connect(clientSocket, &QTcpSocket::disconnected, [this, clientSocket]() {
    m_model.deleteClient(clientSocket->socketDescriptor());
  });
}

void TcpServerWidget::onReadyRead(QTcpSocket *clientSocket) {
  QByteArray buffer;
  QDataStream dataStream(clientSocket);
  dataStream.setVersion(QDataStream::Qt_5_12);

  dataStream.startTransaction();
  dataStream >> buffer;

  if (!dataStream.commitTransaction()) {
    qDebug() << "Транзакция не закрыта...";
    return;
  }
  QString message = QString::fromStdString(buffer.toStdString());
  m_model.saveMessage(clientSocket->socketDescriptor(), message);
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
