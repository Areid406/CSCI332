/** @file BagDriver.cpp
 * Bag Main Driver - use to test Bag class methods and 
 *  functions that are independent from the Bag class.
 *                                
 * @author  Phil Curtiss (modified from original by Jeff Braun)
 * @version 1.0
 * @date 9/8/15
 **********************************************************/

//-----------------------
// C++ includes
//-----------------------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//-----------------------
// Application includes
//-----------------------
#include "Bag.h"
#include "io_functions.h"

//-----------------------
// Using statements
//-----------------------
using namespace std;

//-----------------------
// Manifest Constants
//-----------------------
#define BAGNO	3

//----------------------
// Functions Prototypes
//----------------------
int getBagNum();	//prompts user for bag number
void processOption(char& c, Bag<string> bags[]);	//processes menu input option
void displayBag(Bag<string>& bag);	//display the bag's entire contents
void restoreBag(Bag<string>& bag);	//prompts for filename that contains items
void saveBag(Bag<string>& bag);   //prompts for filename to store items into

/** Bag Driver - use to test Bag class methods and 
 * bag functions that are independent from the Bag class.
 **********************************************************/
int main()
{
  int bagNum;	//The number of the bag to use in the bag array
  Bag<string> bag[BAGNO];	// create array of bags used for testing with bag 0 used for intersection/union
  string restoreBagFlg;	// holds response to restore bag from a file
  string menuOption;	// holds menu option input from user

//Provide an Opening Message to the User
  cout<< "Bag Driver - Tests the Bag class using two bags" << endl;

//Ask the User if they wish to Restore a bag from a file
  cout<< "----------------------------------" << endl; 
  cout<< "Would you like to restore a bag from a file? (Y/N) ";
   
//Read user input - use a string to accept all inputs
  getline(cin, restoreBagFlg);
  bagNum = getBagNum();
  if(restoreBagFlg[0] == 'Y' || restoreBagFlg[0] == 'y'){ 
    restoreBag(bag[bagNum]);	// opens/reads file into aBag
  }

//Menu driven part of main program
//Initial menu display and loop to process menu option
  printMenu();
  do {
    cout << "\nEnter menu selection (0 for menu): ";
    getline(cin, menuOption);	//Use a string in case user enters chars
    processOption(menuOption[0], bag);
  }while(menuOption[0] != '8');
   
  return 0;            //Exit program
}//main()


//---------------------------
// Local function definitions
//---------------------------

/**Reads, validates, and returns a 1 or 2
 * @pre  none
 * @post none
 * @return 1 or 2
 */
int getBagNum()
{
  int bagNum=0;  
  while(bagNum != 1 && bagNum != 2)
  {
    cout << "Set the working bag (1 or 2)? ";
    bagNum = getInt();
  }
  return bagNum;
} //getBagNum()

/**
 * Displays the entire content of the bag
 * @param[in] bag to display
 * @remarks If bag is empty, prints empty bag message.
 */
void displayBag(Bag<string>& bag) 
{
  string item;
  vector<string> bagVector = bag.toVector();

  if(bagVector.size() > 0)
  {
    cout << "The bag contains: " << endl;
    for(unsigned int i=0; i<bagVector.size(); i++){
      cout << bagVector[i] << ", ";
    }
    cout<<endl;
  }
  else
  {
    cout << "The bag is empty." << endl;
  }
} //displayBag()


/**
  * Process input menu option character from user.
  * @param[in] menuChar menu option character
  * @param[in,out] bag the bag to be modified
  */
void processOption(char &menuChar, Bag<string> bag[])
{
  int bagNum;
  string item;
  string saveBagFlg;

   switch (menuChar)
   {
    case '0':	// Display menu options
       printMenu();
       break;

    case '1':   // Output size of the bag
       cout << "\nBag[" << getBagNum() << "] Size is: " << bag[getBagNum()].getCurrentSize() << endl;
       break;

    case '2':	// Add items to the bag 
       cout << "Add Item:" << endl;
       item = getItem();
       bagNum = getBagNum();
       if(bag[bagNum].add(item))
       {
         cout << item << " was successfully added to Bag[" << bagNum << "]" << endl;
       }
       else
       {
         cout << item << " was not added to the Bag." << endl;
       }
       break;

//NOTE that options 3 - 6 are left for the student to complete

    case '7':	// Display entire contents of bag
       displayBag(bag[getBagNum()]);
       break;

    case '8':	// Exit the program
    case 'Q':	// handles multiple quit inputs
    case 'q':
       cout<< "Would you like to save the Bag to a file? (Y/N) ";
       getline(cin, saveBagFlg);
       if(saveBagFlg[0] == 'Y' || saveBagFlg[0] == 'y')
         saveBag(bag[getBagNum()]);	// save bag to file
       cout<< "Goodbye!"<< endl;	// Exit message
       menuChar = '8';	// Make sure we change char so we terminate input loop
       break;
    default:	// Invalid menu option entered
       cout << "\nError!  Invalid option.  Please try again.\n\n";
       printMenu();
    }
}//processOption()

/**
  * Restore the bag from a user specified file
  * @param[inout] bag restored from input file
  * @post The bag contains all items in the file if size < max bag list.
  * @remarks Prompt the user for the filename to retore the bag from.
  * If cannot open file, then reprompt user for filename.
  * Read items from file until end of file (eof) reached
  *  or until the bag is full.
  * Print the number of items read from the file.
  */
void restoreBag(Bag<string>& bag)
{
  bool success = true;
  ifstream fin;
  string filename;
  string item;

  //Data validation to get filename and open it
  do{
    cout<<"Enter the filename that contains the items you wish to restore to the Bag: ";
    getline(cin, filename);
    fin.clear();
    fin.open(filename.c_str());
    if(fin == 0){
      cout << "ERROR  - could not open file " << filename << endl;
    }
  } while (!fin);

  //read file until end of file (EOF) is reached
  while(success && getline(fin, item)){
    success = bag.add(item);
  }
  if (!success) cout << "Not all items added to the bag!" << endl;
  cout << bag.getCurrentSize() << " items read into the bag\n\n";
  fin.close();
}//restoreBag()

/**
  * Prompts the user for the filename in which to store the bag contents.
  * @param[in] bag to be saved to a user specified file
  */
void saveBag(Bag<string>& bag)
{
   //NOTE this is a function stub. You need to implement it. 
   cout << "Bag will be saved when implemented" << endl;
}//saveBag()

