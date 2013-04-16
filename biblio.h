#ifndef BIBLIO_H
#define BIBLIO_H


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
};

#endif // BIBLIO_H
