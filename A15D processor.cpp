#include <iostream>
#include <math.h>

using namespace std;

//to do
//delete this
//constants
//global variebles trolololol
//check defines for stack top and stack bellow

//===========================================================================================================
//==========================================DATA STRUCTURES==================================================
//===========================================================================================================
//[cleaning] this needs to be local :(, made into struck -> read about typedef
struct StackField;
struct ListElement;

struct S            //cleaning zamiana nazw na lepsze i tak bd od teraz przedrostek stack
{
    char program_mem[20000];
    char* mem_ptr;
    int ptr_value;
    int stackCounter;          //shows current elements on stack, no elements and one elements count as zero need to be aware of that
    char dotCommand;
    StackField* stack_ptr;                        //points to top of a stack [cleaning -> zamiana na top_ptr]
};



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

//============================================================================================================================================
//=====================================================FUNCTIONS==============================================================================
//============================================================================================================================================

//initializing program and stack
void initializeStack(S* Stack)
{
    Stack->mem_ptr = Stack->program_mem;    //[error]
    Stack->ptr_value = 0;
    Stack->stackCounter = -1;
    Stack->stack_ptr = nullptr;
}

//returns 1 if stack is empty, 0 otherwise
//[cleaning] can be made a part of bigger function errorhandling
bool stackIsNull(S* Stack)
{
    if (Stack->stack_ptr == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Check if Stack top is an emtyy list
bool isStackTopEmptyList(S* Stack)
{
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }

}

//returns a number of fields in list [size of list], second argument must be 1. cleaning] constant as #define list minimum size = 1
int getListCount(ListElement* listSearched, int listSize)
{
    if (listSearched->nextListItem == nullptr)
    {
        return listSize;
    }

    return getListCount(listSearched->nextListItem, (listSize + 1));
}

//returns contents of a list as an integer [helper]
int readListToIntHelper(ListElement* listSearched, int powerOfTen, int returner)
{
    //get current number in list
    int firstStep = listSearched->value - 48;

    //get current power of 10s e.x. 8 in 1820 is 10^2
    int secondStep = pow(10, (powerOfTen));

    //add this listElement
    returner = returner + firstStep * secondStep;

    //end of recursion
    if (listSearched->nextListItem == nullptr)
    {
        return returner;
    }

    return readListToIntHelper(listSearched->nextListItem, (powerOfTen + 1), (returner));
}

//returns contents of a list as an integer [main] [helper in other functions] [cleaning] [constants]
int readListToInt(S* Stack)
{
    return readListToIntHelper(Stack->stack_ptr->value.startOfList, 0, 0);
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

    //recursion
    return endIsMinus(stackTopList->nextListItem);
}

//append value at beggining of the stackTopList
void appendOnList(char value, S* Stack)
{
    //case with empty list
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        Stack->stack_ptr->value.startOfList = new ListElement;
        Stack->stack_ptr->value.startOfList->value = value;
        Stack->stack_ptr->value.startOfList->nextListItem = nullptr;
    }
    //every other case, we make new beggining of the list, no need for switching every item
    else
    {
        
        ListElement* newListElement = new ListElement;
        newListElement->value = value;
        newListElement->nextListItem = Stack->stack_ptr->value.startOfList;
        Stack->stack_ptr->value.startOfList = newListElement;
    }
}

//add new empty list on the stack
void push(S* Stack)
{
    //create new StackField
    StackField* newField = new StackField;  //List is part of StackField, so it's also allocated here
    newField->value.startOfList = nullptr;

    //check if stack is empty, for previous element pointer
    if (Stack->stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           
    }
    else
    {
        newField->previous_element = Stack->stack_ptr;
    }

    //attach stack pointer to new element and increment stack count
    Stack->stack_ptr = newField;
    Stack->stackCounter++;
}

//print stack content [helper function] [& command]
void printList(ListElement* listIterator)
{
    //print current element of the list
    cout << listIterator->value;               

    //end of recursion
    if (listIterator->nextListItem == nullptr)
    {
        cout << endl;    //next list/end of printing    
        return;
    }
    
    //continue recursion    
    printList(listIterator->nextListItem);
}

