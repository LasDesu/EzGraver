#include "ezgraver_nejev1.h"

#include "specifications.h"

#include <QBitmap>
#include <QBuffer>
#include <QDebug>

namespace Ez {

void EzGraverNejeV1::start(unsigned char burnTime, unsigned char power) {
	Q_UNUSED(power);
	_setBurnTime(burnTime);
	qDebug() << "starting engrave process";
	_transmit(0xF1);
}

void EzGraverNejeV1::_setBurnTime(unsigned char burnTime) {
	if(burnTime < 0x01 || burnTime > 0xF0) {
		throw new std::out_of_range("burntime out of range");
	}
	qDebug() << "setting burn time to:" << static_cast<int>(burnTime);
	_transmit(burnTime);
}

void EzGraverNejeV1::pause() {
	qDebug() << "pausing engrave process";
	_transmit(0xF2);
}

void EzGraverNejeV1::reset() {
	qDebug() << "resetting";
	_transmit(0xF9);
}

void EzGraverNejeV1::home() {
	qDebug() << "moving to home";
	_transmit(0xF3);
}

void EzGraverNejeV1::center() {
	qDebug() << "moving to center";
	_transmit(0xFB);
}

void EzGraverNejeV1::preview() {
	qDebug() << "drawing image preview";
	_transmit(0xF4);
}

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

int EzGraverNejeV1::erase() {
	qDebug() << "erasing EEPROM";
	_transmit(QByteArray{8, '\xFE'});
	return 6000;
}

int EzGraverNejeV1::uploadImage(QImage const& originalImage) {
	qDebug() << "converting image to bitmap";
	QImage image{originalImage
			.scaled(Ez::Specifications::ImageWidth, Ez::Specifications::ImageHeight)
			.mirrored()
			.convertToFormat(QImage::Format_Mono)};
	image.invertPixels();

	QByteArray bytes{};
	QBuffer buffer{&bytes};
	image.save(&buffer, "BMP");
	return uploadImage(bytes);
}

int EzGraverNejeV1::uploadImage(QByteArray const& image) {
	qDebug() << "uploading image";
	// Data is chunked in order to get at least some progress updates
	_transmit(image, 8192);
	return image.size();
}

}
