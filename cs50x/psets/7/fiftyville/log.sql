-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
Confirms theft of CS50 duck at 10:15am at Humphrey Street Bakery, 3 Witnesses were interviewed.
*/
SELECT description, street
FROM crime_scene_reports
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND street = 'Humphrey Street';
/*
- Ruth - Thief got into a car in the bakery parking log and drove away, within 10 minutes of theft.
- Eugene - Recognised Thief but didn't know their name. They saw the thief at the ATM withdrawing money on Leggett Street before getting to the bakery.
- Raymond - Thief called someone and talked to them for less than a minute. Thief was planning to take earliest flight out of Fiftyville the next day and asked person to purchase the flight ticket.
*/
SELECT name, transcript, day, month, year
FROM interviews
WHERE year = 2025
  AND month = 7
  AND day = 28;

/*
Ruth Follow-up - Suspect could have driven the following cars:
------+--------+----------+---------------+
| hour | minute | activity | license_plate |
+------+--------+----------+---------------+
| 10   | 16     | exit     | 5P2BI95       |
| 10   | 18     | exit     | 94KL13X       |
| 10   | 18     | exit     | 6P58WS2       |
| 10   | 19     | exit     | 4328GD8       |
| 10   | 20     | exit     | G412CB7       |
| 10   | 21     | exit     | L93JTIZ       |
| 10   | 23     | exit     | 322W7JE       |
| 10   | 23     | exit     | 0NTHK55       |
+------+--------+----------+---------------+
*/
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND hour = 10
  AND minute BETWEEN 15 AND 25
  AND activity = 'exit';

/*
Eugene Follow-up - Suspect could have made these withdrawals on Leggett Street:
+-----------+----------------+----------------+------------------+--------+
| person_id | account_number |  atm_location  | transaction_type | amount |
+-----------+----------------+----------------+------------------+--------+
| 467400    | 28500762       | Leggett Street | withdraw         | 48     |
| 395717    | 28296815       | Leggett Street | withdraw         | 20     |
| 449774    | 76054385       | Leggett Street | withdraw         | 60     |
| 686048    | 49610011       | Leggett Street | withdraw         | 50     |
| 458378    | 16153065       | Leggett Street | withdraw         | 80     |
| 396669    | 25506511       | Leggett Street | withdraw         | 20     |
| 438727    | 81061156       | Leggett Street | withdraw         | 30     |
| 514354    | 26013199       | Leggett Street | withdraw         | 35     |
+-----------+----------------+----------------+------------------+--------+
*/
SELECT ba.person_id, at.account_number, at.atm_location, at.transaction_type, at.amount
FROM atm_transactions at
JOIN bank_accounts ba
  ON at.account_number = ba.account_number
WHERE at.year = 2025
  AND at.month = 7
  AND at.day = 28
  AND at.atm_location = 'Leggett Street'
  AND at.transaction_type = 'withdraw';
/*
Raymond Follow-up - Suspect & Accomplice could have one of these phone numbers
+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |
| (367) 555-5533 | (375) 555-8161 | 45       |
| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |
| (770) 555-1861 | (725) 555-3243 | 49       |
| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54       |
+----------------+----------------+----------+
*/
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND duration < 60;

/*
Raymond Further Follow-up:
- Earliest flight from Fiftyville the following day took place at 8:20am to LaGuardia Airport (New York City) - Flight ID: 36
- Suspect could have one of these passport numbers:
+----+------+--------+-----------------------------+-------------------+---------------+-----------------+------+
| id | hour | minute |          full_name          |     full_name     |     city      | passport_number | seat |
+----+------+--------+-----------------------------+-------------------+---------------+-----------------+------+
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 7214083635      | 2A   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 1695452385      | 3B   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 5773159633      | 4A   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 1540955065      | 5C   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 8294398571      | 6C   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 1988161715      | 6D   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 9878712108      | 7A   |
| 36 | 8    | 20     | Fiftyville Regional Airport | LaGuardia Airport | New York City | 8496433585      | 7B   |
+----+------+--------+-----------------------------+-------------------+---------------+-----------------+------+
*/
SELECT f.id, f.hour, f.minute, origin_airport.full_name, destination_airport.full_name, destination_airport.city, p.passport_number, p.seat
FROM flights f
JOIN airports origin_airport
  ON f.origin_airport_id = origin_airport.id
 AND origin_airport.id = (SELECT id FROM airports WHERE city = 'Fiftyville')
JOIN airports destination_airport
  ON f.destination_airport_id = destination_airport.id
JOIN passengers p
  ON f.id = p.flight_id
WHERE year = 2025
  AND month = 7
  AND day = 29
  AND f.id = 36;

/*
 Thief - Bruce - Person ID: 686048
*/
SELECT people.*
FROM people
-- Suspected License Plates
JOIN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2025
      AND month = 7
      AND day = 28
      AND hour = 10
      AND minute BETWEEN 15 AND 25
      AND activity = 'exit'
) bsl
  ON people.license_plate = bsl.license_plate
-- Suspected Bank Accounts
JOIN (
    SELECT ba.person_id
    FROM atm_transactions at
    JOIN bank_accounts ba
      ON at.account_number = ba.account_number
    WHERE at.year = 2025
      AND at.month = 7
      AND at.day = 28
      AND at.atm_location = 'Leggett Street'
      AND at.transaction_type = 'withdraw'
) ba
  ON people.id = ba.person_id
-- Suspected Callers
JOIN (
    SELECT caller, duration
    FROM phone_calls
    WHERE year = 2025
    AND month = 7
    AND day = 28 AND duration < 60
) caller
  ON people.phone_number = caller.caller
-- Suspected passports
JOIN (
    SELECT p.passport_number
    FROM flights f
    JOIN airports origin_airport
      ON f.origin_airport_id = origin_airport.id
     AND origin_airport.id = (SELECT id FROM airports WHERE city = 'Fiftyville')
    JOIN airports destination_airport
      ON f.destination_airport_id = destination_airport.id
    JOIN passengers p
      ON f.id = p.flight_id
    WHERE year = 2025
      AND month = 7
      AND day = 29
      AND f.id = 36
) passports
  ON people.passport_number = passports.passport_number;

/*
Accomplice: Robin
*/
SELECT pc.caller, people_caller.name AS caller_name, pc.receiver, people_receiver.name AS receiver_name, duration
FROM phone_calls pc
JOIN people people_caller
  ON pc.caller = people_caller.phone_number
 AND people_caller.id = 686048 -- Thief Person ID
JOIN people people_receiver
  ON pc.receiver = people_receiver.phone_number
WHERE year = 2025
  AND month = 7
  AND day = 28
  AND duration < 60;
