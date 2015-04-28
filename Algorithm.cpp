/* Developer: Shiwei Huang
 * Purpose: A program that simulates a calculator that can handle +, -, *, /, and ^(exponentiation) with floating point operands. No parentheses may be input.
 * Input: A one line calculation such as the following: 5+3.3*8-9 =
 * Output: Display simply the answer with 3 decimal places.
 * Note: 
 * 1) ^ (exponentiation) has the highest precedence, followed by *,/ (same precedence), and finally +,- (same precedence)
 * 2) Stacks must be used to determine the answer. This assignment also requires to implement the stack using a linked-list
 */


#include <iostream>
#include <assert.h>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <math.h>  

using namespace std;


template < class Type >
struct nodeType { //linked-list struct;
	Type info;
	nodeType < Type > *link;
};

template < class Type >
class linkedStackType { //Stack class;
public:
	bool isEmptyStack (); 
	void push ( Type newItem );
	Type top ();
	void pop ();
	linkedStackType (); 

private:
	nodeType < Type > *stackTop;
};

// constructor
template < class Type >
linkedStackType < Type > :: linkedStackType () { 
	stackTop = NULL;
}

//function to determine whether the stack is empty.
//Precondition: stack exists;
//Postcondition: Returns true if the stack is empty.
//Returns false if the stack is not empty.
template < class Type >
bool linkedStackType < Type > :: isEmptyStack () {
	if ( stackTop == NULL ) {
		return true;
	}

	else {
		return false;
	}
}

//Function to add newElement to the stack.
//Precondition: stack exists;
//Postcondition: newElement is added to the stack. 
template < class Type >
void linkedStackType < Type > :: push ( Type newElement ) {
	nodeType < Type > *newNode;
	newNode = new nodeType < Type > ;

	if ( stackTop == NULL ) { // Insertion when stack is empty;
		newNode -> info = newElement;
		newNode -> link = NULL;
		stackTop = newNode;
	}

	else { // Insertion when stack is not empty;
		newNode -> info = newElement;
		newNode -> link = stackTop;
		stackTop = newNode;
	}
}

//Function to return the top element of the stack;
//Precondition: The stack exists and stack is not empty
//Postcondition: If the stack is empty, this function won't do anything;
// If the function is not empty, the top element of the stack will be returned. 
template < class Type >
Type linkedStackType < Type > :: top () {
	if ( stackTop != NULL ) {
		return stackTop -> info;
	}
}

//Function to remove the top element of the stack;
//Precondition: The stack exists and is not empty;
//Postcondition: The top element from the stack is removed;
template < class Type >
void linkedStackType < Type > :: pop () {
	nodeType < Type > *temp;
	if ( stackTop != NULL ) {
		temp = stackTop;
		stackTop = stackTop -> link;
		delete temp;
	} 

	else {
		cout << "Cannot remove from an empty stack." << endl;
	}
}


class compute {
	linkedStackType < float > floatStack; //floatStack stores all floating points;
	linkedStackType < char > charStack; //charStack stores '+','-','*','/','^'

private:
	float myFloat;
	char myChar;
public: 
	void evaluateExp (); // evaluates my incoming character and floating number;
	void displayAns (); // displays my final answer;

};


