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

#include "fichelivre.h"
#include "dossier.h"
#include "itemindex.h"
#include "biblio.h"

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
    Livre* livreFromItem(QTreeWidgetItem* item);
    Dossier* dossierFromItem(QTreeWidgetItem* item);
    QTreeWidgetItem* itemFromLivre(Livre* unLivre);
    QTreeWidgetItem* itemFromDossier(Dossier* unDossier);
    void updateStatusBar();

    ~MainWindow();

signals:
    void appClosed();
    void dragDropSignal();

public slots:
    void changeFicheLivre(QTreeWidgetItem *item);
    void contextMenuAction(QAction *action);
    void contextMenuChange(QTreeWidgetItem *item);
    void buttonEditChange(bool mode);
    void buttonEditEnable(QTreeWidgetItem *item);
    void deleteItemCourant();
    void save();
    void setFicheLabelText(QString qs);
    void menuAction(QAction* action);
    void secureDelete(bool secure);
    
private:
    QGridLayout * mainLayout;
    QTreeWidget * tree; // ou listes
    FicheLivre * ficheLivre;
    vector<ItemIndex*> index;
    QMenu * contextMenu;
    QAction * addDossierAction;
    QAction * addLivreAction;
    QAction * renameAction;
    QAction * deleteAction;
    Biblio * biblio;
    QPushButton * buttonEdit;
    int nbLivres;
    QTreeWidgetItem *itemCourant;
    QLabel * ficheLabel;
    bool securityOnDelete;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
