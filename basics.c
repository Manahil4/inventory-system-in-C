#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxItems 3

//!Structure to represent an inventory item
struct inventoryItem {
    char name[50];
    float price;
    int quantity;
};

//! Function Declarations
void addItem();
void displayInventory();
void updateItem(char name[]);
void updateItemInterface(int index);
void increaseStock(int index);
void decreaseStock(int index);
void deleteItem(char name[]);
int searchItem(char name[]);

//! Global Variables
struct inventoryItem inventoryList[maxItems];
int itemCount = 0;

//! Function to search for an item in the inventory
int searchItem(char name[]) {
    int index = -1;
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(inventoryList[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("\n%s is in the Inventory.", inventoryList[index].name);
        return index;
    } else {
        printf("\n%s is not in the Inventory.", name);
        return -1;
    }
}

//! Function to add a new item to the inventory
void addItem() {
    if (itemCount < maxItems) {
        printf("\nEnter the name of the item: ");
        scanf("%s", inventoryList[itemCount].name);

        printf("Enter the quantity of the item: ");
        scanf("%d", &inventoryList[itemCount].quantity);

        printf("Enter the price of the item: $");
        scanf("%f", &inventoryList[itemCount].price);

        itemCount++;
        printf("\nItem added successfully!\n");
    } else {
        printf("\nInventory is full!\nCannot add more items.\n");
    }

    displayInventory();
}

//! Function to display the current inventory
void displayInventory() {
    if (itemCount > 0) {
        printf("\nInventory:\n");
        for (int i = 0; i < itemCount; i++) {
            printf("Item: %s, Quantity: %d, Price: $%.2f\n", inventoryList[i].name, inventoryList[i].quantity, inventoryList[i].price);
        }
    } else {
        printf("\nInventory is empty.\n");
    }
}

//! Function to update an existing item in the inventory
void updateItem(char name[]) {
    int index = searchItem(name);

    if (index != -1) {
        printf("\nCurrent details of %s: Quantity: %d; Price: $%.2f\n", inventoryList[index].name, inventoryList[index].quantity, inventoryList[index].price);
        updateItemInterface(index);
    } else {
        printf("\n%s cannot be updated. It is not in the inventory.", name);
        displayInventory();
    }
}

//! Function to provide an interface for updating an item
void updateItemInterface(int index) {
    int choice = 0;
    do {
        printf("\n%s Item Stock", inventoryList[index].name);
        printf("\n1. Add quantity to stock");
        printf("\n2. Remove quantity from stock");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                increaseStock(index);
                break;
            case 2:
                decreaseStock(index);
                break;
            case 3:
                printf("\nExiting from the Update Interface...\n");
                break;
            default:
                printf("\nInvalid Choice.");
                break;
        }

        displayInventory();
    } while (choice != 3);
}

//! Function to increase the stock of an item
void increaseStock(int index) {
    int additionalQuantity;
    printf("\nEnter the quantity to add: ");
    scanf("%d", &additionalQuantity);

    inventoryList[index].quantity += additionalQuantity;

    float additionalPrice;
    printf("Enter the price of the added quantities: $");
    scanf("%f", &additionalPrice);

    inventoryList[index].price += additionalPrice;

    printf("\nSuccessfully added %d quantity to %s's stock.", additionalQuantity, inventoryList[index].name);
}

//! Function to decrease the stock of an item
void decreaseStock(int index) {
    int reducedQuantity;
    printf("\nEnter the quantity to remove: ");
    scanf("%d", &reducedQuantity);

    float reducedPrice;
    printf("Enter the price of the removed quantities: $");
    scanf("%f", &reducedPrice);

    if (reducedQuantity == inventoryList[index].quantity) {
        printf("\n%s's stock will be empty, as you have ordered the total stock of %s.", inventoryList[index].name, inventoryList[index].name);
        inventoryList[index].quantity -= reducedQuantity;
        inventoryList[index].price -= reducedPrice;
        printf("\nRemaining %s's stock: %d", inventoryList[index].name, inventoryList[index].quantity);
    } else if (reducedQuantity < inventoryList[index].quantity) {
        printf("\nOrder within the existing stock!");
        inventoryList[index].quantity -= reducedQuantity;
        inventoryList[index].price -= reducedPrice;
        printf("\nRemaining %s's stock: %d", inventoryList[index].name, inventoryList[index].quantity);
    } else {
        printf("\nYou ordered more than is in stock! You can take the available stock of %s, which is %d.", inventoryList[index].name, inventoryList[index].quantity);
    }
}

//! Function to delete an item from the inventory
void deleteItem(char name[]) {
    int index = searchItem(name);

    if (index != -1) {
        printf("\nCurrent details of %s: Quantity: %d; Price: $%.2f\n", inventoryList[index].name, inventoryList[index].quantity, inventoryList[index].price);

        // Shift elements to remove the gap
        for (int i = index; i < itemCount - 1; i++) {
            inventoryList[index] = inventoryList[index + 1];
        }

        itemCount--;
        printf("\n%s has been deleted successfully!", name);
    } else {
        printf("\n%s has not been deleted. It is not in the inventory.", name);
    }

    displayInventory();
}

//! Main function to interact with the user
int main() {
    int choice = 0;
    char itemName[50];

    do {
        printf("\n\nInventory Management System");
        printf("\n1. Add Item");
        printf("\n2. Display Inventory");
        printf("\n3. Update Items");
        printf("\n4. Delete Item");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                printf("\nEnter the name of the item to update: ");
                scanf("%s", itemName);
                updateItem(itemName);
                break;
            case 4:
                printf("\nEnter the name of the item to delete: ");
                scanf("%s", itemName);
                deleteItem(itemName);
                break;
            case 5:
                printf("\nExiting the program...\n");
                break;
            default:
                printf("\nInvalid Choice.");
                break;
        }
    } while (choice != 5);

    return 0;
}
