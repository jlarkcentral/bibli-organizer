#include <QWidget>
#include <QSplitter>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>

#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Taille fentre
    setMinimumWidth(500);
    setMinimumHeight(300);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    QSplitter * splitter = new QSplitter(this);
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    centralwidget->setLayout(mainLayout);
    // Entete fenetre
    setWindowTitle("BiblioApp");

    QLabel * title = new QLabel("");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size : 16px");
    mainLayout->addWidget(title,0,0,1,2);

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    QMenu* menuBiblio = new QMenu("&Biblio");
    QAction * nouveauLivre = new QAction("Nouveau Livre",menuBiblio);
    nouveauLivre->setShortcut(Qt::Key_Space);
    menuBiblio->addAction(nouveauLivre);
    bar->addMenu(menuBiblio);

    // Arbre de gauche
    tree = new QTreeWidget(this);
    tree->header()->hide();

    // Menu contextuel arbre
    contextMenu = new QMenu(tree);
    addDossierAction = new QAction("Ajouter un dossier",contextMenu);
    addLivreAction = new QAction("Ajouter un livre",contextMenu);
    renameAction = new QAction("Renommer",contextMenu);
    QAction * deleteAction = new QAction("Supprimer",contextMenu);
    contextMenu->addAction(renameAction);
    contextMenu->addSeparator();
    contextMenu->addAction(addLivreAction);
    contextMenu->addSeparator();
    contextMenu->addAction(addDossierAction);
    contextMenu->addSeparator();
    contextMenu->addAction(deleteAction);
    contextMenu->addSeparator();
    tree->addAction(renameAction);
    tree->addAction(addLivreAction);
    tree->addAction(addDossierAction);
    tree->addAction(deleteAction);

    QObject::connect(tree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(contextMenuChange(QTreeWidgetItem*)));
    QObject::connect(contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuAction(QAction*)));

    tree->setContextMenuPolicy(Qt::ActionsContextMenu);
    tree->setAcceptDrops(true);
    tree->setDragEnabled(true);
    tree->setDragDropMode(QAbstractItemView::InternalMove);


    // Fiche de droite
    Livre * testLivre = new Livre("");
    testLivre->setAuteur("");
    ficheLivre = new FicheLivre(this,testLivre);

    QObject::connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(changeFicheLivre(QTreeWidgetItem*)));

    splitter->addWidget(tree);
    splitter->addWidget(ficheLivre);

    mainLayout->addWidget(splitter,1,0);

}

void MainWindow::biblioToTree(Dossier * dossier,QTreeWidgetItem * item)
{
    for(int i = 0 ; i < dossier->getDossiers().size() ; i++){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        Dossier * dossierCourant = dossier->getDossiers().at(i);
        newItem->setText(0,QString(dossierCourant->getLabel().c_str()));
        newItem->setData(1,0,1);
        index.push_back(new ItemIndex(dossierCourant,newItem));
        item->addChild(newItem);
        biblioToTree((dossier->getDossiers().at(i)),newItem);
    }
    for(int i = 0 ; i < dossier->getLivres().size() ; i++){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        Livre * livreCourant = dossier->getLivres().at(i);
        newItem->setText(0,QString(livreCourant->getTitre().c_str()));
        newItem->setData(1,0,0);
        newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled);
        index.push_back(new ItemIndex(livreCourant,newItem));
        item->addChild(newItem);
    }
}

QTreeWidget* MainWindow::getTree()
{
    return tree;
}

void MainWindow::setBiblio(Biblio *uneBiblio)
{
    biblio = uneBiblio;
}

Biblio* MainWindow::getBiblio()
{
    return biblio;
}

void MainWindow::setLivreFicheLivre(Livre *unLivre,QTreeWidgetItem * item)
{
    ficheLivre->setTitre(QString(unLivre->getTitre().c_str()));
    ficheLivre->setAuteur(QString(unLivre->getAuteur().c_str()));
    ficheLivre->setNotes(QString(unLivre->getNotes().c_str()));
    ficheLivre->setItemCourant(item);
}

void MainWindow::changeFicheLivre(QTreeWidgetItem * item)
{
    if (item->data(1,0) == 0){
        Livre * livreSelect = livreFromItem(item);
        setLivreFicheLivre(livreSelect,item);
    }
}

void MainWindow::contextMenuAction(QAction *action)
{
    QTreeWidgetItem * item = tree->currentItem();
    QString text = action->text();
    if (item){
        if(item->data(1,0) == 1){
            if(text=="Ajouter un livre"){
                // update arbre
                QTreeWidgetItem * newItem = new QTreeWidgetItem();
                newItem->setText(0,"Nouveau livre (sans titre)");
                newItem->setData(1,0,0);
                item->addChild(newItem);
                // update modele
                Livre * newLivre = new Livre("Sans Titre");
                Dossier * in = dossierFromItem(item);
                in->addLivre(newLivre);
                index.push_back(new ItemIndex(newLivre,newItem));
                // update fiche
                setLivreFicheLivre(newLivre,0);
                ficheLivre->setEditable(true);
            }
            else if(text=="Ajouter un dossier"){
                // update arbre
                QTreeWidgetItem * newItem = new QTreeWidgetItem();
                newItem->setText(0,"Nouveau dossier (sans étiquette)");
                newItem->setData(1,0,1);
                item->addChild(newItem);
                // update modele
                Dossier * newDossier = new Dossier("Sans Titre");
                Dossier * in = dossierFromItem(item);
                in->addDossier(newDossier);
                index.push_back(new ItemIndex(newDossier,newItem));
            }
        }
        if(item->data(1,0) == 0){
            addDossierAction->setDisabled(true);
        }
        if(text=="Supprimer"){
            if (item->data(1,0) == 0){
            }
            else if (item->data(1,0) == 1){
            }
        }
        addDossierAction->setDisabled(false);
    }
}

void MainWindow::contextMenuChange(QTreeWidgetItem *item)
{
    if(item->data(1,0) == 1){
        addDossierAction->setEnabled(true);
        addLivreAction->setEnabled(true);
        renameAction->setEnabled(true);
    }
    if(item->data(1,0) == 0){
        addDossierAction->setEnabled(false);
        addLivreAction->setEnabled(false);
        renameAction->setEnabled(false);
    }
}

Livre* MainWindow::livreFromItem(QTreeWidgetItem *item)
{
    for(int i = 0 ; i < index.size() ; i++){
        ItemIndex * cii = index.at(i);
        if(cii->getTreeItem() == item){
            return cii->getLivre();
        }
    }
    return 0;
}

Dossier* MainWindow::dossierFromItem(QTreeWidgetItem *item)
{
    for(int i = 0 ; i < index.size() ; i++){
        ItemIndex * cii = index.at(i);
        if(cii->getTreeItem() == item){
            return cii->getDossier();
        }
    }
    return 0;
}

QTreeWidgetItem* MainWindow::itemFromDossier(Dossier *unDossier)
{
    for(int i = 0 ; i < index.size() ; i++){
        ItemIndex * cii = index.at(i);
        if(cii->getDossier() == unDossier){
            return cii->getTreeItem();
        }
    }
    return 0;
}

QTreeWidgetItem* MainWindow::itemFromLivre(Livre *unLivre)
{
    for(int i = 0 ; i < index.size() ; i++){
        ItemIndex * cii = index.at(i);
        if(cii->getLivre() == unLivre){
            return cii->getTreeItem();
        }
    }
    return 0;
}

MainWindow::~MainWindow()
{
}
