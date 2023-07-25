#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <QRegExp>

int checkCommandLineArgs(int argc, char *argv[]) {
    int port = 4242;

    if (argc == 2) {
      QRegExp re("\\d*");
      if (!re.exactMatch(argv[1])) {
        std::cout << "Ошибка: не верно указан порт" << std::endl;
        exit(0);
      }
      port = QString(argv[1]).toInt();
      if (port < 1024 || port > 65535) {
        std::cout << "Ошибка: не верно указан порт" << std::endl;
        exit(0);
      }
    }

    return port;
}

#endif // HELPERS_H
