#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void write(string i, string s);
string symboletype(char c);
bool numbercheck(char c);
bool charcheck(char c);

void main()
{
	
	fstream myfile;
	/************to clear the output file content***********/
	myfile.open("scanner_output.txt",ios::out|ios::trunc);
	
	myfile.close();


/*********************to read from the input file **********/ 
	myfile.open("tiny_sample_code.txt");
	string s;
	string fulltxt = "";
	while (!myfile.eof())
	{
		getline(myfile, s);
		fulltxt.append(s);
	}
	myfile.close();



	/********scanning process***************/
	int i = 0;
	enum states {start, innum,inid,inassign,incomment,other,done};
	
	states state = start;
	
	while (i < fulltxt.length())
	{
		string temp = "";


		/**************start state********************/
		if(state==start)

			switch (fulltxt[i])
			{

			case'{' :
				state = incomment;
				break;

			case'+': case'-': case'*': case '/': 
			case'=': case'<': case'(': case ')':
			case';':
				state = other;
				break;

		
			case'0': case'1': case'2': case'3': 
			case'4': case'5': case'6': case'7': 
			case'8': case'9':
				state = innum;
				break;

			case':':
				state = inassign;
				break;


			default:
				state =	inid;
				break;

				
			}



			switch (state)
			{
				/**********************number**********************/
		case innum:
			//i++;
			temp = "";
			while (numbercheck(fulltxt[i]))
			{
				temp += fulltxt[i];
				i++;
			}
			//if(fulltxt[i]!=' ')
			i--;
			write(temp, "number");
			state = start;
			
			break;


			/********************identifier***************************/
		
		case inid:
		//	i++;
			 temp = "";
			while (charcheck(fulltxt[i]))
			{
				temp += fulltxt[i];
				i++;
			}
			//if (fulltxt[i] == ' ')
			if(temp!="")
				i--;
			
			if (temp == "if" || temp == "then" || temp == "else" || temp == "end" ||
				temp == "repeat" || temp == "until" || temp == "read" || temp == "write")
			{
				write(temp, "reserved word");
			}
			else if(temp!="")
			write(temp, "identefier");
			state = start;
			
			break;


		
			/**************************assign**************************/
		case inassign:
			//i++;
			if (fulltxt[i + 1] == '=')
				write(":=", "assingment");
			i++;
			state = start;
			break;


			/********************comment**********************/
		case incomment:
			i++;
			while (fulltxt[i] !='}')
			{
				i++;
				//cout << " incom	";
			}
			//i++;
			//cout << endl;
			state = start;
			break;


			/////////////other/////////////////////////////
			
		case other:
			//i++;
			temp = ""; temp += fulltxt[i];
			write(temp, "special symbol");// symboletype(fulltxt[i]));
			
			state = start;
			break;
			

			/*******************************************************/
			
		default:
			break;
		}


		i++;
	}
//		system("pause");
}

void write(string i, string s)
{
	fstream myfile2;
	//code to write at file 
	myfile2.open("scanner_output.txt",ios::app);
	myfile2 << " "<<i<<" :"<<s<<endl;
	myfile2.close();

	//cout << i << "		" << s << endl;
}

bool numbercheck(char c)
{
	switch (c)
	{
	case'0': case'1': case'2': case'3':
	case'4': case'5': case'6': case'7':
	case'8': case'9':
		return true;

	default:
		return false;
	}
}

	bool charcheck(char c)
	{
		switch (c)		
		{

		case'0': case'1': case'2': case'3':
		case'4': case'5': case'6': case'7':
		case'8': case'9':
			return false;

		case'+': case'-': case'*': case '/':
		case'=': case'<': case'(': case ')':
		case';': case' ': case':': case '{': 
		case'}':
			return false;
		
		default:
			return true;
			
		}
	}
	/*
	string symboletype(char c)
	{
		switch (c)
		{
		case'+':return "PLUS operator";
		case'-':return "MINUS operator";
		case'*':return "MULTIPLICATION operator";
		case'/':return "DIVISION operator";
		case'=':return "EQUAL opetator";
		case'<':return "LESS THAN operator";
		case'>':return "GREATER THAN operator";
		case'(':return "RIGHT PARENTHESIS";
		case')':return "LEFT PARENTHESIS";
		case';':return "SEMICOLON";

		default:
			return "symbol not available in the tiny scanner";
		}
	}*/
