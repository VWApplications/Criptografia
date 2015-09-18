#include "array.hpp"
#include "packet.hpp"
#include <iostream>

using namespace std;

array::array packet::Criarpacote(){
	array::array *enviarPacoteVazio = array::create(7);
		enviarPacoteVazio->data[0] = 0x03;
		enviarPacoteVazio->data[1] = 0;
		enviarPacoteVazio->data[2] = 0;
		enviarPacoteVazio->data[3] = 0;
		enviarPacoteVazio->data[4] = 0xC0;
		enviarPacoteVazio->data[5] = 0;
		enviarPacoteVazio->data[6] = 0;

		return *enviarPacoteVazio;
}


