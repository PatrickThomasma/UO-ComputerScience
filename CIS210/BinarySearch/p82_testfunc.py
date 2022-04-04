'''
Patrick Thomasma
Credits: N/A
Testing and debugging
CIS 210 Project 8-2 Winter 2019
'''
import p81_binsearch as p81
import doctest
def test_isMember():
    '''
    () -> None
    Will test each of the test cases given and will return a statement on its value
    whether it be true or false
    '''
    test_cases=(((1, 2, 3, 3, 4), 4, True),
    ((1, 2, 3, 3, 4), 2, True),
    ('aeiou', 'i', True),
    ('aeiou', 'y', False),
    ((1, 3, 5, 7), 4, False),
    ((23, 24, 25, 26, 27), 5, False),
    ((0, 1, 4, 5, 6, 8), 4, True),
    ((0, 1, 2, 3, 4, 5, 6), 3, True),
    ((1, 3), 1, True),
    ((2, 10), 10, True),
    ((99, 100), 101, False),
    ((42,), 42, True),
    ((43,), 44, False),
    ((), 99, False))
    for test in test_cases:
         arg1 = test[0]
         expected_result = test[1]
         expected_output = test[2]
         

         #print(f"Checking {}('{}')...".format(f.__name__,arg1),end='')
         print(f"Checking {arg1}for target {expected_result}...",end ='')

         actual_result = p81.isMember(arg1,expected_result)

         if (actual_result == expected_output):
             print(f"Its value {actual_result} is correct!")
         else:
             print("Error: has wrong value {}, expected {}.".format(actual_result,expected_output))
    return None
def main():
    '''
    () -> None
    Will test the IsMember function and print the results of each test case
    '''
    test_isMember()
    print()

    return None
doctest.testmod()

if __name__ == '__main__':
    main()
