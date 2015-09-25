#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include "network.hpp"
#include "array.hpp"
#include <string>

using namespace std;

class socket{
private:
	string servidor;
	int porta;

public:
	
	socket();
	socket(string servidor, int porta);
	void setServidor(string servidor);
	string getServidor();
	void setPorta(int porta);
	int getPorta();

	int conectar();
	void ReceberPacote(int address, array::array *enviarPacote);

};
#endif