void compute :: evaluateExp () {
	cout << "Type in equation:" << endl;
	cin >> myFloat;
	cin >> myChar;

	while ( myChar != '=' ) {
		floatStack.push ( myFloat ); // when seeing floats, directly push floats in my floatStack;
		if ( charStack.isEmptyStack() ) { // push character into charStack if that's the first character;
			charStack.push ( myChar );
		}

		else {
			if (( myChar == '+' ) || ( myChar =='-' )) { // "+" || "-" has the same precedence; when incoming character are + or -, always empty the charStack;
				while (!charStack.isEmptyStack()) {
					float right = floatStack.top ();
					floatStack.pop ();
					float left = floatStack.top ();
					floatStack.pop ();
					if ( charStack.top() == '+' ) {
						float ans = left + right;
						charStack.pop();
						floatStack.push (ans);
					}

					if ( charStack.top() == '-' ) {
						float ans = left - right;
						charStack.pop();
						floatStack.push (ans);
					}

					if ( charStack.top() == '*' ) {
						float ans = left * right;
						charStack.pop();
						floatStack.push (ans);
					}

					if ( charStack.top() == '/' ) {
						float ans = left / right;
						charStack.pop();
						floatStack.push (ans);
					}

					if ( charStack.top() == '^' ) {
						float ans = pow ( left, right);
						charStack.pop ();
						floatStack.push ( ans);
					}
				}//while
				charStack.push ( myChar );
			}//if ( myChar == '+'||'-' )

			if (( myChar == '*' ) || ( myChar == '/' )) { 
				if ( ( charStack.top () == '+' ) || ( charStack.top () == '-' ) ) { //since * or / has higher precedence than + or -, always push when charStack top is + or -
					charStack.push ( myChar);
				}
				else { 
						while ( !charStack.isEmptyStack() ) { // when the incoming character is * or /, (1) empty the stack until I see + or - (2) or empty the stack when my stack is empty;
							if ( ( charStack.top() == '+' ) || ( charStack.top() == '-' ) ) { 
								break;
							}
							else {
								if ( charStack.top() == '*' ) {
									float right = floatStack.top ();
									floatStack.pop ();
									float left = floatStack.top ();
									floatStack.pop ();
									float ans = left * right;
									charStack.pop();
									floatStack.push (ans);
								}

								if ( charStack.top() == '/' ) {
									float right = floatStack.top ();
									floatStack.pop ();
									float left = floatStack.top ();
									floatStack.pop ();
									float ans = left / right;
									charStack.pop();
									floatStack.push (ans);
								}

								if ( charStack.top() == '^' ) {
									float right = floatStack.top ();
									floatStack.pop ();
									float left = floatStack.top ();
									floatStack.pop ();
									float ans = pow ( left, right);
									charStack.pop ();
									floatStack.push ( ans);
								}

							} //else
						} //while
					charStack.push ( myChar );
				} //else
			} //if myChar == '*' || '/'

			if ( myChar == '^' ) { 
				if ( charStack.top () != '^' ) { // always push ^ when the top of my charStack character is not ^
					charStack.push ( myChar);
				}
				else { // otherwise, pop my top character from my charStack; 
					float right = floatStack.top ();
					floatStack.pop ();
					float left = floatStack.top ();
					floatStack.pop ();
					float ans = pow ( left, right);
					charStack.pop();
					floatStack.push (ans);
					charStack.push ( myChar );
				}
			}// if ( myChar == '^')

		}//else
		cin >> myFloat;
		cin >> myChar;
	} // end while;

} //compute:: evaluateExp()

void compute :: displayAns () {
	floatStack.push ( myFloat ); // in order to solve "reading two token at one time" problem; push (myFloat) is to push my last float before the '=' sign;

	while ( !( charStack.isEmptyStack() ) ) { // do the calculation from postfix to answer until my character stack is empty;
		float right = floatStack.top ();
		floatStack.pop ();
		float left = floatStack.top ();
		floatStack.pop ();

		if ( charStack.top() == '+' ) {
			float ans = left + right;
			charStack.pop();
			floatStack.push (ans);
		}

		if ( charStack.top () == '-' ) {
			float ans = left - right;
			charStack.pop();
			floatStack.push (ans);

		}

		if ( charStack.top () == '*' ) {
			float ans = left * right;
			charStack.pop();
			floatStack.push (ans);
		}

		if ( charStack.top() == '/' ) {
			float ans = left / right;
			charStack.pop();
			floatStack.push (ans);
		}

		if ( charStack.top() == '^' ) {
			float ans = pow (left, right);
			charStack.pop();
			floatStack.push (ans);
		}

	} // end while charStack.isEmptyStack();

	cout << setprecision(4) << floatStack.top() << endl; // cout my last floating number;
}


int main () {
	
	compute expression;
	expression.evaluateExp ();
	expression.displayAns ();

	return 0;
}
