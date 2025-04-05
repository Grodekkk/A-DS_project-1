#include <iostream>

using namespace std;

//program memory and instruction pointer
char program_mem[20000];
char *mem_ptr = program_mem;
int ptr_value = 0;

//===================================== STACK DATA & FUNCTIONS ============================================================================
//this struct is a single stack element
struct StackField 
{
    int value;
    StackField* previous_element;                       //pointer to a stack element "bellow" this element
};

StackField* stack_ptr = nullptr;                        //points to top of a stack
                                                        //at the beggining no stack -> points nowhere

void push(int value)                                    //*& means the adress of pointer will change
{
    StackField* newField = new StackField;              //we create new stackfield and name it "newField" [TEMPORALY]
    newField->value = value;                            
    if (stack_ptr == nullptr)
    {
        newField->previous_element = nullptr;           //first element of stack doesnt have any element below
    }
    else
    {
        newField->previous_element = stack_ptr;
    }
    stack_ptr = newField;
}

void show()
{
    cout << stack_ptr->value << "<-- top stack value]]" << endl;
}

//==================================== LIST DATA & FUNCTIONS==================================================================











int main()
{
//loading all program instructions
    cin >> program_mem;
    
//iterating through all program instructions
    while (mem_ptr[ptr_value] != '\0')
    {
        switch(mem_ptr[ptr_value])
        {
        case '.':
            int tempNotList;
            cin >> tempNotList;
            push(tempNotList);
            ptr_value++;
            break;
        case '$':
            show();
            ptr_value++;
            break;
        case '%':
            cout << ptr_value << " ==procent operation== " << endl;
            ptr_value++;
            break;
        }
            

    }
}


