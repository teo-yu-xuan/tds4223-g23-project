# Counselling System

## Appointments (appoint.txt)

| Data Type | Field           | Name                                                         |
| --------- | --------------- | ------------------------------------------------------------ |
| string    | appointID       | Appointment's ID (CT0000)                                    |
| string    | appointSvc      | Service (svc.txt)                                            |
| string    | appointCouns    | Counsellor's Name (staff.txt)                                |
| string    | appointMode     | Mode (Online or Offline)                                     |
| int       | appointDate     | Date (YYYYMMDD)                                              |
| string    | appointTime     | Time (HHMM)                                                  |
| string    | appointPtName   | Patient's Name  (pt.txt)                                     |
| int       | appointPtPhone  | Patient's Phone  (pt.txt)                                    |
| string    | appointPtEmail  | Patient's Email  (pt.txt)                                    |
| double    | appointGrossAmt | Gross Amount (svc.txt)                                       |
| double    | appointNetAmt   | Net Amount                                                   |
| string    | appointPayStat  | Payment's Status (Unpaid or Paid)                            |
| string    | appointStat     | Appointment's Status (Pending, Approved, Rejected or Cancelled) |

## Category (cat.txt)

| Data Type | Field   | Name            |
| --------- | ------- | --------------- |
| string    | catName | Category's Name |

## Services (svc.txt)

| Data Type | Field    | Name             |
| --------- | -------- | ---------------- |
| string    | svcName  | Service's Name   |
| int       | svcDur   | Service Duration |
| double    | svcPrice | Service Price    |

## Staff (staff.txt)

| Data Type | Field      | Name                               |
| --------- | ---------- | ---------------------------------- |
| string    | staffFName | Staff's First Name                 |
| string    | staffLName | Staff's Last Name                  |
| int       | staffPhone | Staff's Phone                      |
| string    | staffEmail | Staff's Email                      |
| int       | staffNRIC  | Staff's NRIC                       |
| string    | staffPwd   | Staff Password                     |
| string    | staffRole  | Staff's Role (Manager, Counsellor) |
| string    | staffStat  | Staff's Status                     |

## Patient (pt.txt)

| Data Type | Field    | Name                 |
| --------- | -------- | -------------------- |
| sting     | ptFName  | Patient's First Name |
| string    | ptLName  | Patient's Last Name  |
| int       | ptPhone  | Patient's Phone      |
| string    | ptEmail  | Patient's Email      |
| int       | ptAge    | Patient's Age        |
| string    | ptPwd    | Patient Password     |
| string    | ptStatus | Patient's Status     |

## Comment (cmt.txt)

| Data Type | Field    | Name              |
| --------- | -------- | ----------------- |
| string    | cmtEmail | Commentor's Email |
| string    | cmtCont  | Comment's Content |

