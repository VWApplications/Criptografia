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
	array::array *pacoteVazio = array::create(7);
		
		byte Tag = tag;
		
		pacoteVazio->data[0] = 0x03;
		pacoteVazio->data[1] = 0;
		pacoteVazio->data[2] = 0;
		pacoteVazio->data[3] = 0;
		pacoteVazio->data[4] = Tag;
		pacoteVazio->data[5] = 0;
		pacoteVazio->data[6] = 0;

		return pacoteVazio;
}

array::array* packet::CriarPacoteCheio(int tamanhoDoPacote, byte TP1, byte TP2, byte TP3, byte TP4, byte tag, int tamanhoDoConteudo, byte TC1, byte TC2, array::array* conteudo) {

	//Criar o pacote------------------------------------------------------------	
	array::array *pacote = array::create(tamanhoDoPacote);

	//Criar o tag e o length do pacote-------------------------------------------
		pacote->data[0] = tag; //tag
		pacote->data[1] = TC1; //length menos significativo
		pacote->data[2] = TC2; //length mais significativo
	

	//Vai inserir "tamanhoDoConteudo" com o conteudo a partir da 4° posição do pacote
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
		array::array *pacoteCheio = array::create(pacoteTodo);
		
		// 4 bytes que iremos mandar primeiro com o tamanho do pacote
		pacoteCheio->data[0] = TP1;
		pacoteCheio->data[1] = TP2;
		pacoteCheio->data[2] = TP3;
		pacoteCheio->data[3] = TP4;

		//Vamos pegar o pacote de ... bytes e jogar na 5° posição do enviarPacote
		memcpy(pacoteCheio->data +4, pacote->data, tamanhoDoPacote);
	//---------------------------------------------------------------------------

	array::destroy(pacote);
	array::destroy(hash);
	array::destroy(conteudo);

	return pacoteCheio;
}



