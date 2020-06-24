from cs50 import get_string

## get_string as string in Python can be accessed like an array
credit = get_string("Number: ")

## Initialize sum and legnth of number
sum = 0
length = len(credit)

## Iterate and operate directly from the string using range()
## Luhn’s Algorithm
for i in range(-1,-(length+1),-2):
    sum += int(credit[i])
    
for j in range (-2,-(length+1),-2):
    num = (int(credit[j]))*2
    
    if num < 10:
        sum += num
    else:
        sum += (num//10 + num % 10)

## Passed Condition
if sum % 10 == 0:
    ## Feature checking
    if length == 15 and (int(credit[0]) == 3) and ((int(credit[1]) == 4) or (int(credit[1]) == 7)):
        print("AMEX")
    
    elif length == 16 and (int(credit[0]) == 5) and (int(credit[1]) > 0) and (int(credit[1]) < 6):
        print("MASTERCARD")
        
    elif (length == 13 or length == 16) and (int(credit[0]) == 4):
        print("VISA")
        
    else:
        print("INVALID")
        
else:
    print("INVALID")