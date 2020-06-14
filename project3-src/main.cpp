#include <iostream>
#include <string>
#include "MinHeap.h"
#include "Encoder.h"
#include "Decoder.h"

using namespace std;

void printHelp()
{
}

int main(int argc, char** argv)
{
	if(argc == 4)
	{
		string n = argv[1];
		if(n == "-e")
		{
			Encoder * encode = new Encoder(argv[2]);
			encode->encode();
			encode->writeEncodedFile(argv[3]);
			delete encode;
		}
		else if(n == "-d")
		{
			Decoder * decode = new Decoder(argv[2]);
			decode->decode();
			decode->writeUncompressedFile(argv[3]);
			delete decode;
		}
			
	}
	else
		printHelp();
	
	return 0;
}

