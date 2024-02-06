#include <BankManagementSystem.h>
#include <DatabaseHandler.h>

#define DELAY 1000000000
#define MAX_ADDRESS_LENGTH 60

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void writeCustomer(struct Customer *customer) {
	char query[500];
	char dateStr[11];

	//Generate SQL Statement using provided data
	sprintf(dateStr, "%d/%d/%d", customer->deposit.month, customer->deposit.day, customer->deposit.year);
	printf("%s\n", dateStr);

    sprintf(query, "INSERT INTO RECORDS (NAME,ACCOUNT,AGE,ADDRESS,CITIZENSHIP,ACC_TYPE,PHONE,AMOUNT,DOB,DATE) VALUES ("
    		"'%s', %d, %d, '%s', '%s', '%s', '%s', %.0lf, '%s', '%s');",
            customer->name,
    		customer->acc_no,
			customer->age,
			customer->address,
            customer->citizenship,
			customer->acc_type,
			customer->phone,
			customer->amt,
			customer->dob,
			dateStr
			);

    printf("%s\n", dateStr);

    //Call method to add entry into database
    addAccount(query);

    return;
}

float interest(float t, float amount, int rate)
{
    float SI;
    SI = (rate * t * amount) / 100;
    return SI;
}

void fordelay(int j)
{
    for (int i = 0; i < j; i++){}
}

void clearStdinBuffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Keep reading characters until a newline or EOF is encountered
    }
}

void getAccountInfo(struct Customer *customer){
    clearStdinBuffer();

    //Ask for Full name
    printf("\nEnter account holder's name:");
    scanf("%[^\n]", customer->name);

    //Get Date of Birth
	printf("\nEnter the date of birth(mm/dd/yyyy):");
	scanf("%s",customer->dob);

	//Get age
	printf("\nEnter the age:");
	scanf("%d",&customer->age);

	//Get home address
	clearStdinBuffer();
	printf("\nEnter the address:");
	scanf("%[^\n]", customer->address);

	//Get Citizenship number
	printf("\nEnter the citizenship number:");
	scanf("%15s", customer->citizenship);

	//Get Phone number
	printf("\nEnter the phone number: ");
	scanf("%s",customer->phone);

	//Get amount to deposit
	printf("\nEnter the amount to deposit:$");
	scanf("%f",&customer->amt);

	//Ask user what account type the want
	printf("\nType of account:\n\t#Saving\n\t#Current\n\t#Fixed1(for 1 year)\n\t#Fixed2(for 2 years)\n\t#Fixed3(for 3 years)\n\n\tEnter your choice:");
	scanf("%11s", customer->acc_type);
}

void new_acc()
{
    // Get today's date
    clearScreen();
    printf("\t\t\t\xB2\xB2\xB2\040ADD\040RECORD\040\xB2\xB2\xB2\xB2\n\n\n");
    printf("Enter today's date (mm/dd/yyyy):");
    scanf("%d/%d/%d", &check.deposit.day, &check.deposit.month, &check.deposit.year);

    account_no:
    // Prompt user for an account number
    printf("\nEnter the account number:");
    scanf("%d", &check.acc_no);

    // Checks if the entered account number already exists
    if( entryExists(check.acc_no) > 0 )
	{
		printf("Account number already in use!");
		fordelay(DELAY);
		clearScreen();
		goto account_no;
    }

    // Unique account number, gather additional details
    getAccountInfo(&check);

    // Append information to the file
	writeCustomer(&check);

    //Notify success
    printf("\nAccount created successfully!");

    add_invalid:
    //prompt for next action
    printf("\n\n\nEnter 1 to go to the main menu and 0 to exit: ");
    scanf("%d", &main_exit);
    clearScreen();

    switch(main_exit){
        case 1:
            menu();
            break;
        case 0:
            close();
            break;
        default:
            printf("\nInvalid!\a");
            goto add_invalid;
    }
}

void view_list() {
    int test = 0;

    clearScreen();
    printf("\nACC. NO.\tNAME\t\t\tADDRESS\t\t\t\tPHONE\n");

    // Checks if the entered account number already exists
    test = displayAllAccounts();

    if (test == 0) {
        clearScreen();
        printf("\nNO RECORDS!!\n");
    }

    int choice;
    do {
        printf("\n\nEnter 1 to go to the main menu and 0 to exit: ");
        scanf("%d", &choice);
        clearScreen();

        switch (choice) {
            case 1:
                menu();
                break;
            case 0:
                close();
                break;
            default:
                printf("\nInvalid choice!\a");
        }
    } while (choice != 0);
}

