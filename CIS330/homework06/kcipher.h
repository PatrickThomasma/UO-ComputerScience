#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

class KCipher {
	protected:
		struct CipherCheshire;
		CipherCheshire *smile;
	public:
		KCipher();
		KCipher(string key);
		virtual void add_key(string key);
		virtual void set_id (int page);
		~KCipher();
		virtual string encrypt(string raw);
		virtual string decrypt(string enc);

};

unsigned int find_posrk(string alpha, char c);
inline char UPPER_CASErk(char c) {
    return toupper(c);
}
inline char LOWER_CASErk(char c) {
    return tolower(c);
}

/* A class that implements a
   Running key cipher class. It 
   inherts class Cipher */
// TODO: Implement this function
#endif

