#include "array.hpp"
#include "packet.hpp"
#include "crypto.hpp"
#include <iostream>

using namespace std;

packet::packet() {
	setTag(0xC0);
}

void packet::setTag(byte tag) {
	this->tag = tag;
}

byte packet::getTag() {
	return tag;
}


array::array* packet::CriarPacoteVazio(byte tag) {
	array::array *enviarPacoteVazio = array::create(7);
		
		byte Tag = tag;
		
		enviarPacoteVazio->data[0] = 0x03;
		enviarPacoteVazio->data[1] = 0;
		enviarPacoteVazio->data[2] = 0;
		enviarPacoteVazio->data[3] = 0;
		enviarPacoteVazio->data[4] = Tag;
		enviarPacoteVazio->data[5] = 0;
		enviarPacoteVazio->data[6] = 0;

		return enviarPacoteVazio;
}

array::array* packet::CriarPacoteCheio(byte tag, int tamanhoDoPacote, byte TP1, byte TP2, byte TP3, byte TP4, int tamanhoDoConteudo, byte TC1, byte TC2, array::array* conteudo) {

	//Criar o pacote------------------------------------------------------------
		array::array *pacote = array::create(tamanhoDoPacote);

	//Criar o tag e o length do pacote-------------------------------------------
		pacote->data[0] = tag; //tag
		pacote->data[1] = TC1; //length menos significativo
		pacote->data[2] = TC2; //length mais significativo
	
	//Vai inserir "tamanhoDoConteudo" com o conteudo a partir da 3° posição do pacote
		memcpy(pacote->data +3, conteudo->data, tamanhoDoConteudo);
	//---------------------------------------------------------------------------

	//Criando o hash-------------------------------------------------------------
		array::array *hash = crypto::sha1(conteudo);

		//Vai inserir o pacote hash de 20 bytes a partir da 7° posição do pacote
		int memoria = tamanhoDoConteudo+3;
		memcpy(pacote->data +memoria, hash->data, 20);
	//---------------------------------------------------------------------------

	//Criando o pacote todo------------------------------------------------------
		int pacoteTodo = tamanhoDoPacote+4;
		array::array *enviarPacoteCheio = array::create(pacoteTodo);
		
		// 4 bytes que iremos mandar primeiro com o tamanho do pacote
		enviarPacoteCheio->data[0] = TP1;
		enviarPacoteCheio->data[1] = TP2;
		enviarPacoteCheio->data[2] = TP3;
		enviarPacoteCheio->data[3] = TP4;

		//Vamos pegar o pacote de 27 bytes e jogar na 4° posição do enviarPacote
		memcpy(enviarPacoteCheio->data +4, pacote->data, tamanhoDoPacote);
	//---------------------------------------------------------------------------

	array::destroy(pacote);
	array::destroy(hash);
	array::destroy(conteudo);

	return enviarPacoteCheio;
}



