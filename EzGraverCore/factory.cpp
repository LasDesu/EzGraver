#include "factory.h"

#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include <stdexcept>

#include "ezgraver.h"
#include "ezgraver_decaker.h"
#include "ezgraver_nejev1.h"
#include "ezgraver_nejev2.h"
#include "ezgraver_nejev3.h"

namespace Ez {

std::shared_ptr<EzGraver> create(QString const& portName, QString const& protocol) {
	qDebug() << "Instantiating EzGraver on port" << portName << "with" << protocol << "protocol";

    std::shared_ptr<QSerialPort> serial{new QSerialPort(portName)};
    serial->setBaudRate(QSerialPort::Baud57600, QSerialPort::AllDirections);
    serial->setParity(QSerialPort::Parity::NoParity);
    serial->setDataBits(QSerialPort::DataBits::Data8);
    serial->setStopBits(QSerialPort::StopBits::OneStop);

    if(!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "failed to establish a connection on port" << portName;
        qDebug() << serial->errorString();
        throw std::runtime_error{QString{"failed to connect to port %1 (%2)"}.arg(portName, serial->errorString()).toStdString()};
    }

	switch(protocols().indexOf(protocol)) {
		case 0:
			return std::make_shared<EzGraverNejeV1>(serial);
		case 1:
			return std::make_shared<EzGraverNejeV2>(serial);
		case 2:
			return std::make_shared<EzGraverNejeV3>(serial);
		case 3:
			return std::make_shared<EzGraverDecaker>(serial);
        default:
			throw std::invalid_argument{QString{"unsupported protocol '%1' selected"}.arg(protocol).toStdString()};
    }
}

QList<QString> protocols() {
	return QList<QString>{"NEJE v1", "NEJE v2", "NEJE v3", "Decaker"};
}

QStringList availablePorts() {
    auto toPortName = [](QSerialPortInfo const& port) { return port.portName(); };
    auto ports = QSerialPortInfo::availablePorts();
    QStringList result{};

    std::transform(ports.cbegin(), ports.cend(), std::back_inserter(result), toPortName);
    return result;
}

}

