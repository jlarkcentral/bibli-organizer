#include <QtGui/QApplication>

#include <QTextCodec>

#include "mainwindow.h"
#include "biblio.h"

using namespace std;

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

    Biblio * biblio = new Biblio();
    biblio->loadXml("./save.xml");

    QApplication a(argc, argv);
    MainWindow w;
    w.setBiblio(biblio);
    w.biblioToTree(w.getBiblio()->getDossierPrincipal(),w.getTree()->invisibleRootItem());

    w.show();
    
    return a.exec();
}
