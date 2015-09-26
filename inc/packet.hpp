#ifndef PACKET_H
#define PACKET_H

#include "array.hpp"
#include <iostream>

class packet {
private:
	byte tag;
	int TamanhoDoPacote;
	int TamanhoDoConteudo;


public:

	packet();
	
	void setTag(byte tag);
	byte getTag();

	array::array* CriarPacoteVazio(byte tag);
	array::array* CriarPacoteCheio(byte tag, int tamanhoDoPacote, byte TP1, byte TP2, byte TP3, byte TP4, int tamanhoDoConteudo, byte TC1, byte TC2, array::array* conteudo);

};
#endif


