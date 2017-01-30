/**
 * Implementation
 */
#ifndef _LISTADTIMP
#define _LISTADTIMP

#include "ListADT.h"
#include "ListElement.h"

template<class ItemType>
ListADT<ItemType>::ListADT() : headPtr(NULL), itemCount(0)
{}

template<class ItemType>
ListADT<ItemType>::~ListADT()
{
	clear();
}

template<class ItemType>
bool ListADT<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
int ListADT<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool ListADT<ItemType>::insert(int newPosition, const ItemType& newEntry) throw(logic_error)
{
	//Precondition check
	bool ableToInsert = (newPosition >= 1) &&
						(newPosition <= itemCount + 1);
	//Create pointer to new node & insert
	if (ableToInsert){

		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

		if (newPosition == 1){
			//Puts newEntry on the front of the list.
			newNodePtr -> setNext(headPtr);
			headPtr = newNodePtr;
		}
        //sort by postalCode somehow
		else{
			//Finds the Node before the newPosition to add newEntry after it.
			Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
			newNodePtr -> setNext(prevPtr -> getNext());
			prevPtr -> setNext(newNodePtr);
		}//end if

		itemCount++;
	}
    else{
        throw logic_error("The position is invalid.");
    }//end if

	return ableToInsert;
}//end insert

template<class ItemType>
bool ListADT<ItemType>::remove(int position) throw(logic_error)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if(ableToRemove)
	{
		curPtr = NULL;

		//Sets curPtr to point at the first Node in the list.
		if(position == 1)
		{
			curPtr = headPtr;
			headPtr = headPtr->getNext();
		}else{
			//Finds the Node before the position to remove.
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			curPtr = prevPtr->getNext();
			prevPtr->setNext(curPtr->getNext());
		}//end if

		//Removes the Node that curPtr is pointing at.
		curPtr->setNext(NULL);
		delete curPtr;
		curPtr = NULL;
		itemCount--;
	}else{
        throw logic_error("The position is invalid.");
    }//end if

	return ableToRemove;
}

template<class ItemType>
Node<ItemType>* ListADT<ItemType>::getEntry(int position) const throw(logic_error){

	bool ableToGet = (position >= 1) && (position <= itemCount);

	if (ableToGet){
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr -> getItem();
	}
	else{
		throw logic_error("The position is invalid");
	}//end if

}//end getEntry

template<class ItemType>
void ListADT<ItemType>::setEntry(int position, const ItemType & newEntry) throw(logic_error){

	bool ableToSet = (position >= 1) && (position <= itemCount);

	if(ableToSet){
		Node<ItemType>* nodePtr = getNodeAt(position);
		nodePtr -> setItem(newEntry);
	}
	else{
		throw logic_error("The position is invalid");
	}//end if

}//end setEntry

template<class ItemType>
bool ListADT<ItemType>::swap(int positionA, int positionB) throw (logic_error){

	bool ableToSwap = ((positionA >= 1) && (positionA <= itemCount)) && ((positionB >= 1) && (positionB <= itemCount));

	if(ableToSwap){
		Node<ItemType>* nodePtrA = getNodeAt(positionA);
		Node<ItemType>* nodePtrB = getNodeAt(positionB);
		setEntry(positionA, nodePtrB);
		setEntry(positionB, nodePtrA);
	}
	else{
		throw logic_error("Either positionA or positionB are invalid.");
	}//end if

	return ableToSwap;
}//end swap

template<class ItemType>
void ListADT<ItemType>::reverse(){

	curPtr = headPtr;
	Node<ItemType>* prevPtr = NULL;
	Node<ItemType>* nextPtr;

	while (curPtr != NULL){
		nextPtr = curPtr -> getNext();
		curPtr -> getNext() = prevPtr;
		prevPtr = curPtr;
		curPtr = nextPtr;
	}//end while
	headPtr = prevPtr;

}//end reverse

template<class ItemType>
bool ListADT<ItemType>::replace(int position, const ItemType& newEntry) throw(logic_error){

	bool ableToReplace = (position >= 1) && (position <= itemCount);

	if(ableToReplace){
		Node<ItemType>* newNodePtr = getNodeAt(position);
		setEntry(position, newEntry);
	}
	else{
		throw logic_error("The position is invalid.");
	}//end if

	return ableToReplace;
}//end replace

template<class ItemType>
int ListADT<ItemType>::getPosition(const ItemType& entry) throw(logic_error){

	curPtr = headPtr;
	int position = 0;
	if(contains(entry)){
		for(int i = 0; i < itemCount; i++){
			curPtr = curPtr -> getNext();
			position++;
			if(curPtr.getItem() = entry){
				break;
			}//end if
		}//end for

		return position;
	}
	else{
		throw logic_error("The entry is not in the list.");
	}//end if
}//end getPosition

