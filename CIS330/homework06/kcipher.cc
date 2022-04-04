#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"




/* Helper function definitions
 */

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------
struct KCipher::CipherCheshire {
    vector <string> cipher_alpha;
    string cipher_key;
};


KCipher::KCipher() {
	smile = new CipherCheshire();
	smile->cipher_key = "";
	smile->cipher_alpha.push_back("");
}

KCipher::KCipher(string cipher_alpha) {
	smile = new CipherCheshire();
	smile->cipher_alpha.push_back(cipher_alpha);
}

void KCipher::add_key(string cipher_alpha) {
	smile->cipher_alpha.push_back(cipher_alpha); //pushing the strings into the vector
}
void KCipher::set_id(int page) {
	vector <string> book = smile->cipher_alpha; //getting the page from the book
	smile->cipher_key = book[page];
}

KCipher::~KCipher() {
	free(smile);
	delete(smile);
}


string KCipher::encrypt (string raw) {
	
	int i,j,k,t = 0;
	char letter , ch;
	int temp;
	int counter = 0;
	string retString;
	string finalstring;
	string tempString = smile->cipher_key;
	for (int i = 0; i < tempString.length(); i++) {
		if (tempString[i] == ' '){
			continue;
		} //strip away the space for the running key
		retString += tempString[i];
	}
	//for (int i = 0; i < retString.length(); i++) {
		//printf("%c", retString[i]);
	//}
	for (i = 0; i < raw.length(); i++ , k++, t++) {
		letter = raw[i];
		if (letter == ' ') { //if the string is a space then move on
			finalstring += ' ';
			continue;
		}
		ch = retString[counter]; // use counter because if its space we dont want incrementation for retString to go awry
		temp = (UPPER_CASErk(letter) + UPPER_CASErk(ch)) % 26; //add together the ascii's and number happens to be apart of alphabet after addding 97
		temp += 97;
		finalstring += temp;
		counter++;
	}
	return finalstring;





}


string KCipher::decrypt (string enc) {
	
        int i,j,k = 0;
        char letter , ch;
        int temp;
	int counter = 0;
        string finalstring;
        string retString;
	string tempString = smile->cipher_key;
 	for (int i = 0; i < tempString.length(); i++) {
        if (tempString[i] == ' '){ //space go gone
               continue;
               }
        retString += tempString[i];
        	}

               for (i = 0; i < enc.length(); i++) {
                letter = enc[i];
                if (letter == ' ') { //same deal if it's a space then get it outta here
                        finalstring += ' ';
			continue;
			
                }
                ch = retString[counter];
                temp = (UPPER_CASErk(letter) - UPPER_CASErk(ch) + 26) % 26; //similar equation as last time except tiwll be be the plain - key +26 % 26
                temp += 97;
                finalstring += temp;
		counter++;
        }

       
        return finalstring;



}

unsigned int find_posrk(string alpha, char c) //thought I was going to have to use this in earlier implementation of algorithm but that got blown out
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

