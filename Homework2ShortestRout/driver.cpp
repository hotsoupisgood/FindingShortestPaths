#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Path
{
	vector<int> intersections;
	int total;
};

Path findShortestPath(vector<vector<int>> num, int startingPoint);
Path findShortestPath(vector<vector<int>> num, int point, int depth);



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

Path findShortestPath(vector<vector<int>> num, int startingPoint)
{
	Path path = findShortestPath(num, startingPoint, 0);
	return path;
}

Path findShortestPath(vector<vector<int>> num, int point, int depth)
{
	//base case: the last element in path
	if(depth == num.size() - 1)
	{
		Path path;
		path.total = num[depth][point];
		path.intersections.push_back(num[depth][point]);
		return path;
	}

	else
	{
		Path p1;
		Path p2;

		//if column is even: car can go to the same row index or index+1
		if(depth % 2 == 0)
		{
			p1 = findShortestPath(num, point, depth + 1);

			if(point < num[0].size() - 1) //check out of range
			{
				p2 = findShortestPath(num, point + 1, depth + 1);
			}
			else
			{
				p1.total += num[depth][point];
				p1.intersections.push_back(num[depth][point]);
				return p1;
			}
		}

		//if column is odd: car can go to the same row index or index-1
		else
		{
			p2 = findShortestPath(num, point, depth + 1);

			if(point != 0) //check out of range
			{
				p1 = findShortestPath(num, point - 1, depth + 1);
			}
			else
			{
				p2.total += num[depth][point];
				p2.intersections.push_back(num[depth][point]);
				return p2;
			}
		
		}

		//compare which of two paths is more effective and return it to the highest level
		if(p1.total < p2.total) 
		{
			p1.total += num[depth][point];
			p1.intersections.push_back(num[depth][point]);
			return p1;
		}
		else
		{
			p2.total += num[depth][point];
			p2.intersections.push_back(num[depth][point]);
			return p2;
		}
	}
}

int main()
{
	vector<vector<int>> numbers = readFile("numbers.txt");

	//Path path0 = findShortestPath(numbers, 0);
	
	for(int i = 0; i < numbers[0].size(); i++)
	{
		Path path = findShortestPath(numbers, i);

		cout << "Path " << i << " total: " << path.total << endl;

		cout << "Path " << i << ": ";
		for(int j = numbers.size() - 1; j >= 0; j--)
		{
			cout << path.intersections[j] << " ";
		}
		cout << endl << endl;
	}
	
	return 0;
}