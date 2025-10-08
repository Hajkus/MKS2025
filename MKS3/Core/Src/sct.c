/*
 * sct.c
 *
 *  Created on: Oct 8, 2025
 *      Author: xhajka00
 */


#include "sct.h";

static const uint32_t reg_values[3][10] = {
{
//PCDE--------GFAB @ DIS1
	0b0111000000000111 << 16,
	0b0100000000000001 << 16,
	0b0011000000001011 << 16,
	0b0110000000001011 << 16,
	0b0100000000001101 << 16,
	0b0110000000001110 << 16,
	0b0111000000001110 << 16,
	0b0100000000000011 << 16,
	0b0111000000001111 << 16,
	0b0110000000001111 << 16,
},
{
	//----PCDEGFAB---- @ DIS2
	0b0000011101110000 << 0,
	0b0000010000010000 << 0,
	0b0000001110110000 << 0,
	0b0000011010110000 << 0,
	0b0000010011010000 << 0,
	0b0000011011100000 << 0,
	0b0000011111100000 << 0,
	0b0000010000110000 << 0,
	0b0000011111110000 << 0,
	0b0000011011110000 << 0,
},
{
	//PCDE--------GFAB @ DIS3
	0b0111000000000111 << 0,
	0b0100000000000001 << 0,
	0b0011000000001011 << 0,
	0b0110000000001011 << 0,
	0b0100000000001101 << 0,
	0b0110000000001110 << 0,
	0b0111000000001110 << 0,
	0b0100000000000011 << 0,
	0b0111000000001111 << 0,
	0b0110000000001111 << 0,
},
};

void sct_init(void){
	sct_led(0);
}

void sct_led(uint32_t value){
	for (uint32_t i = 0; i <32; i++){
		//write LSB to SDI
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, (value >> i) & 0b1);

		//pulse CLK
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
	}
	//pulse NLA to latch data
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_value(uint16_t value){

    uint32_t reg = 0;

    // Split number into digits
    uint8_t digit0 = value % 10;         // DIS3
    uint8_t digit1 = (value / 10) % 10;  // DIS2
    uint8_t digit2 = (value / 100) % 10; // DIS1

    // Merge digits
    reg |= reg_values[0][digit2]; // hundreds
    reg |= reg_values[1][digit1]; // tens
    reg |= reg_values[2][digit0]; // units

    // send digits
    sct_led(reg);
}

