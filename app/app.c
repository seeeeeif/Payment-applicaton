#include "app.h"

ST_cardData_t card;
ST_terminalData_t term;
ST_transaction_t trans;
float maxAmount;
EN_transStat_t transState;
ST_accountsDB_t accref;
extern uint8_t SaveTransState;

void appstart(void)
{

	/*getCardHolderName(&card);
	getCardExpiryDate(&card);
	getCardPAN(&card);
     if (isValidAccount(&card ,(& accref ) != SERVER_OK))
         {
             printf("Rejeceted_STOLEN_CARD. \n");
             return ;
         }

	getTransactionDate(&term);
	if (isCardExpired(&card, &term) != TERMINAL_OK)
    {
        printf("expired card\n");
        return ;
    }

	if(setMaxAmount(&term ,maxAmount) != TERMINAL_OK)
    {
        printf(" accept maximum transaction amount \n");
        return ;
    }

	if(getTransactionAmount(&term) != TERMINAL_OK)
    {
        printf("accept amount\n");
        return ;
    }
       trans.terminalData= term;

   if (isAmountAvailable(& term , & accref) == LOW_BALANCE)
     {
         printf("\n cannot make transaction (balance is low)\n");
           return;
     }

	if(isBelowMaxAmount(&term)!= TERMINAL_OK)
     {
         printf(" you have exceed the maximum transaction amount \n");
         return ;
     }

     if (isBlockedAccount(& accref) == BLOCKED_ACCOUNT)
     {
         printf("\n cannot make transaction \n");
       printf("Rejeceted_STOLEN_CARD. \n");
         return ;
     }

	/*trans.cardHolderData = card; // UPDATE CARD_HOLDER_DATA
	trans.terminalData = term;
	saveTransaction(&trans);

	getTransaction(trans.transactionSequenceNumber, &trans);

	if(recieveTransactionData(&trans.cardHolderData) != SERVER_OK)
    {
        printf(" transaction nor recived\n");
        return ;
    }
    else
    {
        printf("transaction resived\n");
        	SaveTransState++;
    }

	getTransaction(1, &trans);


*/
saveTransactionTest();
}
/*extern void app_start(void)
{
	getCardHolderName(&card);
	getCardExpiryDate(&card);
	getCardPAN(&card);
    isBlockedAccount(& accref);
	getTransactionDate(&term);
	isCardExpired(&card, &term);
	setMaxAmount(&term , maxAmount);
	getTransactionAmount(&term);

	isBelowMaxAmount(&term);

	trans.cardHolderData = card;
	trans.terminalData = term;
	saveTransaction(&trans);

	recieveTransactionData(&trans);

	//getTransaction(1, &trans);

	SaveTransState++;


}*/
