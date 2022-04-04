#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------

struct Cipher::CipherCheshire {
    string cipher_alpha;
    int cipher_offset;
};

RCipher :: RCipher() {
	smile = new CipherCheshire();
	smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
	smile->cipher_offset = 13;
	rotate_string(smile->cipher_alpha, 13); //just send in a rotation of 13 to ccipher.cc and it should be all good to go.
}

RCipher::~RCipher() {
	free(smile);
	delete(smile);
}












