'''
Intro to python Exercises
CIS 210 W19 Project 2
Author: Patrick Thomasma
Writing a function that uses babylonian square roots and return the square root and
num of iterations
'''
import math
def mysqrt(n , k):
    if n == 0: #If the input is 0 then the square root will always be 0
        return n;
    
    square = 1 #Assignments for the function
    x = 0
    i = 1
    while x != k:#aslong as x doesn't equal k then while loop will keep running
        square = .5*(i + n/i)#run through an equation and return as square
        i = square #use the answer from previous square and hold for the next iteration
        x += 1
        if x == k:# when x equals k the loop will stop and return the sq.root with itertaions
            return square
def sqrt_compare(num, iterations):
    n = num
    k = iterations
    absolute = math.sqrt(num)#Assign int so print will look nicer
    final = mysqrt(n, k)
    something = final - absolute
    absfinal = round(something, 2)#round to nearest number in hundreth place
    print(f"For {n} using {k} iterations:")
    print("mysqrt value is:", mysqrt(n, k))#in print call function mysqrt
    print("math lib sqrt value is:", absolute)
    print(f"This is a {absfinal} percent error") 

def main():
    sqrt_compare(25,5)
    sqrt_compare(25,10)
    sqrt_compare(625,5)
    sqrt_compare(625,10)
    sqrt_compare(10000,8)
    sqrt_compare(10000,10)
    sqrt_compare(10000,11)
    return None
main()
