def convert(i,j,k):
    x=str(i)
    y=str(j)
    z=str(k)
    return z+y+x

def add_digits(n):
    nums=str(n)
    i=0
    result=0
    while i < len(nums):
        result = int(nums[i]) + result
        i += 1
    return result
def add_digitz(n):
    numbs=str(n)
    result = 0
    for i in numbs:
      result+=int(i)
    return result

"using for loop and while loop they both are functionally the same and they work with numbers"
"of any length but personally I prefer while loop since its more easily comprehendable for me"
    

def profit(n):
    return (n*5)-(20+.50*n)
    

        
    
