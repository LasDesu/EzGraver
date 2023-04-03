#include "ezgraver.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include <iterator>
#include <algorithm>
#include <functional>

namespace Ez {

EzGraver::EzGraver(std::shared_ptr<QSerialPort> serial) : _serial{serial} {}

EzGraver::~EzGraver() {
	qDebug() << "EzGraver is being destroyed, closing serial port";
	_serial->close();
}

void EzGraver::awaitTransmission(int msecs) {
	_serial->waitForBytesWritten(msecs);
}

std::shared_ptr<QSerialPort> EzGraver::serialPort() {
	return _serial;
}

void EzGraver::_transmit(unsigned char const& data) {
	_transmit(QByteArray{1, static_cast<char>(data)});
}

void EzGraver::_transmit(QByteArray const& data) {
	qDebug() << "transmitting" << data.size() << "bytes:" << data.toHex();
	_serial->write(data);
	_serial->flush();
}

void EzGraver::_transmit(QByteArray const& data, int chunkSize) {
	qDebug() << "transmitting" << data.size() << "bytes in chunks of size" << chunkSize;
	for(int i{0}; i < data.size(); i += chunkSize) {
		_serial->write(data.mid(i, chunkSize));
		_serial->flush();
	}
}

}

