/*
 * CPort.h
 *
 *      Author: reza
 */

#ifndef CPORT_H_
#define CPORT_H_
#include "CTRingBuffer.h"
#include <string>

template <uint16_t SIZE>
class CPort {
public:
	typedef CTRingBuffer<uint8_t, SIZE> buffer_t;
protected:
	buffer_t m_ringBufferTx;
	buffer_t m_ringBufferRx;
public:
	CPort();
	virtual RC_t writePackage_hw(buffer_t const& package) = 0;
	virtual RC_t readPackage_hw(buffer_t& package) = 0;
	static constexpr uint16_t getDriverPackageSize();
};

template <uint16_t SIZE>
inline CPort<SIZE>::CPort(){
}

template <uint16_t SIZE>
inline constexpr uint16_t CPort<SIZE>::getDriverPackageSize(){
	return SIZE;
}

#endif /* CPORT_H_ */
