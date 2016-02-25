/****************************************************************************
** Meta object code from reading C++ file 'watchwindow.h'
**
** Created: Thu Feb 11 15:35:18 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../stm32/include/simul/watchwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'watchwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WatchWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      31,   12,   12,   12, 0x08,
      45,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_WatchWindow[] = {
    "WatchWindow\0\0checkBoxChanged()\0"
    "deselectAll()\0requireSync()\0"
};

void WatchWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WatchWindow *_t = static_cast<WatchWindow *>(_o);
        switch (_id) {
        case 0: _t->checkBoxChanged(); break;
        case 1: _t->deselectAll(); break;
        case 2: _t->requireSync(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WatchWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WatchWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WatchWindow,
      qt_meta_data_WatchWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WatchWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WatchWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WatchWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WatchWindow))
        return static_cast<void*>(const_cast< WatchWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int WatchWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
