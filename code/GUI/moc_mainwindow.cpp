/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(4, 58, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(5, 82, 20), // "on_dial_valueChanged"
QT_MOC_LITERAL(6, 103, 5), // "value"
QT_MOC_LITERAL(7, 109, 22), // "on_dial_2_valueChanged"
QT_MOC_LITERAL(8, 132, 12), // "UserMainLoop"
QT_MOC_LITERAL(9, 145, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(10, 169, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(11, 193, 22), // "on_dial_3_valueChanged"
QT_MOC_LITERAL(12, 216, 22), // "on_dial_4_valueChanged"
QT_MOC_LITERAL(13, 239, 22), // "on_dial_5_valueChanged"
QT_MOC_LITERAL(14, 262, 22), // "on_dial_6_valueChanged"
QT_MOC_LITERAL(15, 285, 22) // "on_dial_7_valueChanged"

    },
    "MainWindow\0on_pushButton_clicked\0\0"
    "on_pushButton_3_clicked\0on_pushButton_2_clicked\0"
    "on_dial_valueChanged\0value\0"
    "on_dial_2_valueChanged\0UserMainLoop\0"
    "on_pushButton_4_clicked\0on_pushButton_5_clicked\0"
    "on_dial_3_valueChanged\0on_dial_4_valueChanged\0"
    "on_dial_5_valueChanged\0on_dial_6_valueChanged\0"
    "on_dial_7_valueChanged"
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
       5,    1,   82,    2, 0x08 /* Private */,
       7,    1,   85,    2, 0x08 /* Private */,
       8,    0,   88,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x08 /* Private */,
      10,    0,   90,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      12,    1,   94,    2, 0x08 /* Private */,
      13,    1,   97,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x08 /* Private */,
      15,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_clicked(); break;
        case 1: _t->on_pushButton_3_clicked(); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_dial_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_dial_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->UserMainLoop(); break;
        case 6: _t->on_pushButton_4_clicked(); break;
        case 7: _t->on_pushButton_5_clicked(); break;
        case 8: _t->on_dial_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_dial_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_dial_5_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_dial_6_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_dial_7_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
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
