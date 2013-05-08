#include "itemindex.h"

ItemIndex::ItemIndex(Livre *unLivre, QTreeWidgetItem *item)
{
    livre = unLivre;
    treeItem = item;
}

ItemIndex::ItemIndex(Dossier *unDossier, QTreeWidgetItem *item)
{
    dossier = unDossier;
    treeItem = item;
}

void ItemIndex::setLivre(Livre *unLivre)
{
    livre = unLivre;
}

void ItemIndex::setDossier(Dossier *unDossier)
{
    dossier = unDossier;
}

void ItemIndex::setTreeItem(QTreeWidgetItem *item)
{
    treeItem = item;
}

Livre* ItemIndex::getLivre()
{
    return livre;
}

Dossier* ItemIndex::getDossier()
{
    return dossier;
}

QTreeWidgetItem* ItemIndex::getTreeItem()
{
    return treeItem;
}
