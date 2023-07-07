#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    char item[30];
    float qty;
    float rate;
};

struct orders
{
    char custName[50];
    char date[15];
    char time[15];
    char invNo[12];
    int numOfItems;
    char deluxe[3];
    char member[3];
    struct items itm[50];
};

void generateBillHeader(char custName[50], char date[15], char time[15], char invNo[12])
{
    printf("\n\n");
    printf("\t\t\t\t\t     THE TAJ\n");
    printf("\t\t\t\t\t1045, HIGH HILL ROAD\n");
    printf("\t\t\t\t\t BANDRA WEST,400050\n");
    printf("\n\t\t\t\t **********************************\n\n");
    printf("Invoice Number:\t %s\n", invNo);
    printf("Date :\t\t %s\n", date);
    printf("Time :\t\t %s\n", time);
    printf("Invoice To:\t %s\n", custName);
    printf("\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("S.No.\t\t");
    printf("Items\t\t\t\t\t");
    printf("Qty\t\t");
    printf("Rate\t\t");
    printf("Total\t\t\n");
    printf("-----------------------------------------------------------------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], float qty, float rate)
{

    printf("%s\t\t\t\t", item);
    printf("%0.2f\t\t", qty);
    printf("%0.2f\t\t", rate);
    printf("%0.2f\t\t", qty * rate);
    printf("\n");
}

void generateBillFooter(float total, char deluxe[3], char member[3])
{
    printf("\n");
    float discount = 0;
    char yes[3] = "y";
    printf("-----------------------------------------------------------------------------------------------\n");
    if (!strcmp(deluxe, yes))
    {
        total += 600;
        printf("Sub Total(incl Rs.600 for deluxe dining hall)\t\t\t\t\t\t%0.2f\n", total);
    }
    else
    {
        printf("Sub Total\t\t\t\t\t\t\t\t\t\t%0.2f\n", total);
    }
    if (!strcmp(member, "p"))
    {
        discount = (0.5 * total);
        printf("Discount @50%%\t\t\t\t\t\t\t\t\t\t%0.2f\n", discount);
    }
    else if (!strcmp(member, "c"))
    {
        discount = (0.25 * total);
        printf("Discount @25%%\t\t\t\t\t\t\t\t\t\t%0.2f\n", discount);
    }
    else
    {
        printf("Discount @0%%\t\t\t\t\t\t\t\t\t\t%0.2f\n", discount);
    }
    float grossTotal = total - discount;
    float cgst = (0.09) * grossTotal;
    float sgst = (0.09) * grossTotal;
    float amount = grossTotal + cgst + sgst;
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Gross total (excl GST)\t\t\t\t\t\t\t\t\t%0.2f\n", grossTotal);
    printf("CGST @9%%\t\t\t\t\t\t\t\t\t\t%0.2f\n", cgst);
    printf("SGST @9%%\t\t\t\t\t\t\t\t\t\t%0.2f\n", sgst);
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Amount (incl of all taxes)\t\t\t\t\t\t\t\t%0.2f\n", amount);
    printf("-----------------------------------------------------------------------------------------------\n\n");
    printf("                              *****Thanks for your visit*****\n");
}

int main()
{

    int choice;
    struct orders ord;
    struct orders order;
    char saveBill, contFlag = 'y';
    FILE *fptr;

    while (contFlag == 'y' || contFlag == 'Y')
    {
        printf("\t============ THE TAJ ============\n");
        printf("\nPlease select your preferred option:\n");
        printf("1.Generate Invoice\n");
        printf("2.Show all invoices\n");
        printf("3.Search Invoice\n");
        printf("4.Exit\n");

        printf("Your choice:\t");
        scanf("%d", &choice);

        system("cls");
        fgetc(stdin);
        float total = 0;
        int invoiceFound = 0;
        switch (choice)
        {
        case 1:
            printf("\nPlease enter the invoice number:\t");
            fgets(ord.invNo, 12, stdin);
            ord.invNo[strlen(ord.invNo) - 1] = 0;
            fflush(stdin);
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.custName, 50, stdin);
            ord.custName[strlen(ord.custName) - 1] = 0;
            strcpy(ord.date, __DATE__);
            strcpy(ord.time, __TIME__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &ord.numOfItems);
            fflush(stdin);
            printf("\nWhether the customer opted for the deluxe dining hall? (y/n)\t");
            fgets(ord.deluxe, 3, stdin);
            ord.deluxe[strlen(ord.deluxe) - 1] = 0;
            fflush(stdin);
            char member;
            printf("\nIs the customer having a membership of the Taj?");
            printf("\nPlease click 'p' for prime membership, 'c' for classic membership or 'n' otherwise!\t");
            fgets(ord.member, 3, stdin);
            ord.member[strlen(ord.member) - 1] = 0;

            for (int i = 0; i < ord.numOfItems; i++)
            {
                fflush(stdin);
                printf("\n\n");
                printf("Please enter the item %d:\t", i + 1);
                fgets(ord.itm[i].item, 30, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("\nPlease enter the quantity:\t");
                scanf("%f", &ord.itm[i].qty);
                printf("\nPlease enter the rate of the item:\t");
                scanf("%f", &ord.itm[i].rate);
                total += ord.itm[i].qty * ord.itm[i].rate;
            }
            system("cls");
            generateBillHeader(ord.custName, ord.date, ord.time, ord.invNo);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                printf("%d\t\t", i + 1);
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].rate);
            }
            generateBillFooter(total, ord.deluxe, ord.member);
            printf("\nDo you want to save the invoice? (y/n)\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y' || saveBill == 'Y')
            {
                fptr = fopen("sample.txt", "ab+");
                fwrite(&ord, sizeof(ord), 1, fptr);
                if (fwrite != 0)
                {
                    printf("\nSuccessfully saved\n");
                }
                else
                {
                    printf("\nError Saving\n");
                }
                fclose(fptr);
            }
            break;

        case 2:
            fptr = fopen("sample.txt", "rb");
            printf("\n *****Your Previous Invoices*****\n");
            while (fread(&order, sizeof(struct orders), 1, fptr))
            {
                generateBillHeader(order.custName, order.date, order.time, order.invNo);
                float tot = 0;
                for (int i = 0; i < order.numOfItems; i++)
                {
                    printf("%d\t\t", i + 1);
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].rate);
                    tot += order.itm[i].qty * order.itm[i].rate;
                }
                generateBillFooter(tot, order.deluxe, order.member);
            }
            fclose(fptr);
            break;

        case 3:
            printf("\nEnter the name of the customer:\t");
            char *name;
            name = (char *)malloc(50 * sizeof(char));
            gets(name);
            system("cls");
            fptr = fopen("sample.txt", "rb");
            printf("\t*****Invoice of %s*****\n", name);
            while (fread(&order, sizeof(order), 1, fptr))
            {
                float tot = 0;
                if (!strcmp(order.custName, name))
                {
                    generateBillHeader(order.custName, order.date, order.time, order.invNo);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        printf("%d\t\t", i + 1);
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].rate);
                        tot += order.itm[i].qty * order.itm[i].rate;
                    }
                    generateBillFooter(tot, order.deluxe, order.member);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s doesn't exist\n", name);
            }
            fclose(fptr);
            free(name);
            break;

        case 4:
            printf("\n\t\t THANK YOU\n\n\n");
            exit(0);
            break;

        default:
            printf("Sorry invalid option\n");
            break;
        }
        fflush(stdin);
        printf("\nDo you want to perform another operation? (y/n)\n");
        scanf("%c", &contFlag);
    }
    printf("\n\t\t THANK YOU\n\n\n");
    return 0;
}
