#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("BookManagerQt");
    application.setOrganizationName("BookManagerExample");
    application.setStyle(QStyleFactory::create("Fusion"));

    MainWindow window;
    window.show();
    return application.exec();
}
