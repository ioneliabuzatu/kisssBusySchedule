#include <QApplication>
#include "window.h"

using namespace std;


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    Gui window;
    window.resize(1000, 700);
    window.show();
    return app.exec();
}