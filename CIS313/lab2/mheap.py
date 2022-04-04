import copy
#using copy library for a few functions
class max_heap(object):
    """Binary max-heap

    Supports most standard heap operations (insert, peek, extract_max).
    Can be used for building a priority queue or heapsort. Since Python
    doesn't have built-in arrays, the underlying implementation uses a
    Python list instead. When initialized, max_heap creates a new list of
    fixed size or uses an existing list.
    """

    def __init__(self, size = 20, data = None):
        """Initialize a binary max-heap.

        size: Total capacity of the heap.
        data: List containing the desired heap contents. 
              The list is used in-place, not copied, so its contents 
              will be modified by heap operations.
              If data is specified, then the size field is ignored."""

        # Add to this constructor as needed
        if data is not None:
            self.max_size = len(data)
            self.length = len(data)
            self.heap = data
        else:
            self.max_size = size
            self.length = 0
            self.heap = [None] * size #constructor for basics of the heap
        
    def get_heap(self):
        return self.heap


    def insert(self, data):
        """Insert an element into the heap.

        Raises IndexError if the heap is full."""
        # Tips : insert 'data' at the end of the list initially
        #      : swap with its parent until the parent is larger or you 
        #      : reach the root
        
        heap = self.get_heap()
        if (self.length >= self.max_size):
            raise IndexError ("cannot add anymore")
        heap[self.length] = data
        self.length = self.length + 1
        index = self.length -1
        while (index > 0 and self.get_heap()[self.__get_parent(index)] < self.get_heap()[index]):
            self.__swap(self.__get_parent(index),index)
            index = self.__get_parent(index)
        


    def peek(self):
        """Return the maximum value in the heap."""
        temp = self.get_heap()
        if (len(temp) == 0):
            return
        return temp[0]

    def extract_max(self):
        """Remove and return the maximum value in the heap.

        Raises KeyError if the heap is empty."""
        # Tips: Maximum element is first element of the list
        #     : swap first element with the last element of the list.
        #     : Remove that last element from the list and return it.
        #     : call __heapify to fix the heap
        
        if (self.length == 0): #if nothing then no heap
            raise KeyError("Heap is empty")
        heapmap = self.get_heap()
        self.__swap(0,self.length -1) #swap 0 and 1 short of length
        maxelement = heapmap[self.length-1]
        heapmap[self.length-1] = None
        self.length = self.length - 1 #length is decremented
        self.__heapify(0) #now heapify the 0
        heapmap = self.get_heap() #heap equals new map
        return maxelement
#function mainly taken from textbook

    def __heapify(self, curr_index, list_length = None):
        # helper function for moving elements down in the heap
        # Page 157 of CLRS book
        heapmap = self.get_heap()
        if (list_length is None):
            list_length = self.length #if None then list length will be too length
        l = self.__get_left(curr_index) #left side is left of heap
        r = self.__get_right(curr_index) #right is right side of heap
        largest = curr_index #largest equals index
        if (l < list_length and heapmap[l] > heapmap[curr_index]):
            largest = l
        if (r < list_length and heapmap[r] > heapmap[largest]):
            largest = r
        if (largest != curr_index): #largest will equal length of left or right pass through
            self.__swap(curr_index, largest) 
            self.__heapify(largest, list_length)
    #function taken from textbook
    def build_heap(self):
        # builds max heap from the list l.
        # Tip: call __heapify() to build to the list
        #    : Page 157 of CLRS book
        heapmap = self.get_heap()
        heap_size = self.length
        #the function will build a heap that will derive from the list that is given as a input
        for index in range(int(heap_size / 2-1), -1, -1):
            self.__heapify(index)


    ''' Optional helper methods may be used if required '''
    ''' You may create your own helper methods as required.'''
    ''' But do not modify the function definitions of any of the above methods'''

    def __get_parent(self, loc):
        # left child has odd location index
        # right child has even location index
        # if loc % 2 == 0:
        #     parent = int((loc - 2) / 2)
        # else:
        parent = int((loc - 1) / 2)
        return parent

    def __get_left(self, loc):
        return 2*loc + 1

    def __get_right(self, loc):
        return 2*loc + 2
        

    def __swap(self, a, b):
        # swap elements located at indexes a and b of the heap
        temp = self.heap[a]
        self.heap[a] = self.heap[b]
        self.heap[b] = temp
    



    

def heap_sort(l):
    """Sort a list in place using heapsort."""
    # Note: the heap sort function is outside the class
    #     : The sorted list should be in ascending order
    # Tips: Initialize a heap using the provided list
    #     : Use build_heap() to turn the list into a valid heap
    #     : Repeatedly extract the maximum and place it at the end of the list
    #     : Refer page 161 in the CLRS textbook for the exact procedure
    temp = copy.deepcopy(l)
    heapobj = max_heap(len(temp),temp)
    heap = heapobj.get_heap()
    heap_size = heapobj.length
    heapobj.build_heap()

    for index in range(len(l) -1,-1,-1):
        maxelement = heapobj.extract_max()
        l[index] = maxelement

    return l
