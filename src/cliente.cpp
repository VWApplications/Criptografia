#include "cliente.hpp"
#include "array.hpp"
#include "packet.hpp"
#include "socket.hpp"
#include <iostream>


using namespace std;

cliente::cliente() {
	byte id[] = {0xC6, 0x67, 0x0E, 0x84, 0xC0, 0xCA, 0xBC, 0x82};
	ID = id;
	byte obj[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	OBJ = obj;
}

cliente::cliente(byte *ID, byte *OBJ) {
	setID(ID);
	setOBJ(OBJ);
}

void cliente::setID(byte ID[]) {
	byte *id = ID;
	this->ID = id;
}

byte *cliente::getID() {
	return ID;
}

void cliente::setOBJ(byte OBJ[]) {
	byte *obj = OBJ;
	this->OBJ = obj;
}

byte *cliente::getOBJ() {
	return OBJ;
}

