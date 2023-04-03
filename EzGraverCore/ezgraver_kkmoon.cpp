#include "ezgraver_kkmoon.h"

#include <QDebug>
#include <QByteArray>
#include <QBuffer>

#include "specifications.h"

#ifdef __linux__
#include <endian.h>
#define CPU_TO_BE16(x) htobe16(x)
#endif

namespace Ez {

#pragma pack(push, 1)

#define CMD_MOVE			0x01
#define CMD_FAN_ON			0x04
#define CMD_FAN_OFF			0x05
#define	CMD_FUWEI			0x06
#define CMD_RASTER_LINE		0x09
#define CMD_ACTIVATE		0x0A
#define	CMD_ENGRAVE_START	0x14
#define CMD_ENGRAVE_STOP	0x16
#define CMD_HOME			0x17
#define CMD_PAUSE			0x18
#define CMD_RESUME			0x19
#define CMD_VECTOR_LINES	0x1D
#define CMD_PREVIEW_START	0x20
#define CMD_PREVIEW_STOP	0x21
#define CMD_UPLOAD_LINE		0x22
#define CMD_UPLOAD_START	0x23
#define CMD_OFFLINE_ENGRAVE	0x24 // not sure
#define CMD_OFFLINE_STOP	0x27
#define CMD_SETUP			0x28
#define CMD_FD				0xFD // ? not called in original app - yi_dong_z(1)
#define CMD_FE				0xFE // ? not called in original app - yi_dong_z(0)
#define CMD_FF				0xFF

struct cmd_setup
{
	uint8_t stdby_power;
	uint16_t line_delay;
	uint16_t TIM;	// max power? TIM_chong_zhuang_zhi
	uint8_t BU;	// microsteps?
	uint8_t x_compens;
	uint8_t y_compens;
	uint16_t SS;	// steps per ?revolution?
	uint16_t MM1;	// lower speed limit???
	uint16_t KUAI;	// speed limit???
	uint16_t accuracy;
};

struct cmd_move
{
	uint16_t x;
	uint16_t y;
};

struct cmd_preview
{
	uint16_t w;
	uint16_t h;
	uint16_t x;
	uint16_t y;
};

struct cmd_raster_line
{
	uint16_t depth;
	uint16_t power;
	uint16_t y;
};

struct cmd_upload_start
{
	uint16_t left;
	uint16_t right;
	uint16_t width;
	uint16_t height;
	uint16_t power;
	uint16_t depth;
	uint16_t num;
};

struct cmd_vector_start
{
	uint16_t depth;
	uint16_t power;
};

struct cmd_vector_line
{
	uint16_t x1;
	uint16_t y1;
	uint16_t x2;
	uint16_t y2;
};

#pragma pack(pop)


void EzGraverKKmoon::start(unsigned char burnTime, unsigned char power)
{
	qDebug() << "starting engrave process";
	_transmit(QByteArray::fromRawData("\xFF\x01\x01\x00", 4));
}

void EzGraverKKmoon::_sendCommand(uint8_t cmd, QByteArray const& data = QByteArray())
{
	QByteArray pkt;
	unsigned len;

	len = 3;
	if ( data.isNull() )
		len ++;
	else
		len += data.size();

	pkt.resize( 3 );
	pkt[0] = cmd;
	pkt[1] = len >> 8;
	pkt[2] = len & 0xFF;

	if ( data.isNull() )
		pkt.append( (char)0x00 );
	else
		pkt.append( data );

	EzGraver::_transmit( pkt );
}

void EzGraverKKmoon::pause() {
	qDebug() << "pausing engrave process";
	_sendCommand(CMD_PAUSE);
}

void EzGraverKKmoon::reset() {
	qDebug() << "resetting";
	_transmit(QByteArray::fromRawData("\xFF\x04\x01\x00", 4));
}

void EzGraverKKmoon::home() {
	qDebug() << "moving to home";
	_sendCommand(CMD_HOME);
}

void EzGraverKKmoon::center() {
	qDebug() << "moving to center";
	_transmit(QByteArray::fromRawData("\xFF\x02\x01\x00", 4));
}

void EzGraverKKmoon::preview() {
	qDebug() << "drawing image preview";
	_transmit(QByteArray::fromRawData("\xFF\x02\x02\x00", 4));
}

void EzGraverKKmoon::up() {
	qDebug() << "moving up";
	_transmit(QByteArray::fromRawData("\xFF\x03\x01\x00", 4));
}

void EzGraverKKmoon::down() {
	qDebug() << "moving down";
	_transmit(QByteArray::fromRawData("\xFF\x03\x02\x00", 4));
}

void EzGraverKKmoon::left() {
	qDebug() << "moving left";
	_transmit(QByteArray::fromRawData("\xFF\x03\x03\x00", 4));
}

void EzGraverKKmoon::right() {
	qDebug() << "moving right";
	_transmit(QByteArray::fromRawData("\xFF\x03\x04\x00", 4));
}

int EzGraverKKmoon::erase() {
	qDebug() << "erasing EEPROM";
	_transmit(QByteArray::fromRawData("\xFF\x06\x01\x00", 4));
	return 50;
}

int EzGraverKKmoon::uploadImage(QImage const& originalImage) {
	qDebug() << "converting image to bitmap";
	QImage image{originalImage
			.scaled(Ez::Specifications::ImageWidth, Ez::Specifications::ImageHeight)
			.mirrored()
			.convertToFormat(QImage::Format_Mono)};
	QByteArray bytes{};
	QBuffer buffer{&bytes};
	image.save(&buffer, "BMP");

	// protocol v3 neither needs the BMP header nor the invertion of the pixels.
	//return EzGraverNeje::uploadImage(bytes.mid(62));
	return 1;
}

}
