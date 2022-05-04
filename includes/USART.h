/*
 * USART.h
 *
 * Created: 26.04.2022 09:26:31
 *  Author: Anders K Felde
 */

#ifndef USART_H_
#define USART_H_

void USART_Init(unsigned int baud);
void USART_Transmit(unsigned int data);
char USART_Receive(void);

#endif /* USART_H_ */
