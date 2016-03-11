/****************************************************************************
** Meta object code from reading C++ file 'EdLevelHierarchyWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Hierarchy/EdLevelHierarchyWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelHierarchyWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelHierarchyWindow_t {
    QByteArrayData data[35];
    char stringdata[465];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelHierarchyWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelHierarchyWindow_t qt_meta_stringdata_EdLevelHierarchyWindow = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 9),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 7),
QT_MOC_LITERAL(4, 42, 11),
QT_MOC_LITERAL(5, 54, 18),
QT_MOC_LITERAL(6, 73, 37),
QT_MOC_LITERAL(7, 111, 14),
QT_MOC_LITERAL(8, 126, 9),
QT_MOC_LITERAL(9, 136, 26),
QT_MOC_LITERAL(10, 163, 4),
QT_MOC_LITERAL(11, 168, 12),
QT_MOC_LITERAL(12, 181, 14),
QT_MOC_LITERAL(13, 196, 10),
QT_MOC_LITERAL(14, 207, 10),
QT_MOC_LITERAL(15, 218, 18),
QT_MOC_LITERAL(16, 237, 18),
QT_MOC_LITERAL(17, 256, 13),
QT_MOC_LITERAL(18, 270, 9),
QT_MOC_LITERAL(19, 280, 8),
QT_MOC_LITERAL(20, 289, 8),
QT_MOC_LITERAL(21, 298, 16),
QT_MOC_LITERAL(22, 315, 14),
QT_MOC_LITERAL(23, 330, 6),
QT_MOC_LITERAL(24, 337, 17),
QT_MOC_LITERAL(25, 355, 13),
QT_MOC_LITERAL(26, 369, 10),
QT_MOC_LITERAL(27, 380, 9),
QT_MOC_LITERAL(28, 390, 12),
QT_MOC_LITERAL(29, 403, 4),
QT_MOC_LITERAL(30, 408, 12),
QT_MOC_LITERAL(31, 421, 13),
QT_MOC_LITERAL(32, 435, 16),
QT_MOC_LITERAL(33, 452, 4),
QT_MOC_LITERAL(34, 457, 6)
    },
    "EdLevelHierarchyWindow\0doCommand\0\0"
    "command\0doUndoBlock\0doSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0onAddNode\0"
    "std::shared_ptr<WorldNode>\0node\0"
    "onRemoveNode\0onReparentNode\0old_parent\0"
    "new_parent\0onRefreshHierarchy\0"
    "onSelectionChanged\0onConnectPlug\0"
    "PlugBase*\0outgoing\0incoming\0"
    "onDisconnectPlug\0onConnectEvent\0Event*\0"
    "onDisconnectEvent\0onShowObjects\0"
    "onShowCalc\0onShowAll\0onShowFilter\0"
    "text\0onAutoScroll\0onItemChanged\0"
    "QTreeWidgetItem*\0item\0column\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelHierarchyWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x05,
       4,    0,  107,    2, 0x05,
       5,    1,  108,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    1,  111,    2, 0x0a,
      11,    1,  114,    2, 0x0a,
      12,    3,  117,    2, 0x0a,
      15,    0,  124,    2, 0x0a,
      16,    1,  125,    2, 0x0a,
      17,    2,  128,    2, 0x0a,
      21,    2,  133,    2, 0x0a,
      22,    2,  138,    2, 0x0a,
      24,    2,  143,    2, 0x0a,
      25,    0,  148,    2, 0x0a,
      26,    0,  149,    2, 0x0a,
      27,    0,  150,    2, 0x0a,
      28,    1,  151,    2, 0x0a,
      30,    0,  154,    2, 0x0a,
      31,    2,  155,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9,   10,   13,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18,   19,   20,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 18,   19,   20,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 23,   19,   20,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 23,   19,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32, QMetaType::Int,   33,   34,

       0        // eod
};

void EdLevelHierarchyWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelHierarchyWindow *_t = static_cast<EdLevelHierarchyWindow *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->doSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 3: _t->onAddNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 4: _t->onRemoveNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 5: _t->onReparentNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[3]))); break;
        case 6: _t->onRefreshHierarchy(); break;
        case 7: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 8: _t->onConnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 9: _t->onDisconnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 10: _t->onConnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 11: _t->onDisconnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 12: _t->onShowObjects(); break;
        case 13: _t->onShowCalc(); break;
        case 14: _t->onShowAll(); break;
        case 15: _t->onShowFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->onAutoScroll(); break;
        case 17: _t->onItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelHierarchyWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelHierarchyWindow::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelHierarchyWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelHierarchyWindow::doUndoBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (EdLevelHierarchyWindow::*_t)(const std::list<std::shared_ptr<PlugNode> > & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelHierarchyWindow::doSelectionChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject EdLevelHierarchyWindow::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_EdLevelHierarchyWindow.data,
      qt_meta_data_EdLevelHierarchyWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelHierarchyWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelHierarchyWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelHierarchyWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelHierarchyWindow*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int EdLevelHierarchyWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void EdLevelHierarchyWindow::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelHierarchyWindow::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EdLevelHierarchyWindow::doSelectionChanged(const std::list<std::shared_ptr<PlugNode> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
