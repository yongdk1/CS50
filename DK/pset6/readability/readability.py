# https://cs50.harvard.edu/x/2020/psets/6/readability/


# Initialise text and prompt user for input
text = None
while text == None:
    text = input("Text: ")

# Initialise variables
letterCount = 0
wordCount = 1
sentenceCount = 0

# Iterate through every character in input string
for char in text:
    # Case where character is a letter
    if char.isalpha():
        letterCount += 1
    # Case where character is a space
    elif char == " ":
        wordCount += 1
    # Case where character is a sentence indicator
    elif char == '.' or char == '?' or char == '!':
        sentenceCount += 1
        
# Determine average number of letters per 100 words
L = letterCount / wordCount * 100

# Determine averge number of sentences per 100 words
S = sentenceCount / wordCount * 100

# Calculate coleman-liau index
index = 0.0588 * L - 0.296 * S - 15.8
grade = round(index)

# Print grade
if grade > 0 and grade < 17:
    print(f"Grade {grade}")
elif grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
