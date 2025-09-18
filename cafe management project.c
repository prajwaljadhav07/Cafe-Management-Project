#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void admin();
void customer();

void addmenuitem();
void removemenuitem();
void displaymenu();
void viewfeedback();
void checkexpense();


void viewmenu();
void placeorder();
void canclemenu();
void viewbill();


struct menuitem {
    float price;
    char name[100];
    int id;
    struct menuitem *next;
};

// struct for order process in customer 
struct order{
	int id ; 
	char name[100];
	float price;
	struct order *next;
};
struct order *orderhead = NULL;

struct menuitem *head = NULL;
int current_id = 1; 
FILE *fptr;
FILE *feed;
FILE *exp;

int main()
{
	printf("|| WELCOME TO CAFE ||\n");
	printf("\n");
while(1)
{
	int module;
	printf("Enter 1 for Admin\n");
	printf("Enter 2 for Customer\n");
	printf("Enter 3 for Exit\n");
	
	scanf("%d",&module);

if(module==1)
{
	admin();
}	

else if(module==2)
{
	customer();
}

else if (module==3){
	exit(0);
}
else{
	printf("invalid chioce\n");
}

}

	return 0;
}

//Admin module starts
void admin(){
	int pass;
	printf("Enter the password (int only) : ");
	scanf("%d",&pass);
	
	if (pass==12345){
		while(1) {
        int choice;
        printf("\nEnter your choice:\n");
        printf("1 - Add menu item\n");
        printf("2 - Remove menu item\n");
        printf("3 - Display menu items\n");
        printf("4 - Display feedback\n");
        printf("5 - Check expense\n");
        printf("6 - Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addmenuitem();
                break;
            case 2:
                removemenuitem();
                break;
            case 3:
                displaymenu();
                break;
            case 4:
                viewfeedback();
                break;
            case 5:
            	checkexpense();
            	break;
            case 6:
            	printf("Exiting program");
                return ;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    
	}
	else{
		printf("Wrong pass Pls try again !\n");
		return ;
	}
	 
}//void admin end

//Add menu Function
void addmenuitem() {
    struct menuitem *new_item = (struct menuitem *)malloc(sizeof(struct menuitem));
    if (new_item == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter the name of the item: ");
    scanf("%s", new_item->name);
	
	printf("Enter the price of the item: ");
    scanf("%f", &new_item->price);

    new_item->id = current_id++;
    new_item->next = NULL;

    
    if (head == NULL) {
        head = new_item;
    } else {
        struct menuitem *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_item;
    }

    printf("Item added successfully with ID %d.\n", new_item->id);
    
    fptr=fopen("Menu.txt","a");
    if (fptr==NULL){
    	printf("Menu is not available pls wait .... \n");
    	return ;
	}
	fprintf(fptr,"%d  %s  %.2f \n",new_item->id,new_item->name,new_item->price);
	fclose(fptr);
    
}

//remove menu function
void removemenuitem() {
    int removeid;
    printf("Enter id to remove item : ");
    scanf("%d",&removeid);
    
    FILE *tempfile=fopen("Temp.txt","w");
    fptr=fopen("Menu.txt","r");
    
    if (fptr==NULL || tempfile==NULL){
    	printf("Error opening in file \n");
    	return ;
	}
	
	int id; 
	char name[100];
	float price;
	int found=0;
	
	while (fscanf(fptr,"%d %s %f",&id ,name , &price)==3){
	if (id == removeid){
		found=1;
	}
	else{
		fprintf(tempfile,"%d %s %.2f\n",id , name , price);
	}
		
}
	
	fclose (fptr);
	fclose (tempfile);
	
	remove("Menu.txt");
	rename("Temp.txt","Menu.txt");
	if (found){
		printf("Item removed successfully!\n");
	}
        
    else{
    	printf("Item with ID not found.\n");
	}
        
}


//Display menu function
void displaymenu() {
    
    fptr = fopen("Menu.txt", "r");
    if (fptr == NULL) {
        printf("Menu is empty.\n");
        return;
    }

    int id;
    char name[100];
    float price;

    printf("\n       MENU CARD\n");
    printf("_____________________________\n");
    printf("ID\tItem Name\tPrice\n");
    printf("_____________________________\n");

    while (fscanf(fptr, "%d %s %f", &id, name, &price) == 3) {
        printf("%d\t%s\t\t%.2f Rs\n", id, name, price);
    }

    printf("_____________________________\n");
    fclose(fptr);


}

//view feedback function
void viewfeedback()
{
	char feedback[100];
    long long int mobile;
    char pname[50];
    
	feed=fopen("Feedback.txt","r");
	if (feed == NULL) 
	{
        printf("No Feedback available.\n");
        return;
    }
	
    while (fscanf(feed, "%s\n  %lld\n  %99[^\n]", pname, &mobile , feedback) == 3) 
	{
        printf("%s\n  %lld\n  %s\n", pname, mobile, feedback);
    }
	printf("\n");
	fclose(feed);
}
void checkexpense(){
	
	char name[100];
	exp=fopen("Expense.txt","r");
	if (exp==NULL){
		printf("Not available \n");
		return;	
	}
	printf("The Expenses are : \n");
	while (fscanf(exp,"%s ",name)==1){
		printf("%s\n",name);
	}
	
	fclose(exp);
}

//customer functions starts
void customer()
{

	while(1) {
        int choice1;
        printf("\nEnter your choice from below\n");
        printf("1 - View menu \n");
        printf("2 - place order \n");
        printf("3 - remove Order\n");
        printf("4 - View bill\n");
        printf("5 - feedback\n");
        printf("6 - Exit\n");
        printf("Choice: ");
        scanf("%d", &choice1);

        switch(choice1) {
            case 1:
                viewmenu();
                break;
            case 2:
                placeorder();
                break;
            case 3:
                canclemenu();
                break;
            case 4:
            	viewbill();
            	break;
            case 5:
            	feedback();
            	break;
            case 6:
            	printf("Exiting program \n Thanks ! Visit again...\n");
                return ;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
    
}//customer end 

//view menu functions
void viewmenu() {
    fptr = fopen("Menu.txt", "r");
    if (fptr == NULL) {
        printf("Menu not available, SORRY\n");
        return;
    }
    int id;
    char name[100];
    float price;

    printf("\n       MENU CARD\n");
    printf("================================\n");
    printf("ID\tItem Name\tPrice\n");
    printf("================================\n");


    while (fscanf(fptr, "%d %s %f", &id, name, &price) == 3) {
        printf("%d\t%-10s\t%.2f Rs\n", id, name, price);
    }

    printf("================================\n");
    fclose(fptr);
}


//view place order function
void placeorder()
{
	int id ; 
	char name[100];
	float price ;
	int orderid;
	int found=0;
	
	printf("Enter the id to order menu : \n");
	scanf("%d",&orderid);
	
	fptr = fopen("Menu.txt","r");
	if (fptr==NULL){
		printf("NO Menu available \n");
		return ;
	}
	
	while (fscanf(fptr, "%d %s %f", &id, name, &price) == 3) {
        if (orderid == id ){
        	printf("Id : %d \t Name : %s \t Price : %.2f \n",id , name , price);
			printf("Item added succesfully !");   
			
			struct order *neworder = (struct order*)malloc(sizeof(struct order));
			neworder->id=id ;
			strcpy(neworder->name,name);
			neworder->price=price;
			neworder->next=NULL;
				
			if (orderhead==NULL){
				orderhead = neworder;
			}	
			else{
				struct order *temp=orderhead;
				while (temp->next !=NULL){
					temp=temp->next;
				}
				temp->next=neworder;
			}
		
			found =1;
			break; 
		}
    }
    if (!found){
    	printf("Menu not available !");
	}
fclose(fptr);
}

//view cancel menu
void canclemenu()
{
	if (orderhead==NULL){
		printf("No orders made ! \n");
		return ;
	}
	int cancel;
	printf("Enter the item id to cancel your order : \n");
	scanf("%d",&cancel);
	
	struct order*temp=orderhead;
	struct order*prev=NULL;
	
	while (temp!=NULL && temp->id != cancel){
		prev=temp;
		temp=temp->next;
	}
	
	if (temp==NULL){
		printf("Your order not found !\n");
		return;
	}
	if (prev==NULL){
		orderhead=temp->next;
	}
	else {
		prev->next=temp->next;
	}
	
	printf("Your order removed succesfully !\n");
	free(temp);
}
void viewbill(){
	char name[100];
	if (orderhead==NULL){
		printf("No order placed ! \n");
		return ;
	}
	struct order *temp=orderhead;
	float total =0;
	
    printf("\n         BILL\n");
    printf("================================\n");
    printf("ID\tItem Name\tPrice\n");
    printf("================================\n");
    
     exp=fopen("Expense.txt","a");
    if (exp==NULL){
    	printf("Not available \n");
    	return ;
	}
	
    
    while (temp!=NULL){
    	printf(" %d \t  %s \t  %.2f \n",temp->id , temp->name , temp->price);
    	total=total+temp->price;
    	fprintf(exp," %s\n",temp->name);
    	temp=temp->next;
	}
	
    printf("Total amount to pay : %.2f\n",total);
	fclose(exp);
}
void feedback(){
    char feedback[100];
    long long int mobile;
    char pname[50];
    printf("Enter your name: ");
    scanf("%s",pname);
    printf("Enter your mobile number: ");
    scanf("%lld",&mobile);
    printf("Please enter your valuable feedback:\n");
    scanf(" %99[^\n]", feedback);
	getchar();
	feed=fopen("Feedback.txt","a");
	 if (feed==NULL){
    	printf("Menu is not available pls wait .... \n");
    	return ;
	}
	fprintf(feed, "%s\n%lld\n%s\n", pname, mobile, feedback);

    printf("Thank You For Your Valuable Responce!!!...");
    fclose(feed);
}

