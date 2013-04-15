#ifndef AUTEUR_H
#define AUTEUR_H

#include <vector>
#include "livre.h"

using namespace std;

class Auteur
{
public:
    Auteur(string unNom);
    string getNom();
    vector<Livre*> getLivres();
    void setNom(string unNom);
    void addLivre(Livre * unLivre);
    void delLivre(int position);
private:
    string nom;
    vector<Livre*> livres;
};

#endif // AUTEUR_H
