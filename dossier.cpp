#include "dossier.h"

Dossier::Dossier(string unLabel)
{
    label = unLabel;
}

string Dossier::getLabel()
{
    return label;
}

vector<Livre *> Dossier::getLivres()
{
    return livres;
}

vector<Dossier *> Dossier::getDossiers()
{
    return dossiers;
}

void Dossier::setLabel(string unLabel)
{
    label = unLabel;
}

void Dossier::addDossier(Dossier *unDossier)
{
    dossiers.push_back(unDossier);
}

void Dossier::delDossier(int position)
{
    dossiers.erase(dossiers.begin() + position);
}

void Dossier::addLivre(Livre *unLivre)
{
    livres.push_back(unLivre);
}

void Dossier::delLivre(int position)
{
    livres.erase(livres.begin() + position);
}
