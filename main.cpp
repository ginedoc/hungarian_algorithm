#include "Hungarian.h"
#include <vector>

int main(){
	/*
	vector<vector<int>> matrix{ {4,1,6,2,3},
								{5,0,3,7,6},
								{2,3,4,5,8},
								{3,4,6,3,4},
								{4,6,5,8,6}
							  };
	*/
	vector<vector<int>> matrix;
	int n;
	cin >> n;

	vector<int> temp(n, 0);
	for(int i=0; i<n; i++){
		matrix.push_back(temp);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> matrix[i][j];
		}
	}

	HungarianMatrix H(n,matrix);
	vector<int> R;
	R=H.get_PerfectMatching();
	int weight=0;
	for(int i=0;i<H.size;i++){
		weight += matrix[i][R[i]];
	}
	cout << weight << endl;
}