//print stack content [& command]
void show(StackField* currentStackField, int Counter, S* Stack)
{
    //error handling [cleaning if you really don't have what to do]
    if (Stack->stack_ptr == nullptr)
    {
        return;
    }

    //make pointer to start of the list at this stack field
    ListElement* listIterator = currentStackField->value.startOfList;

    //recursion if stackBottom is not reached
    if (currentStackField->previous_element != nullptr)
    {
        show(currentStackField->previous_element, (Counter + 1), Stack);
    }

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

//top list copying [helper function]
void copyStackTopHelper(ListElement* startOfNewList, ListElement* startOfCopiedList)
{
    //end of recursion
    if (startOfCopiedList->nextListItem == nullptr)
    {
        startOfNewList->value = startOfCopiedList->value;
        startOfNewList->nextListItem = nullptr;
        return;
    }

    //copy contents of existing list field
    startOfNewList->value = startOfCopiedList->value;

    //make new list points to new list element -> instead of copyint pointer to old list
    startOfNewList->nextListItem = new ListElement;

    //if everything is done, "recurse" function one more time
    copyStackTopHelper(startOfNewList->nextListItem, startOfCopiedList->nextListItem);
}

//put a exact copy of list from top on top of an stack [':' command]
void copyStackTop(S* Stack)
{
    //check if stacktop is empty
    if (Stack->stack_ptr == nullptr)
    {
        return;         
    }

    //check if StackTop is an emptylist
    if (isStackTopEmptyList(Stack))
    {
        push(Stack);
        return;
    }

    //create new StackField
    StackField* newField = new StackField;
    newField->value.startOfList = new ListElement; 
    newField->value.startOfList->nextListItem = nullptr; 
   
    //assigning pointers in new StackField
    if (Stack->stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;          
    }
    else
    {
         newField->previous_element = Stack->stack_ptr;
    }

    //copy the list with recursive helper function
    ListElement* startOfList = newField->value.startOfList;
    ListElement* startOfStackList = Stack->stack_ptr->value.startOfList;
    copyStackTopHelper(startOfList, startOfStackList);
    
    //increase the StackCount, and change pointer to StackTop
    Stack->stackCounter++;
    Stack->stack_ptr = newField;
}

//switch top and below lists in places [';' command]
void switchLists(S* Stack)
{
    //error handling
    if (stackIsNull(Stack) || Stack->stack_ptr->previous_element == nullptr)
    {
        return;
    }

    //get pointer to previous element of a bellow field
    StackField* bellowFieldPointer = Stack->stack_ptr->previous_element->previous_element;

    //get pointer to "current" top field
    StackField* topField = Stack->stack_ptr;

    //get pointer to "current" bellow field
    StackField* bellowField = Stack->stack_ptr->previous_element;

    //top field points to bottom field pointer
    Stack->stack_ptr->previous_element = bellowFieldPointer;

    //bellow field points to current top
    bellowField->previous_element = topField;

    //StackTop is previous field
    Stack->stack_ptr = bellowField;
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

    deleteStackContent(listCleaner->nextListItem); 
    delete listCleaner;
}

//remove item from the stack [',' command]
void pop(S* Stack)
{
    //error handling
    if (Stack->stack_ptr == nullptr)
    {
        return;
    }

    //get pointer to element that will be deleted
    StackField* cleaner = Stack->stack_ptr;

    //change StackTop pointer
    if (Stack->stack_ptr->previous_element == nullptr)
    {
        Stack->stack_ptr = nullptr;
    }
    else
    {
        Stack->stack_ptr = Stack->stack_ptr->previous_element;
    }

    //if list is not empty, delete it
    if (cleaner->value.startOfList != nullptr)
    {
        ListElement* listCleaner = cleaner->value.startOfList;
        deleteStackContent(listCleaner);
    }

    delete cleaner;
    Stack->stackCounter--;
}

//gives pointer to start of the list on -ish position [@] [helper]
StackField* givePointer(StackField* stackPosition, int counter, int destination)
{
    if (counter == destination)
    {
        return stackPosition;
    }
    return givePointer(stackPosition->previous_element, (counter + 1), destination);
}

//will perform '@' action of copying number on stack and then copying list on stack [@]
void popAndSwitch(S* Stack)
{
    if (Stack->stack_ptr == nullptr)
    {
        return;
    }
    //read number that is on stack, and remove it from stack
    int numberOnStack = readListToInt(Stack);
    pop(Stack);
    
    //create new stack field
    StackField* newField = new StackField;
    
    //append new stackfield to the stack
    if (Stack->stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           
    }
    else
    {
        newField->previous_element = Stack->stack_ptr;
    }

    //get pointer to ish position
    StackField* numPosition = givePointer(Stack->stack_ptr, 0, numberOnStack);

   //if copied list is empty
    if (numPosition->value.startOfList == nullptr)
    {
        newField->value.startOfList = nullptr;
        Stack->stackCounter++;
        Stack->stack_ptr = newField;
        return;
    }

    //create new listElement
    newField->value.startOfList = new ListElement;
    newField->value.startOfList->nextListItem = nullptr;

    //list copying 
    ListElement* startOfList = newField->value.startOfList;                    
    ListElement* startOfCopiedList = numPosition->value.startOfList;      
    copyStackTopHelper(startOfList, startOfCopiedList);

    //increase stackSize, attach pointer
    Stack->stackCounter++;
    Stack->stack_ptr = newField;
}

//read character from standard output and append it on StackTop list [.]
void readAndAppend(S* Stack)
{
    cin >> Stack->dotCommand;
    appendOnList(Stack->dotCommand, Stack);
}

//if there is minus on end of the list on StackTop, delete it [helper function] [list longer than 1] [^]
void absoluteValueLongHelper(ListElement* stackTopList)
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
               
        }
        return;
    }
    else
    {
        absoluteValueLongHelper(stackTopList->nextListItem);
    }
   
}

