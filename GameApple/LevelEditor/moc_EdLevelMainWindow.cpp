/****************************************************************************
** Meta object code from reading C++ file 'EdLevelMainWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DT3LevelEditor/EdLevelMainWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EdLevelMainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EdLevelMainWindow_t {
    QByteArrayData data[81];
    char stringdata[1144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EdLevelMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EdLevelMainWindow_t qt_meta_stringdata_EdLevelMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 9),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 26),
QT_MOC_LITERAL(4, 56, 4),
QT_MOC_LITERAL(5, 61, 12),
QT_MOC_LITERAL(6, 74, 14),
QT_MOC_LITERAL(7, 89, 10),
QT_MOC_LITERAL(8, 100, 10),
QT_MOC_LITERAL(9, 111, 10),
QT_MOC_LITERAL(10, 122, 22),
QT_MOC_LITERAL(11, 145, 5),
QT_MOC_LITERAL(12, 151, 13),
QT_MOC_LITERAL(13, 165, 14),
QT_MOC_LITERAL(14, 180, 30),
QT_MOC_LITERAL(15, 211, 17),
QT_MOC_LITERAL(16, 229, 13),
QT_MOC_LITERAL(17, 243, 9),
QT_MOC_LITERAL(18, 253, 8),
QT_MOC_LITERAL(19, 262, 8),
QT_MOC_LITERAL(20, 271, 16),
QT_MOC_LITERAL(21, 288, 14),
QT_MOC_LITERAL(22, 303, 6),
QT_MOC_LITERAL(23, 310, 17),
QT_MOC_LITERAL(24, 328, 15),
QT_MOC_LITERAL(25, 344, 14),
QT_MOC_LITERAL(26, 359, 18),
QT_MOC_LITERAL(27, 378, 19),
QT_MOC_LITERAL(28, 398, 16),
QT_MOC_LITERAL(29, 415, 18),
QT_MOC_LITERAL(30, 434, 18),
QT_MOC_LITERAL(31, 453, 16),
QT_MOC_LITERAL(32, 470, 20),
QT_MOC_LITERAL(33, 491, 14),
QT_MOC_LITERAL(34, 506, 16),
QT_MOC_LITERAL(35, 523, 18),
QT_MOC_LITERAL(36, 542, 37),
QT_MOC_LITERAL(37, 580, 14),
QT_MOC_LITERAL(38, 595, 6),
QT_MOC_LITERAL(39, 602, 11),
QT_MOC_LITERAL(40, 614, 13),
QT_MOC_LITERAL(41, 628, 17),
QT_MOC_LITERAL(42, 646, 17),
QT_MOC_LITERAL(43, 664, 11),
QT_MOC_LITERAL(44, 676, 7),
QT_MOC_LITERAL(45, 684, 12),
QT_MOC_LITERAL(46, 697, 6),
QT_MOC_LITERAL(47, 704, 5),
QT_MOC_LITERAL(48, 710, 6),
QT_MOC_LITERAL(49, 717, 7),
QT_MOC_LITERAL(50, 725, 7),
QT_MOC_LITERAL(51, 733, 11),
QT_MOC_LITERAL(52, 745, 12),
QT_MOC_LITERAL(53, 758, 11),
QT_MOC_LITERAL(54, 770, 20),
QT_MOC_LITERAL(55, 791, 7),
QT_MOC_LITERAL(56, 799, 9),
QT_MOC_LITERAL(57, 809, 18),
QT_MOC_LITERAL(58, 828, 17),
QT_MOC_LITERAL(59, 846, 13),
QT_MOC_LITERAL(60, 860, 14),
QT_MOC_LITERAL(61, 875, 17),
QT_MOC_LITERAL(62, 893, 16),
QT_MOC_LITERAL(63, 910, 15),
QT_MOC_LITERAL(64, 926, 13),
QT_MOC_LITERAL(65, 940, 9),
QT_MOC_LITERAL(66, 950, 7),
QT_MOC_LITERAL(67, 958, 11),
QT_MOC_LITERAL(68, 970, 18),
QT_MOC_LITERAL(69, 989, 17),
QT_MOC_LITERAL(70, 1007, 10),
QT_MOC_LITERAL(71, 1018, 22),
QT_MOC_LITERAL(72, 1041, 9),
QT_MOC_LITERAL(73, 1051, 11),
QT_MOC_LITERAL(74, 1063, 13),
QT_MOC_LITERAL(75, 1077, 13),
QT_MOC_LITERAL(76, 1091, 16),
QT_MOC_LITERAL(77, 1108, 17),
QT_MOC_LITERAL(78, 1126, 8),
QT_MOC_LITERAL(79, 1135, 3),
QT_MOC_LITERAL(80, 1139, 3)
    },
    "EdLevelMainWindow\0doAddNode\0\0"
    "std::shared_ptr<WorldNode>\0node\0"
    "doRemoveNode\0doReparentNode\0old_parent\0"
    "new_parent\0doAddGroup\0std::shared_ptr<Group>\0"
    "group\0doRemoveGroup\0doAddComponent\0"
    "std::shared_ptr<ComponentBase>\0"
    "doRemoveComponent\0doConnectPlug\0"
    "PlugBase*\0outgoing\0incoming\0"
    "doDisconnectPlug\0doConnectEvent\0Event*\0"
    "doDisconnectEvent\0doRefreshScript\0"
    "doRefreshWorld\0doRefreshHierarchy\0"
    "doRefreshProperties\0doRefreshLibrary\0"
    "doRefreshResources\0doRefreshAnimation\0"
    "doRefreshConsole\0doRefreshPerformance\0"
    "doRefreshSound\0doRefreshSoundFX\0"
    "doSelectionChanged\0"
    "std::list<std::shared_ptr<PlugNode> >\0"
    "selection_list\0onOpen\0onSaveLevel\0"
    "onSaveLevelAs\0onExportSelection\0"
    "onImportSelection\0onRunScript\0onAbout\0"
    "onOpenRecent\0onUndo\0onCut\0onCopy\0"
    "onPaste\0onClear\0onSelectAll\0onSelectNone\0"
    "onDuplicate\0onDuplicateHierarchy\0"
    "onGroup\0onUngroup\0onDocumentModified\0"
    "onUpdateStatusBar\0onUpdateMenus\0"
    "onCreateObject\0onCreateComponent\0"
    "onClearComponent\0onCreateScripts\0"
    "onCreateWorld\0onCommand\0command\0"
    "onUndoBlock\0onSelectionChanged\0"
    "onNodeContextMenu\0global_pos\0"
    "onComponentContextMenu\0component\0"
    "onPlayLevel\0onPlayOptions\0onMeshBuilder\0"
    "onPackageBuilder\0onAppFocusChanged\0"
    "QWidget*\0old\0now\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EdLevelMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      60,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      23,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  314,    2, 0x05,
       5,    1,  317,    2, 0x05,
       6,    3,  320,    2, 0x05,
       9,    1,  327,    2, 0x05,
      12,    1,  330,    2, 0x05,
      13,    1,  333,    2, 0x05,
      15,    1,  336,    2, 0x05,
      16,    2,  339,    2, 0x05,
      20,    2,  344,    2, 0x05,
      21,    2,  349,    2, 0x05,
      23,    2,  354,    2, 0x05,
      24,    0,  359,    2, 0x05,
      25,    0,  360,    2, 0x05,
      26,    0,  361,    2, 0x05,
      27,    0,  362,    2, 0x05,
      28,    0,  363,    2, 0x05,
      29,    0,  364,    2, 0x05,
      30,    0,  365,    2, 0x05,
      31,    0,  366,    2, 0x05,
      32,    0,  367,    2, 0x05,
      33,    0,  368,    2, 0x05,
      34,    0,  369,    2, 0x05,
      35,    1,  370,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
      38,    0,  373,    2, 0x08,
      39,    0,  374,    2, 0x08,
      40,    0,  375,    2, 0x08,
      41,    0,  376,    2, 0x08,
      42,    0,  377,    2, 0x08,
      43,    0,  378,    2, 0x08,
      44,    0,  379,    2, 0x08,
      45,    0,  380,    2, 0x08,
      46,    0,  381,    2, 0x08,
      47,    0,  382,    2, 0x08,
      48,    0,  383,    2, 0x08,
      49,    0,  384,    2, 0x08,
      50,    0,  385,    2, 0x08,
      51,    0,  386,    2, 0x08,
      52,    0,  387,    2, 0x08,
      53,    0,  388,    2, 0x08,
      54,    0,  389,    2, 0x08,
      55,    0,  390,    2, 0x08,
      56,    0,  391,    2, 0x08,
      57,    0,  392,    2, 0x08,
      58,    0,  393,    2, 0x08,
      59,    0,  394,    2, 0x08,
      60,    0,  395,    2, 0x08,
      61,    0,  396,    2, 0x08,
      62,    0,  397,    2, 0x08,
      63,    0,  398,    2, 0x08,
      64,    0,  399,    2, 0x08,
      65,    1,  400,    2, 0x08,
      67,    0,  403,    2, 0x08,
      68,    1,  404,    2, 0x08,
      69,    2,  407,    2, 0x08,
      71,    2,  412,    2, 0x08,
      73,    0,  417,    2, 0x08,
      74,    0,  418,    2, 0x08,
      75,    0,  419,    2, 0x08,
      76,    0,  420,    2, 0x08,
      77,    2,  421,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 14,    4,
    QMetaType::Void, 0x80000000 | 14,    4,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 17,   18,   19,
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 17,   18,   19,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 22,   18,   19,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 22,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36,   37,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   66,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,    4,   70,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QPointF,   72,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 78, 0x80000000 | 78,   79,   80,

       0        // eod
};

void EdLevelMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EdLevelMainWindow *_t = static_cast<EdLevelMainWindow *>(_o);
        switch (_id) {
        case 0: _t->doAddNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 1: _t->doRemoveNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1]))); break;
        case 2: _t->doReparentNode((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[3]))); break;
        case 3: _t->doAddGroup((*reinterpret_cast< std::shared_ptr<Group>(*)>(_a[1]))); break;
        case 4: _t->doRemoveGroup((*reinterpret_cast< std::shared_ptr<Group>(*)>(_a[1]))); break;
        case 5: _t->doAddComponent((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1]))); break;
        case 6: _t->doRemoveComponent((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1]))); break;
        case 7: _t->doConnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 8: _t->doDisconnectPlug((*reinterpret_cast< PlugBase*(*)>(_a[1])),(*reinterpret_cast< PlugBase*(*)>(_a[2]))); break;
        case 9: _t->doConnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 10: _t->doDisconnectEvent((*reinterpret_cast< Event*(*)>(_a[1])),(*reinterpret_cast< Event*(*)>(_a[2]))); break;
        case 11: _t->doRefreshScript(); break;
        case 12: _t->doRefreshWorld(); break;
        case 13: _t->doRefreshHierarchy(); break;
        case 14: _t->doRefreshProperties(); break;
        case 15: _t->doRefreshLibrary(); break;
        case 16: _t->doRefreshResources(); break;
        case 17: _t->doRefreshAnimation(); break;
        case 18: _t->doRefreshConsole(); break;
        case 19: _t->doRefreshPerformance(); break;
        case 20: _t->doRefreshSound(); break;
        case 21: _t->doRefreshSoundFX(); break;
        case 22: _t->doSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 23: _t->onOpen(); break;
        case 24: { bool _r = _t->onSaveLevel();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: { bool _r = _t->onSaveLevelAs();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 26: { bool _r = _t->onExportSelection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 27: _t->onImportSelection(); break;
        case 28: _t->onRunScript(); break;
        case 29: _t->onAbout(); break;
        case 30: _t->onOpenRecent(); break;
        case 31: _t->onUndo(); break;
        case 32: _t->onCut(); break;
        case 33: _t->onCopy(); break;
        case 34: _t->onPaste(); break;
        case 35: _t->onClear(); break;
        case 36: _t->onSelectAll(); break;
        case 37: _t->onSelectNone(); break;
        case 38: _t->onDuplicate(); break;
        case 39: _t->onDuplicateHierarchy(); break;
        case 40: _t->onGroup(); break;
        case 41: _t->onUngroup(); break;
        case 42: _t->onDocumentModified(); break;
        case 43: _t->onUpdateStatusBar(); break;
        case 44: _t->onUpdateMenus(); break;
        case 45: _t->onCreateObject(); break;
        case 46: _t->onCreateComponent(); break;
        case 47: _t->onClearComponent(); break;
        case 48: _t->onCreateScripts(); break;
        case 49: _t->onCreateWorld(); break;
        case 50: { bool _r = _t->onCommand((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 51: _t->onUndoBlock(); break;
        case 52: _t->onSelectionChanged((*reinterpret_cast< const std::list<std::shared_ptr<PlugNode> >(*)>(_a[1]))); break;
        case 53: _t->onNodeContextMenu((*reinterpret_cast< std::shared_ptr<WorldNode>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 54: _t->onComponentContextMenu((*reinterpret_cast< std::shared_ptr<ComponentBase>(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 55: _t->onPlayLevel(); break;
        case 56: _t->onPlayOptions(); break;
        case 57: _t->onMeshBuilder(); break;
        case 58: _t->onPackageBuilder(); break;
        case 59: _t->onAppFocusChanged((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 59:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<WorldNode> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doAddNode)) {
                *result = 0;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<WorldNode> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRemoveNode)) {
                *result = 1;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<WorldNode> , std::shared_ptr<WorldNode> , std::shared_ptr<WorldNode> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doReparentNode)) {
                *result = 2;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<Group> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doAddGroup)) {
                *result = 3;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<Group> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRemoveGroup)) {
                *result = 4;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<ComponentBase> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doAddComponent)) {
                *result = 5;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(std::shared_ptr<ComponentBase> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRemoveComponent)) {
                *result = 6;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(PlugBase * , PlugBase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doConnectPlug)) {
                *result = 7;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(PlugBase * , PlugBase * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doDisconnectPlug)) {
                *result = 8;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(Event * , Event * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doConnectEvent)) {
                *result = 9;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(Event * , Event * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doDisconnectEvent)) {
                *result = 10;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshScript)) {
                *result = 11;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshWorld)) {
                *result = 12;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshHierarchy)) {
                *result = 13;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshProperties)) {
                *result = 14;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshLibrary)) {
                *result = 15;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshResources)) {
                *result = 16;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshAnimation)) {
                *result = 17;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshConsole)) {
                *result = 18;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshPerformance)) {
                *result = 19;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshSound)) {
                *result = 20;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doRefreshSoundFX)) {
                *result = 21;
            }
        }
        {
            typedef void (EdLevelMainWindow::*_t)(const std::list<std::shared_ptr<PlugNode> > & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EdLevelMainWindow::doSelectionChanged)) {
                *result = 22;
            }
        }
    }
}

const QMetaObject EdLevelMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EdLevelMainWindow.data,
      qt_meta_data_EdLevelMainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EdLevelMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EdLevelMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EdLevelMainWindow.stringdata))
        return static_cast<void*>(const_cast< EdLevelMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EdLevelMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 60)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 60;
    }
    return _id;
}

// SIGNAL 0
void EdLevelMainWindow::doAddNode(std::shared_ptr<WorldNode> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EdLevelMainWindow::doRemoveNode(std::shared_ptr<WorldNode> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EdLevelMainWindow::doReparentNode(std::shared_ptr<WorldNode> _t1, std::shared_ptr<WorldNode> _t2, std::shared_ptr<WorldNode> _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void EdLevelMainWindow::doAddGroup(std::shared_ptr<Group> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void EdLevelMainWindow::doRemoveGroup(std::shared_ptr<Group> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void EdLevelMainWindow::doAddComponent(std::shared_ptr<ComponentBase> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void EdLevelMainWindow::doRemoveComponent(std::shared_ptr<ComponentBase> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void EdLevelMainWindow::doConnectPlug(PlugBase * _t1, PlugBase * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void EdLevelMainWindow::doDisconnectPlug(PlugBase * _t1, PlugBase * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void EdLevelMainWindow::doConnectEvent(Event * _t1, Event * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void EdLevelMainWindow::doDisconnectEvent(Event * _t1, Event * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void EdLevelMainWindow::doRefreshScript()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void EdLevelMainWindow::doRefreshWorld()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void EdLevelMainWindow::doRefreshHierarchy()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}

// SIGNAL 14
void EdLevelMainWindow::doRefreshProperties()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}

// SIGNAL 15
void EdLevelMainWindow::doRefreshLibrary()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}

// SIGNAL 16
void EdLevelMainWindow::doRefreshResources()
{
    QMetaObject::activate(this, &staticMetaObject, 16, 0);
}

// SIGNAL 17
void EdLevelMainWindow::doRefreshAnimation()
{
    QMetaObject::activate(this, &staticMetaObject, 17, 0);
}

// SIGNAL 18
void EdLevelMainWindow::doRefreshConsole()
{
    QMetaObject::activate(this, &staticMetaObject, 18, 0);
}

// SIGNAL 19
void EdLevelMainWindow::doRefreshPerformance()
{
    QMetaObject::activate(this, &staticMetaObject, 19, 0);
}

// SIGNAL 20
void EdLevelMainWindow::doRefreshSound()
{
    QMetaObject::activate(this, &staticMetaObject, 20, 0);
}

// SIGNAL 21
void EdLevelMainWindow::doRefreshSoundFX()
{
    QMetaObject::activate(this, &staticMetaObject, 21, 0);
}

// SIGNAL 22
void EdLevelMainWindow::doSelectionChanged(const std::list<std::shared_ptr<PlugNode> > & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}
QT_END_MOC_NAMESPACE
