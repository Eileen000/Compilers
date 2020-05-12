#include<bits/stdc++.h>
#include "Production.h"
#ifndef ITEM_H
#define ITEM_H
using namespace std;


class Item{
	
	public:
		string sentence;
		string first;
	
	public:
		bool isVT(char c);
		int findStar(Item e);
		//string firstSet(char c,Production pro);
		bool Exit(Item e,vector<Item>II);
		string FIRST(char c,Production pro);
		bool notExit(queue<Item>deal,Item e);
		vector<Item> findClosure(Item e,Production pro);
		
};


#endif
