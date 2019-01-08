//Program 1
//Purpose: to Simulate a FSM thant will take in a set of Roman Numerals 
//and out put the base ten number.
//Author: ELizabeth Ralyea
//Class: CSCI 371
//Date: 9/25/2017

#include <iostream>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;
/***********************************************************************/

//state next_state[state][char] =
//action add_value[state][char] = 

int get_next(map<int, map<char, int>>, int, char);
int do_action(map<int, map<char, int>>, int, char);
bool checkArray(char[]);

int main()
{

	map<int,map<char, int>> next_state_map;
	map<int, map<char, int>> action_map;
	char value[15];
	int current_state = 0;
	int state;
	int x = 0;
	int base_ten = 0;

//next State Table
	next_state_map.emplace(-1, map<char, int>{{'A',-1}});//A denotes dead state
	next_state_map.emplace(0, map<char, int>{{'I',1},{'V',2},{'X',3},{'L',4},{'C',5}}); //inital state
	next_state_map.emplace(1, map<char, int>{{'I',1},{'V',6},{'X',6},{'L',-1},{'C',-1}});//previously given I
	next_state_map.emplace(2, map<char, int>{{'I',1},{'V',-1},{'X',-1},{'L',-1},{'C',-1}});//previously given V
	next_state_map.emplace(3, map<char, int>{{'I',1},{'V',2},{'X',3},{'L',7},{'C',7}});//previously given X
	next_state_map.emplace(4, map<char, int>{{'I',1},{'V',2},{'X',3},{'L',-1},{'C',-1}});//previously given L
	next_state_map.emplace(5, map<char, int>{{'I',1},{'V',2},{'X',3},{'L',4},{'C',5}});//previously given C
	next_state_map.emplace(6, map<char, int>{{'I',-1},{'V',-1},{'X',-1},{'L',-1},{'C',-1}});//previously given IX
	next_state_map.emplace(7, map<char, int>{{'I',1},{'V',2},{'X',-1},{'L',-1},{'C',-1}});//previously given XC
	
//Action Table
	action_map.emplace(0, map<char, int>{{'I',1},{'V',5},{'X',10},{'L',50},{'C',100}}); //inital state
	action_map.emplace(1, map<char, int>{{'I',1},{'V',3},{'X',8},{'L',0},{'C',0}});//previously given I
	action_map.emplace(2, map<char, int>{{'I',1},{'V',0},{'X',0},{'L',0},{'C',0}});//previously given V
	action_map.emplace(3, map<char, int>{{'I',1},{'V',5},{'X',10},{'L',30},{'C',80}});//previously given X
	action_map.emplace(4, map<char, int>{{'I',1},{'V',5},{'X',10},{'L',0},{'C',0}});//previously given L
	action_map.emplace(5, map<char, int>{{'I',1},{'V',5},{'X',10},{'L',50},{'C',100}});//previously given C
	action_map.emplace(6, map<char, int>{{'I',0},{'V',0},{'X',0},{'L',0},{'C',0}});//previously given IX
	action_map.emplace(7, map<char, int>{{'I',1},{'V',5},{'X',0},{'L',0},{'C',0}});//previously given XC
	
	cout << "Please enter a Roman Numeral (using values C,L,X,V,I in CAPS):" << endl;	
	cin >> value;
	
	bool valid = checkArray(value); //checks for 4 of a like in a row

if(valid == true){//if there is no four in a row 
	while(x <= 15){//loops through char[]
	if(value[x] != 0){//checks to see if value is zero/empty
		if(value[x] == 'C' || value[x] == 'L' || 
			value[x] == 'X' || value[x] == 'V' || value[x] == 'I'){ //checks for vaild Roman Numerals 
			state = get_next(next_state_map, current_state, value[x]);
			if(state == -1){
				cout << "Invalid Roman Numeral" << endl;
				base_ten = -1;
				x = 16;
			}
			else{
			base_ten += do_action(action_map, current_state,value[x]);
			current_state = state;
			x++;
			}
		}
		else{
			cout << "Invalid Roman Numeral" << endl;
			base_ten = -1;
			x = 16;
		}
	}
	else{
		x = 16;
	}
	}
	if(base_ten != -1){//output base number
	cout << value << " = "<< base_ten<< endl;}
	}
	 else{cout << "Invalid Roman Numeral" << endl;}


}

bool checkArray(char value[])
{
	int x = 0;
	while(x <= 11)
	{
		if(value[x] != 0){
		if(value[x] == value[x + 1] && value[x + 1] == value[x + 2] && value[x+2] == value[x + 3] ){
		 	return false;
		}
		}else{x = 12;}
		x++;
	}
	return true;
}

int get_next(map<int, map<char, int>> state_map, int state, char input)
{	 
	int new_state;
	map<int, map<char, int>>::const_iterator itr;
	for( itr=state_map.begin(); itr!=state_map.end(); ++itr){
	new_state = state_map[state][input];}
	return new_state;
}
int do_action(map<int, map<char, int>> action_map, int state, char input)
{	 
	int new_action;
	map<int, map<char, int>>::const_iterator itr;
	for( itr=action_map.begin(); itr!=action_map.end(); ++itr){
	new_action = action_map[state][input];}
	return new_action;
}


