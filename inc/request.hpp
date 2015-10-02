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
private:
	array::array *objetoDescriptografado;

public:
	
	request();
	request(array::array *conteudo, array::array *tokenT, array::array *chaveSimetrica, int address);
	array::array *getObjeto();
	void criarObjeto(array::array *objetoDescriptografado);

};
#endif
