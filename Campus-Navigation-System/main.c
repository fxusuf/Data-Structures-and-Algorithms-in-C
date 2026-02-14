#include <stdio.h>
#include <stdbool.h>

#define BUILDING_COUNT 9

char *buildings[BUILDING_COUNT] = {
    "Faculty of Engineering", "Canteen", "Library", 
    "Dining Hall", "Sports Hall", "Rectorate", 
    "Faculty of Maritime", "Faculty of Architecture", "Nejla Uysen"
};

int matrix[BUILDING_COUNT][BUILDING_COUNT];

void create_graph() {
    for(int i=0; i<BUILDING_COUNT; i++) {
        for(int j=0; j<BUILDING_COUNT; j++) {
            matrix[i][j] = 0;
        }
    }

    // 0:Engineering - 1:Canteen
    matrix[0][1] = 1; matrix[1][0] = 1;
    // 0:Engineering - 7:Architecture
    matrix[0][7] = 1; matrix[7][0] = 1;
    // 1:Canteen - 4:Sports Hall
    matrix[1][4] = 1; matrix[4][1] = 1;
    // 7:Architecture - 6:Maritime
    matrix[7][6] = 1; matrix[6][7] = 1;
    // 6:Maritime - 5:Rectorate
    matrix[6][5] = 1; matrix[5][6] = 1;
    // 5:Rectorate - 2:Library
    matrix[5][2] = 1; matrix[2][5] = 1;
    // 2:Library - 3:Dining Hall
    matrix[2][3] = 1; matrix[3][2] = 1;
    // 3:Dining Hall - 4:Sports Hall
    matrix[3][4] = 1; matrix[4][3] = 1;   
    // 8:Nejla Uysen is disconnected, so no edges added
}

void bfs_find_path(int start, int target) {
    int queue[BUILDING_COUNT]; // To queue the places we will visit
    int front = 0, rear = 0;   // Front and rear of the queue
    bool visited[BUILDING_COUNT] = {false}; // Mark visited places
    int previous[BUILDING_COUNT]; // To remember the path

    for(int i=0; i<BUILDING_COUNT; i++) previous[i] = -1;
    
    visited[start] = true;
    queue[rear++] = start; 

    bool found = false;

    while(front < rear) { 
        int current = queue[front++];

        if(current == target) {
            found = true;
            break;
        }

        // Visiting neighbors
        for(int i=0; i<BUILDING_COUNT; i++) {
            if(matrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                previous[i] = current; 
                queue[rear++] = i; 
            }
        }
    }

    if(found) {
        int path[BUILDING_COUNT];
        int step = 0;
        int temp = target;
        
        while(temp != -1) {
            path[step++] = temp;
            temp = previous[temp];
        }

        printf("\nSHORTEST PATH: ");
        for(int i=step-1; i>=0; i--) {
            printf("%s", buildings[path[i]]);
            if(i > 0) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nUnfortunately, there is no path between these two buildings!\n");
    }
}

void dfs(int building, bool visited[]) {
    visited[building] = true;
    printf("%s, ", buildings[building]);

    for(int i=0; i<BUILDING_COUNT; i++) {
        if(matrix[building][i] == 1 && !visited[i]) {
            dfs(i, visited);
        }
    }
}

void disconnected_area_analysis() {
    bool visited[BUILDING_COUNT] = {false};
    int region_count = 0;

    printf("\n--- (DFS) ---\n");
    for(int i=0; i<BUILDING_COUNT; i++) {
        if(!visited[i]) {
            region_count++;
            printf("Region %d: ", region_count);
            dfs(i, visited);
            printf("\n");
        }
    }

    if(region_count > 1) {
        printf("RESULT: There are disconnected areas on the campus.\n");
    } else {
        printf("RESULT: All buildings are connected to each other.\n");
    }
}

int main() {
    create_graph();
    
    int start, target;

    printf("--- CAMPUS NAVIGATION SYSTEM ---\n");
    printf("Buildings and their Codes:\n");
    for(int i=0; i<BUILDING_COUNT; i++) {
        printf("%d: %s\n", i, buildings[i]);
    }

    printf("\nEnter the code of the starting building (0-8): ");
    scanf("%d", &start);

    printf("Enter the code of the target building (0-8): ");
    scanf("%d", &target);

    if(start >= 0 && start < BUILDING_COUNT && target >= 0 && target < BUILDING_COUNT) {
        bfs_find_path(start, target);
    } else {
        printf("Invalid building code entered!\n");
    }

    disconnected_area_analysis();

    return 0;
}