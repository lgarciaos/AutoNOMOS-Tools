/****************************************************************************
** Meta object code from reading C++ file 'plugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/main_gui/include/plugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_main_gui__MyPlugin_t {
    QByteArrayData data[20];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_main_gui__MyPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_main_gui__MyPlugin_t qt_meta_stringdata_main_gui__MyPlugin = {
    {
QT_MOC_LITERAL(0, 0, 18), // "main_gui::MyPlugin"
QT_MOC_LITERAL(1, 19, 15), // "updateTopicList"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "onTopicChanged"
QT_MOC_LITERAL(4, 51, 5), // "index"
QT_MOC_LITERAL(5, 57, 7), // "onZoom1"
QT_MOC_LITERAL(6, 65, 7), // "checked"
QT_MOC_LITERAL(7, 73, 14), // "onDynamicRange"
QT_MOC_LITERAL(8, 88, 9), // "saveImage"
QT_MOC_LITERAL(9, 98, 18), // "updateNumGridlines"
QT_MOC_LITERAL(10, 117, 14), // "onMousePublish"
QT_MOC_LITERAL(11, 132, 11), // "onMouseLeft"
QT_MOC_LITERAL(12, 144, 1), // "x"
QT_MOC_LITERAL(13, 146, 1), // "y"
QT_MOC_LITERAL(14, 148, 17), // "onPubTopicChanged"
QT_MOC_LITERAL(15, 166, 20), // "onHideToolbarChanged"
QT_MOC_LITERAL(16, 187, 4), // "hide"
QT_MOC_LITERAL(17, 192, 20), // "right_scroll_changed"
QT_MOC_LITERAL(18, 213, 21), // "center_scroll_changed"
QT_MOC_LITERAL(19, 235, 19) // "left_scroll_changed"

    },
    "main_gui::MyPlugin\0updateTopicList\0\0"
    "onTopicChanged\0index\0onZoom1\0checked\0"
    "onDynamicRange\0saveImage\0updateNumGridlines\0"
    "onMousePublish\0onMouseLeft\0x\0y\0"
    "onPubTopicChanged\0onHideToolbarChanged\0"
    "hide\0right_scroll_changed\0"
    "center_scroll_changed\0left_scroll_changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_main_gui__MyPlugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x09 /* Protected */,
       3,    1,   80,    2, 0x09 /* Protected */,
       5,    1,   83,    2, 0x09 /* Protected */,
       7,    1,   86,    2, 0x09 /* Protected */,
       8,    0,   89,    2, 0x09 /* Protected */,
       9,    0,   90,    2, 0x09 /* Protected */,
      10,    1,   91,    2, 0x09 /* Protected */,
      11,    2,   94,    2, 0x09 /* Protected */,
      14,    0,   99,    2, 0x09 /* Protected */,
      15,    1,  100,    2, 0x09 /* Protected */,
      17,    0,  103,    2, 0x09 /* Protected */,
      18,    0,  104,    2, 0x09 /* Protected */,
      19,    0,  105,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void main_gui::MyPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyPlugin *_t = static_cast<MyPlugin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTopicList(); break;
        case 1: _t->onTopicChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onZoom1((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onDynamicRange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->saveImage(); break;
        case 5: _t->updateNumGridlines(); break;
        case 6: _t->onMousePublish((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onMouseLeft((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->onPubTopicChanged(); break;
        case 9: _t->onHideToolbarChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->right_scroll_changed(); break;
        case 11: _t->center_scroll_changed(); break;
        case 12: _t->left_scroll_changed(); break;
        default: ;
        }
    }
}

const QMetaObject main_gui::MyPlugin::staticMetaObject = {
    { &rqt_gui_cpp::Plugin::staticMetaObject, qt_meta_stringdata_main_gui__MyPlugin.data,
      qt_meta_data_main_gui__MyPlugin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *main_gui::MyPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *main_gui::MyPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_main_gui__MyPlugin.stringdata0))
        return static_cast<void*>(this);
    return rqt_gui_cpp::Plugin::qt_metacast(_clname);
}

int main_gui::MyPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = rqt_gui_cpp::Plugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
