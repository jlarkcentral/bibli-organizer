#include "pilealire.h"

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
    QTreeWidgetItem * header = new QTreeWidgetItem();
    header->setText(0,"Pile À Lire");
    header->setFont(0,QFont(palList->font().rawName(),12,QFont::DemiBold));
    header->setBackgroundColor(0,QColor(230,230,230));
    header->setBackgroundColor(1,QColor(230,230,230));
    header->setBackgroundColor(2,QColor(230,230,230));
    palList->invisibleRootItem()->addChild(header);

    palLayout->addWidget(palList);
}

