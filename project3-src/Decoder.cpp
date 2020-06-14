#include <iostream>
#include "Decoder.h"
#include "TreeNode.h"
#include "MinHeap.h"
#include "HuffTree.h"
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstring>
#include <cstddef>
#include <vector>

using namespace std;

Decoder::Decoder(string huff_file_path)
{
        this -> file_path = huff_file_path;
        this -> heap = new MinHeap();
        this -> tree = new HuffTree();
	this -> uniqueChars = 0;
	inputfile.open(this->file_path, ios::in | ios::binary);
	if(inputfile.fail())
		return;
}

//Fills up the frequency_table array where frequency_table[i]
//will contain the frequency of char with ASCII code i

void Decoder::buildFrequencyTableFromFile()
{
	this -> uniqueChars = this -> readTwoBytes(this->inputfile);
	int index;
	int freq;
	for(int i=0;i< this->uniqueChars; i++)
	{
		index = this->readOneByte(this->inputfile);
		freq = this->readFourBytes(this->inputfile);
		this->frequency_table[index] = freq;
	}
/*
        ifstream inputfile;
        inputfile.open(infile, ios::in | ios::binary);
        if(inputfile.fail())
        {
		cout << "Error: cannot open input file" << endl;
		return;
        }
        uniqueChars = this -> readTwoBytes(inputfile);
	cout << "unique characters: " << uniqueChars << endl;
	int ch;
        int freq;
        for(int i = 0; i<uniqueChars; i++)
        {
                ch = this -> readOneByte(inputfile);
                cout << "character: " << (char)(ch) << endl;
		freq = this -> readFourBytes(inputfile);
                cout << "frequency: " << freq << endl;
		this -> frequency_table[ch] = freq;
        }*/
}

//Builds the min head and run the encoding algorithm

void Decoder::decode()
{
        this -> buildFrequencyTableFromFile();
        for(int i = 0; i<256; i++)
        {
                if(frequency_table[i] != 0)
                {
                        TreeNode * node = new TreeNode(i, frequency_table[i]);
                        this -> heap -> insert(node);
                }
        }
        this ->tree -> buildTree(this ->heap);
        this ->node = tree->root;
}

bool Decoder::getRight(ofstream& file)
{
	TreeNode * temp = this->node->getRight();
	this->node = temp;
	if(this->node->isLeafNode())
	{
		if(this->frequency_table[this->node->getVal()] > (unsigned int)0)
		{
			this->frequency_table[this->node->getVal()]--;
			file <<(char)this->node->getVal();
			this -> node = tree->root;
			return true;	
		}
		return false;
	}
	return true;
}

bool Decoder::getLeft(ofstream& file)
{
	this->node = this->node->getLeft();
	if(this->node->isLeafNode())
	{
		if(this->frequency_table[this->node->getVal()] > (unsigned int)0)
		{
			this->frequency_table[this->node->getVal()]--;
			file <<(char)this->node->getVal();
			this->node = tree->root;
			return true;	
		}
		return false;
	}
	return true;
}

//Generates the encoded file and save it as output_file_path

void Decoder::writeUncompressedFile(string file_path)
{
	ofstream ofile;
	ofile.open(file_path);
	char c;
	bool complete = true;
	while(inputfile.get(c))
	{
		for(int i = 7; i >= 0 ; i--)
		{
			if (((c >> i )&1) == 1)
			{
				if(!this->getLeft(ofile))
				{
					complete = false;
					break;	
				}
			}
			else
			{
				if(!this->getRight(ofile))
				{
					complete = false;
					break;
				}
			}
		}
		if(!complete)
			break;
	}
}

Decoder::~Decoder()
{
	delete heap;
	delete tree;
}

int Decoder::readOneByte(ifstream& file)
{
        unsigned char byte;
        file.read(reinterpret_cast<char *>(&byte),1);
        return (unsigned int)byte;
}

int Decoder::readTwoBytes(ifstream& file)
{
        unsigned char byte1;
        unsigned char byte2;
        file.read(reinterpret_cast<char *>(&byte1),1);
        file.read(reinterpret_cast<char *>(&byte2),1);
        return (unsigned int)(byte2 << 8 | byte1);
}

int Decoder::readFourBytes(ifstream& file)
{
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
        unsigned char byte4;
        file.read(reinterpret_cast<char *>(&byte1),1);
        file.read(reinterpret_cast<char *>(&byte2),1);
        file.read(reinterpret_cast<char *>(&byte3),1);
        file.read(reinterpret_cast<char *>(&byte4),1);
        return (unsigned int)(byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24));
}

