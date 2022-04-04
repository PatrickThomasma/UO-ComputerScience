#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire {
    string cipher_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);


// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
   smile = new CipherCheshire(); 
   smile->cipher_alpha = "zyxwvutsrqponmlkjihgfedcba"; 
}

/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
	smile = new CipherCheshire();
	if (is_valid_alpha(cipher_alpha))
		smile->cipher_alpha = cipher_alpha;
	else
		cout << "Invalid alpha!" << endl;
}

/* Destructor
 */
Cipher::~Cipher()
{
	free(smile);
	delete(smile);
}

/* This member function encrypts the input text 
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{	
    cout << "Encrypting...";
    string truealpha = "abcdefghijklmnopqrstuvwxyz";
    string alpha = smile->cipher_alpha;
    string retStr = "";
    char ch, temp;
    int pos;
    for (int i = 0; i < raw.length(); i++) {
	    temp = ' ' ;
	    ch = raw.at(i);
	    if (ch != ' ') {
		    pos = find_pos(truealpha, ch); //looking through the OG alphabet for the spot
		    if (ch >= 65 && ch <= 90) { //ascii to check if letter is capital or not
			    for (int i = 0; i <= pos; i++) {
				    temp =  alpha[i]; //now go through encrypted alphabet so find the matching member
				    temp = UPPER_CASE(temp);
			    }
		    }
		    else {
			    for (int i = 0; i <= pos; i++) {
				    temp = alpha[i]; 
			    }
		    }
	    }
	    retStr += temp;
    }

    cout << "Done" << endl;

    return retStr;
}


/* This member function decrypts the input text 
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr = "";
    string truealpha = "abcdefghijklmnopqrstuvwxyz";
    string alpha = smile->cipher_alpha;
    cout << "Decrypting...";
    char ch, temp;
    int pos;
    for ( int i = 0; i < enc.length(); i++) { //for loop for encrpted keyword to decrpyt
 	    temp = ' ';
	    ch = enc.at(i);
	    if (ch != ' ') {
		    pos = find_pos(alpha, ch);
		    if (ch >= 65 && ch <= 90) {
		    	for (int i = 0; i <= pos; i++) {
                            	temp =  truealpha[i]; //basically opposite we look through encrpted member to find spot there then go through OG alphabet to find member
                           	temp = UPPER_CASE(temp);
                    }
		    }
                    else {
                            for (int i = 0; i <= pos; i++) {
                                    	temp = truealpha[i];
			    }

		    }
    }
	    retStr += temp;
    }

    cout << "Done" << endl;

    return retStr;

}
// -------------------------------------------------------


//  Helper functions 
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;
    char ch = LOWER_CASE(c);
    for (int i = 0; i < alpha.length(); i++) {
	    if (ch == alpha.at(i)) {
		    pos = i;
		    break;
	    }
    }

   

    return pos;
}

/* Make sure the cipher alphabet is valid - 
   a) it must contain every letter in the alphabet 
   b) it must contain only one of each letter 
   c) it must be all lower case letters 
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if(alpha.size() != ALPHABET_SIZE) {
        is_valid = false; 
    } else {
        unsigned int letter_exists[ALPHABET_SIZE];
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            letter_exists[i] = 0;
        }
        for(unsigned int i = 0; i < alpha.size(); i++) {
            char c = alpha[i];
            if(!((c >= 'a') && (c <= 'z'))) {
                is_valid = false;
            } else {
                letter_exists[(c - 'a')]++;
            }
        }
        for(unsigned int i = 0; i < ALPHABET_SIZE; i++) {
            if(letter_exists[i] != 1) {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
