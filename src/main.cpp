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
	array::array *pacoteCriado;
	array::array *pacoteRecebido;
	array::array *IDCriptografado;
	//array::array *dadosDescriptografados;
	//array::array *chaveSimetrica;
	//array::array *tokenA;
	//array::array *tokenT;
	//array::array *objeto;
	byte ID[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	byte* id = ID;
	array::array* conteudo = array::create(sizeof(ID), id);
	byte OBJ[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	byte* obj = OBJ;
	array::array* object = array::create(sizeof(OBJ), obj);

	//Construtores
	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);

	//Conectando ao servidor
	address = Socket.conectar();

// PROTOCOLO DE REGISTRO -------------------------------------------------------------------------------------------------------------------

	// Criptografa o ID com a chave publica do servidor
	IDCriptografado = Cript.CriptografiaRSA(conteudo);
	int tamanhoDoID = IDCriptografado->length;
	int tamanhoDoConteudo = tamanhoDoID+23;

	// Receber o pacote e guarda na variável "pacoteCriado"
	pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoConteudo,0x17,0x02,0x00,0x00,0xC2,tamanhoDoID,0x00,0x02, IDCriptografado);
	cout << *pacoteCriado << endl;

	// Manda o ID criptografado para o servidor e o servidor retorna a chave simetrica S criptografada
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);

	// Descriptografa a a chave Simetrica e armazena na variável "chaveSimetrica"
	/* chaveSimetrica = Cript.DescriptografiaRSA(pacoteRecebido); */

// PROTOCOLO DE AUTENTICAÇÃO ---------------------------------------------------------------------------------------------------------------

	// Criar um pacote com o ID criptografado e mandar para o protocolo de autenticação (tag 0xA0) e ele retorna o token A criptografado
	/* pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoConteudo,0x17,0x02,0x00,0x00,0xA0,tamanhoDoID,0x00,0x02, IDCriptografado);
	   pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado); */

	// Descriptografa o token A e armazena na variável "tokenA"
	/* tokenA = Cript.DescriptografiaRSA(pacoteRecebido); */

	// Enviar um pacote vazio REQUEST_CHALLENGE para iniciar a autenticação e o servidor irá retornar um array M aleatorio criptografado
	/* pacoteCriado = Packet.CriarPacoteVazio(0xA2);
	   pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado); */

	// Descriptografar o array M com a chave simetrica S e o token A e receber o array M descriptografado
	/* dadosDescriptografados = Cript.DescriptografiaAES(pacoteRecebido, tokenA, chaveSimetrica); 
	   cout << *dadosDescriptografados << endl;
	   int tamanhoDoArrayM = sizeof(dadosDescriptografados);
	   int tamanhoDoPacoteM = tamanhoDoArrayM+23; */
	
	// Enviar o pacote array M descriptografado para o servidor comparar e ver se está autenticado e ele retorna o token T criptografado.
	/* pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoPacoteM,0x??,0x??,0x??,0x??,0xA5,tamanhoDoArrayM,0x??,0x??, dadosDescriptografados);
	   pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);
	   tokenT = Cript.DescriptografiaAES(pacoteRecebido, tokenA, chaveSimetrica); */

	// tokenA pode ser descartado já que o só vamos usar o tokenT e a chave simetrica S
	/* array::destroy(tokenA); */

// PROTOCOLO DE REQUISIÇÃO -----------------------------------------------------------------------------------------------------------------
	
	// Criptografar o ID do objeto com a chave S e o token T
	/* pacoteCriado = CriptografiaAES(object, tokenT, chaveSimetrica);  */

	// O servidor irá verificar se o ID bate com o ID do objeto que eles tem, se bater eles retornam o OBJETO criptografado
	/* pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado); */

	// E por ultimo descriptografa o objeto recebido com a chave S e o tokenT e manda no moodle
	/* objeto = Cript.DescriptografiaAES(pacoteRecebido, tokenT, chaveSimetrica);*/


// Destruir Pacotes e fechar Servidor ------------------------------------------------------------------------------------------------------

	//network::close(address);
	//array::destroy(pacoteCriado);
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