//remove minus from end of the list if there is one [^]
void absoluteValue(ListElement* thisList, List* stackValue, S* Stack)
{
    //if there is nothing on the stack, return [cleaning double error check]
    if (stackIsNull(Stack))
    {
        return;
    }

    //if stack has an empty list, return
    if (thisList == nullptr)
    {
        return;
    }

    //list with one element -> delete this element from stack
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

    //helper recursive function
    absoluteValueLongHelper(thisList);
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
void addMinusAtEnd(S* Stack)
{
    //case with empty list
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        appendOnList('-', Stack);
        return;
    }

    //with nonEmpty lists do recursion
    ListElement* stackList = Stack->stack_ptr->value.startOfList;
    addMinusAtEndHelper(stackList);
}

//negation of top of the stack
void negate(ListElement* thisList, S* Stack)
{
    //error handling -> operation on an empty stack
    if (stackIsNull(Stack))
    {
        return;
    }

    //error handling -> list is empty
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        appendOnList('-', Stack);
        return;
    }

    //checking if there is minus at the end of the list
    if(endIsMinus(thisList))
    {
        absoluteValue(Stack->stack_ptr->value.startOfList, &Stack->stack_ptr->value, Stack);
    }
    else
    {
        addMinusAtEnd(Stack);
    }
}

//print first character on a list and then pop the list [>]
void printAndDelete(S* Stack)
{
    //check if stackmis empty  [cleaning] [first real double errorcheck]
    if (stackIsNull(Stack))
    {
        return;
    }

    //check if list is empty
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //read first character from a list
    cout << Stack->stack_ptr->value.startOfList->value;

    //remove list from the stack
    pop(Stack);
}

//detach first character from the list, append it to new list on top of the stack [$]
void detachAndAppend(S* Stack)
{
    //check if stackmis empty  [cleaning] [double errorcheck]
    if (stackIsNull(Stack))
    {
        return;
    }

    //check if list is empty
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //case with one element list
    if (Stack->stack_ptr->value.startOfList->nextListItem == nullptr)
    {
        char copy = Stack->stack_ptr->value.startOfList->value;
        pop(Stack);
        push(Stack);
        push(Stack);
        appendOnList(copy, Stack);
        return;
    }

    //case with more than one element list

    //get pointer to start of the list
    ListElement* startOfList = Stack->stack_ptr->value.startOfList;

    //get character from beggining of the list
    char firstChar = Stack->stack_ptr->value.startOfList->value;
    //change List beggining
    Stack->stack_ptr->value.startOfList = Stack->stack_ptr->value.startOfList->nextListItem;
    //delete first list element (detached)
    delete startOfList;


    push(Stack);
    appendOnList(firstChar, Stack);
}

//reads list as number from StackTop, pops and attaches new list with single character [']']
void readNumToChar(S* Stack)
{
    //error handling -> stack is empty  [cleaning] [double error]
    if (stackIsNull(Stack))
    {
        return;
    }

    //error handling -> StackTop is an empty list
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //read list from StackTop as number
    int A = readListToInt(Stack);
    
    //remove list from the stack
    pop(Stack);

    //create new list
    push(Stack);

    //append char of ASCII value of int A on list
    appendOnList(A, Stack);
}

