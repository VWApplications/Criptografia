#include "array.hpp"
#include "packet.hpp"
#include "crypto.hpp"
#include <iostream>

using namespace std;

array::array* packet::CriarPacoteVazio() {
	array::array *enviarPacoteVazio = array::create(7);
		enviarPacoteVazio->data[0] = 0x03;
		enviarPacoteVazio->data[1] = 0;
		enviarPacoteVazio->data[2] = 0;
		enviarPacoteVazio->data[3] = 0;
		enviarPacoteVazio->data[4] = 0xC0;
		enviarPacoteVazio->data[5] = 0;
		enviarPacoteVazio->data[6] = 0;

		return enviarPacoteVazio;
}

array::array* packet::CriarPacoteCheio() {
	
	//Criar o pacote------------------------------------------------------------
		array::array *pacote = array::create(31);
	//Criar o value do pacote---------------------------------------------------
		array::array *ValueDoPacote = array::create(8);

		//conteudo do pacote
		byte valor[] = {0xc6, 0x67, 0x0e, 0x84, 0xc0, 0xca, 0xbc, 0x82};

	//Vai inserir o pacote valor de 4 bytes no pacote ValueDoPacote
		memcpy(ValueDoPacote->data, valor, 8);
	//---------------------------------------------------------------------------

	//Criar o tag e o length do pacote-------------------------------------------
		pacote->data[0] = 0xC2; //tag
		pacote->data[1] = 8; //length menos significativo
		pacote->data[2] = 0; //length mais significativo
	
	//Vai inserir o pacote valor de 4 bytes na 3° posição do pacote
		memcpy(pacote->data +3, valor, 8);
	//---------------------------------------------------------------------------

	//Criando o hash-------------------------------------------------------------
		array::array *hash = crypto::sha1(ValueDoPacote);

		//Vai inserir o pacote hash de 20 bytes na 7° posição do pacote
		memcpy(pacote->data +11, hash->data, 20);
	//---------------------------------------------------------------------------

	//Criando o pacote todo------------------------------------------------------
		array::array *enviarPacoteCheio = array::create(35);
		
		// 4 bytes que iremos mandar primeiro com o tamanho do pacote
		enviarPacoteCheio->data[0] = 31;
		enviarPacoteCheio->data[1] = 0;
		enviarPacoteCheio->data[2] = 0;
		enviarPacoteCheio->data[3] = 0;

		//Vamos pegar o pacote de 27 bytes e jogar na 4° posição do enviarPacote
		memcpy(enviarPacoteCheio->data +4, pacote->data, 31);
	//---------------------------------------------------------------------------

	array::destroy(pacote);
	array::destroy(hash);
	array::destroy(ValueDoPacote);

	return enviarPacoteCheio;
}


