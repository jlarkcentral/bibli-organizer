#include <QtGui/QApplication>

#include "mainwindow.h"
#include "biblio.h"

using namespace std;

int main(int argc, char *argv[])
{
    Biblio biblio;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