template<class ItemType>
bool ListADT<ItemType>::contains(const ItemType & entry){

	return (getPointerTo(entry) != NULL);
}//end contains

template<class ItemType>
bool ListADT<ItemType>::loadList(const string filename) throw (logic_error){

    string child;
    bool canLoad;
    vector<ItemType> childVec;

    ListElement childStruct;

    int posToInsert = 0;
    ifstream naughtyNiceFile;
    naughtyNiceFile.clear();
    naughtyNiceFile.open(filename.c_str());

	if (naughtyNiceFile > 0){
        canLoad = true;
        getline(naughtyNiceFile, child);
        childVec = stringSplit(child, ' ');
        childStruct = setStructItem(childVec);

        posToInsert = getPosByCountryCode(childStruct.countryCode);
        insert(posToInsert, childStruct);
    }
    else{
        canLoad = false;
        string message = "Error opening ";
        message = message + filename;
        throw logic_error(message);
    }
    return canLoad;

}//end loadListADT

template<class ItemType>
void ListADT<ItemType>::displayList(){

    ListElement A;
	//vector<ItemType> listVector = A.toVector();
    curPtr = headPtr;

    if (isEmpty())
        cout << "The list is empty." << endl;

	if(curPtr != NULL){
		cout << "_________________________________________" << endl;
		cout << "Country:   " << curPtr -> A.countryCode << "   Postal Code:   " << curPtr -> A.postalCode <<
                "   Last Name:   " << curPtr -> A.lastName << "   First Name:   " << curPtr -> A.firstName << "   Gifts:   ";
            for (int i = 0; i < curPtr -> A.gifts.size(); i++){
                cout << curPtr -> A.gifts[i] << endl;
            }
		cout << "_________________________________________" << endl;
        curPtr = curPtr -> getNext();
	}//end if
}//end displayListADT

//private

template<class ItemType>
Node<ItemType>* ListADT<ItemType>:: getNodeAt(int position) const throw(logic_error){

	bool posPrecond = ((position >= 1) && (position <= itemCount));
	curPtr = headPtr;
    if (posPrecond){
	for (int i = 1; i < position; i++)
		curPtr = curPtr -> getNext();
    }
    else{
        throw logic_error("The position is invalid.");
    }//end if
	return curPtr;
}//end getNodeAt

template<class ItemType>
Node<ItemType>* ListADT<ItemType>:: getPointerTo(const ItemType& target) const throw(logic_error){
	bool found = false;
	curPtr = headPtr;

	while (!found && (curPtr != NULL)){
		if (target == curPtr -> getItem())
			found = true;
		else
			curPtr = curPtr -> getNext();
	}//end while

    if(found = false)
        throw logic_error("The target does not exist.");

	return curPtr;
}//end getPointerTo

template<class ItemType>
int ListADT<ItemType>:: getPosByCountryCode(string target) const{
    bool found = false;
    curPtr = headPtr;
    int position = 1;

    while(!found && (curPtr != NULL)){

        if (target.compare(curPtr -> ListElement.countryCode/*??*/) == 0)
            found = true;

        else
            curPtr = NULL;
    }//end while

    if(curPtr != NULL)
         position = getPosition(curPtr -> getItem());

    return position;
}//end getNodeByCountryCode

template<class ItemType>
Node<ListElement>* ListADT<ItemType>:: setStructItem(vector <ItemType> child) const{

    ListElement childStruct;
    ListElement* childStructPtr;
    childStructPtr = &childStruct;

    childStructPtr -> naughtyNice = child[0];
    childStructPtr -> countryCode = child[1];

    //parse this to an integer
    childStructPtr -> postalCode = child[2];

    childStructPtr -> lastName = child[3];
    childStructPtr -> firstName = child[4];
    for (int i = 5; i < child.size(); i++){
        childStructPtr -> gifts.push_back(child[i]);
    }
    return childStruct;
}//end setStructItem

template<class ItemType>
vector <ItemType> ListADT<ItemType>::stringSplit(string str, char delimiter) const{

    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
  }

    return internal;
}
/*
template<class ItemType>
vector<ItemType> ListADT<ItemType>::toVector() const{

	vector<ItemType> listContents;
	curPtr = headPtr;

	for (int i = 0; i < itemCount; i++)
		listContents.push_back(items[i]);

   return listContents;
}  // end toVector
*/

#endif
