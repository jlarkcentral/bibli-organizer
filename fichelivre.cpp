#include "fichelivre.h"

#include <iostream>

FicheLivre::FicheLivre(QWidget *parent,Livre *unLivre) :
    QWidget(parent)
{
    auteur = new QLineEdit(unLivre->getAuteur().c_str(),this);
    titre = new QLineEdit(unLivre->getTitre().c_str(),this);
    genre = new QLineEdit(unLivre->getGenre().c_str(),this);
    edition = new QLineEdit(unLivre->getEdition().c_str(),this);
    dateEcriture = new QLineEdit(unLivre->getDateEcriture().c_str(),this);
    dateParution = new QLineEdit(unLivre->getDateParution().c_str(),this);
    notes = new QTextEdit(unLivre->getNotes().c_str(),this);
    notesPerso = new QTextEdit();

    QGridLayout * ficheLayout = new QGridLayout();

    // 1ere colonne
    QLabel * auteurLabel = new QLabel("Auteur :");
    ficheLayout->addWidget(auteurLabel,0,0);
    ficheLayout->addWidget(auteur,0,1);
    QLabel * titreLabel = new QLabel("Titre :");
    ficheLayout->addWidget(titreLabel,1,0);
    ficheLayout->addWidget(titre,1,1);
    QLabel * genreLabel = new QLabel("Genre :");
    ficheLayout->addWidget(genreLabel,2,0);
    ficheLayout->addWidget(genre,2,1);
    // 2eme colonne
    QLabel * editionLabel = new QLabel("Édition :");
    ficheLayout->addWidget(editionLabel,0,2);
    ficheLayout->addWidget(edition,0,3);
    QLabel * dateEcritureLabel = new QLabel("Date d'écriture :");
    ficheLayout->addWidget(dateEcritureLabel,1,2);
    ficheLayout->addWidget(dateEcriture,1,3);
    QLabel * dateParutionLabel = new QLabel("Date de parution :");
    ficheLayout->addWidget(dateParutionLabel,2,2);
    ficheLayout->addWidget(dateParution,2,3);
    // Notes
    QLabel * notesLabel = new QLabel("Notes pratiques:");
    ficheLayout->addWidget(notesLabel,3,0);
    ficheLayout->addWidget(notes,4,0,1,4);
    QLabel * notesPersoLabel = new QLabel("Notes personelles:");
    ficheLayout->addWidget(notesPersoLabel,5,0);
    ficheLayout->addWidget(notesPerso,6,0,1,4);
    this->setLayout(ficheLayout);
}


void FicheLivre::setAuteur(QString unAuteur)
{
    auteur->setText(unAuteur);
}

void FicheLivre::setTitre(QString unTitre)
{
    titre->setText(unTitre);
}

void FicheLivre::setNotes(QString desNotes)
{
    notes->setText(desNotes);
}

void FicheLivre::setEditable(bool b)
{
    editable = b;
    auteur->setReadOnly(!b);
    titre->setReadOnly(!b);
    notes->setReadOnly(!b);
    notesPerso->setReadOnly(!b);
}

QString FicheLivre::getAuteur()
{
    return auteur->text();
}

QString FicheLivre::getTitre()
{
    return titre->text();
}

QString FicheLivre::getNotes()
{
    return notes->toPlainText();
}

QString FicheLivre::getGenre()
{
    return genre->text();
}

QString FicheLivre::getEdition()
{
    return edition->text();
}

QString FicheLivre::getDateEcriture()
{
    return dateEcriture->text();
}

QString FicheLivre::getDateParution()
{
    return dateParution->text();
}

bool FicheLivre::isEditable()
{
    return editable;
}
