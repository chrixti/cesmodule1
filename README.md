# About

This project implements a simple animated dinosaur jumping over randomly generated trees, similar to the Chrome Dino game, on a TFT display using the TFT_eSPI and SPI libraries for Arduino. The game features a dinosaur that jumps over randomly generated trees, similar to the Chrome Dino game. 

# Demo
![get-GIF](https://github.com/chrixti/cesmodule1/blob/main/dino.gif)

The above GIF shows the dinosaur jumping over trees, and the background updating as trees move across the screen.
Project Structure

    image-scroll.ino: Contains logic of animated art.
    b: Stores the bitmap data for the dinosaur and trees.
    README.md: Documentation for the project.

# How It Works

    Dinosaur Movement: The dinosaur remains fixed at the bottom of the screen and can jump when trees approach. The jump has a defined height, speed, and fall mechanics.
    Tree Generation: Trees are randomly generated off-screen and move toward the left. Once they move off-screen, they are reset to reappear after a random delay.
    Collision Detection: The game detects when the dinosaur is about to collide with a tree and initiates a jump if a collision is imminent.
    Graphics: The dinosaur and trees are drawn using bitmap images scaled for the TFT display.

# Installation and Setup 
(source: https://coms3930.notion.site/Lab-1-TFT-Display-a53b9c10137a4d95b22d301ec6009a94)

Requirements

    Arduino IDE: Download here
    TFT_eSPI Library
    SPI Library
    TFT Display Module (e.g., ILI9341)
    ESP32 Board (e.g., TTGO T-Display)

Arduino Installation

We will be using the Arduino IDE to program the TTGO T-Display.

    Download and Install Arduino: You can download the Arduino IDE from this link. Follow the installation instructions for your operating system.

TTGO T-Display Driver Install

    Install the TTGO T-Display Driver:
        The TTGO T-Display uses the CH9102 chip, so ensure you install the appropriate CHxxx Series driver.
        You can find the driver and installation instructions under "Install USB driver" at this GitHub page.
        Download the zip file, which contains the PDF instructions: CH34X_DRV_INSTAL_INSTRUCTIONS.pdf.
        For Mac Users: After downloading the driver, go to Settings > Privacy and Security and scroll down to click Allow to permit the driver installation.

    Check the COM Port Assignment:
        On a Mac, to verify the driver and COM port are correctly installed, run the following command in your terminal:

        bash

        ls /dev/tty.wch*

        This checks for connected input devices that communicate with your computer.

Installing the TFT_eSPI Library

The TFT_eSPI library allows us to control the TTGO T-Display.

    Install the TFT_eSPI Library:
        Open the Arduino IDE and go to Tools > Library Manager.
        Search for tft_espi by Bodmer and click the Install button.

    Configure the TFT_eSPI Library:
        Navigate to the installed library folder, which is usually located at: Documents/Arduino/libraries/tft_espi.
        Open the file User_Setup_Select.h inside the TFT_eSPI folder.
        Comment out the line:

        cpp

#include <User_setup.h>

Uncomment the line:

cpp

        #include <User_Setups/Setup25_TTGO_T_Display.h>

        Commenting and uncommenting simply involves adding // to comment out a line and removing // to uncomment it. Make sure to leave the # character intact.

Installing the ESP32 Board Definition

    Install the ESP32 Board Definition:
        Follow the instructions in the official Espressif documentation for installing the ESP32 board library using the Arduino IDE. You can find the steps here under the section Installing using Arduino IDE.

Additional Arduino Tips

To make debugging and uploads easier, it’s helpful to enable verbose output in the Arduino IDE.

    Go to Arduino > Preferences.
    Under Show verbose output during, check both the compilation and upload options to receive more detailed output when compiling and uploading sketches.

Arduino Upload Settings

    Board: Set the board to ESP32 Dev Module:
        Go to Tools > Boards > esp32 > ESP32 Dev Module.

    Port: Select the correct port:
        Go to Tools > Port and choose the port that corresponds to your device.
        For Mac users: Select the wchusb port, not the usb port (usually, two options will appear).

    Upload Speed: Set the upload speed to 115200.

Uploading the Code

    Open the .ino file provided in the Arduino IDE.
    Ensure the correct board and port are selected (as per the previous steps).
    Click the Upload button (the right arrow icon) to upload the code to your microcontroller.
    
# Code Overview

The main logic is split into several parts:

    Initialization (setup()): Initializes the display and sets up the game parameters, including the initial positions of the dinosaur and trees.
    Main Loop (loop()): Continuously updates the positions of the trees and handles the jumping logic for the dinosaur and also checks for collisions/redraws the screen.
    Bitmap Drawing: The drawScaledBitmap() function is used to scale and draw bitmaps for the dinosaur and trees on the screen.

# Customization

You can customize the following aspects of the art:

    Jump Height & Speed: Modify jumpHeight, jumpSpeed, and fallSpeed variables to adjust the dinosaur's jump behavior.
    Tree Speed: Modify treeSpeed to increase or decrease the movement speed of the trees.
    Number of Trees: Adjust the numTrees variable to add more trees to the game.
