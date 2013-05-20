#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>
#include <QListWidget>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QCloseEvent>
#include <QInputDialog>
#include <QSplitter>

#include <algorithm>

#include "fichelivre.h"
#include "dossier.h"
#include "itemindex.h"
#include "biblio.h"
#include "pilealire.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    void biblioToTree(Dossier *dossier, QTreeWidgetItem *item);
    void treeToBiblio(QTreeWidgetItem *itemCourant, Dossier *dossierCourant);
    QTreeWidget* getTree();
    void setLivreFicheLivre(Livre * unLivre, QTreeWidgetItem *item);
    void setBiblio(Biblio * uneBiblio);
    Biblio* getBiblio();
    void updateStatusBar();
    void loadSettings();
    void saveSettings();

    ~MainWindow();

signals:
    void appClosed();
    void dragDropSignal();

public slots:
    void doubleClickItemSlot(QTreeWidgetItem *item);
    void contextMenuAction(QAction *action);
    void contextMenuChange(QTreeWidgetItem *item);
    void buttonEditChange(bool mode);
    void buttonEditEnable(QTreeWidgetItem *item);
    void deleteItemCourant();
    void save();
    void setFicheLabelText(QString qs);
    void menuAction(QAction* action);
    void secureDelete(bool secure);
    void updateTreeOrder(QTreeWidgetItem *item, int col);
    void updateNbLivresLus(bool b);
    void changePAL(QTreeWidgetItem *item, bool aLire);
    void changePALerase(QTreeWidgetItem *item, bool lu);
    void updatePAL();
    void livrePlusALire(QTreeWidgetItem *item);
    void exportToTxt();
    
private:
    QGridLayout * mainLayout;
    QSplitter * splitter;
    QTreeWidget * tree;
    FicheLivre * ficheLivre;
    PileALire * pilealire;
    map<QTreeWidgetItem*,Dossier*> dossierMap;
    map<QTreeWidgetItem*,Livre*> livreMap;
    map<Livre*,QTreeWidgetItem*> livresALireMap;
    QMenu * contextMenu;
    QAction * addDossierAction;
    QAction * addLivreAction;
    QAction * renameAction;
    QAction * deleteAction;
    QAction * addToPALAction;
    Biblio * biblio;
    QPushButton * buttonEdit;
    int nbLivres;
    int nbLivresLus;
    QTreeWidgetItem *itemCourant;
    QLabel * ficheLabel;
    bool securityOnDelete;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
