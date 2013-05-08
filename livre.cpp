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

void Livre::setNotesPerso(string desNotesPerso)
{
    notesPerso = desNotesPerso;
}

void Livre::setAuteur(string unAuteur)
{
    auteur = unAuteur;
}

string Livre::getTitre()
{
    return titre;
}

string Livre::getAuteur()
{
    return auteur;
}

string Livre::getNotes()
{
    return notes;
}

string Livre::getNotesPerso()
{
    return notesPerso;
}

string Livre::getGenre()
{
    return genre;
}

string Livre::getEdition()
{
    return edition;
}

string Livre::getDateEcriture()
{
    return dateEcriture;
}

string Livre::getDateParution()
{
    return dateParution;
}
