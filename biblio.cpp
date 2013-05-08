#include "biblio.h"

Biblio::Biblio()
{
    dossierPrincipal = new Dossier("Biblioteque");
}

Dossier* Biblio::getDossierPrincipal()
{
    return dossierPrincipal;
}

void Biblio::loadXml(string fileName)
{
    const char * charfilename = fileName.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
    if(element){
        xmlToBiblio(element,dossierPrincipal);
    }
}

void Biblio::xmlToBiblio(TiXmlElement *element, Dossier* unDossier)
{
    while(element){
        Dossier * newDossier = new Dossier(element->Attribute("label"));
        unDossier->addDossier(newDossier);
        TiXmlElement *elementChild = element->FirstChildElement();
        if(elementChild->Attribute("titre")){
            while(elementChild){
                Livre * newLivre = new Livre(elementChild->Attribute("titre"));
                newLivre->setLu(element->Attribute("lu") == "true");
                // ATTENTION !! Auteur pas forcement le label dossier > attribut auteur pour livre dans le XML
                newLivre->setAuteur(newDossier->getLabel());
                TiXmlElement *elementNotes = elementChild->FirstChildElement();
                if(elementNotes){
                    newLivre->setNotes(elementNotes->GetText());
                }
                newDossier->addLivre(newLivre);

                elementChild = elementChild->NextSiblingElement();
            }
        }
        else if(elementChild->Attribute("label")){
            xmlToBiblio(elementChild,newDossier);
        }
        element = element->NextSiblingElement();
    }
}

void Biblio::printBiblio()
{
    printBiblio(dossierPrincipal);
}

void Biblio::printBiblio(Dossier* unDossier)
{
    for(int i = 0 ; i < unDossier->getDossiers().size() ; i++){
        cout << "Dossier : " << unDossier->getDossiers().at(i)->getLabel() << endl;
        printBiblio(unDossier->getDossiers().at(i));
        for(int j = 0 ; j < unDossier->getDossiers().at(i)->getLivres().size() ; j++){
            cout << "Livre : " << unDossier->getDossiers().at(i)->getLivres().at(j)->getTitre() << endl;
        }
    }
}
