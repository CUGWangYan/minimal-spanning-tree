#include "Prim.h"
#include "Kruskal.h"
using namespace std;
int main() {
	Graphlnk<int,int> G;
	cin >> G;
	MinSpanTree<int, int>MST;
	Kruskal<int,int>(G,MST);
	//Prim(G, 1, MST);//ÆðÊ¼¶¥µã
	cout <<endl<< MST << endl;
	int a;
	cin >> a;
	return 0;
}