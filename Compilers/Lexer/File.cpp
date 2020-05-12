#include<bits/stdc++.h> 
#include "File.h"
using namespace std;
bool File::isSymbol(char c)
{
	if(c>='0'&&c<='9')
		return false;
	if(c>='a'&&c<='z')
		return false;
	if(c>='A'&&c<='Z')
		return false;
	return true;
}
bool File::isLimiter(char c)
{
	if(c=='['||c==']'||c=='{'||c=='}'
		||c=='('||c==')'||c==';'||c==','
		||c=='"')
	return true;
	
	return false;	
}
void File::readFile()    //处理用户输入文本 
{
	fstream inFile;
	inFile.open(filePath);

	if(!inFile.is_open())
	{
		cout<<"Could not find the file/n";
		inFile.close();
		return;
	}
	
	ofstream outFile;
	outFile.open("C:\\Users\\Eileen\\Compilers\\Lexer\\filter.txt");
	char c=' ',prec=' ';
	bool comment=false;
	bool single_comment = false;
	bool quote = false;
	bool single_quote = false;
	bool science = false;
	while(!inFile.eof())
	{
		if(inFile.good())
		{
			prec=c;
			inFile.get(c);
			
			if(prec=='*'&&c=='/'&&comment==true)
			{
				comment = false;
				continue;
			}
			if(comment == true)
				continue;
			if(single_comment == true && (c=='\n'||c=='\r'))
			{
				single_comment = false;
				continue;
			}		
			if(single_comment == true&&c!= '\n'&&c!='\r')
				continue;
			
			if(c=='"' && quote == false)
			{
				quote = true;
				outFile<<' ';
				outFile<<c;
				continue;
			}
			if(quote == true && c=='"')
			{
				quote = false;
				outFile<<c;
				continue;
			}
			if(quote == true && c!='\n')
			{
				outFile<<c;
				continue;
			}
			if(single_quote==true && c!=39)
			{
				
				outFile<<c;
				continue;
			}
			
			if(c==39 && single_quote == false)
			{
				single_quote = true;
				outFile<<' ';
				outFile<<c;
				continue;
			}	
			if(c==39 && single_quote == true)
			{
				single_quote = false;
				outFile<<c;
				continue;
			}
			
			if(single_quote == false && prec == 39)
				outFile<<' ';
			
			if(c=='/'&&!inFile.eof())
			{
				prec = c;
				inFile.get(c);
				if(c=='*')
				{
					comment = true;
					continue;
				}
				else if(c=='/')
				{
					single_comment = true;
					continue;
				}
			}	
			if(c=='_')
			{
				outFile<<c;
				continue;
			}
			if(prec=='_' && isSymbol(c) == false)
			{
				outFile<<c;
				continue;
			}
			if(c=='\t')
			{
				outFile<<' ';
				continue;
			}
			if(c=='\n'||c=='\r')
			{
				outFile<<'\n';
				quote = false;
				continue;
			}
			
			if(prec>='0'&&prec<='9'&&c=='.')
			{
				outFile<<c;
				continue;
			}
			if(c>='0'&&c<='9'&&prec=='.')
			{
				outFile<<c;
				continue;
			}
			if(c=='+'&&prec=='E')
			{
				outFile<<c;
				continue;
			}
			if(c>='0'&&c<='9'&&prec=='+')
			{
				outFile<<c;
				continue;
			}
			if(prec>='0'&&prec<='9'&&c=='+')
			{
				outFile<<c;
				continue;
			}
			if(isSymbol(prec)==true && 
				(isSymbol(c) == false || ( (prec!='+'&&prec!='-') && (c>='0'&&c<='9') )  )
				)
				outFile<<' ';
			
			if(isSymbol(prec)==false && isSymbol(c) == true)
				outFile<<' ';
			if(isLimiter(c)==true&&c!='.'||isLimiter(prec)==true)
				outFile<<' ';
				
			outFile<<c;
			if(isSymbol(prec)==true&&isSymbol(c)==true&&c!='.')
				outFile<<' ';
		
			
		}
	}
	inFile.close();
	outFile.close();
	
}
