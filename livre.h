#ifndef LIVRE_H
#define LIVRE_H

#include <string>

using namespace std;

class Livre
{
public:
    Livre(string unTitre);
    string getTitre();
    void setLu(bool estLu);
    void setNotes(string desNotes);
private:
    string titre;
    bool lu;
    string notes;
};

#endif // LIVRE_H
