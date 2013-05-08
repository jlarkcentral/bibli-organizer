#ifndef LIVRE_H
#define LIVRE_H

#include <string>

using namespace std;

class Livre
{
public:
    Livre(string unTitre);
    string getTitre();
    string getAuteur();
    string getGenre();
    string getEdition();
    string getDateEcriture();
    string getDateParution();
    string getNotes();
    string getNotesPerso();
    void setLu(bool estLu);
    void setNotes(string desNotes);
    void setNotesPerso(string desNotesPerso);
    void setAuteur(string unAuteur);
    void setGenre(string unGenre);
    void setEdition(string uneEdition);
    void setDateEcriture(string uneDate);
    void setDateParution(string uneDate);


private:
    string titre;
    string auteur;
    bool lu;
    string notes;
    string notesPerso;
    string edition;
    string dateParution;
    string dateEcriture;
    string genre;

    // edition , date de parution , date d ecriture , genre
};

#endif // LIVRE_H
