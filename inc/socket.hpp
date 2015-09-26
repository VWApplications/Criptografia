#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include "network.hpp"
#include "array.hpp"
#include "cliente.hpp"
#include <string>

using namespace std;

class socket: public cliente {
public:
	
	socket();
	socket(string servidor, int porta);

	int conectar();
	array::array* ReceberPacote(int address, array::array *enviarPacote);

};
#endif
