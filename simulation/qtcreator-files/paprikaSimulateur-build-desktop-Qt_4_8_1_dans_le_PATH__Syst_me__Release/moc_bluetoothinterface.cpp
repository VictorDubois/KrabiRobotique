/****************************************************************************
** Meta object code from reading C++ file 'bluetoothinterface.h'
**
** Created: Thu Feb 11 15:35:17 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/bluetoothinterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bluetoothinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BluetoothInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      34,   20,   19,   19, 0x0a,
      60,   52,   19,   19, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_BluetoothInterface[] = {
    "BluetoothInterface\0\0message,debug\0"
    "log(QString,bool)\0message\0log(QString)\0"
};

void BluetoothInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BluetoothInterface *_t = static_cast<BluetoothInterface *>(_o);
        switch (_id) {
        case 0: _t->log((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BluetoothInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BluetoothInterface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BluetoothInterface,
      qt_meta_data_BluetoothInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BluetoothInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BluetoothInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BluetoothInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BluetoothInterface))
        return static_cast<void*>(const_cast< BluetoothInterface*>(this));
    return QWidget::qt_metacast(_clname);
}

int BluetoothInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
