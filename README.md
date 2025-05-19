# Smart-Phone-Based-Urine-Conductivity-Test-Kit
Smartphone-based Urine Conductivity Test Kit using Arduino Nano, LM334, and sensors to measure urine conductivity. Features real-time data via MIT App Inventor. Achieved 98.14% accuracy through calibration. Simulated in Proteus for validation before hardware implementation.
🔧 Hardware Tools & Technologies
Arduino Nano: Acts as the central controller for data acquisition and signal processing.

LM334: Configured as an adjustable constant current source for accurate conductivity measurements.

Rain Sensor Conductivity Plate: Repurposed as the sensing electrode for detecting urine conductivity.

Analog pH Sensor & DS18B20 Temperature Sensor: Used for extended analysis, with temperature compensation enhancing accuracy.

MIT App Inventor: Enables real-time data visualization and smartphone-based interface for ease of use.

Proteus Software: Circuit design and simulation were validated in Proteus to ensure stable system performance.

Arduino IDE: Used for code development and hardware interfacing.

⚙️ Working Principle
The LM334 provides a stable current through the urine sample using the conductivity plate. The voltage drop across the sensor is measured by the Arduino and converted to conductivity using a calibration equation derived from standard solutions (0.01M KCl). Temperature correction is applied for more accurate readings.

📊 Calibration & Accuracy
The system was calibrated using NaCl, KCl, and mixed salt solutions. A known standard (1.413 mS/cm for 0.01 M KCl) was used to derive the calibration curve. The average error observed was 1.86%, resulting in a practical accuracy of 98.14% for the system. This ensures reliable measurements suitable for preliminary health assessment.

📱 Features
Real-time data transmission to Android smartphone.

Easy-to-use interface for users with no technical background.

Compact and cost-effective design for field and home usage.

💡 Future Scope
Integration of cloud storage for health data tracking.

Advanced analytics using machine learning.

Expansion to include multi-parameter urine analysis.

