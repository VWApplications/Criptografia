#include "network.hpp"
#include "cliente.hpp"
#include "array.hpp"
#include <string>

using namespace std;

cliente::cliente() {
	servidor = "45.55.185.4";
	porta = 3001;
}

cliente::cliente(string servidor, int porta) {
	setServidor(servidor);
	setPorta(porta);
}

void cliente::setServidor(string servidor) {
	this->servidor = servidor;
}

string cliente::getServidor() {
	return servidor;
}

void cliente::setPorta(int porta) {
	this->porta = porta;
}

int cliente::getPorta() {
	return porta;
}

