#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

class CCipher : public Cipher {
public:
	CCipher();
	CCipher(int offset);
	~CCipher();


};
/* A class that implements a
   Caesar cipher class. It 
   inherits the Cipher class */
// TODO: Implement this class

/* Helper function headers 
 */
void rotate_string(string& in_str, int rot);
#endif

