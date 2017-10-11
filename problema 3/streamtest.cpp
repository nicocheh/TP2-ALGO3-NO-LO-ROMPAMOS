#include <iostream>
#include <fstream>
#include <string>


using namespace std;

ifstream fin("streamtest.in");
ofstream fout("streamtest.out");

int main(){
	
	string s;
	fin >> s;
	fin >> s;
	cout << s;
	
	fout << s;
	
	return 0;
}




