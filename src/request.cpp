#include "crypto.hpp"
#include "packet.hpp"
#include "request.hpp"
#include "array.hpp"
#include <iostream>
#include <iomanip>
#include <ostream>
#include <istream>
#include <unistd.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>

using namespace std;

request::request() {
	byte obj[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	byte *object = obj;
	OBJ = array::create(sizeof(obj), object);
}

request::request(array::array *conteudo, array::array *tokenT, array::array *chaveSimetrica, int address) {

	packet Packet;

	int tamanhoDoObjeto;
	array::array *REQUEST_OBJECT;
	array::array *OBJECT;
	array::array *IDcriptografado_objeto;
	array::array *objetoCriptografado;
	

	IDcriptografado_objeto = crypto::aes_encrypt(conteudo, tokenT, chaveSimetrica);

	REQUEST_OBJECT = Packet.criarPacoteCheio(0x27, 0, 0, 0, 0xB0, 0x10, 0, IDcriptografado_objeto);

	network::write(address, REQUEST_OBJECT);
	if((OBJECT = network::read(address, 23863)) == nullptr){
		cout << "Leitura nula" << endl;
	}else{
		cout << "Objeto de "<< OBJECT->length << " bytes recebido com sucesso!" << endl;
	}

	tamanhoDoObjeto = 23863-23;

	objetoCriptografado = array::create(tamanhoDoObjeto);
	memcpy(objetoCriptografado->data, OBJECT->data + 7, tamanhoDoObjeto);
	objetoDescriptografado = crypto::aes_decrypt(objetoCriptografado, tokenT, chaveSimetrica);

}

array::array *request::getObjeto() {
	return objetoDescriptografado;
}

void request::criarObjeto(array::array *objetoDescriptografado) {

	ofstream imagem;
	imagem.open ("/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/imagem.jpg", ios::binary);
	if( !imagem ){
		cout << "Erro ao criar o arquivo";
	}else{
		cout << "Criando o OBJECT\n" << endl;
		sleep(2);
		for (int i = 0; i < ((int)objetoDescriptografado->length); i++){
			imagem << objetoDescriptografado->data[i];
		}

	}
	imagem.close();

}
