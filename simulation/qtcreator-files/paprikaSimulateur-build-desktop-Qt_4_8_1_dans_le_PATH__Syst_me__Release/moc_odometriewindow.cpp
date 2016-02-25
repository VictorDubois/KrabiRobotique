/****************************************************************************
** Meta object code from reading C++ file 'odometriewindow.h'
**
** Created: Thu Feb 11 15:35:17 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/odometriewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'odometriewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OdometrieWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      31,   16,   16,   16, 0x08,
      48,   16,   16,   16, 0x08,
      68,   16,   16,   16, 0x08,
      88,   16,   16,   16, 0x08,
     112,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_OdometrieWindow[] = {
    "OdometrieWindow\0\0requireSync()\0"
    "resetRelatives()\0setWheelSizeFromX()\0"
    "setWheelSizeFromY()\0setInterAxisFromAngle()\0"
    "apply()\0"
};

void OdometrieWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OdometrieWindow *_t = static_cast<OdometrieWindow *>(_o);
        switch (_id) {
        case 0: _t->requireSync(); break;
        case 1: _t->resetRelatives(); break;
        case 2: _t->setWheelSizeFromX(); break;
        case 3: _t->setWheelSizeFromY(); break;
        case 4: _t->setInterAxisFromAngle(); break;
        case 5: _t->apply(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData OdometrieWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject OdometrieWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_OdometrieWindow,
      qt_meta_data_OdometrieWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OdometrieWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OdometrieWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OdometrieWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OdometrieWindow))
        return static_cast<void*>(const_cast< OdometrieWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int OdometrieWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
