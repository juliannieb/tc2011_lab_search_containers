#include "utils.h"

Node* dfSearch(Node *head, int limit, vsc final_state, setvsc &visited){
	vsc frontierState = vsc();
	Node *frontier = head;
	int stateSize;
	int costSoFar;
	frontierState = frontier->state;
	stateSize = frontierState.size();
	costSoFar = frontier->cost_so_far;
	if (isFinalState(frontierState, final_state)) {
		return frontier;
	}
	else{
		for (int i = 0; i < stateSize; i ++){
			for (int j = 0; j < stateSize; j++){
				if (i != j && frontierState[i].size() > 0 && frontierState[j].size() < limit){
					vsc newState = frontierState;
					char char_to_change = newState[i].top();
					newState[i].pop();
					newState[j].push(char_to_change);
					if (!visited.count(newState)){
						ii movement = ii(i, j);
						int newCost = 1 + abs(i - j) + costSoFar;
						Node *newNode = new Node;
						Node *ans = new Node;
						newNode -> parent = frontier;
						newNode -> state = newState;
						newNode -> movement = movement;
						newNode -> cost_so_far = newCost;
						visited.insert(newState);
						ans = dfSearch(newNode, limit, final_state, visited);
						if (ans != NULL){
							return ans;
						}
					}
				}
			}
		}
	}
	return NULL;
}

Node* dfs(Node *head, int limit, vsc final_state){
	setvsc visited = setvsc();
	Node *ans = new Node;
	ans = dfSearch(head, limit, final_state, visited);
	if (ans == NULL)
		return NULL;
	else
		return ans;
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

	Node*ans = dfs(head, limit, final_state);
	if (ans == NULL)
		cout << "No solution found" << endl;
	else 
		backTrack(ans);

	return 0;
}