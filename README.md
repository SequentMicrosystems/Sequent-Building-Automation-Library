# Sequent-Building-Automation-Library
Arduino library for Sequent Microsystems [Building Automation 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/products/building-automation-8-layer-stackable-hat-v4-for-raspberry-pi)

## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *Sequent Building Automation HAT* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/Sequent-Building-Automation-Library/archive/refs/heads/main.zip) button from the main [page](https://github.com/SequentMicrosystems/Sequent-Building-Automation-Library), rename the uncompressed folder to "SM_Building_Automation" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent Home Automation HAT inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > Sequent Building Automation HAT > and chose your example to run.

## Usage
There are three ways to control the Home Automation Card from the Arduino environment.

### Method 1: Using any Arduino controller
You can use this method with any Arduino card with an I2C port by connecting I2C-SDA, I2C-SCL, +5V and GND, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C-SDA | --3| O - O | 4-- |  +5V |
| I2C-SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs using Uno, Nano, Teensy, Feather or ESP32. Plug the Home Automation HAT into the 40 pin connector of the adapter and write your Arduino software.

### Method 3: Using the SM ESP32-Pi Raspberry Pi Alternative Card
ESP32-Pi is a Raspberry Pi alternate solution which can control directly the Home Automation HAT.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1

## Function prototypes

	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	/*!
	 * @brief Set one triac state
	 * @param triac -  Triac number 1..4 as are printed on the card
	 * @param val The new state of the triac, true: energised
	 * @return Returns true if successful
	 */
	bool writeTriac(uint8_t triac, bool val);

	/*!
	 * @brief Write all triacs state as a 4 bits bitmap
	 * @param val The bitmap of the triacs states
	 * @return Returns true if successful
	 */
	bool writeTriac(uint8_t val);

	/*!
	 * @brief Read the value in millivolts of one 0-10V input channel
	 * @param channel The analog input channel number 1..8
	 * @return Returns analog input voltage in millivolts, range 0 ... 10000
	 */
	int read0_10VInMv(uint8_t channel);

	/*!
	 * @brief Read the value of one 0-10V input channel
	 * @param channel The analog input channel number 1..8
	 * @return Returns analog input voltage in millivolts, range 0 ... 10000
	 */
	float read0_10VIn(uint8_t channel);

	/*!
	 * @brief Write the analog output ports voltage in millivolts, range 0 to 10V
	 * @param channel Analog (0-10V) output channel number [1..4]
	 * @param val Votage output in millivolts [0..10000]
	 * @return Returns true if successful
	 */
	bool write0_10VOutMv(uint8_t channel, int val);

	/*!
	 * @brief Read the resistance of the 1k thermistor input channel
	 * @param channel [1..8]
	 * @return Resturns resistance in ohms [0..60000]
	 */
	int read1kThermistor(uint8_t channel);

	/*!
	 * @brief Read the resistance of the 10k thermistor input channel
	 * @param channel [1..8]
	 * @return Resturns resistance in ohms [0..60000]
	 */
	int read10kThermistor(uint8_t channel);

	/*!
	 * @brief Read dry contacts ports as a bitmap.
	 * @return the state of all dry contacts
	 */
	int readDryContact();

	/*!
	 * @brief Read one dry contact channel.
	 * @param channel [1..8]
	 * @return the state of one  dry contact channel
	 */
	bool readDryContact(uint8_t channel);
