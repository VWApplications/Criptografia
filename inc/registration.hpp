#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "array.hpp"
#include "cliente.hpp"
#include <iostream>

using namespace std;

class registration: public cliente {
private:
	array::array *chaveSimetrica;
public:
	
	registration();
	registration(array::array *conteudo, int address);
	array::array *getChaveSimetrica();


};
#endif
