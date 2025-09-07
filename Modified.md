# RFID Door Access Control System (Solenoid Modified)

This Arduino project implements an RFID-based door access control system using the MFRC522 RFID reader module. It allows authorized RFID cards (PICCs) to unlock a door via a solenoid, manages card IDs in the Arduino's EEPROM, and supports a programming mode to add or remove cards. The system includes LED and buzzer feedback, a wipe button to clear EEPROM, and a manual unlock button for internal access.

**Note**: This code is a modification of an original project designed for a servo motor-based lock actuator. The original code was adapted to use a solenoid for door control by Dilan Ravindu, with additional features (buzzer, timeout, adjustable unlock duration) added. The original author is not specified, and this project is shared under the MIT License.

## Features
- **RFID Card Scanning**: Uses the MFRC522 module to read 4-byte UID RFID cards.
- **Access Control**: Grants or denies access based on stored card UIDs in EEPROM.
- **Master Card**: A designated master card toggles programming mode to add/remove cards.
- **EEPROM Storage**: Stores card UIDs persistently, with a magic number (143) to track master card definition.
- **Visual Feedback**: Red, green, and blue LEDs indicate denied access, granted access, and system status.
- **Audible Feedback**: Buzzer provides beeps for access granted/denied, EEPROM operations, and errors.
- **Wipe Functionality**: A button can wipe EEPROM to reset the system (15-second confirmation delay).
- **Manual Unlock**: A button allows unlocking the door from inside without an RFID card.
- **Program Mode**: Cycles LEDs and exits automatically after 30 seconds of inactivity.
- **Solenoid Control**: Modified to use a solenoid (pin 8) instead of a servo motor for door locking/unlocking.
- **Configurable Unlock Duration**: Adjustable solenoid unlock time (default: 5 seconds).

## Hardware Requirements
- **Arduino Board**: Compatible with Uno, Mega, Nano, Leonardo, or Pro Micro.
- **MFRC522 RFID Reader Module**: For scanning RFID cards.
- **Solenoid Lock**: Connected to pin 8 for door control (replaces servo motor).
- **Piezo Buzzer**: Connected to pin 4 for audible feedback.
- **LEDs**:
  - Red LED (pin 6): Indicates denied access or errors.
  - Green LED (pin 7): Indicates granted access.
  - Blue LED (pin 5): Indicates normal mode or programming status.
- **Buttons**:
  - Wipe Button (pin 3): Triggers EEPROM wipe.
  - Door Unlock Button (pin 2): Manual unlock from inside.
- **RFID Cards/Tags**: Mifare cards with 4-byte UIDs (7-byte UIDs not currently supported).

## Pin Connections
| **Signal**      | **MFRC522 Pin** | **Arduino Uno Pin** | **Purpose**                     |
|------------------|-----------------|---------------------|----------------------------------|
| RST/Reset       | RST             | 9                   | Reset MFRC522 module            |
| SPI SS          | SDA(SS)         | 10                  | Slave Select for SPI            |
| SPI MOSI        | MOSI            | 11 / ICSP-4         | SPI Master Out Slave In         |
| SPI MISO        | MISO            | 12 / ICSP-1         | SPI Master In Slave Out         |
| SPI SCK         | SCK             | 13 / ICSP-3         | SPI Clock                       |
| Red LED         | -               | 6                   | Denied access/error indication   |
| Green LED       | -               | 7                   | Granted access indication       |
| Blue LED        | -               | 5                   | System status indication        |
| Solenoid        | -               | 8                   | Door lock control (modified)    |
| Wipe Button     | -               | 3                   | Triggers EEPROM wipe            |
| Door Unlock     | -               | 2                   | Manual door unlock (inside)     |
| Buzzer          | -               | 4                   | Audible feedback (new)          |

**Note**: Adjust pin connections for other Arduino boards as per the code comments. Ensure the solenoid and buzzer are compatible with your Arduino’s voltage/current or use a relay/transistor for safety.

## Software Requirements
- **Arduino IDE**: For uploading the code to the Arduino.
- **Libraries**:
  - `MFRC522.h`: For MFRC522 RFID reader communication.
  - `SPI.h`: For SPI protocol (included with Arduino IDE).
  - `EEPROM.h`: For EEPROM read/write operations (included with Arduino IDE).

