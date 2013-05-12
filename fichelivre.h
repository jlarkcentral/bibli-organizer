#ifndef FICHELIVRE_H
#define FICHELIVRE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextDocument>
#include <QGridLayout>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QCheckBox>

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
    bool getCheckLu();
    bool isEditable();
    void setCheckLu(bool lu);
    void setLivre(Livre * unLivre);
    void setTitre(QString unTitre);
    void setAuteur(QString unAuteur);
    void setNotes(QString desNotes);
    void setNotesPerso(QString desNotes);
    void setGenre(QString unGenre);
    void setEdition(QString uneEdition);
    void setDateEcriture(QString uneDate);
    void setDateParution(QString uneDate);
    void setItemCourant(QTreeWidgetItem * item);
    void focusOnTitre();

    QLineEdit * titre;

private:
    //QLineEdit * titre;
    QLineEdit * auteur;
    QLineEdit * genre;
    QLineEdit * edition;
    QLineEdit * dateParution;
    QLineEdit * dateEcriture;
    QTextEdit * notes;
    QTextEdit * notesPerso;
    bool editable;
    QTreeWidgetItem * itemCourant;
    Livre * leLivre;
    QCheckBox * checkLu;
    
signals:
    
public slots:
    void changeTreeItemTitre(QString newTitre);
    void setEditable(bool b);
    void changeLivreTitre(QString qs);
    void changeLivreAuteur(QString qs);
    void changeLivreGenre(QString qs);
    void changeLivreEdition(QString qs);
    void changeLivreDateEcriture(QString qs);
    void changeLivreDateParution(QString qs);
    void changeLivreNotes();
    void changeLivreNotesPerso();
    void changeLivreLu(bool lu);
};

#endif // FICHELIVRE_H
