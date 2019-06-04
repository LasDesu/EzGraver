#include "ezgraver_nejev1.h"

#include <QDebug>

namespace Ez {

void EzGraverNejeV1::up() {
    qDebug() << "moving up";
    _transmit(0xF5);
}

void EzGraverNejeV1::down() {
    qDebug() << "moving down";
    _transmit(0xF6);
}

void EzGraverNejeV1::left() {
    qDebug() << "moving left";
    _transmit(0xF7);
}

void EzGraverNejeV1::right() {
    qDebug() << "moving right";
    _transmit(0xF8);
}

}
