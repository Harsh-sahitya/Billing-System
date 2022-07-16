#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct billData{
    char name[20];
    int quantity;
    int unitPrice;
} billData;

typedef struct customerData{
    char name[30];
    char number[12];
    char email[40];
    char date[10];
    int itemType;
} customerData;

void preferredOption(int *choice){
    printf("==========QUINTET Restaurant==========\n");
    printf("\n");
    printf("\nPlease Select Your Preferred Option:\n");
    printf("1. Generate Invoice\n");
    printf("2. Show all Invoices\n");
    printf("3. Search Invoice\n");
    printf("4. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", choice);
    return;
}

// HARSHIT, YOU HAVE TO COMPLETE THIS DESIGN FUNCTION NAMED "invoiceDesign"
// USE customerNo TO GET PARTICULAR CUSTOMER'S DETAILS
void invoiceDesign(billData **bills, customerData *customer, int *total, int customerNo){
    printf("\n=============QUINTET Restaurant=============");
    printf("\n%s",customer[customerNo].date);
    printf("\nInvoice To: %s",customer[customerNo].name);
    printf("\n============================================");
    printf("\nItem\t\tQty\t\t  Total");
    printf("\n============================================");
    for(int i = 0; i < customer[customerNo].itemType; i++){
        printf("\n%s\t\t%d\t\t  %d",bills[customerNo][i].name,bills[customerNo][i].quantity,bills[customerNo][i].quantity * bills[customerNo][i].unitPrice);
    }
    printf("\n============================================");
    printf("\nSub Total\t\t\t  %d",total[customerNo]);
    printf("\nDiscount(@10)\t\t          %f",(float)(total[customerNo]*10/100));
    printf("\n             \t\t          ===========");
    printf("\nNet Total    \t\t          %d",total[customerNo]-total[customerNo]*10/100);
    printf("\nCGST (@2.5%)   \t\t          %f",(float)(total[customerNo]*2.5/100));
    printf("\nSGST (@2.5%)   \t\t          %f",(float)(total[customerNo]*2.5/100));
    printf("\n============================================");
    printf("\nGrand Total  \t\t          %f",(float)(total[customerNo]+total[customerNo]*9/100+total[customerNo]*9/100));
    printf("\n============================================\n");
}

// HARSH, YOU HAVE TO COMPLETE THIS CALCULATION FUNCTION NAMED "calculateBill"
// CALCULATE THE TOTAL WITHOUT GST INCLUDED
void calculateBill(billData **bills, customerData *customer, int *total, int customerNo){
    int totalBill = 0;
    for(int i = 0; i < customer[customerNo].itemType; i++){
        totalBill += bills[customerNo][i].quantity * bills[customerNo][i].unitPrice;
    }
    total[customerNo] = totalBill;
    printf("\nTotal Bill: %d\n", totalBill);
    return;
}

void showAllInvoices(billData **bills, customerData *customers, int *customerNo, int *total){
    for(int i = 0; i < *customerNo; i++){
        invoiceDesign(bills, customers, total, i);
    }
    return;
}

void searchInvoice(billData **bills, customerData *customers, int *customerNo, int *total){
    char searchNumber[30];
    printf("\nEnter the number of the customer: ");
    scanf("%s", searchNumber);
    for(int i = 0; i < *customerNo; i++){
        if(strncmp(searchNumber, customers[i].number, 10)){
            invoiceDesign(bills, customers, total, i);
        }
    }
    return;
}

void invoice(customerData *customer, int *customerNo, int *total, billData **bills){
    strcpy(customer[*customerNo].date, __DATE__);
    lable4:
        gets(customer[*customerNo].name);
        printf("\nEnter Your Name: ");
        // scanf("%s", customer[*customerNo].name);
        gets(customer[*customerNo].name);
        if(strlen(customer[*customerNo].name) == 0){
            printf("\nPlease Enter Your Name\n");
            goto lable4;
        }
    lable2:
        printf("\nEnter Your Phone Number: ");
        // scanf("%s", &customer[*customerNo].number);
        gets(customer[*customerNo].number);
        if(strlen(customer[*customerNo].number) != 10){
            printf("\nInvalid Phone Number\n");
            goto lable2;
        }
    lable3:
        printf("\nEnter Your Email: ");
        // scanf("%s", customer[*customerNo].email);
        gets(customer[*customerNo].email);
        int len = strlen(customer[*customerNo].email);
        // printf("%d", len);
        char test[4] = ".com";
        if(!strcmp(&customer[*customerNo].email[len-4], test)){
            printf("\nInvalid Email\n");
            goto lable3;
        }
    printf("\n");
    printf("\nEnter the number of Different items you have ordered: ");
    scanf("%d", &customer[*customerNo].itemType);
    billData *bill = calloc(customer[*customerNo].itemType, sizeof(billData));
    bills[*customerNo] = bill;
    for(int i = 0; i < customer[*customerNo].itemType; i++){
        printf("\nEnter the name of the item %d: ", i+1);
        gets(bills[*customerNo][i].name);
        gets(bills[*customerNo][i].name);
        printf("Enter the quantity of the item %d: ", i+1);
        scanf("%d", &bill[i].quantity);
        printf("Enter the unit price of the item %d: ", i+1);
        scanf("%d", &bill[i].unitPrice);
    }
    calculateBill(bills, customer, total, *customerNo);
    invoiceDesign(bills, customer, total, *customerNo);
    *customerNo += 1;
    return;
}

void Choice(billData **bills, customerData *customers, int *total, int *customerNo){
    int choice = 0, Continue = 0;
    while(choice > 4 || choice < 1){
        preferredOption(&choice);
    }
    switch(choice){
        case 1:
            invoice(customers, customerNo, total, bills);
            break;
        case 2:
            showAllInvoices(bills, customers, customerNo, total);
            break;
        case 3:
            searchInvoice(bills, customers, customerNo, total);
            break;
        case 4:
            return;
    }
}

int main(){
    int customerNo = 0, Continue = 0;
    customerData *customers = calloc(100, sizeof(customerData));
    // customerArr[customerNo] = *customers;
    int *total = calloc(100, sizeof(int));
    billData **bills = calloc(100, sizeof(billData *));
    lable1:
        Choice(bills, customers, total, &customerNo);
    printf("You want to continue? (1. Yes 2. No) \n");
    scanf("%d", &Continue);
    if(Continue == 1){
        Continue = 0;
        goto lable1;
    }
    else if(Continue == 2){
        Continue = 0;
        printf("\nThank you for using our service.\n");
        return 0;
    }
    else{
        Continue = 0;
        printf("\nInvalid Input.\n");
        goto lable1;;            
    }
    return 0;
}
