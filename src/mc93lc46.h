#ifndef mc93lc46
#define mc93lc46

// pins

#define MC93LC46_PIN_CS		9
#define MC93LC46_PIN_CLK	10
#define MC93LC46_PIN_DI		6
#define MC93LC46_PIN_DO		7

#define MC93LC46_OPCODE_LEN (1 << 2) // 3 bits including SB
#define MC93LC46_ADDRESS	(1 << 6) // 7 bit address
#define MC93LC46_DATA_LEN	(1 << 7) // 8 bit data

// command codes 3bits
#define MC93LC46_CMD_READ	0x6
#define MC93LC46_CMD_WRITE	0x5
#define MC93LC46_CMD_EWEN	0x4
#define MC93LC46_CMD_EWDS	0x4
#define MC93LC46_CMD_ERAL	0x4
#define MC93LC46_CMD_ERASE	0x7


void mc93lc46_setup();
void mc93lc46_write(byte address, byte data);
unsigned int mc93lc46_read(unsigned char address);

#endif
