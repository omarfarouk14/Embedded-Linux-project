#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window("192.168.7.1", 8080);
    window.setFixedSize(800,600);
    //window.setWindowFlags(window.windowFlags() & ~Qt::WindowMaximizeButtonHint);
    window.show();
    return app.exec();
}
