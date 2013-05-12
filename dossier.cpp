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

void Dossier::delDossier(Dossier * unDossier)
{
    for( vector<Dossier*>::iterator iter = dossiers.begin(); iter != dossiers.end(); ++iter )
    {
        if( *iter == unDossier )
        {
            dossiers.erase( iter );
            break;
        }
    }
}

void Dossier::addLivre(Livre *unLivre)
{
    livres.push_back(unLivre);
}

void Dossier::delLivre(Livre *unLivre)
{
    for( vector<Livre*>::iterator iter = livres.begin(); iter != livres.end(); ++iter )
    {
        if( *iter == unLivre )
        {
            livres.erase( iter );
            break;
        }
    }
}
