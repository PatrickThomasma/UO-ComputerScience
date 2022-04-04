import lab1
import unittest

class T0_TestingQueue(unittest.TestCase):

    def test_basic_enqueue(self):
        # testing the basic enqueue operation
        print("\n")
        q = lab1.Queue()
        q.enqueue(1)
        q.enqueue(2)
        q.enqueue(3)
        q.enqueue(4)

        self.assertEqual(q.__str__(), '[1, 2, 3, 4]')
        print("\n")

class T1_TestingStack(unittest.TestCase):

    def test_is_empty_false(self):
        # testing if queue is empty
        print("\n")
        s = lab1.Stack()
        s.push("4")
        print("return false if the stack is not empty")
        self.assertEqual(s.isEmpty(), False)
        print("\n")


class T2_TestingPalindrome(unittest.TestCase):

    def test_basic_string(self):
        # testing with basic string
        print("\n")
        string = "hello"
        p = lab1.isPalindrome(string)
        print("The string being tested is -> ", string)
        self.assertEqual(p, False)
        print("\n")

    def test_better_string(self):
        print("\n")
        string = "tenet"
        p = lab1.isPalindrome(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")


    def test_best_string(self):
        print("\n")
        string = "12TENET21"
        p = lab1.isPalindrome(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")


    def test_with_space(self):
        print("\n")
        string = "Eva       can I stab bats in a cave"
        p = lab1.isPalindrome(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")


class T3_TestingQueue(unittest.TestCase):
    def test_queue_function(self):
        print("\n")
        s = lab1.Queue()
        s.enqueue("5")
        print("return false if queue is not empty")
        self.assertEqual(s.isEmpty() , False)
        print("\n")


    def test_queue_empty(self):
        print("\n")
        s = lab1.Queue()
        s.enqueue("5")
        s.enqueue("4")
        s.dequeue()
        s.dequeue()
        print("return true if queue is empty")
        self.assertEqual(s.isEmpty(),True)
        print("\n")

class T4_TestingTwoStackQueue(unittest.TestCase):
    def test_two_stack(self):
        print("\n")
        s = lab1.TwoStackQueue()
        s.enqueue("5")
        print("return false if queue is not empty")
        self.assertEqual(s.isEmpty(), False)
        print("\n")


    def test_two_stackbetter(self):
        s = lab1.TwoStackQueue()
        s.enqueue("5")
        s.enqueue("4")
        s.enqueue("3")
        s.dequeue()
        s.dequeue()
        s.dequeue()
        print ("return true if queue is empty")
        self.assertEqual(s.isEmpty(), True)
        print("\n")



class T5_Testing_PalindromeEC(unittest.TestCase):
    def test_basic_string(self):
        # testing with basic string
        print("\n")
        string = "hello"
        p = lab1.isPalindromeEC(string)
        print("The string being tested is -> ", string)
        self.assertEqual(p, False)
        print("\n")

    def test_better_string(self):
        print("\n")
        string = "tenet"
        p = lab1.isPalindromeEC(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")


    def test_best_string(self):
        print("\n")
        string = "12TENET21"
        p = lab1.isPalindromeEC(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")


    def test_with_space(self):
        print("\n")
        string = "Eva       can I stab bats in a cave"
        p = lab1.isPalindromeEC(string)
        print("The string being tested is", string)
        self.assertEqual(p,True)
        print("\n")





























if __name__ == '__main__':
    unittest.main()
