extern "C" {
#include <inttypes.h>
}

#include "Arduino.h"
#include "Wire.h"
#include "SM_BAS.h"

SM_BAS::SM_BAS(uint8_t stack)
{
	if (stack > 7)
		stack = 7;
	_hwAdd = SLAVE_OWN_ADDRESS_BASE + stack;
	_detected = false;
}

bool SM_BAS::begin()
{
	uint8_t value = 0;
	Wire.begin();
	if (0 == readByte(BAS_I2C_REVISION_MAJOR_MEM_ADD, &value))
	{
		_detected = true;
	}
	return _detected;
}

bool SM_BAS::isAlive()
{
	return _detected;
}

bool SM_BAS::writeTriac(uint8_t triac, bool val)
{
	if (triac > BAS_TRIAC_CH_NR_MAX || triac == 0)
	{
		return false;
	}
	if (val)
	{
		if (OK == writeByte(BAS_I2C_TRIACS_SET_ADD, triac))
			return true;
	}
	else
	{
		if (OK == writeByte(BAS_I2C_TRIACS_CLR_ADD, triac))
			return true;
	}
	return false;
}

bool SM_BAS::writeTriac(uint8_t val)
{
	if (OK == writeByte(BAS_I2C_TRIACS_VAL_ADD, 0x0f & val))
		return true;
	return false;
}

int SM_BAS::read0_10VInMv(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	if (channel < 1 || channel > BAS_ADC_CH_NO)
	{
		return -1;
	}
	ret = readWord(
		BAS_I2C_U0_10_IN_VAL1_ADD + (channel - 1) * BAS_ADC_RAW_VAL_SIZE, &val);
	if (ret < 0)
		return ret;
	return val;
}

float SM_BAS::read0_10VIn(uint8_t channel)
{
	int raw = 0;

	raw = read0_10VInMv(channel);
	if (raw >= 0)
	{
		return (float)raw / VOLT_TO_MILIVOLT;
	}
	return (float)-1;
}

bool SM_BAS::write0_10VOutMv(uint8_t channel, int val)
{

	if (channel < 1 || channel > BAS_DAC_CH_NO)
	{
		return -1;
	}

	if (val < 0)
		val = 0;
	if (val > BAS_DAC_RAW_MAX)
		val = BAS_DAC_RAW_MAX;

	if (OK
		== writeWord(
			BAS_I2C_U0_10_OUT_VAL1_ADD + (channel - 1) * BAS_ADC_RAW_VAL_SIZE, val))
	{
		return true;
	}
	return false;
}

int SM_BAS::read1kThermistor(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	if (channel < 1 || channel > BAS_ADC_CH_NO)
	{
		return -1;
	}
	ret = readWord(BAS_I2C_R_1K_CH1 + (channel - 1) * BAS_ADC_RAW_VAL_SIZE,
		&val);
	if (ret < 0)
		return ret;
	return val;
}

int SM_BAS::read10kThermistor(uint8_t channel)
{
	int ret = 0;
	uint16_t val = 0;

	if (channel < 1 || channel > BAS_ADC_CH_NO)
	{
		return -1;
	}
	ret = readWord(BAS_I2C_R_10K_CH1 + (channel - 1) * BAS_ADC_RAW_VAL_SIZE,
		&val);
	if (ret < 0)
		return ret;
	return val;
}

int SM_BAS::readDryContact()
{
	int ret = 0;
	uint8_t val = 0;
	ret = readByte(BAS_I2C_DRY_CONTACT_VAL_ADD, &val);
	if (ret < 0)
		return ret;
	return val;
}

bool SM_BAS::readDryContact(uint8_t channel)
{
	int ret = 0;
	uint8_t val = 0;
	if (channel > BAS_DRY_CONTACT_COUNT)
		return false;

	ret = readByte(BAS_I2C_DRY_CONTACT_VAL_ADD, &val);
	if (ret < 0)
		return false;
	if (val & (1 << (channel - 1)))
	{
		return true;
	}
	return false;
}

/*
 ***************** BAS_I2C access functions ****************************
 **********************************************************************
 */
int SM_BAS::writeByte(uint8_t add, uint8_t value)
{
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(value);
	return Wire.endTransmission();
}

int SM_BAS::writeWord(uint8_t add, uint16_t value)
{
	uint8_t buff[2];

	memcpy(buff, &value, 2);
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	Wire.write(buff[0]);
	Wire.write(buff[1]);
	return Wire.endTransmission();

}
int SM_BAS::writeDWord(uint8_t add, uint32_t value)
{
	uint8_t buff[4];
	int i = 0;

	memcpy(buff, &value, 4);
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	for (i = 0; i < 4; i++)
	{
		Wire.write(buff[i]);
	}
	return Wire.endTransmission();

}
int SM_BAS::readByte(uint8_t add, uint8_t *value)
{
	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)1);
	if (1 <= Wire.available())
	{
		*value = Wire.read();
	}
	else
	{
		return -1;
	}
	return 0;
}
int SM_BAS::readWord(uint8_t add, uint16_t *value)
{
	uint8_t buff[2];

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (2 <= Wire.available())
	{
		buff[0] = Wire.read();
		buff[1] = Wire.read();
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 2);
	return 0;
}

int SM_BAS::readDWord(uint8_t add, uint32_t *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 4);
	return 0;
}

int SM_BAS::readSignedDWord(uint8_t add, int32_t *value)
{
	uint8_t buff[4];
	int i = 0;

	if (0 == value)
	{
		return -1;
	}
	//Wire.begin();
	Wire.beginTransmission(_hwAdd);
	Wire.write(add);
	if (Wire.endTransmission() != 0)
	{
		return -1;
	}
	Wire.requestFrom(_hwAdd, (uint8_t)2);
	if (4 <= Wire.available())
	{
		for (i = 0; i < 4; i++)
		{
			buff[i] = Wire.read();
		}
	}
	else
	{
		return -1;
	}
	memcpy(value, buff, 4);
	return 0;
}
