#include "biblio.h"

Biblio::Biblio()
{
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

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
    if(element){
        xmlToBiblio(element);
    }
}

void Biblio::xmlToBiblio(TiXmlElement *element)
{
    while(element){
        Groupe * newGroupe = new Groupe(element->Attribute("theme"));
        this->addGroupe(newGroupe);
        TiXmlElement * elementAuteur = element->FirstChildElement();
        while(elementAuteur){
            Auteur * newAuteur = new Auteur(elementAuteur->Attribute("nom"));
            newGroupe->addAuteur(newAuteur);
            TiXmlElement * elementLivre = elementAuteur->FirstChildElement();
            while(elementLivre){
                Livre * newLivre = new Livre(elementLivre->Attribute("titre"));
                string newLivreLu = elementLivre->Attribute("lu");
                newLivre->setLu(newLivreLu == "true");
                TiXmlElement * elementNotes = elementLivre->FirstChildElement();
                newLivre->setNotes(elementNotes->GetText());

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
            for(int k = 0 ; k < groupes.at(i)->getAuteurs()->getLivres().size; k++){
                cout << "Auteur : " << groupes.at(i)->getAuteurs().at(j)->getLivres().at(k)->getTitre() << endl;
            }
            cout << endl;
        }
        cout << endl;
    }
}
