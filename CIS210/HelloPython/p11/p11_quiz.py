''' 
CIS 210 STYLE
CIS 210 W19 Project 1-1

Author: Patrick Thomasma

Credits: [N/A]

Add docstrings to Python functions that implement quiz 1 pseudocode.
(See p11_cricket for examples of functions with docstrings.)
'''

def q1(onTime, absent): #Function header
    '''(string) -> string
                        #Brief desciption If input matches listed functions
                        then it will return the statement if there is no matching input
                        tben it will return with Better late than never
                        #Examples of use
                        >>> q1(ontime)
                        ... Hello!
                        >>>q1(not there)
                        ... Better late than never.
                    
'''
   
 
    if onTime:
        return('Hello!')
    elif absent:
        return('Is anyone there?')
    else:
        return('Better late than never.')

def q2(age, salary): #Function Header
    ''' (int) -> int
    Returns true if input matches the paramaters and returns false if input is outside
    of paramaters

    >>> q2(18,100000)
    False
    >>>q2(5,10)
    True
        
    '''
    return (age < 18) and (salary < 10000)

def q3():
    '''
    (int) -> int
    Will return 6 based off the paramaters that are given in the function

    >>>q3()
    6
    '''
    p = 1
    q = 2
    result = 4
    if p < q:
        if q > 4:
            result = 5
        else:
            result = 6

    return result

def q4(balance, deposit):
    '''
   (int)-> int
   The input of balance and deposit will go through the loop 10 times until count
   reaches 10 and then the function will return the total balance from the loop
   >>>q4(10,10)
   110
   >>>q4(4567,678)
   11347
    '''
    count = 0
    while count < 10:
        balance = balance + deposit
        count += 1

    return balance

def q5(nums):
    '''
    (int) -> int
    The code has to have an input of an array and the while/if nets will
    determine how many numbers are positive in the array
    >>> q5([1,-2,4,-2,5])
    ... 3
    >>>q5([-1,-2,-3,-4,5])
    ... 1
    
    '''
    result = 0
    i = 0
    while i < len(nums):
        if nums[i] >= 0:
            result += 1

        i += 1

    return result

def q6():
    '''
    (int) -> int
    The code will go will loop through i till its 4 and whatever p
    results will the code will return that number
    >>>q6()
    16

    The bug in the code involved i=1 being under the while loop which had probably
    confused the code and resulted into nothing being outputed
    '''
    i = 0
    p = 1
    while i < 4:
        p = p * 2
        i += 1

    return p
