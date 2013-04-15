#ifndef BIBLIO_H
#define BIBLIO_H

#include <QTreeWidget>

#include <fstream>
#include <unistd.h>
#include <iostream>

#include "groupe.h"
#include "tinyxml/tinyxml.h"

using namespace std;

class Biblio
{
public:
    Biblio();
    void addGroupe(Groupe * unGroupe);
    void delGroupe(int position);
    void loadXml(string filename);
    void xmlToBiblio(TiXmlElement * element);
    void printBiblio();

private:
    vector<Groupe*> groupes;
    QTreeWidget arbo;
};

#endif // BIBLIO_H
