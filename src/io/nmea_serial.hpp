#ifndef __IO__NMEA_SERIAL__HPP__
#define __IO__NMEA_SERIAL__HPP__

#include <io/device.hpp>
#include <nmea/sentence.hpp>

namespace io
{

/// This class reads NMEA sentences from a device. Normally this would
/// be a serial character device (e.g. /dev/ttyS0 or /dev/ttyUSB0).
///
/// In order to use this NMEA reader, it must be subclassed.
///
/// @example read_nmea.cpp
class nmea_serial
{
public:
	nmea_serial(std::unique_ptr<device>&& dev);
	nmea_serial(const std::string& name);

	void close();
	void read() throw(std::runtime_error);

protected:
	virtual void process_sentence(const std::string&) = 0;

private:
	void process_nmea() throw(std::runtime_error);
	void read_data() throw(std::runtime_error);

	char raw;
	std::string sentence;
	std::unique_ptr<device> dev; ///< Device to read data from.
};
}

#endif