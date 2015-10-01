#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <iostream>
#include <string>
#include "criptografia.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include "cliente.hpp"

using namespace std;

class authentication: public cliente {
private:
	array::array *tokenA;
	array::array *dadosDescriptografados;

public:
	
	authentication();
	authentication(byte *ID);
	array::array *ProtocoloDeAutenticacao(array::array *conteudo, array::array *chaveSimetrica, int address);
	array::array *CriarConteudo();


};
#endif
