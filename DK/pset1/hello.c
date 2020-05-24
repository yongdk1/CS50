#include <stdio.h>
#include <cs50.h>

//https://cs50.harvard.edu/x/2020/psets/1/hello/

int main(void)
{
    //ask for user input name
    string name = get_string("what is your name?\n");
    //print hello + user input name
    printf("hello, %s\n", name);
}
