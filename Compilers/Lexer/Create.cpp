#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

int num = 33;

int epslion = 6;

void createProduction(char path[])
{
	SetConsoleOutputCP(437);
	string in[num]={
	"<start>->a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z<identifier>",
	"<start>->A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z<identifier>",
	"<identifier>->0|1|2|3|4|5|6|7|8|9|_<identifier>",
	"<identifier>->a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z<identifier>",
	"<identifier>->A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z<identifier>", //A 标识符 
	"<start>->0|1|2|3|4|5|6|7|8|9<integer>",
	"<integer>->0|1|2|3|4|5|6|7|8|9<integer>",  		//B 整数 
	"<integer>->+<science3>",
	"<science3>->0|1|2|3|4|5|6|7|8|9<science4>",
	"<science4>->0|1|2|3|4|5|6|7|8|9<science4>",
	"<science4>->i<integer>",
	"<integer>->.<point>",
	"<point>->0|1|2|3|4|5|6|7|8|9<double>",
	"<double>->0|1|2|3|4|5|6|7|8|9<double>",  		//D 小数 
	"<double>->E<science1>",
	"<science1>->+<science2>",
	"<science2>->0|1|2|3|4|5|6|7|8|9<double>",
	"<start>->+|-|*|/|=|!|%|^|<|>|~|&||<operator>",        	//E 运算符 
	"<start>->==|++|--|=|!=|+=|-=|*=|/=|%=|>=|<=|<<|>>||=|&=||=|::|&&|||<operator>",
	"<start>->if|else|while|signed|throw|union|this<reservedwords>",
	"<start>->int|char|double|unsigned|const|goto|virtual<reservedwords>",
	"<start>->for|float|break|auto|class|operator|case<reservedwords>",
	"<start>->do|long|typedef|static|friend|template|default<reservedwords>",
	"<start>->new|void|register|extern|return|enum|inline<reservedwords>",
	"<start>->try|short|continue|sizeof|switch|private|protected<reservedwords>",
	"<start>->asm|while|catch|delete|public|volatile|struct<reservedwords>",
	"<start>->?|(|)|;|'|{|}|#|.|,|[|]<delimiters>",			
	"<identifier>->?",
	"<integer>->?",
	"<double>->?",
	"<operator>->?",
	"<delimiters>->?",
	"<reservedwords>->?"
	};
	
	
	in[26][9] = '"';
	for(int i= num-epslion;i<num;i++)
		for(int j=0;j<in[i].length();j++)
		{
			if(in[i][j]=='?')
			{
				in[i][j] = 238;
			}
		}
					
	
	char cPath[100];
	strcpy(cPath,path);
	ofstream output;
	output.open(cPath);
	if(!output)
	{
		cout<<"The txt was not exit!"<<endl;
		return;
	}
	else
	{
		for(int i=0;i<num;i++)
		{
			output<<in[i];
			if(i<num-1)
				output<<'\n';
		}
		output.close();
		
		cout<<"The production has been created."<<endl;
		return;
	}
	

}
