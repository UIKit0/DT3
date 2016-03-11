/****************************************************************************
** Meta object code from reading C++ file 'EdLevelScriptWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Scripting/EdLevelScriptWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelScriptWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelScriptWindow_t {
    QByteArrayData data[45];
    char stringdata[687];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelScriptWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelScriptWindow_t qt_meta_stringdata_EdLevelScriptWindow = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 9),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 7),
QT_MOC_LITERAL(4, 39, 11),
QT_MOC_LITERAL(5, 51, 15),
QT_MOC_LITERAL(6, 67, 18),
QT_MOC_LITERAL(7, 86, 37),
QT_MOC_LITERAL(8, 124, 14),
QT_MOC_LITERAL(9, 139, 17),
QT_MOC_LITERAL(10, 157, 26),
QT_MOC_LITERAL(11, 184, 4),
QT_MOC_LITERAL(12, 189, 10),
QT_MOC_LITERAL(13, 200, 22),
QT_MOC_LITERAL(14, 223, 30),
QT_MOC_LITERAL(15, 254, 9),
QT_MOC_LITERAL(16, 264, 9),
QT_MOC_LITERAL(17, 274, 12),
QT_MOC_LITERAL(18, 287, 14),
QT_MOC_LITERAL(19, 302, 10),
QT_MOC_LITERAL(20, 313, 10),
QT_MOC_LITERAL(21, 324, 10),
QT_MOC_LITERAL(22, 335, 22),
QT_MOC_LITERAL(23, 358, 5),
QT_MOC_LITERAL(24, 364, 13),
QT_MOC_LITERAL(25, 378, 14),
QT_MOC_LITERAL(26, 393, 17),
QT_MOC_LITERAL(27, 411, 13),
QT_MOC_LITERAL(28, 425, 9),
QT_MOC_LITERAL(29, 435, 8),
QT_MOC_LITERAL(30, 444, 8),
QT_MOC_LITERAL(31, 453, 16),
QT_MOC_LITERAL(32, 470, 14),
QT_MOC_LITERAL(33, 485, 6),
QT_MOC_LITERAL(34, 492, 17),
QT_MOC_LITERAL(35, 510, 16),
QT_MOC_LITERAL(36, 527, 15),
QT_MOC_LITERAL(37, 543, 18),
QT_MOC_LITERAL(38, 562, 17),
QT_MOC_LITERAL(39, 580, 22),
QT_MOC_LITERAL(40, 603, 12),
QT_MOC_LITERAL(41, 616, 13),
QT_MOC_LITERAL(42, 630, 20),
QT_MOC_LITERAL(43, 651, 20),
QT_MOC_LITERAL(44, 672, 13)
    },
    "EdLevelScriptWindow\0doCommand\0\0command\0"
    "doUndoBlock\0doRefreshScript\0"
    "doSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0doNodeContextMenu\0"
    "std::shared_ptr<WorldNode>\0node\0"
    "global_pos\0doComponentContextMenu\0"
    "std::shared_ptr<ComponentBase>\0component\0"
    "onAddNode\0onRemoveNode\0onReparentNode\0"
    "old_parent\0new_parent\0onAddGroup\0"
    "std::shared_ptr<Group>\0group\0onRemoveGroup\0"
    "onAddComponent\0onRemoveComponent\0"
    "onConnectPlug\0PlugBase*\0outgoing\0"
    "incoming\0onDisconnectPlug\0onConnectEvent\0"
    "Event*\0onDisconnectEvent\0selectionChanged\0"
    "onRefreshScript\0onSelectionChanged\0"
    "onNodeContextMenu\0onComponentContextMenu\0"
    "onAutoScroll\0onScriptAlign\0"
    "onScriptToggleValues\0onScriptAddToLibrary\0"
    "onScriptColor\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelScriptWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  149,    2, 0x05,
       4,    0,  152,    2, 0x05,
       5,    0,  153,    2, 0x05,
       6,    1,  154,    2, 0x05,
       9,    2,  157,    2, 0x05,
      13,    2,  162,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      16,    1,  167,    2, 0x0a,
      17,    1,  170,    2, 0x0a,
      18,    3,  173,    2, 0x0a,
      21,    1,  180,    2, 0x0a,
      24,    1,  183,    2, 0x0a,
      25,    1,  186,    2, 0x0a,
      26,    1,  189,    2, 0x0a,
      27,    2,  192,    2, 0x0a,
      31,    2,  197,    2, 0x0a,
      32,    2,  202,    2, 0x0a,
      34,    2,  207,    2, 0x0a,
      35,    0,  212,    2, 0x0a,
      36,    0,  213,    2, 0x0a,
      37,    1,  214,    2, 0x0a,
      38,    2,  217,    2, 0x0a,
      39,    2,  222,    2, 0x0a,
      40,    0,  227,    2, 0x0a,
      41,    0,  228,    2, 0x0a,
      42,    0,  229,    2, 0x0a,
      43,    0,  230,    2, 0x0a,
      44,    0,  231,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QPointF,   11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QPointF,   15,   12,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 10,   11,   19,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void, 0x80000000 | 14,   11,
    QMetaType::Void, 0x80000000 | 14,   11,
    QMetaType::Void, 0x80000000 | 28, 0x80000000 | 28,   29,   30,
    QMetaType::Void, 0x80000000 | 28, 0x80000000 | 28,   29,   30,
    QMetaType::Void, 0x80000000 | 33, 0x80000000 | 33,   29,   30,
    QMetaType::Void, 0x80000000 | 33, 0x80000000 | 33,   29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QPointF,   11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QPointF,   15,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,

       0        // eod
};

void EdLevelScriptWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelScriptWindow *_t = static_cast<EdLevelScriptWindow *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->doRefreshScript(); break;
        case 3: _t->doSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 4: _t->doNodeContextMenu((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 5: _t->doComponentContextMenu((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 6: _t->onAddNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 7: _t->onRemoveNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 8: _t->onReparentNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[3]))); break;
        case 9: _t->onAddGroup((*reinterpret_cast< std::shared_ptr<Group>(*)>(_a[1]))); break;
        case 10: _t->onRemoveGroup((*reinterpret_cast< std::shared_ptr<Group>(*)>(_a[1]))); break;
        case 11: _t->onAddComponent((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1]))); break;
        case 12: _t->onRemoveComponent((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1]))); break;
        case 13: _t->onConnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 14: _t->onDisconnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 15: _t->onConnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 16: _t->onDisconnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 17: _t->selectionChanged(); break;
        case 18: _t->onRefreshScript(); break;
        case 19: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 20: _t->onNodeContextMenu((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 21: _t->onComponentContextMenu((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 22: _t->onAutoScroll(); break;
        case 23: _t->onScriptAlign(); break;
        case 24: _t->onScriptToggleValues(); break;
        case 25: { bool _r = _t->onScriptAddToLibrary();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: _t->onScriptColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelScriptWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelScriptWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doUndoBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (EdLevelScriptWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doRefreshScript)) {
                *result = 2;
            }
        }
        {
            typedef void (EdLevelScriptWindow::*_t)(const std::list<std::shared_ptr<PlugNode> > & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doSelectionChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (EdLevelScriptWindow::*_t)(std::shared_ptr<WorldNode> , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doNodeContextMenu)) {
                *result = 4;
            }
        }
        {
            typedef void (EdLevelScriptWindow::*_t)(std::shared_ptr<ComponentBase> , const QPointF & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelScriptWindow::doComponentContextMenu)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject EdLevelScriptWindow::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_EdLevelScriptWindow.data,
      qt_meta_data_EdLevelScriptWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelScriptWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelScriptWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelScriptWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelScriptWindow*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int EdLevelScriptWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 27)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 27;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 27)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void EdLevelScriptWindow::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelScriptWindow::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EdLevelScriptWindow::doRefreshScript()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void EdLevelScriptWindow::doSelectionChanged(const std::list<std::shared_ptr<PlugNode> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void EdLevelScriptWindow::doNodeContextMenu(std::shared_ptr<WorldNode> _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void EdLevelScriptWindow::doComponentContextMenu(std::shared_ptr<ComponentBase> _t1, const QPointF & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
