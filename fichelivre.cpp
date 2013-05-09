#include "fichelivre.h"

#include <iostream>

FicheLivre::FicheLivre(QWidget *parent,Livre *unLivre) :
    QWidget(parent)
{
    QLabel * auteurLabel = new QLabel("Auteur :");
    auteur = new QLineEdit(unLivre->getAuteur().c_str(),this);
    QHBoxLayout * auteurLayout = new QHBoxLayout();
    auteurLayout->addWidget(auteurLabel);
    auteurLayout->addWidget(auteur);

    QLabel * titreLabel = new QLabel("Titre :");
    titre = new QLineEdit(unLivre->getTitre().c_str(),this);
    QHBoxLayout * titreLayout = new QHBoxLayout();
    titreLayout->addWidget(titreLabel);
    titreLayout->addWidget(titre);

    QLabel * genreLabel = new QLabel("Genre :");
    genre = new QLineEdit(unLivre->getGenre().c_str(),this);
    QHBoxLayout * genreLayout = new QHBoxLayout();
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genre);

    QLabel * editionLabel = new QLabel("Édition :");
    edition = new QLineEdit(unLivre->getEdition().c_str(),this);
    QHBoxLayout * editionLayout = new QHBoxLayout();
    editionLayout->addWidget(editionLabel);
    editionLayout->addWidget(edition);

    QLabel * dateEcritureLabel = new QLabel("Date d'écriture :");
    dateEcriture = new QLineEdit(unLivre->getDateEcriture().c_str(),this);
    QHBoxLayout * dateEcritureLayout = new QHBoxLayout();
    dateEcritureLayout->addWidget(dateEcritureLabel);
    dateEcritureLayout->addWidget(dateEcriture);

    QLabel * dateParutionLabel = new QLabel("Date de parution :");
    dateParution = new QLineEdit(unLivre->getDateParution().c_str(),this);
    QHBoxLayout * dateParutionLayout = new QHBoxLayout();
    dateParutionLayout->addWidget(dateParutionLabel);
    dateParutionLayout->addWidget(dateParution);

    notes = new QTextEdit(unLivre->getNotes().c_str(),this);
    notesPerso = new QTextEdit();


    QGridLayout * ficheLayout = new QGridLayout();

    // 1ere colonne
    ficheLayout->addLayout(auteurLayout,0,0);
    ficheLayout->addLayout(titreLayout,1,0);
    ficheLayout->addLayout(genreLayout,2,0);
    // 2eme colonne
    ficheLayout->addLayout(editionLayout,0,1);
    ficheLayout->addLayout(dateEcritureLayout,1,1);
    ficheLayout->addLayout(dateParutionLayout,2,1);

    //
    ficheLayout->addWidget(new QLabel(""),3,0);

    // Notes
    QLabel * notesLabel = new QLabel("Notes pratiques:");
    ficheLayout->addWidget(notesLabel,4,0);
    ficheLayout->addWidget(notes,5,0,1,2);
    QLabel * notesPersoLabel = new QLabel("Notes personelles:");
    ficheLayout->addWidget(notesPersoLabel,6,0);
    ficheLayout->addWidget(notesPerso,7,0,1,2);
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
