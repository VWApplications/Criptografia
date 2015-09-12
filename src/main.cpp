#include "network.hpp"


using namespace std;

int main() {

	cout << "Conectando ao servidor..." << endl;

	int conectar = network::connect("127.0.0.1", 3001);

	if(conectar < 0) {
		cout << "Conexão com o servidor falhou" << endl;
		return 1;
	}else{
		cout << "Conexão estabelecida com sucesso" << endl;
	}

	return 0;
}