//power function, returning integrers, used in powers of 10 [readchartonum helper]
int myTenPow(int base, int exponent, int counterOne) //[cleaning definfe]
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

//translate given int ex. 1234 to list 4->3->2->1. puts it on given stack ptr. [readCharToNum helper]
void translateIntegerToList(int translator, int iterator, ListElement* Listend)
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

    //check end of recursion, if translator == 0, whole number is translated
    if (translator == 0)
    {
        return;
    }

    //if not create new listElement and go forward
    ListElement* nextListElement = new ListElement;
    Listend->nextListItem = nextListElement;
    
    //recursion
    translateIntegerToList(translator, (iterator + 1), nextListElement);
}

//pop StackTop, put on stack list with number equal to ASCII of first character ['[']
void readCharToNum(S* Stack)
{
    //error handling -> stack is empty [cleaning] [double error]
    if (stackIsNull(Stack))
    {
        return;
    }

    //error handling -> StackTop is an empty list
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //get character from beggining of the list
    char A = Stack->stack_ptr->value.startOfList->value;

    //convert char to int
    int convertedChar = int(A);

    //remove list from top
    pop(Stack);

    //create new list;
    push(Stack);

    //put empty listelement at start of the list
    Stack->stack_ptr->value.startOfList = new ListElement;

    //put "number A" on top of the list [cleaning] [define]
    translateIntegerToList(convertedChar, 1, Stack->stack_ptr->value.startOfList);
}

//copy the list
void copyList(ListElement* copier, ListElement* destination)
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

    copyList(copier->nextListItem, destination->nextListItem);
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

//pop list, attach it's copy at end of the previous list [#]
void reAttach(S* Stack)
{
    //error Handling [cleaning] [double error handle]
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        return;
    }

    //get pointer to end of previous list
    ListElement* endOfPrevious = getEndListPointer(Stack->stack_ptr->previous_element->value.startOfList);

    //copy the current list to the end of previous list
    copyList(Stack->stack_ptr->value.startOfList, endOfPrevious);

    //pop the stacklist
    pop(Stack);
}

//read instruction pointer as number, attach this number as list at the end of the stack [~]
void putPtrValueOnStack(S* Stack)
{
    //get number of instruction
    int convert = Stack->ptr_value;

    //get new list on a stack
    push(Stack);

    //create new list
    Stack->stack_ptr->value.startOfList = new ListElement;

    //put "number A" on top of the list
    translateIntegerToList(convert, 1, Stack->stack_ptr->value.startOfList);
}

//if StackTop is empty or have only 0, replace with 1, otherwise, replace with 0 [!]
void logicalNegation(S* Stack)
{
    //check if StackTop is empty
    if (Stack->stack_ptr == nullptr)
    {
        push(Stack);
        appendOnList('1', Stack);
        return; 
    }

    //check if StackTop is an empty list
    if (Stack->stack_ptr->value.startOfList == nullptr)
    {
        appendOnList('1', Stack);
        return;
    }

    //check if StackTop list contains only '0'
    if (Stack->stack_ptr->value.startOfList->value == '0' && Stack->stack_ptr->value.startOfList->nextListItem == nullptr)
    {
        pop(Stack);
        push(Stack);
        appendOnList('1', Stack);
        return;
    }

    //otherwise put '0' on top of StackTop
    pop(Stack);
    push(Stack);
    appendOnList('0', Stack);
}

//==============================================================================================================================
//===========================================COMPARE FUNCTIONS==================================================================
//==============================================================================================================================

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

//check if list contains only zeroes, or zeroes and minus, returns 0 if so [compare] [true if zero]
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

    //recursion
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

//true if every next element of the list is zero, false otherwise [deleteZeroes helper]
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

//it will delete all zeroes to the end of the list [deleteZeroes helper]
void deleteZeroes(ListElement* thisList)
{
    //recursion end check if you are at the end of the list
    if (thisList->nextListItem->nextListItem != nullptr)
    {
        deleteZeroes(thisList->nextListItem);
    }

    ListElement* zeroEndList = thisList->nextListItem;
    thisList->nextListItem = nullptr;
    delete zeroEndList;
    //deleting only if next is nullptr
}

