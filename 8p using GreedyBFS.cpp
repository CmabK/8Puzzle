//SeemabKhan
//432826
//8 Puzzle problem using Greedy BFS 
//h1 distance from the original position 
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <sstream>

using namespace std;


struct PuzzleState {
    vector<vector<int>> board; 
    int cost; 
};


struct PuzzleStateCompare {
    bool operator()(const PuzzleState& state1, const PuzzleState& state2) const {
        return state1.cost > state2.cost;
    }
};

// Function to convert a 2D vector to a string for the ease of manipulation
string boardToString(const vector<vector<int>>& board) {
    stringstream ss;
    for (const auto& row : board) {
        for (int value : row) {
            ss << value << ' ';
        }
    }
    return ss.str();
}

// Manhattan distance heuristic for the 8-puzzle
int manhattanDistance(const vector<vector<int>>& board, const vector<vector<int>>& goal) {
    int distance = 0;
    int size = board.size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int value = board[i][j];
            if (value != 0) { // Skip the empty tile
                for (int k = 0; k < size; ++k) {
                    for (int l = 0; l < size; ++l) {
                        if (value == goal[k][l]) {
                            distance += abs(i - k) + abs(j - l);
                        }
                    }
                }
            }
        }
    }

    return distance;
}

// Neighboring states and enque in priority queue 
void exploreNeighbors(const PuzzleState& current, const vector<vector<int>>& goal,
                      priority_queue<PuzzleState, vector<PuzzleState>, PuzzleStateCompare>& pq,
                      unordered_set<string>& visited) {
    int size = current.board.size();
    
    // Find the empty tile (0)
    int emptyRow = -1, emptyCol = -1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (current.board[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                break;
            }
        }
        if (emptyRow != -1) break;
    }

    // Actions (up, down, left, right)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Neighboring states
    for (int i = 0; i < 4; ++i) {
        int newRow = emptyRow + dx[i];
        int newCol = emptyCol + dy[i];

        
        if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size) {
            
            PuzzleState neighbor = current;
            swap(neighbor.board[emptyRow][emptyCol], neighbor.board[newRow][newCol]);

            
            string neighborString = boardToString(neighbor.board);
            if (visited.find(neighborString) == visited.end()) {
                
                neighbor.cost = current.cost + manhattanDistance(neighbor.board, goal);
                pq.push(neighbor);
                visited.insert(neighborString);
            }
        }
    }
}

// Greedy Best-First Search function
void greedyBestFirstSearch(const vector<vector<int>>& initial, const vector<vector<int>>& goal) {
    int size = initial.size();

    // Priority queue for puzzle states to be explored
    priority_queue<PuzzleState, vector<PuzzleState>, PuzzleStateCompare> pq;

    // Explored states set
    unordered_set<string> visited;

    // Add the initial state to the priority queue
    PuzzleState start;
    start.board = initial;
    start.cost = manhattanDistance(initial, goal);
    pq.push(start);
    visited.insert(boardToString(initial));

    while (!pq.empty()) {
        
        PuzzleState current = pq.top();
        pq.pop();

        // Is current state the goal state ?
        if (current.board == goal) {
            cout << "Goal state reached!" << endl;
            
            return;
        }

        exploreNeighbors(current, goal, pq, visited);
    }

    cout << "Goal state not reachable!" << endl;
}



int main() {
   
    	cout <<"Greedy Breadth First Search  : Informed Search technique" << endl;
    vector<vector<int>> initial(3, vector<int>(3));

    // Input elements into initial matrix
    cout << "Enter the initial state : 3x3 matrix :\n";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            cout << "Enter value at position : " << i + 1 << "x" << j + 1 << ": ";
            cin >> initial[i][j];
        }
    }

    // Display the initial matrix 
    cout << "The initial state is as following:\n";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            cout << initial[i][j] << " ";
        }
        cout << endl;
    }

   vector<vector<int>> goal = {
    	{1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
   };

   
    greedyBestFirstSearch(initial, goal);

    return 0;
}
