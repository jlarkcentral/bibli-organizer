#ifndef GROUPE_H
#define GROUPE_H

#include "auteur.h"

using namespace std;

class Groupe
{
public:
    Groupe(string unTheme);
    void addAuteur(Auteur * unAuteur);
    void delAuteur(int position);
    void setTheme(string unTheme);
    string getTheme();
    vector<Auteur*> getAuteurs();

private:
    string theme;
    vector<Auteur*> auteurs;
};

#endif // GROUPE_H
