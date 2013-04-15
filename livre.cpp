#include "livre.h"

Livre::Livre(string unTitre)
{
    titre = unTitre;
    lu = false;
}

void Livre::setLu(bool estLu)
{
    lu = estLu;
}

void Livre::setNotes(string desNotes)
{
    notes = desNotes;
}

string Livre::getTitre()
{
    return titre;
}
