/*
 * clock.h
 *
 *  Created on: Jan 30, 2025
 *      Author: akila
 */

#ifndef INCLUDE_CLOCKS_H_
#define INCLUDE_CLOCKS_H_

// MACROS========================================================================
#define MCLK_FREQ_MHZ           (8) // MCLK = 8MHz
#define CLEAR_REGISTER     (0X0000)

void Init_Clocks(void);
void Software_Trim(void);



#endif /* INCLUDE_CLOCKS_H_ */
