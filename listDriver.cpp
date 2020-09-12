// Test driver
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "unsorted.h"

using namespace std;
void PrintList(ofstream& outFile, UnsortedType& list);

int main(){

  ifstream inFile;       // file containing operations
  ofstream outFile;      // file containing output
  string inFileName;     // input file external name
  string outFileName;    // output file external name
  string outputLabel;
  string command;        // operation to be executed

  int number;
  ItemType item;
  UnsortedType list;
  UnsortedType list_1;
  UnsortedType list_2;
  bool found;
  int numCommands;


  // Prompt for file names, read file names, and prepare files
  cout << "Enter name of input command file; press return." << endl;
  cin  >> inFileName;
  inFile.open(inFileName.c_str());

  cout << "Enter name of output file; press return." << endl;
  cin  >> outFileName;
  outFile.open(outFileName.c_str());

  cout << "Enter name of test run; press return." << endl;
  cin  >> outputLabel;
  outFile << outputLabel << endl;
  if (!inFile){
    cout << "file not found" << endl;
	exit(2);
  }

  inFile >> command;

  numCommands = 0;
  while (command != "Quit"){
    if (command == "PutItem"){
      inFile >> number;
      item.Initialize(number);
      list.PutItem(item);
      item.Print(outFile);
      outFile << " is in list" << endl;
    }
    else if (command == "DeleteItem"){
      inFile >> number;
      item.Initialize(number);
      list.DeleteItem(item);
      item.Print(outFile);
      outFile << " is deleted" << endl;
    }
    else if (command == "GetItem"){
      inFile >> number;
      item.Initialize(number);
      item = list.GetItem(item, found); //SEGFAULT After SplitList
      item.Print(outFile);

      if (found)
        outFile << " found in list." << endl;

      else outFile <<  " not in list."  << endl;
    }
    else if (command == "GetLength"){
      outFile << "Length is " << list.GetLength() << endl;
    }
    else if (command == "IsFull"){
      if (list.IsFull())
        outFile << "List is full." << endl;
      else outFile << "List is not full."  << endl;
    }
    else if (command == "MakeEmpty"){
	     list.MakeEmpty();
    }
	  else if (command == "PrintList"){
	  PrintList(outFile, list);
  }
    else if (command == "SplitList"){
      inFile >> number;
      item.Initialize(number);
      item = list.GetItem(item, found);

      outFile << "Initial List: ";
      PrintList(outFile, list);
      outFile << "list split at key: ";
      item.Print(outFile);
      outFile << endl;

      list.SplitList(list, item, list_1, list_2);

      outFile << "List 1: ";
      PrintList(outFile, list_1);

      outFile << "List 2: ";
      PrintList(outFile, list_2);
    //list.ResetList();
    }
	  else{
	  cout << command << " is not a valid command." << endl;
    }
	numCommands++;
  cout <<  " Command number " << numCommands << " completed."
        << endl;
  inFile >> command;
  };

  cout << "Testing completed."  << endl;
  inFile.close();
  outFile.close();
  return 0;
}

// Pre:  list has been initialized.
//       dataFile is open for writing.
// Post: Each component in list has been written to dataFile.
//       dataFile is still open.
void PrintList(ofstream& dataFile, UnsortedType& list){
  int length;
  ItemType item;

  list.ResetList();
  length = list.GetLength();

  for (int counter = 1; counter <= length; counter++){
    item = list.GetNextItem();
    item.Print(dataFile);
    dataFile << " ";
  }
  dataFile << endl;
}
