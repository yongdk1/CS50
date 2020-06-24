from cs50 import get_string

text = None

## Repeatedly promt user for input
while (text == None):
    text = get_string("Text:  ")

## Initialize letter, word and sentence count
letter = 0
word = 1
sentence = 0

## Counte by features
for char in text:
    if char.isalpha():
        letter += 1
    
    elif char == ' ':
        word += 1
    
    elif char == '.' or char == '?' or char == '!':
        sentence += 1

## Calculate by formula
index = 0.0588 * (letter/word) * 100 - 0.296 * (sentence/word) * 100 - 15.8

## Round index to grade
grade = round(index)

## Print output
if grade > 0 and grade < 17:
    print("Grade", grade)
elif grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")