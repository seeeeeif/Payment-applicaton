#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
typedef unsigned char uint8_t;
typedef struct card_data
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

typedef enum cardeError
{
	OK , WRONG_NAME , WRONG_EXP_DATE , WRONG_PAN
}  EN_cardError_t;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


#endif
