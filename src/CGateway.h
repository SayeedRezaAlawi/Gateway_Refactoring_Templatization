/*
 * CGateway.h
 *
 *      Author: reza
 */

#ifndef CGATEWAY_H_
#define CGATEWAY_H_
#include "CPort.h"
#include "cfg.h"
#include <vector>

template<class PORTA, class PORTB>
class CGateway {
private:
	PORTA m_portA;
	PORTB m_portB;
	CTRingBuffer<uint8_t, 30> m_buffer;
public:
	CGateway();
	RC_t transmitFromAToB();
};

template<class PORTA, class PORTB>
inline CGateway<PORTA, PORTB>::CGateway(){
}

template<class PORTA, class PORTB>
inline RC_t  CGateway<PORTA, PORTB>::transmitFromAToB(){
	RC_t result = RC_ERROR;
	RC_t readResult = RC_ERROR;
	RC_t writeResult = RC_ERROR;
	uint8_t data;
	constexpr uint16_t packagesize_a = PORTA::getDriverPackageSize();
	constexpr uint16_t packagesize_b = PORTB::getDriverPackageSize();
	CTRingBuffer<uint8_t, packagesize_a> buffer_a;
	CTRingBuffer<uint8_t, packagesize_b> buffer_b;

	//Transmit from A to B
	do{
		result = m_portA.readPackage_hw(buffer_a);
		if(result == RC_SUCCESS){
			do{
				readResult = buffer_a.read(data);
				if(readResult == RC_SUCCESS){
					m_buffer.write(data);
				}
			}while(readResult == RC_SUCCESS);
		}
	}while(result == RC_SUCCESS);

	//Write the data
	do{
		result = m_buffer.read(data);
		if(result == RC_SUCCESS){
			writeResult = buffer_b.write(data);
			if(writeResult == RC_BUFFEROVERFLOW){
				m_portB.writePackage_hw(buffer_b);
				buffer_b.clear();
				writeResult = buffer_b.write(data);
			}
		}
	}while(result == RC_SUCCESS);
	m_portB.writePackage_hw(buffer_b);
	buffer_b.clear();
	return RC_SUCCESS;
}
#endif /* CGATEWAY_H_ */
