#include "groupe.h"

Groupe::Groupe(string unTheme)
{
    theme = unTheme;
}

void Groupe::addAuteur(Auteur *unAuteur)
{
    auteurs.push_back(unAuteur);
}

void Groupe::delAuteur(int position)
{
    auteurs.erase(auteurs.begin() + position);
}

void Groupe::setTheme(string unTheme)
{
    theme = unTheme;
}

string Groupe::getTheme()
{
    return theme;
}

vector<Auteur*> Groupe::getAuteurs()
{
    return auteurs;
}
