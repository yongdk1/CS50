from cs50 import get_int

height = get_int("Height: ")

##If value given is invalid, keep prompting user
while (height < 1 or height > 8):
    height = get_int("Height: ")
    
##Python magix
for i in range(height):
    ## Just use + as commas give u free space!!!
    print(" "*(height-i-1) + "#"*(i+1) + "  " + "#"*(i+1))