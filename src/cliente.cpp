#include "network.hpp"
#include "array.hpp"
#include "crypto.hpp"
#include "packet.hpp"
#include "socket.hpp"

using namespace std;

int main() {

	int address; //fd ou endereço de conexão
	array::array *enviarPacote;

	packet Packet;
	socket Socket;

	address = Socket.conectar();

	enviarPacote = Packet.CriarPacoteCheio();

	Socket.ReceberPacote(address, enviarPacote);

	//network::close(address);

	return 0;
}
