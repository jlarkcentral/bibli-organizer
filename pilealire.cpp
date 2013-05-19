#include "pilealire.h"
#include <iostream>

PileALire::PileALire(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout * palLayout = new QGridLayout();
    this->setLayout(palLayout);

    palList = new QTreeWidget(this);
    palList->setColumnCount(2);
    palList->header()->setResizeMode(QHeaderView::ResizeToContents);
    palList->setStyleSheet("font-size : 16px");
    palList->setRootIsDecorated(false);
    palList->setHeaderHidden(true);
    palList->setContextMenuPolicy(Qt::ActionsContextMenu);
    QTreeWidgetItem * header = new QTreeWidgetItem();
    header->setText(0,"Pile À Lire");
    header->setFont(0,QFont(palList->font().rawName(),12,QFont::DemiBold));
    header->setBackgroundColor(0,QColor(230,230,230));
    header->setBackgroundColor(1,QColor(230,230,230));
    header->setBackgroundColor(2,QColor(230,230,230));
    header->setExpanded(true);
    header->setFlags(Qt::ItemIsEnabled);
    palList->invisibleRootItem()->addChild(header);

    palLayout->addWidget(palList);


    // Menu contextuel arbre
    QMenu * contextMenuPAL = new QMenu(palList);
    QAction * enlever = new QAction("Enlever de la liste",contextMenuPAL);
    contextMenuPAL->addAction(enlever);
    palList->addAction(enlever);

    QObject::connect(contextMenuPAL,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuActionPAL(QAction*)));
//    QObject::connect(this,SIGNAL(plusALire(QTreeWidgetItem*)),this,SLOT(test()));
}

void PileALire::contextMenuActionPAL(QAction *action)
{
    QTreeWidgetItem * item = palList->currentItem();
    QString text = action->text();
    if (item){
        if(text == "Enlever de la liste"){
            cout << "elnever" << endl;
            emitPlusALire();
        }
    }
}

void PileALire::emitPlusALire()
{
    cout << "emitPlusALire" << endl;
    emit plusALire(palList->currentItem());
}

void PileALire::test()
{
    cout << "emit works" << endl;
}
