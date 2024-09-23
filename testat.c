#include <stdio.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

typedef struct {
    int id;
} Fork;

int main() {
    const char* philosophers[NUM_PHILOSOPHERS] = {
        "Philosopher 0",
        "Philosopher 1",
        "Philosopher 2",
        "Philosopher 3",
        "Philosopher 4"
    };

    Fork forks[NUM_PHILOSOPHERS];

    // Initialize forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks[i].id = i; // Assign an ID to each fork
    }

    // Print each philosopher's left and right fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        Fork left_fork = forks[i];
        Fork right_fork = forks[(i + 1) % NUM_PHILOSOPHERS];
        printf("%s has left fork %d and right fork %d\n",
               philosophers[i], left_fork.id, right_fork.id);
    }

    return 0;
}
/*

  p0 p1 p2 p3
 f0 f1 f2 f3

*/