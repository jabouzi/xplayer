/****************************************************************************
** Meta object code from reading C++ file 'player.h'
**
** Created: Thu Apr 22 19:11:35 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/player.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Player[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      19,    7,    7,    7, 0x08,
      26,    7,    7,    7, 0x08,
      33,    7,    7,    7, 0x08,
      40,    7,    7,    7, 0x08,
      47,    7,    7,    7, 0x08,
      54,    7,    7,    7, 0x08,
      65,    7,    7,    7, 0x08,
      78,    7,    7,    7, 0x08,
      91,   89,    7,    7, 0x08,
     133,    7,    7,    7, 0x08,
     146,    7,    7,    7, 0x08,
     152,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Player[] = {
    "Player\0\0finished()\0next()\0prev()\0"
    "load()\0play()\0stop()\0autoPlay()\0"
    "updateTime()\0seekFile()\0,\0"
    "stateChanged(Phonon::State,Phonon::State)\0"
    "updateInfo()\0add()\0changeVolume()\0"
};

const QMetaObject Player::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Player,
      qt_meta_data_Player, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Player::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Player::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Player))
        return static_cast<void*>(const_cast< Player*>(this));
    if (!strcmp(_clname, "Ui::Player"))
        return static_cast< Ui::Player*>(const_cast< Player*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: finished(); break;
        case 1: next(); break;
        case 2: prev(); break;
        case 3: load(); break;
        case 4: play(); break;
        case 5: stop(); break;
        case 6: autoPlay(); break;
        case 7: updateTime(); break;
        case 8: seekFile(); break;
        case 9: stateChanged((*reinterpret_cast< Phonon::State(*)>(_a[1])),(*reinterpret_cast< Phonon::State(*)>(_a[2]))); break;
        case 10: updateInfo(); break;
        case 11: add(); break;
        case 12: changeVolume(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
