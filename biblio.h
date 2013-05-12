#ifndef BIBLIO_H
#define BIBLIO_H


#include <fstream>
#include <unistd.h>
#include <iostream>

#include "dossier.h"

#include "tinyxml/tinyxml.h"

using namespace std;

class Biblio
{
public:
    Biblio();
    Dossier * getDossierPrincipal();
    void loadXml(string filename);
    void xmlToBiblio(TiXmlElement *element, Dossier *unDossier);
    void printBiblio(Dossier *unDossier);
    void printBiblio();
    void biblioToXml(Dossier *dossierCourant, TiXmlElement *elementCourant);
    void saveBiblio();

private:
    Dossier * dossierPrincipal;
};

#endif // BIBLIO_H
