#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "authentication.hpp"
#include "array.hpp"
#include <iostream>

using namespace std;

authentication::authentication(array::array *conteudo, array::array *chaveSimetrica, int address) {

	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);

	array::array *REQUEST_AUTH;
	array::array *AUTH_START;
	array::array *REQUEST_CHALLENGE;
	array::array *CHALLENGE;
	array::array *AUTHENTICATE;
	array::array *AUTHENTICATED;

	array::array *tokenA;
	array::array *tokenA_descriptografado;
	array::array *M;
	array::array *M_descriptografado;
	array::array *tokenTcriptografado;

	REQUEST_AUTH = Packet.criarPacoteCheio(0x17, 0x02, 0, 0, 0xA0, 0x00, 0x02, conteudo);

	AUTH_START = Socket.receberPacote(address, REQUEST_AUTH);

	tokenA = array::create(AUTH_START->length-27);
	memcpy(tokenA->data, AUTH_START->data + 7, AUTH_START->length-27);
	tokenA_descriptografado = Cript.descriptografiaRSA(tokenA);

	REQUEST_CHALLENGE = Packet.criarPacoteVazio(0xA2);

	CHALLENGE = Socket.receberPacote(address, REQUEST_CHALLENGE);

	M = array::create(CHALLENGE->length-27);
	memcpy(M->data, CHALLENGE->data + 7, CHALLENGE->length-27);
	M_descriptografado = crypto::aes_decrypt(M, tokenA_descriptografado, chaveSimetrica);

	AUTHENTICATE = Packet.criarPacoteCheio(0x27, 0, 0, 0, 0xA5, 0x10, 0, M_descriptografado);

	AUTHENTICATED = Socket.receberPacote(address, AUTHENTICATE);


	tokenTcriptografado = array::create(AUTHENTICATED->length-27);
	memcpy(tokenTcriptografado->data, AUTHENTICATED->data + 7, AUTHENTICATED->length-27);
	tokenT = crypto::aes_decrypt(tokenTcriptografado, tokenA_descriptografado, chaveSimetrica);

	array::destroy(tokenA);
	array::destroy(tokenA_descriptografado);

}

array::array *authentication::getTokenT() {
	return tokenT;
}
