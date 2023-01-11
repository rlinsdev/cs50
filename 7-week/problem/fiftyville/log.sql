---
--1 Report of crime:
--
-- stoled: 10:15 AM
SELECT * FROM crime_scene_reports
 WHERE street = 'Humphrey Street'
   AND day = 28;
SELECT * FROM crime_scene_reports WHERE id = 295;

---
---2 Interviews. 3 people that told about the 'bakery' in month 7
---
 SELECT * from interviews
  WHERE transcript like ('%bakery%')
    and month = 7;

---
--- 3 Bakery log -
---
-- 10h 25min. +- left the bakery park
-- 1 suspects by parking in bakery. Taylor is the thief?
SELECT p.*, b.* FROM bakery_security_logs b
 INNER JOIN people p on p.license_plate = b.license_plate
 WHERE b.day = 28 and b.month = 7 and b.year = 2021
   and b.hour = 10 -- stay 10h to clean result
   and b.minute > 24 -- 10h 15 stolen. Greather than 10h 25 get out of parking
   and b.activity = 'exit'
 order by b.hour, b.minute;

---
--- 4 atm transactions
---
-- 8 suspects using ATM that day.
--Taylon too. Amout=60
SELECT p.*, ba.*, atm.* FROM atm_transactions atm
 INNER JOIN bank_accounts ba ON ba.account_number = atm.account_number
 INNER JOIN people p on ba.person_id = p.id
 WHERE atm.atm_location = 'Leggett Street'
   AND atm.day = 28
   AND atm.month = 7
   AND atm.year = 2021
   AND atm.transaction_type = 'withdraw';

---
--- 5 Call
---
SELECT *
  FROM phone_calls pc
 WHERE pc.day = 28
   AND pc.month = 7
   AND pc.year = 2021
   AND pc.duration < 60 -- less than 1 min.
   AND caller = '(286) 555-6063'; -- Taylon number

---
--- 6 Receiver the call: James
---
SELECT *
  FROM people
 WHERE phone_number = '(676) 555-6554';

---
---7 Suspects: Taylor. Accomplice: James
---
SELECT * from people WHERE id IN (250277, 449774);


---
--- 8 First Flight in 29/07/2021
---
SELECT f.*, orig.full_name, orig.city, dest.full_name, dest.city
  FROM flights f
 INNER JOIN airports orig ON f.origin_airport_id = orig.id
 INNER JOIN airports dest ON f.destination_airport_id = dest.id
 WHERE f.day = 29
   AND f.month = 7
   AND f.year = 2021
   AND f.hour = 8;
-- Order By f.hour;

---
--- 9 Check if Taylon is in the flight
---
SELECT pp.*, p.*, f.* FROM flights f
 INNER JOIN passengers p on p.flight_id = f.id
 INNER JOIN people pp on pp.passport_number = p.passport_number
 WHERE f.id = 36; -- flight 36
