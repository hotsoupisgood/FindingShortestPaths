#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//function reads numbers from file and write numbers to vector<vector<int>>
vector<vector<int>> readFile(const char* fileName)
{
	ifstream iFile(fileName);
	if(iFile.fail()) exit(1);

	vector<vector<int>> arr;
	vector<string> lines;
	int number = 0;
	char aChar = ' ';
	string str = "";	

	//read from file and write each line as a string to vector<string> lines
	while(!iFile.eof())
	{
		str += aChar;
		iFile.get(aChar);
		
		if(aChar == '\n')
		{
			lines.push_back(str);
			str = "";
		}				
	}
	lines.push_back(str); //write last line (it doesn't have '\n')

	iFile.close();

	//parse vector<string> to integers and put integers to vector<vector<int>>
	for(int i = 0; i < lines.size(); i++)
	{
		vector<int> tempVec;
		stringstream mySS;
		mySS.str(lines[i]);
		while(mySS >> number)
		{
			tempVec.push_back(number);
		}
			arr.push_back(tempVec);
	}

	return arr;
}



int main()
{
	int capacity = 100;
	vector<vector<int>> numbers = readFile("numbers.txt");

	//print numbers
	for(int i = 0; i < numbers.size(); i++)
	{
		for(int j = 0; j < numbers[i].size(); j++)
		{
			cout << numbers[i][j] << " ";
		}
		cout << endl;
	}
	

	return 0;
}