#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
	int key = 0;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}
// Constructor
Node::Node(int in) {
	key = in;
	parent = nullptr;
	left = nullptr;
	right = nullptr;

}
// Destructor
Node::~Node() {
// TODO: Implement this
}

// Add parent 
void Node::add_parent(Node* in) {
	parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
	left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
	 right = in;
}

// Get key
int Node::get_key()
{
	int key = this->key;
	return key;
}
// Get parent node
Node* Node::get_parent()
{
	return  parent;
}
// Get left node
Node* Node::get_left()
{
	return left;
// TODO: Implement this
}
// Get right node
Node* Node::get_right()
{
	 return right;
// TODO: Implement this
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
//from slides
	if (in != nullptr) {
		inorder_walk(in->get_left(),to);
		in->print_info(to);
		inorder_walk(in->get_right(),to);
	}

}
// Constructor
BST::BST()
{
	root = nullptr;
}
// Destructor
BST::~BST()
{
	while (root != nullptr) {
		delete_node(root);
	}
// TODO: Implement this
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
	Node *x = root;
	Node *y = nullptr;
	while (x != nullptr) {
		y = x;
		if (in->get_key() < x->get_key()) {
			x = x->get_left();
		}
		else {
			x = x->get_right();
		}
	}
	in->add_parent(y);
	if (y == nullptr) {
		root = in;
	}
	else if (in->get_key() < y->get_key()) {
		y->add_left(in);
	}
	else {
		y->add_right(in);
		

}
}
// Delete a node to the subtree

void BST::delete_node(Node* out)
{ //taken from CRSL book
	if (out->get_left() == nullptr) {
		transplant(out, out->get_right());
	}
	else if (out->get_right() == nullptr) {
		transplant(out, out->get_left());
	}
	else {
		Node *y = get_min(out->get_right());
		if (y->get_parent() != out) {
			transplant(y,y->get_right());
			y->add_right(out->get_right());
			y->get_right()->add_parent(y);
		}
		transplant(out,y);
		y->add_left(out->get_left());
		y->get_left()->add_parent(y);
	}
}
// minimum key in the BST
Node* BST::tree_min()
{
	Node *temp = root;
	while (temp->get_left() != nullptr) {
		temp = temp->get_left(); 
	}
	return temp;


}
// maximum key in the BST
Node* BST::tree_max()
{
	Node *temp = root;
	while (temp->get_right() != nullptr) {
		temp = temp->get_right();
	}
	return temp;

// TODO: Implement this
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	Node *curr = in;
	while (curr->get_left() != nullptr) {
		curr = curr->get_left();
	}
	return curr;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{ //copied from lecture slides
	Node *curr = in;
	while (curr->get_right() != nullptr) {
		curr= curr->get_right();
	}
	return curr;
// TODO: Implement this
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{ //copy from lecture slides
	Node *now = in;
	if (now->get_right() != nullptr) {
		return get_min(now->get_right());
	}
	Node *y = in->get_parent();
	while (y != nullptr and now == y->get_right()) {
		now = y;
		y = y->get_parent();
	}
	return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	Node *now = in;
	if (now->get_left() != nullptr) {
		return get_max(now->get_left());
	}
	Node *y = in->get_parent();
	while (y != nullptr and now == y->get_left()) {
		now = y;
		y = y->get_parent();
	}
	return y;
	
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
	inorder_walk(root,to);

// TODO: Implement this
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	Node *temp = root;
	while (temp != nullptr and search_key != temp->get_key()) {
		if (search_key < temp->get_key()) {
			temp = temp->get_left();
		}
		else {
			temp = temp->get_right();
		}
	}
	return temp;
// TODO: Implement this
}
Node * BST::transplant(Node *in, Node *out) {
//transplant function using CSRL book
	if (in->get_parent() == nullptr) {
		root = out;
	}
	else if (in == in->get_parent()->get_left()) {
		in->get_parent()->add_left(out);
	}
	else {
		in->get_parent()->add_right(out);
	}
	if (out != nullptr) {
		out->add_parent(in->get_parent());
	}
}

// ---------------------------------------
