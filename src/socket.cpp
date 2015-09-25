#include "network.hpp"
#include "socket.hpp"
#include "array.hpp"
#include <string>

using namespace std;

socket::socket() {
	setServidor("45.55.185.4");
	setPorta(3001);
}

socket::socket(string servidor, int porta) {
	setServidor(servidor);
	setPorta(porta);
}

void socket::setServidor(string servidor) {
	this->servidor = servidor;
}

string socket::getServidor() {
	return servidor;
}

void socket::setPorta(int porta) {
	this->porta = porta;
}

int socket::getPorta() {
	return porta;
}

int socket::conectar() {

	int address;

	string host = getServidor();
	int port = getPorta();

	cout << "Iniciando Servidor ..." << endl;

	if((address = network::connect(host, port))<0) {
		cout << "Conexão falhou!" << endl;
	}else{
		cout << "Conexão " << address << " OK!" << endl;
	}

	return address;
}

void socket::ReceberPacote(int address, array::array *enviarPacote) {

	array::array *receberPacote;

	network::write(address, enviarPacote);

	if((receberPacote = network::read(address)) == nullptr) {
		cout << "A leitura do pacote falhou!" << endl;
	}else{
		cout << "Imprimindo conteudo do pacote de " << receberPacote->length << " bytes recebido" << endl;
		for(int i=0; i<((int) receberPacote->length); i++) {
			printf("%x ", receberPacote->data[i]);
		}
		printf("\n");
	}

	array::destroy(enviarPacote);

}
