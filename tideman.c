#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool cycle_detection(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Update the ranks based on the vote casted
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the preferences of ranks[i] over ranks[j]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Add the winner and loser to the pairs of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Sort the pairs by using selection sort
    int largest = 0;
    int largest_index = 0;
    pair temp;

    for (int i = 0; i < pair_count; i++)
    {
        largest = preferences[pairs[i].winner][pairs[i].loser];
        largest_index = i;

        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > largest)
            {
                largest = preferences[pairs[j].winner][pairs[j].loser];
                largest_index = j;
            }
        }

        temp = pairs[i];
        pairs[i] = pairs[largest_index];
        pairs[largest_index] = temp;
    }

    return;
}

// Detect cycle in the graph
bool cycle_detection(int winner, int loser)
{
    // Base case: Cycle detected when winner is equal to loser (re-visiting the winner, so there is a cycle)
    if (winner == loser)
    {
        return true;
    }

    // Backtracking and exhaust all the possible previous candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check whether the loser points to anyeone (any of all the possible candidates)
        if (locked[loser][i] == true)
        {
            if (cycle_detection(winner, i) == true)
            {
                return true;
            }
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Lock all the pairs when there is no cycle in the graph
    for (int i = 0; i < pair_count; i++)
    {
        // Detect for cycle, lock pairs when there is no cycle
        if (cycle_detection(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Print the winner in the graph
    string winner = "";
    int check[MAX] = {0};

    // Go through locked 2D array and mark the column that has all false
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                check[j] += 1;
            }
        }
    }

    // Column with all falses is the final winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (check[i] == 0)
        {
            winner = candidates[i];
        }
    }

    printf("%s\n", winner);
    return;
}