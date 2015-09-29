#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include <iostream>
#include <string>
#include "array.hpp"
#include "crypto.hpp"

using namespace std;

class criptografia {
private:
	string chavePublica;
	string chavePrivada;

public:
	
	criptografia();
	array::array *CriptografiaRSA(array::array *dados);
	array::array *DescriptografiaRSA(array::array *dados);
	array::array *CriptografiaAES(array::array *dados, array::array *token, array::array *chaveSimetrica);
	array::array *DescriptografiaAES(array::array *dadosCifrados, array::array *token, array::array *chaveSimetrica);
	string getChavePublica();
	string getChavePrivada();

};
#endif
