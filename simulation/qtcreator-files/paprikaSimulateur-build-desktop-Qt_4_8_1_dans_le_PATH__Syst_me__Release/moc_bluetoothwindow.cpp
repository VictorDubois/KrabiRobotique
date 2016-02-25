/****************************************************************************
** Meta object code from reading C++ file 'bluetoothwindow.h'
**
** Created: Thu Feb 11 15:35:17 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/bluetoothwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bluetoothwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BluetoothWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      57,   49,   16,   16, 0x0a,
      80,   49,   16,   16, 0x0a,
     110,   16,   16,   16, 0x0a,
     125,   16,   16,   16, 0x0a,
     143,   16,   16,   16, 0x0a,
     156,   16,   16,   16, 0x0a,
     163,   16,   16,   16, 0x0a,
     172,   16,   16,   16, 0x08,
     184,   16,   16,   16, 0x08,
     199,   16,   16,   16, 0x08,
     211,   16,   16,   16, 0x08,
     236,  226,   16,   16, 0x08,
     267,  262,   16,   16, 0x08,
     299,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BluetoothWindow[] = {
    "BluetoothWindow\0\0addDevice(QBluetoothDeviceInfo)\0"
    "clicked\0on_power_clicked(bool)\0"
    "on_discoverable_clicked(bool)\0"
    "selectDevice()\0connectToDevice()\0"
    "disconnect()\0read()\0update()\0connected()\0"
    "disconnected()\0startScan()\0scanFinished()\0"
    "unlimited\0setGeneralUnlimited(bool)\0"
    "item\0itemActivated(QListWidgetItem*)\0"
    "bluetoothToggle()\0"
};

void BluetoothWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BluetoothWindow *_t = static_cast<BluetoothWindow *>(_o);
        switch (_id) {
        case 0: _t->addDevice((*reinterpret_cast< const QBluetoothDeviceInfo(*)>(_a[1]))); break;
        case 1: _t->on_power_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_discoverable_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->selectDevice(); break;
        case 4: _t->connectToDevice(); break;
        case 5: _t->disconnect(); break;
        case 6: _t->read(); break;
        case 7: _t->update(); break;
        case 8: _t->connected(); break;
        case 9: _t->disconnected(); break;
        case 10: _t->startScan(); break;
        case 11: _t->scanFinished(); break;
        case 12: _t->setGeneralUnlimited((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->itemActivated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: _t->bluetoothToggle(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BluetoothWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BluetoothWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BluetoothWindow,
      qt_meta_data_BluetoothWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BluetoothWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BluetoothWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BluetoothWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BluetoothWindow))
        return static_cast<void*>(const_cast< BluetoothWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int BluetoothWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
