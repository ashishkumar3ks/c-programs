#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char name[50];
    char author[50];
    int quantity;
};

void clearBuffer() {
    while (getchar() != '\n');
}

void addBook() {
    FILE *fp;
    struct Book b;

    fp = fopen("library.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Book ID: ");
    while (scanf("%d", &b.id) != 1) {
        printf("Invalid ID! Enter number: ");
        clearBuffer();
    }
    clearBuffer();

    printf("Enter Book Name: ");
    fgets(b.name, sizeof(b.name), stdin);
    b.name[strcspn(b.name, "\n")] = 0;

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("Enter Quantity: ");
    while (scanf("%d", &b.quantity) != 1) {
        printf("Invalid quantity! Enter number: ");
        clearBuffer();
    }

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\nBook added successfully!\n");
}

void displayBooks() {
    FILE *fp;
    struct Book b;

    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Library Books ---\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d", b.id);
        printf("\nName: %s", b.name);
        printf("\nAuthor: %s", b.author);
        printf("\nQuantity: %d\n", b.quantity);
    }
    fclose(fp);
}

void searchBook() {
    FILE *fp;
    struct Book b;
    int id, found = 0;

    fp = fopen("library.dat", "rb");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    while (scanf("%d", &id) != 1) {
        printf("Invalid ID! Enter number: ");
        clearBuffer();
    }

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found!");
            printf("\nName: %s", b.name);
            printf("\nAuthor: %s", b.author);
            printf("\nQuantity: %d\n", b.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook not found!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n\n===== Library Management System =====");
        printf("\n1. Add Book");
        printf("\n2. Display Books");
        printf("\n3. Search Book");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter a number.\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Choose 1–4.\n");
        }
    }
}

