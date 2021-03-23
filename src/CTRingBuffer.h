/*
 * CTRingBuffer.h
 *
 *      Author: reza
 */

#ifndef CTRINGBUFFER_H_
#define CTRINGBUFFER_H_
#include "global.h"
#include <string>
#include <iostream>

#define DEFAULTRINGBUFFERSIZE 10

template <class DATA, uint16_t SIZE>
class CTRingBuffer {
private:
	DATA* m_pBuffer;
	uint16_t m_size;
	uint16_t m_fillLevel;
	uint16_t m_writeIdx;
	uint16_t m_readIdx;
public:
	typedef DATA iterator;
	CTRingBuffer();
	RC_t write(const DATA& element);
	RC_t read(DATA& element);
	CTRingBuffer<DATA, SIZE>& operator=(const CTRingBuffer<DATA, SIZE>& other);
	RC_t operator +=(const DATA& element);
	DATA operator *();
	uint16_t first();
	uint16_t last();
	operator std::string() const ;
	RC_t clear();
	uint16_t getNoElements() const;
	virtual ~CTRingBuffer();
};

template<class DATA, uint16_t SIZE>
inline CTRingBuffer<DATA, SIZE>::CTRingBuffer() {
	m_size = SIZE;
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;
	m_pBuffer = new DATA[m_size];
	for(uint16_t i=0; i < m_size; i++){
		m_pBuffer[i] = DATA();
	}
}

template<class DATA, uint16_t SIZE>
inline RC_t CTRingBuffer<DATA, SIZE>::write(const DATA& element) {

	if(m_fillLevel < m_size){
		m_pBuffer[(m_writeIdx++) % m_size] = element;
		m_fillLevel++;
		return RC_SUCCESS;
	}
	else{
		return RC_BUFFEROVERFLOW;
	}
}

template<class DATA, uint16_t SIZE>
inline RC_t CTRingBuffer<DATA, SIZE>::read(DATA &element) {

	if(m_fillLevel > 0){
		element = m_pBuffer[m_readIdx++];
		m_readIdx %= m_size;
		m_fillLevel--;
		return RC_SUCCESS;
	}
	else{
		return RC_BUFFERUNDERFLOW;
	}
}

template<class DATA, uint16_t SIZE>
inline CTRingBuffer<DATA, SIZE>& CTRingBuffer<DATA, SIZE>::operator =(const CTRingBuffer<DATA, SIZE> &other) {
	m_size = other.m_size;
	m_fillLevel = other.m_fillLevel;
	m_readIdx = other.m_readIdx;
	m_writeIdx = other.m_writeIdx;
	m_pBuffer = new DATA[m_size];
	for(uint16_t i=0; i < m_size; i++){
		m_pBuffer[i] = other.m_pBuffer[i];
	}
}

template<class DATA, uint16_t SIZE>
inline RC_t CTRingBuffer<DATA, SIZE>::operator +=(const DATA &element) {
	if(m_fillLevel < m_size){
		m_pBuffer[m_writeIdx++] = element;
		m_writeIdx %= m_size;
		m_fillLevel++;
		return RC_SUCCESS;
	}
	else{
		return RC_BUFFEROVERFLOW;
	}
}

template<class DATA, uint16_t SIZE>
inline DATA CTRingBuffer<DATA, SIZE>::operator *() {
	if (m_fillLevel > 0)
	{
		m_fillLevel--;
		return m_pBuffer[(m_readIdx++) % m_size];
	}
	else
	{
	throw RC_BUFFERUNDERFLOW;
	}
	return 0; //will never be reached
}

template<class DATA, uint16_t SIZE>
inline uint16_t CTRingBuffer<DATA, SIZE>::first() {
	return m_readIdx;
}

template<class DATA, uint16_t SIZE>
inline uint16_t CTRingBuffer<DATA, SIZE>::last() {
	if (m_writeIdx > m_readIdx)
	{
	return m_writeIdx;
	}
	else
	{
	return m_size + m_writeIdx - m_readIdx ;
	}
}

template<class DATA, uint16_t SIZE>
inline RC_t CTRingBuffer<DATA, SIZE>::clear() {
	m_fillLevel = 0;
	m_readIdx = 0;
	m_writeIdx = 0;

	return RC_SUCCESS;
}

template<class DATA, uint16_t SIZE>
inline CTRingBuffer<DATA, SIZE>::operator std::string() const
{
	std::string data = "";
	uint16_t size = m_size;
	uint16_t readIdx= m_readIdx;
	uint16_t fillLevel = m_fillLevel;
	while(fillLevel > 0)
	{
	data += (char) m_pBuffer[readIdx++];
	readIdx %= size;
	fillLevel--;
	}
	return data;
}

template<class DATA, uint16_t SIZE>
inline uint16_t CTRingBuffer<DATA, SIZE>::getNoElements() const{
	return m_fillLevel;
}

template<class DATA, uint16_t SIZE>
inline CTRingBuffer<DATA, SIZE>::~CTRingBuffer() {
	delete [] m_pBuffer;
}

#endif /* CTRINGBUFFER_H_ */
