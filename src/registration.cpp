#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "registration.hpp"
#include "array.hpp"
#include <iostream>

using namespace std;

registration::registration() {
	byte id[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	byte *conteudo = id;
	ID = array::create(sizeof(id), conteudo);
}

registration::registration(array::array *ID) {
	setID(ID);
}

array::array *registration::ProtocoloDeRegistro(array::array *conteudo, int address) {

	criptografia Cript;
	packet Packet;
	socket Socket("45.55.185.4", 3000);
	array::array *chaveSimetrica;

	// Criptografa o ID com a chave publica do servidor
	IDCriptografado = Cript.CriptografiaRSA(conteudo);
	int tamanhoDoID = IDCriptografado->length;
	int tamanhoDoConteudo = tamanhoDoID+23;

	// Receber o pacote e guarda na variável "pacoteCriado"
	pacoteCriado = Packet.CriarPacoteCheio(tamanhoDoConteudo,0x17,0x02,0x00,0x00,0xC2,tamanhoDoID,0x00,0x02, IDCriptografado);
	cout << "Pacote com os 4 bytes do tamanho do pacote, tag, 2 bytes com o tamanho do conteudo, 512 bytes do ID criptografado e os 20 bytes de Hash: "<< *pacoteCriado << endl;

	// Manda o ID criptografado para o servidor e o servidor retorna a chave simetrica S criptografada
	pacoteRecebido = Socket.ReceberPacote(address, pacoteCriado);
	cout << "Não consigo achar o motivo do pacote acima (f2) = pacote desconhecido" << endl;

	// Descriptografa a a chave Simetrica e armazena na variável "chaveSimetrica"
	//chaveSimetrica = Cript.DescriptografiaRSA(pacoteRecebido);

	//array::destroy(pacoteCriado);
	//array::destroy(pacoteRecebido);
	//array::destroy(conteudo);
	//array::destroy(IDCriptografado);

	return chaveSimetrica;
}
