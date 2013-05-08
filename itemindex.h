#ifndef ITEMINDEX_H
#define ITEMINDEX_H

#include <QTreeWidgetItem>

#include "livre.h"
#include "dossier.h"

class ItemIndex
{
public:
    ItemIndex(Livre* unLivre, QTreeWidgetItem* item);
    ItemIndex(Dossier* unDossier, QTreeWidgetItem* item);

    void setLivre(Livre * unLivre);
    void setTreeItem(QTreeWidgetItem * item);
    void setDossier(Dossier * unDossier);
    Livre* getLivre();
    Dossier* getDossier();
    QTreeWidgetItem* getTreeItem();

private:
    Livre * livre;
    Dossier * dossier;
    QTreeWidgetItem * treeItem;
};

#endif // ITEMINDEX_H
