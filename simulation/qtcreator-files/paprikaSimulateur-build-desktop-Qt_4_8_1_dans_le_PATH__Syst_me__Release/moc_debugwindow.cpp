/****************************************************************************
** Meta object code from reading C++ file 'debugwindow.h'
**
** Created: Thu Feb 11 15:35:16 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/debugwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debugwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DebugWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x0a,
      47,   13,   12,   12, 0x0a,
      79,   13,   12,   12, 0x0a,
     108,   13,   12,   12, 0x0a,
     134,   13,   12,   12, 0x0a,
     159,   13,   12,   12, 0x0a,
     184,   12,   12,   12, 0x0a,
     193,   12,   12,   12, 0x0a,
     213,   12,   12,   12, 0x0a,
     236,   12,   12,   12, 0x0a,
     260,   12,   12,   12, 0x0a,
     274,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DebugWindow[] = {
    "DebugWindow\0\0show\0displayBluetoothWindow(bool)\0"
    "displayBluetoothInterface(bool)\0"
    "displayOdometrieWindow(bool)\0"
    "displayAsservWindow(bool)\0"
    "displaySharpWindow(bool)\0"
    "displayWatchWindow(bool)\0update()\0"
    "perspectiveAsserv()\0perspectiveOdometrie()\0"
    "perspectiveSimulateur()\0hideWindows()\0"
    "clearPlots()\0"
};

void DebugWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DebugWindow *_t = static_cast<DebugWindow *>(_o);
        switch (_id) {
        case 0: _t->displayBluetoothWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->displayBluetoothInterface((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->displayOdometrieWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->displayAsservWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->displaySharpWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->displayWatchWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->update(); break;
        case 7: _t->perspectiveAsserv(); break;
        case 8: _t->perspectiveOdometrie(); break;
        case 9: _t->perspectiveSimulateur(); break;
        case 10: _t->hideWindows(); break;
        case 11: _t->clearPlots(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DebugWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DebugWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DebugWindow,
      qt_meta_data_DebugWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DebugWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DebugWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DebugWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DebugWindow))
        return static_cast<void*>(const_cast< DebugWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int DebugWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
