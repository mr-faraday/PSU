#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

const char* publicKeyName = "rsa.public";
const char* privateKeyName = "rsa.private";

using namespace std;
void GenKeys(char secret[]);
void Enc();
void Dec(char secret[]);
void GenKeysMenu();
void EncryptMenu();
void DecryptMenu();

int main() {
	setlocale(LC_ALL, "Russian");

	char key;
	int status = 1;
	while (status) {
		system("cls");
		cout << "-------------- Шифрование RSA --------------" << endl << endl;
		cout << "  1. Получение ключей" << endl;
		cout << "  2. Зашифровать содержимое файла" << endl;
		cout << "  3. Дешифровать содержимое файла" << endl << endl;
		cout << "Ваш выбор: ";
		cin >> key;

		switch (key) {
			case '1':
				GenKeysMenu();
				break;
			case '2':
				EncryptMenu();
				break;
			case '3':
				DecryptMenu();
				break;
			default:
				break;
		}
	}

	return 0;
}

void GenKeys(char secret[]) {
	/* указатель на структуру для хранения ключей */
	RSA* rsa = NULL;
	unsigned long bits = 1024; /* длина ключа в битах */
	FILE* privKey_file = NULL, * pubKey_file = NULL;
	/* контекст алгоритма шифрования */
	const EVP_CIPHER* cipher = NULL;
	/*Создаем файлы ключей*/
	privKey_file = fopen("\private.key", "wb");
	pubKey_file = fopen("\public.key", "wb");
	/* Генерируем ключи */
	rsa = RSA_generate_key(bits, RSA_F4, NULL, NULL);
	/* Формируем контекст алгоритма шифрования */
	cipher = EVP_get_cipherbyname("bf-ofb");
	/* Получаем из структуры rsa открытый и секретный ключи и сохраняем в файлах.
	* Секретный ключ шифруем с помощью парольной фразы
	*/
	PEM_write_RSAPrivateKey(privKey_file, rsa, cipher, NULL, 0, NULL, secret);
	PEM_write_RSAPublicKey(pubKey_file, rsa);
	/* Освобождаем память, выделенную под структуру rsa */
	RSA_free(rsa);
	fclose(privKey_file);
	fclose(pubKey_file);
	cout << "Ключи сгенерированы и помещены в папку с исполняемым файлом" << endl;
}

void Encrypt() {
	/* структура для хранения открытого ключа */
	RSA* pubKey = NULL;
	FILE* pubKey_file = NULL;
	unsigned char* ctext, * ptext;
	int inlen, outlen;
	/* Считываем открытый ключ */
	pubKey_file = fopen("\public.key", "rb");
	pubKey = PEM_read_RSAPublicKey(pubKey_file, NULL, NULL, NULL);
	fclose(pubKey_file);

	/* Определяем длину ключа */
	int key_size = RSA_size(pubKey);
	ctext = (unsigned char*)malloc(key_size);
	ptext = (unsigned char*)malloc(key_size);
	OpenSSL_add_all_algorithms();

	int out = _open("rsa.file", O_CREAT | O_TRUNC | O_RDWR, 0600);
	int in = _open("in.txt", O_RDWR);
	/* Шифруем содержимое входного файла */
	while (1) {
		inlen = _read(in, ptext, key_size - 11);
		if (inlen <= 0) break;
		outlen = RSA_public_encrypt(inlen, ptext, ctext, pubKey, RSA_PKCS1_PADDING);
		if (outlen != RSA_size(pubKey)) exit(-1);
		_write(out, ctext, outlen);
	}
	cout << "Содержимое файла in.txt было зашифровано и помещено в файл rsa.file" << endl;
}

void Decrypt(char secret[]) {
	RSA* privKey = NULL;
	FILE* privKey_file;
	unsigned char* ptext, * ctext;
	int inlen, outlen;

	/* Открываем ключевой файл и считываем секретный ключ */
	OpenSSL_add_all_algorithms();
	privKey_file = fopen("private.key", "rb");
	privKey = PEM_read_RSAPrivateKey(privKey_file, NULL, NULL, secret);

	/* Определяем размер ключа */
	int key_size = RSA_size(privKey);
	ptext = (unsigned char*)malloc(key_size);
	ctext = (unsigned char*)malloc(key_size);

	int out = _open("out.txt", O_CREAT | O_TRUNC | O_RDWR, 0600);
	int in = _open("rsa.file", O_RDWR);

	/* Дешифруем файл */
	while (1) {
		inlen = _read(in, ctext, key_size);
		if (inlen <= 0) break;
		outlen = RSA_private_decrypt(inlen, ctext, ptext, privKey, RSA_PKCS1_PADDING);
		if (outlen < 0) exit(0);
		_write(out, ptext, outlen);
	}
	cout << "Содержимое файла rsa.file было дешифровано и помещено в файл out.txt" << endl;

}
void GenKeysMenu() {
	char secret[] = "";
	system("cls");
	cout << "-------------- Шифрование RSA --------------" << endl << endl;
	cout << "Введите парольную фразу для закрытого ключа: ";
	cin >> secret;
	GenKeys(secret);
	cout << "Нажмите любую кнопку для возврата в меню...";
	_getch();
}
void EncryptMenu() {
	system("cls");
	cout << "-------------- Шифрование RSA --------------" << endl << endl;
	Encrypt();
	cout << "Нажмите любую кнопку для возврата в меню...";
	_getch();
}
void DecryptMenu() {
	char secret[] = "";
	system("cls");
	cout << "-------------- Шифрование RSA --------------" << endl << endl;
	cout << "Введите парольную фразу для закрытого ключа: ";
	cin >> secret;
	Decrypt(secret);
	cout << "Нажмите любую кнопку для возврата в меню...";
	_getch();
}