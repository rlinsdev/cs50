---
--- Parking log
---
SELECT * FROM bakery_security_logs b
 INNER JOIN people p on p.license_plate = b.license_plate
 WHERE b.day = 28 and b.month = 7 and b.year = 2021
   and b.hour = 10 -- stay 10h to clean result
   and b.minute > 15 -- 10h 15 stolen. Greather than 10h 25 get out of parking
   and b.activity = 'exit'
 order by b.hour, b.minute;
-- id's Suspects [9]:
-- 221103
-- 686048
-- 243696
-- 467400
-- 398010
-- 396669
-- 514354
-- 560886
-- 449774

---
--- Transactions in ATM + Cars in Park
---
SELECT * FROM atm_transactions atm
 INNER JOIN bank_accounts ba ON ba.account_number = atm.account_number
 INNER JOIN people p on ba.person_id = p.id
 WHERE atm.atm_location = 'Leggett Street'
   AND atm.day = 28
   AND atm.month = 7
   AND atm.year = 2021
   AND atm.transaction_type = 'withdraw'
   AND p.id in (
'221103',
'686048',
'243696',
'467400',
'398010',
'396669',
'514354',
'560886',
'449774');

-- id's Suspects [5]
-- 686048
-- 514354
-- 396669
-- 467400
-- 449774

---
--- Call phone whit characteristics + filter by Suspects
-- Adding info of Suspect Name
---
SELECT PC.*, p_su.name AS Suspect, p.*
  FROM phone_calls pc
 INNER JOIN people p ON p.phone_number = pc.caller
 INNER JOIN people p_su ON p_su.phone_number = pc.receiver
 WHERE pc.day = 28
   AND pc.month = 7
   AND pc.year = 2021
   AND pc.duration < 60 -- less than 1 min.
 AND p.id in (
'686048',
'514354',
'396669',
'467400',
'449774');

---
-- 3 suspects:
---
-- id	    name
-- 449774	Taylor
-- 514354	Diana
-- 686048	Bruce

---
--- Flight 36
---
select * From flights f
  WHERE f.day = 29
   AND f.month = 7
   AND f.year = 2021
   AND f.hour = 8;

-- Brucer and Taylor are suspects. I Posted the exercise before with taylor,
--so, is Bruce
SELECT *
  FROM passengers p
 INNER JOIN people pp ON p.passport_number = pp.passport_number
 WHERE p.flight_id = 36
 AND pp.id IN (
 449774, 514354, 686048
 );

 ---
-- 2 suspects:
---
-- id	    name
-- 449774	Taylor
-- 686048	Bruce

---
---Taylor spend so much time in bakery... So, is Bruce:
---
SELECT p.*, b.* FROM bakery_security_logs b
 INNER JOIN people p on p.license_plate = b.license_plate
 WHERE b.day = 28 and b.month = 7 and b.year = 2021
   and b.hour = 10 -- stay 10h to clean result
   and b.activity = 'exit'
   AND p.id IN (686048, 449774)
 order by b.hour, b.minute;
