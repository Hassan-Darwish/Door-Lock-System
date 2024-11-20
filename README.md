# Door Lock System

The Door Lock System is a robust, AVR microcontroller-based security solution designed for access control. It uses a keypad and LCD for user interaction, password verification, and secure door operations. The system ensures user-friendly access management with built-in features like multiple attempts, password change functionality, and system lockdown for enhanced security.

---

## Features

1. **Password Management:**
   - Password setup during the initial configuration.
   - Password verification during door access.
   - Password reset/change functionality.

2. **Modes of Operation:**
   - **Normal Operation Mode:** Open the door with the correct password.
   - **Change Password Mode:** Update the stored password securely.

3. **Multiple Password Attempts:**
   - Allows up to three incorrect attempts before locking the system.

4. **Visual and Audio Feedback:**
   - LCD provides step-by-step instructions and feedback.
   - Buzzer alarm activates during unauthorized access or system lockdown.

5. **Security Features:**
   - System lockdown after exceeding the maximum incorrect attempts.
   - Timed door opening and closing operations using a motor.

---

## Components Required

1. **Microcontroller:**
   - ATmega32.

2. **Input Devices:**
   - 4x4 Keypad.

3. **Output Devices:**
   - LCD (16x2) for user interaction.
   - DC motor for door control.
   - Buzzer for alarm signals.

4. **Additional Components:**
   - External EEPROM for password storage.
   - PIR sensor for detecting door entry.

---

## How It Works

1. **Initialization:**
   - The HMI ECU initializes the keypad, LCD, and UART communication.
   - The Control ECU initializes the motor, buzzer, EEPROM, and PIR sensor.

2. **Password Verification:**
   - Users enter their password on the keypad.
   - The password is transmitted to the Control ECU via UART for verification.
   - If the password is correct, the door opens; otherwise, an error message is displayed.

3. **Password Change:**
   - Users can request a password change via the keypad.
   - The old password is verified before allowing a new password to be set.

4. **System Lockdown:**
   - After three incorrect password attempts, the system locks down for a specified duration.

5. **Door Operation:**
   - The door opens upon successful verification and automatically closes after a timeout.

---

## Code Overview

The system consists of two main modules:

1. **HMI ECU:**
   - Handles user input and display using the keypad and LCD.
   - Communicates with the Control ECU via UART.
   - Key Functions:
     - `getPasswordSend()`: Collects and sends the password to the Control ECU.
     - `awaitPasswordResponse()`: Waits for the password verification response.

2. **Control ECU:**
   - Verifies the password and controls hardware operations.
   - Stores and retrieves passwords using external EEPROM.
   - Key Functions:
     - `isPasswordCorrect()`: Compares user-entered passwords with stored passwords.
     - `savePassword()`: Stores a new password in EEPROM.
     - `extractPassword()`: Retrieves the stored password from EEPROM.

---

## Pin Configuration

| Device         | Port/Pin   | Description                          |
|----------------|------------|--------------------------------------|
| Keypad         | PORTA      | Collects user input for passwords.  |
| LCD            | PORTC      | Displays system messages.           |
| UART           | PORTD/PIN1 | Transmits data between HMI and Control ECU. |
| DC Motor       | PORTB/PIN0 | Controls door opening and closing.  |
| Buzzer         | PORTB/PIN1 | Activates during alarms.            |
| PIR Sensor     | PORTB/PIN2 | Detects door entry.                 |

---

## How to Run

1. **Setup Hardware:**
   - Assemble the circuit according to the pin configuration.
   - Connect the HMI ECU and Control ECU via UART.

2. **Load Code:**
   - Program the HMI ECU and Control ECU firmware using an AVR programmer.

3. **Power On:**
   - The system will prompt for password setup during the first use.
   - Use the keypad to interact with the system for normal operations or password changes.

---

## Circuit Diagram

The circuit design can be found in the included Proteus simulation file. Open it using Proteus Design Suite to explore or modify the circuit.
<img width="1920" alt="Screenshot 2024-11-21 at 12 23 02 AM" src="https://github.com/user-attachments/assets/217f50d2-e043-4067-9f75-6ef0389a6f5a">


---

## Future Enhancements

- Add a mobile app for remote door access control.
- Introduce fingerprint or RFID authentication for enhanced security.
- Expand to support multiple users with unique passwords.

---

## License

This project is open-source under the MIT License. Feel free to modify and share.

---

## Author

Developed by **Hassan Darwish**.
