/**
 * ListADT: Linked List Implementation
 */
#ifndef _LISTADT
#define _LISTADT

#include "ListInterface.h"
#include "Node.h"
#include <stdexcept>
#include <cassert>
#include <vector>
#include <sstream>


template<class ItemType>
class ListADT: public ListInterface<ItemType>
{
private:
	int itemCount = 0;

    Node<ListElement>* item;

	Node<ItemType>* headPtr;

	Node<ItemType>* curPtr = headPtr;

	/** Gets the Node at the given position.
    @param position The position of the Node that wants to be located.
    @throw logic_error if position <= 1 or position >= itemCount.
    @return The Node at the given position.
    */
    Node<ItemType>* getNodeAt(int position) const throw(logic_error);

	/** Gets the pointer of the Node that contains the target.
    @param target The Node item that wants to be located.
    @throw logic_error if the target does not exist.
    @return The pointer to the Node containing the target.
    */
    Node<ItemType>* getPointerTo(const ItemType& target) const throw(logic_error);

    /** Goes through the list to find the next Node with that country code using compare
    @param target The country code from the new struct to be inserted in the List.
    @return Position of the first Node with the same country. If there is no Node with the same
            country code getPosByCountryCode() will return 1.
    */
    int getPosByCountryCode(string target) const;

    /**Sets the elements in the struct ListElement to the items from the file
    @param string vector containing the child information from the file.
    @return The new struct to be inserted.
    */
    Node<ListElement>* setStructItem(vector<ItemType> str) const;

    /** Splits a single string into a vector of strings.
    @param str The string that will be split.
    @param delimiter The character that will be the splitting point.
    @return A vector of the strings that were obtained by splitting str at the delimiter.
    */
    vector <ItemType> stringSplit(string str, char delimiter) const;

	/** Makes the list contents into a vector.
    @return A vector containing the list contents.
    */
    vector<ItemType> toVector() const;

public:
	// Must have at least these based on Interface
	ListADT();

	~ ListADT();

	bool isEmpty() const;

	int getLength() const;

    //@throw logic_error if newPosition <= 1 or newPosition >= itemCount + 1.
	bool insert(int newPosition, const ItemType& newEntry) throw(logic_error);

    //@throw logic_error if position <= 1 or position >= itemCount.
	bool remove(int position) throw(logic_error);

	void clear();

	//@throw logic_error if position <= 1 or position >= itemCount.
	Node<ItemType>* getEntry(int position) const throw(logic_error);

	//@throw logic_error if position <= 1 or position >= itemCount.
	void setEntry(int position, const ItemType& newEntry) throw(logic_error);

	//@throw logic_error if either positionA or positionB <= 1 or positionA or positionB >= itemCount.
	bool swap(int positionA, int positionB) throw(logic_error);

	void reverse();

	//@throw logic_error if position <= 1 or position >= itemCount.
	bool replace(int position, const ItemType& newEntry) throw(logic_error);

	//@throw logic_error if the list is empty or entry is not in the list.
	int getPosition(const ItemType& entry) throw(logic_error);

	bool contains(const ItemType& entry);

    //@throw logic_error if the filename cannot be opened.
	bool loadList(const string filename) throw(logic_error);

	void displayList();
};

#include "ListADT.cpp"
#endif



