/****************************************************************************
** Meta object code from reading C++ file 'EdLevelWorldWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/World/EdLevelWorldWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelWorldWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelWorldWindow_t {
    QByteArrayData data[18];
    char stringdata[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelWorldWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelWorldWindow_t qt_meta_stringdata_EdLevelWorldWindow = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 18),
QT_MOC_LITERAL(2, 38, 0),
QT_MOC_LITERAL(3, 39, 37),
QT_MOC_LITERAL(4, 77, 14),
QT_MOC_LITERAL(5, 92, 11),
QT_MOC_LITERAL(6, 104, 14),
QT_MOC_LITERAL(7, 119, 5),
QT_MOC_LITERAL(8, 125, 18),
QT_MOC_LITERAL(9, 144, 14),
QT_MOC_LITERAL(10, 159, 18),
QT_MOC_LITERAL(11, 178, 11),
QT_MOC_LITERAL(12, 190, 9),
QT_MOC_LITERAL(13, 200, 12),
QT_MOC_LITERAL(14, 213, 11),
QT_MOC_LITERAL(15, 225, 17),
QT_MOC_LITERAL(16, 243, 12),
QT_MOC_LITERAL(17, 256, 5)
    },
    "EdLevelWorldWindow\0doSelectionChanged\0"
    "\0std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0doUndoBlock\0onChangeCamera\0"
    "index\0onChangeResolution\0onRefreshWorld\0"
    "onSelectionChanged\0onArrowTool\0onPanTool\0"
    "onRotateTool\0onScaleTool\0onSelectComponent\0"
    "onChangeGrid\0state\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelWorldWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x05,
       5,    0,   77,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       6,    1,   78,    2, 0x0a,
       8,    1,   81,    2, 0x0a,
       9,    0,   84,    2, 0x0a,
      10,    1,   85,    2, 0x0a,
      11,    0,   88,    2, 0x0a,
      12,    0,   89,    2, 0x0a,
      13,    0,   90,    2, 0x0a,
      14,    0,   91,    2, 0x0a,
      15,    0,   92,    2, 0x0a,
      16,    1,   93,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void EdLevelWorldWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelWorldWindow *_t = static_cast<EdLevelWorldWindow *>(_o);
        switch (_id) {
        case 0: _t->doSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->onChangeCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onChangeResolution((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onRefreshWorld(); break;
        case 5: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 6: _t->onArrowTool(); break;
        case 7: _t->onPanTool(); break;
        case 8: _t->onRotateTool(); break;
        case 9: _t->onScaleTool(); break;
        case 10: _t->onSelectComponent(); break;
        case 11: _t->onChangeGrid((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelWorldWindow::*_t)(const std::list<std::shared_ptr<PlugNode> > & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelWorldWindow::doSelectionChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelWorldWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelWorldWindow::doUndoBlock)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject EdLevelWorldWindow::staticMetaObject = {
    { &EdLevelToolWindow::staticMetaObject, qt_meta_stringdata_EdLevelWorldWindow.data,
      qt_meta_data_EdLevelWorldWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelWorldWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelWorldWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelWorldWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelWorldWindow*>(this));
    return EdLevelToolWindow::qt_metacast(_clname);
}

int EdLevelWorldWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EdLevelToolWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void EdLevelWorldWindow::doSelectionChanged(const std::list<std::shared_ptr<PlugNode> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelWorldWindow::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
