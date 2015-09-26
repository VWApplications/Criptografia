#include "network.hpp"
#include "array.hpp"
#include "crypto.hpp"
#include "packet.hpp"
#include "socket.hpp"

using namespace std;

array::array *CriptografiaRSA(array::array *dados) {
	
	array::array *DadosCriptografados;
	RSA *LerChavePublica;

	LerChavePublica = crypto::rsa_read_public_key_from_PEM("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/server_pk.pem");

	DadosCriptografados = crypto::rsa_encrypt(dados, LerChavePublica);

	array::destroy(dados);
	//crypto::rsa_destroy_key(LerChavePublica);

	return DadosCriptografados;

}

array::array *DescriptografiaRSA(array::array *dados) {
	
	array::array *DadosDescriptografados;
	RSA *LerChavePrivada;

	LerChavePrivada = crypto::rsa_read_private_key_from_PEM("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/private.pem");

	DadosDescriptografados = crypto::rsa_decrypt(dados, LerChavePrivada);

	array::destroy(dados);
	//crypto::rsa_destroy_key(LerChavePrivada);

	return DadosDescriptografados;

}



int main() {

	int address; //fd ou endereço de conexão
	array::array *enviarPacote; // ID empacotado
	array::array *dadosCriptografados; // ID criptografado
	array::array *dadosDescriptografados; //Chave simetrica S descriptografada
	array::array *receberPacote; // Chave simetrica S criptografada
	byte id[] = {0xc6, 0x67, 0x0e, 0x84, 0xc0, 0xca, 0xbc, 0x82};
	array::array* ID = array::create(8, id);

	//Construtores
	packet Packet;
	socket Socket("45.55.185.4", 3000);

	//Conectando ao servidor
	address = Socket.conectar();

	// Recebendo o pacote REQUEST_REGISTRATION e guardando na variável "enviarPacote"
	enviarPacote = Packet.CriarPacoteVazio(0xC0);

	// Enviar o pacote REQUEST_REGISTRATION que vai retornar o pacote REGISTRATION_START que será armazenado na variável "receberPacote"
	receberPacote = Socket.ReceberPacote(address, enviarPacote);

	// Criptografa o ID com a chave publica do servidor
	dadosCriptografados = CriptografiaRSA(ID);

	// Receber o ID empacotado e guarda na variável "enviarPacote"
	enviarPacote = Packet.CriarPacoteCheio(0xC2, 31,0x1F,0x00,0x00,0x00, 8,0x08,0x00, dadosCriptografados);

	// Manda o ID criptografado para o servidor e o servidor retorna a chave simetrica S criptografada
	receberPacote = Socket.ReceberPacote(address, enviarPacote);

	// Descriptografa a a chave Simetrica e armazena na variável "dadosDescriptografados"
	dadosDescriptografados = DescriptografiaRSA(receberPacote);



	// Fechar o servidor e desalocar memória
	//network::close(address);
	//array::destroy(enviarPacote);
	//array::destroy(dadosCriptografados);
	//array::destroy(dadosDescriptografados);
	//array::destroy(receberPacotes);


	return 0;
}
