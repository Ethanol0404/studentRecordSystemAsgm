#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::deepestNodes() {
	BTNode* cur;
	Queue current, next, statistic;
	int lvl = 0;
	int memory[100]; //count element by lvl, assume the tree have 100 lvl

	if (empty()) {
		return false;
	}
	current.enqueue(root);

	do {
		memory[lvl] = 0; //initialise the memory value when enter new lvl
		while (!current.empty()) {
			current.dequeue(cur);
			if (cur != NULL) {
				statistic.enqueue(cur); //enqueue as make statistic regardless different lvl
				memory[lvl]++; // record memory by lvl
				if (cur->left != NULL) {
					next.enqueue(cur->left); //enqueue in next level
				}

				if (cur->right != NULL) {
					next.enqueue(cur->right);
				}
			}
		}
		while (!next.empty()) { //next level move to current level
			next.dequeue(cur);
			current.enqueue(cur);
		}
		lvl++;
	} while (!current.empty());

	cout << "\nStudent ID in deepest nodes: ";
	for (int i = 0; i < lvl - 1; i++) { //loop by lvl but excluding last lvl
		for (int j = 0; j < memory[i]; j++) { //dequeue memory by lvl 
			statistic.dequeue(cur);
		}
	}
	while (!statistic.empty()) { //output last level
		statistic.dequeue(cur);
		cout << cur->item.id << " ";
	}
	cout << "\n";
	return true;
}

void BST::ascendPrintF(ostream& out) {//descending (inversed) inOrder Print
	if (root == NULL) return;// handle special case
	else ascendPrintF2(root, out);// do normal process
	cout << endl;
}

void BST::ascendPrintF2(BTNode* cur, ostream& out) {

	if (cur == NULL) return;

	ascendPrintF2(cur->left, out);
	cur->item.print(out);
	ascendPrintF2(cur->right, out);
}

void BST::descendPrint() {//descending (inversed) inOrder Print
	if (root == NULL) return;// handle special case
	else descendPrint2(root);// do normal process
	cout << endl;
}


void BST::descendPrint2(BTNode* cur) {

	if (cur == NULL) return;

	descendPrint2(cur->right);
	cur->item.print(cout);
	descendPrint2(cur->left);
}

void BST::descendPrintF(ostream& out) {//descending (inversed) inOrder Print
	if (root == NULL) return;// handle special case
	else descendPrintF2(root, out);// do normal process
	cout << endl;
}


void BST::descendPrintF2(BTNode* cur, ostream& out) {

	if (cur == NULL) return;

	descendPrintF2(cur->right, out);
	cur->item.print(out);
	descendPrintF2(cur->left, out);
}

bool BST::display(int order, int source) {
	ofstream out("student-info.txt");

	if (root == NULL) {
		return false;
	}
	if (order == 1) {
		if (source == 1) {
			inOrderPrint();
			cout << "All student records displayed successfully in ascending order.\n\n";
			return true;
		}
		else {
			ascendPrintF(out);
			cout << "All student records displayed successfully in ascending order. Please check file (student-info.txt).\n\n";
			return true;
		}

	}
	else {
		if (source == 1) {
			descendPrint();
			cout << "All student records displayed successfully in descending order.\n\n";
			return true;
		}
		else {
			descendPrintF(out);
			cout << "All student records displayed successfully in descending order. Please check file (student-info.txt).\n\n";
			return true;
		}

	}
}

bool BST::printLevelNodes() {
	if (root == NULL) {
		return false;
	}
	else {
		Student stu;
		int lvl = 1;
		BTNode* cur = root;
		BTNode* temp;
		Queue q1, q2;

		q1.enqueue(root);	// Step 1: enqueue the first node
		do {

			cout << "\nLevel " << lvl << " nodes: ";
			while (!q1.empty()) { 	// Step 2: do 2 operations inside
				q1.dequeue(cur);
				if (cur != NULL) {
					cout << cur->item.id << " ";

					if (cur->left != NULL) //enqueue nodes of the next level to q2
						q2.enqueue(cur->left);

					if (cur->right != NULL)
						q2.enqueue(cur->right);
				}
			}
			while (!q2.empty()) {//move content in q2 to q1
				q2.dequeue(temp);
				q1.enqueue(temp);
			}
			lvl++;
		} while (!q1.empty());
		return true;
	}
}

bool BST::CloneSubtree(BST t1, type item) {
	BST t2; //subtree to be clone
	BTNode* cur;
	Queue q, q1;

	root = NULL; //clear tree structure when call again this function

	if (t1.empty()) {
		cout << "The tree is empty. Please insert student record first.\n\n";
		return false;
	}

	q.enqueue(t1.root); //arrange tree into queue

	while (!q.empty()) {

		q.dequeue(cur);
		if (cur->item.id != item.id) { //search the tree to match the id that inputed
			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);

			if (q.empty()) { //cannot find student id
				cout << "Student ID not found. Cannot clone subtree.\n\n";
				return false;
			}
		}
		else { //student id is found, arrange this node and its offspring in original tree into queue
			do {
				if (!q1.empty()) { //make sure start working in second loop
					q1.dequeue(cur);
				}
				//insert subtree first in first loop
				insert(cur->item); //dequeue then insert as sub tree
				if (cur->left != NULL) {
					q1.enqueue(cur->left);
				}

				if (cur->right != NULL) {
					q1.enqueue(cur->right);
				}
			} while (!q1.empty());

			//output if subtree insert successfully
			cout << "Clone sub tree successfully.\n\n";
			for (int i = 0; i < 71; i++) {
				cout << "=";
			}
			cout << "\n\nThe t2 subtree from t1\n\n";
			for (int i = 0; i < 71; i++) {
				cout << "=";
			}
			preOrderPrint();
			return true;
		}
	}
}


void BST::findPath(BTNode* cur, Queue& pathRecord) {
	if (cur == NULL) {
		return;
	}
	pathRecord.enqueue(cur);
	if (cur->left == NULL && cur->right == NULL) { //leaf node found
		Queue print;
		BTNode* temp;
		while (!pathRecord.empty()) {
			pathRecord.dequeue(temp); //replace to another queue and output
			print.enqueue(temp);
			cout << temp->item.id << " ";
		}
		cout << endl;

		while (!print.empty()) { //restore to original
			print.dequeue(temp);
			pathRecord.enqueue(temp);
		}
	}
	else {
		findPath(cur->left, pathRecord);
		findPath(cur->right, pathRecord);
	}
	// after leaf node found, proceed reverse queue to remove the last-in element 
	pathRecord.reverseQueue(pathRecord);
	pathRecord.dequeue(cur);
	pathRecord.reverseQueue(pathRecord); //restore the queue 
}

bool BST::printPath() {
	if (empty()) {
		return false;
	}
	Queue pathRecord;
	cout << "\nBelow are all the external paths for the tree: \n\n";
	findPath(root, pathRecord); //start finding path from the root

	return true;
}