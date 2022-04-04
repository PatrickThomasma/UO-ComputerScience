class Node(object):
    def __init__(self, data):
        self.parent = None
        self.left = None
        self.right = None
        self.data = data


class Tree(object):
    # Binary Search Tree
    # class constants
    PREORDER = 1
    INORDER = 2
    POSTORDER = 3

    def __init__(self):
        # Do not create any other private variables.
        # You may create more helper methods as needed.
        self.root = None

    def print(self):
        # Print the data of all nodes in order
        self.__print(self.root)


    def __print(self, curr_node):
        # Recursively print a subtree (in order), rooted at curr_node
        if curr_node is not None:
            self.__print(curr_node.left)
            print(str(curr_node.data), end=' ')  # save space
            self.__print(curr_node.right)
            

    def insert(self, data):
        # Find the right spot in the tree for the new node
        # Make sure to check if anything is in the tree
        # Hint: if a node n is null, calling n.getData() will cause an error
        if self.root is None:
            self.root = Node(data)
        else:
            current = self.root
            while True:
                if current.data > data:
                    if current.left == None:
                        current.left = Node(data)
                        current.left.parent = current
                    else:
                        current = current.left
                elif current.data < data:
                    if current.right == None:
                        current.right = Node(data)
                        current.right.parent = current
                        break
                    else:
                        current = current.right
                else:
                    break

    def min(self):
        # Returns the minimum value held in the tree
        # Returns None if the tree is empty
        current = self.root
        if current is None:
            return None
        while True:
            if current.left == None:
                return current.data
            else:
                current = current.left

    def max(self):
        # Returns the maximum value held in the tree
        # Returns None if the tree is empty
        current = self.root
        if current is None:
            return None
        while True:
            if (current.right == None):
                return current.data
            else:
                current = current.right


    def __find_node(self, data):
        # returns the node with that particular data value else returns None
        current = self.root
        if current is None:
            return None
        while current is not None:
            if (data > current.data):
                current = current.right
            elif (data < current.data):
                current = current.left
            elif (data == current.data):
                return current
        return None

    def contains(self, data):
        # return True of node containing data is present in the tree.
        # otherwise, return False.
        # you may use a helper method __find_node() to find a particular node with the data value and return that node
        current = self.__find_node(data)
        if current is None:
            return False
        else:
            return True

    def __iter__(self):
        # iterate over the nodes with inorder traversal using a for loop
        return self.inorder()

    def inorder(self):
        # inorder traversal : (LEFT, ROOT, RIGHT)
        return self.__traverse(self.root, Tree.INORDER)

    def preorder(self):
        # preorder traversal : (ROOT, LEFT, RIGHT)
        return self.__traverse(self.root, Tree.PREORDER)

    def postorder(self):
        # postorder traversal : (LEFT, RIGHT, ROOT)
        return self.__traverse(self.root, Tree.POSTORDER)

    def __traverse(self, curr_node, traversal_type):
        # helper method implemented using generators
        # all the traversals can be implemented using a single method
        
        #Yield data of the correct node/s
        if self.root is None:
            return None
        current = self.root
        stack = []
        tree = []
        stack.append(current)
        if (traversal_type == 2):
            while len(stack) > 0:
                if current.left:
                    stack.append(current.left)
                    current = current.left
                else:
                    current = stack.pop()
                    tree.append(current.data)

                    if current.right:
                        stack.append(current.right)
                        current = current.right
            res = []
            for i in tree:
                if i not in res:
                    res.append(i)
            if len(res) > 0:
                return iter(res)
            else:
                return None
        elif (traversal_type == 1):
            while len(stack):
                current = stack.pop()
                tree.append(current.data)
                if current.right is not None:
                    stack.append(current.right)
                if current.left is not None:
                    stack.append(current.left)
            if len(tree) > 0:
                return iter(tree)
            else:
                return None
        elif (traversal_type == 3):
            if self.root is None:
                return
            while True:
                while(current):
                    if current.right is not None:
                        stack.append(current.right)
                    stack.append(current)

                    current = current.left
                current = stack.pop()

                if (current.right is not None and self.peek(stack) == current.right):
                    stack.pop()
                    stack.append(current)
                    current = current.right
                else:
                    tree.append(current.data)
                    current = None
                if (len(stack) <= 0):
                    break
            res = []
            for i in tree:
                if i not in res:
                    res.append(i)
            if len(res) > 0:
                return iter(res)
            else:
                return None


    def peek(self,stack):
        if len(stack) > 0:
            return stack[-1]
        return None

    def find_successor(self, data):
        # helper method to implement the delete method but may be called on its own
        # if the right subtree of the node is nonempty,then the successor is just 
        # the leftmost node in the right subtree.
        # If the right subtree of the node is empty,then go up the tree until a node that is
        # the left child of its parent is encountered. The parent of the found node will be the
        #successor to the initial node.
    
    	#Return object of successor if found else return None
        current = self.__find_node(data)
        if current is None:
            return None
        if current.right is not None:
            baby = current.right
            while baby.left is not None:
                baby = baby.left
            return baby
        parent = current.parent
        while (parent is not None) and (current == parent.right):
            current = parent
            parent = current.parent
        return parent

    def delete(self, data):
        # Find the node to delete.
        # If the value specified by delete does not exist in the tree, then don't change the tree and raise a KeyError
        # If you find the node and ...
        #  a) The node has no children, just set it's parent's pointer to Null.
        #  b) The node has one child, make the nodes parent point to its child.
        #  c) The node has two children, replace it with its successor, and remove
        #       successor from its previous location.
        # Recall: The successor of a node is the left-most node in the node's right subtree.
    
        if self.root == None:
            return None
        else:
            parent = None
            current = self.root
            replace_node = None
            while (current != None and current.data != data):
                parent = current
                if data >= current.data:
                    current = current.right
                    flag = 1
                else:
                    current = current.left
                    flag = 0
            if current is None:
                raise KeyError
            else:
                if (current.left == None) and (current.right == None):
                    if (flag):
                        parent.right = None
                    else:
                        parent.left = None
                    del current
                elif (current.left == None) or (current.right == None):
                    if current.left == None:
                        if (flag):
                            parent.right = current.right
                        else:
                            parent.left = current.left
                    else:
                        if (flag):
                            parent.right = current.left
                        else:
                            parent.left = current.left

                    del current

                else:
                    replace_node = self.minimum_element(current.right)
                    temp = replace_node.data
                    self.delete(replace_node.data)
                    current.data = temp

    def minimum_element(self,data):
        if self.root == None:
            raise KeyError
        else:
            while (data.left != None):
                data = data.left
            return (data)
    
