#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ship {
    char name[21]; // name of ship
    int x, y;      // position
    char dir;      // direction ('L', 'R', 'U', 'D')
    struct ship *next; // pointer to next ship in linked list
} Ship;

Ship *head = NULL;

void add_ship(int x, int y, char dir, char *name) {
    Ship *new_ship = (Ship *)malloc(sizeof(Ship));
    new_ship->x = x;
    new_ship->y = y;
    new_ship->dir = dir;
    strcpy(new_ship->name, name);
    new_ship->next = head;
    head = new_ship;
}

void move_ships(int time, int w, int h) {
    Ship *curr = head;
    while (curr != NULL) {
        switch (curr->dir) {
            case 'L':
                curr->x = (curr->x - time + w) % w;
                break;
            case 'R':
                curr->x = (curr->x + time) % w;
                break;
            case 'U':
                curr->y = (curr->y + time) % h;
                break;
            case 'D':
                curr->y = (curr->y - time + h) % h;
                break;
        }
        curr = curr->next;
    }
}

void check_affected_ships(int x, int y, int w, int h, char **affected_ships, int *num_affected) {
    Ship *curr = head;
    while (curr != NULL) {
        // check if ship's position is affected by storm
        if (((curr->x >= x) && (curr->x < x + w)) && ((curr->y >= y) && (curr->y < y + h))) {
            // add ship's name to list of affected ships
            affected_ships[*num_affected] = (char *)malloc(sizeof(char) * 21);
            strcpy(affected_ships[(*num_affected)++], curr->name);
        }
        curr = curr->next;
    }
}

int main() {
    int w, h;
    scanf("%d %d", &w, &h);

    char command;
    while (scanf(" %c", &command) != EOF) {
        if (command == '1') {
            int x, y;
            char dir[21], name[21];
            scanf("%d %d %s %s", &x, &y, dir, name);
            add_ship(x, y, dir[0], name);
        } else if (command == '2') {
            int time;
            scanf("%d", &time);
            move_ships(time, w, h);
        } else if (command == '3') {
            int x, y, w, h;
            scanf("%d %d %d %d", &x, &y, &w, &h);
            char *affected_ships[1000];
            int num_affected = 0;
            check_affected_ships(x, y, w, h, affected_ships, &num_affected);
            printf("%d\n", num_affected);
            for (int i = 0; i < num_affected; i++) {
                printf("%s\n", affected_ships[i]);
                free(affected_ships[i]);
            }
        } else if (command == '4') {
          printf("Exitted");
            break;
        }
    }
    return 0;
}