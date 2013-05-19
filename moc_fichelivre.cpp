/****************************************************************************
** Meta object code from reading C++ file 'fichelivre.h'
**
** Created: Sun May 19 15:27:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../bibli-organizer/fichelivre.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fichelivre.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FicheLivre[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   12,   11,   11, 0x05,
      33,   26,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      74,   65,   11,   11, 0x0a,
     103,   12,   11,   11, 0x0a,
     124,  121,   11,   11, 0x0a,
     150,  121,   11,   11, 0x0a,
     177,  121,   11,   11, 0x0a,
     203,  121,   11,   11, 0x0a,
     231,  121,   11,   11, 0x0a,
     264,  121,   11,   11, 0x0a,
     297,   11,   11,   11, 0x0a,
     316,   11,   11,   11, 0x0a,
     343,  340,   11,   11, 0x0a,
     365,  363,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FicheLivre[] = {
    "FicheLivre\0\0b\0setLu(bool)\0item,b\0"
    "setALire(QTreeWidgetItem*,bool)\0"
    "newTitre\0changeTreeItemTitre(QString)\0"
    "setEditable(bool)\0qs\0changeLivreTitre(QString)\0"
    "changeLivreAuteur(QString)\0"
    "changeLivreGenre(QString)\0"
    "changeLivreEdition(QString)\0"
    "changeLivreDateEcriture(QString)\0"
    "changeLivreDateParution(QString)\0"
    "changeLivreNotes()\0changeLivreNotesPerso()\0"
    "lu\0changeLivreLu(bool)\0c\0"
    "changeLivreALire(bool)\0"
};

void FicheLivre::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FicheLivre *_t = static_cast<FicheLivre *>(_o);
        switch (_id) {
        case 0: _t->setLu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setALire((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->changeTreeItemTitre((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setEditable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->changeLivreTitre((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->changeLivreAuteur((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->changeLivreGenre((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->changeLivreEdition((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->changeLivreDateEcriture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->changeLivreDateParution((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->changeLivreNotes(); break;
        case 11: _t->changeLivreNotesPerso(); break;
        case 12: _t->changeLivreLu((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->changeLivreALire((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FicheLivre::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FicheLivre::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FicheLivre,
      qt_meta_data_FicheLivre, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FicheLivre::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FicheLivre::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FicheLivre::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FicheLivre))
        return static_cast<void*>(const_cast< FicheLivre*>(this));
    return QWidget::qt_metacast(_clname);
}

int FicheLivre::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void FicheLivre::setLu(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FicheLivre::setALire(QTreeWidgetItem * _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
