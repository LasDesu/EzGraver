#ifndef EZGRAVERNEJEV1_H
#define EZGRAVERNEJEV1_H

#include <QSerialPort>

#include <memory>

#include "ezgraver.h"

namespace Ez {

struct EzGraverNejeV1 : EzGraver {
	using EzGraver::EzGraver;

	/*!
	 * Starts the engraving process with the given \a burnTime.
	 *
	 * \param burnTime The burn time to use in milliseconds.
	 */
	virtual void start(unsigned char burnTime, unsigned char power);

	/*!
	 * Pauses the engraving process at the given location. The process
	 * can be continued by invoking start.
	 */
	virtual void pause();

	/*! Resets the engraver. */
	virtual void reset();

	/*! Moves the engraver to the home position. */
	virtual void home();

	/*! Moves the engraver to the center. */
	virtual void center();

	/*! Draws a preview of the currently loaded image. */
	virtual void preview();

    /*! Moves the engraver up. */
    void up() override;

    /*! Moves the engraver down. */
    void down() override;

    /*! Moves the engraver left. */
    void left() override;

    /*! Moves the engraver right. */
    void right() override;

	virtual int erase();

	/*!
	 * Uploads the given \a image to the EEPROM. It is mandatory to use \a erase()
	 * it prior uploading an image. The image will automatically be scaled, inverted,
	 * mirrored and converted to a monochrome bitmap.
	 *
	 * \param image The image to upload to the EEPROM for engraving.
	 * \return The number of bytes being sent to the device.
	 */
	virtual int uploadImage(QImage const& image);

	/*!
	 * Uploads any given \a image byte array to the EEPROM. It has to be a monochrome
	 * bitmap of the dimensions 512x512. Every white pixel is being engraved.
	 *
	 * \param image The image byte array to upload to the EEPROM.
	 * \return The number of bytes being sent to the device.
	 */
	int uploadImage(QByteArray const& image);

	/*!
	 * Waits until the current serial port buffer is fully written to the device.
	 *
	 * \param msecs The time in milliseconds to await the transmission to complete.
	 */
	void awaitTransmission(int msecs=-1);

private:
	void _setBurnTime(unsigned char burnTime);
};

}

#endif // EZGRAVERNEJEV1_H