Install the MFRC522 library via the Arduino Library Manager or download from [GitHub](https://github.com/miguelbalboa/rfid).

## Modifications from Original
The original code was designed to control a servo motor for the lock actuator. Key changes made by Dilan Ravindu include:
- Replaced servo motor control with solenoid control on pin 8.
- Removed `Servo.h` library dependency.
- Modified the `granted()` function to use `digitalWrite(sol, HIGH)` for unlocking and `digitalWrite(sol, LOW)` for locking, instead of servo angle commands.
- Ensured the solenoid is initialized to `LOW` (locked) in `setup()`.

**Additional Modifications**:
- Added buzzer support on pin 4 for audible feedback (e.g., beeps for access, EEPROM operations).
- Introduced configurable unlock duration (`UNLOCK_DURATION`, default 5 seconds).
- Added 30-second timeout for program mode to enhance security.

## Setup Instructions
1. **Connect Hardware**:
   - Wire the MFRC522 module, LEDs, solenoid, buzzer, and buttons to the Arduino as per the pin table.
   - Ensure LEDs and buzzer are connected with appropriate resistors (e.g., 220Ω for LEDs, 100Ω for buzzer if needed).
   - Verify whether your LEDs are common anode or cathode and comment/uncomment `#define COMMON_ANODE` in the code accordingly.
   - Connect the solenoid to pin 8, ensuring it is compatible with your Arduino’s power supply (or use a relay with appropriate driver circuitry).

2. **Install Libraries**:
   - Open Arduino IDE, go to `Sketch > Include Library > Manage Libraries`.
   - Search for and install the `MFRC522` library.

3. **Upload Code**:
   - Copy the modified code into the Arduino IDE.
   - Connect your Arduino to your computer via USB.
   - Select the correct board and port in the IDE.
   - Upload the code.

4. **Initial Setup**:
   - On first boot, if no master card is defined (EEPROM address 1 ≠ 143), the system prompts you to scan a card to set as the master card.
   - The blue LED blinks, and the buzzer beeps until a master card is scanned and stored.

## Usage
- **Normal Mode**:
  - The blue LED is on, indicating the system is ready to scan cards.
  - Scan an RFID card:
    - If the card’s UID is in EEPROM, the green LED lights, the buzzer beeps once (500ms), and the solenoid unlocks the door for 5 seconds.
    - If not, the red LED lights, and the buzzer beeps three times (100ms each).
  - Press the door unlock button (pin 2) to manually unlock the door from inside (buzzer beeps).

- **Program Mode**:
  - Scan the master card to enter program mode (LEDs cycle red, green, blue; buzzer beeps).
  - The system exits program mode automatically after 30 seconds of no card scans.
  - Scan a card:
    - If known, it is removed from EEPROM (buzzer beeps for success).
    - If unknown, it is added to EEPROM (buzzer beeps for success).
  - Scan the master card again to exit program mode (buzzer beeps).

- **EEPROM Wipe**:
  - Hold the wipe button (pin 3) during startup for 15 seconds to clear all EEPROM data (buzzer beeps).
  - Alternatively, hold the wipe button for 10 seconds during operation to reset the master card (system halts, buzzer beeps).

## Debugging
- Open the Serial Monitor (9600 baud) to view system messages, such as:
  - Scanned card UIDs.
  - Success/failure of EEPROM operations.
  - Master card definition status.
  - MFRC522 module version and connection status.
  - Program mode timeout events.

## Notes
- The code assumes 4-byte UID cards. Support for 7-byte UIDs requires modification.
- EEPROM has limited write cycles; avoid excessive writes to prolong its lifespan.
- Ensure the solenoid and buzzer are properly rated for your Arduino’s voltage/current. Use a relay or transistor circuit if necessary to avoid damaging the Arduino.
- Adjust `UNLOCK_DURATION` in the code to change the solenoid unlock time.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Contributing
This project is a derivative work. Feel free to fork this repository, make improvements, and submit pull requests. For suggestions or bug reports, contact Dilan Ravindu at mbdilanravindu1777@gmail.com. Please respect the original code’s licensing.

## Acknowledgments
- Original code: Unknown author, designed for servo motor-based lock actuator.
- Modified by: Dilan Ravindu (mbdilanravindu1777@gmail.com) to support solenoid control, buzzer, and additional features.
- Based on the MFRC522 library by Miguel Balboa.
- Inspired by RFID access control projects in the Arduino community.
