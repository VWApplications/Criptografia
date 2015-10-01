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

array::array* criptografia::CriptografiaRSA(array::array *dados) {

	string chavePublica = getChavePublica();

	RSA *chave_publica = crypto::rsa_read_public_key_from_PEM(chavePublica);

	cout << "ID: " << *dados << endl;

	array::array *DadosCriptografados = crypto::rsa_encrypt(dados, chave_publica);

	cout << "ID Criptografado: "<< *DadosCriptografados << endl;

	//array::destroy(dados);

	return DadosCriptografados;

}

array::array* criptografia::DescriptografiaRSA(array::array *dados) {
	
	string chavePrivada = getChavePrivada();

	RSA *chave_privada = crypto::rsa_read_private_key_from_PEM(chavePrivada);

	array::array *DadosDescriptografados = crypto::rsa_decrypt(dados, chave_privada);

	//array::destroy(dados);

	return DadosDescriptografados;

}

array::array* criptografia::CriptografiaAES(array::array *dados, array::array *token, array::array *chaveSimetrica) {

	array::array *dadosCifrados = crypto::aes_encrypt(dados, token, chaveSimetrica);

	//array::destroy(dados);
	//array::destroy(chaveSimetrica);
	//array::destroy(token);

	return dadosCifrados;
}

array::array* criptografia::DescriptografiaAES(array::array *dadosCifrados, array::array *token, array::array *chaveSimetrica) {

	array::array *dadosDecifrados = crypto::aes_decrypt(dadosCifrados, token, chaveSimetrica);

	//array::destroy(dadosCifrados);
	//array::destroy(chaveSimetrica);
	//array::destroy(token);

	return dadosDecifrados;
}
