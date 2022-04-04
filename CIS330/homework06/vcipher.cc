#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"


// -------------------------------------------------------
// Running Key Cipher implementation
// ------------------------------------------------------
struct VCipher::CipherCheshire {
	string cipher_key;
	};
VCipher::VCipher() {
	smile = new CipherCheshire();
	smile->cipher_key = "";

}

VCipher::VCipher(string key) {
	smile = new CipherCheshire(); //memory error effected the finishing of this struct, I suspect that if the memory error didn't hit then this implementation would be correct more or less with some adjustments
	smile->cipher_key = key;
	printf("%s", key);
	smile = new CipherCheshire();
	string cipher = "";
	int counter;
	for (int i = 0; i < MAX_LENGTH; i++) {
		if (i == key.length()) {
			counter = 0;
		}
		//cipher += key[counter];
		counter++;
	}
	int i = 0;
	smile->cipher_key = key;

}
VCipher::~VCipher() {
	delete(smile);
}

