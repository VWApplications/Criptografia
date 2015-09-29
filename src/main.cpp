#include "network.hpp"
#include "array.hpp"
#include "crypto.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "criptografia.hpp"
#include <iostream>

using namespace std;

int main() {

	int address; //fd ou endereço de conexão
	array::array *enviarPacote;
	array::array *receberPacote;
	array::array *IDCriptografado;
	//array::array *chaveSimetrica;
	//array::array *tokenA;
	//array::array *tokenT;
	//array::array *dadosDescriptografados;
	//array::array *objeto;
	byte ID[] = {0xc6, 0x67, 0x0e, 0x84, 0xc0, 0xca, 0xbc, 0x82};
	byte* id = ID;
	array::array* conteudo = array::create(8, id);

	//Construtores
	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);

	//Conectando ao servidor
	address = Socket.conectar();

// PROTOCOLO DE REGISTRO -------------------------------------------------------------------------------------------------------------------

	// Criptografa o ID com a chave publica do servidor
	IDCriptografado = Cript.CriptografiaRSA(conteudo);

	// Receber o pacote e guarda na variável "enviarPacote"
	enviarPacote = Packet.CriarPacoteCheio(535,0x17,0x02,0x00,0x00,0xC2,512,0x00,0x02, IDCriptografado);
	cout << *enviarPacote << endl;

	// Manda o ID criptografado para o servidor e o servidor retorna a chave simetrica S criptografada
	receberPacote = Socket.ReceberPacote(address, enviarPacote);

	// Descriptografa a a chave Simetrica e armazena na variável "chaveSimetrica"
	/* chaveSimetrica = Cript.DescriptografiaRSA(receberPacote); */

// PROTOCOLO DE AUTENTICAÇÃO ---------------------------------------------------------------------------------------------------------------

	// Criar um pacote com o ID criptografado e mandar para o protocolo de autenticação (tag 0xA0) e ele retorna o token A criptografado
	/* enviarPacote = Packet.CriarPacoteCheio(535,0x17,0x02,0x00,0x00,0xA0,512,0x00,0x02, IDCriptografado);
	   receberPacote = Socket.ReceberPacote(address, enviarPacote); */

	// Descriptografa o token A e armazena na variável "tokenA"
	/* tokenA = Cript.DescriptografiaRSA(receberPacote); */

	// Enviar um pacote vazio REQUEST_CHALLENGE para iniciar a autenticação e o servidor irá retornar um array M aleatorio criptografado
	/* enviarPacote = Packet.CriarPacoteVazio(0xA2);
	   receberPacote = Socket.ReceberPacote(address, enviarPacote); */

	// Descriptografar o array M com a chave simetrica S e o token A e receber o array M descriptografado
	/* dadosDescriptografados = Cript.DescriptografiaAES(receberPacote, tokenA, chaveSimetrica); */
	
	// Enviar o pacote array M descriptografado para o servidor comparar e ver se está autenticado e ele retorna o token T criptografado.
	/* enviarPacote = Packet.CriarPacoteCheio(tamanhoDoPacote,0x??,0x??,0x??,0x??,0xA5,tamanhoDoConteudo,0x??,0x??, dadosDescriptografados);
	   receberPacote = Socket.ReceberPacote(address, enviarPacote);
	   tokenT = Cript.DescriptografiaAES(receberPacote, tokenA, chaveSimetrica); */

	// tokenA pode ser descartado já que o só vamos usar o tokenT e a chave simetrica S
	/* array::destroy(tokenA); */

// PROTOCOLO DE REQUISIÇÃO -----------------------------------------------------------------------------------------------------------------
	
	// Criptografar o ID do objeto (que objeto é esse?) com a chave S e o token T
	/* enviarPacote = CriptografiaAES(conteudo, tokenT, chaveSimetrica); */

	// O servidor irá verificar se o ID bate com o ID do objeto que eles tem, se bater eles retornam o OBJETO criptografado
	/* receberPacote = Socket.ReceberPacote(address, enviarPacote); */

	// E por ultimo descriptografa o objeto recebido com a chave S e o tokenT e manda no moodle
	/* objeto = Cript.DescriptografiaAES(receberPacote, tokenT, chaveSimetrica);*/


// Destruir Pacotes e fechar Servidor ------------------------------------------------------------------------------------------------------

	//network::close(address);
	//array::destroy(enviarPacote);
	//array::destroy(IDCriptografado);
	//array::destroy(IDCliente);
	//array::destroy(chaveSimetrica);
	//array::destroy(tokenA);
	//array::destroy(tokenT);
	//array::destroy(dadosDescriptografados);
	//array::destroy(objeto);
	//array::destroy(id);
	//array::destroy(conteudo);

	return 0;
}
