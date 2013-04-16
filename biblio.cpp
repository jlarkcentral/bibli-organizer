#include "biblio.h"

Biblio::Biblio()
{
    cout << "biblio" << endl;
}

void Biblio::addGroupe(Groupe *unGroupe)
{
    groupes.push_back(unGroupe);
}

void Biblio::delGroupe(int position)
{
    groupes.erase(groupes.begin() + position);
}

void Biblio::loadXml(string fileName)
{
    const char * charfilename = fileName.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();

    cout << "Doc loaded" << endl;

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
    if(element){
        xmlToBiblio(element);
    }
}

void Biblio::xmlToBiblio(TiXmlElement *element)
{
    cout << "xml to biblio" << endl;

    while(element){
        cout << "while element" << endl;
        Groupe * newGroupe = new Groupe(element->Attribute("theme"));
        this->addGroupe(newGroupe);
        TiXmlElement * elementAuteur = element->FirstChildElement();
        while(elementAuteur){
            cout << "while elementAuteur" << endl;
            Auteur * newAuteur = new Auteur(elementAuteur->Attribute("nom"));
            newGroupe->addAuteur(newAuteur);
            TiXmlElement * elementLivre = elementAuteur->FirstChildElement();
            while(elementLivre){
                cout << "while elementLivre" << endl;
                Livre * newLivre = new Livre(elementLivre->Attribute("titre"));
                string newLivreLu = elementLivre->Attribute("lu");
                newLivre->setLu(newLivreLu == "true");
                TiXmlElement * elementNotes = elementLivre->FirstChildElement();
                if(elementNotes){
                    newLivre->setNotes(elementNotes->GetText());
                }
                newAuteur->addLivre(newLivre);

                elementLivre = elementLivre->NextSiblingElement();
            }
            elementAuteur = elementAuteur->NextSiblingElement();
        }
        element = element->NextSiblingElement();
    }
}

void Biblio::printBiblio()
{
    for(int i = 0 ; i < groupes.size() ; i++){
        cout << "Groupe : " << groupes.at(i)->getTheme() << endl;
        for(int j = 0 ; j < groupes.at(i)->getAuteurs().size(); j++){
            cout << "Auteur : " << groupes.at(i)->getAuteurs().at(j)->getNom() << endl;
            for(int k = 0 ; k < groupes.at(i)->getAuteurs().at(j)->getLivres().size(); k++){
                cout << "Livre : " << groupes.at(i)->getAuteurs().at(j)->getLivres().at(k)->getTitre() << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
}
