/*
 * DAC.h
 *
 *  Created on: Apr 15, 2025
 *      Author: akila
 */

#ifndef INCLUDE_DAC_H_
#define INCLUDE_DAC_H_

#define DAC_Begin (2725) // 2v
//#define DAC_Limit (850) // 6.08v
//#define DAC_Adjust (875) // 6.00v

#define DAC_Limit (1500) // 4.02v
#define DAC_Adjust (1505) // 4.00v

//#define DAC_Limit (1400) // 4.29v
//#define DAC_Adjust (1405) // 4.32v

//#define DAC_Limit (1300) // 4.66v
//#define DAC_Adjust (1300) // 4.66v

//#define DAC_Limit (1200) // 4.98v
//#define DAC_Adjust (1190) // 5.00v

//#define DAC_Limit (1000) // 5.61v
//#define DAC_Adjust (1033) // 5.50v

//#define DAC_Limit (715) // 6.5v
//#define DAC_Adjust (712) // 6.5v


unsigned int DAC_data;

void Init_DAC(void);





#endif /* INCLUDE_DAC_H_ */
