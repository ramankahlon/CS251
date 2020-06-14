#include <iostream>
#include "TreeNode.h"
#include "MinHeap.h"
#include "Encoder.h"
#include "HuffTree.h"
#include <fstream>
#include <bitset>
#include <string>

using namespace std;

Encoder::Encoder(string file_path){ 
	this->inputFile = file_path;
	tree = new HuffTree();
	heap = new MinHeap();

}

void Encoder::buildFrequencyTable(){
	ifstream infile;
	infile.open(inputFile);
	if(infile.fail())
		return;
	else
	{
		char val;
		while(infile.get(val))
		{
				unsigned char convert = val;			
				frequency_table[convert]++;
		}
	}
	infile.close();
}

void Encoder::encode(){
	this->buildFrequencyTable();
	for(int i = 0; i < 256; i++)
	{
		if(frequency_table[i] != 0)
		{
			TreeNode * node = new TreeNode(i,frequency_table[i]);
			heap->insert(node);
		}
	}
	tree->buildTree(heap);
	tree->generateCodes();
}

void Encoder::writeEncodedFile(string output_file_path)
{
	ofstream ofile;
	ofile.open(output_file_path, ios::out | ios::binary);
	if (ofile.fail())
		return;
	
	int n = tree->vec.size();
	cout<<n<<"\n";
	ofile.write((const char *)&n,2);
	for(int i = 0; i < 256; i++)
	{
		if(frequency_table[i] != 0)
		{
			int freq = frequency_table[i];
			ofile.write((const char *)&i,1);
			ofile.write((const char *)&freq,4);
		}	
	}
	ifstream inputfile;
	inputfile.open(inputFile);
	if(inputfile.fail())
		return;
	char c;
	string bitCode = "";
	while(inputfile.get(c))
	{
		int ascii = (int)(c);
		string charCode = tree->getCharCode(ascii);
		bitCode += charCode;
	}
	int index;
	string convert;
	for(index = 0; index < bitCode.length(); )
	{
		int byte = 0;
		convert = "";
		while(byte < 8 && index < bitCode.length() )
		{
			convert+= bitCode[index];		
			index++;
			byte++;
		}
		int size;
		for(size = convert.length(); size < 8; size++)
		{
			convert += "0";
		}
		bitset<8> bit(convert);
		unsigned long bits = bit.to_ulong();
		ofile.write((const char *)&bits,1);	
	}
	ofile.close();
	inputfile.close();
}

Encoder::~Encoder()
{
	delete tree;
	delete heap;
}

