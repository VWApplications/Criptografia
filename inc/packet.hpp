#ifndef PACKET_H
#define PACKET_H

#include "array.hpp"
#include <iostream>

class packet {
public:

	array::array* CriarPacoteVazio();
	array::array* CriarPacoteCheio();

};
#endif


