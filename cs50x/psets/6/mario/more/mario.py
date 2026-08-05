from cs50 import get_int

while True:
    # Prompt the user for the pyramid's height
    height = get_int("Height: ")
    if height <= 8 and height > 0:
        break
# Print a pyramid of the specified height
for i in range(1, height+1):
    print(f"{" " * (height - i)}{"#" * i}{"  "}{"#" * i}")
