/****************************************************************************
** Meta object code from reading C++ file 'bdeletedialog.h'
**
** Created: Sun Jun 15 18:42:31 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "bdeletedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bdeletedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_BDeleteDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      27,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_BDeleteDialog[] = {
    "BDeleteDialog\0\0deteleOne()\0deteleTwo()\0"
};

const QMetaObject BDeleteDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BDeleteDialog,
      qt_meta_data_BDeleteDialog, 0 }
};

const QMetaObject *BDeleteDialog::metaObject() const
{
    return &staticMetaObject;
}

void *BDeleteDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BDeleteDialog))
	return static_cast<void*>(const_cast< BDeleteDialog*>(this));
    if (!strcmp(_clname, "Ui::BDeleteDialog"))
	return static_cast< Ui::BDeleteDialog*>(const_cast< BDeleteDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BDeleteDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: deteleOne(); break;
        case 1: deteleTwo(); break;
        }
        _id -= 2;
    }
    return _id;
}
