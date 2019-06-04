#ifndef EZGRAVERNEJEV1_H
#define EZGRAVERNEJEV1_H

#include <QSerialPort>

#include <memory>

#include "ezgraver.h"

namespace Ez {

struct EzGraverNejeV1 : EzGraver {
    using EzGraver::EzGraver;

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

#endif // EZGRAVERNEJEV1_H
