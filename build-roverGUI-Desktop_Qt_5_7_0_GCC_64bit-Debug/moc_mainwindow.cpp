/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../roverGUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 18), // "on_scan_bt_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 18), // "acceptCliTelemetry"
QT_MOC_LITERAL(4, 50, 17), // "acceptCliCommands"
QT_MOC_LITERAL(5, 68, 17), // "readDataTelemetry"
QT_MOC_LITERAL(6, 86, 16), // "readDataCommands"
QT_MOC_LITERAL(7, 103, 17), // "on_clrLog_clicked"
QT_MOC_LITERAL(8, 121, 20), // "on_reboot_BT_clicked"
QT_MOC_LITERAL(9, 142, 19), // "on_inReb_PB_clicked"
QT_MOC_LITERAL(10, 162, 20), // "on_clrVel_PB_clicked"
QT_MOC_LITERAL(11, 183, 32), // "on_updateTime_SB_editingFinished"
QT_MOC_LITERAL(12, 216, 21), // "on_imuSamp_CB_toggled"
QT_MOC_LITERAL(13, 238, 7), // "checked"
QT_MOC_LITERAL(14, 246, 13), // "sockCommClose"
QT_MOC_LITERAL(15, 260, 12) // "sockTelClose"

    },
    "MainWindow\0on_scan_bt_clicked\0\0"
    "acceptCliTelemetry\0acceptCliCommands\0"
    "readDataTelemetry\0readDataCommands\0"
    "on_clrLog_clicked\0on_reboot_BT_clicked\0"
    "on_inReb_PB_clicked\0on_clrVel_PB_clicked\0"
    "on_updateTime_SB_editingFinished\0"
    "on_imuSamp_CB_toggled\0checked\0"
    "sockCommClose\0sockTelClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
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
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_scan_bt_clicked(); break;
        case 1: _t->acceptCliTelemetry(); break;
        case 2: _t->acceptCliCommands(); break;
        case 3: _t->readDataTelemetry(); break;
        case 4: _t->readDataCommands(); break;
        case 5: _t->on_clrLog_clicked(); break;
        case 6: _t->on_reboot_BT_clicked(); break;
        case 7: _t->on_inReb_PB_clicked(); break;
        case 8: _t->on_clrVel_PB_clicked(); break;
        case 9: _t->on_updateTime_SB_editingFinished(); break;
        case 10: _t->on_imuSamp_CB_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->sockCommClose(); break;
        case 12: _t->sockTelClose(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
