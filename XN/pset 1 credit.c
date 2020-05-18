#include <stdio.h>
#include <cs50.h>

int main()
{
    int n;
    long long int number;
    int checker(long long int x);
    
    number = get_long("Number:");
    n = checker(number);
//depending on the returned value, print the corresponding results    
    switch(n){
        case 1:
            printf("AMEX\n");
            break;
        
        case 2:
            printf("MASTERCARD\n");
            break;
        
        case 3:
            printf("VISA\n");
            break;
        
        default:
            printf("INVALID\n");
    }
    
}    


int checker(long long int number){
  int counter = 1, i = 0,j = 0,l;
  int y[8],z[8],sum = 0;
// fill the alternating digits into 2 diff arrays  
  do{
      if(counter % 2 == 0){
          y[i] = number % 10;
          number /= 10;
          counter++;
          i++;
      }
      else{
          //for every other digit starting for last, we add directly to the sum
          z[j] = number % 10;
          sum += z[j];
          number /= 10;
          counter++;
          j++;
      }
  }while(counter < 17);
//for every other digit starting from 2nd last, we multiply by 2 then add to sum
  for(i = 0; i < 8; i++){
      if(y[i]*2 < 10){
          sum += y[i]*2;
      }
      else{
          //however, if the product is 2 digit, we need to split the 2 digits up and add them separately
          l = y[i]*2;
          sum += l%10 + l/10;
      }
  }

//checking for features to identify payment network
  if(sum % 10 == 0){
      if(z[7] == 3 && (y[6] == 4 || y[6] == 7)){
          return 1;
      }
      else if(y[7] == 5 && z[7] > 0 && z[7] <6){
          return 2;
      }
      //to avoid simply identifying the card to be VISA just because it has a 4 in the 13th digit in a 16 digit card,
      //we need add the condition when the 16th digit has to be blank when the 13th digit is 4 for it to be considered a VISA card
      else if(y[7] == 4 || (z[6] == 4 && y[7] == '\0')){
          return 3;
      }
      else{
          return 0;
      }
  }
  else{
      return 0;
  }
}
