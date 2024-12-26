import random, string

def random_string(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))

MAX_LENGTH = 15

file = open("normal.txt", "w")

for i in range(1, MAX_LENGTH+1):
    original = ''.join(random.choices(string.ascii_lowercase, k=i))
    destination = ''.join(random.choices(string.ascii_lowercase, k=i))
    file.write(f"{original} {destination}\n")

file.close()

file = open("empty.txt", "w")

for i in range(1, MAX_LENGTH+1):
    destination = ''.join(random.choices(string.ascii_lowercase, k=i))
    file.write(f" {destination}\n")

file.close()

file = open("substring.txt", "w")

for i in range(1, MAX_LENGTH+1):
    sub = ''.join(random.choices(string.ascii_lowercase, k=i//2))
    original = random_string(i//4) + sub
    destination = random_string(i//4) + sub

    original += random_string(i - len(original))
    destination += random_string(i - len(destination))

    file.write(f"{original} {destination}\n")

file.close()

file = open("transpose.txt", "w")

for i in range(1, MAX_LENGTH+1):
    original = random_string(i)

    destination = ""
    j = 0
    while (j < i - 1):
        destination += original[j+1] + original[j]
        j += 2

    if len(destination) < len(original):
        destination += original[-1]

    file.write(f"{original} {destination}\n")

file.close()

file = open("length.txt", "w")

for i in range(1, MAX_LENGTH+1):
    original = random_string(i//2)
    destination = random_string(i)

    file.write(f"{original} {destination}\n")

file.close()

