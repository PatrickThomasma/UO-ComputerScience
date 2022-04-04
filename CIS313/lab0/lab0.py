import math
class mathOps:

    def __init__(self, u, v):
        self.u = u
        self.v = v
    
    def __repr__(self):
        return "LeastCommonMultiple({}, {})".format(self.u, self.v)
    
    def __str__(self):
        return "GreatestCommonDivisor({}, {}).".format(self.u, self.v)

    def valid(self):
        return isinstance(self.u, int) and isinstance(self.v, int)
    
    def gcd(self):
      # Find the greatest common divisor of a and b
      # Hint: Use Euclid's Algorithm
      # https://en.wikipedia.org/wiki/Euclidean_algorithm#Procedure
        tempU = self.u
        tempV = self.v
         
        try:
          if tempU == (float("inf") or float("-inf")) or tempV == (float("inf") or float("-inf")):
            raise OverflowError
          tempU = abs(math.ceil(tempU))
          tempV = abs(math.ceil(tempV))
          rem = tempV % tempU
          while rem != 0:
              tempU = rem
              rem = tempV % rem
              tempV = tempU
          return tempU

        
      

        except OverflowError:
          print("one or both the values of", tempU, " and ", tempV, "are equal to infinity")
          raise OverflowError
          
             

        
    def lcm(self):
      # Find the least common multiple of a and b
      # Hint: Use the gcd of a and b
      try:
        tempU = self.u
        tempV = self.v
        if tempU == (float("inf") or float("-inf")) or tempV == (float("inf") or float("-inf")):
            raise OverflowError
        tempU = math.ceil(abs(tempU))
        tempV = math.ceil(abs(tempV))
        denom = self.gcd()

        return (tempU * tempV) / denom
      except OverflowError:
          print("one or both the values of", tempU, " and ", tempV, "are equal to infinity")
          raise OverflowError

