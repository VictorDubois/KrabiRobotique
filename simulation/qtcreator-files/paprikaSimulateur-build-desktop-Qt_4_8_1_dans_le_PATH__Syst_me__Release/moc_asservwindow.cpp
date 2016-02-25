/****************************************************************************
** Meta object code from reading C++ file 'asservwindow.h'
**
** Created: Thu Feb 11 15:35:18 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/asservwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'asservwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AsservWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x0a,
      63,   14,   13,   13, 0x0a,
     105,   13,   13,   13, 0x0a,
     126,   13,   13,   13, 0x0a,
     146,   13,   13,   13, 0x0a,
     156,   13,   13,   13, 0x0a,
     167,   13,   13,   13, 0x08,
     189,   13,   13,   13, 0x08,
     209,   13,   13,   13, 0x08,
     231,   13,   13,   13, 0x08,
     251,   13,   13,   13, 0x08,
     275,   13,   13,   13, 0x08,
     305,  298,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AsservWindow[] = {
    "AsservWindow\0\0p,i,d\0"
    "settingsReceivedAngular(float,float,float)\0"
    "settingsReceivedLinear(float,float,float)\0"
    "requireSyncAngular()\0requireSyncLinear()\0"
    "runTest()\0stopTest()\0on_linQuery_clicked()\0"
    "on_linSet_clicked()\0on_angQuery_clicked()\0"
    "on_angSet_clicked()\0on_stopButton_clicked()\0"
    "on_runButton_clicked()\0cycles\0"
    "on_spinBox_valueChanged(int)\0"
};

void AsservWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AsservWindow *_t = static_cast<AsservWindow *>(_o);
        switch (_id) {
        case 0: _t->settingsReceivedAngular((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->settingsReceivedLinear((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 2: _t->requireSyncAngular(); break;
        case 3: _t->requireSyncLinear(); break;
        case 4: _t->runTest(); break;
        case 5: _t->stopTest(); break;
        case 6: _t->on_linQuery_clicked(); break;
        case 7: _t->on_linSet_clicked(); break;
        case 8: _t->on_angQuery_clicked(); break;
        case 9: _t->on_angSet_clicked(); break;
        case 10: _t->on_stopButton_clicked(); break;
        case 11: _t->on_runButton_clicked(); break;
        case 12: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AsservWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AsservWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AsservWindow,
      qt_meta_data_AsservWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AsservWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AsservWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AsservWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AsservWindow))
        return static_cast<void*>(const_cast< AsservWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int AsservWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
