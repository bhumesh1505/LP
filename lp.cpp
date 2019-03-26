#include <bits/stdc++.h>
using namespace std;
void f(const string &code,int &i , int len , stack<string> &stck,string &convertedCode)
{
	string s1 = "";
	while(i + 3 < len )
	{
		if(code[i] == 'f' && code[i+1] == 'o' && code[i+2] == 'r' && (code[i+3] == ' ' || code[i+3] == '(' ))
		{
			i = i + 3;
			// skip all blankspaces after for keyword
			if(code[i] == ' ')
			{
				i++;
				while(i <len && code[i] == ' ' ) 
				{
					i++;
				}
			}
			i++; // skip "(" 

			// initialization part of for loop with multiple variables initialization for(i=0,j=0,k=0; ; )
			string initialize = "";
			int flag = 0;
			while(i<len && code[i] != ';')
			{
				flag = 1;
				if(code[i] == ',')
				{
					//cout << initialize + ";" << endl;
					convertedCode += initialize + ";\n"; 
					initialize = "";
				}
				else
				{
					initialize = initialize + code[i];
				}
				i++;
			}
			if(flag == 1)
			{
				//cout << initialize + ";" << endl;
				convertedCode += initialize + ";\n";
			}
			i++;	// skip ";"



			//condition part of for loop
			string codition = "";
			while( i<len && code[i] != ';' )
			{
				codition = codition + code[i];
				i++;
			}
			//cout << "while(" + codition + ")" << endl;
			convertedCode = convertedCode +  "while(" + codition + ")\n";
			i++; // skip ";"



			// increament or decreament part of for loop ex. for(i=0,j=0;cond;i = (i+(j+1)) )
			int countOpening = 0;
			string incr = "";
			while( i<len && countOpening >= 0 )
			{

				if(code[i] == '(')
				{
					countOpening++;
				}
				else if(code[i] == ')')
				{
					countOpening--;
				}

				if(countOpening >= 0)
				{
					incr = incr + code[i];
				}
				i++;
			}

			stck.push(incr);


			//skip all spaces after for() ______ 
			while(i<len && (code[i] == ' ' || code[i] == '\n' ))
			{
				i++;
			}

			//cout << "{" << endl;
			convertedCode += "{\n";

			if(code[i]=='{')
			{
				stck.push("{");
				i++;
				f(code,i,len,stck,convertedCode);
			}
			else if(i+3 < len) 
			{
				if(code[i]=='f' && code[i+1]=='o' && code[i+2]=='r' && (code[i+3]==' ' || code[i+3]=='('))
				{
					f(code,i,len,stck,convertedCode);
				}
				else
				{
					// single line inside for loop without {}
					int flag = 0;
					while(i<len && code[i]!=';')
					{
						flag = 1;
						//cout << code[i];
						convertedCode += code[i];
						i++;
					}
					i++;
					if(flag == 1)
					{
						//cout << ";" << endl;
						convertedCode += ";\n";
					}
				}
			}
			

			if(!stck.empty())
			{
				string incrTop = stck.top();
				stck.pop();
				if(incrTop != "")
				{
					int j = 0;
					int incrLen = incrTop.length(); 
					while(j < incrLen)
					{
						incr = "";
						while(j < incrLen && incrTop[j] != ',')
						{
							incr = incr + incrTop[j];
							j++;
						}
						j++;
						if(incr != "")
						{
							//cout << incr + ";" << endl;
							convertedCode += incr + ";\n";
						}
					}
				}
				//cout << "}" << endl;
				convertedCode += "}\n";
			}
		}
		else
		{
			if(code[i] == '{')
			{
				stck.push("{");
			}
			else if(code[i] == '}')
			{
				stck.pop();
				string incrTop = stck.top();
					
				if(incrTop != "{") // for loop close }
				{
					stck.pop();
					if(incrTop != "")
					{
						int j = 0;
						int incrLen = incrTop.length(); 
						while(j < incrLen)
						{
							string incr = "";
							while(j < incrLen && incrTop[j] != ',')
							{
								incr = incr + incrTop[j];
								j++;
							}
							j++;
							if(incr != "")
							{
								//cout << incr + ";" << endl;
								convertedCode += incr + ";\n";
							}
						}
					}
				}
			}
			//cout << code[i];
			convertedCode += code[i];
			if(code[i] == ';' || code[i] == '}')
			{
				//cout << endl;
				convertedCode += "\n";
			}
			i++;
		}
	}
	i = i + 3;
	if(i == len)
	{
		//cout << code[i-3] << code[i-2] << code[i-1] << endl;
		convertedCode += code[i-3];
		convertedCode += code[i-2];
		convertedCode += code[i-1];
		convertedCode += "\n";
	}

}
int main(int argc, char const *argv[])
{
	ifstream fin; 
  
    string line;  
    fin.open("input.txt");   
    string code = "";

 	while (fin) { 
  
        getline(fin, line); 
  		code = code + line; 
    } 
  	fin.close(); 

 	stack <string> stck;
 	int len = code.length();
 	int i = 0;
 	string convertedCode = "";

  	f(code,i,len,stck,convertedCode);   
  	cout << convertedCode << endl;
	return 0;
}