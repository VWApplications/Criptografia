#include "network.hpp"
#include "socket.hpp"
#include "array.hpp"
#include "packet.hpp"

using namespace std;

int address;

int socket::conectar() {

	cout << "Iniciando Servidor ..." << endl;

	if((address = network::connect("45.55.185.4", 3001))<0) {
		cout << "Conexão falhou!" << endl;
	}else{
		cout << "Conexão " << address << " OK!" << endl;
	}

}

int socket::escrever(){

	packet Packet;

	const array::array *enviarPacote = Packet.Criarpacote();

	network::write(address, enviarPacote);

	return address;

}

