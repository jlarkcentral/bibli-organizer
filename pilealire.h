#ifndef PILEALIRE_H
#define PILEALIRE_H

#include <QWidget>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include <QMenu>

#include "livre.h"

using namespace std;

class PileALire : public QWidget
{
    Q_OBJECT
public:
    explicit PileALire(QWidget *parent = 0);

    QTreeWidget * palList;
    void emitPlusALire();
    
signals:
    void plusALire(QTreeWidgetItem* item);
    
public slots:
    void contextMenuActionPAL(QAction * action);
    void test();


private:


};

#endif // PILEALIRE_H
