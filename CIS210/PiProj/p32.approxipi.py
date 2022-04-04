'''
Approximating pi.  CIS 210 W19 Project 3-2
Author: Patrick Thomasma
Credits: N/A
Approximate pi based on number of dots that are in the circle based
on the distance formula

'''
import random
import math
def montePi(numDarts):
    '''
     (int) -> float
    #will take the number of darts thrown at board and return the pi for amount of darts
    inside of the circle
    #examples
    >>> montePi(50)
    3.12
    >>>montePi(100)
    3.08
    >>>montePi(500)
    3.064
    '''

    inCircle = 0 # set incircle to 0 for the for loop to repeat

    for i in range(numDarts):#for loop will go loop as many times as darts there are
        x = random.random()
        y = random.random()

        boo = isInCircle(x,y,1)#call to isinCircle for distance formula

        if boo:#when Isincircle is true then add 1 to Incircle
            inCircle += 1

    approxpi = inCircle/numDarts * 4 #Amount of darts in the circle divided by the total numberof darts

    return approxpi
def isInCircle(x,y,r):
    '''
     (int,int,int) -> Boolean
    #desc isInCircle will use the x and y from random and try to find whether darts are within
    circle or not
    #examples
    isInCircle(0,0,1)
    True
    isInCircle(0.5,0.5,1)
    True
    isIncirlce(1,1,1)
    False
    '''
    

    d = math.sqrt(x**2 + y**2)#Distance formula for random x and y

    if d <= r: # determine whether the dart is in the circle or not
        return True 
    else:
        return False
def reportPi(i,approxpi):#on shell replace approxpi for a call to montepi(i)
    '''
     (int,float) -> string
    report pi will take however many interations and compare the approxi pi of it and compare
    it to intial pi
    #examples
    >>>reportPi(100, montePi(100))
    With 100 iterations:
    my approximate value for pi is: 2.92
    math lib pi value is: 3.141592653589793
    This is a 0.14 percent error.
    >>>reportPi(500,montePi(500))
    With 500 iterations:
    my approximate value for pi is: 3.024
    math lib pi value is: 3.141592653589793
    This is a 0.02 percent error.
    >>>reportPi(1000,montePi(1000))
    With 1000 iterations:
    my approximate value for pi is: 3.176
    math lib pi value is: 3.141592653589793
    This is a 0.01 percent error.
    
    '''
    numDarts = i #Set assignments for the print assignment further down
    final = montePi(numDarts)#call montepi for pi running through i itertaions
    absolute = final - math.pi
    something = round(absolute, 2)
    calculation = abs(something)
    
    print(f'With {numDarts} iterations:')
    print('my approximate value for pi is:', montePi(numDarts))
    print('math lib pi value is:',math.pi)
    print(f'This is a {calculation} percent error.')

def main():
    '''
    calls ReportPi
    '''
    reportPi(100,montePi(100))#call reportpi for multiple print lines
    reportPi(1000,montePi(1000))
    reportPi(10000,montePi(10000))
    return None
main() 
    

    
    
    
