#include<bits/stdc++.h>
#ifndef FILE_H
#define FILE_H


class File{
	public:
		char filePath[100];
	bool isSymbol(char c);
	bool isLimiter(char c);
	void readFile();
};


#endif
