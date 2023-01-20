#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#include	"../card/card.h"
#include	<stdio.h>
#include    <string.h>
#include    <stdlib.h>

typedef unsigned char uint8_t;

typedef struct terminalData
{
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum terminalError
{
	TERMINAL_OK = 1, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t*);
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData ,float maxAmount);

#endif

