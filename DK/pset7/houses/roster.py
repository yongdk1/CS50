# TODO

'''
In roster.py, write a program that prints a list of students for a given house in alphabetical order.

Your program should accept the name of a house as a command-line argument.
- If the incorrect number of command-line arguments are provided, your program should print an error and exit.

Your program should query the students table in the students.db database for all of the students in the specified house.

Your program should then print out each student’s full name and birth year (formatted as, e.g., Harry James Potter, born 1980 or Luna Lovegood, born 1981).
- Each student should be printed on their own line.
- Students should be ordered by last name. For students with the same last name, they should be ordered by first name.
'''

from sys import argv
import sqlite3


def main():
    # Check if user gave appropriate input, return 1 if invalid
    if len(argv) != 2:
        print("Usage: python import.py characters.csv")
        return 1

    # Connect to .db file students.db
    try:
        conn = sqlite3.connect("file:students.db?mode=rw", uri=True)
        c = conn.cursor()
    except sqlite3.OperationalError:
        print("Error: database file does not exist")
        return 3

    # Save housename as variable
    house = argv[1]

    # Select rows from database where house = input house
    query = c.execute("SELECT * FROM students WHERE house=? ORDER BY last, first", (house,))
    conn.commit()

    # Print out each row in desired format
    for i in query.fetchall():
        if i[2] == None:
            print(f"{i[1]} {i[3]}, born {i[5]}")
        else:
            print(f"{i[1]} {i[2]} {i[3]}, born {i[5]}")


main()
