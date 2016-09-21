#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

typedef stack<char> sc;
typedef vector<sc> vsc;
typedef pair<vsc, vsc> pvsc;
typedef pair<int, int> ii;
typedef pair<int, pvsc> pipvsc;

struct node {
	struct node *parent;
	vsc state;
	pair<int, int> movement;
};

typedef struct node Node;
typedef queue<Node*> queueNode;

void printState(vsc state) {
	cout << "{ ";
	for (int i = 0; i < state.size(); i++) {
		sc aux = sc();
		sc copy = state[i];
		while(!copy.empty()) {
			char c = copy.top();
			aux.push(c);
			copy.pop();
		}
		cout << "[";
		int j = 0;
		while(!aux.empty()) {
			char c = aux.top();
			cout << (j != 0 ? ", " : "") << c;
			j++;
			aux.pop();
		}
		cout << "]";
	}
	cout << " }\n";
}

vsc createState(string line) {
	vsc state = vsc(0, sc());
	sc temp_stack = sc();
	state.push_back(temp_stack);

	int curr_vec_idx = 0;
	for (int i = 0; i < line.size(); i++) {
		char c = line[i];
		if (isalpha(c)) {
			state[curr_vec_idx].push(c);
		}
		if (c == ';') {
			curr_vec_idx++;
			state.push_back(sc());
		}
	}
	return state;
}

pipvsc readInput() {
	int limit;
	scanf("%i%*c", &limit);
	string line2, line3;
	getline (cin, line2);
	getline (cin, line3);

	//cout << limit << " - " << line2 << " - " << line3 << endl;

	vsc initial_state = createState(line2);
	vsc final_state = createState(line3);

	pipvsc ans = pipvsc(limit, pvsc(initial_state, final_state));
	return ans;
}

Node* bfs(Node *head) {

}

int main () {
	pipvsc input = readInput();
	int limit;
	vsc initial_state, final_state;
	limit = input.first;
	initial_state = input.second.first;
	final_state = input.second.second;

	printState(initial_state);
	printState(final_state);

	return 0;
}