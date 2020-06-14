/*
 *  CS251 - Spring 2018: Project 1
 */
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;
void dashLine(int c);//method declaration

int main(int argc, char** argv)
{
	int c;//first number of file, indicates amount of numbers in each subsequent row
	cin >> c;//read first number from input file
	dashLine(c);//call method to print first row of hyphens

	int num = 0;//variable to hold each number that is read as input
	int j;//counter to indicate when to end line
	int counter;                
	while(cin >> counter)
	{
		int n = counter;//set variable equal to next number
		if(n < 10)//for single digit numbers
		{
			if((num + 1) % c == 0)//if last number in line, only print number
                		cout << n;
            		if((num + 1) % c != 0)//print pipe character in between numbers on same line
                		cout << n << " " << "|" << " ";
            		num++;//increment index of number on line
		}
		else if(n < 100 && n >= 10)//for two digit numbers
		{
			if((num + 1) % c == 0)//if last number in line, print one space before number
                		cout << " " << n;
            		if((num + 1) % c != 0)//print one space before number then pipe character between numbers on same line
                		cout << " " << n << " " << "|" << " ";
            		num++;//increment index of number on line
		}
		else//for three digit numbers
		{	
            		if((num + 1) % c == 0)//if last number in line, don't print any spaces before number
                		cout << n;
            		if((num + 1) % c != 0)//print pipe character in between numbers on same line
                		cout << n << " " << "|" << " ";
            		num++;//increment index of number on line
		}
		if(num == c)//if on last number in line, reset num to 0 and start printing on a new line
		{
			num = 0;
			cout << endl;
		}
	}
	dashLine(c);//call method to print dashes in between each line
	return 0;
}

void dashLine(int c)
{
        //cout << "\r\n";//return and go to new line after all dashes have been printed

	for(int a=0;a<(6*c-3);a++)
        {
                cout << "-";//print 6c-3 dashes in between each line of numbers
        }
}
