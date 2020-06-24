from sys import argv
import cs50
import csv

## If incorect number of command_line arguments
if len(argv) != 2:
    print("Missing command-line argument")
    exit(1)

## Connect to database
db = cs50.SQL("sqlite:///students.db")

## Open CSV file 
with open(argv[1], "r") as characters_csv:
    
    ## Create DictReadeer
    students = csv.DictReader(characters_csv)
    
    ## Iterate over csv file
    for row in students:
        
        ## Split the name string into a list of names 
        name = row["name"].split()
        
        ## If character has middle name 
        if len(name) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", 
                       name[0], name[1], name[2], row["house"], row["birth"])
        
        ## If character has no middle name
        elif len(name) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", 
                       name[0], None, name[1], row["house"], row["birth"])