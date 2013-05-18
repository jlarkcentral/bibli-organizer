#include <QWidget>
#include <QSplitter>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QMessageBox>

#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // init param
    loadSettings();
    nbLivresLus = 0;

    // Taille fenetre
    setMinimumWidth(500);
    setMinimumHeight(300);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    QSplitter * splitter = new QSplitter();
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    centralwidget->setLayout(mainLayout);
    // Entete fenetre
    setWindowTitle("BiblioApp");

    QStatusBar * stbar = new QStatusBar(this);
    setStatusBar(stbar);

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    bar->setMinimumWidth(250);

    QMenu* menuBiblio = new QMenu("&Biblio");
    QAction * nouveauDossier = new QAction("Ajouter un dossier principal",menuBiblio);
    nouveauDossier->setShortcut(QKeySequence("CTRL+A"));
    QAction * affichage = new QAction("Développer la liste",menuBiblio);
    affichage->setShortcut(QKeySequence("CTRL+D"));
    QAction * sauver = new QAction("Sauvegarder la liste",menuBiblio);
    sauver->setShortcut(QKeySequence("CTRL+S"));
    QAction * quitter = new QAction("Quitter",menuBiblio);
    quitter->setShortcut(QKeySequence("CTRL+Q"));
    menuBiblio->addAction(nouveauDossier);
    menuBiblio->addAction(affichage);
    menuBiblio->addAction(sauver);
    menuBiblio->addAction(quitter);

    QMenu* menuPref = new QMenu("&Préférences");
    QAction * securite = new QAction("Confirmer avant de supprimer",menuPref);
    securite->setCheckable(true);
    securite->setChecked(securityOnDelete);
    menuPref->addAction(securite);

    bar->addMenu(menuBiblio);
    bar->addMenu(menuPref);

    // titre - espacement
    QLabel * title = new QLabel("");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size : 16px");
    mainLayout->addWidget(title,0,0);

    ficheLabel = new QLabel("");
    ficheLabel->setStyleSheet("font-size : 18px");
    mainLayout->addWidget(ficheLabel,0,3);

    // bouton edition
    buttonEdit = new QPushButton("Mode lecture");
    buttonEdit->setCheckable(true);
    buttonEdit->setEnabled(false);
    buttonEdit->setFixedWidth(110);
    mainLayout->addWidget(buttonEdit,0,5);

    // Arbre de gauche
    tree = new QTreeWidget(this);
    tree->header()->hide();
    tree->setStyleSheet("font-size : 16px");
    tree->setRootIsDecorated(false);
    tree->sortItems(0,Qt::AscendingOrder);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Menu contextuel arbre
    contextMenu = new QMenu(tree);
    addDossierAction = new QAction("Ajouter un dossier",contextMenu);
    addLivreAction = new QAction("Ajouter un livre",contextMenu);
    renameAction = new QAction("Renommer",contextMenu);
    deleteAction = new QAction("Supprimer",contextMenu);
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

    tree->setContextMenuPolicy(Qt::ActionsContextMenu);
    tree->setAcceptDrops(true);
    tree->setDragEnabled(true);
    tree->setDragDropMode(QAbstractItemView::InternalMove);

    // Fiche de droite
    Livre * testLivre = new Livre("");
    testLivre->setAuteur("");
    ficheLivre = new FicheLivre(this,testLivre);
    ficheLivre->setEditable(false);
    ficheLivre->setDisabled(true);

    splitter->addWidget(tree);
    splitter->addWidget(ficheLivre);
    splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    mainLayout->addWidget(splitter,1,0,1,6);

    QObject::connect(menuBiblio,SIGNAL(triggered(QAction*)),this,SLOT(menuAction(QAction*)));
    QObject::connect(securite,SIGNAL(toggled(bool)),this,SLOT(secureDelete(bool)));
    QObject::connect(tree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(contextMenuChange(QTreeWidgetItem*)));
    QObject::connect(tree,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(buttonEditEnable(QTreeWidgetItem*)));
    QObject::connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClickItemSlot(QTreeWidgetItem*)));
    QObject::connect(tree,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(updateTreeOrder(QTreeWidgetItem*,int)));
    QObject::connect(contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuAction(QAction*)));
    QObject::connect(buttonEdit,SIGNAL(toggled(bool)),ficheLivre,SLOT(setEditable(bool)));
    QObject::connect(buttonEdit,SIGNAL(toggled(bool)),this,SLOT(buttonEditChange(bool)));
    QObject::connect(ficheLivre->titre,SIGNAL(textChanged(QString)),this,SLOT(setFicheLabelText(QString)));
