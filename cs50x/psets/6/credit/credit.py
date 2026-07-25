from cs50 import get_string


def main():
    card = get_string("Number: ")
    try:
        card = int(card)
        card = str(card)
    except:
        print("INVALID")
    # Check length and first digits for valid card
    if len(card) == 13:
        if int(card[0]) == 4:
            if checksum(card) == 0:
                print("VISA")
            else:
                print("INVALID")
        else:
            print("INVALID")
    elif len(card) == 15:
        if int(card[:2]) in [34, 37]:
            if checksum(card) == 0:
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")
    elif len(card) == 16:
        if int(card[0]) == 4:
            if checksum(card) == 0:
                print("VISA")
            else:
                print("INVALID")
        elif int(card[:2]) in range(51, 56):
            if checksum(card) == 0:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


# Checksum for each card type
def checksum(card):
    check = 0
    # Iterate over each digit of supplied card
    # Add every n+1 digit multiplied by 2 to checksum sum
    for i in range(-2, (len(card) * -1)-1, -2):
        # If digit * 2 is two digits, then add each of those digits together, then add to checksum sum
        if int(card[i]) * 2 > 9:
            check += int((int(card[i]) * 2) / 10) + ((int(card[i]) * 2) % 10)
        else:
            # Otherwise, add digit multiplied by 2 to other checksum sum
            check += int(card[i]) * 2
    # Add every n digit to checksum sum
    for i in range(((len(card) + 1) % 2), len(card), 2):
        check += int(card[i])

    check = check % 10
    # Return checksum digit: 0 = Valid Card
    return check


if __name__ == "__main__":
    main()
