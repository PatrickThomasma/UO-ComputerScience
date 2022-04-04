import unittest
import pqueue
import mheap


class T0_pqueue_insert(unittest.TestCase):


    def test_1_pq_insert(self):
        print("\n")
        pq = pqueue.pqueue(5)
        pq.insert(1)
        pq.insert(2)
        pq.insert(3)
        pq.insert(4)
        pq.insert(5)
        pq_list = [element for element in pq]
        self.assertEqual(pq_list, [5,4,2,1,3])
        print("\n")

    def test_extract_multiple(self):
        ex = mheap.max_heap(5)
        ex.insert(8)
        ex.insert(5)
        ex.insert(6)
        ex.insert(9)
        ex.insert(100)
        ex.extract_max()
        self.assertEqual(ex.get_heap(), [9,8,6,5,None])

    def test_extract_all(self):
        p = mheap.max_heap(5)
        p.insert(8)
        p.insert(5)
        p.insert(6)
        p.insert(9)
        p.insert(100)
        p.extract_max()
        p.extract_max()
        p.extract_max()
        p.extract_max()
        p.extract_max()
        self.assertEqual(p.get_heap(), [None,None,None,None,None])

    def test_insert_on_mheap(self):
        ex = mheap.max_heap(5)
        ex.insert(8)
        ex.insert(5)
        ex.insert(6)
        ex.insert(9)
        ex.insert(100)
        self.assertEqual(ex.get_heap(), [100,9,6,5,8])

    def test_empty(self):
        ex = mheap.max_heap(5)
        self.assertEqual(ex.get_heap(), [None,None,None,None,None])

    def test1_pq_insert(self):
        print("\n")
        pq = pqueue.pqueue(5)
        pq.insert(1)
        pq.insert(2)
        pq.insert(3)
        pq.insert(4)
        pq.insert(5)
        pqlist = [element for element in pq]
        self.assertEqual(pqlist, [5,4,2,1,3])
        print("\n")

class T1_pqueue_peek(unittest.TestCase):

    def test_1_pq_peek(self):
        print("Just return the fist element of the queue.")
        print("\n")
        pq = pqueue.pqueue(5)
        pq.insert(1)
        pq.insert(2)
        pq.insert(3)
        self.assertEqual(pq.peek(), 3)
        print("\n")


class T2_pqueue_extract_max(unittest.TestCase):

    def test_1_pq_extract_max(self):
        print("extract and return the maximum element of the queue")
        print("\n")
        pq = pqueue.pqueue(5)
        pq.insert(1)
        pq.insert(2)
        pq.insert(3)
        self.assertEqual(pq.extract_max(), 3)
        print("\n")


class T5_heap_sort(unittest.TestCase):

    def test_heap_sort_1(self):
        print("\n")
        to_sort_list = [10,24,3,57,4,67,37,87,7]
        sorted_list = mheap.heap_sort(to_sort_list)

        self.assertEqual(sorted_list, [3, 4, 7, 10, 24, 37, 57, 67, 87])
        print("\n")

    def test_heap_sort_2_doubles(self):
        print("\n")
        sortlist = [10,10,24,24,3,57,4,67,37,87,7]
        sorted_list = mheap.heap_sort(sortlist)
        self.assertEqual(sorted_list, [3,4,7,10,10,24,24,37,57,67,87])

class test_error(unittest.TestCase):
    
    def test_keyError(self):
        print("\n")
        pq = pqueue.pqueue(5)
        with self.assertRaises(KeyError):
            pq.extract_max()
        print("\n")

class test_error(unittest.TestCase):
    def test_IndexError(self):
        print("\n")
        pq = pqueue.pqueue(5)
        pq.insert(1)
        pq.insert(2)
        pq.insert(3)
        pq.insert(4)
        pq.insert(5)
        with self.assertRaises(IndexError):
            pq.insert(6)
        print("\n")
    

    
    
if __name__ == '__main__':
    unittest.main()
