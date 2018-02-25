/*
Group 1
1155063406 Au Yeung Tat On
1155083016 Lam Ming Yuen
1155064634 Ho Kwan Hi Marcus Kuncoro
1155063795 Chan Yue Kan

Reference:
C++ load Wave File Headers - part1
https://www.youtube.com/watch?v=YIdgeuEjZoE
C++ load Wave File Headers - part2
https://www.youtube.com/watch?v=e1-bRZMPq-U
*/

#include<iostream>
#include"decode.h"
#include<Windows.h>
using namespace std;

typedef char _TCHAR;


int endwitherror(char* msg, int error = 0) 
{
	cout << msg << endl;
	while (cin.get() != 10);

	return error;
}

int _tmain(int argc, _TCHAR* argv[]) {
	FILE* fp = NULL;

	fp = fopen("a.wav", "r");
	if (!fp) 
		return endwitherror("Error : Failed To Open File");

	char type[4];
	DWORD size, chunkSize, sampleRate, avgBytesPerSec, dataSize;
	fread(type, sizeof(char), 4, fp);
	short formatType, channels, bytesPerSample, bitsPerSample;

	if (!strcmp(type, "RIFF")) 
		return endwitherror("Error: Not RIFF Format");

	fread(&size, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if (!strcmp(type,"WAVE"))
		return endwitherror("Error : Not WAVE Format");

	fread(type, sizeof(char), 4, fp);
	if (!strcmp(type,"fmt "))
		return endwitherror("Error : Not fmt");


	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if (!strcmp(type, "data"))
		return endwitherror("Error : Missing Data");

	fread(&dataSize, sizeof(DWORD), 1, fp);

	cout << "Chunk Size: " << chunkSize << endl;
	cout << "Format Type: " << formatType << endl;
	cout << "Channels: " << channels << endl;
	cout << "Average Bytes Per Second: " << avgBytesPerSec << endl;
	cout << "Bytes Per Sample: " << bytesPerSample << endl;
	cout << "Bits Per Sample:" << bitsPerSample << endl;
	cout << "Press Enter To End" << endl;

	while (cin.get() != 10);

	return 0;
}