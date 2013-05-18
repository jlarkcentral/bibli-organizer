#include "pilealire.h"

PileALire::PileALire(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout * palLayout = new QGridLayout();
    this->setLayout(palLayout);

    palList = new QListWidget(this);
    QListWidgetItem * header = new QListWidgetItem("Pile À Lire");
    header->setBackgroundColor(QColor(230,230,230));
    palList->addItem(header);
    palList->setStyleSheet("font-size : 16px");
    palList->sortItems();
    palLayout->addWidget(palList,0,0,1,6);
}
