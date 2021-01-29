#include <iostream>
#include <stack>
#include "Catalogue.h"
using namespace std;

class Store {
	Catalogue Catalogue;
private:
	void userPrint(int, int);
public:
	Store();
	void userType();
	void traverse(int);
	void newCategory(binaryTreeNode<Category*>*, bool);
	void newItem(binaryTreeNode<Category*>*, bool);
	void modMenu(binaryTreeNode<Category*>*);
	int itemMenu(binaryTreeNode<Category*>*, int);
	bool itemBuy(binaryTreeNode<Category*>*);
	void deleteObject(binaryTreeNode<Category*>*);
};

Store::Store() {
	userType();
}

//Menu to select type of user
void Store::userType() {
	int user;
	cout << "What kind of user are you?" << endl;
	cout << "1: Buyer" << endl << "2: Seller" << endl << "3: Moderator" << endl << "4: Quit" << endl << endl;
	cin >> user;
	if ( user < 1 || user > 4 )
		userType();
	else if ( user != 4 )
		traverse(user-1);
}

//Menus specific to user type
void Store::userPrint(int user, int count) {
	if ( user == 0 ) {
		cout << count++ << ": Quit to menu" <<  endl << endl;
	}
	if ( user == 1 ) {
		cout << count++ << ": Add a Category" << endl;
		cout << count++ << ": Sell an Item" << endl;
		cout << count++ << ": Quit to menu" <<  endl << endl;
	}
	if ( user == 2 ) {
		cout << count++ << ": Add a Category" << endl;
		cout << count++ << ": Add an Item" << endl;
		cout << count++ << ": Modify an Item/Category" << endl;
		cout << count++ << ": Delete an Item/Category" << endl;
		cout << count++ << ": Quit to menu" <<  endl << endl;
	}
}

//Menu to traverse and effect the tree
void Store::traverse(int user = 0) {
	int input = 0;
	stack<binaryTreeNode<Category*>*> prevNode;
	binaryTreeNode<Category*>* node = Catalogue.retRoot(), *test;
	while ( input > -1 ) {
		int count = 0;
		//if the node is an item
		if ( node != NULL && node->info->item ) {
			input = itemMenu(node, user);

			if ( input == 0 ) {
				if ( !prevNode.empty() ) {
					node = prevNode.top();
					prevNode.pop();
				}
				else
					node = Catalogue.retRoot();
			}

			if ( input == 1) {
				if ( user == 0 ){
					if ( itemBuy(node) )
						Catalogue.deleteSearch(prevNode.top(), node);
					node = prevNode.top();
					prevNode.pop();
				}
				else {
					Catalogue.modification(node);
				}
			}

			if ( input == 2 ) {
				Catalogue.deleteSearch(prevNode.top(), node);
				node = prevNode.top();
				prevNode.pop();
			}

		}
		//otherwise run catalogue menu
		else {
			//Print correct menu
			if ( node == Catalogue.retRoot() ) {
				prevNode.push(node);
				node = node->llink;
			}
			if ( node == Catalogue.retRoot()->llink ) {
				count = Catalogue.printLevel(node);
				userPrint(user, count);
			}
			else {
				count = Catalogue.printLevel(node, true);
				userPrint(user, count);
			}

			cin >> input;
			//if Go back is selected
			if (input == 0 ) {

				//Handle go back
				if ( !prevNode.empty() ) {
					node = prevNode.top();
					prevNode.pop();
				}
				else
					node = Catalogue.retRoot();
			}

			//if an item/category is selected
			if ( input > 0 && input < count ) {
				prevNode.push(node);
				test = Catalogue.selectNode(node, input);
				if ( test->info->item )
					node = test;
				else
					node = test->llink;
			}

			//If Quit option selected
			if ( (input == count && user == 0) || (input == count + 2 && user == 1) || (input == count + 4 && user == 2) ) {
				userType();
				break;
			}

			//If Create a category is selected
			if ( input == count && user > 0 ) {
				if ( node == NULL ) {
					newCategory(test, true);
					node = test->llink;
				}
				else
					newCategory(node, false);
			}

			//if Create an item is selected
			if ( input == count + 1 && user > 0 ) {
				if ( node == NULL ) {
					newItem(test, true);
					node = test->llink;
				}
				else
					newItem(node, false);
			}

			if ( input == count + 2 && user == 2) {
				modMenu(node);
			}

			//if Delete an category/item is selected
			if ( input == count + 3 && user == 2) {
				deleteObject(node);
				node = prevNode.top();
				prevNode.pop();
			}
		}
	}
}

