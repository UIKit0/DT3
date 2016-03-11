/****************************************************************************
** Meta object code from reading C++ file 'EdLevelPropertiesWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Properties/EdLevelPropertiesWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelPropertiesWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelPropertiesWindow_t {
    QByteArrayData data[24];
    char stringdata[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelPropertiesWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelPropertiesWindow_t qt_meta_stringdata_EdLevelPropertiesWindow = {
    {
QT_MOC_LITERAL(0, 0, 23),
QT_MOC_LITERAL(1, 24, 9),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 7),
QT_MOC_LITERAL(4, 43, 11),
QT_MOC_LITERAL(5, 55, 19),
QT_MOC_LITERAL(6, 75, 19),
QT_MOC_LITERAL(7, 95, 18),
QT_MOC_LITERAL(8, 114, 37),
QT_MOC_LITERAL(9, 152, 14),
QT_MOC_LITERAL(10, 167, 14),
QT_MOC_LITERAL(11, 182, 14),
QT_MOC_LITERAL(12, 197, 4),
QT_MOC_LITERAL(13, 202, 17),
QT_MOC_LITERAL(14, 220, 9),
QT_MOC_LITERAL(15, 230, 7),
QT_MOC_LITERAL(16, 238, 9),
QT_MOC_LITERAL(17, 248, 8),
QT_MOC_LITERAL(18, 257, 10),
QT_MOC_LITERAL(19, 268, 8),
QT_MOC_LITERAL(20, 277, 14),
QT_MOC_LITERAL(21, 292, 3),
QT_MOC_LITERAL(22, 296, 4),
QT_MOC_LITERAL(23, 301, 5)
    },
    "EdLevelPropertiesWindow\0doCommand\0\0"
    "command\0doUndoBlock\0doReadAllProperties\0"
    "onRefreshProperties\0onSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0onAddComponent\0"
    "ComponentBase*\0node\0onRemoveComponent\0"
    "onCommand\0recache\0onKeyMenu\0property\0"
    "global_pos\0onSetKey\0onClearAllKeys\0"
    "cut\0copy\0paste\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelPropertiesWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x05,
       4,    0,   87,    2, 0x05,
       5,    0,   88,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    0,   89,    2, 0x0a,
       7,    1,   90,    2, 0x0a,
      10,    1,   93,    2, 0x0a,
      13,    1,   96,    2, 0x0a,
      14,    2,   99,    2, 0x0a,
      16,    2,  104,    2, 0x0a,
      19,    0,  109,    2, 0x0a,
      20,    0,  110,    2, 0x0a,
      21,    0,  111,    2, 0x0a,
      22,    0,  112,    2, 0x0a,
      23,    0,  113,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QPointF,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EdLevelPropertiesWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelPropertiesWindow *_t = static_cast<EdLevelPropertiesWindow *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->doReadAllProperties(); break;
        case 3: _t->onRefreshProperties(); break;
        case 4: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 5: _t->onAddComponent((*reinterpret_cast< ComponentBase*(*)>(_a[1]))); break;
        case 6: _t->onRemoveComponent((*reinterpret_cast< ComponentBase*(*)>(_a[1]))); break;
        case 7: _t->onCommand((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->onKeyMenu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 9: _t->onSetKey(); break;
        case 10: _t->onClearAllKeys(); break;
        case 11: _t->cut(); break;
        case 12: _t->copy(); break;
        case 13: _t->paste(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelPropertiesWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelPropertiesWindow::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelPropertiesWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelPropertiesWindow::doUndoBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (EdLevelPropertiesWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelPropertiesWindow::doReadAllProperties)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject EdLevelPropertiesWindow::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_EdLevelPropertiesWindow.data,
      qt_meta_data_EdLevelPropertiesWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelPropertiesWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelPropertiesWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelPropertiesWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelPropertiesWindow*>(this));
    return QListWidget::qt_metacast(_clname);
}

int EdLevelPropertiesWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void EdLevelPropertiesWindow::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelPropertiesWindow::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EdLevelPropertiesWindow::doReadAllProperties()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
