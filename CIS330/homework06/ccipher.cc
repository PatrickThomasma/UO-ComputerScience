#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"


// -------------------------------------------------------
// Caesar Cipher implementation


// -------------------------------------------------------

struct Cipher::CipherCheshire {
    string cipher_alpha;
    int cipher_offset;
};

CCipher::CCipher() {
	smile = new CipherCheshire();
	smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
	smile->cipher_offset = 0;

}

CCipher::CCipher(int offset) {
	smile->cipher_offset = offset;
	if (offset < 0) { //if offset is less than 0 obviously its an error
		cout << "Caesar value is less than 0" << endl;
		exit(1);
	}
	smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
	rotate_string(smile->cipher_alpha, smile->cipher_offset);
	string retstr = smile->cipher_alpha;
	//for (int i = 0; i < retstr.length(); i++) {
		//printf("%c\n", retstr[i]);
	//}
}

CCipher::~CCipher() {
	free(smile);
	delete(smile);

}


// Rotates the input string in_str by rot positions
void rotate_string(string& in_str, int rot)
{

	string Retstr = in_str;

	char letter;
	for (int i = 0; i < Retstr.length(); i++) {
		letter = Retstr[i];


		letter -= 97;
		letter = (letter + rot + 26) % 26; //rotation equation that will take offset https://stackoverflow.com/questions/522778/caesar-cipher-in-c used this as a reference
		//printf("%d:\n", letter);
		letter += 97;

		Retstr[i] = letter;
	}
	in_str = Retstr;
}

    // TODO: You will likely need this function. Implement it.
