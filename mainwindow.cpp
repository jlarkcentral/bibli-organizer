#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Taille fentre
    setMinimumWidth(500);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    centralwidget->setLayout(mainLayout);

    statbar = new QStatusBar(this);
    setStatusBar(statbar);

    // Entete fenetre
    setWindowTitle("BiblioApp");

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    QMenu* menuBiblio = new QMenu("&Biblio");
    QAction * nouveauLivre = new QAction("Nouveau Livre",menuBiblio);
    nouveauLivre->setShortcut(Qt::Key_Space);
    menuBiblio->addAction(nouveauLivre);
    bar->addMenu(menuBiblio);

    // TreeWidget
    arbo = new QTreeWidget();
    QHeaderView * header = arbo->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setResizeMode(0,QHeaderView::Stretch);
    arbo->setHeaderHidden(true);
    //arbo->setMouseTracking(true);
    //arbo->setStyleSheet("font-size : 18px; ");
    arbo->setColumnCount(1);
    //arbo->setSelectionMode(QAbstractItemView::NoSelection);


}

MainWindow::~MainWindow()
{
}