//    QObject::connect(ficheLivre,SIGNAL(setlu(bool)),this,SLOT(updateNbLivresLus(bool)));
    QObject::connect(this,SIGNAL(appClosed()),this,SLOT(save()));
}

void MainWindow::updateTreeOrder(QTreeWidgetItem * item, int col)
{
    if(col == 0){
        tree->sortItems(0,Qt::AscendingOrder);
    }
}

void MainWindow::updateNbLivresLus(bool b)
{
    if(b){
        nbLivresLus++;
    }
    else nbLivresLus--;
    updateStatusBar();
}

void MainWindow::loadSettings()
{
    const char * charfilename = "./settings.xml";
    TiXmlDocument doc(charfilename);
    doc.LoadFile();

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
    if(element->Attribute("secureDelete")){
        secureDelete(string(element->Attribute("secureDelete")) == "true");
    }
}

void MainWindow::saveSettings()
{
    const char * charnom = "./settings.xml";
    TiXmlDocument doc(charnom);

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
    doc.LinkEndChild( decl );
    TiXmlElement * firstElement = new TiXmlElement( "root" );
    doc.LinkEndChild( firstElement );
    TiXmlElement * element = new TiXmlElement( "settings" );
    firstElement->LinkEndChild(element);

    const char * securityAtt = "";
    if(securityOnDelete){
        securityAtt = "true";
    }
    else securityAtt = "false";

    element->SetAttribute("secureDelete",securityAtt);

    doc.SaveFile();
}

void MainWindow::biblioToTree(Dossier * dossier,QTreeWidgetItem * item)
{
    for(uint i = 0 ; i < dossier->getDossiers().size() ; i++){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        Dossier * dossierCourant = dossier->getDossiers().at(i);
        newItem->setText(0,QString(dossierCourant->getLabel().c_str()));
        newItem->setData(1,0,1);
        newItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);
        //        index.push_back(new ItemIndex(dossierCourant,newItem));
        dossierMap.insert(pair<QTreeWidgetItem*,Dossier*>(newItem,dossierCourant));
        item->addChild(newItem);
        biblioToTree((dossier->getDossiers().at(i)),newItem);
    }
    for(uint i = 0 ; i < dossier->getLivres().size() ; i++){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        Livre * livreCourant = dossier->getLivres().at(i);
        newItem->setText(0,QString(livreCourant->getTitre().c_str()));
        newItem->setData(1,0,0);
        newItem->setFont(0,QFont(tree->font().rawName(),tree->font().pointSize(),QFont::Light));
        newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled);
        //        index.push_back(new ItemIndex(livreCourant,newItem));
        livreMap.insert(pair<QTreeWidgetItem*,Livre*>(newItem,livreCourant));
        item->addChild(newItem);
        if(livreCourant->getLu() == "y"){
            nbLivresLus++;
        }
    }
    QTreeWidgetItem * top = tree->topLevelItem(0);
    top->setExpanded(true);
    top->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDropEnabled);
    top->setData(1,0,2);
    top->setBackgroundColor(0,QColor(230,230,230));
    tree->sortItems(0,Qt::AscendingOrder);

    updateStatusBar();
}

