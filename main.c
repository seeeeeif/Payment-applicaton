
#include <stdlib.h>
#include <stdio.h>
#include "../payment_application/app/app.h"

int main(void)
{
	static char choice[1] = "1";
	printf("1: New Transaction\n");
	printf("2: Show previous Transactions\n");
	printf("3: Exit\n");
	while (1)
	{
		printf("choice: ");
		gets(choice);
		switch (choice[0])
		{
		case '1':
			appstart();
			break;
		case '2':
			listSavedTransactions();
			break;
		case '3':
			printf("ByeBye\n");
			break;
		}
	}

}
