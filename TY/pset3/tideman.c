#include <cs50.h>
#include <string.h>
#include <stdio.h>

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
void lock_pairs();
void print_winner();

pair* mergesort(pair* array, int items);
void print1d(int x, int array[x]);
void print1dpairs(int x, pair array[x]);
void print2d(int x, int array[][x]);
void print2dbool(int x, bool array[][x]);

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

    // Check on preferences
    // printf("Preferences: \n");
    // print2d(candidate_count, preferences);

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // if NAME is the rank of a valid candidate,
    // Update the RANKS array to indicate that the voter has the candidate as their RANK preferrence.

    // Check for valid candidate: Iterate through candidates array and see if there is a match
    for(int i=0; i<candidate_count; i++){
        if(strcmp(name, candidates[i])==0){
            // If found, update the rank with the given rank
            ranks[rank] = i;
            // printf("Updating index %d with candidate %d\n", rank, i);
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // printf("Ranks:\n");
    // print1d(candidate_count, ranks);
    // iterate through the ranks list. ranks[k]=preferences[i]; and every number after that->preferences[k]
    // Run through the list till the 2nd last item. No point running through the last element.
    for(int i=0; i<candidate_count-1; i++){
        int current = ranks[i];
        // Iterate through each element that the current element "beat"
        for(int j=i+1; j<candidate_count; j++){
            int beaten = ranks[j];
            // printf("current: %d, beaten: %d, currVal: %d\n", current, beaten, preferences[current][beaten]);
            preferences[current][beaten]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate through the preferences array to look for pairs
    for(int i=0; i<candidate_count; i++){
        for(int j=0; j<candidate_count; j++){
            if(preferences[i][j] > 0){
                // Initialize new pair
                pair newPair;
                newPair.winner = i;
                newPair.loser = j;
                // write to pair index, assume that pair_count is initied to 0
                pairs[pair_count] = newPair;
                pair_count++;
            }
        }
    }
    // printf("pair count: %d, pairs: ", pair_count);
    // print1dpairs(pair_count, pairs);
    return;
}

// Sort pairs in decreasing order by strength of victory
// Strength of victory given by the position in the preferences[][] 2d array
void sort_pairs(void)
{
    // Fudge Mergesort
    pair* pairPtr = pairs;
    pairPtr = mergesort(pairs, pair_count);

    // Assign the new value back into the original array
    for(int i=0; i<pair_count; i++){
        pairs[i] = pairPtr[i];
    }

    // printf("Sorted Pairs:\n");
    // print1dpairs(pair_count, pairs);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs()
{
    int pointy[candidate_count]; // candidates with things pointing to them; 0-initialized
    for (int i = 0; i < candidate_count; i++){
        pointy[i] = 0;  // Clear this graph as well
    }

    int cyclical = 1;
    // create the LOCKED graph by locking in the strongest edges first
    for(int i=0; i<pair_count; i++){
        // Check if doing this leads to a cyclical argument:

        pointy[pairs[pair_count-1-i].loser] = 1;
        int flagCheck = 0;
        for(int j=0; j<candidate_count; j++){      // Checks if adding the next edge will lead to cyclical.
            if(pointy[j]==0){                      // If there are no more 0's in pointy, then flagCheck will become 0, tripping cyclical.
                flagCheck=1;
                break;
            }
        }
        cyclical = flagCheck;

        if(cyclical){   // Check for cyclical arguments
            // printf("Writing to [%d][%d]\n", pairs[pair_count-1-i].loser, pairs[pair_count-1-i].winner);
            // write 1 to those who lost to someone
            locked[pairs[pair_count-1-i].loser][pairs[pair_count-1-i].winner] = 1; // take from the highest index first.
        } else {
            pointy[pairs[pair_count-1-i].loser] = 0;
            break;
        }
    }

    // printf("Pointy: ");
    // print1d(candidate_count, pointy);

    printf("Locked:\n");
    for(int i=0; i<candidate_count; i++){
        for(int j=0; j<candidate_count; j++){
            printf("%d ", locked[i][j]);
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner()
{
    string winner;
    // look at which does not does not have anything attached (locked is all false)
    for(int i=0; i<candidate_count; i++){
        int flag = 1;
        for(int j=0; j<candidate_count; j++){
            if(locked[i][j]==1){
                // Locked is true, stop linear searching
                flag = 0;
                break;
            }
        }
        if (flag==1){
            winner = candidates[i];
        }
    }
    printf("%s\n", winner);
    return;
}

// Mergesort implementation
pair* mergesort(pair* array, int items){
    // Base case
    if(items <= 1){
        return array;   // If only need to sort one or fewer elements, just return.
    }
    // Recursive case
    // Split current array into half, assign both values
    int item1 = items/2;
    int item2 = items-item1;
    pair list1[item1], list2[item2];
    pair* list1ptr = list1;
    pair* list2ptr = list2;

    // printf("Split array 1: ");
    for(int i=0; i<item1; i++){
        list1[i] = array[i];
        // printf("%d ", list1[i]);
    }
    // printf("\nSplit array 2: ");
    for(int i=0; i<item2; i++){
        list2[i] = array[i+item1];  // Offset by values that have already been assigned
        // printf("%d ", list2[i]);
    }
    // printf("\n");

    // Sort each split array:
    list1ptr = mergesort(list1, item1);
    list2ptr = mergesort(list2, item2);
    // Sort larger split arrays:
    // Iterate in parallel through each.
    int x = 0;
    int y = 0;   // indices for each sub-array.
    for(int i=0; i<items; i++){

        // If we have finished iterating through a sub-array we simply assign
        // the rest of the array as the remainign values in the other sub-array.
        if( x >= item1 ) {
            array[i] = list2ptr[y];
            y++;
        } else if( y >= item2 ){
            array[i] = list1ptr[x];
            x++;
        } else {
            // Begin from 0,0 and see which one is the smaller one, iterating the index
            // of the chosen one as we go along until we finish one sub-array
            // Herein is the comparison
            if( preferences[list1ptr[x].winner][list1ptr[x].loser] <= preferences[list2ptr[y].winner][list2ptr[y].loser] ){
                array[i] = list1ptr[x];
                x++;
            } else {
                array[i] = list2ptr[y];
                y++;
            }
        }
    }

    // Check on our intermediate sorted array:
    // printf("Intermediate Sorted Array: ");
    // for(int i=0; i<items; i++){
    //     printf("%d ", array[i]);
    // }
    // printf("\n");

    return array;
}

void print1d(int x, int array[x]){
    for(int i=0; i<x; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void print1dpairs(int x, pair array[x]){
    for(int i=0; i<x; i++){
        printf("{%d, %d} ", array[i].winner, array[i].loser);
    }
    printf("\n");
}

void print2d(int x, int array[][x]){
    for(int i=0; i<x; i++){
        for(int j=0; j<x; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    return;
}
// overload to print bool
void print2dbool(int x, bool array[][x]){
    for(int i=0; i<x; i++){
        for(int j=0; j<x; j++){
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
    return;
}