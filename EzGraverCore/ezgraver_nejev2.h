#ifndef EZGRAVERNEJEV2_H
#define EZGRAVERNEJEV2_H

#include <QSerialPort>

#include <memory>

#include "ezgraver_nejev1.h"

namespace Ez {

struct EzGraverNejeV2 : EzGraverNejeV1 {
	using EzGraverNejeV1::EzGraverNejeV1;

    /*! Moves the engraver up. */
    void up() override;

    /*! Moves the engraver down. */
    void down() override;

    /*! Moves the engraver left. */
    void left() override;

    /*! Moves the engraver right. */
    void right() override;
};

}

#endif // EZGRAVERNEJEV2_H
