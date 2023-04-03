#include "ezgraver_nejev3.h"

#include <QDebug>
#include <QByteArray>
#include <QBuffer>

#include "specifications.h"

namespace Ez {

void EzGraverNejeV3::start(unsigned char burnTime, unsigned char power) {
	Q_UNUSED(power);
    _setBurnTime(burnTime);
    qDebug() << "starting engrave process";
    _transmit(QByteArray::fromRawData("\xFF\x01\x01\x00", 4));
}

void EzGraverNejeV3::_setBurnTime(unsigned char burnTime) {
    if(burnTime < 0x01 || burnTime > 0xF0) {
        throw new std::out_of_range("burntime out of range");
    }
    qDebug() << "setting burn time to:" << static_cast<int>(burnTime);

    QByteArray payload{"\xFF\x05?\x00", 4};
    payload[2] = burnTime;
    _transmit(payload);
}

void EzGraverNejeV3::pause() {
    qDebug() << "pausing engrave process";
    _transmit(QByteArray::fromRawData("\xFF\x01\x02\x00", 4));
}

void EzGraverNejeV3::reset() {
    qDebug() << "resetting";
    _transmit(QByteArray::fromRawData("\xFF\x04\x01\x00", 4));
}

void EzGraverNejeV3::home() {
    qDebug() << "moving to home";
    _transmit(0xF3);
}

void EzGraverNejeV3::center() {
    qDebug() << "moving to center";
    _transmit(QByteArray::fromRawData("\xFF\x02\x01\x00", 4));
}

void EzGraverNejeV3::preview() {
    qDebug() << "drawing image preview";
    _transmit(QByteArray::fromRawData("\xFF\x02\x02\x00", 4));
}

void EzGraverNejeV3::up() {
    qDebug() << "moving up";
    _transmit(QByteArray::fromRawData("\xFF\x03\x01\x00", 4));
}

void EzGraverNejeV3::down() {
    qDebug() << "moving down";
    _transmit(QByteArray::fromRawData("\xFF\x03\x02\x00", 4));
}

void EzGraverNejeV3::left() {
    qDebug() << "moving left";
    _transmit(QByteArray::fromRawData("\xFF\x03\x03\x00", 4));
}

void EzGraverNejeV3::right() {
    qDebug() << "moving right";
    _transmit(QByteArray::fromRawData("\xFF\x03\x04\x00", 4));
}

int EzGraverNejeV3::erase() {
    qDebug() << "erasing EEPROM";
    _transmit(QByteArray::fromRawData("\xFF\x06\x01\x00", 4));
    return 50;
}

int EzGraverNejeV3::uploadImage(QImage const& originalImage) {
    qDebug() << "converting image to bitmap";
    QImage image{originalImage
            .scaled(Ez::Specifications::ImageWidth, Ez::Specifications::ImageHeight)
            .mirrored()
            .convertToFormat(QImage::Format_Mono)};
    QByteArray bytes{};
    QBuffer buffer{&bytes};
    image.save(&buffer, "BMP");

    // protocol v3 neither needs the BMP header nor the invertion of the pixels.
	return EzGraverNejeV1::uploadImage(bytes.mid(62));
}

}
