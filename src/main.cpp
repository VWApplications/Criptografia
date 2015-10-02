#include "array.hpp"
#include "socket.hpp"
#include "criptografia.hpp"
#include "registration.hpp"
#include "authentication.hpp"
#include "request.hpp"
#include <iostream>

using namespace std;

int main() {

	int address;
	array::array *ID;
	array::array *OBJ;
	array::array *IDcriptografado;
	array::array *chaveSimetrica;
	array::array *tokenT;
	array::array *objeto;

	socket Socket("45.55.185.4", 3000);
	criptografia Cript;
	registration Protocolo1;
	request Protocolo3;

	ID = Protocolo1.getID();
	OBJ = Protocolo3.getOBJ();

	address = Socket.conectar();

	IDcriptografado = Cript.criptografiaRSA(ID);

	registration ProtocoloDeRegistro(IDcriptografado, address);

	chaveSimetrica = ProtocoloDeRegistro.getChaveSimetrica();

	authentication ProtocoloDeAutenticacao(IDcriptografado, chaveSimetrica, address);

	tokenT = ProtocoloDeAutenticacao.getTokenT();
	
	request ProtocoloDeRequisicao(OBJ, tokenT, chaveSimetrica, address);

	objeto = ProtocoloDeRequisicao.getObjeto();

	ProtocoloDeRequisicao.criarObjeto(objeto);

	//network::close(address);
	//array::destroy(ID);
	//array::destroy(chaveSimetrica);
	//array::destroy(tokenT);
	//array::destroy(objeto);


	return 0;
}
