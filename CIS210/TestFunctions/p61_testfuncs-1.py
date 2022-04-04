import p41_alphapin_key as p41

def test_decode(f):
    '''
    (function) --> None
    will use the test cases and check each one with alphapindecode to see if the correspoinding
    answer is correct.
    >>> test_decode(p41.alphapinDecode)
    Itll report the test cases in the function
    >>> test_decode(p41.alphapinDecode2)
    Itll report the test cases in the second function
    '''
    test_cases =  (('lo', 43),('hi', 27),('bomelela', 3464140),
    ('bomeluco', 3464408),('', -1),('abcd', -1),('diju', 1234),)
    for test in test_cases:
        print("Checking {}('{}')...".format(f.__name__,test[0]),end='')
        if f(test[0]) == test[1]:
            print("Its value {} is correct!".format(test[1]))
        else:
            print("Tone is not in correct format")
    return None

def test_checkTone(f):
    '''
    (function) --> None
    Will look through the test cases and use checktone to find out if each test case is
    correct
    >>>test_checkTone(p41.checkTone)
    Itll check and report result of each test case
    >>>test_checkTone(p41.checkTone2)
    Itll check and report result of each test case
    '''
    test_cases =  (('lohi', True),('hajeku', True),('olih', False),
                       ('', False),('z', False),('zz', False), )
    for test in test_cases:
        print("Checking {}('{}')...".format(f.__name__,test[0]),end = '')
            
        if f(test[0]) == test[1]:
            print("... Its value {} is correct!".format(test[1]))
        else:
            print("Tone is not in correct format")
    return None

def main():
    '''
    () --> None
    each line in main will check the test cases in the correspoinding function
    >>> main()
    itll call each function and check the test cases for each
    '''
    test_decode(p41.alphapinDecode)
    print()
    test_decode(p41.alphapinDecode2)
    print()
    test_checkTone(p41.checkTone)
    print()
    test_checkTone(p41.checkTone2)
    return None
main()
    
        
