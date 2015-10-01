#ifndef CLIENTE_H
#define CLIENTE_H

#include "array.hpp"

using namespace std;

class cliente {
protected:
	array::array *ID;
	array::array *OBJ;
	array::array *pacoteCriado;
	array::array *pacoteRecebido;
	array::array *IDCriptografado;

public:
	
	cliente();
	cliente(array::array *ID, array::array *OBJ);

	void setID(array::array *ID);
	array::array *getID();
	void setOBJ(array::array *OBJ);
	array::array *getOBJ();
	


};
#endif
