#include "Item.h"
#include "Category.h"
#include "binaryTree.h"
#include <string>
#ifndef CATALOGUE_H_
#define CATALOGUE_H_
using namespace std;

class Catalogue : public binaryTreeType<Category*> {
private:
	string strings[17] = {"Computers & Tablets", "Health, fitness & wearables", "Mobile Phones",
				"Cameras", "Desktops", "Tablets", "Laptops", "Sports Watches",
				"Smart Watches", "Wearable", "iPhones", "Android Phones", "Lenovo",
				"HP", "Dell", "Apple watches", "Samsung watches"};
	void demoCatalogue();
	void deleteEntries(binaryTreeNode<Category*>* &);
public:
	Catalogue();
	~Catalogue();
	binaryTreeNode<Category*>* retRoot();
	void insert(binaryTreeNode<Category*>*, Category*);
	void insertChild(binaryTreeNode<Category*>*, Category*);
	int printLevel(binaryTreeNode<Category*>*, bool);
	void modification(binaryTreeNode<Category*>*);
	binaryTreeNode<Category*>* newNode(Category* data);
	binaryTreeNode<Category*>* selectNode(binaryTreeNode<Category*>*, int);
	bool deleteSearch(binaryTreeNode<Category*>*, binaryTreeNode<Category*>*);
	void removeNode(binaryTreeNode<Category*>*, binaryTreeNode<Category*>*);
};

Catalogue::Catalogue() {
	demoCatalogue();
}

Catalogue::~Catalogue() {
	binaryTreeNode<Category*>* node = retRoot();
	deleteEntries(node);
}

//delete the dynamic memory for each category and item linked to this node
void Catalogue::deleteEntries(binaryTreeNode<Category*>* &node) {
	if (node != NULL) {
		deleteEntries(node->llink);
		deleteEntries(node->rlink);
	    delete node->info;
	    node->info = NULL;
	}
}

//Create the starter catalogue
void Catalogue::demoCatalogue() {
	Category *cat = new Category("Root");
	root = newNode(cat);
	for (int i = 0; i < 17; i++) {
		Category *newCat = new Category(strings[i]);
		if ( i < 3 ) {
			insertChild(root, newCat);
		}
		else if ( i < 6 ) {
			insertChild(root->llink, newCat);
		}
		else if ( i < 9 ) {
			insertChild(root->llink->rlink, newCat);
		}
		else if ( i < 12 ) {
			insertChild(root->llink->rlink->rlink, newCat);
		}
		else if ( i < 14 ) {
			insertChild(root->llink->llink, newCat);
		}
		else {
			insertChild(root->llink->rlink->llink->rlink, newCat);
		}
	}
	Item *item = new Item();
	item->setName("TestItem");
	item->setPrice(20.0);
	item->setDescription("Best Test item");
	item->setMaxDiscount(20.0);
	insertChild(root, item);
}

//Insert a new item as a sibling
void Catalogue::insert(binaryTreeNode<Category*>* node, Category* item) {
	if (node->rlink != NULL ) {
		insert(node->rlink, item);
	}
	else {
		node->rlink = newNode(item);
	}
}

//Insert a new item as a child
void Catalogue::insertChild(binaryTreeNode<Category*>* node, Category* item) {
	if (node->llink == NULL ) {
		node->llink = newNode(item);
	}
	else {
		insert(node->llink, item);
	}
}

//remove a node and link everything back together correctly
//Move children into position with siblings
void Catalogue::removeNode(binaryTreeNode<Category*>* node, binaryTreeNode<Category*>* prevNode) {
	bool left = false;
	if ( prevNode->llink == node ) {
		prevNode->llink = node->rlink;
		left = true;
	}
	if ( prevNode->rlink == node ) {
		prevNode->rlink = node->rlink;
	}
	if ( node->llink != NULL ) {
		binaryTreeNode<Category*>* temp = prevNode;
		if ( left == true && prevNode->llink == NULL )
			prevNode->llink = node->llink;
		else {
			if ( left )
				temp = temp->llink;
			while ( temp->rlink != NULL)
				temp = temp->rlink;
			temp->rlink = node->llink;
		}
	}

	node->rlink = NULL;
	node->llink = NULL;
	deleteEntries(node);
	delete node;
	node = NULL;
}

binaryTreeNode<Category*>* Catalogue::retRoot() {
	return root;
}

//Print all items on the same level as the node
int Catalogue::printLevel(binaryTreeNode<Category*>* node, bool back = false) {
	int count = 1;
	if ( back ) {
		cout << "0: Go back" << endl;
	}
	binaryTreeNode<Category*>* point = node;
	while ( point != NULL ) {
		cout << count++ << ": " << point->info->retName() << endl;
		point = point->rlink;
	}
	return count;
}

//return the node selected by the Store menu
binaryTreeNode<Category*>* Catalogue::selectNode(binaryTreeNode<Category*>* node, int selection) {
	for ( int i = 0; i < selection-1; i++ ) {
		if ( node != NULL )
			node = node->rlink;
		else {
			return retRoot();
		}
	}
	return node;
}

//find the node before a target node to be deleted. then delete the target node
bool Catalogue::deleteSearch(binaryTreeNode<Category*>* node, binaryTreeNode<Category*>* searchNode) {
	if ( node != NULL ) {
		if ( node->rlink == searchNode ) {
			removeNode(searchNode, node);
			return true;
		}
		if ( node->llink == searchNode ) {
			removeNode(searchNode, node);
			return true;
		}
		if ( deleteSearch(node->rlink, searchNode) )
			return true;
		if ( deleteSearch(node->llink, searchNode) )
			return true;
	}
	return false;
}

//Modify the object within a node
void Catalogue::modification(binaryTreeNode<Category*> *node) {
	node->info->modify();
	cout << "Item modified";
}

//Create a new node with an object inside
binaryTreeNode<Category*>* Catalogue::newNode(Category* data) {
	binaryTreeNode<Category*>* node;
	node = new binaryTreeNode<Category*>;
	node->info = data;
	node->rlink = NULL;
	node->llink = NULL;
	return node;
}

//new item/category - go right till null, add item/category to that link
//Produce Category - Print all right object names with numbers to select
//When selected, print all children and repeat
//IF item selected print item details other than max discount (Unless Manager)



#endif /* CATALOGUE_H_ */
