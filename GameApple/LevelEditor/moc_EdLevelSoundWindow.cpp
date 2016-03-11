/****************************************************************************
** Meta object code from reading C++ file 'EdLevelSoundWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Sound/EdLevelSoundWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelSoundWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelSoundWindow_t {
    QByteArrayData data[14];
    char stringdata[211];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelSoundWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelSoundWindow_t qt_meta_stringdata_EdLevelSoundWindow = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 9),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 7),
QT_MOC_LITERAL(4, 38, 9),
QT_MOC_LITERAL(5, 48, 26),
QT_MOC_LITERAL(6, 75, 4),
QT_MOC_LITERAL(7, 80, 12),
QT_MOC_LITERAL(8, 93, 14),
QT_MOC_LITERAL(9, 108, 19),
QT_MOC_LITERAL(10, 128, 18),
QT_MOC_LITERAL(11, 147, 37),
QT_MOC_LITERAL(12, 185, 14),
QT_MOC_LITERAL(13, 200, 9)
    },
    "EdLevelSoundWindow\0doCommand\0\0command\0"
    "onAddNode\0std::shared_ptr<WorldNode>\0"
    "node\0onRemoveNode\0onRefreshSound\0"
    "onRefreshProperties\0onSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0onCommand\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelSoundWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a,
       7,    1,   55,    2, 0x0a,
       8,    0,   58,    2, 0x0a,
       9,    0,   59,    2, 0x0a,
      10,    1,   60,    2, 0x0a,
      13,    1,   63,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void EdLevelSoundWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelSoundWindow *_t = static_cast<EdLevelSoundWindow *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onAddNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 2: _t->onRemoveNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 3: _t->onRefreshSound(); break;
        case 4: _t->onRefreshProperties(); break;
        case 5: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 6: _t->onCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelSoundWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelSoundWindow::doCommand)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EdLevelSoundWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EdLevelSoundWindow.data,
      qt_meta_data_EdLevelSoundWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelSoundWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelSoundWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelSoundWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelSoundWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int EdLevelSoundWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void EdLevelSoundWindow::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
