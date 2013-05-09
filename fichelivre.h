#ifndef FICHELIVRE_H
#define FICHELIVRE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextDocument>
#include <QGridLayout>
#include <QLabel>
#include <QTreeWidgetItem>

#include "livre.h"

class FicheLivre : public QWidget
{
    Q_OBJECT
public:
    FicheLivre(QWidget *parent = 0, Livre * unLivre = 0);

    QString getTitre();
    QString getAuteur();
    QString getNotes();
    QString getGenre();
    QString getEdition();
    QString getDateEcriture();
    QString getDateParution();
    bool isEditable();

    void setTitre(QString unTitre);
    void setAuteur(QString unAuteur);
    void setNotes(QString desNotes);
    void setGenre(QString unGenre);
    void setEdition(QString uneEdition);
    void setDateEcriture(QString uneDate);
    void setDateParution(QString uneDate);
    void setEditable(bool b);
    void setItemCourant(QTreeWidgetItem * item);

private:
    QLineEdit * titre;
    QLineEdit * auteur;
    QLineEdit * genre;
    QLineEdit * edition;
    QLineEdit * dateParution;
    QLineEdit * dateEcriture;
    QTextEdit * notes;
    QTextEdit * notesPerso;
    bool editable;
    QTreeWidgetItem * itemCourant;
    
signals:
    
public slots:
    void changeTreeItemTitre(QString newTitre);
    
};

#endif // FICHELIVRE_H
