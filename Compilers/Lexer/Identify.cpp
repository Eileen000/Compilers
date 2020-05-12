#include <bits/stdc++.h>
#include "Identify.h"
#include "File.h"
#include "NFA.h"
#include "DFA.h" 
using namespace std;
string rr[49]={"if","else","while","signed","throw","union","this",
	"int","char","double","unsigned","const","goto","virtual",
	"for","float","break","auto","class","operator","case",
	"do","long","typedef","static","friend","template","default",
	"new","void","register","extern","return","enum","inline",
	"try","short","continue","sizeof","switch","private","protected",
	"asm","while","catch","delete","public","volatile","struct"};
void Identify::markFile()
{
	File file;
	strcpy(file.filePath,"C:\\Users\\Eileen\\Compilers\\Lexer\\test.txt");
	file.readFile();
	
	int line = 0;
	char c;
	string word="";
	
	fstream read;
	read.open("C:\\Users\\Eileen\\Compilers\\Lexer\\filter.txt");
	
	bool quote = false;
	while(!read.eof())
	{
		read.get(c);
		if(c=='"'&&quote == true)
		{
			quote = false;
			word+=c;
			continue;
		}
		if(c=='"' && quote == false)
		{
			quote = true;
			word+=c;
			continue;
		}
			
		if(c==' '||c=='\n'||c=='\r')
		{
			
			if(word!=""&&quote == false)
			{
				Token now;
				now.row_number = line;
				now.word = word;
				result.push_back(now);
				word = "";
			}	
			if(c=='\n'||c=='\r')
				line++;
			continue;
		}
		word+=c;
	}
	read.close();
	
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\word.txt");
	for(int i=0;i<result.size();i++)
	{
		output<<result[i].row_number<<"  "<<result[i].word<<endl;
	}
	output.close();
}


void Identify::createToken(DFA dfa)
{
	dfa.makeRules();
	
	ofstream output;
	output.open("C:\\Users\\Eileen\\Compilers\\Lexer\\myResult.txt");
	//output<<"(  所在行号 ， 类别 ， token内容 ）"<<endl;
	for(int i=0;i<result.size();i++)
	{
		//cout<<"****"<<result[i].row_number<<" "<<result[i].word<<endl;
		if(result[i].word[0]==34 || result[i].word[0]==39)
			continue;
		int ans = dfa.isLegal(result[i].word);
		//cout<<"**"<<ans<<endl;
		if(ans==-1)
		{
			output<<"not legal  :  "<<result[i].row_number<<"   "<<result[i].word<<endl;
			continue;
		}
		
		output<<"("<<result[i].row_number<<",";
		bool flag=false;
		if(dfa.rules[ans].second=="identifier")
		{
			//cout<<"**"<<endl;
			for(int j=0;j<49;j++)
			{
				if(result[i].word==rr[j])
					{
						flag = true;
						break;
					}
				}
			}
			if(flag==false)
				output<<dfa.rules[ans].second;
			else
				output<<"reservedwords"; 
			output<<","<<result[i].word<<")"<<endl;		
	}
	output.close();
	cout<<" Finish Identify "<<endl;
}
