#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <string>

using namespace std;

typedef stack<char> sc;
typedef vector<sc> vsc;
typedef pair<vsc, vsc> pvsc;
typedef pair<int, int> ii;
typedef pair<int, pvsc> pipvsc;
typedef set<vsc> setvsc;

struct node {
	struct node *parent;
	vsc state;
	ii movement;
	int cost_so_far;
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

bool isFinalState(vsc currState, vsc final_state) {
	//printState(currState);
	//printState(final_state);
	//cout << endl;
	bool match = true;
	for (int i = 0; i < final_state.size(); i++) {
		if (!final_state[i].empty() && final_state[i].top() == 'X') {
			continue;
		}
		else if (final_state[i].empty() && !currState[i].empty()) {
			match = false;
			break;
		}
		else if (!final_state[i].empty() && currState[i].empty()) {
			match = false;
			break;
		}
		else {
			while(!final_state[i].empty() && !currState[i].empty()) {
				char c_final = final_state[i].top();
				char c_curr = currState[i].top();
				final_state[i].pop();
				currState[i].pop();
				if (c_final != c_curr) {
					match = false;
					break;
				}
			}
			if (!final_state[i].empty() || !currState[i].empty()) {
				match = false;
				break;
			}
			if (!match) {
				break;
			}
		}
	}
	return match;
}


void backTrack(Node *endState) {
	Node *curr = endState;
	if (endState != NULL) {
		cout << "Total cost = " << endState -> cost_so_far << endl;
	}
	stack< pair<int, int> > steps = stack<pair<int, int> >();
	while(curr != NULL) {
		if (curr -> parent != NULL)
			steps.push(curr -> movement);
		curr = curr -> parent;
	}
	while(!steps.empty()) {
		ii curr_step = steps.top();
		//cout << "(" << curr_step.first << "," << curr_step.second << ")" << endl;
		steps.pop();
	}
}