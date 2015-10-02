#include "array.hpp"
#include "crypto.hpp"
#include "criptografia.hpp"
#include <iostream>
#include <string>

using namespace std;

criptografia::criptografia() {
	chavePublica = "/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/server_pk.pem";
	chavePrivada = "/home/victor/Desktop/UnB/OO/CriptografiaEP1/doc/private.pem";
}

string criptografia::getChavePublica() {
	return chavePublica;
}

string criptografia::getChavePrivada() {
	return chavePrivada;
}

array::array *criptografia::criptografiaRSA(array::array *dados) {

	RSA *chave_publica;
	array::array *dadosCriptografado;
	string chavePublica = getChavePublica();

	chave_publica = crypto::rsa_read_public_key_from_PEM(chavePublica);

	dadosCriptografado = crypto::rsa_encrypt(dados, chave_publica);

	return dadosCriptografado;
}

array::array *criptografia::descriptografiaRSA(array::array *dados) {

	RSA *chave_privada;
	array::array *dadosDescriptografado;
	string chavePrivada = getChavePrivada();

	chave_privada = crypto::rsa_read_private_key_from_PEM(chavePrivada);

	dadosDescriptografado = crypto::rsa_decrypt(dados, chave_privada);

	return dadosDescriptografado;
}
