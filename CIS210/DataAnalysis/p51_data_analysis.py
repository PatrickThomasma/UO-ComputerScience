'''
Data analysis CIS 210 W19 Project 5-1
Author: Patrick Thomasma
Credits: N/A
Revise and revision mean,mode,median code and use frequency tables too
'''
def isEven(n):
    '''
    (int) ->  boolean
    Will determine of a number is even or odd
    >>> isEven(5)
    False
    >>> isEven(4)
    True
    >>> isEven(1)
    False
    '''
    if n % 2 == 0:
        return True
    else:
        return False
def median (alist):
    '''
    (list) -> number
    Put list in lower and higher
    >>> median ([1,2,3,7,1,2,9,2,7])
    2.5
    >>> median ([1,2,3,4,5,6,7,8])
    4
    >>> median([100,0,100,0,100,0])
    50
    '''
    copylist = alist[:]
    copylist.sort()
    n = len(alist)
    if isEven(n) == True:
        rightmid = len(copylist) // 2
        leftmid = rightmid - 1
        median = (copylist[leftmid] + copylist[rightmid])/2.0
    else:
        mid = len(copylist) // 2
        median = copylist[mid]
    return median
def mode(alist):
    '''
    (list) -> tuple
    will return the number(s) that shows up the most in the list
    >>> mode([1,1,2,5,4,1,2])
    1
    >>> mode([0])
    0
    >>> mode([1,1,1,2,2,2,3,5,6])
    '''
    countdict = {}
    alist = genFrequencyTable(alist)

    for item in alist:
        if item in countdict:
            countdict[item] = countdict[item] + 1
        else:
            countdict[item] = 1
    countlist = countdict.values()
    maxcount = max(countlist)

    modelist = []
    for item in countdict:
        if countdict[item] == maxcount:
            modelist.append(item)
    return modelist
def mean(alist):
    '''
    (list) -> float
    The mean finds the average of the list of numbers that are given
    >>> mean([1,2,3])
    2.0
    >>> mean([0])
    0.0
    >>> mean([100,100,100,100])
    100.0
    
    '''
    mean = sum(alist) / len(alist)
    return mean
def frequencyTable(alist):
    '''
    (list) -> tuple
    will show the number and the amount it shows up in the list
    >>> frequencyTable([1,1,2,5,3,4])
    ITEM FREQUENCY
    1       2
    2       1
    3       1
    4       1
    5       1
    >>> frequencyTable([0])
    ITEM FREQUENCY
    0       1
    >>> frequencyTable([1,1,1,1,1])
    ITEM FREQUENCY
    1       5
    '''
    countdict = {}
    alist = genFrequencyTable(alist)

    for item in alist:
        if item in countdict:
            countdict[item] = countdict[item] + 1
        else:
            countdict[item] = 1
    itemlist = list(countdict.keys())
    itemlist.sort()

    print("ITEM","FREQUENCY")

    for item in itemlist:
        print(item, "     ", countdict[item])
def genFrequencyTable(alist):
    '''
    (list) -> dictionary
    Will return a dictionary of a key and the value for the key
    >>> genFrequencyTable([3,5,2,1,5])
    {3: 1, 5: 2, 2: 1, 1: 1}
    >>> genFrequencyTable([0,0,0,0,0])
    {0: 5}
    >>> genFrequencyTable([1,1,1,1,2,3])
    {1: 4, 2: 1, 3: 1}
    '''
    countdict = {}
    for item in alist:
        if item in countdict:
            countdict[item] = countdict[item] + 1
        else:
            countdict[item] = 1
    return countdict
def main():
    '''
    main() ->
    will perform the main function
    '''
    print("Mean of earthquakes:",mean(equakes))
    print("Mode of earthquakes:",mode(equakes))
    print("Median of earthquakes:",median(equakes))
    print("Frequency of earthquakes",frequencyTable(equakes))
    print("GenFrequency of Earthquakes", genFrequencyTable(equakes))
    return None
equakes = [5.3, 3.0, 2.6, 4.4, 2.9, 4.8, 4.3,
2.6, 2.9, 4.9, 2.5, 4.8, 4.2, 2.6,
4.8, 2.7, 5.0, 2.7, 2.8, 4.3, 3.1,
4.1, 2.8, 5.8, 2.5, 3.9, 4.8, 2.9,
2.5, 4.9, 5.0, 2.5, 3.2, 2.6, 2.7,
4.8, 4.1, 5.1, 4.7, 2.6, 2.9, 2.7,
3.3, 3.0, 4.4, 2.7, 5.7, 2.5, 5.1,
2.5, 4.4, 4.6, 5.7, 4.5, 4.7, 5.1,
2.9, 3.3, 2.7, 2.8, 2.9, 2.6, 5.3,
6.0, 3.0, 5.3, 2.7, 4.3, 5.4, 4.4,
2.6, 2.8, 4.4, 4.3, 4.7, 3.3, 4.0,
2.5, 4.9, 4.9, 2.5, 4.8, 3.1, 4.9,
4.4, 6.6, 3.3, 2.5, 5.0, 4.8, 2.5,
4.2, 4.5, 2.6, 4.0, 3.3, 3.1, 2.6,
2.7, 2.9, 2.7, 2.9, 3.3, 2.8, 3.1,
2.5, 4.3, 3.2, 4.6, 2.8, 4.8, 5.1,
2.7, 2.6, 3.1, 2.9, 4.2, 4.8, 2.5,
4.5, 4.5, 2.8, 4.7, 4.6, 4.6, 5.1,
4.2, 2.8, 2.5, 4.5, 4.6, 2.6, 5.0,
2.8, 2.9, 2.7, 3.1, 2.6, 2.5, 3.2,
3.2, 5.2, 2.8, 3.2, 2.6, 5.3, 5.5,
2.7, 5.2, 6.4, 4.2, 3.1, 2.8, 4.5,
2.9, 3.1, 4.3, 4.9, 5.2, 2.6, 6.7,
2.7, 4.9, 3.0, 4.9, 4.7, 2.6, 4.6,
2.5, 3.2, 2.7, 6.2, 4.0, 4.6, 4.9,
2.5, 5.1, 3.3, 2.5, 4.7, 2.5, 4.1,
3.1, 4.6, 2.8, 3.1, 6.3]
main()
        
    
    
    
