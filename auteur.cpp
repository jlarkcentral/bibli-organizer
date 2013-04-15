#include "auteur.h"

Auteur::Auteur(string unNom)
{
    this->nom = unNom;
}

string Auteur::getNom()
{
    return nom;
}

vector<Livre *> Auteur::getLivres()
{
    return livres;
}

void Auteur::setNom(string unNom)
{
    this->nom = unNom;
}

void Auteur::addLivre(Livre *unLivre)
{
    livres.push_back(unLivre);
}

void Auteur::delLivre(int position)
{
    livres.erase(livres.begin() + position);
}
