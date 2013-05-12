#ifndef DOSSIER_H
#define DOSSIER_H

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
    void delDossier(Dossier * unDossier);
    void addLivre(Livre * unLivre);
    void delLivre(Livre * unLivre);

private:
    string label;
    vector<Dossier*> dossiers;
    vector<Livre*> livres;
};

#endif // DOSSIER_H
