from sys import argv
import cs50
import csv

## If incorect number of command_line arguments
if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

## Connect to database
db = cs50.SQL("sqlite:///students.db")

## Query the database and store the list as variable query
query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last,first", argv[1])

## Print the rows in the correct format depending on whether they have a middle name or not
for student in query:
    if student['middle'] == None:
        print(student['first'], student['last']+", born", student['birth'])
    else:
        print(student['first'], student['middle'], student['last']+", born", student['birth'])