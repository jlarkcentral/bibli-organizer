#include "biblio.h"

Biblio::Biblio()
{
    dossierPrincipal = new Dossier("Bibliothèque");
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
        if(element->Attribute("label")){
            Dossier * newDossier = new Dossier(element->Attribute("label"));
            unDossier->addDossier(newDossier);
            xmlToBiblio(element->FirstChildElement(),newDossier);
        }
        else if(element->Attribute("titre")){
            Livre * newLivre = new Livre(element->Attribute("titre"));
            newLivre->setAuteur(element->Attribute("auteur"));
            newLivre->setGenre(element->Attribute("genre"));
            newLivre->setEdition(element->Attribute("edition"));
            newLivre->setDateEcriture(element->Attribute("dateEcriture"));
            newLivre->setDateParution(element->Attribute("dateParution"));
            newLivre->setLu(element->Attribute("lu"));
            if(element->FirstChildElement()){
                if(element->FirstChildElement()->GetText()){
                    newLivre->setNotes(element->FirstChildElement()->GetText());
                }
            }
            if(element->FirstChildElement()->NextSiblingElement()){
                if(element->FirstChildElement()->NextSiblingElement()->GetText()){
                    newLivre->setNotesPerso(element->FirstChildElement()->NextSiblingElement()->GetText());
                }
            }
            unDossier->addLivre(newLivre);
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
    for(uint i = 0 ; i < unDossier->getDossiers().size() ; i++){
        cout << "Dossier : " << unDossier->getDossiers().at(i)->getLabel() << endl;
        printBiblio(unDossier->getDossiers().at(i));
        for(uint j = 0 ; j < unDossier->getDossiers().at(i)->getLivres().size() ; j++){
            cout << "Livre : " << unDossier->getDossiers().at(i)->getLivres().at(j)->getTitre() << endl;
        }
    }
}

void Biblio::biblioToXml(Dossier * dossierCourant,TiXmlElement * elementCourant)
{
    for(uint i = 0 ; i < dossierCourant->getDossiers().size() ; i++){
        TiXmlElement * newElement = new TiXmlElement("dossier");
        Dossier * d = dossierCourant->getDossiers().at(i);
        newElement->SetAttribute("label",d->getLabel().c_str());
        elementCourant->LinkEndChild(newElement);
        biblioToXml(d,newElement);
    }
    for(uint i = 0 ; i < dossierCourant->getLivres().size() ; i++){
        TiXmlElement * newElement = new TiXmlElement("livre");
        Livre * l = dossierCourant->getLivres().at(i);
        newElement->SetAttribute("titre",l->getTitre().c_str());
        newElement->SetAttribute("auteur",l->getAuteur().c_str());
        newElement->SetAttribute("genre",l->getGenre().c_str());
        newElement->SetAttribute("edition",l->getEdition().c_str());
        newElement->SetAttribute("dateEcriture",l->getDateEcriture().c_str());
        newElement->SetAttribute("dateParution",l->getDateParution().c_str());
        newElement->SetAttribute("lu",l->getLu().c_str());

        TiXmlElement * notesElement = new TiXmlElement("notes");
        newElement->LinkEndChild(notesElement);
        TiXmlText * notesText = new TiXmlText(l->getNotes().c_str());
        notesElement->LinkEndChild(notesText);

        TiXmlElement * notesPersoElement = new TiXmlElement("notesPerso");
        newElement->LinkEndChild(notesPersoElement);
        TiXmlText * notesPersoText = new TiXmlText(l->getNotesPerso().c_str());
        notesPersoElement->LinkEndChild(notesPersoText);

        elementCourant->LinkEndChild(newElement);
    }
}

void Biblio::saveBiblio()
{
    string filename = "/home/primo/Documents/QtCreator/bibli-organizer/save.xml";
    const char * charnom = filename.c_str();
    TiXmlDocument doc(charnom);

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "ISO-8859-1", "" );
    doc.LinkEndChild( decl );
    TiXmlElement * firstElement = new TiXmlElement( "racine" );
    doc.LinkEndChild( firstElement );

    biblioToXml(dossierPrincipal,firstElement);

    doc.SaveFile();
}
