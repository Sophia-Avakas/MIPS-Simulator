#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
//#include "solution.cpp"
//#include "tester.cpp"

using namespace std;

using namespace std;
class solution {

private:

bool DEBUG;
int clck;
vector<string> vect_lines;
vector<int>* t_vars;
int cycle_of_completion;

public :

solution(ifstream &file_in,int clck_in = 10 ,bool DEBUG_in = false);
void dbg(const string &msg);
vector<int>* alu();
int mips_clock();

vector<string> splitString(string str);
void excuteOperation(string opt, string opt1,string opt2,string opt3);

};


solution::solution(ifstream &file_in,int clck_in,bool DEBUG_in){
	clck = clck_in;
	DEBUG = DEBUG_in;
	//read lines
	string line;
	if (file_in.is_open())
	{
		while ( getline (file_in,line) )
		{
			vect_lines.push_back(line);
		}
		file_in.close();
	}
	t_vars = new vector<int>();
	cycle_of_completion = 0;
}

void solution::dbg(const string &msg){
	cout << msg << endl;
	int i = 0;
	for (; i < t_vars->size()-1 ; i++){
		cout << t_vars->at(i) << ",";
	}
	cout << t_vars->at(i) << endl;
	cout << cycle_of_completion << endl;
}

vector<string> solution::splitString(string str)
{
	int cur_pos = 0;
	vector<string> result;
	for(unsigned int i=0; i<str.size(); i++)
	{
		if(str[i] == ',' || str[i] == ' ')
		{
			result.push_back(str.substr(cur_pos,i-cur_pos));
			cur_pos = i + 1;
		}
	}
	result.push_back(str.substr(cur_pos));
	return result;
}

void solution::excuteOperation(string opt, string opt1,string opt2,string opt3){
	int index1 = stoi(opt1.substr(1));
	int index2 = stoi(opt2.substr(1));
	int value2 = t_vars->at(index2);
	int index3 = -1, value3 = 0;

	if(opt.compare("addi") != 0)
	{
		index3 = stoi(opt3.substr(1));
		value3 = t_vars->at(index3);
	}
	else
	{
		value3 = stoi(opt3);
	}

	if(opt.compare("add") == 0 || opt.compare("addi") == 0)
	{
		t_vars->at(index1) = value2 + value3;
	}
	else if(opt.compare("sub") == 0)
	{
		t_vars->at(index1) = value2 - value3;
	}
	else if(opt.compare("mul") == 0)
	{
		t_vars->at(index1) = value2 * value3;
	}
	else if(opt.compare("div") == 0)
	{
		t_vars->at(index1) = value2 / value3;
	}
}
vector<int>* solution::alu(){
	//Initialize registered values
	vector<string> splitted_string = splitString(vect_lines[0]);
	unordered_map<string,int> label_map; //record the label and corresponding line
	unsigned int i = 0;
	for(i=0; i<splitted_string.size(); i++)
	{
		t_vars->push_back(stoi(splitted_string[i]));
	}

	vector<vector<string> > command_lines; //record the splitted command lines
	for(i=1; i<vect_lines.size()-1; i++)
	{
		command_lines.push_back(splitString(vect_lines[i]));
		if(command_lines[i-1][0].substr(0,5) == "label")
		{
			label_map[command_lines[i-1][0]] = i-1;
 		}
	}

	cout << cycle_of_completion << endl;
	i = 0;
	while(i < command_lines.size())
	{
		int new_i = i;
		if(command_lines[i][0].compare("b") == 0) //jump to label
		{
			new_i = label_map[command_lines[i][1]];
		}
		else if(command_lines[i][0].compare("beq") == 0)
		{
			int index1 = stoi(command_lines[i][1].substr(1));
			int index2 = stoi(command_lines[i][2].substr(1));
			if(t_vars->at(index1) == t_vars->at(index2))
			{
				new_i = label_map[command_lines[i][3]]; //jump to label
			}
		}
		else if(command_lines[i][0].compare("bnq") == 0)
		{
			int index1 = stoi(command_lines[i][1].substr(1));
			int index2 = stoi(command_lines[i][2].substr(1));
			if(t_vars->at(index1) != t_vars->at(index2))
			{
				new_i = label_map[command_lines[i][3]]; //jump to label
			}
		}
		else if(command_lines[i][0].substr(0,5).compare("label") == 0)
		{
			excuteOperation(command_lines[i][1],command_lines[i][2],command_lines[i][3],command_lines[i][4]);
			cycle_of_completion += 3;
		}
		else //add,addi,sub,mul,div
		{
			excuteOperation(command_lines[i][0],command_lines[i][1],command_lines[i][2],command_lines[i][3]);
			cycle_of_completion += 3;
		}
		dbg(vect_lines[i+1]);
		if(new_i == i) i++;
		else i = new_i;
	}
	cout << "end" << endl;
	return t_vars;
}


int solution::mips_clock() {
chrono::milliseconds timespan(clck);

this_thread::sleep_for(timespan);
static int cycle = 0;
if (cycle == 0 )
	cycle = 1;
else
	cycle = 0;
return cycle;

}


int main (int argc,char* argv[]) {

	//The following three lines are initializations of argc and argv, for submission they should be commented
	argc = 4;
	char* argv1[] = {"mips","assembly.txt","1","1"};
	argv = argv1;

	bool DEBUG = 0;
	int clck  = 100;

	//Makeing sure the file is supplied
	if (argc < 2){
		cout << "File not supplied" << endl;
                return 1;

	}
	if (argc >= 3) {
                clck = stoi(argv[2]); 
        }

	if (argc >= 4) {
		DEBUG = true;
	}
	
	ifstream infile(argv[1]);
	if(!infile){
		cout << "assembly file cannot be open!!ERROR" << endl;
		return 1;
	}
	string answer;
	getline(infile,answer);	
	cout << "answer is : " << answer <<endl;
	solution mips (infile,clck,DEBUG);
	cout << "after init" << endl;
	vector<int>* t_vars = mips.alu();
	
	cout << "your answer is : " <<endl;
	int i = 0;
	for (; i < t_vars->size()-1 ; i++){
		cout << t_vars->at(i) << ","; 
	}
	cout << t_vars->at(i) << endl;
	delete t_vars;
}

