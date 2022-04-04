'''
Encoding pin CIS 210 W19 Project 4-1
Author: Patrick Thomasma
Credits: Stephanie, Eliane, Bethany, Warren, Max
Come up wiht an integer and encode it with a string and then decode it back
into an integer

'''
import doctest
a = "bcdfghjklmnpqrstvwyz"
b = "aeiou"
def alphapinEncode(pin):
    '''
    int -> string
    #will take a sequence of integers and will seperate the integer into two
    and give each a consonent followed by a vowel
    #examples
    >>> alphapinEncode(346448)
    'juqumo'
    >>> alphapinEncode(3464140)
    'bomelela'
    >>> alphapinEncode(1298)
    'dizo'
    '''
    result = len(str(pin))
    code = ""
    while result > 0:
        first = pin % 100
        second = pin // 100
        n = first // 5
        k = first % 5
        cons = a[n]
        vow = b[k]
        final = cons + vow
        code = final + code
        pin = second
        result -= 2
    return code
def alphapinDecode(tone):
    '''
    string -> int
    #Will take a string and check if its valid and then it will decode it back
    to the original integer
    #examples
    >>> alphapinDecode('lohi')
    4327
    >>> alphapinDecode('pina')
    5750
    >>> alphapinDecode('bomeluco')
    3464408
    '''
    
    if checkTone(tone) == True:
        result = len(tone)
        s = 0
        k = 1
        code = ""
    if checkTone(tone) == False:
        print("Tone is not in correct Format.")
        print(-1)
        return None
    while result > 0:
        first = tone [s]
        second = tone [k]
        cons = a.find(first)
        pros = b.find (second)
        f = cons * 5
        final = f + pros
        if result % 2 == 0 and final < 10 and len(code) % 2 == 1:
            code = code + "0" + str(final)
            tone = tone[2:]
            result -= 2
        else:
            code = code + str(final)
            tone = tone [2:]
            result -= 2
    return int(code)
def checkTone(tone):
    '''
    string -> boolean
    will take a string and check if its a string that starts with a vowel
    and it followed by a vowel
    #examples
    >>> checkTone('bomelala')
    True
    >>> checkTone('pinaso')
    True
    >>> checkTone('pinaz')
    False
    '''
    result = len(tone)
    if result % 2 == 1 or result == 0:
        return False
    s = 0
    k = 1
    while result > 0:
        first = tone [s]
        second = tone [k]
        if first in a and second in b:
            result -= 2
            tone = tone[2:]
        else:
            return False
    return True
print(doctest.testmod())
def main():
    '''
    Program driver to alphapinEncode and alphapinDecode
    '''
    pins = input('What number would you like to encode? ')
    pins = int(pins)
    bits = alphapinEncode(pins)
    print(bits)
    dits = alphapinDecode(bits)
    print(dits)
    return None            
main()


