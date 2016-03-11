/****************************************************************************
** Meta object code from reading C++ file 'EdLevelSoundBus.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Sound/EdLevelSoundBus.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelSoundBus.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelSoundBus_t {
    QByteArrayData data[10];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelSoundBus_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelSoundBus_t qt_meta_stringdata_EdLevelSoundBus = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 9),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 7),
QT_MOC_LITERAL(4, 35, 11),
QT_MOC_LITERAL(5, 47, 11),
QT_MOC_LITERAL(6, 59, 16),
QT_MOC_LITERAL(7, 76, 11),
QT_MOC_LITERAL(8, 88, 16),
QT_MOC_LITERAL(9, 105, 4)
    },
    "EdLevelSoundBus\0doCommand\0\0command\0"
    "doUndoBlock\0nameChanged\0gainKnobsChanged\0"
    "listChanged\0QListWidgetItem*\0item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelSoundBus[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x05,
       4,    0,   42,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   43,    2, 0x08,
       6,    0,   44,    2, 0x08,
       7,    1,   45,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void EdLevelSoundBus::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelSoundBus *_t = static_cast<EdLevelSoundBus *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->nameChanged(); break;
        case 3: _t->gainKnobsChanged(); break;
        case 4: _t->listChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelSoundBus::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelSoundBus::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelSoundBus::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelSoundBus::doUndoBlock)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject EdLevelSoundBus::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EdLevelSoundBus.data,
      qt_meta_data_EdLevelSoundBus,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelSoundBus::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelSoundBus::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelSoundBus.stringdata))
        return static_cast<void*>(const_cast< EdLevelSoundBus*>(this));
    return QWidget::qt_metacast(_clname);
}

int EdLevelSoundBus::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void EdLevelSoundBus::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelSoundBus::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
