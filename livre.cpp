#include "livre.h"

Livre::Livre(string unTitre)
{
    titre = unTitre;
}

void Livre::setLu(string estLu)
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

void Livre::setTitre(string unTitre)
{
    titre = unTitre;
}

void Livre::setAuteur(string unAuteur)
{
    auteur = unAuteur;
}

void Livre::setGenre(string unGenre)
{
    genre = unGenre;
}

void Livre::setEdition(string uneEdition)
{
    edition = uneEdition;
}

void Livre::setDateEcriture(string uneDate)
{
    dateEcriture = uneDate;
}

void Livre::setDateParution(string uneDate)
{
    dateParution = uneDate;
}

string Livre::getLu()
{
    return lu;
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
