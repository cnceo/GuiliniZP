#pragma once

#include <iostream>
#include <vector>
using namespace std;
class Win
{
public:
	static Win* Instance;
	static Win* getInstance();

	void setVector(int type, int value);
	void getVector();
	void clearVector();

public:
	vector<int > m_vec[2];
private:

	Win();
	~Win();
};

