from sys import argv
import csv

if len(argv) != 3:
    print("Missing command-line argument")
    exit(1)

with open(argv[1], mode='r') as data_file:    
    data = csv.DictReader(data_file)
    header = data.fieldnames
    
    seq = open(argv[2], 'r').read()
    
    STR_List = []
    for item in header:
        if item != 'name':
            STR_List.append(item)
            
    STR_count = {}
    DNA_length = len(seq)
    
    for STR in STR_List:
        count = 0
        max_count = 0
        i = 0
        while i < DNA_length:
            if seq[i : i + len(STR)] == STR:
                count += 1
                i += len(STR)-1
                
            else:
                if count > max_count:
                    max_count = count
                    count = 0
                else:
                    count = 0
            
            i += 1
        STR_count[STR] = str(max_count)
        
    for rows in data:
        if STR_count.items() <= rows.items():
            print(rows['name'])
            exit(0)

    print("No match")
            