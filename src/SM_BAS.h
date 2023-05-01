/*!
 * @file SM_BAS.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * Building Automation 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/products/building-automation-8-layer-stackable-hat-v4-for-raspberry-pi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2023, Sequent Microsystems 
 *  
 */
#ifndef __SM_BAS__
#define __SM_BAS__

#define BAS_CHANNEL_NR_MIN		1
#define BAS_TRIAC_CH_NR_MAX		4

#define BAS_ADC_CH_NO	8
#define BAS_DAC_CH_NO 4
#define BAS_ADC_RAW_VAL_SIZE	2
#define BAS_DAC_MV_VAL_SIZE		2
#define VOLT_TO_MILIVOLT	1000
#define BAS_DAC_RAW_MAX 10000
#define BAS_COUNTER_SIZE 4
#define BAS_DRY_CONTACT_COUNT	8
#define BAS_DRY_CONTACT_CONTOR_SIZE 4

#define BAS_RETRY_TIMES	10
#define BAS_CALIBRATION_KEY 0xaa
#define BAS_RESET_CALIBRATION_KEY	0x55 
#define BAS_WDT_RESET_SIGNATURE 	0xCA
#define BAS_WDT_MAX_OFF_INTERVAL_S 4147200 //48 days

#define BAS_OWB_SENS_CNT 16
#define BAS_OWB_TEMP_SIZE_B 2

#define SLAVE_OWN_ADDRESS_BASE 0x48

enum
{
	BAS_I2C_TRIACS_VAL_ADD = 0,
	BAS_I2C_TRIACS_SET_ADD,
	BAS_I2C_TRIACS_CLR_ADD,
	BAS_I2C_DRY_CONTACT_VAL_ADD,

	BAS_I2C_U0_10_OUT_VAL1_ADD,
	BAS_I2C_U0_10_IN_VAL1_ADD = BAS_I2C_U0_10_OUT_VAL1_ADD
		+ BAS_DAC_CH_NO * BAS_ADC_RAW_VAL_SIZE,
	BAS_I2C_R_1K_CH1 = BAS_I2C_U0_10_IN_VAL1_ADD
		+ BAS_ADC_CH_NO * BAS_ADC_RAW_VAL_SIZE,
	BAS_I2C_R_10K_CH1 = BAS_I2C_R_1K_CH1 + BAS_ADC_CH_NO * BAS_ADC_RAW_VAL_SIZE,
	BAS_I2C_MEM_CALIB_VALUE = BAS_I2C_R_10K_CH1
		+ BAS_ADC_CH_NO * BAS_ADC_RAW_VAL_SIZE,
	BAS_I2C_MEM_CALIB_CHANNEL = BAS_I2C_MEM_CALIB_VALUE + 2, //0-10V out [1,4]; 0-10V in [5, 12]; R 1K in [13, 20]; R 10K in [21, 28]
	BAS_I2C_MEM_CALIB_KEY, //set calib point 0xaa; reset calibration on the channel 0x55
	BAS_I2C_MEM_CALIB_STATUS,
	BAS_I2C_MODBUS_SETINGS_ADD = 65,
	BAS_I2C_NBS1,
	BAS_I2C_MBS2,
	BAS_I2C_MBS3,
	BAS_I2C_MODBUS_ID_OFFSET_ADD,
	BAS_I2C_RTC_YEAR_ADD,
	BAS_I2C_RTC_MONTH_ADD,
	BAS_I2C_RTC_DAY_ADD,
	BAS_I2C_RTC_HOUR_ADD,
	BAS_I2C_RTC_MINUTE_ADD,
	BAS_I2C_RTC_SECOND_ADD,
	BAS_I2C_RTC_SET_YEAR_ADD,
	BAS_I2C_RTC_SET_MONTH_ADD,
	BAS_I2C_RTC_SET_DAY_ADD,
	BAS_I2C_RTC_SET_HOUR_ADD,
	BAS_I2C_RTC_SET_MINUTE_ADD,
	BAS_I2C_RTC_SET_SECOND_ADD,
	BAS_I2C_RTC_CMD_ADD,
	BAS_I2C_MEM_WDT_RESET_ADD,
	BAS_I2C_MEM_WDT_INTERVAL_SET_ADD,
	BAS_I2C_MEM_WDT_INTERVAL_GET_ADD = BAS_I2C_MEM_WDT_INTERVAL_SET_ADD + 2,
	BAS_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD = BAS_I2C_MEM_WDT_INTERVAL_GET_ADD + 2,
	BAS_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD = BAS_I2C_MEM_WDT_INIT_INTERVAL_SET_ADD
		+ 2,
	BAS_I2C_MEM_WDT_RESET_COUNT_ADD = BAS_I2C_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	BAS_I2C_MEM_WDT_CLEAR_RESET_COUNT_ADD = BAS_I2C_MEM_WDT_RESET_COUNT_ADD + 2,
	BAS_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	BAS_I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = BAS_I2C_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD
		+ 4,
	BAS_I2C_MEM_DRY_CONTACT_RISING_ENABLE = BAS_I2C_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD
		+ 4,
	BAS_I2C_MEM_DRY_CONTACT_FALLING_ENABLE,
	BAS_I2C_MEM_DRY_CONTACT_CH_CONT_RESET,
	BAS_I2C_DIAG_TEMPERATURE_MEM_ADD = 0x72,
	BAS_I2C_DIAG_24V_MEM_ADD,
	BAS_I2C_DIAG_24V_MEM_ADD1,
	BAS_I2C_DIAG_5V_MEM_ADD,
	BAS_I2C_DIAG_5V_MEM_ADD1,
	BAS_I2C_CAN_REC_MPS_MEM_ADD,
	BAS_I2C_REVISION_HW_MAJOR_MEM_ADD = 0x78,
	BAS_I2C_REVISION_HW_MINOR_MEM_ADD,
	BAS_I2C_REVISION_MAJOR_MEM_ADD,
	BAS_I2C_REVISION_MINOR_MEM_ADD,
	BAS_I2C_BUILD_DAY_MEM_ADD,
	BAS_I2C_BUILD_MOTH_MEM_ADD,
	BAS_I2C_BUILD_YEAR_MEM_ADD,
	BAS_I2C_BOARD_TYPE_MEM_ADD,
	BAS_I2C_MEM_DRY_CONTACT_CONTORS,
	BAS_I2C_MEM_DRY_CONTACT_CONTROL_END = 1 + BAS_I2C_MEM_DRY_CONTACT_CONTORS
		+ BAS_DRY_CONTACT_COUNT * BAS_DRY_CONTACT_CONTOR_SIZE,
	BAS_I2C_MEM_1WB_DEV = BAS_I2C_MEM_DRY_CONTACT_CONTROL_END,
	BAS_I2C_MEM_1WB_TEMP_ALL,

