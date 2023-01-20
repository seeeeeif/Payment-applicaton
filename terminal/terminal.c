#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
        printf("Please Enter The Transaction Date as DD/MM/YYYY : ");
	scanf("%s", termData->transactionDate, 12);
	if (strlen(termData->transactionDate) != 10 || (termData->transactionDate)[2] != '/' || (termData->transactionDate)[5] != '/')
	{
		printf("Wrong TransactionDate. \n");
		return WRONG_DATE;
	}
	return TERMINAL_OK;
}



EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	uint8_t trans_year_val;
	uint8_t card_year_val;
	uint8_t trans_month_val;
	uint8_t card_month_val;
	uint8_t trans_day_val;
	uint8_t trans_year[3];

	trans_year[0] = termData->transactionDate[8];
	trans_year[1] = termData->transactionDate[9];

	uint8_t card_year[3];
	card_year[0] = cardData->cardExpirationDate[3];
	card_year[1] = cardData->cardExpirationDate[4];

	uint8_t trans_month[3];
	trans_month[0] = termData->transactionDate[3];
	trans_month[1] = termData->transactionDate[4];

	uint8_t card_month[3];
	card_month[0] = cardData->cardExpirationDate[0];
	card_month[1] = cardData->cardExpirationDate[1];

	uint8_t trans_day[3];
	trans_day[0] = termData->transactionDate[0];
	trans_day[1] = termData->transactionDate[1];

	trans_year_val = atoi(trans_year);
	card_year_val = atoi(card_year);
	trans_month_val = atoi(trans_month);
	card_month_val = atoi(card_month);
	trans_day_val = atoi(trans_day);

	if (card_year_val > trans_year_val || (card_month_val - trans_month_val) == 0 && (card_month_val - trans_month_val) > 0)
	{
		return TERMINAL_OK;
	}
	else
	{
		printf("\nExpired Card");
		return EXPIRED_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{

    printf("Enter the transaction amount : ");
    scanf("%f", &(termData->transAmount));

    if (termData->transAmount <= 0)
    {
        printf("Invalid Amount of Transaction. \n");
        return INVALID_AMOUNT;
    }
    else
    {
     printf("accepted\n");
     return TERMINAL_OK;
    }

}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData , float maxAmount)
{


    // scanf("%f", &termData->maxTransAmount);
        if (termData->transAmount > termData->maxTransAmount)
    {
        printf("\nCan not make transaction ");
        return INVALID_AMOUNT;
    }
    if ( maxAmount<= 0)
    {
        printf("not accepted try again\n");
        return INVALID_AMOUNT;
    }

    else
    {
        termData->maxTransAmount=maxAmount;
        return TERMINAL_OK;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount > termData->maxTransAmount)
    {
        printf("\nCan not make transaction ");
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
   //  printf("\nYou can make a transaction");
     return TERMINAL_OK;
    }

}
void setMaxAmountTest(void)
{

	ST_terminalData_t termData;


	printf("Tester Name: seif Mohamed \n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 1: -ve number (-100)\n");
	printf("Input Data: -100 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData,1500));
	printf(" \n");
	printf("Tester Name: seif Mohamed \n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 2: zero (0)\n");
	printf("Input Data: 0 \n");
	printf("Expected Result: 6  (INVALID_MAX_AMOUNT) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData,1500));
	printf(" \n");
	printf("Tester Name:seif Mohamed \n");
	printf("Function Name: setMaxAmount\n");
	printf("Test Case 3: +ve number  (2500)\n");
	printf("Input Data: 2300 \n");
	printf("Expected Result: 0  (TERMINAL_OK) \n");
	printf("Actual Result: %d \n", setMaxAmount(&termData,1500));
	printf(" \n");

}
