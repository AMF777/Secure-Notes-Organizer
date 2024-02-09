/****************************************************************************
** Meta object code from reading C++ file 'custom_widget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../secure-notes-ogranizer/custom_widget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'custom_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
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
struct qt_meta_stringdata_CLASSCustomWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSCustomWidgetENDCLASS = QtMocHelpers::stringData(
    "CustomWidget",
    "createComponent",
    "TextEditComponent*",
    "",
    "index",
    "deleteComponent",
    "createComponentWithText",
    "text",
    "deleteComponentAppendText",
    "focusAdjacentComponent",
    "currentIndex",
    "forward",
    "initComponentWithLine",
    "NoteComponent&",
    "component"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCustomWidgetENDCLASS_t {
    uint offsetsAndSizes[30];
    char stringdata0[13];
    char stringdata1[16];
    char stringdata2[19];
    char stringdata3[1];
    char stringdata4[6];
    char stringdata5[16];
    char stringdata6[24];
    char stringdata7[5];
    char stringdata8[26];
    char stringdata9[23];
    char stringdata10[13];
    char stringdata11[8];
    char stringdata12[22];
    char stringdata13[15];
    char stringdata14[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCustomWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCustomWidgetENDCLASS_t qt_meta_stringdata_CLASSCustomWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "CustomWidget"
        QT_MOC_LITERAL(13, 15),  // "createComponent"
        QT_MOC_LITERAL(29, 18),  // "TextEditComponent*"
        QT_MOC_LITERAL(48, 0),  // ""
        QT_MOC_LITERAL(49, 5),  // "index"
        QT_MOC_LITERAL(55, 15),  // "deleteComponent"
        QT_MOC_LITERAL(71, 23),  // "createComponentWithText"
        QT_MOC_LITERAL(95, 4),  // "text"
        QT_MOC_LITERAL(100, 25),  // "deleteComponentAppendText"
        QT_MOC_LITERAL(126, 22),  // "focusAdjacentComponent"
        QT_MOC_LITERAL(149, 12),  // "currentIndex"
        QT_MOC_LITERAL(162, 7),  // "forward"
        QT_MOC_LITERAL(170, 21),  // "initComponentWithLine"
        QT_MOC_LITERAL(192, 14),  // "NoteComponent&"
        QT_MOC_LITERAL(207, 9)   // "component"
    },
    "CustomWidget",
    "createComponent",
    "TextEditComponent*",
    "",
    "index",
    "deleteComponent",
    "createComponentWithText",
    "text",
    "deleteComponentAppendText",
    "focusAdjacentComponent",
    "currentIndex",
    "forward",
    "initComponentWithLine",
    "NoteComponent&",
    "component"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCustomWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    3, 0x08,    1 /* Private */,
       5,    1,   53,    3, 0x08,    3 /* Private */,
       6,    2,   56,    3, 0x08,    5 /* Private */,
       8,    2,   61,    3, 0x08,    8 /* Private */,
       9,    2,   66,    3, 0x08,   11 /* Private */,
      12,    2,   71,    3, 0x08,   14 /* Private */,

 // slots: parameters
    0x80000000 | 2, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,    4,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject CustomWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSCustomWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCustomWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCustomWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CustomWidget, std::true_type>,
        // method 'createComponent'
        QtPrivate::TypeAndForceComplete<TextEditComponent *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'deleteComponent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'createComponentWithText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'deleteComponentAppendText'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'focusAdjacentComponent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'initComponentWithLine'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<NoteComponent &, std::false_type>
    >,
    nullptr
} };

void CustomWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { TextEditComponent* _r = _t->createComponent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< TextEditComponent**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->deleteComponent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->createComponentWithText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 3: _t->deleteComponentAppendText((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->focusAdjacentComponent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 5: _t->initComponentWithLine((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NoteComponent&>>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject *CustomWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCustomWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CustomWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
