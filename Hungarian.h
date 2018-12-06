#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

vector<vector<int>> Zeros2D(int x, int y);
int get_Mmin(vector<vector<int>>);
int get_Mmax(vector<vector<int>>);
template <class T>
	T get_Mmin(vector<T>);
template <class T>
	T get_Mmax(vector<T>);
void printM(vector<vector<int>>);
template <class T>
	void printM(vector<T>);

class HungarianMatrix{
	public:
		HungarianMatrix();
		HungarianMatrix(int size, vector<vector<int>> matrix);
		
		vector<vector<int>> get_PerfectMatching();
		//=======================
		int size;
		vector<vector<int>> Hmat;
	private:
		template <class U>
			int M_zero_number(vector<U>);
		int M_zero_number(vector<vector<int>>);
		//=======================
		int epsilon;
		vector<int>	u;
		vector<int> v;
		vector<vector<int>> W; // Omega
		vector<bool> R;
		vector<bool> T;
};
