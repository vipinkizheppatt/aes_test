/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xil_io.h"
#include "myip.h"

#define my_ip_addr 0x43c00000

int main()
{

	u32 data;

	xil_printf("Hello welcome\n\r");

	//Input in registers reg0, reg1, reg2, reg3
	//                   reg4, reg5, reg6, reg7
	//Output             reg8, reg9, reg10, reg11
	//Basically XOR the contents of four registers with other four registers and
	//store the result in another 4 registers

    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG0_OFFSET,0x55);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG1_OFFSET,0x55);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG2_OFFSET,0x55);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG3_OFFSET,0x55);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG4_OFFSET,0xAA);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG5_OFFSET,0xAA);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG6_OFFSET,0xAA);
    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG7_OFFSET,0xAA);

    MYIP_mWriteReg(my_ip_addr,MYIP_S00_AXI_SLV_REG12_OFFSET,0x1);

    data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG12_OFFSET);

    while(data != 0x0)
    	data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG12_OFFSET);

	data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG8_OFFSET);
	xil_printf("Register8 : %0x\n\r",data);
	data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG9_OFFSET);
	xil_printf("Register9 : %0x\n\r",data);
	data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG10_OFFSET);
	xil_printf("Register10 : %0x\n\r",data);
	data = MYIP_mReadReg(my_ip_addr, MYIP_S00_AXI_SLV_REG11_OFFSET);
	xil_printf("Register11 : %0x\n\r",data);

    return 0;
}