void MainWindow::treeToBiblio(QTreeWidgetItem *itemCourant,Dossier * dossierCourant)
{
    for(int i = 0 ; i < itemCourant->childCount() ; i++){
        if(itemCourant->child(i)->data(1,0) == 1 || itemCourant->child(i)->data(1,0) == 2){
            Dossier * d = new Dossier(itemCourant->child(i)->text(0).toStdString());
            dossierCourant->addDossier(d);
            treeToBiblio(itemCourant->child(i),d);
        }
        else if(itemCourant->child(i)->data(1,0) == 0){
            //            Livre * l = livreFromItem(itemCourant->child(i));
            Livre * l = livreMap.at(itemCourant->child(i));
            dossierCourant->addLivre(l);
        }
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
    ficheLivre->setItemCourant(item);
    ficheLivre->setLivre(unLivre);
    ficheLivre->setTitre(QString(unLivre->getTitre().c_str()));
    ficheLivre->setAuteur(QString(unLivre->getAuteur().c_str()));
    ficheLivre->setGenre(QString(unLivre->getGenre().c_str()));
    ficheLivre->setEdition(QString(unLivre->getEdition().c_str()));
    ficheLivre->setDateEcriture(QString(unLivre->getDateEcriture().c_str()));
    ficheLivre->setDateParution(QString(unLivre->getDateParution().c_str()));
    ficheLivre->setNotes(QString(unLivre->getNotes().c_str()));
    ficheLivre->setNotesPerso(QString(unLivre->getNotesPerso().c_str()));
    ficheLivre->setCheckLu(unLivre->getLu() == "y");
}

void MainWindow::doubleClickItemSlot(QTreeWidgetItem * item)
{
    if (item->data(1,0) == 0){
        if(ficheLivre->isEnabled() == false){
            ficheLivre->setEnabled(true);
        }
        //        Livre * livreSelect = livreFromItem(item);
        Livre * livreSelect = livreMap.at(item);
        setLivreFicheLivre(livreSelect,item);
        //        ficheLabel->setText("Fiche du livre \"" + QString(livreSelect->getTitre().c_str()) + "\"");
        setWindowTitle("BiblioApp  :   \"" + QString(livreSelect->getTitre().c_str()) + "\"");
    }
    else if(item->data(1,0) == 2){
        item->setExpanded(false);
    }
}

void MainWindow::contextMenuAction(QAction *action)
{
    QTreeWidgetItem * item = tree->currentItem();
    QString text = action->text();
    if (item){
        if(item->data(1,0) == 1 || item->data(1,0) == 2){
            if(text=="Ajouter un livre"){
                ficheLivre->setEnabled(true);
                // update arbre
                item->setExpanded(true);
                QTreeWidgetItem * newItem = new QTreeWidgetItem();
                newItem->setText(0,"Nouveau Livre");
                newItem->setData(1,0,0);
                newItem->setFont(0,QFont(tree->font().rawName(),tree->font().pointSize(),QFont::Light));
                newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled);
                item->addChild(newItem);
                // update modele
                Livre * newLivre = new Livre("Nouveau Livre");
                //                Dossier * in = dossierFromItem(item);
                Dossier * in = dossierMap.at(item);
                in->addLivre(newLivre);
                //                index.push_back(new ItemIndex(newLivre,newItem));
                livreMap.insert(pair<QTreeWidgetItem*,Livre*>(newItem,newLivre));
                // update fiche
                setLivreFicheLivre(newLivre,0);
                ficheLivre->setEditable(true);
                ficheLivre->focusOnTitre();
                ficheLivre->setItemCourant(newItem);
                tree->selectedItems().at(0)->setSelected(false);
                newItem->setSelected(true);
                //                ficheLabel->setText("Nouvelle fiche de livre");
                setWindowTitle("BilioApp  :  Nouvelle fiche de livre");
                buttonEdit->setEnabled(true);
                buttonEdit->setChecked(true);
                buttonEditChange(true);
                updateStatusBar();
            }
            else if(text=="Ajouter un dossier"){
                // update arbre
                item->setExpanded(true);
                QTreeWidgetItem * newItem = new QTreeWidgetItem();
                newItem->setText(0,"Nouveau dossier");
                newItem->setData(1,0,1);
                newItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);
                item->addChild(newItem);
                // update modele
                Dossier * newDossier = new Dossier("Nouveau Dossier");
                //                Dossier * in = dossierFromItem(item);
                Dossier * in = dossierMap.at(item);
                in->addDossier(newDossier);
                //                index.push_back(new ItemIndex(newDossier,newItem));
                dossierMap.insert(pair<QTreeWidgetItem*,Dossier*>(newItem,newDossier));
                //                tree->sortItems(0,Qt::AscendingOrder);
                tree->editItem(newItem,0);
            }
            else if(text=="Renommer"){
                tree->editItem(item,0);
            }
        }
        if(item->data(1,0) == 0){
            addDossierAction->setDisabled(true);
        }
        if(text=="Supprimer"){
            itemCourant = item;
            if(securityOnDelete){
                QMessageBox * supprDiag = new QMessageBox();
                supprDiag->setWindowTitle("Supprimer...");
                supprDiag->addButton("Annuler",QMessageBox::RejectRole);
                supprDiag->addButton("Ok",QMessageBox::AcceptRole);
                if(item->data(1,0) == 1){
                    supprDiag->setText("Le dossier \"" + item->text(0) + "\" va être supprimé");
                }
                else if(item->data(1,0) == 0){
                    supprDiag->setText("Le livre \"" + item->text(0) + "\" va être supprimé");
                }
                supprDiag->show();
                QObject::connect(supprDiag,SIGNAL(accepted()),this,SLOT(deleteItemCourant()));
            }
            else{
                deleteItemCourant();
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
        deleteAction->setEnabled(true);
    }
    if(item->data(1,0) == 0){
        addDossierAction->setEnabled(false);
        addLivreAction->setEnabled(false);
        renameAction->setEnabled(false);
        deleteAction->setEnabled(true);
    }
    if(item->data(1,0) == 2){
        addDossierAction->setEnabled(true);
        addLivreAction->setEnabled(true);
        renameAction->setEnabled(false);
        deleteAction->setEnabled(false);
    }
}

void MainWindow::buttonEditChange(bool mode)
{
    if(mode){
        buttonEdit->setText("Mode édition");
    }
    else{
        buttonEdit->setText("Mode lecture");
    }
}

void MainWindow::buttonEditEnable(QTreeWidgetItem *item)
{
    if(item->data(1,0) == 0){
        buttonEdit->setEnabled(true);
    }
    else if(item->data(1,0) == 1){
        buttonEdit->setEnabled(false);
    }
}

//Livre* MainWindow::livreFromItem(QTreeWidgetItem *item)
//{
//    for(uint i = 0 ; i < index.size() ; i++){
//        ItemIndex * cii = index.at(i);
//        if(cii->getTreeItem() == item){
//            return cii->getLivre();
//        }
//    }
//    return 0;
//}

//Dossier* MainWindow::dossierFromItem(QTreeWidgetItem *item)
//{
//    for(uint i = 0 ; i < index.size() ; i++){
//        ItemIndex * cii = index.at(i);
//        if(cii->getTreeItem() == item){
//            return cii->getDossier();
//        }
//    }
//    return 0;
//}

//QTreeWidgetItem* MainWindow::itemFromDossier(Dossier *unDossier)
//{
//    for(uint i = 0 ; i < index.size() ; i++){
//        ItemIndex * cii = index.at(i);
//        if(cii->getDossier() == unDossier){
//            return cii->getTreeItem();
//        }
//    }
//    return 0;
//}

//QTreeWidgetItem* MainWindow::itemFromLivre(Livre *unLivre)
//{
//    for(uint i = 0 ; i < index.size() ; i++){
//        ItemIndex * cii = index.at(i);
//        if(cii->getLivre() == unLivre){
//            return cii->getTreeItem();
//        }
//    }
//    return 0;
//}

void MainWindow::updateStatusBar()
{
    nbLivres = livreMap.size();
    this->statusBar()->showMessage("Livres : " + QString::number(nbLivres) + "       Lus : " + QString::number(nbLivresLus));
}

void MainWindow::deleteItemCourant()
{
    if(itemCourant){
        Dossier * dossierCourant = dossierMap.at(itemCourant->parent());
        if(itemCourant->data(1,0) == 0){
            Livre * l = livreMap.at(itemCourant);
            if(l->getLu() == "y"){
                nbLivresLus--;
                updateStatusBar();
            }
            dossierCourant->delLivre(l);
            livreMap.erase(itemCourant);
        }
        else if(itemCourant->data(1,0) == 1){
            Dossier * d = dossierMap.at(itemCourant);
            dossierCourant->delDossier(d);
            dossierMap.erase(itemCourant);
        }
        delete(itemCourant);
    }
}

void MainWindow::save()
{
    Biblio * newBiblio = new Biblio();
    treeToBiblio(tree->invisibleRootItem(),newBiblio->getDossierPrincipal());
    biblio = newBiblio;
    biblio->saveBiblio();

    saveSettings();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    emit appClosed();
    event->accept();
}

void MainWindow::setFicheLabelText(QString qs)
{
    //    ficheLabel->setText("Fiche du livre \"" + qs + "\"");
    setWindowTitle("BiblioApp  :  \"" + qs + "\"");
}

void MainWindow::menuAction(QAction *action)
{
    QString text = action->text();
    if(text == "Ajouter un dossier principal"){
        QTreeWidgetItem * newItem = new QTreeWidgetItem();
        newItem->setText(0,"Nouveau dossier");
        newItem->setData(1,0,1);
        newItem->setFlags(Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled);
        tree->topLevelItem(0)->addChild(newItem);
        // update modele
        Dossier * newDossier = new Dossier("Nouveau Dossier");
        //                Dossier * in = dossierFromItem(item);
        Dossier * in = dossierMap.at(tree->topLevelItem(0));
        in->addDossier(newDossier);
        //                index.push_back(new ItemIndex(newDossier,newItem));
        dossierMap.insert(pair<QTreeWidgetItem*,Dossier*>(newItem,newDossier));
        tree->editItem(newItem,0);
    }
    else if(text == "Développer la liste"){
        tree->expandAll();
        action->setText("Réduire la liste");
    }
    else if(text == "Réduire la liste"){
        tree->collapseAll();
        tree->topLevelItem(0)->setExpanded(true);
        action->setText("Développer la liste");
    }
    else if(text == "Sauvegarder la liste"){

    }
    else if(text == "Quitter"){
        close();
    }
}

void MainWindow::secureDelete(bool secure)
{
    securityOnDelete = secure;
}

MainWindow::~MainWindow()
{
}
