/*
 * CCanPort.h
 *
 *      Author: reza
 */

#ifndef CCANPORT_H_
#define CCANPORT_H_

#include "CPort.h"
#include "cfg.h"

#define CAN_DEFAULTBUFFERSIZE 64
#define CAN_DEFAULTBYTESIZE 8

template <uint16_t SIZE>
class CCanPort : public CPort<SIZE> {
public:
	enum port_t{
	CAN1,		/**< \brief CAN Port 1 */
	CAN2, 		/**< \brief CAN Port 2 */
	NONE,		/**< \brief default value no valid port */
	};

	CCanPort(port_t port = NONE, uint32_t baudrate = 1000000);
	RC_t writePackage_hw(CPort<8>::buffer_t const& package);
	RC_t readPackage_hw(CPort<8>::buffer_t& package);
};

template <uint16_t SIZE>
inline CCanPort<SIZE>::CCanPort(port_t port, uint32_t baudrate)
						:CPort<SIZE>(){

}

template <uint16_t SIZE>
inline RC_t CCanPort<SIZE>::writePackage_hw(CPort<8>::buffer_t const& package){
	std::cout << "Just wrote to CAN hardware: Package: [ "
			<< package.operator std::__cxx11::basic_string<char,
			std::char_traits<char>,std::allocator<char>>() << " ]" << std::endl;
	return RC_SUCCESS;
}

template <uint16_t SIZE>
inline RC_t CCanPort<SIZE>::readPackage_hw(CPort<8>::buffer_t& package){
	static uint8_t fakeData = 'a';
	static uint8_t counter = 0;
	RC_t result = RC_ERROR;
	if(counter < 20)
	{
		do{
			result = package.write(fakeData);
			if(result == RC_SUCCESS){
				fakeData++;
				counter++;
			}
		}while(result == RC_SUCCESS && counter < 20);

		std::cout << "Just read from CAN hardware: Package: [ "
				<< package.operator std::__cxx11::basic_string<char,
				std::char_traits<char>,std::allocator<char>>() << " ]" << std::endl;
		return RC_SUCCESS;
	}
	else
	{
		return RC_NODATA;
	}
}

#endif /* CCANPORT_H_ */
