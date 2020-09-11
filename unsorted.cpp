// This file contains the linked implementation of class UnsortedType.

#include "unsorted.h"
#include<iostream>
using namespace std;

struct NodeType{
    ItemType info;
    NodeType* next;
};

// Class constructor
UnsortedType::UnsortedType(){
  length = 0;
  listData = NULL;
}

// Returns true if there is no room for another ItemType
//  on the free store; false otherwise.
bool UnsortedType::IsFull() const{
  NodeType* location;
  try{
    location = new NodeType;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception){
    return true;
  }
}

// Post: Number of items in the list is returned.
int UnsortedType::GetLength() const{
  return length;
}

// Post: List is empty; all items have been deallocated.
void UnsortedType::MakeEmpty(){
  NodeType* tempPtr;
    while (listData != NULL){
      tempPtr = listData;
      listData = listData->next;
      delete tempPtr;
  }
  length = 0;
}

// item is in the list; length has been incremented.
void UnsortedType::PutItem(ItemType item){
  NodeType* location;			// Declare a pointer to a node

  location = new NodeType;		// Get a new node
  location->info = item;		// Store the item in the node
  location->next = listData;	// Store address of first node in next field of new node
  listData = location;		// Store address of new node into external pointer
  length++;				// Increment length of the list
}

// Pre:  Key member(s) of item is initialized.
// Post: If found, item's key matches an element's key in the
//       list and a copy of that element has been stored in item;
//       otherwise, item is unchanged.
ItemType UnsortedType::GetItem(ItemType& item, bool& found){
  bool moreToSearch;
  NodeType* location;

  location = listData;
  found = false;
  moreToSearch = (location != NULL);

  while (moreToSearch && !found){
    switch (item.ComparedTo(location->info)){
      case LESS    :
      case GREATER : location = location->next;
                     moreToSearch = (location != NULL);
                     break;
      case EQUAL   : found = true;
                     item = location->info;
                     break;
    }
  }
  return item;
}

// Pre:  item's key has been initialized.
//       An element in the list has a key that matches item's.
// Post: No element in the list has a key that matches item's.
 void UnsortedType::DeleteItem(ItemType item){
  NodeType* location = listData;
  NodeType* tempLocation;

  // Locate node to be deleted.
  if (item.ComparedTo(listData->info) == EQUAL){
    tempLocation = location;
    listData = listData->next;		// Delete first node.
  }
  else{
    while (item.ComparedTo((location->next)->info) != EQUAL)
      location = location->next;

    // Delete node at location->next
    tempLocation = location->next;
    location->next = (location->next)->next;
  }
  delete tempLocation;
  length--;
}

// Post: Current position has been initialized.
void UnsortedType::ResetList(){
  currentPos = NULL;
}

// Post:  A copy of the next item in the list is returned.
//        When the end of the list is reached, currentPos
//        is reset to begin again.
ItemType UnsortedType::GetNextItem(){
  ItemType item;
  if (currentPos == NULL)
    currentPos = listData;
  else
    currentPos = currentPos->next;
  item = currentPos->info;
  return item;
}

void UnsortedType::SplitList(UnsortedType list, ItemType item, UnsortedType& list_1, UnsortedType& list_2){
  //Construct list_1
    int length;
    int counter;
    ItemType tempItem;

    list.ResetList();
    length = list.GetLength();

    for (counter = 1; counter <= length; counter++){
      tempItem = list.GetNextItem();
      if (tempItem.ComparedTo(item) == EQUAL) {
        list_1.PutItem(tempItem);
        break;
      }
      else{
        list_1.PutItem(tempItem);
      }
    }

    for (int counter2 = counter; counter2 < length; counter2++) {
      tempItem = list.GetNextItem();
      list_2.PutItem(tempItem);
    }
}

// Post: List is empty; all items have been deallocated.
UnsortedType::~UnsortedType(){
  NodeType* tempPtr;

  while (listData != NULL){
    tempPtr = listData;
    listData = listData->next;
    delete tempPtr;
  }
}
