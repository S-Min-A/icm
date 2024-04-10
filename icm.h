#define IO_I2C_SUCCESS                      0
#define IO_I2C_ERROR                       -1
#define IO_I2C_ERROR_OPEN                  -2
#define IO_I2C_ERROR_INIT                  -3
#define IO_I2C_ERROR_IOCTL                 -4
#define IO_I2C_ERROR_WRITE                 -5
#define IO_I2C_ERROR_READ                  -6

#define HWLIB_SUCCESS                       0
#define HWLIB_ERROR                        -1

void Command(void);

void ICM_Init(void);

void ICM_GetTempOut(void);
void ICM_GetGyroXout(void);
void ICM_GetGyroYout(void);
void ICM_GetGyroZout(void);
void ICM_GetWhoAmI(void);

void ICM_SetConfig(uint8_t Config);
void ICM_SetGyroConfig(uint8_t GyroConfig);
void ICM_SetPwrMgmt1(uint8_t PwrMgmt1);

void ICM_GetAll(void);
void ICM_GetGyro(void);

int32_t I2C_Init(void);
int32_t I2C_Read_ICM(uint8_t address, uint8_t reg,void *rx_buffer, uint8_t len);
int32_t I2C_Write_ICM(uint8_t address, uint8_t reg, void *tx_buffer, uint8_t len);
