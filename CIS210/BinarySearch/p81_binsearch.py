'''
Patrick Thomasma
Credits: N/A
Testing and debugging
CIS 210 Project 8-1 Winter 2019
'''
def isMember(nums,t):
    '''
    tuple -> boolean
    Will take a list of numbers and try to find whatever the given target number
    is, if its in the list the function will return true if not then it will
    return false
    >>>isMember((1,2,3,4,5,6,7),7)
    True
    >>>isMember((1,5,6,8),4)
    False
    >>>isMember((),4)
    False
    '''
    x = len(nums) // 2
    while len(nums) > 1:
        if nums[x] > t:               
            nums = nums[0:x]
            x = len(nums) // 2
        elif nums[x] < t:
            nums = nums[x:len(nums)]
            x = len(nums) // 2
        else:
            return True
        
    return False
def main():
    print(isMember((1, 2, 3, 3, 4), 4))
    print(isMember((1, 2, 3, 3, 4), 2))
    print(isMember('aeiou', 'i'))
    print(isMember('aeiou', 'y'))
    print(isMember((1, 3, 5, 7), 4))
    print(isMember((23, 24, 25, 26, 27), 5))
    print(isMember((0, 1, 4, 5, 6, 8), 4))
    print(isMember((0, 1, 2, 3, 4, 5, 6), 3))
    print(isMember((1, 3), 1))
    print(isMember((2, 10), 10))
    print(isMember((99, 100), 101))
    print(isMember((42,), 42))
    print(isMember((43,), 44))
    print(isMember((), 99))
    
    return None
main()
                
