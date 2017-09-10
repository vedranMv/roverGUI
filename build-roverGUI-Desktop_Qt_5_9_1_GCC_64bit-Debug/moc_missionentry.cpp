/****************************************************************************
** Meta object code from reading C++ file 'missionentry.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../roverGUI/missionentry.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'missionentry.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MissionEntry_t {
    QByteArrayData data[8];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MissionEntry_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MissionEntry_t qt_meta_stringdata_MissionEntry = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MissionEntry"
QT_MOC_LITERAL(1, 13, 7), // "Deleted"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "Delete"
QT_MOC_LITERAL(4, 29, 15), // "UpdateArguments"
QT_MOC_LITERAL(5, 45, 5), // "index"
QT_MOC_LITERAL(6, 51, 12), // "UpdateTaskCB"
QT_MOC_LITERAL(7, 64, 13) // "UpdateEngUnit"

    },
    "MissionEntry\0Deleted\0\0Delete\0"
    "UpdateArguments\0index\0UpdateTaskCB\0"
    "UpdateEngUnit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MissionEntry[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       7,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void MissionEntry::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MissionEntry *_t = static_cast<MissionEntry *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Deleted(); break;
        case 1: _t->Delete(); break;
        case 2: _t->UpdateArguments((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->UpdateTaskCB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->UpdateEngUnit((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MissionEntry::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MissionEntry::Deleted)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MissionEntry::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MissionEntry.data,
      qt_meta_data_MissionEntry,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MissionEntry::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MissionEntry::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MissionEntry.stringdata0))
        return static_cast<void*>(const_cast< MissionEntry*>(this));
    return QObject::qt_metacast(_clname);
}

int MissionEntry::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MissionEntry::Deleted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
