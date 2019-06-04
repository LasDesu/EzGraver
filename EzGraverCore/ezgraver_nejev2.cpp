#include "ezgraver_nejev2.h"

#include <QDebug>

namespace Ez {

void EzGraverNejeV2::up() {
    qDebug() << "moving up";
    _transmit("\xf5\x01");
}

void EzGraverNejeV2::down() {
    qDebug() << "moving down";
    _transmit("\xf5\x02");
}

void EzGraverNejeV2::left() {
    qDebug() << "moving left";
    _transmit("\xf5\x03");
}

void EzGraverNejeV2::right() {
    qDebug() << "moving right";
    _transmit("\xf5\x04");
}

}
