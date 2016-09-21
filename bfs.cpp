#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>

using namespace std;

typedef stack<char> sc;
typedef vector<sc> vsc;

struct Node {
	struct Node *parent;
	vsc state;
	pair<int, int> movement;
};

int main () {
	
	return 0;
}