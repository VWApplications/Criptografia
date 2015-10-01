#ifndef CLIENTE_H
#define CLIENTE_H

#include "array.hpp"

using namespace std;

class cliente {
protected:
	byte *ID;
	byte *OBJ;
	array::array *pacoteCriado;
	array::array *pacoteRecebido;
	array::array *IDCriptografado;

public:
	
	cliente();
	cliente(byte ID[], byte OBJ[]);

	virtual array::array *CriarConteudo() = 0;
	void setID(byte ID[]);
	byte *getID();
	void setOBJ(byte OBJ[]);
	byte *getOBJ();
	


};
#endif
