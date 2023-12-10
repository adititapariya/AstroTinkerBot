/*
* AstroTinker Bot (AB): Task 1B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#ifdef _linux_ // for host PC
#include <stdio.h>

void _put_byte(char c) {
    putchar(c);
}

void _put_str(char *str) {
    while (*str) {
        _put_byte(*str++);
    }
}

void print_output(uint8_t num) {
    if (num == 0) {
        putchar('0'); // if the number is 0, directly print '0'
        _put_byte('\n');
        return;
    }

    if (num < 0) {
        putchar('-'); // print the negative sign for negative numbers
        num = -num;   // make the number positive for easier processing
    }

    // convert the integer to a string
    char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
    uint8_t index = 0;

    while (num > 0) {
        buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
        num /= 10;                        // move to the next digit
    }

    // print the characters in reverse order (from right to left)
    while (index > 0) {
        putchar(buffer[--index]);
    }
    _put_byte('\n');
}

void _put_value(uint8_t val) {
    print_output(val);
}

#else // for the test device
void _put_value(uint8_t val) {}
void _put_str(char *str) {}
#endif

// Define your adjacency matrix for path planning
#define NUM_NODES 30

int adjacency_matrix[NUM_NODES][NUM_NODES] = {
  	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, };
	[0 1 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 ];
	[0 0 0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 1 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 0 ];
	[0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 ];
	[0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 ];
	[0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 ];
};

// Define your Node structure
typedef struct {
    int x;
    int y;
    int f;
    int g;
    int h;
    bool obstacle;
} Node;

// Define your map size
#define MAX_MAP_SIZE 10

// Define your map and A* specific variables here
Node map[MAX_MAP_SIZE][MAX_MAP_SIZE];
uint8_t path_planned[32];
uint8_t idx = 0;

// Function to initialize the map with obstacles
void initializeMap() {
    // Initialize the map with obstacles. For simplicity, we assume a 10x10 grid.
    for (int x = 0; x < MAX_MAP_SIZE; x++) {
        for (int y = 0; y < MAX_MAP_SIZE; y++) {
            map[x][y].x = x;
            map[x][y].y = y;
            map[x][y].f = 0;
            map[x][y].g = 0;
            map[x][y].h = 0;
            map[x][y].obstacle = false; // Set obstacles as needed
        }
    }
}

// A* Algorithm
void AStar(int start_x, int start_y, int end_x, int end_y) {
    // Define possible movement directions (up, down, left, right, diagonals)
    int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // Create an open list to store nodes to be evaluated
    Node openList[MAX_MAP_SIZE * MAX_MAP_SIZE];
    int openListSize = 0;

    // Create a closed list to store nodes that have already been evaluated
    bool closedList[MAX_MAP_SIZE][MAX_MAP_SIZE];
    for (int i = 0; i < MAX_MAP_SIZE; i++) {
        for (int j = 0; j < MAX_MAP_SIZE; j++) {
            closedList[i][j] = false;
        }
    }

    // Set the initial values for the start node
    map[start_x][start_y].g = 0;
    map[start_x][start_y].h = abs(end_x - start_x) + abs(end_y - start_y);
    map[start_x][start_y].f = map[start_x][start_y].g + map[start_x][start_y].h;

    // Add the start node to the open list
    openList[openListSize++] = map[start_x][start_y];

    // A* algorithm loop
    while (openListSize > 0) {
        // Find the node with the lowest f value in the open list
        int minFIndex = 0;
        for (int i = 1; i < openListSize; i++) {
            if (openList[i].f < openList[minFIndex].f) {
                minFIndex = i;
            }
        }

        // Set the current node to the node with the lowest f value
        int current_x = openList[minFIndex].x;
        int current_y = openList[minFIndex].y;

        // Remove the current node from the open list
        for (int i = minFIndex; i < openListSize - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListSize--;

        // Mark the current node as evaluated (in the closed list)
        closedList[current_x][current_y] = true;

        // Check if the current node is the end node
        if (current_x == end_x && current_y == end_y) {
            // Reconstruct the path and store it in the path_planned array
           int path_x = end_x;
	int path_y = end_y;
	while (path_x != start_x || path_y != start_y) {
	    path_planned[idx++] = path_x;
	    int temp_y = path_y;
	    path_y = map[path_x][path_y].y;
	    path_x = map[path_x][temp_y].x;
	}
	path_planned[idx++] = start_x;
            break; // Path found, exit the loop
        }

        // Explore the neighbors of the current node
        for (int dir = 0; dir < 8; dir++) {
            int new_x = current_x + dx[dir];
            int new_y = current_y + dy[dir];

            // Check if the new coordinates are within the map boundaries and not an obstacle
            if (new_x >= 0 && new_x < MAX_MAP_SIZE && new_y >= 0 && new_y < MAX_MAP_SIZE &&
                !map[new_x][new_y].obstacle) {
                // Calculate tentative g value
                int tentative_g = map[current_x][current_y].g + 1;

                // Check if this path is better than the previous one
                if (tentative_g < map[new_x][new_y].g) {
                    // Update the new node's values
                    map[new_x][new_y].x = current_x;
                    map[new_x][new_y].y = current_y;
                    map[new_x][new_y].g = tentative_g;
                    map[new_x][new_y].h = abs(end_x - new_x) + abs(end_y - new_y);
                    map[new_x][new_y].f = map[new_x][new_y].g + map[new_x][new_y].h;

                    // Add the new node to the open list
                    openList[openListSize++] = map[new_x][new_y];
                }
            }
        }
    }
}

// main function
int main(int argc, char const *argv[]) {

    #ifdef _linux_

    const uint8_t START_POINT = atoi(argv[1]);
    const uint8_t END_POINT = atoi(argv[2]);
    uint8_t CPU_DONE = 0;

    #else

    #define START_POINT (* (volatile uint8_t * ) 0x20000000)
    #define END_POINT (* (volatile uint8_t * ) 0x20000001)
    #define CPU_DONE (* (volatile uint8_t * ) 0x20000003)

    #endif

    // Array to store the planned path
    uint8_t path_planned[30];
    uint8_t idx = 0;

    // Instead of using printf() function for debugging,
    // use the below function calls to print a number, string, or a newline

    // For newline: _put_byte('\n');
    // For string:  _put_str("your string here");
    // For number:  _put_value(your_number_here);

    // Examples:
    // _put_value(START_POINT);
    // _put_value(END_POINT);
    // _put_str("Hello World!");
    // _put_byte('\n');

    // ############# Add your code here #############

    int start_x, start_y, end_x, end_y;

    #ifdef _linux_
    start_x = 0;  // Define your start_x and start_y here
    start_y = 0;
    end_x = 2;    // Define your end_x and end_y here
    end_y = 8;
    #endif

    // Initialize your map and run the A* algorithm
    initializeMap();
    AStar(start_x, start_y, end_x, end_y);

    // Reconstruct the path and store it in the path_planned array
    int path_x = end_x;
    int path_y = end_y;
    while (path_x != start_x || path_y != start_y) {
        path_planned[idx++] = path_x;
        int temp_x = map[path_x][path_y].x;
        path_y = map[path_x][path_y].y;
        path_x = temp_x;
    }
    path_planned[idx++] = start_x;

    // #############################################

    #ifdef _linux_ // for host PC

    _put_str("######### Planned Path #########\n");
    for (int i = idx - 1; i >= 0; --i) {
        _put_value(path_planned[i]);
    }
    _put_str("################################\n");

    #endif

    return 0;
}
