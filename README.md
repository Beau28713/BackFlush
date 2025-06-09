
# Automated Water Management System

## Project Overview

This project was initiated to assist my father in monitoring and managing the water supply for his off-grid camper. Previously, he had to manually check the water level each morning and ensure that water was still flowing from a natural spring source. If the flow stopped due to sediment blockage or airlocks, he would need to manually insert a hose and perform a backflush to clear the lines.

Although we installed a sediment screen at the spring house to reduce the debris, small particles and airlocks would still occasionally block the system. This project aims to automate the monitoring and backflushing process to reduce the need for manual intervention and improve system reliability.

## System Objectives

- **Monitor water level and flow status** in real time  
- **Automate the backflush process** in response to line blockages or low water levels  
- **Enable manual override mode** for on-demand system flushing  
- **Design a modular and upgradeable platform** for future feature additions  

## System Description

The system is built around an **Arduino Uno WiFi Rev 2**, which serves as the central controller. Water levels are monitored using a **tilt switch** and **float sensor**, while a **flow sensor** detects water movement.

When the water level drops below a predefined threshold, the Arduino detects a signal from the tilt switch and initiates the following automated sequence:

1. **Relay 1 activates**, rotating a **servo-operated 3-way water valve** to redirect the water line away from the holding tank.
2. After a 5-second delay, **Relay 2 activates**, powering a **5 GPM submersible pump** to perform a backflush operation.
3. The pump runs for **1 minute**, clearing out sediment and airlocks from the line.
4. **Relay 2 deactivates**, turning off the pump.
5. After a short delay, **Relay 1 deactivates**, returning the 3-way valve to its default position to resume normal water flow to the holding tank.

The system also includes a **manual override mode**, which allows the user to initiate the backflush cycle on demand, regardless of sensor input.

## Hardware Components

### Field Devices
- [3-Way Servo-Actuated Water Valve](https://www.aliexpress.us/item/3256804648845790.html)
- [5 GPM Submersible Pump](https://www.amazon.com/dp/B09ZV2364K)
- [Water Flow Sensor (Adafruit #5066)](https://www.adafruit.com/product/5066)
- [4-Channel Relay Module](https://www.amazon.com/dp/B00E0NSORY)
- [Water Circulator Pump (for testing)](https://www.amazon.com/dp/B0196WL55G)

### Control and Display
- [Arduino Uno WiFi Rev 2](https://store-usa.arduino.cc/products/arduino-uno-wifi-rev2)
- [Adafruit 16x2 LCD with I2C Backpack](https://www.adafruit.com/product/292)
- Push buttons, toggle switches, and status LEDs

### Power Supply
- **Input:** 120V AC  
- **Output:** 12V DC regulated power supply

## Future Improvements

- Integration with cloud monitoring for remote alerts and control  
- Addition of pressure sensors and logging capability  
- Solar power integration for off-grid energy independence  
- Enclosure for weatherproofing and durability in the field

## License

This project is open-source and available under the MIT License. Contributions and suggestions for improvement are welcome.
