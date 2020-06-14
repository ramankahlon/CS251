#ifndef DECODER_H
#define DECODER_H
#include "MinHeap.h"
#include "TreeNode.h"
#include "HuffTree.h"
#include <string>
#include <fstream>
#include <ostream>

using namespace std;



class Decoder
{
	private:
		unsigned frequency_table[256];
		string file_path;
		MinHeap * heap;
		HuffTree * tree;
		int uniqueChars;
		ifstream inputfile;
		TreeNode * node;		

		bool getRight(ofstream &file);
		bool getLeft(ofstream &file);
		int readOneByte(ifstream &file);
 		int readTwoBytes(ifstream &file);
 		int readFourBytes(ifstream &file);
		int readOneBit(ifstream &file);
		// You need to add more class memeber and methods

	public:
		//huff_file_path is the input (encoded) file that we 
		//want to decode
		Decoder(string huff_file_path);

		//Fills up the frequency_table array where frequency_table[i] 
		//will contain the frequency of char with ASCII code i			
		//This method will read the header of the encoded file to 
		//extract the chars and their frequency
		void buildFrequencyTableFromFile();

		//Creates a min-heap and builds the Huffman tree
		void decode();


		//Writes the uncompressed file and save it as file_path
		void writeUncompressedFile(string file_path);

		~Decoder();

};

#endif
