#include "array.hpp"
#include "packet.hpp"
#include "crypto.hpp"
#include <iostream>

using namespace std;

packet::packet() {
	
}

array::array* packet::criarPacoteVazio(byte tag) {
	
	array::array *pacoteVazio = array::create(7);
				
		pacoteVazio->data[0] = 0x03;
		pacoteVazio->data[1] = 0;
		pacoteVazio->data[2] = 0;
		pacoteVazio->data[3] = 0;
		pacoteVazio->data[4] = tag;
		pacoteVazio->data[5] = 0;
		pacoteVazio->data[6] = 0;

		return pacoteVazio;
}

array::array *packet::criarPacoteCheio(byte TP1, byte TP2, byte TP3, byte TP4, byte tag, byte TC1, byte TC2, array::array* conteudo) {

	array::array *pacoteCheio;
	array::array *HASH;

	pacoteCheio = array::create(27 + conteudo->length);

	pacoteCheio->data[0] = TP1;
	pacoteCheio->data[1] = TP2;
	pacoteCheio->data[2] = TP3;
	pacoteCheio->data[3] = TP4;
	pacoteCheio->data[4] = tag;
	pacoteCheio->data[5] = TC1;
	pacoteCheio->data[6] = TC2;

	HASH = crypto::sha1(conteudo);
	memcpy(pacoteCheio->data+7, conteudo->data, conteudo->length);
	memcpy(pacoteCheio->data + 7 + conteudo->length, HASH->data, 20);

	array::destroy(HASH);

	return pacoteCheio;
}



