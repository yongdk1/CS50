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
void lock_pairs(void);
bool check_cycle(int r, int i, int j);
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
            //initialize preferences array
            preferences[i][j] = 0;
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
    for(int i = 0; i < candidate_count; i++){
        //check if name of candidate exist in candidates array
        if(strcmp(name,candidates[i]) == 0){
            //if exists, function stores the index of the candidate in candidates[]
            //to rank[] which stores rankining inforamtion of the current voter
            //with index rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++){

        for(int j = i + 1; j < candidate_count; j++){

            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++){

        for(int j = i + 1; j < candidate_count; j++){
            //iterate through preference 2D array and compare preferences between 2 candidates
            if(preferences[i][j] > preferences[j][i]){
                //if more voters prefer candidate [i] over candidate [j], create pair with winner [i] and loser [j]
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if(preferences[i][j] < preferences[j][i]){
                //if more voters prefer candidate [j] over candidate [i], create pair with winner [j] and loser [i]
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
    pair temp_;
    int temp;

    for(int i = 0; i < pair_count; i++){
        //initialize max_margin as the margin of win between winner and loser of pairs[i]
        int max_margin = preferences[pairs[i].winner][pairs[i].loser]-preferences[pairs[i].loser][pairs[i].winner];
        //!!! remember to initialize temp = i as biggest margin of win might already be in 1st position!!!
        temp = i;
        for(int j = i + 1; j < pair_count; j++){
            //find the margin of win between winner and loser of subsequent pairs[j]
            int margin = preferences[pairs[j].winner][pairs[j].loser]-preferences[pairs[j].loser][pairs[j].winner];
            //if subsequent margin is greater than max_margin, update
            if(margin > max_margin){
                max_margin = margin;
                //need to keep track of index of the pairs with the new max_margin
                temp = j;
            }
        }
        //after exiting j-loop, swap pairs[i] with pairs[temp](pairs with new max_margin)
        temp_ = pairs[temp];
        pairs[temp] = pairs[i];
        pairs[i] = temp_;

    }
    return;
}

//Check if locking the next pair creates a cycle
bool check_cycle(int r, int i, int j)
{
    //if the loser of a locked pair is the root(where the cycle started), then there is a cycle
    if(j == r){
        return true;
    }
    else{
        //iterate through locked array with winner [j] and loser [k]
        for (int k = 0; k < pair_count; k++){
            //check for edge
            if(locked[j][k]){
                //if edge exist, recursively check the next winner, loser pair
                return check_cycle(r,j,k); //!!! simply return the output of the function if u want the base case result to trave back up
            }
        }
        return false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for(int i = 0; i < pair_count; i++){
        //progressively lock in the pairs
        locked[pairs[i].winner][pairs[i].loser] = true;
        //check is a cycle is created after locking in the pairs, first parameter sets pairs[i].winner as the root of possible cycle
        if(check_cycle(pairs[i].winner,pairs[i].winner,pairs[i].loser)){
            //if check_cycle returns true, a cycle has been created and the pairs need to be unlocked
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool r;
    //check each candidate i
    for(int i = 0; i < candidate_count; i++){
        //assume that candidate i is the root i.e the winner
        r = true;
        //check candidate j against i
        for(int j = 0; j < candidate_count; j++){
            //if i is the root, there should not be a locked pair in which j wins against i
            if(locked[j][i]){
                //so if locked[j][i] is true, then i is not the winner
                r = false;
                break;
            }
        }
        //if after comparing against all other candidates j, r is still true,
        if(r){
            //then candidate i is a winner
            printf("%s\n",candidates[i]);
        }
    }
    return;
}
