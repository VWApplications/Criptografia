#ifndef PACKET_H
#define PACKET_H

#include "array.hpp"
#include "crypto.hpp"
#include <iostream>

class packet {
public:

	packet();

	array::array *criarPacoteVazio(byte tag);
	array::array *criarPacoteCheio(byte TP1, byte TP2, byte TP3, byte TP4, byte tag, byte TC1, byte TC2, array::array* conteudo);

};
#endif



