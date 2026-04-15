Smart Robotic Arm with Force-Based Gripping
Overview:
This project presents a 3-DOF robotic arm controlled using an ESP32 and PCA9685 servo driver. The system features an adaptive gripper that uses force feedback 
from FSR sensors to securely grasp objects without causing damage. The gripping action automatically stops when sufficient force is detected.
Features:
3-DOF robotic arm (Base, Arm, Gripper)
Serial command-based control
Force-controlled adaptive gripping using FSR sensors
Real-time feedback to prevent over-gripping
Expandable for automation and intelligent control
Hardware Components:
ESP32 Development Board
PCA9685 16-Channel Servo Driver
2 25 Kg servos and 1 MG995R servo
2 × Force Sensitive Resistors (FSR)
1kΩ Resistors (for voltage divider with FSR)
External 5V Power Supply:
Circuit Description:
ESP32 ↔ PCA9685
SDA → GPIO 21
SCL → GPIO 22
VCC → 3.3V
GND → GND
Servos (via PCA9685):
Channel 0 → Base Servo
Channel 1 → Arm Servo
Channel 2 → Gripper Servo
FSR Sensors (Voltage Divider):
Each FSR is connected in a voltage divider configuration:
One terminal → 3.3V
Other terminal → Analog Pin + 1kΩ resistor to GND
Pins Used:
FSR1 → GPIO 34
FSR2 → GPIO 35
Control Commands
Key	Function
a	elbow up
d	elbow down
w	wrist up
s	wrist down
g	Close gripper (stops on force detection)
o	Open gripper
 Working Principle:
The gripper begins closing when the 'g' command is received.
FSR sensors continuously measure the applied force.
When either FSR value crosses a predefined threshold, the gripping motion stops.
This ensures safe and adaptive object handling.
⚠️ Notes
FSR readings depend on resistor value (1kΩ used in this project).
Threshold values may require calibration based on object type.
External power supply is required for stable servo operation.
Common ground between ESP32 and PCA9685 is essential.
