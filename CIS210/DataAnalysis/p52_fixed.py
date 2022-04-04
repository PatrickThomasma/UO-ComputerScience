'''
Patrick Thomasma
Testing and debugging
CIS 210 Project 5-2 Winter 2019

Functions need to be tested.
'''
import doctest

def bigSalesBug(sales_list):
    '''(list) -> number

    Returns sum of all sales for amounts at or over $40,000.
    sales_list has the record of all the sales.

    >>> bigSalesBug([40000, 45.67, 19000.0, 25000, 100000])
    140000
    >>> bigSalesBug([])
    0
    >>> bigSalesBug([1,2,3,4,5,6,150000])
    150000
    '''
    total = 0 #changed this to a int so the test case is applicable
    for sales in sales_list:
        if sales >= 40_000: #if statement was missing colon
            total += sales #sales was misspelt as 'saales'
    return total #return statement was idented too much 

def ratsBug(weight, rate):
    '''(number, number) -> tuple

    Return number of weeks it will
    take for a rat to weigh 1.5 times
    as much as its original weight
    (weight > 0) if it gains at rate (rate > 0).

    >>> ratsBug(10,.1)
    (16.1, 5)
    >>> ratsBug(0.1,.1)
    (0.2, 5)
    >>> ratsBug(1000,100)
    (101000, 1)
    >>> ratsBug(0,0)
    (0, 0)
    '''
    weeks = 0
    startweight = weight  #had to add a variable here since weight was just comparing to itself
    while weight < (1.5 * startweight): #startweight here so we can accurately find 1.5 of the og weight
        weight += weight * rate #also made weight no equal to the 1.5 * startweight
        weeks += 1
        
    weight = round(weight, 1)
    return (weight, weeks)

def my_averageBug(dataset):
    '''(list of numbers) -> float

    returns average of values in dataset,
    but zeros do not count at all
    
    >>> my_averageBug([2, 3])
    2.5
    >>> my_averageBug([2, 0, 3])
    2.5
    >>> my_averageBug([1,2,3,4,5,6,7,8,0])
    4.5
    >>> my_averageBug([])
    0
    '''
    count = 0
    total = 0
    for value in dataset:
        if value != 0: #if value was equal to a string so I took made it back into a integer
            total += value
            count += 1 #Idented count so it'll be in if statement
    if count != 0:
        avg = total/count
    else:
        avg = 0
    return avg

def countSeqBug(alist):
    '''(list) -> int

    Returns the length of the longest recurring
    sequence in alist, a list of strings.

    >>> countSeqBug(['a', 'b', 'c', 'c', 'd', 'e'])  	
    2
    >>> countSeqBug([])
    0
    >>> countSeqBug(['c','b','c','c','c','c'])
    4
    '''
    if len(alist) != 0:
        prev_item = alist[0]
        dup_ct = 1
        high_ct = 1
    else:
        high_ct = 0
        dup_ct = 0
        
    for i in range(1, len(alist)):
        if alist[i] == prev_item:
            dup_ct += 1
        else:
            prev_item = alist[i]
            dup_ct = 1 #this is added here so the sequence resets when it breaks but longest should still be stored as high_ct

        if dup_ct > high_ct: #had to unindent this function under the loop instead of in the end of it
            high_ct = dup_ct
            #had to remove dup_ct = 1 here since it would reset the sequence at the wrong time

    return high_ct

def salesReportBug(salesli):
    '''(list) --> None

    Prints report of sales totals for each day of week (salesli)
    and range of per-day sales. salesli is non-empty - 0 sales
    for any day are reported as 0.

    > salesReportBug([40000, 45.67, 19000.0, 25000, 100000]) 
    Weekly Range: $45.67 - $100,000.00
    
    Mon          Tue          Wed          Thu          Fri         
    $40,000.00   $45.67       $19,000.00   $25,000.00   $100,000.00
    > salesReportBug([1,0,0,0,0])
    Weekly Range: $0.00 - $1.00
    
    Mon          Tue          Wed          Thu          Fri         
    $1.00        $0.00        $0.00        $0.00        $0.00
    > salesReportBug([0])
    Weekly Range: $100.00 - $100.00
    #took out the three carrots and made it into one
    Mon          Tue          Wed          Thu          Fri         
    $0.00     
    

    '''
    #calculate and report low and high sales
    a = salesli[:]#use this to copy the salesli so it doesnt returned sorted for the end print
    low, high = findRangeBug(a)
    print(f'Weekly Range: ${low:,.2f} - ${high:,.2f}\n')

    #print daily report header
    fw = 12
    print(f"{'Mon':<{fw}} {'Tue':<{fw}} {'Wed':<{fw}} {'Thu':<{fw}} {'Fri':<{fw}}")

    #report on sales per day from list data
    for sales in salesli:
        print(f'${float(sales):<{fw},.2f}', end='')
        
    return None

def findRangeBug(salesli):
    '''(list) -> tuple

    Returns largest and smallest number in non-empty salesli.
    (Note that Python has built in funcs max and min
    to do this, but not using them here, so we can
    work with the list directly.)

    >>> findRangeBug([40000, 45.67, 19000.0, 25000, 100000])
    (45.67, 100000.0)
    >>> findRangeBug([1])
    (1.0, 1.0)
    >>> findRangeBug([0])
    (0.0, 0.0)
    '''
    salesli.sort()#sales list was returning none because sort() was making it none
    low = float(salesli[0])
    high = float(salesli[-1])
    return low, high

print(doctest.testmod())#removed comment for function to test it
