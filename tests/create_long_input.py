#!/usr/bin/env python3
import random
import string


def get_random_string(length):
    # Define the possible characters (letters and digits)
    characters = string.ascii_letters + string.digits
    # Choose random characters for the specified length
    return "".join(random.choice(characters) for _ in range(length))


with open("client_long_input.txt", "w") as f:
    f.write(get_random_string(1000000))
