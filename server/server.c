#include "server.h"

static ST_accountsDB_t accountsDB[255] =
{
	{23450.0, RUNNING, "5365227418449952"},
	{10000.0, RUNNING, "6216421762123284"},
	{5000.0, BLOCKED, "5494031536443382"},
	{2010.0, RUNNING, "2946376193279905"},
	{254.0, RUNNING, "6964690405822411"},
	{120.0, RUNNING, "1388393921568886"},
	{29852.0, BLOCKED, "2010377165328481"},
	{98745.0, RUNNING, "9737628650154429"},
	{140.0, RUNNING, "4031373251867921"},
	{845.0, RUNNING, "5027705752873721"},
	{450.0, RUNNING, "5506659692130454"},
	{87451.0, BLOCKED, "8625948822271191"},
	{564.0, RUNNING, "9768698847407065"},
	{35130.5, BLOCKED, "1532424181474690"},
	{212.4, RUNNING, "7270910662920824"},
	{935130.9, RUNNING, "2958468509546062"},
	{654130.2, RUNNING, "9116722165124844"},
	{17132.5, RUNNING, "7857467935523357"},
	{23459478.0, BLOCKED, "8348419678890647"},
};
ST_transaction_t transactionsDB[255] = { 0 };

uint8_t SaveTransState;
uint8_t temp = 0;
uint8_t sequqnce = 0;
EN_transStat_t recieveTransactionData(ST_transaction_t* transData) {
	EN_transStat_t ret = APPROVED;
	if (isValidAccount(&transData->cardHolderData, accountsDB) == ACCOUNT_NOT_FOUND) {
		transData->transState = FRAUD_CARD;
		printf("FRAUD_CARD. \n");
		ret = FRAUD_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData, accountsDB) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		printf("DECLINED_INSUFFECIENT_FUND. \n");
		ret = DECLINED_INSUFFECIENT_FUND;
	}
	else if (isBlockedAccount(&accountsDB[temp]) == DECLINED_STOLEN_CARD) {
		transData->transState = DECLINED_STOLEN_CARD;
		printf("DECLINED_STOLEN_CARD. \n");
		ret = DECLINED_STOLEN_CARD;
	}
	else if (saveTransaction(transData) == SAVING_FAILED) {
		printf("INTERNAL_SERVER_ERROR. \n");
		ret = INTERNAL_SERVER_ERROR;
	}
	else {
		printf("\nDone recieveTransactionData Successfully\n");
		transData->transState = APPROVED;
		accountsDB[temp].balance = accountsDB[temp].balance - transData->terminalData.transAmount;
		printf("your balance now is %.2f\n", accountsDB[temp].balance);
	}
	return 0;
}
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	uint32_t i = 0, flag = 0;
	for (i = 0; i < 255; i++)
	{
		if (strcmp((cardData->primaryAccountNumber), (accountsDB[i].primaryAccountNumber)) == 0)
		{
			flag = 1;
			temp = i;
			break;
		}
	}
	if (flag == 0)
	{
		printf("DECLINED_STOLEN_CARD. \n");
		return ACCOUNT_NOT_FOUND;
	}
	else
	{
		return OK;
	}
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	if (accountsDB[temp].state == BLOCKED) {
	//	printf("\nBlocked Account");
		return BLOCKED_ACCOUNT;
	}
	return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{

	if (termData->transAmount > accountsDB[temp].balance)
	{
		printf("\n cannot make transaction (balance is low)");
		return LOW_BALANCE;
	}
	return	TERMINAL_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	uint8_t i = sequqnce;
	if (i >= 1) {
		printf("\nFailed Saving");
		return SAVING_FAILED;
	}

	transData->transactionSequenceNumber = sequqnce ;
	transactionsDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
	transactionsDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
	transactionsDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
	transactionsDB[transData->transactionSequenceNumber].transState = transData->transState;
	sequqnce++;
	printf("\nSaving Success");
	return SERVER_OK;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
  	EN_serverError_t save = OK;
	if (transactionsDB[transactionSequenceNumber].transactionSequenceNumber == 0) {
		//printf("Transaction not Found.\n");
		save = TRANSACTION_NOT_FOUND;
	}
	else {
		printf("Card HolderName: %s\n", transactionsDB[transactionSequenceNumber].cardHolderData.cardHolderName);
		printf("=================================\n");
		printf("PrimaryAccountNumber: %s\n", transactionsDB[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
		printf("=================================\n");
		printf("CardExpiration Date : %s\n", transactionsDB[transactionSequenceNumber].cardHolderData.cardExpirationDate);
		printf("=================================\n");
		printf("Transaction Date : %s\n", transactionsDB[transactionSequenceNumber].terminalData.transactionDate);
		printf("=================================\n");
		printf("Transaction Amount: %.2f\n", transactionsDB[transactionSequenceNumber].terminalData.transAmount);
		printf("=================================\n");
		printf("Transaction Sequence number: %d\n", transactionsDB[transactionSequenceNumber].transactionSequenceNumber);
		printf("=================================\n");
	}
	return save;
}
void listSavedTransactions(void) {
	uint8_t i;
	if (sequqnce == 1) {
		printf("There are no saved transactions\n");
		printf("\n");
		return 0;
	}
	for (i = 0; i < SaveTransState; i++) {
		printf("Transaction Sequence Number: %d  \n", transactionsDB[i].transactionSequenceNumber);
			printf("=================================\n");
		printf("Transaction Date: ");
		puts(transactionsDB[i].terminalData.transactionDate);
			printf("=================================\n");
		printf("Transaction Amount: %f\n", transactionsDB[i].terminalData.transAmount);
	printf("=================================\n");
		switch (SaveTransState) {
		case 0:
			printf("Transaction State: Approved\n");
			break;
		case 1:
		//	printf("Transaction State: DECLINED_INSUFFECIENT_FUND\n");
			break;
		case 2:
			//printf("Transaction State: DECLINED_STOLEN_CARD\n");
			break;
		case 3:
			//printf("Transaction State:FRAUD_CARD\n");
			break;
		case 4:
			//printf("Transaction State:INTERNAL_SERVER_ERROR\n");
			break;
		}
		printf("Terminal Max Amount: %f\n", transactionsDB[i].terminalData.maxTransAmount);
			printf("=================================\n");
		printf("Card-holder Name:");
		puts(transactionsDB[i].cardHolderData.cardHolderName);
			printf("=================================\n");
		printf("PAN:  ");
		puts(transactionsDB[i].cardHolderData.primaryAccountNumber);
	printf("=================================\n");
		printf("Card Expiration Data:");
		puts(transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("\n");

	}
}
void isValidAccountTest(void)
{
	ST_cardData_t cardData;
	ST_accountsDB_t* accountRefrence;
	printf("Tester Name:seif  Mohamad \n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 1:account not found (WRONG PAN)\n");
	cardData = (ST_cardData_t){ .cardHolderName = "seif Mohamed ",.primaryAccountNumber = "1236541265474145",.cardExpirationDate = "11/26" };
	printf("Input Data: cardHolderName=seif Mohamed ,primaryAccountNumber=1236541265474145,cardExpirationDate=11/26\n");
	printf("Expected Result: 3  (ACCOUNT_NOT_FOUND) \n");
	printf("Actual Result: %d \n", isValidAccount(&cardData, &accountRefrence));
	printf("\n");

	printf("Tester Name: seif Mohamed \n");
	printf("Function Name: isValidAccount\n");
	printf("Test Case 2:account found (Correct PAN)\n");
	cardData = (ST_cardData_t){ .cardHolderName = "seif Mohamed ",.primaryAccountNumber = "6964690405822411",.cardExpirationDate = "10/26" };
	printf("Input Data: cardHolderName= seif Mohamed ,primaryAccountNumber=6964690405822411,cardExpirationDate=10/26\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", isValidAccount(&cardData, &accountRefrence));
}
void saveTransactionTest(void)
{
	ST_transaction_t transData;
	ST_terminalData_t* termData ;
	 float maxAmount;
	ST_cardData_t cardData;
    getCardHolderName( &cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    setMaxAmount(& termData , 1500);
    getTransactionAmount(&termData);
    getTransactionDate(&termData);
	printf("Tester Name: seif Mohamad \n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 1: saving ok state APPROVED \n");
	/*transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "seif Mohamad",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = APPROVED
	};*/
	//printf("Input Data: .cardHolderData = {.cardHolderName = seif Mohamad,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = APPROVED);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("\n");

    getCardHolderName( &cardData);
    getCardExpiryDate(&cardData);
    getCardPAN(&cardData);
    setMaxAmount(& termData , 1500);
    getTransactionAmount(&termData);
    getTransactionDate(&termData);
	printf("Tester Name: seif Mohamad \n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 2: Failed Saving\n");
    printf("Expected Result: 1  (Failed Saving) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	//printf("Test Case 2: saving ok state DECLINED_INSUFFECIENT_FUND \n");
	/*transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "seif Mohamad",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = DECLINED_INSUFFECIENT_FUND
	};*/
	/*printf("Input Data: .cardHolderData = {.cardHolderName = seif Mohamad,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = DECLINED_INSUFFECIENT_FUND);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	printf("\n");

	printf("Tester Name: seif Mohamad \n");
	printf("Function Name: saveTransaction\n");
	printf("Test Case 3: saving ok state FRAUD_CARD \n");
	transData = (ST_transaction_t)
	{ .cardHolderData = {.cardHolderName = "seif Mohamad",.cardExpirationDate = "10/27",.primaryAccountNumber = "9737628650154429"}
	 ,.terminalData = {.maxTransAmount = 1500,.transactionDate = "30/9/2022",.transAmount = 150}
	 ,.transState = FRAUD_CARD
	};
	printf("Input Data: .cardHolderData = {.cardHolderName = seif Mohamad,.cardExpirationDate = 10 / 27,.primaryAccountNumber = 9737628650154429}\nterminalData = { maxTransAmount = 1500transactionDate = 30/9/2022transAmount = 150 }\ntransactionSequenceNumber = 0, .transState = FRAUD_CARD);\n");
	printf("Expected Result: 0  (SERVER_OK) \n");
	printf("Actual Result: %d \n", saveTransaction(&transData));
	*/
}
