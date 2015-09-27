#include "network.hpp"
#include "array.hpp"
#include "crypto.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include <iostream>

using namespace std;

array::array *CriptografiaRSA(array::array *dados) {

	array::array *DadosCriptografados;
	RSA *LerChavePublica;

	//cout << *dados << endl;

	LerChavePublica = crypto::rsa_read_public_key_from_PEM("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/server_pk.pem");

	DadosCriptografados = crypto::rsa_encrypt(dados, LerChavePublica);

	cout << *DadosCriptografados << endl;

	//array::destroy(dados);
	//crypto::rsa_destroy_key(LerChavePublica);

	return DadosCriptografados;

}

array::array *DescriptografiaRSA(array::array *dados) {
	
	array::array *DadosDescriptografados;
	RSA *LerChavePrivada;

	LerChavePrivada = crypto::rsa_read_private_key_from_PEM("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/private.pem");

	DadosDescriptografados = crypto::rsa_decrypt(dados, LerChavePrivada);

	//array::destroy(dados);
	//crypto::rsa_destroy_key(LerChavePrivada);

	return DadosDescriptografados;

}



int main() {

	int address1; //fd ou endereço de conexão
	array::array *enviarPacote;
	array::array *dadosCriptografados;
	//array::array *dadosDescriptografados;
	array::array *receberPacote;
	byte ID[] = {0xc6, 0x67, 0x0e, 0x84, 0xc0, 0xca, 0xbc, 0x82};
	byte* id = ID;
	array::array* conteudo = array::create(8, id);

	//Construtores
	packet Packet;
	socket Socket("45.55.185.4", 3000);

	//Conectando ao servidor
	address1 = Socket.conectar();

	// Criptografa o ID com a chave publica do servidor
	dadosCriptografados = CriptografiaRSA(conteudo);

	// Receber o pacote e guarda na variável "enviarPacote"
	enviarPacote = Packet.CriarPacoteCheio(535,0x17,0x02,0x00,0x00,0xC2,512,0x00,0x02, dadosCriptografados);
	cout << *enviarPacote << endl;

	// Manda o ID criptografado para o servidor e o servidor retorna a chave simetrica S criptografada
	receberPacote = Socket.ReceberPacote(address1, enviarPacote);

	// Descriptografa a a chave Simetrica e armazena na variável "dadosDescriptografados"
	//dadosDescriptografados = DescriptografiaRSA(receberPacote);



	// Fechar o servidor e desalocar memória
	//network::close(address);
	//array::destroy(enviarPacote);
	//array::destroy(dadosCriptografados);
	//array::destroy(dadosDescriptografados);
	//array::destroy(receberPacotes);


	return 0;
}
