#include "criptografia.hpp"
#include "socket.hpp"
#include "request.hpp"
#include "array.hpp"
#include <iostream>

using namespace std;

request::request() {
	byte obj[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	byte *object = obj;
	OBJ = array::create(sizeof(obj), object);
}

request::request(array::array *OBJ) {
	setOBJ(OBJ);
}

array::array *request::ProtocoloDeRequisicao(array::array *conteudo, array::array *tokenT, array::array *chaveSimetrica, int address) {

	criptografia Cript;
	socket Socket("45.55.185.4", 3000);
	array::array *objeto;

	// Criptografar o ID do objeto com a chave S e o token T
	pacoteCriado = Cript.CriptografiaAES(conteudo, tokenT, chaveSimetrica);

	// O servidor irá verificar se o ID bate com o ID do objeto que eles tem, se bater eles retornam o OBJETO criptografado
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);

	// Descriptografa o objeto recebido com a chave S e o tokenT e manda no moodle
	objeto = Cript.DescriptografiaAES(pacoteRecebido, tokenT, chaveSimetrica);

	//array::destroy(pacoteCriado);
	//array::destroy(pacoteRecebido);
	//array::destroy(conteudo);
	//array::destroy(tokenT);
	//array::destroy(chaveSimetrica);

	return objeto;
}
