/*
 * com_port.h
 *
 *  Created on: 22-Jun-2026
 *      Author: soham
 */

#include "build_config.h"
#if defined(DEBUG_LOGGING)

#ifndef COM_PORT_H
#define COM_PORT_H

#include "stm32f446xx.h"

void com_port_init();
void com_port_log(char* buffer);
void com_port_transmit(char* buffer);
void com_port_flush();

#define USART_BAUDRATE 115200

#endif

#endif