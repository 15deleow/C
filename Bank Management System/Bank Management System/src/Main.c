#include "BankManagementSystem.h"
#include "DatabaseHandler.h"

int main(){
	char pass[10],password[10]="codewithc";
	int i=0;

	createDatabase();

	printf("Enter the password to login:");
	scanf("%s", pass);

	if (strcmp(pass, password) == 0) {
		printf("Password Match!\nLOADING");

		for (i = 0; i <= 6; i++) {
			fordelay(100000000);
			printf(".");
		}

		system("cls");
		menu();
	} else {
        printf("Wrong password!!\a\a\a");
        printf("\nEnter 1 to try again and 0 to exit:");
        scanf("%d", &main_exit);

        if(main_exit == 1)
        	main();
    }

    return 0;
}
