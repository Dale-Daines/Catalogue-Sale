//Dale Daines - 16998416 - Assignment 2 - Catagory
#include <string>
#ifndef CATEGORY_H_
#define CATEGORY_H_
using namespace std;
static int keyCount = 100;

class Category {
protected:
	string name;
	int key;
public:
	bool item;
	Category();
	Category(string);
	virtual ~Category();
	virtual void print(int);
	virtual bool offer(double, double&);
	virtual void modify();
	void setName(string);
	string retName();
	int retKey();
};

Category::Category() {
	key = keyCount++;
	name = "";
	item = false;
}

Category::Category(string newName) {
	key = keyCount++;
	name = newName;
	item = false;
}

Category::~Category() {

}

void Category::setName(string newName) {
	name = newName;
}

string Category::retName() {
	return name;
}

int Category::retKey() {
	return key;
}

//Prints the category details
void Category::print(int user) {
	cout 	<< "CategoryID: " << key << endl
			<< "Name: " << name << endl;
}

//used to allow Item to accept offers using virtual implementation. Should an offer be made for a category will return false
bool Category::offer(double, double&) {
	return false;
}

//Menu to modify category name
void Category::modify() {
	cout << "CategoryKey: " << key << endl;
	cout << "CategoryName: " << name << endl;
	cout << "Please insert new Category name:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Category modified." << endl << endl;
}

#endif /* CATEGORY_H_ */
