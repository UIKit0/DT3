/****************************************************************************
** Meta object code from reading C++ file 'EdLevelPropertyBoolField.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Properties/EdLevelPropertyBoolField.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelPropertyBoolField.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelPropertyBoolField_t {
    QByteArrayData data[11];
    char stringdata[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelPropertyBoolField_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelPropertyBoolField_t qt_meta_stringdata_EdLevelPropertyBoolField = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 9),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 7),
QT_MOC_LITERAL(4, 44, 7),
QT_MOC_LITERAL(5, 52, 9),
QT_MOC_LITERAL(6, 62, 8),
QT_MOC_LITERAL(7, 71, 10),
QT_MOC_LITERAL(8, 82, 12),
QT_MOC_LITERAL(9, 95, 13),
QT_MOC_LITERAL(10, 109, 17)
    },
    "EdLevelPropertyBoolField\0doCommand\0\0"
    "command\0recache\0doKeyMenu\0property\0"
    "global_pos\0doReadParams\0doWriteParams\0"
    "doKeyframePressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelPropertyBoolField[] = {

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
       1,    2,   39,    2, 0x05,
       5,    2,   44,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    0,   49,    2, 0x0a,
       9,    0,   50,    2, 0x0a,
      10,    0,   51,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QPointF,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EdLevelPropertyBoolField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelPropertyBoolField *_t = static_cast<EdLevelPropertyBoolField *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->doKeyMenu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 2: _t->doReadParams(); break;
        case 3: _t->doWriteParams(); break;
        case 4: _t->doKeyframePressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelPropertyBoolField::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelPropertyBoolField::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelPropertyBoolField::*_t)(QString , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelPropertyBoolField::doKeyMenu)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject EdLevelPropertyBoolField::staticMetaObject = {
    { &EdLevelPropertyBase::staticMetaObject, qt_meta_stringdata_EdLevelPropertyBoolField.data,
      qt_meta_data_EdLevelPropertyBoolField,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelPropertyBoolField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelPropertyBoolField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelPropertyBoolField.stringdata))
        return static_cast<void*>(const_cast< EdLevelPropertyBoolField*>(this));
    return EdLevelPropertyBase::qt_metacast(_clname);
}

int EdLevelPropertyBoolField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EdLevelPropertyBase::qt_metacall(_c, _id, _a);
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
void EdLevelPropertyBoolField::doCommand(QString _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelPropertyBoolField::doKeyMenu(QString _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
