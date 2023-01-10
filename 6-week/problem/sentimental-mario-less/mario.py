from cs50 import get_int


def main():
    init()


# Initialization method
def init():
    size = get_int("Height: ")
    is_valid = validate_input(size)
    c_size = size
    if is_valid == True:
        i = 0
        while size > 0:
            print_blocks(i, c_size)
            i += 1
            # Decrement size loop
            size -= 1
            # New break line
            print("")
    else:
        init()


# Print blocks
def print_blocks(size, full_size):
    j = 1
    while j < full_size - size:
        print(" ", end="")
        j += 1

    i = 0
    while i <= size:
        print("#", end="")
        i += 1


# Validate the input passed by user
def validate_input(size):
    if size >= 1 and size <= 8:
        return True
    else:
        return False


if __name__ == "__main__":
    main()