	BAS_I2C_MEM_CPU_RESET = 0xaa,
	BAS_I2C_MEM_HSI_LO,
	BAS_I2C_MEM_HSI_HI,
	BAS_I2C_MEM_1WB_START_SEARCH,
	BAS_I2C_MEM_1WB_T1,
	BAS_I2C_MEM_1WB_T16_END = BAS_I2C_MEM_1WB_T1 + BAS_OWB_SENS_CNT * BAS_OWB_TEMP_SIZE_B
		- 1,
	BAS_I2C_MEM_1WB_ROM_CODE_IDX = BAS_I2C_MEM_1WB_T1
		+ BAS_OWB_SENS_CNT * BAS_OWB_TEMP_SIZE_B,
	BAS_I2C_MEM_1WB_ROM_CODE, //rom code 64 bits
	BAS_I2C_MEM_1WB_ROM_CODE_END = BAS_I2C_MEM_1WB_ROM_CODE + 7,

	SLAVE_BUFF_SIZE = 255
};

/*!
 * @brief SM_BAS class
 */
class SM_BAS
{
public:
	/*!
	 * @brief Class constructor.
	 */
	SM_BAS(uint8_t stack = 0);

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

private:
	uint8_t _hwAdd;
	bool _detected;
	int writeBuff(uint8_t add, uint8_t* buff, uint8_t size);
	int readBuff(uint8_t add, uint8_t* buff, uint8_t size);
	int writeByte(uint8_t add, uint8_t value);
	int writeWord(uint8_t add, uint16_t value);
	int writeDWord(uint8_t add, uint32_t value);
	int readByte(uint8_t add, uint8_t* value);
	int readWord(uint8_t add, uint16_t* value);
	int readDWord(uint8_t add, uint32_t* value);
	int readSignedDWord(uint8_t add, int32_t* value);
};

#endif //__SM_BAS__
