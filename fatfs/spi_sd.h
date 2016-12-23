//  ******************************************************************************
//  * @file    sd.h 
//  * @author  CIG
//  * @version V1.0.0
//  * @date    
//  * @brief   
//  ******************************************************************************

#ifndef SD_H_
#define SD_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
// �������  ���  ������  �  SD
#include "stm32f0xx_spi.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"
#include "diskio.h"

#include "ff.h"
#include "ffconf.h"

//#include "system.h"
/*
#define GO_IDLE_STATE            0              //����������� ������������
#define SEND_IF_COND             8              //��� SDC V2 - �������� ��������� ����������
#define READ_SINGLE_BLOCK        17             //������ ���������� ����� ������
#define WRITE_SINGLE_BLOCK       24             //������ ���������� ����� ������
#define SD_SEND_OP_COND	         41             //������ �������� �������������
#define APP_CMD			 55                    //������� ������� �� ACMD <n> ������
#define READ_OCR		 58                     //������ �������� OCR
*/
//���������������� ��� ���������� ������� SS
//#define CS_ENABLE         GPIO_ResetBits(GPIOB, GPIO_Pin_12)
//#define CS_DISABLE    	  GPIO_SetBits(GPIOB, GPIO_Pin_12)
/* Port Controls */
#define CS_HIGH()			GPIOA->BSRR  = GPIO_Pin_4		/* MMC CS = H */
#define CS_LOW()			GPIOA->BRR  = GPIO_Pin_4		/* MMC CS = L */

void disk_timerproc(void);
//DRESULT disk_read(uint8_t drv,uint8_t *buff,	uint32_t sector,uint8_t count);

#ifdef __cplusplus
}
#endif

#endif /* SD_H_ */
