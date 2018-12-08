#include "Hungarian.h"

/* Constructor */
HungarianMatrix::HungarianMatrix(){

}
HungarianMatrix::HungarianMatrix(int size, vector<vector<int>> matrix):size(size), Hmat(matrix){
	u.resize(size);
	v.resize(size);
	R.resize(size); fill(R.begin(), R.end(), false);
	T.resize(size); fill(T.begin(), T.end(), false);
	W.assign(Hmat.begin(), Hmat.end());

	// set v
	for(int i = 0; i < size; i++){
		v[i] = 0;
	}
}

template <class U>
int HungarianMatrix::M_zero_number(vector<U> M){
	int num=0;
	for(auto it=M.begin(); it!=M.end(); it++){
		if(*it==0) num++;
	}
	return num;
}

int HungarianMatrix::M_zero_number(vector<vector<int>> M){
	int num=0;
	for(auto it=M.begin(); it!=M.end(); it++){
	for(auto it1=(*it).begin(); it1!=(*it).end(); it1++){
		if(*it1==0) num++;
	}
	}
	return num;
}

vector<int> HungarianMatrix::get_PerfectMatching(){
	
/*	ini: - u = max(W_row)
 *		 - v = 0
 *		------------------
 *		 - remove u[i] in W_row
 *		 - build M
 *		 - find R, T
 *	step 1: is M perfect matching?
 *	step 2: e = min(u+v-w) ,(xR, xT)
 *			u = u+e	(xR)
 *			v = v-e (T)
 *			w = w-e (xR, xT)
 *	step 3: find R, T -> goto step 1
 */

	// init
	for(int i = 0; i < size; i++){
		u[i] = get_Mmax(W[i]);
		v[i] = 0;
		for(int j = 0; j < size; j++){
			W[i][j] = u[i]+v[j]-W[i][j];
		}
	}

	vector<vector<bool>> M;
	M = build_vector_cover(W);

	find_R(M);
	find_T(M);

	while(!has_PerfectMatch(M)){
		// e
		vector<bool> R_reverse;
		vector<bool> T_reverse;
		R_reverse.assign(R.begin(), R.end());
		T_reverse.assign(T.begin(), T.end());
		R_reverse.flip();
		T_reverse.flip();

		epsilon = INT_MAX;
		for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(R_reverse[i] && T_reverse[j]){
				if((W[i][j]) < epsilon)	epsilon = W[i][j];
			}
		}
		}	
		// u, v, W	
		for(int i = 0; i < size; i++){
			if(R_reverse[i]) u[i] -= epsilon;
			if(T[i]) v[i] += epsilon;
			// W
			for(int j = 0; j <size; j++){
				if(R_reverse[i]&&W[i][j]!=0) W[i][j] -= epsilon;
				if(T[j]&&W[i][j]!=0) W[i][j] += epsilon;
			}
		}

		M = build_vector_cover(W);
		// R, T
		find_R(M);
		find_T(M);
	}
	vector<int> P(size, 0);
	return find_PerfectMatch(M, P, 0);
}
bool HungarianMatrix::has_PerfectMatch(vector<vector<bool>> M){
	if(M.size()==2){
		if(M[0][1]==true && M[1][0]) return true;
		if(M[1][0]==true && M[0][1]) return true;
		return false;
	}
	for(int i=0; i<size; i++){
		if(M[0][i]==true){
			vector<vector<bool>> m;
			m.assign(M.begin(), M.end());
			m.erase(m.begin());	// remove first row
			for(int j=0;j<m.size();j++){	// remove first column
				m[j].erase(m[j].begin());
			}
			return has_PerfectMatch(m);
		}
	}
	return false;
}

vector<int> HungarianMatrix::find_PerfectMatch(vector<vector<bool>> M, vector<int> P, int index){
	if(index==size) return P;

	for(int i = index; i < size; i++){
		for(int j = 0; j < size; j++){
			if((M[i][j]==true) && (count(P.begin(), P.begin()+index+1, j)<1)){
				P[i] = j;
			   	return find_PerfectMatch(M, P, index+1);
			}
		}
	}

	return P;
}
vector<vector<bool>> HungarianMatrix::build_vector_cover(vector<vector<int>> M){
	vector<vector<bool>> V(size, vector<bool>(size));


	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(M[i][j] == 0) V[i][j] = true;
			else			 V[i][j] = false;
		}
	}

	return V;
}
void HungarianMatrix::find_R(vector<vector<bool>> V){	
	for(int i = 0; i < size; i++){
		int num=0;
		int zeroPos=-1;		
		// row
		if(M_zero_number(V[i]) == (size-1)){
			for(int j = 0; j < size; j++){
				if(V[i][j] == true){
					zeroPos = j;
					break;
				}
			}
			// col
			num = 0;
			for(int j = 0; j < size; j++){
				if(V[j][zeroPos]==true) num++;
				if(num>1) break;
			}
			if(num==1) R[i] = true;
		}
	}
	
}

void HungarianMatrix::find_T(vector<vector<bool>> V){	
	int num;
	for(int i = 0; i < size; i++){
		num = 0;
		for(int j = 0; j < size; j++){
			if(V[j][i] == true) num++; 
		}
		if(num>1) T[i] = true;
	}
}

/* private */

vector<vector<int>> Zeros2D(int x, int y){
	vector<vector<int>> X;
	vector<int> Y(y,0);
	
	for(int i = 0; i < x; i++){
		X.push_back(Y);
	}

	return X;
}

int get_Mmin(vector<vector<int>> M){
	int min = M[0][0];
	int sx = M[0].size();
	int sy = M.size();
	for(int i=0;i<sx;i++)
	for(int j=0; j<sy;j++)
		if(M[i][j]<min) min = M[i][j];

	return min;
				
}
template <class T>
T get_Mmin(vector<T> M){
	T min = M[0];
	for(int i=0;i<M.size();i++)
		if(M[i]<min) min = M[i];
	return min;
}
int get_Mmax(vector<vector<int>> M){
	int max = M[0][0];
	int sx = M[0].size();
	int sy = M.size();
	for(int i=0;i<sx;i++)
	for(int j=0; j<sy;j++)
		if(M[i][j]>max) max = M[i][j];
	return max;
}
template <class T>
T get_Mmax(vector<T> M){
	T max = M[0];
	for(int i=0;i<M.size();i++)
		if(M[i]>max) max = M[i];
	return max;
}
void printM(vector<vector<int>> M){
	for(auto iter = M.begin(); iter != M.end(); iter++){
		for(auto iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++){
			cout << *iter2 << " " ;
		}
		cout << endl;
	}
	cout << endl;
}
template <class T>
void printM(vector<T> M){
	for(auto iter = M.begin(); iter != M.end(); iter++){
		cout << *iter << " ";
	}
	cout << endl;
}

