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
    QByteArrayData data[38];
    char stringdata0[689];
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
QT_MOC_LITERAL(8, 121, 8), // "sendNext"
QT_MOC_LITERAL(9, 130, 11), // "HaltEngines"
QT_MOC_LITERAL(10, 142, 20), // "on_reboot_BT_clicked"
QT_MOC_LITERAL(11, 163, 19), // "on_inReb_PB_clicked"
QT_MOC_LITERAL(12, 183, 20), // "on_clrVel_PB_clicked"
QT_MOC_LITERAL(13, 204, 32), // "on_updateTime_SB_editingFinished"
QT_MOC_LITERAL(14, 237, 21), // "on_imuSamp_CB_toggled"
QT_MOC_LITERAL(15, 259, 7), // "checked"
QT_MOC_LITERAL(16, 267, 13), // "sockCommClose"
QT_MOC_LITERAL(17, 281, 12), // "sockTelClose"
QT_MOC_LITERAL(18, 294, 21), // "on_commReb_PB_clicked"
QT_MOC_LITERAL(19, 316, 23), // "on_commands_L_2_clicked"
QT_MOC_LITERAL(20, 340, 21), // "on_addTask_PB_clicked"
QT_MOC_LITERAL(21, 362, 22), // "on_evlogReb_PB_clicked"
QT_MOC_LITERAL(22, 385, 22), // "on_evlogUpd_PB_clicked"
QT_MOC_LITERAL(23, 408, 19), // "on_tsUpd_PB_clicked"
QT_MOC_LITERAL(24, 428, 9), // "UpdateIDs"
QT_MOC_LITERAL(25, 438, 23), // "on_schedMiss_PB_clicked"
QT_MOC_LITERAL(26, 462, 24), // "on_mStart_LE_textChanged"
QT_MOC_LITERAL(27, 487, 4), // "arg1"
QT_MOC_LITERAL(28, 492, 20), // "on_engReb_PB_clicked"
QT_MOC_LITERAL(29, 513, 21), // "on_missPer_CB_clicked"
QT_MOC_LITERAL(30, 535, 17), // "on_fwd_PB_pressed"
QT_MOC_LITERAL(31, 553, 18), // "on_fwd_PB_released"
QT_MOC_LITERAL(32, 572, 18), // "on_left_PB_pressed"
QT_MOC_LITERAL(33, 591, 19), // "on_right_PB_pressed"
QT_MOC_LITERAL(34, 611, 20), // "on_right_PB_released"
QT_MOC_LITERAL(35, 632, 19), // "on_left_PB_released"
QT_MOC_LITERAL(36, 652, 17), // "on_bck_PB_pressed"
QT_MOC_LITERAL(37, 670, 18) // "on_bck_PB_released"

    },
    "MainWindow\0on_scan_bt_clicked\0\0"
    "acceptCliTelemetry\0acceptCliCommands\0"
    "readDataTelemetry\0readDataCommands\0"
    "on_clrLog_clicked\0sendNext\0HaltEngines\0"
    "on_reboot_BT_clicked\0on_inReb_PB_clicked\0"
    "on_clrVel_PB_clicked\0"
    "on_updateTime_SB_editingFinished\0"
    "on_imuSamp_CB_toggled\0checked\0"
    "sockCommClose\0sockTelClose\0"
    "on_commReb_PB_clicked\0on_commands_L_2_clicked\0"
    "on_addTask_PB_clicked\0on_evlogReb_PB_clicked\0"
    "on_evlogUpd_PB_clicked\0on_tsUpd_PB_clicked\0"
    "UpdateIDs\0on_schedMiss_PB_clicked\0"
    "on_mStart_LE_textChanged\0arg1\0"
    "on_engReb_PB_clicked\0on_missPer_CB_clicked\0"
    "on_fwd_PB_pressed\0on_fwd_PB_released\0"
    "on_left_PB_pressed\0on_right_PB_pressed\0"
    "on_right_PB_released\0on_left_PB_released\0"
    "on_bck_PB_pressed\0on_bck_PB_released"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  184,    2, 0x08 /* Private */,
       3,    0,  185,    2, 0x08 /* Private */,
       4,    0,  186,    2, 0x08 /* Private */,
       5,    0,  187,    2, 0x08 /* Private */,
       6,    0,  188,    2, 0x08 /* Private */,
       7,    0,  189,    2, 0x08 /* Private */,
       8,    0,  190,    2, 0x08 /* Private */,
       9,    0,  191,    2, 0x08 /* Private */,
      10,    0,  192,    2, 0x08 /* Private */,
      11,    0,  193,    2, 0x08 /* Private */,
      12,    0,  194,    2, 0x08 /* Private */,
      13,    0,  195,    2, 0x08 /* Private */,
      14,    1,  196,    2, 0x08 /* Private */,
      16,    0,  199,    2, 0x08 /* Private */,
      17,    0,  200,    2, 0x08 /* Private */,
      18,    0,  201,    2, 0x08 /* Private */,
      19,    0,  202,    2, 0x08 /* Private */,
      20,    0,  203,    2, 0x08 /* Private */,
      21,    0,  204,    2, 0x08 /* Private */,
      22,    0,  205,    2, 0x08 /* Private */,
      23,    0,  206,    2, 0x08 /* Private */,
      24,    0,  207,    2, 0x08 /* Private */,
      25,    0,  208,    2, 0x08 /* Private */,
      26,    1,  209,    2, 0x08 /* Private */,
      28,    0,  212,    2, 0x08 /* Private */,
      29,    1,  213,    2, 0x08 /* Private */,
      30,    0,  216,    2, 0x08 /* Private */,
      31,    0,  217,    2, 0x08 /* Private */,
      32,    0,  218,    2, 0x08 /* Private */,
      33,    0,  219,    2, 0x08 /* Private */,
      34,    0,  220,    2, 0x08 /* Private */,
      35,    0,  221,    2, 0x08 /* Private */,
      36,    0,  222,    2, 0x08 /* Private */,
      37,    0,  223,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
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
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 6: _t->sendNext(); break;
        case 7: _t->HaltEngines(); break;
        case 8: _t->on_reboot_BT_clicked(); break;
        case 9: _t->on_inReb_PB_clicked(); break;
        case 10: _t->on_clrVel_PB_clicked(); break;
        case 11: _t->on_updateTime_SB_editingFinished(); break;
        case 12: _t->on_imuSamp_CB_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->sockCommClose(); break;
        case 14: _t->sockTelClose(); break;
        case 15: _t->on_commReb_PB_clicked(); break;
        case 16: _t->on_commands_L_2_clicked(); break;
        case 17: _t->on_addTask_PB_clicked(); break;
        case 18: _t->on_evlogReb_PB_clicked(); break;
        case 19: _t->on_evlogUpd_PB_clicked(); break;
        case 20: _t->on_tsUpd_PB_clicked(); break;
        case 21: _t->UpdateIDs(); break;
        case 22: _t->on_schedMiss_PB_clicked(); break;
        case 23: _t->on_mStart_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_engReb_PB_clicked(); break;
        case 25: _t->on_missPer_CB_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_fwd_PB_pressed(); break;
        case 27: _t->on_fwd_PB_released(); break;
        case 28: _t->on_left_PB_pressed(); break;
        case 29: _t->on_right_PB_pressed(); break;
        case 30: _t->on_right_PB_released(); break;
        case 31: _t->on_left_PB_released(); break;
        case 32: _t->on_bck_PB_pressed(); break;
        case 33: _t->on_bck_PB_released(); break;
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
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 34;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
