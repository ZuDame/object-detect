/****************************************************************************
** Meta object code from reading C++ file 'unittest.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../solution/unit-test/unittest.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unittest.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UnitTest_t {
    QByteArrayData data[23];
    char stringdata[665];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UnitTest_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UnitTest_t qt_meta_stringdata_UnitTest = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 27),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 32),
QT_MOC_LITERAL(4, 71, 20),
QT_MOC_LITERAL(5, 92, 30),
QT_MOC_LITERAL(6, 123, 23),
QT_MOC_LITERAL(7, 147, 35),
QT_MOC_LITERAL(8, 183, 23),
QT_MOC_LITERAL(9, 207, 35),
QT_MOC_LITERAL(10, 243, 30),
QT_MOC_LITERAL(11, 274, 42),
QT_MOC_LITERAL(12, 317, 30),
QT_MOC_LITERAL(13, 348, 38),
QT_MOC_LITERAL(14, 387, 23),
QT_MOC_LITERAL(15, 411, 31),
QT_MOC_LITERAL(16, 443, 23),
QT_MOC_LITERAL(17, 467, 31),
QT_MOC_LITERAL(18, 499, 36),
QT_MOC_LITERAL(19, 536, 44),
QT_MOC_LITERAL(20, 581, 23),
QT_MOC_LITERAL(21, 605, 33),
QT_MOC_LITERAL(22, 639, 24)
    },
    "UnitTest\0surfLogic_initDefaultValues\0"
    "\0surfLogic_resetMinAndMaxDistance\0"
    "surfLogic_loadImages\0"
    "surfLogic_loadImagesMutantTest\0"
    "surfLogic_createSurfCpu\0"
    "surfLogic_createSurfCpuMutationTest\0"
    "surfLogic_createSurfGpu\0"
    "surfLogic_createSurfGpuMutationTest\0"
    "surfLogic_detectAndDescribeCPU\0"
    "surfLogic_detectAndDescribeCPUMutationTest\0"
    "surfLogic_detectAndDescribeGPU\0"
    "surfLogic_detectAndDescribeGPUMutation\0"
    "surfLogic_runMatcherCPU\0"
    "surfLogic_runMatcherCPUMutation\0"
    "surfLogic_runMatcherGPU\0"
    "surfLogic_runMatcherGPUMutation\0"
    "surfLogic_calculateMinAndMaxDistance\0"
    "surfLogic_calculateMinAndMaxDistanceMutation\0"
    "surfLogic_filterMatches\0"
    "surfLogic_drawKeyPointsAndMatches\0"
    "surfLogic_localiseObject\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UnitTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x08,
       3,    0,  120,    2, 0x08,
       4,    0,  121,    2, 0x08,
       5,    0,  122,    2, 0x08,
       6,    0,  123,    2, 0x08,
       7,    0,  124,    2, 0x08,
       8,    0,  125,    2, 0x08,
       9,    0,  126,    2, 0x08,
      10,    0,  127,    2, 0x08,
      11,    0,  128,    2, 0x08,
      12,    0,  129,    2, 0x08,
      13,    0,  130,    2, 0x08,
      14,    0,  131,    2, 0x08,
      15,    0,  132,    2, 0x08,
      16,    0,  133,    2, 0x08,
      17,    0,  134,    2, 0x08,
      18,    0,  135,    2, 0x08,
      19,    0,  136,    2, 0x08,
      20,    0,  137,    2, 0x08,
      21,    0,  138,    2, 0x08,
      22,    0,  139,    2, 0x08,

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
    QMetaType::Void,
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

void UnitTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UnitTest *_t = static_cast<UnitTest *>(_o);
        switch (_id) {
        case 0: _t->surfLogic_initDefaultValues(); break;
        case 1: _t->surfLogic_resetMinAndMaxDistance(); break;
        case 2: _t->surfLogic_loadImages(); break;
        case 3: _t->surfLogic_loadImagesMutantTest(); break;
        case 4: _t->surfLogic_createSurfCpu(); break;
        case 5: _t->surfLogic_createSurfCpuMutationTest(); break;
        case 6: _t->surfLogic_createSurfGpu(); break;
        case 7: _t->surfLogic_createSurfGpuMutationTest(); break;
        case 8: _t->surfLogic_detectAndDescribeCPU(); break;
        case 9: _t->surfLogic_detectAndDescribeCPUMutationTest(); break;
        case 10: _t->surfLogic_detectAndDescribeGPU(); break;
        case 11: _t->surfLogic_detectAndDescribeGPUMutation(); break;
        case 12: _t->surfLogic_runMatcherCPU(); break;
        case 13: _t->surfLogic_runMatcherCPUMutation(); break;
        case 14: _t->surfLogic_runMatcherGPU(); break;
        case 15: _t->surfLogic_runMatcherGPUMutation(); break;
        case 16: _t->surfLogic_calculateMinAndMaxDistance(); break;
        case 17: _t->surfLogic_calculateMinAndMaxDistanceMutation(); break;
        case 18: _t->surfLogic_filterMatches(); break;
        case 19: _t->surfLogic_drawKeyPointsAndMatches(); break;
        case 20: _t->surfLogic_localiseObject(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UnitTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UnitTest.data,
      qt_meta_data_UnitTest,  qt_static_metacall, 0, 0}
};


const QMetaObject *UnitTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UnitTest::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UnitTest.stringdata))
        return static_cast<void*>(const_cast< UnitTest*>(this));
    return QObject::qt_metacast(_clname);
}

int UnitTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
