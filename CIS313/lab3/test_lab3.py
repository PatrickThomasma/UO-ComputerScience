import lab3
import unittest



class T0_tree__insert(unittest.TestCase):

    def test_balanced_binary_search_tree(self):
        print("\n")
        print("tree_insert_with_individual_check")
        t = lab3.Tree()

        t.insert(4)
        t.insert(2)
        t.insert(6)
        t.insert(1)
        t.insert(3)
        t.insert(5)
        t.insert(7)

        #The following check is without using tree as an iterator (which uses inorder traversal)
        #So this function also does not check the implementation of the traversal function

        self.assertEqual(t.root.data, 4)
        self.assertEqual(t.root.left.data, 2)
        self.assertEqual(t.root.left.left.data, 1)
        self.assertEqual(t.root.left.right.data, 3)
        self.assertEqual(t.root.right.data, 6)
        self.assertEqual(t.root.right.left.data, 5)
        self.assertEqual(t.root.right.right.data, 7)

        print("\n")

    def test_balanced_binary_search_tree_two(self):
        print("\n")
        print("tree_insert_with_individual_check_two")
        t = lab3.Tree()

        t.insert(20)
        t.insert(10)
        t.insert(40)
        t.insert(5)
        t.insert(15)
        t.insert(25)
        t.insert(75)
        t.insert(3)
        t.insert(7)
        t.insert(12)
        t.insert(16)
        t.insert(24)
        t.insert(30)
        t.insert(65)
        t.insert(90)


        self.assertEqual(t.root.data, 20)

        self.assertEqual(t.root.left.data, 10)
        self.assertEqual(t.root.left.left.data, 5)
        self.assertEqual(t.root.left.left.left.data, 3)
        self.assertEqual(t.root.left.left.right.data, 7)
        self.assertEqual(t.root.left.right.data, 15)
        self.assertEqual(t.root.left.right.right.data, 16)
        self.assertEqual(t.root.left.right.left.data, 12)

        self.assertEqual(t.root.right.data, 40)
        self.assertEqual(t.root.right.left.data, 25)
        self.assertEqual(t.root.right.left.left.data, 24)
        self.assertEqual(t.root.right.left.right.data, 30)
        self.assertEqual(t.root.right.right.data, 75)
        self.assertEqual(t.root.right.right.right.data, 90)
        self.assertEqual(t.root.right.right.left.data, 65)


    def test_skewed_right_binary_search_tree(self):
        print("\n")
        print("test_skewed_right_bst")
        t = lab3.Tree()

        t.insert(5)
        t.insert(20)
        t.insert(1000)
        t.insert(1299)

        self.assertEqual(t.root.data, 5)
        self.assertEqual(t.root.right.data,20)
        self.assertEqual(t.root.right.right.data, 1000)
        self.assertEqual(t.root.right.right.right.data, 1299)

        print("\n")




class T1_min_and_max(unittest.TestCase):

    def test_min_and_max(self):
        print("\n")
        print("Checkin the min and the max functions")
        t = lab3.Tree()

        t.insert(4)
        t.insert(2)
        t.insert(6)
        t.insert(1)
        t.insert(3)
        t.insert(5)
        t.insert(7)

        minimum = t.min()
        self.assertEqual(minimum, 1)
        maximum = t.max()
        self.assertEqual(maximum, 7)

        print("\n")



    def test_if_min_is_left_most_node(self):
        print("\n")
        print("Checkin if the min is the left most node")
        t = lab3.Tree()

        t.insert(20)
        t.insert(10)
        t.insert(30)
        t.insert(5)
        t.insert(15)
        t.insert(25)
        t.insert(35)

        minimum = t.min()
        self.assertEqual(t.root.left.left.data, 5)

        print("\n")


