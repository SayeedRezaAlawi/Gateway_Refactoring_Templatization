/*
 * CUartPort.h
 *
 *      Author: reza
 */

#ifndef CUARTPORT_H_
#define CUARTPORT_H_
#include "CPort.h"

#define UART_DEFAULTBUFFERSIZE 20
#define UART_DEFAULTBYTESIZE 1

template <uint16_t SIZE>
class CUartPort : public CPort<SIZE> {
public:
	enum port_t{
		ASCLIN1,		/**< \brief ASCLIN Port 1, per default mapped to USB bridge */
		ASCLIN2, 		/**< \brief ASCLIN Port 2, can be mapped to PIN P12(0),PIN P12(2) */
		ASCLIN3, 		/**< \brief ASCLIN Port 3, can be mapped to PIN P12(3),PIN P12(4) */
		ASCLIN4, 		/**< \brief ASCLIN Port 4, can be mapped to PIN P12(1),PIN P12(5) */
		ASCLIN5, 		/**< \brief ASCLIN Port 5, can be mapped to PIN P12(6) */
		NONE,			/**< \brief default value no valid port */
	};

	enum parity_t{
		ODD, 			/**< \brief ODD parity, will detect single bit transmission errors */
		EVEN, 			/**< \brief EVEN parity, will detect single bit transmission errors */
		NOPARITY,		/**< \brief NO parity check, only recommended for baudrates below 115200 */
	};

public:
	CUartPort(
			port_t port = NONE,
			uint32_t baudrate = 115200,
			uint8_t bits = 8,
			parity_t parity = NOPARITY,
			uint8_t stopbits = 1);

	RC_t writePackage_hw(CPort<1>::buffer_t const& package);
	RC_t readPackage_hw(CPort<1>::buffer_t& package);

};


template <uint16_t SIZE>
inline CUartPort<SIZE>::CUartPort(port_t port,
			uint32_t baudrate,
			uint8_t bits,
			parity_t parity,
			uint8_t stopbits) : CPort<SIZE>(){
}

template <uint16_t SIZE>
inline RC_t CUartPort<SIZE>::writePackage_hw(CPort<1>::buffer_t const& package){
	std::cout << "Just wrote to UART hardware: Package: [ "
				<< package.operator std::__cxx11::basic_string<char,
				std::char_traits<char>,std::allocator<char>>() << " ]" << std::endl;
	return RC_SUCCESS;
}

template <uint16_t SIZE>
inline RC_t CUartPort<SIZE>::readPackage_hw(CPort<1>::buffer_t& package){
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

		std::cout << "Just read from UART hardware: Package: [ "
				<< package.operator std::__cxx11::basic_string<char,
				std::char_traits<char>,std::allocator<char>>() << " ]" << std::endl;
		return RC_SUCCESS;
	}
	else
	{
		return RC_NODATA;
	}
}
#endif /* CUARTPORT_H_ */
