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
	printState(currState);
	printState(final_state);
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

Node* bfs(Node *head, int limit, vsc final_state) {
	setvsc visited = setvsc();
	queueNode frontierQueue = queueNode();
	if (head != NULL) {
		frontierQueue.push(head);
		visited.insert(head -> state);
	}
	while(!frontierQueue.empty()) {
		Node *frontier = frontierQueue.front();
		frontierQueue.pop();
		vsc frontierState = frontier -> state;
		int cost_so_far = frontier -> cost_so_far;
		for (int i = 0; i < frontierState.size(); i++) {
			for (int j = 0; j < frontierState.size(); j++) {
				if (i != j && frontierState[i].size() > 0 && frontierState[j].size() < limit) {
					vsc newState = frontierState;
					char char_to_change = newState[i].top();
					newState[i].pop();
					newState[j].push(char_to_change);

					if (!visited.count(newState)) {
						cout << i << ", " << j << endl;
						ii movement = ii(i, j);
						int newCost = 1 + abs(i - j) + cost_so_far;
						Node *newNode = new Node;
						newNode -> parent = frontier;
						newNode -> state = newState;
						newNode -> movement = movement;
						newNode -> cost_so_far = newCost;
						visited.insert(newState);

						if (isFinalState(newState, final_state)) {
							return newNode;
						}

						frontierQueue.push(newNode);

					}
					
				}
			}
		}
	}
	return NULL;
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
		cout << "(" << curr_step.first << "," << curr_step.second << ")" << endl;
		steps.pop();
	}
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

	Node *head = new Node;
	head -> parent = NULL;
	head -> state = initial_state;
	head -> movement = ii(0, 0);
	head -> cost_so_far = 0;

	Node *ans = bfs(head, limit, final_state);
	if (ans == NULL)
		cout << "No solution found" << endl;
	else 
		backTrack(ans);

	return 0;
}