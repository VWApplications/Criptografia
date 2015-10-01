#ifndef SOCKET_H
#define SOCKET_H

#include "network.hpp"
#include "array.hpp"
#include <iostream>
#include <string>

using namespace std;

class socket {
private:

	string servidor;
	int porta;

public:
	
	socket();
	socket(string servidor, int porta);

	int conectar();
	array::array* ReceberPacote(int address, array::array *pacoteEnviado);
	void setServidor(string servidor);
	string getServidor();
	void setPorta(int porta);
	int getPorta();

};
#endif
