#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <openssl/evp.h>
#include <openssl/aes.h>

#define BUFSIZE 1024

int encrypt();
int decrypt();
void clearBuffer();

std::ifstream fIn;
std::ofstream fOut;

unsigned char key[24];
unsigned char iv[] = "vector-vector-ve";
unsigned char inbuf[BUFSIZE], outbuf[BUFSIZE];

int inlen, outlen;
EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
const EVP_CIPHER *cipher;

int main(int argc, char *argv[]) {
    std::cout << argv[1] << std::endl;
    std::cout << argv[2] << std::endl;
    std::cout << argv[3] << std::endl;
    std::cout << argv[4] << std::endl;

    // Открытие ключа
    std::ifstream fKey(argv[2]);
    std::string keyStr((std::istreambuf_iterator<char>(fKey)), std::istreambuf_iterator<char>());
    strcpy((char *) key, keyStr.c_str());
    fKey.close();

    fIn = std::ifstream(argv[1], std::ifstream::binary);
    fOut = std::ofstream(argv[4], std::ofstream::binary);

    EVP_CIPHER_CTX_init(ctx);
    cipher = EVP_aes_192_cfb();

    std::cout << "Cipher IV length: " << EVP_CIPHER_iv_length(cipher) << std::endl;

    if (argv[3][0] == 'e') encrypt();
    if (argv[3][0] == 'd') decrypt();

    EVP_CIPHER_CTX_free(ctx);
    fIn.close();
    fOut.close();

    return 0;
}

int encrypt() {
    EVP_EncryptInit(ctx, cipher, key, iv);

    while (!fIn.eof()) {
        clearBuffer();

        fIn.read((char *) inbuf, BUFSIZE);
        inlen = strlen((char *) inbuf);

        if (inlen <= 0) break;

        EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fOut << outbuf;
    }

    clearBuffer();

    EVP_EncryptFinal(ctx, outbuf, &outlen);
    fOut << outbuf;
    EVP_CIPHER_CTX_cleanup(ctx);

    return 0;
}

int decrypt() {
    EVP_DecryptInit(ctx, cipher, key, iv);

    while (!fIn.eof()) {
        clearBuffer();

        fIn.read((char *) inbuf, BUFSIZE);
        inlen = strlen((char *) inbuf);

        if (inlen <= 0) break;

        EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen);
        fOut << outbuf;
    }

    clearBuffer();

    EVP_DecryptFinal(ctx, outbuf, &outlen);
    fOut << outbuf;

    return 0;
}

void clearBuffer() {
    memset(inbuf, 0, BUFSIZE);
    memset(outbuf, 0, BUFSIZE);
}
