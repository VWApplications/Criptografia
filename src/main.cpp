#include "array.hpp"
#include "socket.hpp"
#include "registration.hpp"
#include "authentication.hpp"
#include "request.hpp"
#include <iostream>

using namespace std;

int main() {

	int address;
	array::array *ID;
	array::array *chaveSimetrica;
	//array::array *OBJ;
	//array::array *tokenT;
	//array::array *objeto;

	socket Socket("45.55.185.4", 3000);
	registration Protocolo1;
	//authentication Protocolo2;
	//request Protocolo3;

	ID = Protocolo1.CriarConteudo();
	//OBJ = Protocolo3.CriarConteudo();

	address = Socket.conectar();

	chaveSimetrica = Protocolo1.ProtocoloDeRegistro(ID, address);

	//tokenT = Protocolo2.ProtocoloDeAutenticacao(ID, chaveSimetrica, address);
	
	//objeto = Protocolo3.ProtocoloDeRequisicao(OBJ, tokenT, chaveSimetrica, address);

	//Criar algo para escrever o objeto

	//network::close(address);
	//array::destroy(ID);
	//array::destroy(chaveSimetrica);
	//array::destroy(tokenT);
	//array::destroy(OBJ);


	return 0;
}
