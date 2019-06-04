#ifndef EZGRAVER_FACTORY_H
#define EZGRAVER_FACTORY_H

#include "ezgravercore_global.h"

#include <QString>
#include <QList>
#include <QStringList>

#include <memory>

#include "ezgraver.h"

namespace Ez {

/*!
 * Creates an instance and connects to the given \a portName.
 *
 * \param portName The port the connection should be established to.
 * \param device The device familly to connect to.
 * \param protocol The protocol version to use.
 * \return An instance of the EzGraver as a shared pointer.
 * \throws std::runtime_error Thrown if no connection to the specified port could be established.
 * \throws std::invalid_argument Thrown if the provided protocol code is unknown.
 */
EZGRAVERCORESHARED_EXPORT std::shared_ptr<EzGraver> create(QString const& portName, QString const& device = "neje", int protocol = 1);

/*!
 * Gets the available devices.
 *
 * \return The available devices.
 */
EZGRAVERCORESHARED_EXPORT QList<QString> devices();

/*!
 * Gets the available protocols.
 *
 * \return The available protocols.
 */
EZGRAVERCORESHARED_EXPORT QList<int> protocols();

/*!
 * Gets a list of all available ports.
 *
 * \return A list with all ports.
 */
EZGRAVERCORESHARED_EXPORT QStringList availablePorts();

}


#endif // EZGRAVER_FACTORY_H
