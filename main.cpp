#include "Hungarian.h"
#include <vector>

int main(){
	vector<vector<int>> matrix{ {4,1,6,2,3},
								{5,0,3,7,6},
								{2,3,4,5,8},
								{3,4,6,3,4},
								{4,6,5,8,6}
							  };
	int a;
	cin >> a;
	cout << a;

	HungarianMatrix H(5,matrix);
	vector<int> R;
	R=H.get_PerfectMatching();
	int weight=0;
	for(int i=0;i<H.size;i++){
		weight += matrix[i][R[i]];
	}
	cout << weight << endl;
}
