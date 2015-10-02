#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "registration.hpp"
#include "array.hpp"
#include <iostream>

using namespace std;

registration::registration() {
	byte id[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	byte *conteudo = id;
	ID = array::create(sizeof(id), conteudo);
}

registration::registration(array::array *conteudo, int address) {

	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);
	
	array::array *REQUEST_REGISTRATION;
	array::array *REGISTER_ID;
	array::array *REGISTERED;
	array::array *symmetricKey;

	REQUEST_REGISTRATION = Packet.criarPacoteVazio(0xC0);

	Socket.receberPacote(address, REQUEST_REGISTRATION);

	REGISTER_ID = Packet.criarPacoteCheio(0x17, 0x02, 0, 0, 0xC2, 0x00, 0x02, conteudo);

	REGISTERED = Socket.receberPacote(address, REGISTER_ID);

	symmetricKey = array::create(512);

	memcpy(symmetricKey->data, REGISTERED->data + 7, 512);

	chaveSimetrica = Cript.descriptografiaRSA(symmetricKey);

}

array::array *registration::getChaveSimetrica() {
	return chaveSimetrica;
}

