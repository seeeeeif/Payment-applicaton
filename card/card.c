#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	printf("please insert card holder name\n");
	char name , i=0,len=0;
                      // seif mohamed abdelfatah 23
	for ( i=0 ; i < 25 &&(name = getchar()) != '\n'; i++)
	{
		cardData->cardHolderName[i] = name;

	}
	cardData->cardHolderName[i] ='\0';
	len= strlen(cardData->cardHolderName);

	if (len >19 || len < 25)
	{
		printf("accepted\n");
		return OK;
	}
	 else
	{
		printf("WRONG_NAME\n");
		printf("num of characters = %d   not accepted try again\n", i);
		return WRONG_NAME;
	}
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    printf("Please insert card Expiry Date:\t format (MM/YY)\n");
    char date = 0, i = 0;
    uint8_t date_of_card[6];
    for (i = 0; i < 6 && (date = getchar()) != '\n'; i++)
    {
        date_of_card[i] = date;
    }
    uint8_t  month_arr[3];
    month_arr[0] = date_of_card[0];
    month_arr[1] = date_of_card[1];

    int month = atoi(month_arr);

    if (month > 12)
    {
        printf("month error\n");
        return WRONG_EXP_DATE;
    }

    if (i < 6 && (date_of_card[2] == 47) || (date_of_card[2] == 92))
    {
        int j ;
	     for(j=0;j<6;j++)
         {
            cardData->cardExpirationDate[j] = date_of_card[j];
         }
        printf("accepted\n");
        return OK;
    }
    else
    {
        printf("wrong date\n not accepted try again\n");
        return WRONG_EXP_DATE;
    }

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    printf("Please enter card's Primary Account Number:\n");
    char pan = 0, i = 0;
    for (i = 0; i < 20 && (pan = getchar()) != '\n'; i++)
    {
        if((pan >= '0') && (pan <= '9'))
        {
         cardData->primaryAccountNumber[i] = pan;
        }
        else
        {
           printf("WRONG_PAN\n not accepted try again\n");
           return WRONG_PAN;
        }

    }
    if ((strlen(cardData->primaryAccountNumber) >= 16) && (strlen(cardData->primaryAccountNumber) <= 19))
    {
        printf("accepted\n");
        return OK;
    }
    else
    {
        printf("WRONG_PAN\n not accepted try again\n");
        return WRONG_PAN;
    }
}
