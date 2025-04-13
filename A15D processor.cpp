#include <iostream>
#include <math.h>
//infinite loop
// 49 - 58 -> infinite loop
// test 1 COMPLETE
// test 2 COMPLETE
// test 3 COMPLETE
// test 4 COMPLETE
// test 5 COMPLETE
// test 6 COMPLETE
// test 7 0/
using namespace std;

//==============TO DO LIST=================================================
/*
* GENERAL CODE CLEANING, THIS IS A MESS
* popAndSwitch() cleaning
* reading negative numbers in reading lists as numbers
* error handling function
*/ 
// hashtag functions need serious overhaul
// last test num compare when num is bigger than int
//==============================================================================

//program memory and instruction pointer
char program_mem[20000];
char* mem_ptr = program_mem;
int ptr_value = 0;
int stackCounter = -1;                                   //shows current elements on stack, no elements and one elements count as zero need to be aware of that
char dotCommand;

struct ListElement;

struct List
{
    ListElement* startOfList;           //pointer to 1st position on the list
};

struct ListElement
{
    char value;
    ListElement* nextListItem;
};

struct StackField
{
    List value;
    StackField* previous_element;                       //pointer to a stack element "bellow" this element
};

StackField* stack_ptr = nullptr;                        //points to top of a stack

//=========================================================================================================================================================//
//=====================================================FUNCTIONS===========================================================================================//
//=========================================================================================================================================================//

