#include <stdio.h>
#include <string.h>

char currentPage[50] = "google.com"; // Default starting page
char backStack[20][50];   
int backTop = -1;     

char forwardStack[20][50];  
int forwardTop = -1;      

void visit() {
    char newUrl[50];
    printf("Enter the site you want to visit: ");
    scanf("%s", newUrl);

    backTop++;
    strcpy(backStack[backTop], currentPage);

    strcpy(currentPage, newUrl);

    forwardTop = -1; // Clear forward history when a new site is visited
}

void back() {
    if (backTop == -1) {
        printf("WARNING: No page to go back to!\n");
        return;
    }

    forwardTop++;
    strcpy(forwardStack[forwardTop], currentPage);

    strcpy(currentPage, backStack[backTop]);
    backTop--; 
}

void forward() {
    if (forwardTop == -1) {
        printf("WARNING: No page to go forward to!\n");
        return;
    }

    backTop++;
    strcpy(backStack[backTop], currentPage);

    strcpy(currentPage, forwardStack[forwardTop]);
    forwardTop--; 
}

void printStatus() {
    printf("\n--- STATUS ---\n");
    printf("ACTIVE PAGE: %s\n", currentPage);
    
    printf("Back List: [ ");
    for(int i=0; i<=backTop; i++) printf("%s ", backStack[i]);
    printf("]\n");

    printf("Forward List: [ ");
    for(int i=0; i<=forwardTop; i++) printf("%s ", forwardStack[i]);
    printf("]\n");
    printf("----------------\n");
}

int main() {
    int choice;
    
    while(1) {
        printStatus();
        printf("1. Visit Site\n");
        printf("2. Back\n");
        printf("3. Forward\n");
        printf("4. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        if (choice == 1) visit();
        else if (choice == 2) back();
        else if (choice == 3) forward();
        else if (choice == 4) break;
        else printf("Invalid choice!\n");
    }

    return 0;
}