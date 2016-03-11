/****************************************************************************
** Meta object code from reading C++ file 'EdLevelScriptNodeStandard.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Scripting/EdLevelScriptNodeStandard.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelScriptNodeStandard.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelScriptNodeStandard_t {
    QByteArrayData data[9];
    char stringdata[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelScriptNodeStandard_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelScriptNodeStandard_t qt_meta_stringdata_EdLevelScriptNodeStandard = {
    {
QT_MOC_LITERAL(0, 0, 25),
QT_MOC_LITERAL(1, 26, 17),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 26),
QT_MOC_LITERAL(4, 72, 4),
QT_MOC_LITERAL(5, 77, 10),
QT_MOC_LITERAL(6, 88, 22),
QT_MOC_LITERAL(7, 111, 30),
QT_MOC_LITERAL(8, 142, 9)
    },
    "EdLevelScriptNodeStandard\0doNodeContextMenu\0"
    "\0std::shared_ptr<WorldNode>\0node\0"
    "global_pos\0doComponentContextMenu\0"
    "std::shared_ptr<ComponentBase>\0component\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelScriptNodeStandard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x05,
       6,    2,   29,    2, 0x05,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QPointF,    8,    5,

       0        // eod
};

void EdLevelScriptNodeStandard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelScriptNodeStandard *_t = static_cast<EdLevelScriptNodeStandard *>(_o);
        switch (_id) {
        case 0: _t->doNodeContextMenu((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 1: _t->doComponentContextMenu((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelScriptNodeStandard::*_t)(std::shared_ptr<WorldNode> , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptNodeStandard::doNodeContextMenu)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelScriptNodeStandard::*_t)(std::shared_ptr<ComponentBase> , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptNodeStandard::doComponentContextMenu)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject EdLevelScriptNodeStandard::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EdLevelScriptNodeStandard.data,
      qt_meta_data_EdLevelScriptNodeStandard,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelScriptNodeStandard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelScriptNodeStandard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelScriptNodeStandard.stringdata))
        return static_cast<void*>(const_cast< EdLevelScriptNodeStandard*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< EdLevelScriptNodeStandard*>(this));
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< EdLevelScriptNodeStandard*>(this));
    return QObject::qt_metacast(_clname);
}

int EdLevelScriptNodeStandard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void EdLevelScriptNodeStandard::doNodeContextMenu(std::shared_ptr<WorldNode> _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelScriptNodeStandard::doComponentContextMenu(std::shared_ptr<ComponentBase> _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
