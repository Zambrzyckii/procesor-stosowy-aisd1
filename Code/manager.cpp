#include <iostream>
#include "manager.h"

// odwraca liczbe
int ReverseNumber(int number, int reversed) {
    if (number == 0) return reversed;
    return ReverseNumber(number / 10, reversed * 10 + number % 10);
}

// dodaje znak na poczatek listy
void PushCharacter(List** listHead, char character) {
    List* newNode = new List;
    newNode->character = character;
    newNode->head = *listHead;
    *listHead = newNode;
}

// zwraca ostatni element listy
List* GetLastNode(List* node) {
    if (!node) return nullptr;
    if (!node->head) return node;
    return GetLastNode(node->head);
}

// zwraca przedostatni element listy
List* GetSecondLastNode(List* node) {
    if (!node || !node->head) return nullptr;
    if (!node->head->head) return node;
    return GetSecondLastNode(node->head);
}

// rekurencyjnie porownuje dwie listy znakow reprezentujace liczby
int AreEqualRecursive(List* num1, List* num2, int minusCount, int isZero) {
    // pomin minus w num1
    if (num1 && num1->character == '-') {
        return AreEqualRecursive(num1->head, num2, minusCount + 1, isZero);
    
}

    // pomin minus w num2
    if (num2 && num2->character == '-') {
        return AreEqualRecursive(num1, num2->head, minusCount - 1, isZero);
    
}

    // jesli obie listy sie skonczyly
    if (!num1 && !num2) {
        return (minusCount == 0) || isZero;
    
}

    // porownanie znak po znaku
    if (num1 && num2) {
        if (num1->character == num2->character) {
            int nextZero = (num1->character == '0' && isZero);
            return AreEqualRecursive(num1->head, num2->head, minusCount, nextZero);
        
}
        return 0;
    
}

    // sprawdz czy zostaly tylko zera w jednej z list
    if (num1 == NULL && num2) {
        return (num2->character == '0') ? AreEqualRecursive(NULL, num2->head, minusCount, isZero) : 0;
    
}

    return (num1->character == '0') ? AreEqualRecursive(num1->head, NULL, minusCount, isZero) : 0;
}

// sprawdza czy dwie liczby w formie list sa rowne
int AreEqual(List* num1, List* num2) {
    return AreEqualRecursive(num1, num2, 0, 1);
}

// rekurencyjnie sprawdza czy num1 < num2
int IsLessThanRecursive(List* num1, List* num2, int isSmaller) {
    // pomin minus w num1
    if (num1 && num1->character == '-') {
        return IsLessThanRecursive(NULL, num2, isSmaller);
    
}

    // pomin minus w num2
    if (num2 && num2->character == '-') {
        return IsLessThanRecursive(num1, NULL, isSmaller);
    
}

    // jesli obie listy sie skonczyly
    if (!num1 && !num2) {
        return isSmaller;
    
}

    // porownanie cyfr
    if (num1 && num2 && num1->character != '-' && num2->character != '-') {
        if (num1->character != num2->character) {
            return IsLessThanRecursive(num1->head, num2->head, num1->character < num2->character);
        
}
        return IsLessThanRecursive(num1->head, num2->head, isSmaller);
    
}

    // pomin zera w jednej z list
    if (!num1 && num2 && num2->character == '0') {
        return IsLessThanRecursive(NULL, num2->head, isSmaller);
    
}

    if (!num2 && num1 && num1->character == '0') {
        return IsLessThanRecursive(num1->head, NULL, isSmaller);
    
}

    // jesli jedna z list jest krotsza to jest mniejsza
    return (num1 == NULL) || !(num2 == NULL && num1->character > '0');
}

// glowna funkcja do sprawdzania czy num1 < num2 z uwzglednieniem znakow
int IsLessThan(List* num1, List* num2) {
    if (AreEqual(num1, num2)) return 0;

    char last1 = GetLastNode(num1)->character;
    char last2 = GetLastNode(num2)->character;

    // minus jest mniejszy niz liczba dodatnia
    if (last1 == '-' && last2 != '-') return 1;
    if (last1 != '-' && last2 == '-') return 0;

    int result = IsLessThanRecursive(num1, num2, 0);
    return (last1 == '-' && last2 == '-') ? !result : result;
}

// rekurencyjne odejmowanie num2 od num1 i zapis do listy wynikowej
int SubtractRecursive(List** result, List* num1, List* num2, int borrow) {
    if (!num1 && !num2 && borrow == 0)
        return 0;

    int val1 = num1 ? (num1->character - '0') : 0;
    int val2 = num2 ? (num2->character - '0') : 0;

    int diff = val1 - val2 - borrow;

    borrow = (diff < 0) ? 1 : 0;
    if (borrow) diff += 10;

    int hasValue = SubtractRecursive(result, num1 ? num1->head : NULL, num2 ? num2->head : NULL, (num1 || num2) ? borrow : 0);

    if (hasValue || diff != 0) {
        PushCharacter(result, (diff % 10) + '0');
        return 1;
    
}

    return hasValue;
}

// rekurencyjne dodawanie dwoch liczb zapisanych jako listy
int AddRecursive(List** result, List* num1, List* num2, int carry) {
    if (!num1 && !num2 && carry == 0)
        return 0;

    int sum = carry;
    if (num1) sum += num1->character - '0';
    if (num2) sum += num2->character - '0';

    int nextCarry = sum / 10;

    int hasValue = AddRecursive(result, num1 ? num1->head : NULL, num2 ? num2->head : NULL, nextCarry);

    if (hasValue || sum != 0) {
        PushCharacter(result, (sum % 10) + '0');
        return 1;
    
}

    return hasValue;
}

// dodaje lub odejmuje dwie liczby w formie list, zwraca wynik jako nowa lista
List* Add(List* num1, List* num2) {
    List* result = nullptr;
    List* secondLast1 = GetSecondLastNode(num1);
    int isNegative1 = 0, isNegative2 = 0;

    // sprawdzenie i usuniecie minusa z num1
    if (secondLast1 && secondLast1->head && secondLast1->head->character == '-') {
        isNegative1 = 1;
        delete secondLast1->head;
        secondLast1->head = nullptr;
    
}

    // sprawdzenie i usuniecie minusa z num2
    List* secondLast2 = GetSecondLastNode(num2);
    if (secondLast2 && secondLast2->head && secondLast2->head->character == '-') {
        isNegative2 = 1;
        delete secondLast2->head;
        secondLast2->head = nullptr;
    
}

    // jesli znaki takie same, wykonaj zwykle dodawanie
    if (isNegative1 == isNegative2) {
        if (isNegative1) PushCharacter(&result, '-');
        int hasValue = AddRecursive(&result, num1, num2, 0);
        if (!hasValue) PushCharacter(&result, '0');
        return result;
    
}

    // jesli liczby sa rowne, wynik to 0
    if (AreEqual(num1, num2)) {
        PushCharacter(&result, '0');
        return result;
    
}

    int num1IsSmaller = IsLessThan(num1, num2);

    // okresl znak wyniku na podstawie wiekszej liczby
    if ((isNegative1 && !num1IsSmaller) || (isNegative2 && num1IsSmaller)) {
        PushCharacter(&result, '-');
    
}

    // odejmowanie odpowiednich liczb
    if (num1IsSmaller) {
        SubtractRecursive(&result, num2, num1, 0);
    
} else {
        SubtractRecursive(&result, num1, num2, 0);
    
}

    return result;
}
