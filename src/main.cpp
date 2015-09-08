#include "crypto.hpp"
#include "array.hpp"
#include "network.hpp"

#include <iostream>
#include <iomanip>
#include <ostream>
#include <unistd.h>

using namespace std;

class Packet;

ostream& operator<<(ostream& os, const Packet& p);

class Packet {
public:
	
	Packet(const array::array* data) {
		byte* d = data->data;
		
		this->tag = d[0];
		this->length = d[0] & (d[1] << 8);
		
		if(this->length > 0) {
			this->value = array::create(this->length, d + 3);
			this->signature = array::create(20, d + this->length + 3);
		}
		//TODO verify signature
	}
	
	Packet(const byte tag, const array::array* value)  {
		this->tag = tag;
		this->set_value(value);
	}
	
	Packet(const byte tag) {
		this->tag = tag;
		this->value = nullptr;
		this->signature = nullptr;
	}
	
	~Packet() {
		if(this->value != nullptr) {
			array::destroy(this->value);
			array::destroy(this->signature);
		}
	}
	
	size_t total_size() {
		return 3 + (value != nullptr ? value->length : 0) + (signature != nullptr ? signature->length : 0);
	}
	
	void set_value(const array::array* value) {
	
		if(this->value != nullptr) {
			array::destroy(this->value);
			array::destroy(this->signature);
		}
		
		this->value = array::copy(value);
		if(value != nullptr) {
			this->signature = crypto::sha1(value);	
			this->length = this->value->length;
		}
		else {
			this->length = 0;		
		}
	}
	
	array::array* bytes() {
		array::array* raw;
		
		if(this->length == 0) {
			raw = array::create(3);
		}
		else {
			raw = array::create(this->total_size());
		}
		
		raw->data[0] = this->tag;
		raw->data[1] = this->length & 0xFF;
		raw->data[2] = (this->length >> 8) & 0xFF;
		
		if(this->length > 0) {
			memcpy(raw->data + 3, this->value, this->length);
			memcpy(raw->data + 3 + this->length, this->signature, 20);
		}
		
		return raw;
	}
	
	friend ostream& operator<<(ostream& os, const Packet& p);
private:

	byte tag;
	unsigned short length;
	array::array* value;
	array::array* signature;
};

std::ostream& operator<<(std::ostream& os, const Packet& packet) {
	os << "[tag: " << std::hex << (int) packet.tag << "; " <<
              "len: "  << std::dec << packet.length << ";";
	if(packet.length > 0) {
	      os << " value: {" << *(packet.value) << "}; " <<
	      "sign: {" << *(packet.signature) << "};";
	}
	os << "]";
	
	return os;
}

void sock_send(int sock, Packet* packet) {
	size_t size = packet->total_size();
	array::array* packet_bytes = packet->bytes();

	byte* tmp = new byte[4];
	array::array* header = array::wrap(4, tmp);
	tmp[0] = size & 0xFF;
	tmp[1] = (size >> 8) & 0xFF;
	tmp[2] = (size >> 16) & 0xFF;
	tmp[3] = (size >> 24) & 0xFF;
	
	network::write(sock, header);
	network::write(sock, packet_bytes);
	
	cout << "destroy 1" << endl;
	array::destroy(header);
	cout << "destroy 2" << endl;
	array::destroy(packet_bytes);
	cout << "destroy 3" << endl;
	delete[] tmp;
}

int main(int argc, char** argv) {
	cout << "Connecting...";
	int sock = network::connect("127.0.0.1", 3001);
	
	if(sock < 0) {
		cout << "failed :(" << endl;
		return 1;
	}
	cout << "ok." << endl;
	
	cout << "Sending packets." << endl;
	while(true) {
		cout << ".";
		Packet* packet = new Packet(0xFA, crypto::nonce(32));
		cout << "Packet: " << *packet << endl;
		sock_send(sock, packet);
		cout << "Free" << endl;
		delete packet;
		sleep(3);
	}
	
	return 0;	
}
