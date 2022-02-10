#include "GUI/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // Setup the application.
    QApplication a(argc, argv);

    /// Create the window instance.
    MainWindow window;
    window.show();

    // Execute the application.
    return a.exec();
}