void edit(void){
    int recordFound = 0;
    int userChoice = 0;

    //Prompt user for account number
    printf("\nEnter the account no. of the customer whose info you want to change:");
    scanf("%d",&upd.acc_no);

    //Lookup the account
    if(entryExists(upd.acc_no) > 0){
    	recordFound = 1;
		printf("\nWhich information do you want to change?\n1.Phone\n2.Address\n\nEnter your choice(1 for address and 2 for phone):");
		scanf("%d",&userChoice);
		clearScreen();

		switch(userChoice){
			case ADDRESS:
				//Prompt user for new address
				clearStdinBuffer();
				printf("Enter the new address: ");
				scanf("%[^\n]", upd.address);
				//Write updated account to the new file
				if(updateAccount(ADDRESS, upd.address, upd.acc_no) == false){
					return;
				}
				clearScreen();
				printf("Changes Saved!");
				break;
			case PHONE:
				//Prompt user for new phone number
				printf("Enter the new phone number: ");
				scanf("%s", upd.phone);
				//Write updated account to the new file
				if(updateAccount(PHONE, upd.phone, upd.acc_no) == false){
					return;
				}
				clearScreen();
				printf("Changes Saved!");
				break;
		}
    }

    if(recordFound != 1){
    	clearScreen();
        printf("\nRecord not found!!\a\a\a");

        do{
            printf("\nEnter 0 to try again, 1 to return to the main menu, and 2 to exit: ");
            scanf("%d", &userChoice);
            printf("%d\n", userChoice);
            clearScreen();

            switch(userChoice){
                case 0:
                    edit();
                    break;
                case 1:
                    menu();
                    break;
                case 2:
                    close();
                    break;
                default:
                    printf("\nInvalid choice!\a");
            }
        } while(userChoice != 1 && userChoice != 2 && userChoice != 0);
    }else{
        printf("\n\n\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        clearScreen();

        switch(userChoice){
            case 1:
                menu();
                break;
            default:
                close();
                break;
        }
    }

}

void transact(void){
	int userChoice;
    int recordFound = 0;

    //Prompt user for account number
    printf("Enter the account no. of the customer: ");
    scanf("%d", &transaction.acc_no);

    //Search record.dat file for requested account number
    if(entryExists(transaction.acc_no) > 0){
    	getData(&add, transaction.acc_no);
    	recordFound = 1;

    	if(add.acc_type[5] == '1' || add.acc_type[5] == '2' || add.acc_type[5] == '3'){
			printf("\a\a\a\n\nYOU CANNOT DEPOSIT OR WITHDRAW CASH IN FIXED ACCOUNTS!!!!!");
			fordelay(DELAY);
			clearScreen();
    	}

    	printf("\n\nDo you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
		scanf("%d",&userChoice);

		if(userChoice == 1){
			printf("Enter the amount you want to deposit:$ ");
			scanf("%f",&transaction.amt);

			add.amt+=transaction.amt;
			printf("\n\nDeposited successfully!");

		}else{
			printf("Enter the amount you want to withdraw:$ ");
			scanf("%f",&transaction.amt);

			add.amt-=transaction.amt;
			printf("\n\nWithdrawn successfully!");
		}

		char newAmount[100];
		sprintf(newAmount, "%f", add.amt);
		updateAccount(TRANSACTION, newAmount, add.acc_no);
    }

    if(recordFound != 1){
    	printf("\n\nRecord not found!!");
		transact_invalid:
		printf("\n\n\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
		scanf("%d",&main_exit);
		clearScreen();

		switch(main_exit){
		case 0:
			transact();
			break;
		case 1:
			menu();
			break;
		case 2:
			close();
			break;
		default:
			printf("\nInvalid!");
			goto transact_invalid;
		}
    }else{
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d",&main_exit);
        clearScreen();
        if (main_exit==1)
        	menu();
        else
        	close();
    }
}

void erase(void){
    int recordFound = 0;

    printf("Enter the account number of the customer you want to delete: ");
    scanf("%d", &rem.acc_no);

	//Search records for account number entered by user
    if(entryExists(rem.acc_no) > 0){
    	//Account exists, proceed to delete
		recordFound++;
		deleteAccount(rem.acc_no);
		printf("\nRecord deleted successfully!\n");
    }

    //Base on if a record was deleted or not, prompt user for next instruction
    if(recordFound == 0){
    	printf("\nRecord not found!!\a\a\a");
		erase_invalid:
		printf("\nEnter 0 to try again,1 to return to main menu and 2 to exit:");
		scanf("%d",&main_exit);

		switch(main_exit){
		case 0:
			erase();
			break;
		case 1:
			menu();
			break;
		case 2:
			close();
			break;
		default:
			printf("\nInvalid!\a");
			goto erase_invalid;
		}
    }else{
    	printf("\nEnter 1 to go to the main menu and 0 to exit: ");
    	scanf("%d", &main_exit);
    	clearScreen();

    	if(main_exit == 1){
    		menu();
    	}else{
    		close();
    	}
    }
}

void see(void){
	int recordFound = 0;
	int userChoice;
	int rate;
	float time;
	float intrst;

	//Prompt user for a name or account number
	prompt_user:
	printf("Do you want to check by \n\t1. Account number\n\t2. Name\nEnter Choice: ");
	scanf("%d", &userChoice);

	//Search records for the given name or account number
	if(userChoice == 1){
		printf("Enter the account number: ");
		scanf("%d", &check.acc_no);

		//Search for the requested account number in the record
		if(entryExists(check.acc_no) > 0){
			getData(&check, check.acc_no);
			clearScreen();
			recordFound = 1;

			if(displayAccount(check.acc_no) != SQLITE_OK){
				perror("Failed to display account data!");
				return;
			}

			//Based on Account type, calculate time, rate, and interest
			if(strcmp(check.acc_type, "Fixed1") == 0){
				time = 1.0;
				rate = 9;
				intrst = interest(time, check.amt, rate);
				printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
			}else if(strcmp(check.acc_type, "Fixed2") == 0){
				time= 2.0;
				rate= 11;
				intrst= interest(time,check.amt,rate);
				printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+2);
			}else if(strcmp(add.acc_type, "Fixed3") == 0){
				time = 3.0;
				rate = 13;
				intrst = interest(time, check.amt, rate);
				printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
			}else if(strcmp(check.acc_type, "saving") == 0){
				time = (1.0 / 12.0);
				rate = 8;
				intrst = interest(time, check.amt, rate);
				printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
			}else if(strcmp(check.acc_type, "current") == 0){
				printf("\n\nYou will get no interest\a\a");
			}
		}
	}else if(userChoice == 2){
		clearStdinBuffer();
		printf("Enter the name: ");
		scanf("%[^\n]", check.name);
		if(nameEntryExists(check.name)){
			recordFound = 1;
			clearScreen();
			displayAccountByName(check.name);
			getData(&check, check.acc_no);
		}

		//Based on Account type, calculate time, rate, and interest
		if(strcmp(check.acc_type, "Fixed1") == 0){
			time = 1.0;
			rate = 9;
			intrst = interest(time, add.amt, rate);
			printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
		}else if(strcmp(check.acc_type, "Fixed2") == 0){
			time= 2.0;
			rate= 11;
			intrst= interest(time,check.amt,rate);
			printf("\n\nYou will get $.%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+2);
		}else if(strcmp(check.acc_type, "Fixed3") == 0){
			time = 3.0;
			rate = 13;
			intrst = interest(time, check.amt, rate);
			printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
		}else if(strcmp(check.acc_type, "saving") == 0){
			time = (1.0 / 12.0);
			rate = 8;
			intrst = interest(time, check.amt, rate);
			printf("\n\nYou will get $%.2f as interest on %d/%d/%d",intrst,check.deposit.month,check.deposit.day,check.deposit.year+1);
		}else if(strcmp(check.acc_type, "current") == 0){
			printf("\n\nYou will get no interest\a\a");
		}
	}else{
		printf("Invalid Input\n");
		goto prompt_user;
	}

	//Prompt user for next instructions
	if(recordFound != 1){
		clearScreen();
		printf("\nRecord not found!!\a\a\a");
		see_invalid:
			printf("\nEnter 0 to try again, 1 to return to main menu, and 2 to exit: ");
			scanf("%d", &userChoice);
			clearScreen();
			switch(userChoice){
			case 0:
				see();
				break;
			case 1:
				menu();
				break;
			case 2:
				close();
				break;
			default:
				printf("\nInvalid Input!\a");
				goto see_invalid;
			}
	}else{
		see_invalidTwo:
			printf("\Enter 1 to return to main menu, and 2 to exit: ");
			scanf("%d", &userChoice);
			clearScreen();
			switch(userChoice){
			case 1:
				menu();
				break;
			case 2:
				close();
				break;
			default:
				printf("\nInvalid Input!\a");
				goto see_invalidTwo;
			}
	}
}

void close(void){
	printf("\n\n\n\nThis C Mini Project is developed by Code With C team and Modified by William Deleon!!");
}

void menu(void){
	int userChoice;

	//Display the main menu
	clearScreen();
	system("color 9");
	printf("\n\n\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t1.Create new account\n\t\t2.Update information of existing account\n\t\t3.For transactions\n\t\t4.Check the details of existing account\n\t\t5.Removing existing account\n\t\t6.View customer's list\n\t\t7.Exit\n\n\t\t Enter your choice:");
	scanf("%d",&userChoice);
    clearScreen();

    //Execute the users selection
    switch(userChoice)
    {
        case 1:new_acc();
        break;
        case 2:edit();
        break;
        case 3:transact();
        break;
        case 4:see();
        break;
        case 5:erase();
        break;
        case 6:view_list();
        break;
        case 7:close();
        break;
        default:
        	printf("\nInvalid Input!\a");
        	menu();
        	break;
    }
}
