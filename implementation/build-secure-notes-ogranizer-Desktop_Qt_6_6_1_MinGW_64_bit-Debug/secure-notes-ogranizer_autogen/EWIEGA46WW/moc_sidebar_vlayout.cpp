/****************************************************************************
** Meta object code from reading C++ file 'sidebar_vlayout.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../secure-notes-ogranizer/sidebar_vlayout.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sidebar_vlayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS = QtMocHelpers::stringData(
    "sidebar_vlayout",
    "profileButtonClicked",
    "",
    "addNewNoteButtonClicked",
    "editNoteButtonClicked",
    "logoutButtonClicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[16];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[24];
    char stringdata4[22];
    char stringdata5[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS_t qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS = {
    {
        QT_MOC_LITERAL(0, 15),  // "sidebar_vlayout"
        QT_MOC_LITERAL(16, 20),  // "profileButtonClicked"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 23),  // "addNewNoteButtonClicked"
        QT_MOC_LITERAL(62, 21),  // "editNoteButtonClicked"
        QT_MOC_LITERAL(84, 19)   // "logoutButtonClicked"
    },
    "sidebar_vlayout",
    "profileButtonClicked",
    "",
    "addNewNoteButtonClicked",
    "editNoteButtonClicked",
    "logoutButtonClicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSsidebar_vlayoutENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    0,   40,    2, 0x08,    3 /* Private */,
       5,    0,   41,    2, 0x08,    4 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject sidebar_vlayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QVBoxLayout::staticMetaObject>(),
    qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSsidebar_vlayoutENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<sidebar_vlayout, std::true_type>,
        // method 'profileButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addNewNoteButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editNoteButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'logoutButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void sidebar_vlayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sidebar_vlayout *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->profileButtonClicked(); break;
        case 1: _t->addNewNoteButtonClicked(); break;
        case 2: _t->editNoteButtonClicked(); break;
        case 3: _t->logoutButtonClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *sidebar_vlayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sidebar_vlayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSsidebar_vlayoutENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QVBoxLayout::qt_metacast(_clname);
}

int sidebar_vlayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
