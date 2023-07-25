#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <src/helpers.h>

int main(int argc, char *argv[]) {

  int port = checkCommandLineArgs(argc, argv);

  QApplication a(argc, argv);
  MainWindow w(port);
  w.show();
  return a.exec();
}
