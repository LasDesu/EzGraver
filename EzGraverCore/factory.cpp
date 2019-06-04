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

std::shared_ptr<EzGraver> create(QString const& portName, QString const& device, int protocol) {
    qDebug() << "Instantiating EzGraver on port" << portName << "with protocol version" << protocol << "for " << device << " device";

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

    switch(devices().indexOf(device)) {
        case 0:
            switch(protocol) {
            case 1:
                return std::make_shared<EzGraverNejeV1>(serial);
            case 2:
                return std::make_shared<EzGraverNejeV2>(serial);
            case 3:
                return std::make_shared<EzGraverNejeV3>(serial);
            default:
                throw std::invalid_argument{QString{"Unsupported protocol '%1' selected for NEJE device familly"}.arg(protocol).toStdString()};
            }
	case 1:
            switch(protocol) {
            case 1:
                return std::make_shared<EzGraverDecaker>(serial);
            default:
                throw std::invalid_argument{QString{"Unsupported protocol '%1' selected for DECAKER device familly"}.arg(protocol).toStdString()};
            }
        default:
            throw std::invalid_argument{QString{"Unsupported device familly '%1' selected"}.arg(device).toStdString()};
    }
}

QList<QString> devices() {
    return QList<QString>{"neje", "decaker"};
}

QList<int> protocols() {
    return QList<int>{1, 2, 3};
}

QStringList availablePorts() {
    auto toPortName = [](QSerialPortInfo const& port) { return port.portName(); };
    auto ports = QSerialPortInfo::availablePorts();
    QStringList result{};

    std::transform(ports.cbegin(), ports.cend(), std::back_inserter(result), toPortName);
    return result;
}

}

