#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define Block 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Create file for SD card
    FILE *card;
    
    //Create file of jpg to store jpg data
    FILE *jpg = NULL;
    
    //buffer to store blocks of data
    BYTE buffer [512];
    
    char filename[8];
    int jpgcount = 0;
    
    //Check if user inputs a file in the command line
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover\n ");
        return 1;
    }
    
    //open the file
    card = fopen(argv[1], "r");
    
    //Check if file can be opened
    if (card == NULL){
    fprintf(stderr, "Could not open %s\n ", argv[1]);
    return 2;
    }
    
    //While loop through the file and read 512 bytes at a time until the end of the file
    while (fread(buffer, 1, Block, card) == Block){
        
        //Check for start of jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            
            //If first jpg file, open a jpg file and write in
            if (jpgcount == 0){
                sprintf(filename, "%03i.jpg", jpgcount);
                jpg = fopen(filename, "w");
                fwrite(buffer, 1, Block, jpg);
                jpgcount++;

            }
            //Else close the last jpg file and open a new one to write in
            else{
                fclose(jpg);
                
                sprintf(filename, "%03i.jpg", jpgcount);
                jpg = fopen(filename, "w");
                fwrite(buffer, 1, Block, jpg);
                jpgcount++;
            }
            
        }
        //Need to use else if as if first few blocks are junk data, fwrite running will result in segmentation fault!!!
        /*with the else if condition, we need to update the count once we open the first file(0) or the file will not continue to write
        as it failed the else if condition!!!*/
        else if (jpgcount != 0){
            fwrite(buffer, 1, Block, jpg);
        }
    }
    //Close the last jpg file
    fclose(jpg);
    
    //Close the file
    fclose(card);
    
    return 0;
}
