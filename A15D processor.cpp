#include <iostream>

using namespace std;

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
    
int stackCounter = 0;                                   //shows current elements on stack, no elements and one elements count as zero need to be aware of that
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
    stackCounter++;
}

void printList(ListElement* listIterator)
{
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

//this will be '&' function, print entire content of stack.
void show(StackField* currentStackField)
{
    //cout << stack_ptr->value << "<-- top stack value]]" << endl;
    if (stack_ptr == nullptr)
    {
        cout << "emptystack" << endl;
        return;
    }
    //todo number od the stack

    //this propably cannot be here
    

    //is it correct place for this???
    ListElement* listIterator = currentStackField->value.startOfList; //list iterator start at beggining of list at current stack level
    if (currentStackField->previous_element == nullptr)
    {
        printList(listIterator);            //print list on this stack field
        return;
    }
    else
    {
        printList(listIterator);                                        //print current list
        currentStackField = currentStackField->previous_element;        //change pointer to one layer lower
        show(currentStackField);                                        //do it once again until there is nothing under

    }
    //everything works by far, we just dont have the "recursion here" 
    
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
        
            case '`'://push empty list on the stack
                {
                    List* newList = new List;
                    newList->startOfList = nullptr;         //list is empty so it points nowhere
                    push(newList);
                    ptr_value++;
                    break;
                }
               
        
            case '&':
                {
                    StackField* currentStackField = stack_ptr;   //our inside pointer that will iterate thru all stack
                    show(currentStackField);
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
                

        }
            

    }
}


