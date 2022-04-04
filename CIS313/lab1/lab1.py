class Node(object):
    """
    A class to represent a node.

    ...

    Attributes
    ----------
    data : int or float
        An individual character or number to be stored in a node
    next_node : object of class Node
        A pointer to the next node in a stack or queue

    Methods
    -------
    setData(data):
        Updates the value of data attribute of Node
    setNext(next_node):
        Updates the value of next_node attribute of Node
    getData():
        Returns the value of data attribute
    getNext():
        Returns the value of next_node attribute
    """
    def __init__(self, data = None, next_node = None):
        """
        Constructs (or initializes) the attributes for an object of the class

        ...

        Parameters
        ----------
        data : int or float
            An individual character or number to be stored in a node
        next_node : object of class Node
            A pointer to the next node in a stack or queue

        """
        self.__data = data
        self.__next_node = next_node

    def setData(self, data):
        '''Set the "data" data field to the corresponding input.'''
        self.__date = data

    def setNext(self, next_node):
        '''Set the "next_node" data field to the corresponding input.'''
        self.__next_node = next_node

    def getData(self):
        '''Return the "data" data field.'''
        return self.__data

    def getNext(self):
        '''Return the "next_node" data field.'''
        return self.__next_node

class Queue(object):
    """Provide class dosctring"""
    def __init__(self):
        self.__head = None
        self.__tail = None

    def __str__(self):
        '''Loop through your queue and print each Node's data.'''
        temp = self.__head
        Nodelist = list()
        while (temp is not None):
            Nodelist.append(temp.getData())
            temp = temp.getNext()
        return str(Nodelist)

    def enqueue(self, newData):
        '''Create a new node whose data is newData and whose next node is null
        Update head and tail.'''
        # Hint: Think about what's different for the first node added to the Queue
        node = Node(newData)
        if self.__tail is None:
            self.__head = node
            self.__tail = node
        else:
            self.__tail.setNext(node)
            self.__tail = node

    def dequeue(self):
        '''Return the head of the Queue
        Update head.'''
        #  Hint: The order you implement the above 2 tasks matters, so use a temporary node
        #          to hold important information
        #  Hint: Return null on a empty Queue
        # Hint: Return the element(data) that is dequeued.
        if self.__head is None:
            raise Exception("Queue is empty")
        else:
            temp = self.__head.getData()
            self.__head = self.__head.getNext()
            return temp

    def isEmpty(self):
        '''Check if the Queue is empty.'''
        if self.__head is None:
            return True
        else:
            return False

class TwoStackQueue(object):
    def __init__(self):
        self.__top = None
        self.__top2 = None

    def __str__(self):
        temp = self.__top2
        Nodelist = list()
        while (temp is not None):
            Nodelist.append(temp.getData)
            temp = temp.getNext()
        return str(Nodelist)


    def enqueue(self, newData):
        new = Node(newData)
        new.setNext(self.__top)
        self.__top = new
        pass


    def dequeue(self):
        print("Check here",self.__top2)
        if self.__top is None and self.__top2 is None:
            print("Q is empty")
            return None
        elif self.__top is not None and self.__top2 is None:
            #print("Should be last letter",self.__top.getData())
            while (self.__top is not None):
                temp = self.__top
                #print("Help me out", temp.getData())
                self.__top = self.__top.getNext()
                print(temp.getData())
                temp.setNext(self.__top2)
                self.__top2 = temp
                #print("This is",self.__top2.getData())
                #self.__top2 = self.__top2.getNext()
                #print(self.__top2)
            temp = self.__top2
            self.__top2 = self.__top2.getNext()
            #self.__top2 = self.__top2.getNext()
            #print("Help me out", self.__top2)
            return temp.getData()
        else:
            temp = self.__top2
            #print("this is," , self.__top2.getNext())
            self.__top2 = self.__top2.getNext()
            return temp.getData()

    def isEmpty(self):
        return self.__top is None



class Stack(object):
    """Provide class dosctring"""
    def __init__(self):
        ''' We want to initialize our Stack to be empty.
        (ie) Set top as null'''
        self.__top = None

    def __str__(self):
        '''Loop through your stack and print each Node's data.'''
        if self.__top is None:
            return self.__top
        stacklist = []
        temp = self.__top
        while temp:
            stacklist.append(temp.getData())
            temp = temp.getNext()
        return str(stacklist)

    def push(self, newData):
        '''We want to create a node whose data is newData and next node is top.
        Push this new node onto the stack
        Update top'''
        newnode = Node(newData)
        newnode.setNext(self.__top)
        self.__top = newnode
        pass

    def pop(self):
        ''' Return the Node that currently represents the top of the stack.
        Update top'''
        # Hint: The order you implement the above 2 tasks matters, so use a temporary node
        #         to hold important information
        # Hint: Return null on a empty stack
        # Hint: Return the element(data) that is popped
        if self.isEmpty():
            return None

        temp = self.__top.getData()
        self.__top = self.__top.getNext()
        return temp

    def isEmpty(self):
        '''Check if the Stack is empty.'''
        return self.__top is None

def isPalindrome(s):
    '''Use your Queue and Stack class to test wheather an input is a palindrome.'''
    myStack = Stack()
    myQueue = Queue()
    s = s.replace(" ", "")

    ## Helper function ##
    # print("stack data")
    # myStack.printStack()

    # print("queue data")
    # myQueue.printQueue()

    # Return appropriate value
    for i in range(len(s)):
        myQueue.enqueue(s[i])
        myStack.push(s[i])
    myStack.__str__()

    front = None
    back = None

    for i in range (len(s)):
        front = myQueue.dequeue()
        back = myStack.pop()
        if front.lower() != back.lower():
            return False
    return True

def isPalindromeEC(s):
    '''Implement if you wish to do the extra credit.'''
    mytwoStack = TwoStackQueue()
    myStack = Stack()
    print(s)
    s = s.replace(" ", "")
    for i in range(len(s)):
        mytwoStack.enqueue(s[i])
        myStack.push(s[i])
    myStack.__str__()
    front = None
    back = None

    for i in range(len(s)):
        front = mytwoStack.dequeue()
        print("Look at my queue", front)
        back = myStack.pop()
        print("Look at my stack", back)
        if front.lower() != back.lower():
            return False
    return True