bool stackIsNull()
{
    if (stack_ptr == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//append value at beggining of the list
void appendOnList(char value)
{
    //case with empty list
    if (stack_ptr->value.startOfList == nullptr)
    {
        stack_ptr->value.startOfList = new ListElement;
        stack_ptr->value.startOfList->value = value;
        stack_ptr->value.startOfList->nextListItem = nullptr;
    }
    else
    {
        //every other case, we make new beggining of the list, no need for switching every item
        ListElement* newListElement = new ListElement;
        newListElement->value = value;
        newListElement->nextListItem = stack_ptr->value.startOfList;
        stack_ptr->value.startOfList = newListElement;
    }
}

//add new empty list on the stack
void push()
{
    //create new StackField
    StackField* newField = new StackField;  //List is part of StackField, so it's also allocated here
    newField->value.startOfList = nullptr;  //so we can do it like that

    //check if stack is empty
    if (stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           //first element of stack doesnt have any element below
    }
    else
    {
        newField->previous_element = stack_ptr;
    }

    //attach stack pointer to new element and increment stack count
    stack_ptr = newField;
    stackCounter++;
}

//print stack content [helper function]
void printList(ListElement* listIterator)
{
    //again if works this should be moved to the main cause its shitty
    if (listIterator == nullptr)
    {
        cout << endl;        //prints last value and end a function at the end of the list
        return;
    }
    //unknown memory, need to make it null right now its "trash memory" fix it in push
    if (listIterator->nextListItem == nullptr)
    {
        cout << listIterator->value << endl;        //prints last value and end a function at the end of the list
        return;
    }
    else
    {
        cout << listIterator->value;                //prints current element of the list
        listIterator = listIterator->nextListItem;  //listIteratr jumps to next element of list
        printList(listIterator);
    }

}

//print stack content
void show(StackField* currentStackField, int Counter)
{
    //error handling
    if (stack_ptr == nullptr)
    {
        return;
    }

    //make pointer to start of the list at this stack field
    ListElement* listIterator = currentStackField->value.startOfList;

    //end ofrecursion when we reached end of the stack
    if (currentStackField->previous_element == nullptr)
    {
        //printing empty list if list is empty
        if (listIterator == nullptr)
        {
            cout << Counter << ": " << endl;
            return;
        }
        cout << Counter << ": ";
        printList(listIterator);            //print list on this stack field
        return;
    }
    else
    {

        //change pointer to one layer lower [recursion]
        currentStackField = currentStackField->previous_element;
        show(currentStackField, (Counter + 1));

        //printing empty list if list is empty
        if (listIterator == nullptr)
        {
            cout << Counter << ": ";
            cout << endl;
        }
        else
        {
            cout << Counter << ": ";
            printList(listIterator);
        }
    }
}

//put a exact copy of list from top on top of an stack [helper function]
void copyStackTopHelper(ListElement* startOfList, ListElement* startOfStackList)
{
    //ListElement* startOfList -> first pointer to a list.
    //ListElement* startOfStackList -> first pointer to a list on stack


    //if list has reached the end, end recursion
    //!!!if works this should me moved to the main function
    if (startOfStackList == nullptr)
    {
        //startOfList = nullptr;
        return;
    }
    if (startOfStackList->nextListItem == nullptr)
    {
        startOfList->value = startOfStackList->value;
        startOfList->nextListItem = nullptr;
        return;
    }

    //copy contents of existing list field
    startOfList->value = startOfStackList->value; ///[!!!] maybe before if

    //make new list points to new list element -> instead of copyint pointer to old list
    startOfList->nextListItem = new ListElement;

    //if everything is done, "recurse" function one more time
    copyStackTopHelper(startOfList->nextListItem, startOfStackList->nextListItem);
}

//Check if Stack top is an emtyy list
bool isStackTopEmptyList()
{
    if (stack_ptr->value.startOfList == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//put a exact copy of list from top on top of an stack
void copyStackTop()
{
    //check if stacktop is empty
    if (stack_ptr == nullptr)
    {
        return;         
    }

    //check if StackTop is an emptylist
    if (isStackTopEmptyList())
    {
        push();
        return;
    }

    //create new StackField, list with one emptyElement, once again List is already initiated here
    StackField* newField = new StackField;
    newField->value.startOfList = new ListElement; //need to decide between new ListElement/nullptr
    newField->value.startOfList->nextListItem = nullptr; //important
    //getting pointers of our stackfield, NULL if on bottom previous stackfield if not
   //THIS IF STATEMENT 99% CHANCE DOES NOTHING, FUNCTION ENDS IF NULLPTR
   if (stack_ptr == nullptr)
   {
       newField->previous_element = nullptr;           //first element of stack doesnt have any element below
   }
   else
   {
        newField->previous_element = stack_ptr;
   }

    //if copied list is empty, do not copy it
    if (stack_ptr->value.startOfList == nullptr)
    {

    }
    else
    {
        ListElement* startOfList = newField->value.startOfList;
        ListElement* startOfStackList = stack_ptr->value.startOfList;
        copyStackTopHelper(startOfList, startOfStackList);
    }
    //list copying mechanic, maybe another function with recursion

    //after everything move stack pointer to the new field

    stackCounter++;
    stack_ptr = newField;
}

//switch top and below lists in places
void switchLists()
{
    //error handling --> this can be made into function
    if (stackIsNull())
    {
        return;
    }
    //get pointer to previous element of a bellow field
    StackField* bellowFieldPointer = stack_ptr->previous_element->previous_element;

    //get pointer to "current" top field
    StackField* topField = stack_ptr;

    //get pointer to "current" bellow field
    StackField* bellowField = stack_ptr->previous_element;

    stack_ptr->previous_element = bellowFieldPointer;

    bellowField->previous_element = topField;

    stack_ptr = bellowField;
}

//remove item from stack [helper function]
void deleteStackContent(ListElement* listCleaner)
{
    //end of the list, end of recursion
    if (listCleaner->nextListItem == nullptr)
    {
        delete listCleaner;
        return;
    }
    deleteStackContent(listCleaner->nextListItem); //the correct way chat?
    delete listCleaner;

}

//remove item from the stack
void pop()
{
    //error handling
    if (stack_ptr == nullptr)
    {
        return;
    }

    //change pointer to top of the stack to element below
    StackField* cleaner = stack_ptr;

    //if this is bottom of a stack, change stack pointer to NULL
    if (stack_ptr->previous_element == nullptr)
    {
        stack_ptr = nullptr;
    }
    else
    {
        stack_ptr = stack_ptr->previous_element;
    }

    //if list is not empty, delete it
    if (cleaner->value.startOfList != nullptr)
    {
        ListElement* listCleaner = cleaner->value.startOfList;
        deleteStackContent(listCleaner);
    }

    delete cleaner;
    stackCounter--;
}

//function returning size of list
//returns a number of fields in list, second argument must be 1, need to think how to redo this
int getListCount(ListElement* listSearched, int listSize)
{
    if (listSearched->nextListItem == nullptr)
    {
        return listSize;
    }
    //also dlaczego nie dziala tutaj listSize++, a (listSize + 1) już tak   
    return getListCount(listSearched->nextListItem, (listSize + 1));
}

//returns contents of a list as an integer [helper]
int sumUpList(ListElement* listSearched, int powerOfTen, int returner)
{
    //listSearched -> beggining of our list
    //listSize -> number of numbers in the list
    //listSum -> numerical value of our list, will be returned, maybe we should pass it as 0

    int firstStep = listSearched->value - 48;
    int secondStep = pow(10, (powerOfTen));

    returner = returner + firstStep * secondStep;

    if (listSearched->nextListItem == nullptr)
    {
        return returner;
    }

    return sumUpList(listSearched->nextListItem, (powerOfTen + 1), (returner));
}

//returns contents of a list as an integer [main]
int readListToInt()
{

    //int listSize = getListCount(stack_ptr->value.startOfList, 1); //not used because of misinterpretation of list
    int numValue = sumUpList(stack_ptr->value.startOfList, 0, 0);
    return numValue;
}

//gives pointer to start of the list on -ish position [helper]
StackField* givePointer(StackField* stackPosition, int counter, int destination)
{
    if (counter == destination)
    {
        return stackPosition;
    }
    return givePointer(stackPosition->previous_element, (counter + 1), destination);
}

//will perform '@' action of copying number on stack and then copying list on stack [@]
void popAndSwitch()
{
    

    //read number that is on stack
    int numberOnStack = readListToInt();

    //if (numberOnStack >= stackCounter || numberOnStack < 0) //[!!!] cleaner way
    //{
    //    return;
    //}

    //remove that list/number from stack
    pop();

    //create new stack field, again List is part of StackField -> also initiated
    StackField* newField = new StackField;
    


    //what if we copy empty list
    
    //start of list points to nowhere
    

    //append new stackfield to the stack
    if (stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           //first element of stack doesnt have any element below
    }
    else
    {
        newField->previous_element = stack_ptr;
    }

    //get pointer to ish position
    StackField* numPosition = givePointer(stack_ptr, 0, numberOnStack);

    //debug
    if (numPosition->value.startOfList == nullptr)
    {
        newField->value.startOfList = nullptr;
        stackCounter++;
        stack_ptr = newField;
        return;
    }

    newField->value.startOfList = new ListElement;
    newField->value.startOfList->nextListItem = nullptr;
    //list copying 
    ListElement* startOfList = newField->value.startOfList;                    //this is correct
    // replace stack_ptr->value.startOfList to something else
    ListElement* startOfStackList = numPosition->value.startOfList;       //this need to be our i-sh field
    copyStackTopHelper(startOfList, startOfStackList);

    //increase stack size counter
    stackCounter++;

    //attach new stackField as top of the stack
    stack_ptr = newField;
}

//test function to see if list->int translate function works properly
void readStackChars(ListElement* listSearched)
{
    if (listSearched->nextListItem == nullptr)
    {
        cout << listSearched->value;
        return;
    }
    cout << listSearched->value;
    readStackChars(listSearched->nextListItem);
}

//read character from standard output and append it on StackTop list
void readAndAppend()
{
    //read a character from the standard output
    cin >> dotCommand;
    appendOnList(dotCommand);
}

//if there is minus on end of the list on StackTop, delete it [helper function] [list longer than 1]
void absoluteValueLongList(ListElement* stackTopList)
{  
    //if next list element is the last, check if pointer needs fixing
    if (stackTopList->nextListItem->nextListItem == nullptr)
    {
        if (stackTopList->nextListItem->value == '-')
        {
            //this way because we cannot operate on pointers to deleted memory
            ListElement* minusListElement = stackTopList->nextListItem;
            stackTopList->nextListItem = nullptr;
            delete minusListElement;
            return;   
        }
    }
    else
    {
        absoluteValueLongList(stackTopList->nextListItem);
    }
   
}

//remove minus from end of the list if there is one
void absoluteValue(ListElement* thisList, List* stackValue)
{
    //if there is nothing on the stack, return
    if (stackIsNull())
    {
        return;
    }

    //if stack has an empty list, return
    if (thisList == nullptr)
    {
        return;
    }

    //list with one element
    if (thisList->nextListItem == nullptr)
    {
        if (thisList->value == '-')
        {
            ListElement* oneListMinus = thisList;
            stackValue->startOfList = nullptr;
            delete oneListMinus;
        }
        return;
    }

    absoluteValueLongList(thisList);
}

//check if there is a minus at the end of the list
bool endIsMinus(ListElement* stackTopList)
{
    //check if we reached end of the list
    if (stackTopList->nextListItem == nullptr)
    {
        if (stackTopList->value == '-')
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return endIsMinus(stackTopList->nextListItem);
}

//add minus at the end of the list [helper]
void addMinusAtEndHelper(ListElement* stackList)
{
    //end of recursion
    if (stackList->nextListItem == nullptr)
    {
        ListElement* newListElement = new ListElement;
        stackList->nextListItem = newListElement;
        newListElement->value = '-';
        newListElement->nextListItem = nullptr;
        return;
    }

    addMinusAtEndHelper(stackList->nextListItem);
}

//add minus at the end of the list
void addMinusAtEnd()
{
    //case with empty list
    if (stack_ptr->value.startOfList == nullptr)
    {
        appendOnList('-');
        return;
    }

    //with nonEmpty lists do recursion
    ListElement* stackList = stack_ptr->value.startOfList;
    addMinusAtEndHelper(stackList);
}

//negation of top of the stack
void negate(ListElement* thisList)
{
    //rror handling -> operation on an empty stack
    if (stackIsNull())
    {
        return;
    }

    //emptylistcheckdumbbbbb
    if (stack_ptr->value.startOfList == nullptr)
    {
        addMinusAtEnd();
        return;
    }

    //checking if there is minus at the end of the list
    if(endIsMinus(thisList))
    {
        absoluteValue(stack_ptr->value.startOfList, &stack_ptr->value);
    }
    else
    {
        addMinusAtEnd();
    }
}

//print first character on a list and then pop the list
void printAndDelete()
{
    //check if stackmis empty
    if (stackIsNull())
    {
        return;
    }

    //check if list is empty
    if (stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //read first character from a list
    cout << stack_ptr->value.startOfList->value;

    //remove list from the stack
    pop();
}

//detach first character from the list, append it to new list on top of the stack
void detachAndAppend()
{
    //check if stackmis empty
    if (stackIsNull())
    {
        return;
    }

    //check if list is empty
    if (stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //case with one element list
    if (stack_ptr->value.startOfList->nextListItem == nullptr)
    {
        char copy = stack_ptr->value.startOfList->value;
        pop();
        push();
        push();
        appendOnList(copy);
        return;
    }

    //case with more than one element list

    //get pointer to start of the list ?
    ListElement* startOfList = stack_ptr->value.startOfList;
    //get character from beggining of the list
    char firstChar = stack_ptr->value.startOfList->value;
    //change List beggining
    stack_ptr->value.startOfList = stack_ptr->value.startOfList->nextListItem;
    delete startOfList;


    push();
    appendOnList(firstChar);
}

//reads list as number from StackTop, pops and attaches new list with single character
void readNumToChar()
{
    //error handling -> stack is empty
    if (stackIsNull())
    {
        return;
    }

    //error handling -> StackTop is an empty list
    if (stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //read list from StackTop as number
    int A = readListToInt();
    
    //remove list from the stack
    pop();

    //create new list
    push();

    //append char of ASCII value of int A on list
    appendOnList(A);
}

//returns integrer of power
int myTenPow(int base, int exponent, int counterOne)
{
    if (exponent == 0)
    {
        return 1;
    }

    if (counterOne == exponent)
    {
        return base;
    }

    return myTenPow((base * 10), exponent, (counterOne + 1));

}

//translate given int ex. 1234 to list 4->3->2->1. puts it on given stack ptr.
void translateNumberToList(int translator, int iterator, ListElement* Listend)
{
    int singleDigit;
    //get single digit number
    singleDigit = translator % myTenPow(10, iterator, 1) / myTenPow(10, iterator-1, 1);

    //"remove" the last digit from the translator
    translator = translator - translator % myTenPow(10, iterator, 1);

    //turn "single digit" into 'char'
    char ch = 48 + singleDigit;

    //get the single digit at the list [NEW FUNCTION APPEND AT END]
    Listend->value = ch;
    Listend->nextListItem = nullptr;

    //check end of recursion
    if (translator == 0)
    {
        return;
    }

    //if not create new listElement and go forward
    ListElement* nextListElement = new ListElement;
    Listend->nextListItem = nextListElement;

    //once again
    
    translateNumberToList(translator, (iterator + 1), nextListElement);     
}

//pop StackTop, put on stack list with number equal to ASCII of first character
void readCharToNum()
{
    //error handling -> stack is empty
    if (stackIsNull())
    {
        return;
    }

    //error handling -> StackTop is an empty list
    if (stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //get character from beggining of the list
    char A = stack_ptr->value.startOfList->value;

    //convert char to int
    int convert = int(A);

    //remove list from top
    pop();

    //create new list;
    push();

    //put empty listelement at start of the list
    stack_ptr->value.startOfList = new ListElement;

    //put "number A" on top of the list
    translateNumberToList(convert, 1, stack_ptr->value.startOfList);
}

//get pointer to the last element at the List
ListElement* getEndListPointer(ListElement* ourList)
{
    //end of recursion
    if (ourList->nextListItem == nullptr)
    {
        return ourList;
    }

    return getEndListPointer(ourList->nextListItem);
}

//copy the list
void cpyList(ListElement* copier, ListElement* destination)
{
    //create new list element
    destination->nextListItem = new ListElement;
    destination->nextListItem->nextListItem = nullptr;

    //copty the value
    destination->nextListItem->value = copier->value;

    //end recursion
    if (copier->nextListItem == nullptr)
    {
        return;
    }

    cpyList(copier->nextListItem, destination->nextListItem);
}

//pop list, attach it's copy at end of the previous list
void reAttach()
{
    //[!!!] propably some error handling could be nice

    //get pointer to end of previous list
    ListElement* endOfPrevious = getEndListPointer(stack_ptr->previous_element->value.startOfList);

    //error Handling
    if (stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //copy the current list to the end of previous list
    cpyList(stack_ptr->value.startOfList, endOfPrevious);

    //pop the stacklist
    pop();
}

//read instruction pointer as number, attach this number as list at the end of the stack
void putPtrValueOnStack()
{
    //get number of instruction
    int convert = ptr_value;

    //get new list on a stack
    push();

    //create new list
    stack_ptr->value.startOfList = new ListElement;

    //put "number A" on top of the list
    translateNumberToList(convert, 1, stack_ptr->value.startOfList);

}

//if StackTop is empty or have only 0, replace with 1, otherwise, replace with 0
void logicalNegation()
{
    //check if StackTop is empty
    if (stack_ptr == nullptr)
    {
        push();
        appendOnList('1');
        return; 
    }

    //check if StackTop is an empty list
    if (stack_ptr->value.startOfList == nullptr)
    {
        appendOnList('1');
        return;
    }

    //check if StackTop list contains only '0'
    if (stack_ptr->value.startOfList->value == '0' && stack_ptr->value.startOfList->nextListItem == nullptr)
    {
        pop();
        push();
        appendOnList('1');
        return;
    }

    //otherwise put '0' on top of StackTop
    pop();
    push();
    appendOnList('0');
}

//===========================================COMPARE FUNCTIONS==================================================================

//checks if list has minus at the end [compare]
bool isNegative(ListElement* thisList)
{
    if (thisList->nextListItem == nullptr)
    {
        if (thisList->value == '-')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return isNegative(thisList->nextListItem);
}

//check if list contains only zeroes, or zeroes and minus, returns 0 if so [compare]
bool isZero(ListElement* thisList)
{
    //check if current element is something else
    if ((thisList->value != '0') && (thisList->value != '-'))
    {
        return false;
    }

    //if end of list is reached return true
    if (thisList->nextListItem == nullptr)
    {
        return true;
    }

    //if not, go further
    return isZero(thisList->nextListItem);
}

//remove minus from the list
void removeMinus(ListElement* thisList)
{
    //if next value is an minus, remove is
    if (thisList->nextListItem->value == '-')
    {
        ListElement* minusElement = thisList->nextListItem;
        thisList->nextListItem = nullptr;
        delete minusElement;
        return;
    }

    removeMinus(thisList->nextListItem);
}

//add minus at the end of the list
void addMinus(ListElement* thisList)
{
    //if at the end of the list add minus
    if (thisList->nextListItem == nullptr)
    {
        thisList->nextListItem = new ListElement;
        thisList->nextListItem->value = '-';
        thisList->nextListItem->nextListItem = nullptr;
        return;
    }

    addMinus(thisList->nextListItem);
}

//true if every next element of the list is zero, false otherwise
bool everyNextElementIsZero(ListElement* thisList)
{
    //false condition
    if (thisList->value != '0')
    {
        return false;
    }

    //if we reached to the end without false checker, then it's true
    if (thisList->nextListItem == nullptr)
    {
        return true;
    }

    //recursion
    return everyNextElementIsZero(thisList->nextListItem);
}

//go through rest of the list, if everything will be zero delete everything (from the end)
//it will delete everything from this point, just need to isEveryElementNextZero(to be true)
void deleteZeroes(ListElement* thisList)
{

    //recursion end check if you are at the end of the list
    if (thisList->nextListItem->nextListItem != nullptr)
    {
        deleteZeroes(thisList->nextListItem);
    }

    //propably helper function will be needed

    ListElement* zeroEndList = thisList->nextListItem;
    thisList->nextListItem = nullptr;
    delete zeroEndList;
    //deleting only if next is nullptr
}

//iterate thru list, deleting streak of zeroes at the end
void deleteZeroesListIterator(ListElement* thisList)
{
    //pointer problems
    // next vs current one
    // needs fixing
    
    //when we reached end of the list, end function
    if (thisList->nextListItem == nullptr)
    {
        return;
    }

    //because of function isZero, we know that first element will not have to be deleted
    if (thisList->nextListItem->value == '0')
    {
        if (everyNextElementIsZero(thisList->nextListItem))
        {
            deleteZeroes(thisList);
        }
        
    }

    if (thisList->nextListItem == nullptr)
    {
        return;
    }

    //continue iteration until the end
    deleteZeroesListIterator(thisList->nextListItem);
}

//helper function, deletes zeroes at the end of the list [!!!] what if minus at the end?, changes number '000120' to '120' [compare]
void deleteZeroesMain(ListElement* thisList)
{
    //since minus at end could be troublesome we will delete it temporarly
    if (isNegative(thisList))
    {
        //remove minus for now [helper]
        removeMinus(thisList);

        //remove zeroes from end of the list [main task]
        deleteZeroesListIterator(thisList);
        
        //add minus at the end [helper]
        addMinus(thisList);

        return;
    }
    else
    {
        //remove zeroes from end of the list [main task]
        deleteZeroesListIterator(thisList);

        return;
    }
}

//returns size of a list as integer number, size in declaration must be one
int returnListSize(ListElement* thisList, int size)
{
    //if reached end of the list
    if (thisList->nextListItem == nullptr)
    {
        return size;
    }

    return returnListSize(thisList->nextListItem, (size + 1));

}

//compares lenght of two lists [compare]
bool AreSameSize()
{
    return true;
}

//helper function comparing lists char by char returns 1->toplist bigger  2-> bottom bigger  3->equal
int CompareCharByCharHelper(ListElement* topList, ListElement* bottomList, int code)
{
    //code starts as 3, if there won't be any change then lists are equal
    //every next list item is x10 bigger number so final bigger will decide
    if (topList->value > bottomList->value)
    {
        code = 1;
    }

    if(topList->value < bottomList->value)
    {
        code = 2;
    }

    //end of recursion
    if (topList->nextListItem == nullptr)
    {
        return code;
    }

    return CompareCharByCharHelper(topList->nextListItem, bottomList->nextListItem, code);
}

//compares two lists char by char [compare], only when both are positive or negative returns 1->toplist bigger  2-> bottom bigger  3->equal
int CompareCharByChar(ListElement* topList, ListElement* bottomList)
{
    //once again minuses are pain so we can remove them temporarly
    if ((isNegative(topList) == 1) && (isNegative(bottomList) == 1))
    {
        //remove minusus for comparison
        removeMinus(topList);
        removeMinus(bottomList);
        
        //1->toplist bigger  2-> bottom bigger  3->equal
        int result = CompareCharByCharHelper(topList, bottomList, 3);


        //add minuses after everything
        addMinus(topList);
        addMinus(bottomList);

        return result;
    }
    else
    {
        int result = CompareCharByCharHelper(topList, bottomList, 3);
        return result;
    }

}

//returns true if any list is empty or zero returns 1->toplist bigger  2-> bottom bigger  3->equal
int compareTwoListsMainError(ListElement* topList, ListElement* bottomList)
{
    //if both lists are equal, return 3
    if (stack_ptr->value.startOfList == nullptr && stack_ptr->previous_element->value.startOfList == nullptr)
    {
        return 3;
    }

    //if both lists are zero, return 3
    if (isZero(topList) == 1 && isZero(bottomList) == 1)
    {
        return 3;
    }

    // top->0   bottom->-10   return 1
    if (isZero(topList) == 1 && isNegative(bottomList) == 1)
    {
        return 1;
    }

    // top->0   bottom->10   return 2
    if (isZero(topList) == 1 && isNegative(bottomList) == 0)
    {
        return 2;
    }

    // top->-1   bottom->0   return 2
    if (isNegative(topList) == 1 && isZero(bottomList) == 1)
    {
        return 2;
    }

    // top->1   bottom->0   return 1
    if (isNegative(topList) == 0 && isZero(bottomList) == 1)
    {
        return 1;
    }

    //otherwise 
    return 10;
}

//main function for comparing two functions, [returns 1 if toplist is bigger, 2 if bottom one, 3 if equal], lists shouldn't be empty
//what about zeroes and empty lists warning: control may reach end of non-void function [-Wreturn-type]
int compareTwoListsMain(ListElement* topList, ListElement* bottomList)
{

    //=======CASE 0, POSITIVE AND NEGATIVE===================
    if ((isNegative(topList) == 1) && (isNegative(bottomList) == 0))
    {
        return 2;
    }

    if ((isNegative(topList) == 0) && (isNegative(bottomList) == 1))
    {
        return 1;
    }

    //check size of both lists
    int listA = returnListSize(topList, 1);
    int listB = returnListSize(bottomList, 1);
    //=======CASE 1, BOTH POSITIVE===========================
    if ((isNegative(topList) == 0) && (isNegative(bottomList) == 0))
    {
        //if one of the lists are longer
        if (listA > listB)
        {
            return 1;
        }
        
        if (listA < listB)
        {
            return 2;
        }

        return CompareCharByChar(topList, bottomList);
    }



    //=======CASE 2, BOTH NEGATIVE===========================
    if ((isNegative(topList) == 1) && (isNegative(bottomList) == 1))
    {
        //if one of the lists are longer
        if (listA < listB)
        {
            return 1;
        }

        if (listA > listB)
        {
            return 2;
        }

        if (CompareCharByChar(topList, bottomList) == 2)
        {
            return 1;
        }
        else if (CompareCharByChar(topList, bottomList) == 1)
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }

}


int main()
{
    //loading all program instructions
    cin >> program_mem;

    //iterating through all program instructions
    while (mem_ptr[ptr_value] != '\0')
    {
        //[!!!] debug
        //cout << ptr_value << ": " << endl;
        switch (mem_ptr[ptr_value])
        {
            
            

            case '\''://push empty list on the stack
            {
                push();
                ptr_value++;
                break;
            }

            case '&':
            {
                int stackCpy = 0; //!!! zamiana z stackCounter
                StackField* currentStackField = stack_ptr;   //our inside pointer that will iterate thru all stack
                show(currentStackField, stackCpy);
                ptr_value++;
                break;
            }

            case ':':
            {
                copyStackTop();

                ptr_value++;
                break;
            }

            case ';':
            {
                switchLists();
                ptr_value++;
                break;
            }

            case ',':
            {
                pop();
                ptr_value++;
                break;
            }

            case '@':
            {

                popAndSwitch();
                /*
                //test dlugosci listy
                cout << "liczba na stosie [INT]: " << readListToInt() << endl;
                cout << "liczba na stosie [CHAR]: ";
                readStackChars(stack_ptr->value.startOfList);
                cout << endl;
                */
                ptr_value++;
                break;
            }

            case '.':
            {
                readAndAppend();
                ptr_value++;
                break;
            }

            case '^':
            {
                absoluteValue(stack_ptr->value.startOfList, &stack_ptr->value);
                ptr_value++;
                break;
            }

            case '-':
            {
                negate(stack_ptr->value.startOfList);
                ptr_value++;
                break;
            }

            case '>':
            {
                printAndDelete();
                ptr_value++;
                break;
            }

            case '$':
            {
                detachAndAppend();
                ptr_value++;
                break;
            }

            case ']':
            {
                readNumToChar();
                ptr_value++;
                break;
            }

            case '[':
            {
                readCharToNum();
                ptr_value++;
                break;
            }

            case '#':
            {
                reAttach();
                ptr_value++;
                break;
            }

            case '~':
            {
                putPtrValueOnStack();
                ptr_value++;
                break;
            }

            case '!':
            {
                logicalNegation();
                ptr_value++;
                break;
            }

            //very easily new function
            case '=':
            {
                
                if (compareTwoListsMainError(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) != 10)
                {
                    if (compareTwoListsMainError(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) == 3)
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('1');
                        ptr_value++;
                        break;
                    }
                    else
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('0');
                        ptr_value++;
                        break;
                    }
                }
                else 
                {
                    //clean lists
                    deleteZeroesMain(stack_ptr->value.startOfList);
                    deleteZeroesMain(stack_ptr->previous_element->value.startOfList);

                    if (compareTwoListsMain(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) == 3)
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('1');
                        ptr_value++;
                        break;
                    }
                    else
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('0');
                        ptr_value++;
                        break;
                    }
                }
                    
                

                ptr_value++;
                break;


            }

            //very easily new function
            case '<':
            {
                if (compareTwoListsMainError(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) != 10)
                {
                    if (compareTwoListsMainError(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) == 1)
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('1');
                        ptr_value++;
                        break;
                    }
                    else
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('0');
                        ptr_value++;
                        break;
                    }
                }
                else
                {
                    //clean lists
                    deleteZeroesMain(stack_ptr->value.startOfList);
                    deleteZeroesMain(stack_ptr->previous_element->value.startOfList);

                    if (compareTwoListsMain(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList) == 1)
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('1');
                        ptr_value++;
                        break;
                    }
                    else
                    {
                        pop();
                        pop();
                        push();
                        appendOnList('0');
                        ptr_value++;
                        break;
                    }
                }



                ptr_value++;
                break;
            }

            case '?':
            {
                
                int replacer = readListToInt();
                //if (replacer == ptr_value)
               // {
               //     cout << "[ERROR] Infinite loop detected: replacer == ptr_value == " << replacer << endl;
               //     break;
              //  }
                pop();

                if(stack_ptr->value.startOfList == nullptr)
                {
                    pop();
                    
                    ptr_value++;
                    break;
                }

                if (stack_ptr->value.startOfList->value == '0' && stack_ptr->previous_element->value.startOfList->nextListItem == nullptr)
                {
                    pop();
                    ptr_value++;
                    break;
                }

                //actual jump
                
               
                pop();
                ptr_value = replacer;
                break;
                

            }

            case '+':
            {
                cout << "szefik szefik" << endl;
                ptr_value++;
                break;
            }
            //check if this can be moved to "default"
            case 'q':
            case 'w':
            case 'e':
            case 'r':
            case 't':
            case 'y':
            case 'u':
            case 'i':
            case 'o':
            case 'p':
            case 'a':
            case 's':
            case 'd':
            case 'f':
            case 'g':
            case 'h':
            case 'j':
            case 'k':
            case 'l':
            case 'z':
            case 'x':
            case 'c':
            case 'v':
            case 'b':
            case 'n':
            case 'm':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                appendOnList(mem_ptr[ptr_value]);
                ptr_value++;
                break;
            }
            default:
            {
                ptr_value++;
            }
        }
    }
}

//======================== '=' DEBUGGING =============================================
/*
                // is list zero test '0-' == '0' == '0000' =='000000-'
                if (isZero(stack_ptr->value.startOfList))
                {
                    cout << "==ZERO==";
                }
                else
                {
                    cout << "==NON ZERO==";
                }
                cout << endl;
                */

                /*
                // is list negative test
                if (isNegative(stack_ptr->value.startOfList))
                {
                    cout << "==NEGATIVE==";
                }
                else
                {
                    cout << "==NON NEGATIVE==";
                }
                cout << endl;
                */

                //removeMinus(stack_ptr->value.startOfList);

                //deleteZeroesMain(stack_ptr->value.startOfList);

                //cout << compareTwoListsMain(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList);

                //cout << CompareCharByChar(stack_ptr->value.startOfList, stack_ptr->previous_element->value.startOfList);
