///*
// * Tanner Brown
// * TCSS 333 - Assignment 5
// * Winter - 2018
// */
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <ctype.h>
//
///************* Defines *********/
////#define INPUTFILENAME "hw5input.txt"
//#define NAME_LEN 29
//#define MAX_PURCHASES 10
//
///************** Structs *************/
////Contains product name, quantity purchased, item price and order total price
//struct store_purchase_tag {
//    char product[NAME_LEN];
//    int qty; //
//    double itemPrice;
//    double orderPrice; //This stores the itemprice * qty.
//};
//typedef struct store_purchase_tag Order;
//
////Contains a name, total order and array of orders
//struct customer_tag {
//    char name[NAME_LEN]; //
//    double orderTotal;
//    Order orders[MAX_PURCHASES];
//    int orderCount;
//};
//typedef struct customer_tag Customer;
//
///************* Prototypes **************/
//void readFiles(Customer *customers);
//
//Customer * parseLine(char *newLine, int space[3], Customer *customers);
//
//int getCustomer(char *name, Customer *customer);
//
//double getOrderPrice(char *productCost);
//
//Customer * sortCustomers(Customer *customers, int size);
//
//Customer * sortOrders(Customer *customers, int size);
//
//void printTimeFile(Customer*, int, char*);
//
//void printMoneyFile(Customer *customers, int customer_count, char *fileName);
//
//Customer updateCustomer(char *name, char *product, int qty, double orderCost, Customer customers);
//
///************** Functions **************/
//
///**
// * Main function that kicks off the program.
// */
//int main (void){
//
//    Customer customers[MAX_PURCHASES];
//    readFiles(customers);
//
//    printf("\n\nend of program!!");
//    return 0;
//}
//
///**
// * Function reads input file and calls to another function which stores the
// * customer information, then sends the customer information to be
// * sorted and printed.
// *
// * @param customers a pointer to an array of customers.
// */
//void readFiles(Customer *customers){
//
//    FILE *inputFile = fopen("hw5input.txt", "r");
//    if(!inputFile){
//        perror("Invalid file, please try again");
//        fclose(inputFile);
//    }
//
//    else {
//        int customer_count, i, lineIndex;;
//        i = lineIndex = customer_count = 0;
//        __ssize_t lineLength = 0;
//        //char newLine[200] = {'\0'};
//        char *newLine = (char *)malloc(1000);
//        newLine[0] = '\0';
//        lineLength = getline(&newLine, (size_t *) &lineLength, inputFile);
//        while(lineLength > 0 && newLine[0] != '\r'){
//            lineIndex = 0;
//            i = 0;
//            int space_locations[3];
//
//            while (EOF != newLine[lineIndex] && newLine[lineIndex] != '\0' && i < 3){
//                if(newLine[lineIndex] == ' '){
//                    space_locations[i] = lineIndex;
//                    i++;
//                }
//                lineIndex++;
//            }
//            if(EOF != newLine[lineIndex] && '\r' != newLine[0]) {
//
//                customers = parseLine(newLine, space_locations, customers);
//                newLine[0] = '\0';
//                lineLength = getline(&newLine, (size_t *) &lineIndex, inputFile);
//            }
//        }
//        /*****! Free Memory !*****/
//        free(newLine);
//        fclose(inputFile);
//
//        customer_count = getCustCount(customers);
//        //Print sorted by time
//        printTimeFile(customers, customer_count, "hw5Time.txt");
//        //Sort
//        customers = sortCustomers(customers, customer_count);
//        customers = sortOrders(customers, customer_count);
//        //Print by total order price
//        printMoneyFile(customers, customer_count, "hw5Money.txt");
//
//
//    }
//
//    //fclose(inputFile);
//}
///**
// * This function accepts a line from a textfile, parses the data into
// * relevent information, then assigns it to the proper struct values.
// * @param newLine the new line being read
// * @param space an array identifying the location of the spaces in the line
// * @param customers the array of Customers
// * @param custCount a count of the number of customers that have been identifed
// * @return an updated count of customers.
// */
//Customer * parseLine(char *newLine, int space[3], Customer *customers){
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nTEST:  Parse Line Function  \n\n");
//        printf("line:  %s\n", newLine);
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//    char name[NAME_LEN] = {'\0'};
//    char product[NAME_LEN] = {'\0'};
//    char qtyc[2] = {'\0'};
//    char productCost[10] = {'\0'}; //allows for product cost of up to $999999.99
//    int qty = 0;
//    int ctr = 0;
//    int i = -1;
//    while (newLine[i++] != '\r' && newLine[i] != '\0'){
//        if(i != space[0] && i != space[1] && i != space[2]) {
//            if (i < space[0]) { //name
//                name[i] = newLine[i];
//            } else if (i < space[1]) { //qty
//                qtyc[ctr] = newLine[i];
//                ctr++;
//            } else if (i < space[2]) { //product name
//                product[ctr] = newLine[i];
//                ctr++;
//            } else { //price
//                productCost[ctr++] = newLine[i+1];
//            }
//        }else{
//            ctr = 0;
//        }
//    }
//
//    int customerIndex = getCustomer(name, customers); //should return the index where the name exists or where it should be added.
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nTEST:  Customer Name and Index  \n\n");
//    printf("Customer: %s Index: %d\n", name,customerIndex);
//    printf("E~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
//    double orderPrice = getOrderPrice(productCost);
//    qty = atoi(qtyc);
//
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nTEST:  updateCustomer Function  \n\n");
//    printf("Customer: %s Index: %d    Product name: %s   Quantity:   %d\n  OrderPrice:   %d, ", name, customerIndex, product, qty, orderPrice);
//
//    customers[customerIndex] = updateCustomer(name, product, qty, orderPrice, customers[customerIndex]);
//    printf("After:    Customer: %s total order  %d\n", customers[customerIndex].name , customers[customerIndex].orderTotal);
//    printf("E~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
//
//    return customers;
//}
///**
// * Checks the array of customers and determines if that customer exists,
// * and the index of the customer.
// * @param name name of customer being searched for.
// * @param customer array of customers
// * @return the index of the customer, or 0 if they don't exist.
// */
//int getCustomer(char *name, Customer *customer){
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nTesting getCustomer function\n\n");
//    printf("name :  %s\n", name);
//    int nameFound = 0;
//    int i = 0;
//    while (!nameFound && customer[i].name[0] != '\0'){
//        printf("Customer [ %d ].name = %s",i, customer[i].name);
//        if(strcmp(name, customer[i].name) == 0){
//
//            nameFound = 1;
//        }else{
//            i++;
//        }
//    }
//    printf("%d", i);
//    printf("\nB~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//    return i;
//}
///**
// * Reads the product cost and converts it from a string to a double.
// * @param productCost a string representing the cost of the product
// * @return a double value of the cost of the product.
// */
//double getOrderPrice(char *productCost){
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nTesting getOrderPrice function\n\n");
//
//
//    while (*productCost && !(isdigit(*productCost) || ((*productCost == '-' || *productCost == '+') && isdigit(*(productCost + 1)))))
//        productCost++;
//
//    double orderCost = strtod(productCost, NULL);
//    printf("%d\n", orderCost);
//    printf("B~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
//    return orderCost;
//}
///**
// * Prints the customers and their orders
// * sorted in order of which their purchases were made.
// *
// * @param customers an array of customers
// * @param customer_count the number of customers in the array
// * @param fileName the name of the file to write to.
// */
//void printTimeFile(Customer *customers, int customer_count, char *fileName){
//    printf("Time file function ...... Customer count:  %d\n", customer_count);
//    FILE *outputFile = fopen(fileName, "w");
//
//    Customer *currentCust = malloc(sizeof(Customer));
//    Order *currentOrd = malloc(sizeof(Order));
//
//    for(int i = 0; i < customer_count; i++){
//
//        *currentCust = customers[i];
//        fprintf(outputFile, "Customer: %s\n %14s", currentCust->name, "Orders:");
//        for(int j = 0; j < customers[i].orderCount; j++){
//            *currentOrd = currentCust->orders[j];
//            fprintf(outputFile, "\n %14s %-15s %-7d %7.2f %10.2f", "", currentOrd->product, currentOrd->qty, currentOrd->itemPrice, currentOrd->orderPrice );
//        }
//        fprintf(outputFile, "\n %48s%9.2f\n", "Total:", customers[i].orderTotal);
//    }
//
//    /******! Free memory!***/
//    fclose(outputFile);
//    free(currentCust);
//    free(currentOrd);
//}
//
//Customer *sortCustomers(Customer *customers, int size){
//    printf("sort customers function ...... Customer count:  %d\n", size);
//    Customer c;
//    int topBubble, bubbles, notSorted = 1;
//    for(topBubble = 0; topBubble < size && notSorted; topBubble++)
//        for(bubbles = size, notSorted = 0; bubbles > topBubble; bubbles--){
//            if(customers[bubbles].orderTotal > customers[bubbles -1].orderTotal){
//                c = customers[bubbles];
//                customers[bubbles] = customers[bubbles-1];
//                customers[bubbles-1] = c;
//                notSorted = 1;
//            }
//        }
//    return customers;
//}
///**
// * Sorts the customers orders by total value.
// * @param customers an array of customers
// * @param size the number of customers in the array
// */
//Customer *sortOrders(Customer *customers, int size){
//    printf("sort orders function ...... Customer count:  %d\n", size);
//    Order order;
//    for(int i = 0; i < size; i++){
//        int topBubble, bubbles, orderCount = customers[i].orderCount, notSorted = 1;
//        for(topBubble = 0; topBubble < orderCount && notSorted; topBubble++)
//            for(bubbles = orderCount-1, notSorted = 0; bubbles > topBubble; bubbles--){
//                if(customers[i].orders[bubbles].orderPrice > customers[i].orders[bubbles -1].orderPrice){
//                    order = customers[i].orders[bubbles];
//                    customers[i].orders[bubbles] = customers[i].orders[bubbles-1];
//                    customers[i].orders[bubbles -1] = order;
//                    notSorted = 1;
//                }
//            }
//    }
//    return customers;
//}
///**
// * Function that prints the customers after they have been sorted.
// *
// * @param customers an array of customers
// * @param customer_count the number of customers in the array
// * @param fileName the name of the file to write to.
// */
//void printMoneyFile(Customer *customers, int customer_count, char *fileName){
//    FILE *outputFile = fopen(fileName, "w");
//
//    Customer *currentCust = malloc(sizeof(Customer));
//    Order *currentOrd = malloc(sizeof(Order));
//
//    for(int i = 0; i < customer_count; i++){
//        *currentCust = customers[i];
//        //print name and total
//        fprintf(outputFile,"%s, TotalOrder = $%.2f", currentCust->name, customers[i].orderTotal);
//        //print individual orders
//        int orderNum = currentCust->orderCount+1;
//        for(int j = 0; j < orderNum; j++){
//            fprintf(outputFile,"\n%s %d $%.2f, Item Value = $%.2f", customers[i].orders[j].product, customers[i].orders[j].qty, customers[i].orders[j].itemPrice, customers[i].orders[j].orderPrice);
//            printf("\n%s %d $%.2f, Item Value = $%.2f", customers[i].orders[j].product, customers[i].orders[j].qty, customers[i].orders[j].itemPrice, customers[i].orders[j].orderPrice);
//
//        }
//        fprintf(outputFile, "\n");
//    }
//
//    /******! Free memory!***/
//    fclose(outputFile);
//    free(currentCust);
//    free(currentOrd);
//}
//
//Customer updateCustomer(char *name, char *product, int qty, double itemCost, Customer customer){
//    printf("update customers function ...... Customer name:  %s\n", name);
//    //int newCustomer = 0;
//    int orderNum = 0;
//    if(customer.name[0] == '\0'){ //name doesn't exist, therefore, new customer. Initialize values.
//        //newCustomer = 1;          //update boolean
//        strcpy(customer.name, name); //add name
//        customer.orderCount = -1;
//        customer.orderTotal = 0;
//    }
//    orderNum = customer.orderCount = customer.orderCount+1;
//    strcpy(customer.orders[orderNum].product, product); //update product name
//    customer.orders[orderNum].qty = qty; //update qty in that order
//    customer.orders[orderNum].itemPrice = itemCost; //update product cost
//    customer.orders[orderNum].orderPrice = itemCost * qty; //update total cost of the order
//    customer.orderTotal += itemCost*qty;
//
//    return customer;
//}
//
//int getCustCount(Customer *customers){
//    printf("~~~~~~~ TESTING CUSTOMER COUNT ~~~~~~~~: \n");
//    int count = 0;
//    while(customers[count].name[0] != '\0'){
//        printf("Customer: %s:  %d\n\n", customers[count].name, count);
//        count++;
//    }
//    return count;
//}