#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

class VCipher : public KCipher {
	public:
		VCipher();
		VCipher(string key);
		~VCipher();

};

/* A class that implements a
   Vigenere cipher class. It 
   inherts KCipher */
// TODO: Implement this class
#endif

