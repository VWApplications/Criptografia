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
		array::array *pacote = array::create(27);
	//Criar o value do pacote---------------------------------------------------
		array::array *ValueDoPacote = array::create(4);

		//conteudo do pacote
		byte valor[] = {0xAB, 0x23, 0x12, 0x43};

	//Vai inserir o pacote valor de 4 bytes no pacote ValueDoPacote
		memcpy(ValueDoPacote->data, valor, 4);
	//---------------------------------------------------------------------------

	//Criar o tag e o length do pacote-------------------------------------------
		pacote->data[0] = 0xC0; //tag
		pacote->data[1] = 4; //length menos significativo
		pacote->data[2] = 0; //length mais significativo
	
	//Vai inserir o pacote valor de 4 bytes na 3° posição do pacote
		memcpy(pacote->data +3, valor, 4);
	//---------------------------------------------------------------------------

	//Criando o hash-------------------------------------------------------------
		array::array *hash = crypto::sha1(ValueDoPacote);

		//Vai inserir o pacote hash de 20 bytes na 7° posição do pacote
		memcpy(pacote->data +7, hash->data, 20);
	//---------------------------------------------------------------------------

	//Criando o pacote todo------------------------------------------------------
		array::array *enviarPacoteCheio = array::create(31);
		
		// 4 bytes que iremos mandar primeiro com o tamanho do pacote
		enviarPacoteCheio->data[0] = 27;
		enviarPacoteCheio->data[1] = 0;
		enviarPacoteCheio->data[2] = 0;
		enviarPacoteCheio->data[3] = 0;

		//Vamos pegar o pacote de 27 bytes e jogar na 4° posição do enviarPacote
		memcpy(enviarPacoteCheio->data +4, pacote->data, 27);
	//---------------------------------------------------------------------------

	array::destroy(pacote);
	array::destroy(hash);
	array::destroy(ValueDoPacote);

	return enviarPacoteCheio;
}


