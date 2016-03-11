/****************************************************************************
** Meta object code from reading C++ file 'EdLevelAnimationWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/Animation/EdLevelAnimationWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelAnimationWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelAnimationWindow_t {
    QByteArrayData data[17];
    char stringdata[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelAnimationWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelAnimationWindow_t qt_meta_stringdata_EdLevelAnimationWindow = {
    {
QT_MOC_LITERAL(0, 0, 22),
QT_MOC_LITERAL(1, 23, 9),
QT_MOC_LITERAL(2, 33, 0),
QT_MOC_LITERAL(3, 34, 7),
QT_MOC_LITERAL(4, 42, 11),
QT_MOC_LITERAL(5, 54, 18),
QT_MOC_LITERAL(6, 73, 37),
QT_MOC_LITERAL(7, 111, 14),
QT_MOC_LITERAL(8, 126, 18),
QT_MOC_LITERAL(9, 145, 12),
QT_MOC_LITERAL(10, 158, 4),
QT_MOC_LITERAL(11, 163, 8),
QT_MOC_LITERAL(12, 172, 6),
QT_MOC_LITERAL(13, 179, 17),
QT_MOC_LITERAL(14, 197, 18),
QT_MOC_LITERAL(15, 216, 10),
QT_MOC_LITERAL(16, 227, 10)
    },
    "EdLevelAnimationWindow\0doCommand\0\0"
    "command\0doUndoBlock\0doSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0onSelectionChanged\0"
    "onScrollTime\0time\0onScroll\0scroll\0"
    "onChangeTimeRange\0onRefreshAnimation\0"
    "onAnimPlay\0onAnimStop\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelAnimationWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x05,
       4,    0,   67,    2, 0x05,
       5,    1,   68,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       8,    1,   71,    2, 0x0a,
       9,    1,   74,    2, 0x0a,
      11,    1,   77,    2, 0x0a,
      13,    0,   80,    2, 0x0a,
      14,    0,   81,    2, 0x0a,
      15,    0,   82,    2, 0x0a,
      16,    0,   83,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EdLevelAnimationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelAnimationWindow *_t = static_cast<EdLevelAnimationWindow *>(_o);
        switch (_id) {
        case 0: _t->doCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->doUndoBlock(); break;
        case 2: _t->doSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 3: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 4: _t->onScrollTime((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onChangeTimeRange(); break;
        case 7: _t->onRefreshAnimation(); break;
        case 8: _t->onAnimPlay(); break;
        case 9: _t->onAnimStop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelAnimationWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelAnimationWindow::doCommand)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelAnimationWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelAnimationWindow::doUndoBlock)) {
                *result = 1;
            }
        }
        {
            typedef void (EdLevelAnimationWindow::*_t)(const std::list<std::shared_ptr<PlugNode> > & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelAnimationWindow::doSelectionChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject EdLevelAnimationWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EdLevelAnimationWindow.data,
      qt_meta_data_EdLevelAnimationWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelAnimationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelAnimationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelAnimationWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelAnimationWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int EdLevelAnimationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void EdLevelAnimationWindow::doCommand(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelAnimationWindow::doUndoBlock()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void EdLevelAnimationWindow::doSelectionChanged(const std::list<std::shared_ptr<PlugNode> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
