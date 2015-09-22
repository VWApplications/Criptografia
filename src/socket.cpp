#include "network.hpp"
#include "socket.hpp"
#include "array.hpp"

using namespace std;

int socket::conectar() {

	int address;

	cout << "Iniciando Servidor ..." << endl;

	if((address = network::connect("45.55.185.4", 3001))<0) {
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
