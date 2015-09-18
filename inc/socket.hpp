#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <string>
#include "network.hpp"
#include "array.hpp"

class socket{
public:
	int conectar();
	int escrever();

};
#endif

/* int connect(const std::string& host, const int& port);
void close(int fd);
void write(int fd, const array::array* content);
array::array* read(int fd);
array::array* read(int fd, size_t len); */