//iterate thru list, deleting streak of zeroes at the end [deleteZeroes helper]
void deleteZeroesListIterator(ListElement* thisList)
{   
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

//returns size of a list as integer number, size in declaration must be one [cleaning magic number]
int returnListSize(ListElement* thisList, int size)
{
    //if reached end of the list
    if (thisList->nextListItem == nullptr)
    {
        return size;
    }

    return returnListSize(thisList->nextListItem, (size + 1));
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
    //once again minuses are troublesome so we can remove them temporarly
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
    //both positive
    else
    {
        int result = CompareCharByCharHelper(topList, bottomList, 3);
        return result;
    }
}

//returns true if any list is empty or zero returns 1->toplist bigger  2-> bottom bigger  3->equal
int compareTwoListsMainError(ListElement* topList, ListElement* bottomList, S* Stack)
{
    //if both lists are equal, return 3
    if (Stack->stack_ptr->value.startOfList == nullptr && Stack->stack_ptr->previous_element->value.startOfList == nullptr)
    {
        return 3;
    }

    //if one of them is null
    if (Stack->stack_ptr->value.startOfList == nullptr && Stack->stack_ptr->previous_element->value.startOfList != nullptr)
    {
        return 2;
    }
    if (Stack->stack_ptr->value.startOfList != nullptr && Stack->stack_ptr->previous_element->value.startOfList == nullptr)
    {
        return 1;
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
    return 10;// [cleaning big magic number] 1,2,3,10, also is there a way for better
}

//main function for comparing two functions, [returns 1 if toplist is bigger, 2 if bottom one, 3 if equal], lists shouldn't be empty
//what about zeroes and empty lists warning: control may reach end of non-void function [-Wreturn-type]
int compareTwoListsMain(ListElement* topList, ListElement* bottomList)
{
    //[cleaning] [define]
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

//remove two list if bottom is non zero jump to instrction number of first list content
void instructionJump(S* Stack)
{
    //get number from first list
    int replacer = readListToInt(Stack);
    pop(Stack);

    //checking if there is no jump
    if (Stack->stack_ptr->value.startOfList == nullptr || isZero(Stack->stack_ptr->value.startOfList))
    {
        pop(Stack);

        Stack->ptr_value++;
        //break
        //there is some error here move it ti the main for now 
    }

    //jump
    pop(Stack);
    Stack->ptr_value = replacer;
}

//===========================================================================================================================================
//====================================== PLUS COMMAND "+" ===================================================================================
//===========================================================================================================================================

//error handling helper function, removes list beneath the stack
void popSecondStackField(S* Stack)
{
    StackField* secondField = Stack->stack_ptr->previous_element;

    //rearange stacktop pointer -> previous element is third  
    Stack->stack_ptr->previous_element = Stack->stack_ptr->previous_element->previous_element;

    //delete second stackfield
    if (secondField->value.startOfList != nullptr)
    {
        ListElement* listCleaner = secondField->value.startOfList;
        deleteStackContent(listCleaner);
    }

    delete secondField;
    Stack->stackCounter--;

}

//in case of one or two list being zero or empty, add Those lists accordingly [is this needed?] [maybe only the empty lists]    
bool plusCommandErrorHandling(S* Stack)
{
    //[cleaning] look at it for 5 seconds maybe zeroes are not needed at least
    // //test on stos ofc
    //case 1 both lists are empty
    if (Stack->stack_ptr->value.startOfList == nullptr && Stack->stack_ptr->previous_element->value.startOfList == nullptr)
    {
        //multiplication of two lists will be one empty list, we just need to delete one
        pop(Stack);
        return true;
    }

    //case 2: top list is empty
    if (Stack->stack_ptr->value.startOfList == nullptr && Stack->stack_ptr->previous_element->value.startOfList != nullptr)
    {
        //delete top list, bottom one is result
        pop(Stack);
        return true;
    }

    //case 3: bottom list is empty
    if (Stack->stack_ptr->value.startOfList != nullptr && Stack->stack_ptr->previous_element->value.startOfList == nullptr)
    {
        popSecondStackField(Stack);
        return true;
    }

    //case 4: both lists are zero
    if ((isZero(Stack->stack_ptr->value.startOfList) == 1) && (isZero(Stack->stack_ptr->previous_element->value.startOfList) == 1))
    {
        //adding two empty lists will be empty list
        pop(Stack);
        return true;
    }

    //case 5: top list is zero
    if ((isZero(Stack->stack_ptr->value.startOfList) == 1) && (isZero(Stack->stack_ptr->previous_element->value.startOfList) == 0))
    {
        //adding two empty lists will be empty list
        pop(Stack);
        return true;
    }

    //case 6: bottom list is zero
    if ((isZero(Stack->stack_ptr->value.startOfList) == 0) && (isZero(Stack->stack_ptr->previous_element->value.startOfList) == 1))
    {
        //adding two empty lists will be empty list
        popSecondStackField(Stack);
        return true;
    }



    return false;
}

//end of adding carry handle in the bigger list
void carryHandleBiggerList(ListElement* biggerList, int carry)
{
    //cleaning defines
    //if our value + carry > 9
    if ((biggerList->value - 48) + carry > 9)
    {
        biggerList->value = (((biggerList->value - 48) + carry) % 10) + 48;
        carry = 1;
    }
    else
    {
        biggerList->value = biggerList->value + carry;
        //no carry, we can return
        return;
    }

    if (carry == 1 && biggerList->nextListItem == nullptr)
    {
        biggerList->nextListItem = new ListElement;
        biggerList->nextListItem->value = '0';
        biggerList->nextListItem->nextListItem = nullptr;
    }

    carryHandleBiggerList(biggerList->nextListItem, carry);
}


//adding two positive numbers function
void addingPositives(ListElement* biggerList, ListElement* smallerList, int carry)
{
    //adding current stackElements -> checking if there is number to carry
    //carry handle
    if ((biggerList->value - 48) + (smallerList->value - 48) + carry > 9)
    {
        //biggerlist will have modulo 10 of current num
        biggerList->value = (((biggerList->value - 48) + (smallerList->value - 48) + carry) % 10) + 48;
        carry = 1;
    }
    else
    {
        biggerList->value = biggerList->value - 48 + smallerList->value + carry;
        carry = 0;
    }

    //if we carry and list is empty, add new field
    if (carry == 1 && biggerList->nextListItem == nullptr)
    {
        biggerList->nextListItem = new ListElement;
        biggerList->nextListItem->value = '0';
        biggerList->nextListItem->nextListItem = nullptr;
    }

    //when do we end recursion -> smaller.next == nullptr
    //but we have to handle carry then
    if (smallerList->nextListItem == nullptr)
    {
        //if there is carry [wont work] e.g. 99999999+ 1
        if (carry)
        {
            carryHandleBiggerList(biggerList->nextListItem, carry);
            //helper function: 99% needed
            //biggerList->nextListItem->value = carry + 48; //nah wont be working
        }

        return;
    }

    addingPositives(biggerList->nextListItem, smallerList->nextListItem, carry);
}

//cleaning the stack after [+], removing not needed list
void addingStackClean(ListElement* biggerList, S* Stack)
{
    //if the "bottom list" became top one, remove top
    if (biggerList == Stack->stack_ptr->previous_element->value.startOfList)
    {
        pop(Stack);
    }
    else //if the top is bigger, remove list underneath
    {
        popSecondStackField(Stack);
    }
}

//handling the borrowing from only one list, like 1000000000 - 1 (borrowing only from one list)
void substractionHelperBiggerList(ListElement* biggerList, int borrow)
{
    //if borrowing is needed
    if (biggerList->value - borrow - 48 < 0)
    {
        biggerList->value = (biggerList->value - 1 + 10);
        borrow = 1;
    }
    //if borrowing is not needed
    else
    {
        biggerList->value = biggerList->value - 1;
        return;
    }

    //there is no need for errorchecking or anything like that, because we are always substracting bigger - smaller
    substractionHelperBiggerList(biggerList->nextListItem, borrow);
}

//function substracting bigger-smaller
void substractionHelper(ListElement* biggerList, ListElement* smallerList, int borrow)
{
    //substracting current listBlocks, is carry needed?
    //potential bugger -> what if 
    if ((biggerList->value - smallerList->value - borrow) < 0)
    {
        biggerList->value = biggerList->value - smallerList->value - borrow + 10 + 48;
        borrow = 1;
    }
    else
    {
        biggerList->value = biggerList->value - smallerList->value - borrow + 48;
        borrow = 0;
    }

    //end of substraction
    if (smallerList->nextListItem == nullptr)
    {
        if (borrow)
        {
            substractionHelperBiggerList(biggerList->nextListItem, borrow);
        }
        return;
    }

    //recursion
    substractionHelper(biggerList->nextListItem, smallerList->nextListItem, borrow);
}

void handlesubtraction(S* Stack)
{
    //we already know that one list is negative and second one is positive, let's specify which one
    ListElement* negativeList;
    if (isNegative(Stack->stack_ptr->value.startOfList) == 1)
    {
        negativeList = Stack->stack_ptr->value.startOfList;
    }
    else
    {
        negativeList = Stack->stack_ptr->previous_element->value.startOfList;
    }

    //lets remove the negative sign from bigger list [for now]
    removeMinus(negativeList);

    //compare the lists -> we will substract [bigger - smaller]
    ListElement* bigger;
    ListElement* smaller;

    if (compareTwoListsMain(Stack->stack_ptr->value.startOfList, Stack->stack_ptr->previous_element->value.startOfList) == 1)
    {
        bigger = Stack->stack_ptr->value.startOfList;
        smaller = Stack->stack_ptr->previous_element->value.startOfList;
    }
    else
    {
        bigger = Stack->stack_ptr->previous_element->value.startOfList;
        smaller = Stack->stack_ptr->value.startOfList;
    }

    //do the actual substraction
    substractionHelper(bigger, smaller, 0);

    //stack cleaning!!!
    if (bigger == Stack->stack_ptr->value.startOfList)
    {
        popSecondStackField(Stack);
    }
    else
    {
        pop(Stack);
    }

    //add minus if needed ex. we did 1-999
    if (bigger == negativeList && (isZero(bigger) == 0))
    {
        addMinus(bigger);
    }

    //remove leading zeroes
    deleteZeroesMain(bigger);
}


//add two list from top of the stack [main] [+]
//notes for future optimalisation:
//error handle for zeroes might be not needed if everything works
//but check adding 0, 0- to positive and negative numbers
void addStackTopLists(S* Stack)
{
    //error handling -> adding of zero and empty lists
    if(plusCommandErrorHandling(Stack))
    {
            return;
    }

    //clean the data -> remove last minuses
    deleteZeroesMain(Stack->stack_ptr->value.startOfList);
    deleteZeroesMain(Stack->stack_ptr->previous_element->value.startOfList);


    //determine which list is bigger -> easier adding [returns 1 if toplist is bigger, 2 if bottom one, 3 if equal]
    //compareTwoListsMain(ListElement* topList, ListElement* bottomList)

    //declare the pointers to the lists
    //see if this will be needed, maybe we can also dodge that
    ListElement* bigger;
    ListElement* smaller;
    if (compareTwoListsMain(Stack->stack_ptr->value.startOfList, Stack->stack_ptr->previous_element->value.startOfList) == 1)
    {
        bigger = Stack->stack_ptr->value.startOfList;
        smaller = Stack->stack_ptr->previous_element->value.startOfList;
    }
    else
    {
        bigger = Stack->stack_ptr->previous_element->value.startOfList;
        smaller = Stack->stack_ptr->value.startOfList;
    }
    
    //case 1: adding two positive numbers
    //todo: organise stack, there is two lists currently
    if ((isNegative(Stack->stack_ptr->value.startOfList) == 0) && (isNegative(Stack->stack_ptr->previous_element->value.startOfList) == 0))
    {
        addingPositives(bigger, smaller, 0);
        //helper real adding
        //rearange the stack
        addingStackClean(bigger, Stack);
        return;
    }

    //case 2: "adding" two negative numbers
    //important -> do the comparison after the changing or change the bigger smaller
    //one is cleaner [!!!] bug!
    //second one more efficient
    //for now we changed , seek online which better, add coments
    if ((isNegative(Stack->stack_ptr->value.startOfList) == 1) && (isNegative(Stack->stack_ptr->previous_element->value.startOfList) == 1))
    {
        //step one remove minuses
        removeMinus(Stack->stack_ptr->value.startOfList);
        removeMinus(Stack->stack_ptr->previous_element->value.startOfList);
        
        //was bigger smaller -> switch order because how negative numbers work
        addingPositives(smaller, bigger, 0);
        //helper real adding
        //rearange the stack
        //was bigger
        addingStackClean(smaller, Stack);

        //negate stacktop -> switch order because how negative numbers work
        addMinus(Stack->stack_ptr->value.startOfList);

        return;
    }

    //case 3: "adding" negative and positive number (every other case)
    //idea of always minusing the smaller from the bigger like 9999-1 even when it's 1-9999

    //get to know which one is "bigger" in absolute value way
    handlesubtraction(Stack);
    //remove minuses also
    //onlyone is negative so we have to check that ony once
}


int main()
{
    //initialize stack
    S Stack;
    initializeStack(&Stack);
    //loading all program instructions
    cin >> Stack.program_mem;

    //iterating through all program instructions
    while (Stack.mem_ptr[Stack.ptr_value] != '\0')
    {
        
        switch (Stack.mem_ptr[Stack.ptr_value])
        {
            case '\'':
            {
                push(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '&':
            {
                int stackCpy = 0; 
                StackField* currentStackField = Stack.stack_ptr;   
                show(currentStackField, stackCpy, &Stack);
                Stack.ptr_value++;
                break;
            }

            case ':':
            {
                copyStackTop(&Stack);

                Stack.ptr_value++;
                break;
            }

            case ';':
            {
                switchLists(&Stack);
                Stack.ptr_value++;
                break;
            }

            case ',':
            {
                pop(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '@':
            {
                popAndSwitch(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '.':
            {
                readAndAppend(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '^':
            {
                absoluteValue(Stack.stack_ptr->value.startOfList, &Stack.stack_ptr->value, &Stack); //error
                Stack.ptr_value++;
                break;
            }

            case '-':
            {
                negate(Stack.stack_ptr->value.startOfList, &Stack);
                Stack.ptr_value++;
                break;
            }

            case '>':
            {
                printAndDelete(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '$':
            {
                detachAndAppend(&Stack);
                Stack.ptr_value++;
                break;
            }

            case ']':
            {
                readNumToChar(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '[':
            {
                readCharToNum(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '#':
            {
                reAttach(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '~':
            {
                putPtrValueOnStack(&Stack);
                Stack.ptr_value++;
                break;
            }

            case '!':
            {
                logicalNegation(&Stack);
                Stack.ptr_value++;
                break;
            }

            //very easily new function [cleaning]
            case '=':
            {
                
                if (compareTwoListsMainError(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList, &Stack) != 10)
                {
                    if (compareTwoListsMainError(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList, &Stack) == 3)
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('1', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                    else
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('0', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                }
                else 
                {
                    //clean lists
                    deleteZeroesMain(Stack.stack_ptr->value.startOfList);
                    deleteZeroesMain(Stack.stack_ptr->previous_element->value.startOfList);

                    if (compareTwoListsMain(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList) == 3)
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('1', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                    else
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('0', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                }
                    
                

                Stack.ptr_value++;
                break;


            }

            //very easily new function [cleaning]
            case '<':
            {
                if (compareTwoListsMainError(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList, &Stack) != 10)
                {
                    if (compareTwoListsMainError(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList, &Stack) == 1)
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('1', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                    else
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('0', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                }
                else
                {
                    //clean lists
                    deleteZeroesMain(Stack.stack_ptr->value.startOfList);
                    deleteZeroesMain(Stack.stack_ptr->previous_element->value.startOfList);

                    if (compareTwoListsMain(Stack.stack_ptr->value.startOfList, Stack.stack_ptr->previous_element->value.startOfList) == 1)
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('1', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                    else
                    {
                        pop(&Stack);
                        pop(&Stack);
                        push(&Stack);
                        appendOnList('0', &Stack);
                        Stack.ptr_value++;
                        break;
                    }
                }



                Stack.ptr_value++;
                break;
            }

            case '?':
            {
                //instructionJump(&Stack);
                //get number from first list
                int replacer = readListToInt(&Stack);
                pop(&Stack);

                //checking if there is no jump
                if (Stack.stack_ptr->value.startOfList == nullptr || isZero(Stack.stack_ptr->value.startOfList))
                {
                    pop(&Stack);

                    Stack.ptr_value++;
                    break;
                    //there is some error here move it ti the main for now 
                }

                //jump
                pop(&Stack);
                Stack.ptr_value = replacer;
                break;
            }

            case '+':
            {
                addStackTopLists(&Stack);
                Stack.ptr_value++;
                break;
            }
            default:
            {
                appendOnList(Stack.mem_ptr[Stack.ptr_value], &Stack);
                Stack.ptr_value++;
                break;
            }
        }
    }
}
