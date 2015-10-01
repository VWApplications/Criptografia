#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <string>
#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "cliente.hpp"

using namespace std;

class request: public cliente {
public:
	
	request();
	request(byte *OBJ);
	array::array *ProtocoloDeRequisicao(array::array *conteudo, array::array *tokenT, array::array *chaveSimetrica, int address);
	array::array *CriarConteudo();


};
#endif
