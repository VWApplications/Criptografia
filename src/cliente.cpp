#include "cliente.hpp"
#include "array.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include <iostream>


using namespace std;

cliente::cliente() {

	byte id[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	byte *conteudo = id;
	ID = array::create(sizeof(id), conteudo);

	byte obj[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	byte *object = obj;
	OBJ = array::create(sizeof(obj), object);

}

cliente::cliente(array::array *ID, array::array *OBJ) {
	setID(ID);
	setOBJ(OBJ);
}

void cliente::setID(array::array *ID) {
	this->ID = ID;
}

array::array *cliente::getID() {
	return ID;
}

void cliente::setOBJ(array::array *OBJ) {
	this->OBJ = OBJ;
}

array::array *cliente::getOBJ() {
	return OBJ;
}
