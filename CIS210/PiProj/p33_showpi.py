'''
Approximating pi.  CIS 210 W19 Project 3-3
Starter Code for showMontePi

Author: Patrick Thomasma

Credits: Based on code on p.78 Miller and Ranum text.

Approximate pi using a Monte Carlo simulation.
Then add graphics to visualize simulation.
'''

from turtle import *
import math
import random

def showMontePi(numDarts):
    '''
      (int)-> float
      Will take the number of darts and return approxpi based on amount inside
      circle defined by the distance formula
      #examples
    >>> montePi(50)
    3.12
    >>>montePi(100)
    3.08
    >>>montePi(500)
    3.064
      
    '''
    # set up canvas and turtle
    # to animate the algorithm;
    # draw x, y axes
    # new drawBoard function will replace this code
    
    drawBoard()
    # pen should stay up for drawing darts
 
    inCircle = 0

    # throw the darts and check whether
    # they landed on the dart board and
    # keep count of those that do
    for i in range(numDarts):
        x = random.random()
        y = random.random()

    # Revise code to call new isInCircle function.
    # See Project 3-2 and 3-3 specifications.

        d = isInCircle(x,y,1)

        # show the dart on the board
        if d == True:
            inCircle += 1
            color('blue')
        else:
            color('red')

        goto(x, y)
        dot()

    # calculate approximate pi
    approxPi = inCircle/numDarts * 4

    #wn.exitonclick()

    return approxPi
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
    

    d = math.sqrt(x**2 + y**2)

    if d <= r:
        return True
    else:
        return False
def drawBoard():
    '''
    ()->none
    Will draw the coordinate plane which the dots will form in
    examples:
    >>>drawBoard()
    (uses turtle to draw coordinate plane)
    '''
    
    wn = Screen()
    wn.setworldcoordinates(-2, -2, 2, 2)

    speed(0); hideturtle()
    penup()

    goto(-1, 0)
    pendown()
    goto(1, 0)
    penup()
    goto(0, 1)
    pendown()
    goto(0, -1)
    penup()
    goto(0, -1)
    return None
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
    This is a 0.01 percent error.'''
    numDarts = i #Set assignments for the print assignment further down
    final = approxpi #call montepi for pi running through i itertaions
    absolute = final - math.pi
    something = round(absolute, 2)
    calculation = abs(something)
    
    print(f'With {numDarts} iterations:')
    print('my approximate value for pi is:', approxpi )
    print('math lib pi value is:',math.pi)
    print(f'This is a {calculation} percent error.')
def main():
    '''
    ()-> none
    main function will call each function and put into shell
    examples
    >>>()
    With 100 iterations:
    my approximate value for pi is: 3.2
    math lib pi value is: 3.141592653589793
    This is a 0.06 percent error.
    '''
    k = showMontePi(100)
    reportPi(100,k)
    return None

main()
    

#add reportPi function
#add main function
