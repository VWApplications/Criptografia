#include "network.hpp"
#include "array.hpp"
#include "crypto.hpp"
#include "packet.hpp"
#include "socket.hpp"

using namespace std;

array::array *Criptografia(array::array *enviarPacote) {
	
	array::array *ArrayCriptografado;
	RSA *LerChave;

	LerChave = crypto::rsa_read_public_key_from_PEM("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/server_pk.pem");

	ArrayCriptografado = crypto::rsa_encrypt(enviarPacote, LerChave);

	return ArrayCriptografado;

}

int main() {

	int address; //fd ou endereço de conexão
	array::array *enviarPacote;
	array::array *ArrayCriptografado;

	packet Packet;
	socket Socket("45.55.185.4", 3001);

	address = Socket.conectar();

	enviarPacote = Packet.CriarPacoteCheio();

	ArrayCriptografado = Criptografia(enviarPacote);

	Socket.ReceberPacote(address, ArrayCriptografado);
	//Socket.ReceberPacote(address, enviarPacote);

	//network::close(address);

	return 0;
}
