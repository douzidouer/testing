#include "bcm2835.h"
#include "mfi.h"
#include "stdio.h"


/**
* This function will init the i2c interface and set the i2c baudrate and address of mfi chip
*/
void mfi_init(unsigned int Baudrate)
{
	bcm2835_gpio_fsel(RST_PIN, BCM2835_GPIO_FSEL_OUTP); // Setting the reset pin as an output pin
	bcm2835_gpio_write(RST_PIN, HIGH);

	#ifdef DEBUG
	printf("======= Debugging Message =======\n");
	printf("[mfi_init()]\nMFi Chip 7bit I2C address is [0x%.2x];\nMFi Chip Baudrate is [%d];\n", MFI_IIC_ADDRESS, Baudrate);
	printf("======= Debugging Output End =======\n");
	#endif

	bcm2835_i2c_set_baudrate(Baudrate);
	bcm2835_i2c_setSlaveAddress(MFI_IIC_ADDRESS);
}

/**
* This function will reset the MFI chip
*/
void mfi_reset(void)
{

}


/**
* This function will read data from the registers of the MFI chip
*/
int mfi_reg_read(char RegisterAddress, char* ReceiveBuffer, unsigned int bytes )
{
	int rc, count = 0;

	do
	{
		rc = bcm2835_i2c_write(&RegisterAddress,1);
		if(rc != 0){ count++; }
		bcm2835_delay(1);
	}while((count < MFI_MAX_RETRIES)&&(rc!=0));

	if(rc == 0)
	{
		rc = bcm2835_i2c_read(ReceiveBuffer, bytes);
	}

	#ifdef DEBUG
	printf("======= Debugging Message =======\n");
	printf("[mfi_reg_read()]\nWriting register address failed [%d] times;\nReading return value is [%d]--[0:ok,1:failed]\n", count, rc);
	printf("======= Debugging Output End =======\n");
	#endif

	return rc;
}

/**
* This function will write data to the registers of the MFI chip
* The first data of WriteBuffer should be the Register Address;
*/
int mfi_reg_write(char* WriteBuffer, unsigned int bytes)
{
	int rc, i, count = 0;

	do
	{
		rc = bcm2835_i2c_write(WriteBuffer, bytes);
		if(rc != 0){ count++; }
		bcm2835_delay(1);
	}while((count < MFI_MAX_RETRIES)&&(rc!=0));

	#ifdef DEBUG
	printf("======= Debugging Message =======\n");
	for(i=0; i<bytes; i++)
		{ printf("The writing data is[%.2d:0x%.2x];\n",i , *WriteBuffer++);}
	printf("[mfi_reg_write()]\nWriting register address failed [%d] times;\nWriting return value is [%d]--[0:ok,1:failed]\n", count, rc);
	printf("======= Debugging Output End =======\n");
	#endif

	return rc;
}


/**
* Reads the device/fw version. Returns 0 on success, otherwise < 0
*/
int mfi_read_device_version(char *dev_fw)
{
	int rc;

	rc = mfi_reg_read(DeviceVersion, dev_fw, 2);
	return rc;
}


/**
* Reads the device protocol version. Returns 0 on success, otherwise < 0
*/
int mfi_read_protocol_version(char *major_minor)
{
	int rc;

	rc = mfi_reg_read(AuthProtMajorV, major_minor, 2);
	return rc;
}

/**
* Reads the device ID (4 bytes). Returns 0 on success, otherwise < 0
*/
int mfi_read_device_id(char device_id[4])
{
	int rc;

	rc = mfi_reg_read(DeviceID,device_id,4);
	return rc;
}

/**
* Reads the device information registers of the authentication coprocessor
* (protocol version and device ID). Returns 0 on success, otherwise < 0
*/
void mfi_show_device_info(void)
{
	char dev_fw[2] = {0};
	char maj_min[2] = {0};
	char device_id[4] = {0};

	mfi_read_device_version(dev_fw);
	mfi_read_protocol_version(maj_min);
	mfi_read_device_id(device_id);

	printf("MFi: Device Version is [0x%.2x];\nMFi: Firmware Version is [0x%.2x];\n", dev_fw[0], dev_fw[1]);
	printf("MFi: Authentication Protocol Major Version is [0x%.2x];\nMFI: Authentication Protocol Minor Version is [0x%.2x];\n",maj_min[0], maj_min[1]);
	printf("MFi: Device ID is [0x%.2x%.2x%.2x%.2x];\n", device_id[0],device_id[1],device_id[2],device_id[3]);
}






