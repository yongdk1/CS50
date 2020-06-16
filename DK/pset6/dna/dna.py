# https://cs50.harvard.edu/x/2020/psets/6/dna/


from sys import argv
import csv


def main():
    # Check if correct number of inputs are given
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Try to open the files according to the inputs given
    try:
        # Open data.csv
        dataFile = csv.DictReader(open(argv[1], 'r'))
        headers = dataFile.fieldnames
        # Open sequence.txt
        seqFile = open(argv[2], 'r').read()

        # Save list of codes
        codeList = []
        for fieldname in headers:
            if fieldname != 'name':
                codeList.append(fieldname)

        codeCount = {}
        for code in codeList:
            codeCount[code] = '0'
            maxCount = seqFile.count(code)
            for i in range(maxCount, 0, -1):
                newCount = code * i
                if newCount in seqFile:
                    codeCount[code] = str(i)
                    break

        for row in dataFile:
            if codeCount.items() <= row.items():
                print(row['name'])
                return

        print("No match")
        return

    # Case where files given are invalid/ not found
    except FileNotFoundError:
        print("Usage: python dna.py data.csv sequence.txt")
        return


main()
