import csv
import sys


def main():

    # Validate user input
    validate_input()

    # Get all DataBase (people and the sequence)
    full_db = read_db()

    # Retrieve all the sequence of DNA (Read file)
    full_sequence = read_sq()

    # Retrieve all the header in DB (Different bases)
    STRs = list(full_db[0].keys())[1:]

    # Get the longest match, based in the Base Sequence (STRs)
    result = get_result_long_match(full_sequence, STRs)

    # Check what user has the same combination
    name = get_person(full_db, result, STRs)

    # Print the user name or 'not found'
    print(name)

    return


# Try to get the person, based on math of STRs
def get_person(full_db, result, STRs):
    for name in full_db:
        match = 0
        for str in STRs:
            # Must to be a integer
            if int(name[str]) == result[str]:
                match += 1
        if match == len(STRs):
            return name["name"]

    return "No Match"


def get_result_long_match(dna, STRs):
    result = {}
    for str in STRs:
        # Longest math with each of one STRs
        result[str] = longest_match(dna, str)
    return result


# argv2 txt
def read_sq():
    sequence = sys.argv[2]
    with open(sequence) as f:
        full_sequence = f.read()
    return full_sequence


# argv1 csv
def read_db():
    full_db = []
    data_base = sys.argv[1]
    with open(data_base) as f:
        reader = csv.DictReader(f)
        for reg in reader:
            full_db.append(reg)
    return full_db


def validate_input():
    if len(sys.argv) != 3:
        print("Invalid param")
        sys.exit(1)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
