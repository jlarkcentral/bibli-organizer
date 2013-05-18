#ifndef PILEALIRE_H
#define PILEALIRE_H

#include <QWidget>
#include <QListWidget>
#include <QGridLayout>

class PileALire : public QWidget
{
    Q_OBJECT
public:
    explicit PileALire(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QListWidget * palList;
};

#endif // PILEALIRE_H