class T2_Traversal(unittest.TestCase):

    def test_traversal(self):
        print("\n")
        print("Checking all the three traversals")
        t = lab3.Tree()

        t.insert(4)
        t.insert(2)
        t.insert(6)
        t.insert(1)
        t.insert(3)
        t.insert(5)
        t.insert(7)
        tree_iterator = [node for node in t]
        inorder = [node for node in t.inorder()]
        preorder = [node for node in t.preorder()]
        

        print("__iter__(): inorder traversal")
        self.assertEqual(tree_iterator, [1, 2, 3, 4, 5, 6, 7])
        print("inorder traversal")
        self.assertEqual(inorder, [1, 2, 3, 4, 5, 6, 7])
        print("preorder traversal")
        self.assertEqual(preorder, [4, 2, 1, 3, 6, 5, 7])
        print("\n")







class T3_successor(unittest.TestCase):

    def test_successor(self):
        print("\n")
        print("successor function")
        tree_success = lab3.Tree()
        tree_success.insert(8)
        tree_success.insert(3)
        tree_success.insert(10)
        tree_success.insert(1)
        tree_success.insert(6)
        tree_success.insert(4)
        tree_success.insert(7)
        tree_success.insert(14)
        tree_success.insert(13)

        easy_success = tree_success.find_successor(8).data
        medium_success = tree_success.find_successor(10).data
        tough_success = tree_success.find_successor(7).data

        self.assertEqual(easy_success, 10)
        self.assertEqual(medium_success, 13)
        self.assertEqual(tough_success, 8)

        print("\n")


    def test_contains_and__find_node(self):
        print("\n")
        print("Contains method which uses the __find_node private method")
        tree_success = lab3.Tree()
        tree_success.insert(8)
        tree_success.insert(3)
        tree_success.insert(10)
        tree_success.insert(1)
        tree_success.insert(6)
        tree_success.insert(4)
        tree_success.insert(7)
        tree_success.insert(14)
        tree_success.insert(13)

        checkT = tree_success.contains(6)
        checkF1 = tree_success.contains(50)
        checkF2 = tree_success.contains(2)
        self.assertEqual(checkT, True)
        self.assertEqual(checkF1, False)
        self.assertEqual(checkF2, False)




class T4_delete(unittest.TestCase):

    def test_delete(self):
        print("\n")
        print("delete function")
        t = lab3.Tree()
        t.insert(8)
        t.insert(3)
        t.insert(10)
        t.insert(1)
        t.insert(6)
        t.insert(4)
        t.insert(7)
        t.insert(14)
        t.insert(13)

        l1 = [node for node in t]
        t.delete(7)
        l2 = [node for node in t]
        t.delete(6)
        l3 = [node for node in t]
        t.delete(8)
        l4 = [node for node in t]
        t.delete(10)
        l5 = [node for node in t]



        self.assertEqual(l1, [1, 3, 4, 6, 7, 8, 10, 13, 14])
        self.assertEqual(l2, [1, 3, 4, 6, 8, 10, 13, 14])
        self.assertEqual(l3, [1, 3, 4, 8, 10, 13, 14])
        self.assertEqual(l4, [1, 3, 4, 10, 13, 14])
        self.assertEqual(l5, [1, 3, 4, 13, 14])

        print("\n")


class T7_find_node(unittest.TestCase):
    def test_findnode(self):
        t = lab3.Tree()
        t.insert(4)
        t.insert(2)
        t.insert(6)
        t.insert(1)
        t.insert(3)
        t.insert(5)
        t.insert(7)
        self.assertEqual(t._Tree__find_node(9), None)



class T5_contains(unittest.TestCase):

    def test_contains(self):
        print("\n")
        print("contains function")
        t = lab3.Tree()
        t.insert(8)
        t.insert(3)
        t.insert(10)
        t.insert(1)
        t.insert(6)
        t.insert(4)
        t.insert(7)
        t.insert(14)
        t.insert(13)
        self.assertEqual(t.contains(13), True)
        self.assertEqual(t.contains(15), False)
        print("\n")

if __name__ == '__main__' :
    unittest.main()
