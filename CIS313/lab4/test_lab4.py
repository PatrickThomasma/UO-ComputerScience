from rb_tree import Node, rb_tree
import unittest
 
class T0_tree_left_rotation(unittest.TestCase):

    def test_tree_left_rotation_1(self):
        print("\n")
        print("tree_left_rotation")
        tree = rb_tree()
        tree.bst_insert(2)
        tree.bst_insert(1)
        tree.bst_insert(3)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.left_rotate(tree.root)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [3,2,1])
        tree.print_tree()
        print("tree after left rotation about root  in prorder")
        print("\n")
    
    def test_tree_left_rotation_2(self):
        print("\n")
        print("tree_left_rotation")
        tree = rb_tree()
        tree.bst_insert(7)
        tree.bst_insert(5)
        tree.bst_insert(9)
        tree.bst_insert(3)
        tree.bst_insert(6)
        tree.bst_insert(8)
        tree.bst_insert(10)
        tree.bst_insert(1)
        tree.bst_insert(2)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.left_rotate(tree.root)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [9,7,5,3,1,2,6,8,10])
        tree.print_tree()
        print("tree after left rotation about root  in prorder")
        print("\n")
    


class T1_tree_right_rotation(unittest.TestCase):

    def test_tree_right_rotation_1(self):
        print("\n")
        print("tree_right_rotation")
        tree = rb_tree()
        tree.bst_insert(2)
        tree.bst_insert(1)
        tree.bst_insert(3)

        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.right_rotate(tree.root)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [1,2,3])
        tree.print_tree()
        print("tree after right rotation about root  in prorder")
        print("\n")
    
    def test_tree_right_rotation_2(self):
        print("\n")
        print("tree_right_rotation")
        tree = rb_tree()
        tree.bst_insert(7)
        tree.bst_insert(5)
        tree.bst_insert(9)
        tree.bst_insert(3)
        tree.bst_insert(6)
        tree.bst_insert(8)
        tree.bst_insert(10)
        tree.bst_insert(1)
        tree.bst_insert(2)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.right_rotate(tree.root)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [5,3,1,2,7,6,9,8,10])
        tree.print_tree()
        print("tree after right rotation about root  in prorder")
        print("\n")
    

class T2_tree_insert_color(unittest.TestCase):


    def test_tree_insert_color_0(self):
        print("\n")
        print("tree_color_check")
        
        tree = rb_tree()

        tree.insert(2)
        tree.insert(1)
        tree.insert(3)
        tree.insert(4)
        tree.print_tree()
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [2, 1, 3, 4])
        self.assertEqual(tree_preorder_color, ['black', 'black', 'black', 'red'])
        print("\n")


    def test_tree_insert_color_1(self):
        print("\n")
        print("tree_color_check")
        
        tree = rb_tree()

        for i in range(1, 8):
            tree.insert(i)
        tree.print_tree()
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [2, 1, 4, 3, 6, 5, 7])
        self.assertEqual(tree_preorder_color, ['black', 'black', 'red', 'black', 'black', 'red', 'red'])
        print("\n")

class T3_tree_delete(unittest.TestCase):


    def test_tree_delete_0(self):
        print("\n")
        print("tree_insert")
        #print("checking in order, preorder and post order")
        tree = rb_tree()

        tree.insert(7)
        tree.insert(5)
        tree.insert(9)
        tree.insert(6)
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [7, 5, 6, 9])
        self.assertEqual(tree_preorder_color, ['black', 'black', 'red', 'black'])
        tree.delete(9)
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [6, 5, 7])
        self.assertEqual(tree_preorder_color, ['black', 'black', 'black'])
        print("\n")

    def test_tree_delete_1(self):
        print("\n")
        print("tree_insert")
        print("checking in order, preorder and post order")
        tree = rb_tree()

        for i in range(1, 8):
            tree.insert(i)
        tree.delete(5)
        tree.delete(4)
        # tree.print_tree()
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [2, 1, 6, 3, 7])
        self.assertEqual(tree_preorder_color, ['black', 'black', 'red', 'black', 'black'])
        print("\n")
    
    def test_tree_delete_color_2(self):
        print("\n")
        print("tree_left_rotation")
        tree = rb_tree()
        tree.insert(7)
        tree.insert(5)
        tree.insert(9)
        tree.insert(3)
        tree.insert(6)
        tree.insert(8)
        tree.insert(10)
        tree.insert(1)
        tree.insert(2)
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [7, 5, 2, 1, 3, 6, 9, 8, 10])
        self.assertEqual(tree_preorder_color, ['black', 'red', 'black', 'red', 'red', 'black', 'black', 'red', 'red'])
        tree.delete(6)
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [7, 2, 1, 5, 3, 9, 8, 10])
        self.assertEqual(tree_preorder_color, ['black', 'red', 'black', 'black', 'red', 'black', 'red', 'red'])
        tree.delete(7)
        tree_preorder = [node.data for node in tree.preorder()]
        tree_preorder_color = [node.color for node in tree.preorder()]
        self.assertEqual(tree_preorder, [8, 2, 1, 5, 3, 9, 10])
        self.assertEqual(tree_preorder_color, ['black', 'red', 'black', 'black', 'red', 'black', 'red'])
        print("\n")

