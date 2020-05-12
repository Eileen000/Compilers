#include<bits/stdc++.h>
#include "File.h"
using namespace std;

string read()
{
	
	vector<string> token;
	fstream input;
	//input.open("C:\\Users\\Eileen\\Compilers\\Parser\\token.txt");
	input.open("C:\\Users\\Eileen\\Compilers\\Lexer\\myResult.txt");
	string line = "";
	while(!input.eof())
	{
		if(input.good())
		{
			char c;
			input.get(c);
			
			if(c!='\n'&&c!='\t')
			{
				line+=c;
			}
			else
			{
				
				token.push_back(line);
				line = "";
			}
				
		}
	}
	input.close();
	/*ofstream output;
	output.open("C:\\Users\\Eileen\\desktop\\test.txt");
	for(int i=0;i<token.size();i++)
	{
		output<<token[i]<<endl;
	}
	output.close();*/
	//以下是自定义 
	//ofstream output;
	//output.open("C:\\Users\\Eileen\\Compilers\\Parser\\test.txt");
	//cout<<token.size()<<endl;
	string ans="";
	for(int i=0;i<token.size();i++)
	{
		if(token[i].size()==0)
			break;
		//cout<<token[i]<<endl;
		string x="";
		string tmp[3];
		int cnt=0;
		for(int j=1;j<token[i].size()-1;j++)
		{
			if(token[i][j]!=',')
				x+=token[i][j];
			else if(cnt<2)
			{
				tmp[cnt++]=x;
				x="";
			}
		}
		tmp[cnt] = x;
		//output<<endl;
		if(tmp[1]=="reservedwords")
		{
			if(tmp[2]=="int"||tmp[2]=="char"||tmp[2]=="double")
				//cout<<"f"<<endl;
				//output<<"f";
				{ans+="f";} 
				
			else if(tmp[2]=="if"||tmp[2]=="while")
				ans+="p";
			else if(tmp[2]=="for")
				//output<<"k";
				ans+="k";
			else if(tmp[2]=="return")
				//output<<"m";
				ans+="m";
		}
		else if(tmp[1]=="operator")
		{
			//output<<tmp[2];
			ans+=tmp[2];
		}
		else if(tmp[1]=="identifier")
		{
			//output<<"e";
			if(tmp[2]=="include")
				//output<<"b";
				ans+="b";
			else
				ans+="e";
		}
		else if(tmp[1]=="delimiters")
		{
			//output<<tmp[2];
			if(tmp[2]=="#")
				ans+="a";
			else
				ans+=tmp[2];
		}
		else if(tmp[1]=="constant")
		{
			ans+="j";
		}
		
	}
	//cout<<ans<<endl;
	//output.close();

	return ans;
}


