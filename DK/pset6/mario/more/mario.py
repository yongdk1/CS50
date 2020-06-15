# https://cs50.harvard.edu/x/2020/psets/6/mario/more/

# Run loop that only exits when input is within acceptable parameters
while True:
    height = input("Height: ")
    # Case where height is an int
    try:
        height = int(height)
        # Case where height is within desired parameters and break
        if height > 0 and height < 9:
            break
        else:
            print("Error. Please enter an integer between 1 and 8 inclusive.")
    # Case where height is not an int
    except ValueError:
        print("Error. Please enter an integer.")

# Print the pyramid as desired
for i in range(height):
    print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
