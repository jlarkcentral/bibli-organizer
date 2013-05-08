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

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    QMenu* menuBiblio = new QMenu("&Biblio");
    QAction * nouveauLivre = new QAction("Nouveau Livre",menuBiblio);
    nouveauLivre->setShortcut(Qt::Key_Space);
    menuBiblio->addAction(nouveauLivre);
    bar->addMenu(menuBiblio);

    // Arbre de gauche
    tree = new QTreeWidget(this);
    QLabel * biblioLabel = new QLabel("",this);
    mainLayout->addWidget(biblioLabel,0,0);
    //mainLayout->addWidget(tree,1,0);
    tree->header()->hide();

    // Menu contextuel arbre
    contextMenu = new QMenu(tree);
    addDossierAction = new QAction("Ajouter un dossier",contextMenu);
    QAction * addLivreAction = new QAction("Ajouter un livre",contextMenu);
    QAction * deleteAction = new QAction("Supprimer",contextMenu);
    contextMenu->addAction(addLivreAction);
    contextMenu->addSeparator();
    contextMenu->addAction(addDossierAction);
    contextMenu->addSeparator();
    contextMenu->addAction(deleteAction);
    contextMenu->addSeparator();
    tree->addAction(addLivreAction);
    tree->addAction(addDossierAction);
    tree->addAction(deleteAction);

    QObject::connect(contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuAction(QAction*)));
    tree->setContextMenuPolicy(Qt::ActionsContextMenu);
    tree->setAcceptDrops(true);
    tree->setDragEnabled(true);
    tree->setDragDropMode(QAbstractItemView::InternalMove);


    // Fiche de droite
    Livre * testLivre = new Livre("");
    testLivre->setAuteur("");
    ficheLivre = new FicheLivre(this,testLivre);
    QLabel * ficheLabel = new QLabel("",this);
    mainLayout->addWidget(ficheLabel,0,1);
    //mainLayout->addWidget(ficheLivre,1,1);

    QObject::connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(changeFicheLivre(QTreeWidgetItem*)));
    //QObject::connect(tree,SIGNAL(),this,SLOT(changeFicheLivre(QTreeWidgetItem*)));

    splitter->addWidget(tree);
    splitter->addWidget(ficheLivre);

    mainLayout->addWidget(splitter,1,0,1,2);

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

void MainWindow::setLivreFicheLivre(Livre *unLivre)
{
    ficheLivre->setTitre(QString(unLivre->getTitre().c_str()));
    ficheLivre->setAuteur(QString(unLivre->getAuteur().c_str()));
    ficheLivre->setNotes(QString(unLivre->getNotes().c_str()));
}

void MainWindow::changeFicheLivre(QTreeWidgetItem * item)
{
    if (item->data(1,0) == 0){
        Livre * livreSelect = livreFromItem(item);
        setLivreFicheLivre(livreSelect);
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
                setLivreFicheLivre(newLivre);
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
