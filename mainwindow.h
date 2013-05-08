#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>
#include <QListWidget>
#include <QStatusBar>
#include <QMenu>
#include <QAction>

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
    QTreeWidget* getTree();
    void setLivreFicheLivre(Livre * unLivre);
    void setBiblio(Biblio * uneBiblio);
    Biblio* getBiblio();
    Livre* livreFromItem(QTreeWidgetItem* item);
    Dossier* dossierFromItem(QTreeWidgetItem* item);
    QTreeWidgetItem* itemFromLivre(Livre* unLivre);
    QTreeWidgetItem* itemFromDossier(Dossier* unDossier);

    ~MainWindow();

signals:

public slots:
    void changeFicheLivre(QTreeWidgetItem *item);
    void contextMenuAction(QAction *action);
    void contextMenuChange(QTreeWidgetItem *item);
    
private:
    QGridLayout * mainLayout;
    QTreeWidget * tree; // ou listes
    FicheLivre * ficheLivre;
    vector<ItemIndex*> index;
    QMenu * contextMenu;
    QAction * addDossierAction;
    QAction * addLivreAction;
    QAction * renameAction;
    Biblio * biblio;
};

#endif // MAINWINDOW_H
