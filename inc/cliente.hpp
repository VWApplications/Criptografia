#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include "network.hpp"
#include "array.hpp"
#include <string>

using namespace std;

class cliente {
private:
	string servidor;
	int porta;

public:
	
	cliente();
	cliente(string servidor, int porta);
	void setServidor(string servidor);
	string getServidor();
	void setPorta(int porta);
	int getPorta();

};
#endif
