# DATA-DRIVEN-BILLING-SYSTEM
Tutorial
## 🎯 Aim
The main objective is to develop a **general-purpose billing system** using **RFID technology** and **database integration** between an LPC2148 microcontroller and a Linux-based system.

## 📐 Block Diagram

> *(Insert block diagram image here if available. Example placeholder below)*

```text
  [ RFID Card ] ──▶ [ RFID Reader ]
                           │
                     [ LPC2148 MCU ]
                           │
                      [ UART ↔ MAX232 ]
                           │
                  [ USB-to-Serial Converter ]
                           │
                     [ Linux Host System ]
                           │
               [ stock.txt & bank.txt Database ]
🧰 Requirements
🔧 Hardware
✅ LPC2148 Development Board (ARM7)

✅ RFID Reader Module

✅ RFID Cards

✅ LCD Display

✅ Switches

✅ 4x4 Keypad

✅ MAX232 IC

✅ USB-to-UART Converter

💻 Software
✅ Embedded C Programming

✅ Keil µVision IDE

✅ Flash Magic (for flashing HEX)

✅ Linux OS (Ubuntu preferred)

✅ GCC Compiler

🚦 Project Workflow
📁 Create a project folder for all code files and data files.

🔗 Develop two modules:

👾 Embedded Application on LPC2148

💽 Linux Application with database (file-based)

🧱 Test peripherals individually:

✅ LCD (Strings, Chars, Integers)

✅ Keypad Input

✅ UART0/UART1 Communication (interrupt-based)

📡 Connect RFID Reader (D0 pin) to UART1

🧠 Implement the interrupt-based logic:

EINT0: Entry

EINT1: Delete

EINT2: Exit

🛠️ Microcontroller Operation
🔁 State Machine Behavior
Startup Display – LCD shows project title

Waiting for Entry Key (EINT0)

🔄 Accept Manager/Customer Card

➕ Manager Card → Add stock

🛒 Customer Card → Fetch item from DB → Update quantity → Add to bill

Delete Key (EINT1) – Rollback similar to Entry but in reverse

Exit Key (EINT2) – Trigger payment

💳 Payment Modes
Cash Mode:

Enter amount via keypad

Card Mode:

Place bank card → Send: BCARDNUMBERABILLAMOUNT$

Enter ATM PIN (3 attempts)

On failure → rollback stock

On success → complete transaction

💻 Linux Side Logic
📜 Create two text files:

stock.txt: Maintains stock info

bank.txt: Holds bank account data

🛠 Program Flow:

Display stock on terminal

Listen for card input via UART

Process based on card type:

MCARDNUMBER$ → Add items

CCARDNUMBER$ → Fetch cost & quantity

DCARDNUMBER$ → Delete item (reverse transaction)

BCARDNUMBERABILLAMOUNT$ → Payment handling

📁 Sample Text Files
🗂️ stock.txt

ItemName  | CardNumber | Quantity | Price
-----------------------------------------
SOAPS     | 00332069   |   190    | 100
MILKY     | 00336463   |   95     | 50
CHIPS     | 00312472   |   26     | 10

🏦 bank.txt 
Place     | IFSC Code | Bank Name | Account No | Balance | PIN
--------------------------------------------------------------
HYDERABAD | 099V23HE9 | VECTOR    | 12638754   | 10000   | 1234

📡 RFID Communication Format

When a card is scanned:
Raw Output (Hex): 
0x02 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38 0x03
→ Interpreted Card Number: 12345678

🧪 Test Plan
✅ LCD - Display static/dynamic content
✅ Keypad - Validate key inputs
✅ UART0/UART1 - Loopback test using minicom or HyperTerminal
✅ RFID Card Detection - Test output format
✅ Interrupts - Validate Entry/Delete/Exit triggers
✅ End-to-End - Add item → Pay → Bill generate.

🚀 Future Work
📲 Mobile App for live billing
☁️ Cloud sync for distributed stores
🧾 PDF bill generation
🔐 Secure PIN encryption.
