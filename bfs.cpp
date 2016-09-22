#include "utils.h"

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

int main () {
	pipvsc input = readInput();
	int limit;
	vsc initial_state, final_state;
	limit = input.first;
	initial_state = input.second.first;
	final_state = input.second.second;

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