class additional_test_cases(unittest.TestCase):
    def test_left_rotate_of_intermediate_node(self):
        print("\n")
        print("tree_left_rotation_of_intermediate_node")
        tree = rb_tree()
        tree.bst_insert(2)
        tree.bst_insert(5)
        tree.bst_insert(8)
        tree.bst_insert(4)
        tree.bst_insert(6)
        tree.bst_insert(15)
        tree.bst_insert(10)
        tree.bst_insert(1)
        tree.bst_insert(2)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.left_rotate(tree.root.right)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [2, 1, 8, 5, 4, 2, 6, 15, 10])
        tree.print_tree()
        print("tree after left rotation about 9 in prorder")
        print("\n")

    def test_left_rotate_of_intermediate_node2(self):
        print("\n")
        print("tree_left_rotation_of_intermediate_node")
        tree = rb_tree()
        tree.bst_insert(7)
        tree.bst_insert(5)
        tree.bst_insert(9)
        tree.bst_insert(3)
        tree.bst_insert(6)
        tree.bst_insert(8)
        tree.bst_insert(10)
        tree.bst_insert(1)
        tree.bst_insert(2)
        tree.bst_insert(15)
        tree.bst_insert(20)
        tree.bst_insert(30)
        tree.bst_insert(4)
        tree.bst_insert(25)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.left_rotate(tree.root.left)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [7, 6, 5, 3, 1, 2, 4,9, 8, 10,15,20,30,25])
        tree.print_tree()
        print("tree after left rotation about 9 in prorder")
        print("\n")

    def test_left_rotate_of_middle_node(self):
        print("\n")
        print("tree_left_rotation_of_middle_node")
        tree = rb_tree()
        tree.bst_insert(7)
        tree.bst_insert(5)
        tree.bst_insert(9)
        tree.bst_insert(3)
        tree.bst_insert(6)
        tree.bst_insert(8)
        tree.bst_insert(10)
        tree.bst_insert(1)
        tree.bst_insert(2)
        tree.bst_insert(0)
        tree.print_tree()
        print("intial prorder tree", "\n")
        tree.left_rotate(tree.root.left.left.left)
        tree_preorder = [node.data for node in tree.preorder()]
        self.assertEqual(tree_preorder, [7, 5, 3, 2, 1, 0, 6, 9, 8, 10])
        tree.print_tree()
        print("Tree after left rotation about 9 in prorder")
        print("\n")

    def test_colours_post_insertion(self):
        print("\n")
        print("test_colors_post_insertion")
        tree = rb_tree()
        tree.insert(7)
        tree.insert(5)
        tree.insert(9)
        tree.insert(3)
        tree.insert(6)
        tree.insert(8)
        tree.insert(10)
        tree.insert(1)
        tree.insert(2)
        tree.print_tree()
        new_insert = tree.find_node(7)
        self.assertEqual(new_insert.color, "black")
        new_insert = tree.find_node(5)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(9)
        self.assertEqual(new_insert.color, "black")
        new_insert = tree.find_node(3)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(6)
        self.assertEqual(new_insert.color, "black")
        new_insert = tree.find_node(8)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(10)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(1)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(2)
        self.assertEqual(new_insert.color, "black")

    def test_colours_post_insertion(self):
        print("\n")
        print("test_colors_post_insertion")
        tree = rb_tree()
        tree.insert(6)
        tree.insert(7)
        tree.insert(8)
        tree.insert(2)
        tree.insert(5)
        tree.print_tree()
        new_insert = tree.find_node(6)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(7)
        self.assertEqual(new_insert.color, "black")
        new_insert = tree.find_node(8)
        self.assertEqual(new_insert.color, "black")
        new_insert = tree.find_node(2)
        self.assertEqual(new_insert.color, "red")
        new_insert = tree.find_node(5)
        self.assertEqual(new_insert.color, "black")

if __name__ == "__main__":
    unittest.main()
