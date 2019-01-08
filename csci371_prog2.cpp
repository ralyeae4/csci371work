//Program 2
//Purpose: to Simulate a FSM thant will take in a set of Roman Numerals 
//and out put the base ten number.
//Author: ELizabeth Ralyea
//Class: CSCI 371
//Date: 10/8/2017

#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <string>

using namespace std;
	int current_state = 0;
	int state;
int get_next(map<int, map<char, int>>, int, char);
bool check_for_letter(string, int);
bool checkString(string , map<int, map<char, int>>, int, int);
bool check_last(string, int);

int main(){

	map<int,map<char, int>> next_state_map;
	string data;
	string filename;
	ifstream myfile;
	bool isNum;
	int e_count = 0;
	int dot_count = 0;
	char to_do;

	//next_state_table
	next_state_map.emplace(-1, map<char, int>{{'D',-1}}); //Capital D denotes dead state
	next_state_map.emplace(0, map<char, int>{{'-',1},{'+',2},{'.',3},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',-1}, {'e',-1}});//inital state
	next_state_map.emplace(1, map<char, int>{{'-',-1},{'+',-1},{'.',3},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',-1}, {'e',-1}});//previously given -
	next_state_map.emplace(2, map<char, int>{{'-',-1},{'+',-1},{'.',3},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',-1}, {'e',-1}});//previously given +
	next_state_map.emplace(3, map<char, int>{{'-',-1},{'+',-1},{'.',-1},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',-1}, {'e',-1}});//previously given .
	next_state_map.emplace(4, map<char, int>{{'-',-1},{'+',-1},{'.',3},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',5}, {'e',5}});//previously given a #
	next_state_map.emplace(5, map<char, int>{{'-',1},{'+',2},{'.',3},{'1',4},{'2',4},{'3',4},{'4',4},{'5',4},{'6',4},{'7',4},{'8',4},{'9',4},{'0',4}, {'E',-1}, {'e',-1}});//previously given E,e

cout<< "*******************************************" << endl;
cout<< "*******************************************" << endl;
cout<< "********       Menu            ************" << endl;
cout<< "**** 1: Number Entered Manually ***********" << endl;
cout<< "**** 2: Number Entered By File  ***********" << endl;
cout<< "**** 3: Exit                    ***********" << endl;
cout<< "*******************************************" << endl;
cout<< "*******************************************" << endl;
cout<< "***** Please Enter The number *************" << endl;
cout<< "****** of what you would like to do: *******" << endl;
cin >> to_do;



switch(to_do){
	case '1':
		cout << "Please enter your numbers (ctrl+D to end):" << endl;
		while(!cin.eof()){
		cin >> data;
		cout << data << "  ";
		isNum = checkString(data, next_state_map, e_count, dot_count);
		if(isNum == true){cout << "yes" << endl<<endl;}
		else{cout <<"no" << endl<< endl;}}
		break;
	case '2':
		cout<< "Please enter the filename:"<< endl;
		cin >> filename;
		myfile.open(filename);
		if(myfile.is_open()){
		while(!myfile.eof()){
			myfile >> data;
			cout << data << "  ";
			isNum = checkString(data, next_state_map, e_count, dot_count);
			if(isNum == true){cout << "yes" << endl <<endl;}
			else{cout <<"no" << endl << endl;}	
		}
		myfile.close();		
		}
		else cout << "Unable to open file:" << filename << endl;
		
		break;
	case '3': 
		return 0;
	default: 
		cout << "That is not a valid choice. Goodbye" << endl;
		break;
	}
	
}
bool check_last(string data, int i){
	
	if( data.back() == 'E'){
	 return false;
	}
else if(data.back() == '-' ){
	 return false;
	}
else if( data.back() == '+'){
	 return false;
	}
return true;
}
bool checkString(string data, map<int, map<char, int>> next_state_map, int e_count, int dot_count)
{
	current_state = 0;
	for(int i = 0; i < data.length(); i++){
		bool last = check_last(data, i);
		if(last == false){
			return false;		
		}
		bool valid = check_for_letter(data, i); //checks for letters other than E or e
		if(valid == true ){
		
			if(e_count <= 1){
				if(dot_count <= 1){
					
				state = get_next(next_state_map, current_state, data[i]);
				if(state == -1){
					cout << "bad state " << data[i] << current_state << state<< endl;
					return false;
				}
				if(data[i] == '.'){
					dot_count++;
				}
				if(toupper(data[i]) == 'E'){
					e_count++;
					dot_count = 1;				
				}
				
				current_state = state;}
			else{
				
				return false;
			}
			}
			else{
				return false;
			}
			
		}
		else{
		return false;
		}}
		
	
return true;
}

bool check_for_letter(string value, int i)
{
	if(isdigit(value[i]) == 1 || toupper(value[i]) == 'E' || value[i] == '.' || value[i] == '+' || value[i] == '-'){
		return true;	
	}
	
	return false;
}

int get_next(map<int, map<char, int>> state_map, int state, char input)
{	 
	int new_state;
	map<int, map<char, int>>::const_iterator itr;
	for( itr=state_map.begin(); itr!=state_map.end(); ++itr){
	new_state = state_map[state][input];}
	return new_state;
}
