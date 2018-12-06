#include "Hungarian.h"
#include <vector>

int main(){
	vector<vector<int>> matrix{ {4,1,6,2,3},
								{5,0,3,7,6},
								{2,3,4,5,8},
								{3,4,6,3,4},
								{4,6,5,8,6}
								};

	HungarianMatrix H(5,matrix);
	H.get_PerfectMatching();
}
