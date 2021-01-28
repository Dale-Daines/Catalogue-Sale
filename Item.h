//Dale Daines - 16998416 - Assignment 2 - Item
#include <string>
#include "Category.h"
#ifndef ITEM_H_
#define ITEM_H_
using namespace std;

class Item : public Category {
private:
	string description;
	double price, maxDiscount;
public:
	Item();
	void setDescription(string);
	void setPrice(double);
	void setMaxDiscount(double);
	string retDescription();
	double retPrice();
	double retMaxDiscount();
	virtual void print(int);
	virtual bool offer(double, double&);
	virtual void modify();
};

Item::Item() {
	key = keyCount++;
	keyCount++;
	item = true;
	name = "";
	description = "";
	price = 0;
	maxDiscount = 0;
}

void Item::setDescription(string desc) {
	description = desc;
}

void Item::setPrice(double pri) {
	price = pri;
}

void Item::setMaxDiscount(double discount) {
	maxDiscount = discount/100;
}

string Item::retDescription() {
	return description;
}

//Prints the details of the item
void Item::print(int user) {
	cout 	<< "ItemID:		" << key << endl
			<< "Name:		" << name << endl
			<< "Description:	" << description << endl
			<< "Price:		" << price << endl;
	if ( user == 2 ) {
		cout << "maxDiscount:	" << maxDiscount*100 << "%" << endl;
	}
}

//returns whether an offer is accepted and at what price
bool Item::offer(double pay, double &cost) {
	if ( pay >= ( price *( 1 - maxDiscount ) ) ) {
		if ( price < pay )
			cost = price;
		else
			cost = pay;
		return true;
	}

	if ( pay < ( price * ( 1 - maxDiscount ) ) ) {
		return false;
	}

	return false;
}

double Item::retPrice() {
	return price;
}

double Item::retMaxDiscount() {
	return maxDiscount;
}

//allows the modification of the item
void Item::modify() {
	cout << "ItemKey: " << key << endl;
	cout << "ItemName: " << name << endl;
	cout << "Please insert new Item name:" << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Price: " << price << endl;
	cout << "Please insert new Item price:" << endl;
	cin >> price;
	cout << "Description: " << description << endl;
	cout << "Please insert new Item description:" << endl;
	cin.ignore();
	getline(cin, description);
	cout << "Discount: " << maxDiscount*100 << "%" << endl;
	cout << "Please insert new maximum Item discount as a %:" << endl;
	cin >> maxDiscount;
	maxDiscount = maxDiscount/100;
	cout << "Item modified." <<  endl << endl;
}

#endif /* ITEM_H_ */
