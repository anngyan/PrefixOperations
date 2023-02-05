#include <iostream>

//Function to get expression length
int expLength(char exp[]) {
    int expLength = 0;
    int i = 0;
    while(exp[i] != '\0') {
        ++expLength;
        ++i;
    }
    return expLength;
}

//A function that tells which operator has a greater priotiry
int precendence(char c) {
    if(c == '*') {
        return 2;
    }
    if(c == '+') {
        return 1;
    }
    return 0;
}

//Checking if Char Stack is empty
bool empty(char a[], int top) {
    return (top == 0 && a[top] == '\0');
}

//Checking if Int Stack is empty
bool Iempty(int a[], int top) {
    return (top == 0 && a[top] == 0);
}

//Pop function for Char Stack
void pop(char a[], int& top) {
    if(empty(a, top)) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }
    a[top] = '\0';
    --top;
}

//Pop function for Int Stack
void Ipop(int a[], int& top) {
    if(Iempty(a, top)) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }
    a[top] = 0;
    --top;
}

//Push function for Char Stack
void push(char a[], int& top, char c) {
    ++top;
    a[top] = c;
}

//Push function for Int Stack
void Ipush(int a[], int& top, int c) {
    ++top;
    a[top] = c;
}

//Function that checks if the character is an operand
bool isOperand (char c) 
{
	return (c >= '0' && c <= '9');
}

//Function that checks if the character is an operator
bool isOperator (char c) 
{
	return (c == '+' || c == '*');
}

int main() {

    //Initializing char array
    char exp[100] = {0};

    //Inputing the expression, and checking if it's valid
    std::cout << "Input the expression(one-digit numbers, or *,+ operators): ";
    bool validExp = false;
    while(validExp == false) {
        std::cin.getline(exp, 100);
        int i = 0;
        while(exp[i] != '\0') {
            if(!isOperand(exp[i]) && !isOperator(exp[i])) {
                std::cout << "Invalid expression. Input again: ";
                break;
            }
            ++i;
        }
        if(i == expLength(exp)) {
            validExp = true;
        }
    }
    



    std::cout << std::endl;

    //Initializing a stack and an array for our prefix expression
    char Stack[100] = {0};
    int top = 0;
    char prefixExp[100] = {0};
    int j = 0;

    
    //Iterating through the expression from reverse order
    for (int i = expLength(exp) - 1; i >= 0; --i) {
        
        //If the character is an operand, push it to prefixExp
        if(isOperand(exp[i])) {
            push(prefixExp, j, exp[i]);
        }

        //If the character is an operator, push it to Stack
        else if(isOperator(exp[i])) {
            //Just push if Stack is empty
            if(empty(Stack, top)) {
                push(Stack, top, exp[i]);
            }
            else if(!empty(Stack, top)) {
                //If the top of Stack has lower or same precendence, push the operator to Stack
                if(precendence(exp[i]) >= precendence(Stack[top])) {
                    push(Stack, top, exp[i]);
                }
                //If the top of Stack has higher precendence, push it to prefixExp 
                //and pop from Stack till it's empty or the top has lower or same precendence
                else {
                    while((precendence(exp[i]) < precendence(Stack[top])) || !empty(Stack, top)) {
                        push(prefixExp, j, Stack[top]);
                        pop(Stack, top);
                    }
                    push(Stack, top, exp[i]); //push the character to Stack after the loop ends

                } 
            }
        }
    }

    //Emptying the Stack to prefixExp
    while(!empty(Stack, top)) {
        push(prefixExp, j, Stack[top]);
        pop(Stack, top);
    }
    
    //Outputing the result in reverse order
    std::cout << "Prefix representation: ";
    for(int i = j; i > 0; --i) {
        std::cout << prefixExp[i];
    }

    std::cout << std::endl;

    //Initializing a Stack for integers
    int intStack[100] = {0};
    int intTop = 0;

    //Iterating through our prefix expression
    for(int i = 1; i <= j; ++i) {
        //If the character is operand Push it to intStack
        if(isOperand(prefixExp[i])) {
            Ipush(intStack, intTop, (prefixExp[i] - '0')); 
        }
        else {
            //Initializing last two operands from intStack
            int operand1 = intStack[intTop];
            Ipop(intStack, intTop);
            int operand2 = intStack[intTop];
            Ipop(intStack, intTop);

            //Doing the calculations depending on character and pushing the result to intStack
            if(prefixExp[i] == '+') {
                Ipush(intStack, intTop, operand1 + operand2);
            }
            else if(prefixExp[i] == '*') {
                Ipush(intStack, intTop, operand1 * operand2);
            }
        }
    }

    //Outputing the top of intStack as the result of our expression
    std::cout << std::endl;
    std::cout << "Result of the expression: " << intStack[intTop];
    return 0;
}