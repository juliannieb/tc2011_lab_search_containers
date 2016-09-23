#include "utils.h"

int heuristic1(char c) {
	return 0;
}

Node* aStar(Node *head, int limit, vsc final_state) {
	setvsc visited = setvsc();
	priorityQueuePIN frontierPriorityQueue = priorityQueuePIN();
	if (head != NULL) {
		int cost = 0;
		pairIntNode headElement = pairIntNode(cost, head);
		frontierPriorityQueue.push(headElement);
		visited.insert(head -> state);
	}
	while(!frontierPriorityQueue.empty()) {
		pairIntNode frontierElement = frontierPriorityQueue.top();
		Node *frontier = frontierElement.second;
		frontierPriorityQueue.pop();
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
						int newHeuristicCost = newCost + heuristic1(char_to_change);
						Node *newNode = new Node;
						newNode -> parent = frontier;
						newNode -> state = newState;
						newNode -> movement = movement;
						newNode -> cost_so_far = newCost;
						visited.insert(newState);
						if (isFinalState(newState, final_state)) {
							return newNode;
						}
						frontierPriorityQueue.push(pairIntNode(newHeuristicCost, newNode));
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

	Node *ans = aStar(head, limit, final_state);
	if (ans == NULL)
		cout << "No solution found" << endl;
	else 
		backTrack(ans);

	return 0;
}