#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include "array.hpp"
#include "crypto.hpp"
#include <iostream>
#include <string>

using namespace std;

class criptografia {
private:
	string chavePublica;
	string chavePrivada;

public:
	
	criptografia();
	array::array *criptografiaRSA(array::array *dados);
	array::array *descriptografiaRSA(array::array *dados);
	string getChavePublica();
	string getChavePrivada();

};
#endif
