# Home-Automation-Using-Aws
This demonstrates how to create a simple home automation project using Amazon AWS IoT Core and an ESP32 WiFi module. In a previous tutorial, we learned about getting started with AWS IoT Core with ESP32 and ESP8266. We also created an AWS IoT Lamp using the ESP32 and controlled it through the AWS Dashboard.

AWS IoT Core is a managed cloud service that enables connected devices to securely interact with cloud applications and other devices. The AWS IoT Core MQTT messaging service allows you to send and receive MQTT messages to and from AWS IoT Core. Using the Publish/Subscribe feature, you can send or receive data to and from the AWS IoT Core dashboard.

This tutorial focuses on controlling peripherals, such as AC appliances and light bulbs, via a relay from the AWS IoT Dashboard using an ESP32 WiFi module. This type of project is known as a home automation project. Home automation is the automatic control of electronic devices in a home using the Internet. This allows devices to be controlled remotely.

Here are the steps involved in this project:

1. Set up the ESP32 hardware.
2. Sign up for and configure Amazon Web Services.
3. Install the necessary libraries in the Arduino IDE.
4. Write the Arduino sketch.
5. Upload the sketch to the ESP32.
6. Test the project.

# Circuit Diagram
![Home-Automation-ESP32](https://github.com/PIYUSHVK00/Home-Automation-Using-Aws/assets/124399569/90ab424f-f433-4a3c-9457-c336a2f34492)

# Hardware

1. ESP32 WiFi Module
2. Relay 5V 4CH
3. 7805 Voltage Regulator
4. DC Power Jack DCJ0202
5. Resistor 330-ohm x 5
6. LED 5mm Any Color
7. 9V or 12V Power Supply