//Menu for when an item is selected
int Store::itemMenu(binaryTreeNode<Category*> *node, int user) {
	int input;
	bool goodInput = false;
	node->info->print(user);

	cout << endl << "0: Go back" << endl;
	if ( user == 0 )
		cout << "1: Make an offer" << endl;
	if ( user == 2 )
		cout << "1: Modify item" << endl
			<<	"2: Delete item" << endl;
	while ( !goodInput ) {
		cin >> input;
		if ( user == 0 && ( input == 0 || input == 1 ))
			goodInput = true;
		if ( user == 1 && input == 0 )
			goodInput = true;
		if ( user == 2 && ( input >= 0 && input <=2))
			goodInput = true;
	}
	return input;
}

//Menu for buying an item
bool Store::itemBuy(binaryTreeNode<Category*> *node) {
	double pay = 0, cost = 0;
	cout << "How much are you willing to offer?" << endl;
	cin >> pay;
	if ( node->info->offer(pay, cost) ) {
		cout << "Your offer has been accepted, please pay $" << cost << "." <<  endl << endl;
		return true;
	}
	cout << "Your offer has been rejected." <<  endl << endl;
	return false;
}

void Store::newItem(binaryTreeNode<Category*> *node, bool child = false) {
	string name, description;
	double price, maxDiscount;
	cout << "Please insert Item name:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Please insert Item price:" << endl;
	cin >> price;
	cout << "Please insert Item description:" << endl;
	cin.ignore();
	getline(cin, description);
	cout << "Please insert maximum Item discount as a %:" << endl;
	cin >> maxDiscount;
	Item *newItem = new Item;
	newItem->setName(name);
	newItem->setPrice(price);
	newItem->setDescription(description);
	newItem->setMaxDiscount(maxDiscount);
	if ( child ) {
		Catalogue.insertChild(node, newItem);
	}
	else {
		Catalogue.insert(node, newItem);
	}
	cout << "Item Added." <<  endl << endl;
}

//Menu for creating a new category
void Store::newCategory(binaryTreeNode<Category*> *node, bool child = false) {
	string name;
	cout << "Please insert Category name:" << endl;
	cin.ignore();
	getline(cin, name);
	Category *newCat = new Category(name);
	if ( child )
		Catalogue.insertChild(node, newCat);
	else
		Catalogue.insert(node, newCat);
	cout << "Category Added." <<  endl << endl;
}

//menu for modifying an object
void Store::modMenu(binaryTreeNode<Category*> *node) {
	int selection, count;
	cout << "Which Item/Category would you like to modify?" << endl;
	count = Catalogue.printLevel(node);
	cin >> selection;
	if ( selection > 0 && selection <= count ) {
		Catalogue.modification(Catalogue.selectNode(node, selection));
	}
	else
	{
		cout << "Error: No valid option selected. Exiting to menu" <<  endl << endl;
	}
}

//menu for deleting an object
void Store::deleteObject(binaryTreeNode<Category*> *node) {
	int selection, count;
	cout << "Which Item/Category would you like to delete?" << endl;
	count = Catalogue.printLevel(node);
	cin >> selection;
	if ( selection > 0 && selection <= count ) {
		binaryTreeNode<Category*> *test;
		test = Catalogue.selectNode(node, selection);
		Catalogue.deleteSearch(Catalogue.retRoot(), test);
		cout << "Item/Category deleted." <<  endl << endl;
	}
	else
	{
		cout << "Error: No valid option selected. Exiting to menu" <<  endl << endl;
	}

}


int main() {
	Store Store;


	return 0;
}
