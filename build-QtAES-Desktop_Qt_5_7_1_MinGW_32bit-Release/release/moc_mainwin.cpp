/****************************************************************************
** Meta object code from reading C++ file 'mainwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtAES/mainwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWin_t {
    QByteArrayData data[16];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWin_t qt_meta_stringdata_MainWin = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainWin"
QT_MOC_LITERAL(1, 8, 38), // "on_comboBox_keyLen_currentInd..."
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 5), // "index"
QT_MOC_LITERAL(4, 54, 36), // "on_comboBox_mode_currentIndex..."
QT_MOC_LITERAL(5, 91, 39), // "on_comboBox_blockLen_currentT..."
QT_MOC_LITERAL(6, 131, 4), // "arg1"
QT_MOC_LITERAL(7, 136, 22), // "on_Btn_encrypt_clicked"
QT_MOC_LITERAL(8, 159, 22), // "on_Btn_decrypt_clicked"
QT_MOC_LITERAL(9, 182, 19), // "on_Btn_file_clicked"
QT_MOC_LITERAL(10, 202, 19), // "on_Btn_save_clicked"
QT_MOC_LITERAL(11, 222, 23), // "on_rBtn_compare_toggled"
QT_MOC_LITERAL(12, 246, 7), // "checked"
QT_MOC_LITERAL(13, 254, 20), // "on_Btn_file1_clicked"
QT_MOC_LITERAL(14, 275, 20), // "on_Btn_file2_clicked"
QT_MOC_LITERAL(15, 296, 22) // "on_Btn_compare_clicked"

    },
    "MainWin\0on_comboBox_keyLen_currentIndexChanged\0"
    "\0index\0on_comboBox_mode_currentIndexChanged\0"
    "on_comboBox_blockLen_currentTextChanged\0"
    "arg1\0on_Btn_encrypt_clicked\0"
    "on_Btn_decrypt_clicked\0on_Btn_file_clicked\0"
    "on_Btn_save_clicked\0on_rBtn_compare_toggled\0"
    "checked\0on_Btn_file1_clicked\0"
    "on_Btn_file2_clicked\0on_Btn_compare_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08 /* Private */,
       4,    1,   72,    2, 0x08 /* Private */,
       5,    1,   75,    2, 0x08 /* Private */,
       7,    0,   78,    2, 0x08 /* Private */,
       8,    0,   79,    2, 0x08 /* Private */,
       9,    0,   80,    2, 0x08 /* Private */,
      10,    0,   81,    2, 0x08 /* Private */,
      11,    1,   82,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWin *_t = static_cast<MainWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_comboBox_keyLen_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_comboBox_mode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_comboBox_blockLen_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_Btn_encrypt_clicked(); break;
        case 4: _t->on_Btn_decrypt_clicked(); break;
        case 5: _t->on_Btn_file_clicked(); break;
        case 6: _t->on_Btn_save_clicked(); break;
        case 7: _t->on_rBtn_compare_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_Btn_file1_clicked(); break;
        case 9: _t->on_Btn_file2_clicked(); break;
        case 10: _t->on_Btn_compare_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWin::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWin.data,
      qt_meta_data_MainWin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWin.stringdata0))
        return static_cast<void*>(const_cast< MainWin*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
