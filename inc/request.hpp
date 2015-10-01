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
	request(array::array *OBJ);
	array::array *ProtocoloDeRequisicao(array::array *conteudo, array::array *tokenT, array::array *chaveSimetrica, int address);


};
#endif
