'''
Binary conversion CIS 210 W19 Project 4-2
Author: Patrick Thomasma
Credits: Stephanie Schofield
Come up with a code that will translate any int number into a binary and vice
-versa
'''
import doctest
def dtob(n):
    '''
    int -> string
    #will take an integer and convert it into the corresponding binary number
    #examples
    >>> dtob(34)
    '100010'
    >>> dtob(55)
    '110111'
    >>> dtob(1212)
    '10010111100'
    '''
    end = ""
    if n == 0:
        return 0
    while n > 0:
        final = n % 2
        end = str(final) + end
        n = n // 2
    return end
def btod(b):
    '''
    string -> int
    #Will take a binary number and change it to its corresponding int number
    #examples
    >>> btod("101100")
    44
    >>> btod("1010")
    10
    >>> btod("111000")
    56
    '''
    a = len(b)
    g = len(b)-1
    i = 0
    end = 0
    for i in range (a):
        final = b[i]
        if final == "0":
          index = 0 
        if final == "1":
          index = 2 ** g
        end += index   
        g -= 1
    return end
print(doctest.testmod())
def main():
    '''
    calls dtob and btod to bring prove that each int has a corresponding binary
    number
    '''
    userdecimal = input('Enter non-negative integer: ')
    userdecimal = int(userdecimal)
    binary = dtob(userdecimal)
    print('Binary format is ', binary)
    decimal = btod(binary)
    print('Back to decimal: ', decimal)
    return None
main()
    
    
        
        
