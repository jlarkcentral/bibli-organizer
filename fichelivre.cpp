#include "fichelivre.h"

#include <iostream>

FicheLivre::FicheLivre(QWidget *parent,Livre *unLivre):
    QWidget(parent)
{
    leLivre = unLivre;
    // les champs
    QLabel * auteurLabel = new QLabel("Auteur :");
    auteur = new QLineEdit();
    QHBoxLayout * auteurLayout = new QHBoxLayout();
    auteurLayout->addWidget(auteurLabel);
    auteurLayout->addWidget(auteur);

    QLabel * titreLabel = new QLabel("Titre :   ");
    titre = new QLineEdit();
    QHBoxLayout * titreLayout = new QHBoxLayout();
    titreLayout->addWidget(titreLabel);
    titreLayout->addWidget(titre);

    QLabel * genreLabel = new QLabel("Genre : ");
    genre = new QLineEdit();
    QHBoxLayout * genreLayout = new QHBoxLayout();
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(genre);

    QLabel * editionLabel = new QLabel("Édition :");
    edition = new QLineEdit();
    QHBoxLayout * editionLayout = new QHBoxLayout();
    editionLayout->addWidget(editionLabel);
    editionLayout->addWidget(edition);

    QLabel * dateEcritureLabel = new QLabel("Date d'écriture :   ");
    dateEcriture = new QLineEdit();
    QHBoxLayout * dateEcritureLayout = new QHBoxLayout();
    dateEcritureLayout->addWidget(dateEcritureLabel);
    dateEcritureLayout->addWidget(dateEcriture);

    QLabel * dateParutionLabel = new QLabel("Date de parution :");
    dateParution = new QLineEdit();
    QHBoxLayout * dateParutionLayout = new QHBoxLayout();
    dateParutionLayout->addWidget(dateParutionLabel);
    dateParutionLayout->addWidget(dateParution);

    notes = new QTextEdit();
    notesPerso = new QTextEdit();
    checkLu = new QCheckBox("J'ai lu");
    aLire = new QCheckBox("À lire");

    QGridLayout * ficheLayout = new QGridLayout();

    // 1ere colonne
    ficheLayout->addLayout(auteurLayout,0,0);
    ficheLayout->addLayout(titreLayout,1,0);
    ficheLayout->addLayout(genreLayout,2,0);
    // 2eme colonne
    ficheLayout->addLayout(editionLayout,0,1);
    ficheLayout->addLayout(dateEcritureLayout,1,1);
    ficheLayout->addLayout(dateParutionLayout,2,1);

    QHBoxLayout * checkLayout = new QHBoxLayout();
    // J ai lu
    checkLu->setFocusPolicy(Qt::NoFocus);
    checkLu->setLayoutDirection(Qt::LayoutDirection(Qt::RightToLeft));
    checkLayout->addWidget(checkLu);

    // J ai lu
    aLire->setFocusPolicy(Qt::NoFocus);
    aLire->setLayoutDirection(Qt::LayoutDirection(Qt::RightToLeft));
    checkLayout->addWidget(aLire);

    ficheLayout->addLayout(checkLayout,6,1);

    // Notes
    QLabel * notesLabel = new QLabel("Notes pratiques:");
    ficheLayout->addWidget(notesLabel,4,0);
    ficheLayout->addWidget(notes,5,0,1,2);
    QLabel * notesPersoLabel = new QLabel("Notes personelles:");
    ficheLayout->addWidget(notesPersoLabel,6,0);
    ficheLayout->addWidget(notesPerso,7,0,1,2);
    this->setLayout(ficheLayout);

    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(changeTreeItemTitre(QString)));

    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(changeLivreTitre(QString)));
    QObject::connect(auteur,SIGNAL(textEdited(QString)),this,SLOT(changeLivreAuteur(QString)));
    QObject::connect(genre,SIGNAL(textEdited(QString)),this,SLOT(changeLivreGenre(QString)));
    QObject::connect(edition,SIGNAL(textEdited(QString)),this,SLOT(changeLivreEdition(QString)));
    QObject::connect(dateEcriture,SIGNAL(textEdited(QString)),this,SLOT(changeLivreDateEcriture(QString)));
    QObject::connect(dateParution,SIGNAL(textEdited(QString)),this,SLOT(changeLivreDateParution(QString)));
    QObject::connect(notes,SIGNAL(textChanged()),this,SLOT(changeLivreNotes()));
    QObject::connect(notesPerso,SIGNAL(textChanged()),this,SLOT(changeLivreNotesPerso()));
    QObject::connect(checkLu,SIGNAL(toggled(bool)),this,SLOT(changeLivreLu(bool)));
    QObject::connect(aLire,SIGNAL(toggled(bool)),this,SLOT(changeLivreALire(bool)));

}

