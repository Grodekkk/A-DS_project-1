#include <iostream>
#include <math.h>
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
*/
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
        cout << "emptystack" << endl;
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

    //remove that list/number from stack
    pop();

    //create new stack field, again List is part of StackField -> also initiated
    StackField* newField = new StackField;
    newField->value.startOfList = new ListElement;

    //start of list points to nowhere
    newField->value.startOfList->nextListItem = nullptr;

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


int main()
{
    //loading all program instructions
    cin >> program_mem;

    //iterating through all program instructions
    while (mem_ptr[ptr_value] != '\0')
    {
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
        case '-':
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
