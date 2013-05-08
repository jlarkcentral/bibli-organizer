#ifndef DOSSIER_H
#define DOSSIER_H

#include <iostream>
#include <vector>

#include "livre.h"

using namespace std;

class Dossier
{
public:
    Dossier(string unLabel);
    string getLabel();
    vector<Dossier*> getDossiers();
    vector<Livre*> getLivres();
    void setLabel(string unLabel);
    void addDossier(Dossier * unDossier);
    void delDossier(int position);
    void addLivre(Livre * unLivre);
    void delLivre(int position);

private:
    string label;
    vector<Dossier*> dossiers;
    vector<Livre*> livres;
};

#endif // DOSSIER_H
