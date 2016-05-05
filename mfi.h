/* Defines for MFI APN337S3959 */
#ifndef MFI_H
#define MFI_H

/**
* 7 bits I2C address
*/
#define MFI_IIC_ADDRESS  0x11

/**
*  the number of rewrite
*/
#define MFI_MAX_RETRIES 10

/**
*  the reset pin(Pi GPIO6) of mfi chip
*/
#define RST_PIN    RPI_BPLUS_GPIO_J8_31

/**
* The MFi chip register
*/
typedef enum {
	DeviceVersion      = 0x00,    /*Device Version*/
	FirmwareVersion    = 0x01,    /*Firmware Version*/
	AuthProtMajorV     = 0x02,    /*Authentication Protocol Major Version*/
	AuthProtMinorV     = 0x03,    /*Authentication Protocol Minor Version*/
	DeviceID           = 0x04,    /*Device ID*/
	ErrorCode          = 0x05,    /*Error Code*/
	AuthenticationC_S  = 0x10,    /*Authentication Control and Status*/
	CRespDataLength    = 0x11,    /*Challenge Response Data Length*/
	CRespData          = 0x12,    /*Challenge Response Data*/
	CDataLength        = 0x20,    /*Challenge Data Length*/
	ChallengeData      = 0x21,    /*Challenge Data*/
	AcceCertDataLength = 0x30,	  /*Accessory Certificate Data Length*/
	AcceCertDataP1     = 0x31,    /*Accessory Certificate Data Part 1*/
	AcceCertDataP2     = 0x32,    /*Accessory Certificate Data Part 2*/
	AcceCertDataP3     = 0x33,    /*Accessory Certificate Data Part 3*/
	AcceCertDataP4     = 0x34,    /*Accessory Certificate Data Part 4*/
	AcceCertDataP5     = 0x35,    /*Accessory Certificate Data Part 5*/
	AcceCertDataP6     = 0x36,    /*Accessory Certificate Data Part 6*/
	AcceCertDataP7     = 0x37,    /*Accessory Certificate Data Part 7*/
	AcceCertDataP8     = 0x38,    /*Accessory Certificate Data Part 8*/
	AcceCertDataP9     = 0x39,    /*Accessory Certificate Data Part 9*/
	AcceCertDataP10    = 0x3A,    /*Accessory Certificate Data Part 10*/
	SelfTestC_S        = 0x40,    /*Self-Test Contorl and Status*/
	SysEventCounter    = 0x4D,    /*System Event Counter*/
	ApDevCertDataLeng  = 0x50,    /*Apple Device Certificate Data Length*/
	ApDevCertDataP1    = 0x51,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP2    = 0x52,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP3    = 0x53,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP4    = 0x54,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP5    = 0x55,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP6    = 0x56,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP7    = 0x57,    /*Apple Certificate Data Part 1*/
	ApDevCertDataP8    = 0x58,    /*Apple Certificate Data Part 1*/
}MFiRegisterMap;

/**
 * Setting the reset pin, IIC baudrate and address
 *
 * @param Baudrate         - Setting the I2C baudrate.
 */
extern void mfi_init(unsigned int Baudrate);

/**
 * Reset the MFi chip
 */
extern void mfi_reset(void);

/**
 * Reading data from the MFi chip
 *
 * @param RegisterAddress - the register address of MFi chip .
 * @param ReceiveBuffer   - the data will save into this buffer.
 * @param bytes           - how many data you want to read.
 */
extern int mfi_reg_read(char RegisterAddress, char* ReceiveBuffer, unsigned int bytes );

/**
 * Writing data to the MFi chip
 *
 * @param WriteBuffer     - the data will write into MFi chip; 
 *                          the first data should be the register address which you are writing.
 * @param bytes           - how many data you want to write.
 */
extern int mfi_reg_write(char* WriteBuffer, unsigned int bytes);

/**
* Reads the device/fw version. Returns 0 on success, otherwise < 0
*/
extern int mfi_read_device_version(char *dev_fw);

/**
* Reads the device protocol version. Returns 0 on success, otherwise < 0
*/
extern int mfi_read_protocol_version(char *major_minor);

/**
* Reads the device ID (4 bytes). Returns 0 on success, otherwise < 0
*/
extern int mfi_read_device_id(char device_id[4]);

/**
* Reads the device information registers of the authentication coprocessor
* (protocol version and device ID). 
*/
extern void mfi_show_device_info(void);

#endif /* MFI_H */