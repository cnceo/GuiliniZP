#include "Win.h"

Win::Win()
{
}

Win::~Win()
{
}

Win*Win:: Instance =  nullptr;

 Win* Win::getInstance()
 {
	 if (Instance == nullptr)
	 {
		 Instance = new Win();
	 }
	 return Instance;
 }

 void Win::setVector(int type, int value)
 {
	 m_vec[type].push_back(value);
 }

 void Win::clearVector()
 {
	 for (int i = 0; i < 2;i++)
	 {
		 m_vec[i].clear();
	 }
 }
