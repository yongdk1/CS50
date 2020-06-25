# https://cs50.harvard.edu/x/2020/psets/7/houses/

'''
In import.py, write a program that imports data from a CSV spreadsheet.

Your program should accept the name of a CSV file as a command-line argument.
- If the incorrect number of command-line arguments are provided, your program should print an error and exit.
- You may assume that the CSV file will exist, and will have columns name, house, and birth.

For each student in the CSV file, insert the student into the students table in the students.db database.
- While the CSV file provided to you has just a name column, the database has separate columns for first, middle, and last names.
  You’ll thus want to first parse each name and separate it into first, middle, and last names.
  You may assume that each person’s name field will contain either two space-separated names (a first and last name)
  or three space-separated names (a first, middle, and last name).
  For students without a middle name, you should leave their middle name field as NULL in the table.
'''

from sys import argv
import csv
import sqlite3


def main():
    # Check if user gave appropriate input, return 1 if invalid
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        return 1

    # Check if user gave a valid input .csv, return 2 if invalid
    try:
        # Save .csv as OrderedDict object characters
        characters_csv = csv.DictReader(open(argv[1], 'r'))
    except FileNotFoundError:
        print("Error:.csv file does not exist")
        return 2

    # Connect to .db file students.db
    try:
        conn = sqlite3.connect("file:students.db?mode=rw", uri=True)
        c = conn.cursor()
    except sqlite3.OperationalError:
        print("Error: database file does not exist")
        return 3

    # Operate on each row
    for row in characters_csv:
        # Define variables for each column in the database
        name = row['name'].split()
        if len(name) == 2:
            first = name[0]
            middle = None
            last = name[1]
        elif len(name) == 3:
            first = name[0]
            middle = name[1]
            last = name[2]

        # Insert each row into the database
        conn.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                     (first, middle, last, row['house'], row['birth']))

    # Run commit to lock in the executes
    conn.commit()
    conn.close()


main()
