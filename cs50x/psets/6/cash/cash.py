from cs50 import get_float


def main():
    while True:
        # Prompt the user for change
        change = get_float("Change: ")
        if change > 0.0:
            break
    # Calculate how many quarters you should give the customer
    quarters = calculate_quarters(change)
    # Substract the value of those quarters from change
    change = round(change - (quarters * 0.25), 2)
    print(f"Remaining Change: {change}")
    # Calculate how many dimes you should give the customer
    dimes = calculate_dimes(change)
    # Substract the value of those dimes from change
    change = round(change - (dimes * 0.10), 2)
    print(f"Remaining Change: {change}")
    # Calculate how many nickels you should give the customer
    nickels = calculate_nickels(change)
    # Substract the value of those nickels from change
    change = round(change - (nickels * 0.05), 2)
    print(f"Remaining Change: {change}")
    # Calculate how many pennies you should give the customer
    pennies = calculate_pennies(change)
    # Substract the value of those pennies from change
    change = round(change - (pennies * 0.01), 2)
    print(f"Remaining Change: {change}")
    # Sum the number of quarters, dimes, nickels, and pennies used
    sum = quarters + dimes + nickels + pennies
    # Print that sum
    print(f"{sum}")


def calculate_quarters(change):
    # Calculate how many quarters you should give the customer
    quarters = 0
    while (change >= 0.25):
        quarters += 1
        change = change - 0.25
    print(quarters)
    return quarters


def calculate_dimes(change):
    # Calculate how many dimes you should give the customer
    dimes = 0
    while (change >= 0.10):
        dimes += 1
        change = change - 0.10
    print(dimes)
    return dimes


def calculate_nickels(change):
    # Calculate how many nickels you should give the customer
    nickels = 0
    while (change >= 0.05):
        nickels += 1
        change = change - 0.05
    print(nickels)
    return nickels


def calculate_pennies(change):
    # Calculate how many pennies you should give the customer
    pennies = 0
    while (change >= 0.01):
        pennies += 1
        change = change - 0.01
    print(pennies)
    return pennies


if __name__ == "__main__":
    main()
