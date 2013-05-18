#ifndef PILEALIRE_H
#define PILEALIRE_H

#include <QWidget>
#include <QTreeWidget>
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>

class PileALire : public QWidget
{
    Q_OBJECT
public:
    explicit PileALire(QWidget *parent = 0);

    QTreeWidget * palList;
    
signals:
    
public slots:


private:

};

#endif // PILEALIRE_H
