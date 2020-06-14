#include <iostream>
#include <string>
#include <cstddef>
#include "expr_eval.h"
#include "mystack.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <cctype>
#include <math.h>

using namespace std;

bool error;
 
// returns true if op2 has lower or equal priority than op1, false otherwise
bool precedence(char op1, char op2)   
{
    	switch (op1) 
	{
        	case '(': return false;
        	case '-': return op2 == '-';
        	case '+': return op2 == '-' || op2 == '+';
        	case '*': return op2 != '/';
                case '/': return op2 != '*';
		case '^': return op2 != '(';
		case 's': return op2 != '(';
		case 'c': return op2 != '(';
		case 't': return op2 != '(';
		case 'l': return op2 != '(';
        	default : error = true; return false;
    	}
}
 
stack < char > operators;
stack < int > operands;
 
// perform the operation 'op' on the two operands on top of the stack
void operation(char op) 
{
	if(operands.size() < 2)
	{
        	error = true; 
		return;
	}
    	int op2 = operands.top(); operands.pop();
    	int op1 = operands.top(); operands.pop();
    	switch(op)  
	{
        	case '+': operands.push(op1 + op2); break;
        	case '-': operands.push(op1 - op2); break;
        	case '*': operands.push(op1 * op2); break;
        	case '/': operands.push(op1 / op2); break;
        	case '^': operands.push(pow(op1,op2));break;
		case 's': operands.push(sin(op2));break;
		case 'c': operands.push(cos(op2));break;
		case 't': operands.push(tan(op2));break;
		case 'l': operands.push(op2);break;
		default : error = true; return;
    	}
}

double evaluate(string exp, double x)
{
	char *p;
	int len = strlen(exp);
        if(len == 0)
		getchar();continue;
        exp[len] = ' '; 
	exp[len + 1] = ')'; 
	exp[len + 2] = '\0';
        error = false;
        operators.push('(');
 
        p = strtok(exp, " ");
        while(p && !error)
	{
		if(isdigit(p[0]))
                	operands.push(atoi(p));
            	else
		{
			switch(p[0])    
			{
                		case '(' :  operators.push('('); break;
                		case ')' :  while (!operators.empty() && !error && operators.top() != '('){
				operation(operators.top()); 
				operators.pop();
			    }
			    if (!operators.empty())
				operators.pop();
			    else
				error = true;
			    break;
                		default  :  while(!operators.empty() && !error && hasLowerPriority(operators.top(), p[0])) {
                                operation(operators.top()); operators.pop();
                            }
                            operators.push(p[0]);
            		}
            		p = strtok(NULL, " ");
        	}
        	if(error || !operators.empty() || operands.size() != 1) 
		{
            		printf("ERROR\n");
            		while(!operands.empty())
                		operands.pop();
            		while(!operators.empty())
                		operators.pop();
        	} 
		else    
		{
            		printf("%d\n", operands.top()); 
			operands.pop();
        	}
	}
}

int main(int argc, char** argv)
{
	string exp[1000];
	int len, double x;

    	while(getline(cin,exp))
	{
		len = strlen(exp);
		size_t found = exp.find_first_of("x");
		if(found==npos)
			evaluate(exp, -1.0);
		else
		{
			x = exp.substr(exp.find_last_of(" ")+1,len);
			exp.erase(exp.find_last_of(" ")+1,len);

			while(found!=npos)
			{
				exp[found] = x;
				found = exp.find_first_of("x",found+1);
        		}
			evaluate(exp, atof(x));
		}
	}
	return 0;
}