void FicheLivre::setLivre(Livre *unLivre)
{
    leLivre = unLivre;
}

void FicheLivre::setAuteur(QString unAuteur)
{
    auteur->setText(unAuteur);
}

void FicheLivre::setTitre(QString unTitre)
{
    titre->setText(unTitre);
}

void FicheLivre::setGenre(QString unGenre)
{
    genre->setText(unGenre);
}

void FicheLivre::setEdition(QString uneEdition)
{
    edition->setText(uneEdition);
}

void FicheLivre::setDateEcriture(QString uneDate)
{
    dateEcriture->setText(uneDate);
}

void FicheLivre::setDateParution(QString uneDate)
{
    dateParution->setText(uneDate);
}

void FicheLivre::setNotes(QString desNotes)
{
    notes->setText(desNotes);
}

void FicheLivre::setNotesPerso(QString desNotes)
{
    notesPerso->setText(desNotes);
}

void FicheLivre::setEditable(bool b)
{
    editable = b;
    auteur->setReadOnly(!b);
    titre->setReadOnly(!b);
    genre->setReadOnly(!b);
    edition->setReadOnly(!b);
    dateEcriture->setReadOnly(!b);
    dateParution->setReadOnly(!b);
    notes->setReadOnly(!b);
    notesPerso->setReadOnly(!b);
    //checkLu->setEnabled(b);
}

void FicheLivre::setItemCourant(QTreeWidgetItem *item)
{
    itemCourant = item;
}

void FicheLivre::setCheckLu(bool lu)
{
    checkLu->setChecked(lu);
}

void FicheLivre::setCheckALire(bool lire)
{
    aLire->setChecked(lire);
}

bool FicheLivre::getCheckLu()
{
    return checkLu->isChecked();
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

void FicheLivre::changeTreeItemTitre(QString newTitre)
{
    if(itemCourant && itemCourant->data(1,0) == 0){
        itemCourant->setText(0,newTitre);
        itemCourant->treeWidget()->sortItems(0,Qt::AscendingOrder);
    }
}

void FicheLivre::changeLivreTitre(QString qs)
{
    leLivre->setTitre(qs.toStdString());
}

void FicheLivre::changeLivreAuteur(QString qs)
{
    leLivre->setAuteur(qs.toStdString());
}

void FicheLivre::changeLivreGenre(QString qs)
{
    leLivre->setGenre(qs.toStdString());
}

void FicheLivre::changeLivreEdition(QString qs)
{
    leLivre->setEdition(qs.toStdString());
}

void FicheLivre::changeLivreDateEcriture(QString qs)
{
    leLivre->setDateEcriture(qs.toStdString());
}

void FicheLivre::changeLivreDateParution(QString qs)
{
    leLivre->setDateParution(qs.toStdString());
}

void FicheLivre::changeLivreNotes()
{
    if(notes->hasFocus()){
        leLivre->setNotes(notes->toPlainText().toStdString());
    }
}

void FicheLivre::changeLivreNotesPerso()
{
    if(notesPerso->hasFocus()){
        leLivre->setNotesPerso(notesPerso->toPlainText().toStdString());
    }
}

void FicheLivre::changeLivreLu(bool lu)
{
    string estLu = (lu)? "y" : "n";
    leLivre->setLu(estLu);
    if(lu){
        emitSetLu();
    }
    else emitSetNonLu();
}

void FicheLivre::changeLivreALire(bool lu)
{
    string aLire = (lu)? "y" : "n";
    leLivre->setALire(aLire);
    if(lu){
        emitSetALire();
    }
    else emitSetNonALire();
}

void FicheLivre::focusOnTitre()
{
    titre->setFocus();
}

void FicheLivre::emitSetLu()
{
    emit setLu(true);
}

void FicheLivre::emitSetNonLu()
{
    emit setLu(false);
}

void FicheLivre::emitSetALire()
{
    emit setALire(itemCourant, true);
}

void FicheLivre::emitSetNonALire()
{
    emit setALire(itemCourant, false);
}
