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
} pair;

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    // ranks[0] tells me index number in candidates[] of their (1)st preference
    // theyd prefer rank 0 over rank 1, rank 2...rank candidate_count
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int l = 0;
    //preferences[i][j] means i is preferred to j
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[l].winner = i;
                pairs[l].loser = j;
                l++;
            }
        }
        pair_count = l + 1;
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 2; i++)
    {
        if (preferences[pairs[i+1].winner] > preferences[pairs[i].winner])
        {
            pair temp = pairs[i];
            pairs[i] = pairs[i+1];
            pairs[i+1] = temp;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool detect = false;
    for (int i = 0; i < pair_count - 2; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    for (int i = 0; i < pair_count - 2; i++)
    {
        if(locked[pairs[i].winner][pairs[i].loser] == false)
        {
            detect = true;
            break;
        }
    }
    if (detect == true)
    {
       locked[pairs[pair_count - 1].winner][pairs[pair_count - 1].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool find = true;
    for (int j = 0; j < pair_count - 1; j++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (locked[i][j] == true)
            {
                find = false;
                break;
            }
        }
        if (find == true)
        {
            printf("%s\n", candidates[j]);
            break;
        }
    }
    return;
}
