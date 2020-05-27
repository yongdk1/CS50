#include <cs50.h>
#include <stdio.h>
#include <string.h>

//https://cs50.harvard.edu/x/2020/psets/3/tideman/

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

        /*// debug display of ranks[] array
        printf("ranks[%i] array debug\n", i);
        for (int j = 0; j < candidate_count; j ++)
        {
            printf("[%i]", ranks[j]);
        }*/

        record_preferences(ranks);

        printf("\n");
    }

    /*//debug display of preferences[][] array
    printf("preferences[][] array debug\n");
    for (int i = 0; i < candidate_count; i++)
    {
        // Update indice [i][j] of preferences[] with a ++ for each voter who prefers candidate i over candidate j
        for (int j = 0; j < candidate_count; j++)
        {
            printf("[%i][%i] : %i\n", i, j, preferences[i][j]);
        }
    }*/


    add_pairs();

    /*//debug display of pairs[] array
    printf("pairs[] array debug\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i : [%i][%i]\n", i, pairs[i].winner, pairs[i].loser);
    }*/

    sort_pairs();

    /*//debug display of sorted pairs[] array
    printf("pairs[] array debug\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i : [%i][%i]\n", i, pairs[i].winner, pairs[i].loser);
    }*/

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    /*The function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate,
    then you should update the ranks array to indicate that the voter has the candidate as their rank preference
    (where 0 is the first preference, 1 is the second preference, etc.)
    Recall that ranks[i] here represents the user’s ith preference.
    The function should return true if the rank was successfully recorded, and false otherwise
    (if, for instance, name is not the name of one of the candidates).
    You may assume that no two candidates will have the same name.*/

    // Iterate through array of candidates candidates[]
    for (int  k = 0; k < candidate_count; k++)
    {
        // Check if user input is a valid candidate
        if (strcmp(name, candidates[k]) == 0)
        {
            // Update indice rank of ranks[] with indice of candidate in candidates[] and return true
            ranks[rank] = k;
            return true;
        }
    }
    // If user input is not a valid candidate return false
    return false;

}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    /* The function is called once for each voter, and takes as argument the ranks array,
    (recall that ranks[i] is the voter’s ith preference, where ranks[0] is the first preference).
    The function should update the global preferences array to add the current voter’s preferences.
    Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j.
    You may assume that every voter will rank each of the candidates. */

    // Iterate through ranks[] array in order of highest rank to lowest
    for (int i = 0; i < candidate_count; i++)
    {
        // Update indice [i][j] of preferences[][] with a ++ for each voter who prefers candidate i over candidate j
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
    /*The function should add all pairs of candidates where one candidate is preferred to the pairs array.
    A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
    The function should update the global variable pair_count to be the number of pairs of candidates.
    (The pairs should thus all be stored between pairs[0] and pairs[pair_count - 1], inclusive).*/

    // Iterate through preferences[][] array to find uneven [i][j], [j][i] pairs
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Add pair to array if either candidate i or candidate j is more preferred over the other,
            // and increase pair_count
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] < preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    /*The function should sort the pairs array in decreasing order of strength of victory,
    where strength of victory is defined to be the number of voters who prefer the preferred candidate.
    If multiple pairs have the same strength of victory, you may assume that the order does not matter.*/

    /* ORIGINAL THOUGHT PROCESS
    // Create a new structure, pairmargin, that relates winner:loser pair with victory margin
    // Extra work used for visualisation
    typedef struct
    {
        int winner;
        int loser;
        int victoryMargin;
    }
    pairmargin;

    pairmargin pairmargins[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        pairmargins[i].winner = pairs[i].winner;
        pairmargins[i].loser = pairs[i].loser;

        int winStrength = preferences[pairs[i].winner][pairs[i].loser];
        int lossStrength = preferences[pairs[i].loser][pairs[i].winner];
        int victoryMargin = winStrength - lossStrength;

        pairmargins[i].victoryMargin = victoryMargin;

        //debug display for unsorted pairmargins[] to confirm victoryMargin recorded correctly
        printf("pairmargin[] unsorted debug\n");
        printf("[%i][%i] : %i\n", pairmargins[i].winner, pairmargins[i].loser, pairmargins[i].victoryMargin);
    }

    // Sort pairmargins[] in order of descending victoryMargin value
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (pairmargins[i].victoryMargin > pairmargins[j].victoryMargin)
            {
                pairmargin tmp = pairmargins[j];
                pairmargins[j] = pairmargins[i];
                pairmargins[i] = tmp;
            }
        }
    }

    // Sort pairs[] in order of descending victoryMargin value
    for (int i = 0; i < pair_count; i++)
    {
        //debug display for sorted pairmargins[]
        printf("pairmargin[] sorted debug\n");
        printf("[%i][%i] : %i\n", pairmargins[i].winner, pairmargins[i].loser, pairmargins[i].victoryMargin);

        pairs[i].winner = pairmargins[i].winner;
        pairs[i].loser = pairmargins[i].loser;
    }
    */

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner] >
                preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner])
            {
                pair tmp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = tmp;
            }
        }
    }

    return;
}

// New recursive function to check if a cycle will be created
bool cycle_check(int origin, int winner, int loser)
{
    // Check if loser points back to the origin (i.e. a cycle has formed) and return false
    if (origin == loser)
    {
        return false;
    }
    else
    {
        // Iterate through locked[][] array to find already locked pairs
        for (int i = 0; i < pair_count; i++)
        {
            // Follow the next locked pair to see if its loser points back to the origin, recursively
            if (locked[loser][i])
            {
                return cycle_check(origin, loser, i);
            }
        }
    }
    // If loser does not not point back to the origin (i.e. no cycle formed) return true
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*The function should create the locked graph,
    adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.*/

    /* ORIGINAL THOUGHT PROCESS
    If edge would create a cycle, do not lock the edge
    Cycle could be identified if the last element that did not have any candidate locked above it has
    a candidate locked above it
    As long as at least one source exits, allow all pairs to be locked
    This allows for cycles to be created and is NOT what the question is asking for

    // Iterate through pairs[] array to examine indice i
    for (int i = 0; i < pair_count; i++)
    {

        int lockcount = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != pairs[i].loser)
            {
                 for (int k = 0; k < candidate_count; k++)
                 {
                     if (locked[k][j] == true)
                     {
                         lockcount++;
                         break;
                     }
                 }
            }
        }
        if (lockcount < candidate_count-1)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }*/

    // Iterate through each element of pairs[] array to determine if whether to lock pair
    for (int i = 0; i < pair_count; i++)
    {
        // Run cycle_check to determine if cycle will be formed, returns true if cycle is not formed
        if (cycle_check(pairs[i].winner, pairs[i].winner, pairs[i].loser))
        {
            // If cycle is not formed, lock pair
            locked[pairs[i].winner][pairs[i].loser] = true;
        }

    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    /*The function should print out the name of the candidate who is the source of the graph.
    You may assume there will not be more than one source.*/
    
    // Iterate through candidates[] array to find source
    for (int i = 0; i < candidate_count; i++)
    {
        bool lock = true;
        // If candidate[i] has another candidate[j] locked over them, they are not the source
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                lock = false;
                break;
            }
        }
        if (lock)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

