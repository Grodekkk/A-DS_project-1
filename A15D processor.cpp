#include <iostream>
#include <math.h>
// test 1 63/90 testow
using namespace std;

//==============TO DO LIST=================================================
/*
* GENERAL CODE CLEANING, THIS IS A MESS
* done ;-)






*/
//==============================================================================

//program memory and instruction pointer
char program_mem[20000];
char *mem_ptr = program_mem;
int ptr_value = 0;

struct ListElement;

//==================================== LIST DATA & FUNCTIONS==================================================================
struct List
{
    ListElement* startOfList;           //pointer to 1st position on the list
};

struct ListElement
{
    char value;
    ListElement* nextListItem;
};




//===================================== STACK DATA & FUNCTIONS ============================================================================
//this struct is a single stack element
    
int stackCounter = -1;                                   //shows current elements on stack, no elements and one elements count as zero need to be aware of that
struct StackField 
{
    List value;
    StackField* previous_element;                       //pointer to a stack element "bellow" this element
};

StackField* stack_ptr = nullptr;                        //points to top of a stack
                                                        //at the beggining no stack -> points nowhere


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

//need fixing with lists, checking if works correctly
void push(List* newList)
{
    StackField* newField = new StackField;              //we create new stackfield and name it "newField" [TEMPORALY]
    newField->value = *newList;//!!!  [might be incorrect]                          
    if (stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           //first element of stack doesnt have any element below
    }
    else
    {
        newField->previous_element = stack_ptr;
    }
    stack_ptr = newField;
    newField->value.startOfList = nullptr;
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
    if (stack_ptr == nullptr)//error handling
    {
        cout << "emptystack" << endl;
        return;
    }

    ListElement* listIterator = currentStackField->value.startOfList; //list iterator start at beggining of list at current stack level
    
    if (currentStackField->previous_element == nullptr)
    {
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
        
        //print current list
        currentStackField = currentStackField->previous_element;        //change pointer to one layer lower
        // ++ doesn't work need to do this with (ctr+1) as func parameter
        show(currentStackField, (Counter+1));                                        //do it once again until there is nothing under

        if (listIterator != nullptr)
        {
            cout << Counter << ": ";
            printList(listIterator);
        }
        else
        {
            cout << Counter << ": ";
            cout << endl;
        }

    }
    //everything works by far, we just dont have the "recursion here" 

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

//put a exact copy of list from top on top of an stack
void copyStackTop()
{
    //create new list
    List* newList = new List;
    newList->startOfList = new ListElement;

    //create new stack field
    StackField* newField = new StackField;              //we create new stackfield and name it "newField" [TEMPORALY]
    newField->value = *newList;//!!!  [might be incorrect] 

    //getting pointers of our stackfield
    if (stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           //first element of stack doesnt have any element below
    }
    else
    {
        newField->previous_element = stack_ptr;
    }
    
    
    //getting values of our stackfield, should do the same check-in here as upward ^^^
    //check the push if it attaches something
    
    //list copying mechanic, maybe another function with recursion
    ListElement* startOfList = newList->startOfList;
    ListElement* startOfStackList = stack_ptr->value.startOfList; //seems problematic [tuesday illness day]
    copyStackTopHelper(startOfList, startOfStackList);
    //after everything move stack pointer to the new field



    stackCounter++;
    stack_ptr = newField;
}

//switch top and below lists in places
void switchLists()
{
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
    //change pointer to top of the stack to element below
    StackField* cleaner = stack_ptr;
    stack_ptr = stack_ptr->previous_element;

    ListElement* listCleaner = cleaner->value.startOfList;
    deleteStackContent(listCleaner);
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

    return sumUpList(listSearched->nextListItem, (powerOfTen +1), (returner));
}

//returns contents of a list as an integer [main]
int readListToInt()
{
    
    int listSize = getListCount(stack_ptr->value.startOfList, 1); //not used because of misinterpretation of list
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

    //copy the number-ish pos of stack to the top
    
    
    //create new list
    List* newList = new List;
    newList->startOfList = new ListElement;

    //create new stack field
    StackField* newField = new StackField;              
    newField->value = *newList;

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

    //FIX START
    //list copying 
    ListElement* startOfList = newList->startOfList;                    //this is correct
    // replace stack_ptr->value.startOfList to something else
    ListElement* startOfStackList = numPosition->value.startOfList;       //this need to be our i-sh field
    copyStackTopHelper(startOfList, startOfStackList);
    
    //FIX STOP


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



int main()
{
//loading all program instructions
    cin >> program_mem;
    
//iterating through all program instructions
    while (mem_ptr[ptr_value] != '\0')
    {
        switch(mem_ptr[ptr_value])
        {
        
            case '\''://push empty list on the stack
                {
                    List* newList = new List;
                    newList->startOfList = nullptr;         //list is empty so it points nowhere
                    push(newList);
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
