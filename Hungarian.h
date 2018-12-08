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
		
		vector<int> get_PerfectMatching();
		//=======================
		int size;
		vector<vector<int>> Hmat;
	private:
		template <class U>
			int M_number(vector<U>, int);
		int M_number(vector<vector<int>>, int);
		vector<vector<bool>> build_vector_cover(vector<vector<int>>);
		void find_R(vector<vector<bool>>);
		void find_T(vector<vector<bool>>);

		bool has_PerfectMatch(vector<vector<bool>>);
		vector<int> find_PerfectMatch(vector<vector<bool>>, vector<int>, int);
		//=======================
		int epsilon;
		vector<int>	u;
		vector<int> v;
		vector<vector<int>> W; // Omega
		vector<bool> R;
		vector<bool> T;
};
