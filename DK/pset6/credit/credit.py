# https://cs50.harvard.edu/x/2020/psets/6/credit/


def main():
    # Take user input string
    creditStr = input("Number: ")
    length = len(creditStr)
    
    # Case where length is valid
    if (length == j for j in [13, 15, 16]):
    
        # Case where input is an integer
        try:
            creditNum = int(creditStr)
            # Save reverse of input as a variable
            creditRev = creditStr[::-1]
            totalNum = 0
            # Iterate over every element of input to perform luhn's test
            for i in range(length):
                if i % 2 == 0:
                    totalNum += int(creditRev[i])
                if i % 2 == 1:
                    if int(creditRev[i]) < 5:
                        totalNum += int(creditRev[i]) * 2
                    else:
                        totalNum += ((int(creditRev[i])) - 4) * 2 - 1
            
            # Case where luhn's test suceeds
            if totalNum % 10 == 0:
                if length == 15 and creditStr[0] == '3' and (creditStr[1] == '4' or creditStr[1] == '7'):
                    print("AMEX")
                elif length == 16 and creditStr[0] == '5' and (creditStr[1] == i for i in ['1', '2', '3', '4', '5']):
                    print("MASTERCARD")
                elif (length == 13 or length == 16) and creditStr[0] == '4':
                    print("VISA")
                else:
                    print("INVALID")

            # Case where luhn's test fails
            else:
                print("INVALID")

        # Case where input is not an integer
        except ValueError:
            print("INVALID")

    # Case where length is invalid
    else:
        print("INVALID")


main()
