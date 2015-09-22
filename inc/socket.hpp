#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include "network.hpp"
#include "array.hpp"

class socket{
public:
	int conectar();
	void ReceberPacote(int address, array::array *enviarPacote);

};
#endif
