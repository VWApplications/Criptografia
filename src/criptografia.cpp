#include "array.hpp"
#include "packet.hpp"
#include "crypto.hpp"
#include "criptografia.hpp"
#include <iostream>

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

<<<<<<< HEAD
	string ChavePublica = getChavePublica();

	RSA *LerChavePublica = crypto::rsa_read_public_key_from_PEM(ChavePublica);

	array::array *DadosCriptografados = crypto::rsa_encrypt(dados, LerChavePublica);
=======
	array::array *DadosCriptografados;
	RSA *LerChavePublica;
	string ChavePublica = getChavePublica();

	LerChavePublica = crypto::rsa_read_public_key_from_PEM(ChavePublica);

	DadosCriptografados = crypto::rsa_encrypt(dados, LerChavePublica);
>>>>>>> dad31d2c1ee76721063e9756f79c41d873cc4d7f

	cout << *DadosCriptografados << endl;

	array::destroy(dados);

	return DadosCriptografados;

}

array::array* criptografia::DescriptografiaRSA(array::array *dados) {
	
<<<<<<< HEAD
	string ChavePrivada = getChavePrivada();

	RSA *LerChavePrivada = crypto::rsa_read_private_key_from_PEM(ChavePrivada);

	array::array *DadosDescriptografados = crypto::rsa_decrypt(dados, LerChavePrivada);
=======
	array::array *DadosDescriptografados;
	RSA *LerChavePrivada;
	string ChavePrivada = getChavePrivada();

	LerChavePrivada = crypto::rsa_read_private_key_from_PEM(ChavePrivada);

	DadosDescriptografados = crypto::rsa_decrypt(dados, LerChavePrivada);
>>>>>>> dad31d2c1ee76721063e9756f79c41d873cc4d7f

	array::destroy(dados);

	return DadosDescriptografados;

}

array::array* criptografia::CriptografiaAES(array::array *dados, array::array *token, array::array *chaveSimetrica) {

	array::array *dadosCifrados = crypto::aes_encrypt(dados, token, chaveSimetrica);

	array::destroy(dados);
	array::destroy(chaveSimetrica);
	array::destroy(token);

	return dadosCifrados;
}

array::array* criptografia::DescriptografiaAES(array::array *dadosCifrados, array::array *token, array::array *chaveSimetrica) {

	array::array *dadosDecifrados = crypto::aes_decrypt(dadosCifrados, token, chaveSimetrica);

	array::destroy(dadosCifrados);
	array::destroy(chaveSimetrica);
	array::destroy(token);

	return dadosDecifrados;
}
