#ifndef PACKET_H
#define PACKET_H

#include "array.hpp"
#include "crypto.hpp"
#include <iostream>

class packet {
public:

	packet();

	array::array* CriarPacoteVazio(byte tag);
	array::array* CriarPacoteCheio(int tamanhoDoPacote, byte TP1, byte TP2, byte TP3, byte TP4, byte tag, int tamanhoDoConteudo, byte TC1, byte TC2, array::array* conteudo);

};
#endif

