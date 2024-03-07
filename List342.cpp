/*
#ifndef ACTUAL_PROGRAM_3_LIST342_CPP
#define ACTUAL_PROGRAM_3_LIST342_CPP
#include "List342.h"
#include <string>
#include <fstream>

using namespace std;

//Constructor
template <class ItemType>
List342<ItemType>::List342() //Default Constructor
{
    this->head = nullptr;
}

template <class ItemType>
List342<ItemType>::List342(const List342 &that) //Copy Constructor
{
    this->head = nullptr;
    *this = that;
}

template <class ItemType>
List342<ItemType>::~List342() //Destructor delete the linked list upon destruction
{
    while(this->head != nullptr)
    {
        //clear out the data and values
        Node *temp = this->head; //takes data as a placeholder
        ItemType *itemValue = temp->data; //store the data
        this->head = this->head->next; //move to next node
        delete temp; //delete the data
    }
}


//Member Functions
template <class ItemType>
bool List342<ItemType>::BuildList(string fileName)
{
    ifstream inputFile;
    inputFile.open(fileName);

    ItemType *value;

    if(!inputFile.is_open()) //if the file does not exist
    {
        cout << "The file " << fileName << " cannot be found." << endl;
        return false;
    }
    else { //file found, time to add into the list
        cout << "The file has been found!" << endl;
        while (!inputFile.eof()) { //while the file is opened
            //cout << "Invoked" << endl;
            value = new ItemType;
            inputFile >> *value;
            this->Insert(value); //inserts item in list
        }
        inputFile.close();
        return true;
    }
}


template <class ItemType>
bool List342<ItemType>::Insert(ItemType *obj)
{
    Node *insObj = new Node();
    Node *pNode, *cNode; //pNode: pointer node, cNode: current list node
    insObj->data = obj; //copies the object

    //Check for duplicates
    Node *dupNode = new Node();
    dupNode = this->head;

    while(dupNode != nullptr){
        if(dupNode->data == insObj->data) //if a duplicate is found
            return false;
        dupNode = dupNode->next; //move to next node
    }

    if(insObj == nullptr) //if the object has nothing
    {
        delete insObj; //deallocate
        insObj = nullptr;
        return false;
    }

    if(this->head == nullptr) //inserts at the top of the list
    {
        this->head = insObj;
        return true;
    }
    else //the rest of the list
    {
        if(*insObj->data < *this->head->data) //starts at the head
        {
            insObj->next = this->head;
            this->head = insObj; //insert
            return true;
        }
        cNode = this->head->next;
        pNode = this->head;

        while(cNode != nullptr)
        {
            if(*insObj->data == *cNode->data) //additional duplicate check
            {
                delete insObj; //toss out duplicate object
                insObj = nullptr; //deallocate memory
                return false;
            }
            else if(*insObj->data < *cNode->data) //if not a duplicate
            {
                insObj->next = cNode; //found
                pNode->next = insObj; //insert object into list
                return true;
            }
            pNode = cNode; //iterate back
            cNode = cNode->next; //traverse the list
        }

        if(pNode != nullptr)
        {
            pNode->next = insObj;
            return true;
        }
        delete insObj;
        insObj = nullptr;
    }
    delete insObj;
    insObj = nullptr;
    return false;
}

template <class ItemType>
bool List342<ItemType>::Remove(ItemType target, ItemType &result) //remove and peek need work
{
    if(this->head == nullptr) //empty list - nothing to remove
        return false;

    if(*this->head->data == target) //if the target is the first in the list
    {
        //cout << "HEAD INVOKED" << endl;
        result = target;
        this->head->next = this->head->next->next; //deletes
        this->head = nullptr; //allocates memory
        return true;
    }
    Node *pNode = this->head; //to point in the rest of the list
    //pNode->data = this->head->data;
    while(pNode->next != nullptr) //anywhere else in the list
    {
        //cout << *pNode->next->data << " == ";
        //cout << target << " ";
        //cout << "INVOKED ";
        if(*pNode->next->data == target)
        {
            //cout << "INVOKED ";
            //cout << "REMOVED: " << target << endl;
            result = target;
            pNode->next = pNode->next->next; //deletes
            pNode = nullptr; //allocates memory
            return true;
        }
        pNode = pNode->next; //traverse through list
    }

    if(pNode->next == nullptr) //reached end, no target found
        return false;

    return false;
}

template <class ItemType>
bool List342<ItemType>::Peek(ItemType target, ItemType &result) const
{
    if(this->head == nullptr) //empty list - nothing to remove
        return false;

    if(*this->head->data == target) //if the target is the first in the list
    {
        //cout << "HEAD INVOKED" << endl;
        result = target;
        return true;
    }
    Node *pNode = this->head; //to point in the rest of the list
    pNode->data = this->head->data;
    while(pNode->next != nullptr) //anywhere else in the list
    {
        //cout << *pNode->next->data << " == ";
        //cout << target << " ";
        if(*pNode->next->data == target)
        {
            result = target;
            return true;
        }
        pNode = pNode->next; //traverse through list
    }

    if(pNode->next == nullptr) //reached end, no target found
        return false;

    return false;
}

template <class ItemType>
bool List342<ItemType>::isEmpty() const
{
    if(this->head == nullptr) //if the head is empty
        return true; //list is empty

    return false; //else, the list is not empty
}

template <class ItemType>
void List342<ItemType>::DeleteList()
{
    Node *cNode = this->head;
    Node *nNode;
    while(cNode != nullptr) //traverse entire list
    {
        nNode = cNode->next; //allocate memory
        delete cNode;
        cNode = nNode;
    }
    cNode = nullptr;
    this->head = nullptr;
}

template <class ItemType>
bool List342<ItemType>::Merge(List342 &list1) {
    Node *thisPtr = this->head;
    Node *list1Ptr = list1.head;
    if(this->head == nullptr) //empty list
    {
        *this = list1;
        list1.head = nullptr;
        return true;
    }
    if (*this == list1)
        return false; //merging the same lists - no duplicates
    else {
        while (thisPtr != nullptr && list1Ptr != nullptr)
        {
            this->Insert(list1Ptr->data);
            thisPtr = thisPtr->next;
            list1Ptr = list1Ptr->next;
        }
        list1.DeleteList();
        return true;
    }
}

//Operator Overloads
template <class ItemType>
List342<ItemType> List342<ItemType>::operator+(const List342<ItemType> &that) const
{
    List342<ItemType> addList;
    Node *listPtr;
    while(listPtr != nullptr)
    {
        addList.Insert(listPtr->data); //add to list
        listPtr = listPtr->next; //traverses the list
    }
    listPtr = that.head;
    while(listPtr != nullptr)
    {
        addList.Insert(listPtr->data);
        listPtr = listPtr->next;
    }
    return addList;
}

template <class ItemType>
void List342<ItemType>::operator+=(List342<ItemType> &that)
{
    Node *cNode;
    if(that.head == nullptr) //list is either the same or one is empty
        return; //nothing to do here

    cNode = that.head;
    while(cNode != nullptr)
    {
        this->Insert(cNode->data);
        cNode = cNode->next; //traverses the list
    }
}

template <class ItemType>
void List342<ItemType>::operator=(const List342<ItemType> &that) {
    if(that.head == nullptr) //list is empty
        return;

    if(this == &that) //lists are the same
        return;

    this->DeleteList();

    Node *thatPtr, *insNode;
    thatPtr = that.head;
    this->head = thatPtr;
    insNode = this->head->next;
    thatPtr = thatPtr->next;

    while(thatPtr != nullptr)
    {
        insNode = thatPtr;
        thatPtr = thatPtr->next;
    }
}


template <class ItemType>
bool List342<ItemType>::operator==(const List342<ItemType> &that) const
{
    Node *thisPtr = this->head;
    Node *thatPtr = that.head;

    if(this->head == nullptr && that.head == nullptr)
        return true; //lists are empty

    while(thisPtr->data == thatPtr->data && thisPtr->next != nullptr && thatPtr->next != nullptr)
    {
        thisPtr = thisPtr->next; //traverse through list this
        thatPtr = thatPtr->next; //traverse through list that
        //cout << "INVOKED" << endl;
    }
    if (thisPtr->data != thatPtr->data) //elements being checked are not equal
        return false;

    if(thisPtr->next == nullptr && thatPtr->next == nullptr) //if everything is found equal by the last index
        return true;

    return false;
}

template <class ItemType>
bool List342<ItemType>::operator!=(const List342<ItemType> &that) const
{
    return !(*this == *that);
}

#endif //ACTUAL_PROGRAM_3_LIST342_CPP
*/