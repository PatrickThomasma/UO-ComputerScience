'''
Intro to python Exercises
CIS 210 W19 Project 2
Author: Patrick Thomasma
Write function that will give the total netpay for amount of hours worked'''
def tax(gross):
    '''determines tax, given gross'''
    tax = gross * 0.15#tax is total * percentage
    return tax

def netpay(n):
    gross = n * 10.75
    '''determines net pay of employee, given number of hours worked'''
    net = gross - tax(gross)#tax(gross) will call up function for use
    net = round(net, 2)
    print(net)
def main():
    '''Net pay program driver'''
    print(f'For 10 hours work, netpay is:',netpay(10))
    print(f'For 40 hours work, netpay is:',netpay(40))#Call up netpay for print
    return None
main()
