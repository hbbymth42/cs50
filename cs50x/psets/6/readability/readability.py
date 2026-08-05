from cs50 import get_string

# Prompt the user for some text
text = get_string("Text: ")

letters = 0.0
words = 0.0
sentences = 0.0

for i in range(0, len(text)):
    # Increments number of letters based on if character is alphanumeric.
    if text[i].isalnum():
        letters += 1
    # Increments number of words based on presence of spaces between words
    elif text[i] == " ":
        words += 1
    # Increments number of sentences based on presence of 'ending characters' i.e. '.', '!', '?'
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# 1 added to include last word
words += 1

# Compute the Coleman-Liau index
index = int(round((0.0588 * ((letters / words) * 100.0) -
            0.296 * ((sentences / words) * 100.0) - 15.8), 0))

# Print the grade level
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
