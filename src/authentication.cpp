#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "authentication.hpp"
#include "array.hpp"
#include <iostream>

using namespace std;

authentication::authentication() {
	byte id[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	ID = id;
}

authentication::authentication(byte *ID) {
	setID(ID);
}

array::array *authentication::CriarConteudo() {

	byte* id = getID();
	array::array* conteudo = array::create(sizeof(ID), id);

	return conteudo;
}

array::array *authentication::ProtocoloDeAutenticacao(array::array *conteudo, array::array *chaveSimetrica, int address) {

	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);
	array::array *tokenT;

	// Criptografa o ID com a chave publica do servidor
	IDCriptografado = Cript.CriptografiaRSA(conteudo);
	int tamanhoDoID = IDCriptografado->length;
	int tamanhoDoConteudo = tamanhoDoID+23;

	// Criar um pacote com o ID criptografado e mandar para o protocolo de autenticação (tag 0xA0) e ele retorna o token A criptografado
	pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoConteudo,0x17,0x02,0x00,0x00,0xA0,tamanhoDoID,0x00,0x02, IDCriptografado);
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);

	// Descriptografa o token A e armazena na variável "tokenA"
	tokenA = Cript.DescriptografiaRSA(pacoteRecebido);

	// Enviar um pacote vazio REQUEST_CHALLENGE para iniciar a autenticação e o servidor irá retornar um array M aleatorio criptografado
	pacoteCriado = Packet.CriarPacoteVazio(0xA2);
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);

	// Descriptografar o array M com a chave simetrica S e o token A e receber o array M descriptografado
	dadosDescriptografados = Cript.DescriptografiaAES(pacoteRecebido, tokenA, chaveSimetrica); 
	int tamanhoDoArrayM = dadosDescriptografados->length;
	int tamanhoDoPacoteM = tamanhoDoArrayM+23;
	
	// Enviar o pacote array M descriptografado para o servidor comparar e ver se está autenticado e ele retorna o token T criptografado.
	// Como ainda não consegui descriptografar o array M então coloquei 0x00 em tudo para poder copilar
	pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoPacoteM,0x00,0x00,0x00,0x00,0xA5,tamanhoDoArrayM,0x00,0x00, dadosDescriptografados);
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);
	tokenT = Cript.DescriptografiaAES(pacoteRecebido, tokenA, chaveSimetrica);

	// tokenA pode ser descartado já que o só vamos usar o tokenT e a chave simetrica S
	//array::destroy(tokenA);

	return tokenT;
}
