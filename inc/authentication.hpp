#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <iostream>
#include <string>
#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "cliente.hpp"

using namespace std;

class authentication: public cliente {
private:
	array::array *tokenT;

public:
	
	authentication(array::array *conteudo, array::array *chaveSimetrica, int address);
	array::array *getTokenT();


};
#endif
