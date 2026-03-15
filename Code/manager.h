#ifndef MANAGER_H
#define MANAGER_H

// pojedynczy element listy znakow
class List {
public:
    char character;
    List* head;
    int index;

    List() : character('\0'), head(nullptr), index(0) {
}
    ~List() { delete head; 
}
};

// stos zawierajacy listy znakow
class Stack {
public:
    List* value;
    Stack* head;
    int index;
    int size;

    Stack() : value(nullptr), head(nullptr), index(0), size(0) {
}
    ~Stack() { delete value; delete head; 
}
};

// obsluga stosu i operacji na listach
class StackManager {
private:
    // wypisuje znaki z listy
    void print(List* list) {
        if (!list) return;
        std::cout << list->character;
        print(list->head);
    
}

    // pokazuje stos
    void show_list(Stack* stack, int level) {
        if (!stack) return;
        show_list(stack->head, level + 1);
        std::cout << level << ": ";
        if (stack->value) print(stack->value);
        std::cout << std::endl;
    
}

    // kopiuje liste z danego indeksu stosu
    void copy_list_from_index_wrap(Stack** stos, Stack* current, int index) {
        if (!current) return;
        if (index == 0) {
            Stack* newStack = new Stack;
            newStack->value = copy_list(current->value);
            update_indexes(newStack->value);
            newStack->size = count_elements(newStack->value);
            newStack->head = *stos;
            newStack->index = (*stos ? (*stos)->index + 1 : 0);
            *stos = newStack;
        
} else {
            copy_list_from_index_wrap(stos, current->head, index - 1);
        
}
    
}

    // dolacza liste na koniec
    List* append_to_end(List* base, List* toAppend) {
        if (!base) return toAppend;
        base->head = append_to_end(base->head, toAppend);
        return base;
    
}

    // usuwa minus z konca listy
    List* toggle_minus_recursive(List* node, bool& removed) {
        if (!node) return nullptr;
        if (!node->head) {
            if (node->character == '-') {
                removed = true;
                delete node;
                return nullptr;
            
}
            return node;
        
}
        node->head = toggle_minus_recursive(node->head, removed);
        return node;
    
}

    // usuwa minus z konca listy
    List* remove_trailing_minus(List* node, bool& removed) {
        if (!node) return nullptr;
        if (!node->head) {
            if (node->character == '-') {
                removed = true;
                delete node;
                return nullptr;
            
}
            return node;
        
}
        node->head = remove_trailing_minus(node->head, removed);
        return node;
    
}

    // sprawdza czy lista to zero
    bool is_zero(const List* node) {
        if (!node) return true;
        if (node->character != '0' && node->character != '-') return false;
        return is_zero(node->head);
    
}

    // porownuje dlugosci list
    int compare_length(const List* A, const List* B) {
        if (!A || !B) return 0;
        if (A->character < B->character) return -1;
        if (A->character > B->character) return 1;
        return compare_length(A->head, B->head);
    
}

    // usuwa zera z poczatku
    List* strip_leading_zero(const List* node) {
        if (!node) return nullptr;
        if (node->character == '0' && node->head)
            return strip_leading_zero(node->head);

        List* newNode = new List;
        newNode->character = node->character;
        newNode->head = strip_leading_zero(node->head);
        return newNode;
    
}

    // usuwa zera z konca
    List* strip_trailing_zero_recursive(List* node, bool& found_non_zero) {
        if (!node) return nullptr;
        node->head = strip_trailing_zero_recursive(node->head, found_non_zero);
        if (node->character == '0' && !found_non_zero) {
            delete node;
            return nullptr;
        
}
        found_non_zero = true;
        return node;
    
}

    // usuwa wszystkie zera
    List* strip_zero(const List* A) {
        if (!A) return nullptr;
        List* without_leading = strip_leading_zero(A);
        if (!without_leading) {
            List* zero = new List;
            zero->character = '0';
            zero->head = nullptr;
            return zero;
        
}
        bool found_non_zero = false;
        return strip_trailing_zero_recursive(without_leading, found_non_zero);
    
}

    // odwraca kolejnosc elementow listy
    List* reverse_recursive(List* A, List* acc = nullptr) {
        if (!A) return acc;
        List* next = A->head;
        A->head = acc;
        return reverse_recursive(next, A);
    
}

public:
    Stack* top = nullptr;

    // liczy elementy listy
    int count_elements(List* list) {
        if (!list) return 0;
        return 1 + count_elements(list->head);
    
}

    // aktualizuje indeksy w liscie
    void update_indexes(List* list, int currentIndex = 1) {
        if (!list) return;
        list->index = currentIndex;
        update_indexes(list->head, currentIndex + 1);
    
}

    // wrzuca pusta liste na stos
    void push_empty_list() {
        Stack* newStack = new Stack;
        newStack->value = nullptr;
        newStack->head = top;
        newStack->index = (top ? top->index + 1 : 0);
        newStack->size = 0;
        top = newStack;
    
}

    // wrzuca liste na stos
    void push_list(List* list) {
        Stack* newStack = new Stack;
        newStack->value = list;
        update_indexes(list);
        newStack->size = count_elements(list);
        newStack->head = top;
        newStack->index = (top ? top->index + 1 : 0);
        top = newStack;
    
}

    // dodaje znak do gory stosu
    void push_char_to_top_list(char character) {
        if (!top) return;
        List* newList = new List;
        newList->character = character;
        newList->head = top->value;
        update_indexes(newList);
        top->value = newList;
        top->size = count_elements(newList);
    
}

    // dodaje pojedynczy znak jako liste
    void push_single_char_list(char c) {
        push_empty_list();
        push_char_to_top_list(c);
    
}

    // dodaje cyfry liczby na stos
    void push_number_digits(StackManager& manager, int n) {
        if (n == 0) {
            manager.push_char_to_top_list('0');
            return;
        
}
        if (n / 10 > 0) push_number_digits(manager, n / 10);
        manager.push_char_to_top_list((n % 10) + '0');
    
}

    // scala dwie listy ze stosu
    void pop_and_append_to_top() {
        if (!top || !top->head) return;
        List* A = top->head->value;
        top->head->value = nullptr;
        Stack* toDelete = top->head;
        top->head = toDelete->head;
        toDelete->head = nullptr;
        delete toDelete;
        List* B = top->value;
        top->value = append_to_end(A, B);
        update_indexes(top->value);
        top->size = count_elements(top->value);
    
}

    // dzieli pierwszy znak na nowa liste
    void split_first_char_to_new_list() {
        if (!top || !top->value) return;
        List* original = top->value;
        List* first = new List;
        first->character = original->character;
        first->head = nullptr;
        List* rest = original->head;
        original->head = nullptr;
        Stack* restStack = new Stack;
        restStack->value = rest;
        restStack->size = count_elements(rest);
        restStack->index = top->index + 1;
        restStack->head = top->head;
        top->value = first;
        top->size = 1;
        top->head = restStack;
        update_indexes(first);
    
}

    // usuwa element ze stosu
    void pop_stack() {
        if (!top) return;
        Stack* toDelete = top;
        top = top->head;
        toDelete->head = nullptr;
        delete toDelete;
    
}

    // pobiera i usuwa liste z gory stosu
    List* get_and_pop_top_list() {
        if (!top) return nullptr;
        List* result = top->value;
        top->value = nullptr;
        pop_stack();
        return result;
    
}

    bool is_top_list_empty() const {
        return !top || top->value == nullptr;
    
}

    bool top_has_value() const {
        return top && top->value;
    
}

    bool top_list_is_single_zero() const {
        return top && top->value &&
               top->value->character == '0' &&
               top->value->head == nullptr;
    
}

    void replace_top_list_with_char(char character) {
        if (!top) return;
        delete top->value;
        List* newList = new List;
        newList->character = character;
        newList->head = nullptr;
        newList->index = 1;
        top->value = newList;
        top->size = 1;
    
}

    // kopiuje cala liste
    List* copy_list(List* original) {
        if (!original) return nullptr;
        List* copiedHead = new List();
        copiedHead->character = original->character;
        copiedHead->head = copy_list(original->head);
        return copiedHead;
    
}

   // wypisuje wszystkie listy na stosie
void show_stack() {
    show_list(top, 0);
}

// kopiuje liste z gory stosu i dodaje ja jako nowa
void duplicate_top_list() {
    if (!top || !top->value) return;
    Stack* newStack = new Stack;
    newStack->value = copy_list(top->value);
    update_indexes(newStack->value);
    newStack->size = count_elements(newStack->value);
    newStack->head = top;
    newStack->index = top->index + 1;
    top = newStack;
}

// zamienia miejscami dwie gorne listy na stosie
void swap_top_two_lists() {
    Stack* first = top;
    Stack* second = top->head;
    first->head = second->head;
    second->head = first;
    top = second;
}

// zamienia liste znakow na liczbe
int parse_number(List* list, int level = 1, bool* isNegative = nullptr) {
    if (!list) return 0;
    if (list->character == '-') {
        if (isNegative) *isNegative = true;
        return 0;
    
}
    int partial = (list->character - '0') * level;
    return partial + parse_number(list->head, level * 10, isNegative);
}

// zdejmuje liste ze stosu i zwraca jej wartosc jako liczbe
int pop_list_and_get_number() {
    if (!top || !top->value) return 0;
    bool isNegative = false;
    int number = parse_number(top->value, 1, &isNegative);
    pop_stack();
    return isNegative ? -number : number;
}

// kopiuje liste z podanego indeksu stosu
void copy_list_from_index(int index) {
    copy_list_from_index_wrap(&top, top, index);
}

// usuwa lub dodaje minus z listy na gorze stosu
void toggle_minus_on_top_list() {
    if (!top) return;
    bool removed = false;
    top->value = toggle_minus_recursive(top->value, removed);
    if (!removed) {
        List* newMinus = new List;
        newMinus->character = '-';
        newMinus->head = nullptr;
        top->value = append_to_end(top->value, newMinus);
    
}
    update_indexes(top->value);
    top->size = count_elements(top->value);
}

// usuwa minus z listy na gorze stosu jesli jest
void absolute_top_list() {
    if (!top || !top->value) return;
    bool removed = false;
    top->value = remove_trailing_minus(top->value, removed);
    if (removed) {
        update_indexes(top->value);
        top->size = count_elements(top->value);
    
}
}

// porownuje dwie listy znakow jako liczby
int compare_list(const List* A, const List* B) {
    if (is_zero(A) && is_zero(B)) return 0;
    bool NegA = has_minus(A);
    bool NegB = has_minus(B);
    List* stripped_A = strip_zero(strip_minus(A));
    List* stripped_B = strip_zero(strip_minus(B));
    List* revA = reverse_recursive(copy_list(stripped_A));
    List* revB = reverse_recursive(copy_list(stripped_B));
    int len_A = count_elements(stripped_A);
    int len_B = count_elements(stripped_B);
    int result = 0;

    if (len_A != len_B) {
        result = (len_A < len_B) ? -1 : 1;
    
} else {
        result = compare_length(revA, revB);
    
}

    if (NegA && !NegB) result = -1;
    else if (NegB && !NegA) result = 1;
    else if (NegA && NegB) result *= -1;

    delete stripped_A;
    delete stripped_B;
    delete revA;
    delete revB;
    return result;
}

// sprawdza czy lista zawiera znak minus
bool has_minus(const List* A) {
    if (!A) return false;
    if (A->character == '-') return true;
    return has_minus(A->head);
}

// usuwa wszystkie minusy z listy
List* strip_minus(const List* A) {
    if (!A) return nullptr;
    List* rest = strip_minus(A->head);
    if (A->character == '-') return rest;
    List* node = new List;
    node->character = A->character;
    node->head = rest;
    node->index = 0;
    return node;
}

// destruktor usuwa stos
~StackManager() {
    delete top;
}

};

// dodaje znak na poczatek listy
void PushCharacter(List** listHead, char character);

// porownuje dwie listy rekurencyjnie uwzgledniajac minusy i zera
int AreEqualRecursive(List* num1, List* num2, int minusCount, int isZero);

// sprawdza czy dwie listy sa rowne
int AreEqual(List* num1, List* num2);

// porownuje czy pierwsza lista jest mniejsza niz druga rekurencyjnie
int IsLessThanRecursive(List* num1, List* num2, int isSmaller);

// sprawdza czy pierwsza liczba jest mniejsza niz druga
int IsLessThan(List* num1, List* num2);

// wykonuje rekurencyjne odejmowanie dwoch liczb reprezentowanych jako lista
int SubtractRecursive(List** result, List* num1, List* num2, int borrow);

// wykonuje rekurencyjne dodawanie dwoch liczb jako lista
int AddRecursive(List** result, List* num1, List* num2, int carry);

// odwrocenie liczby calkowitej
int ReverseNumber(int number, int reversed = 0);

// dodaje dwie liczby jako listy i zwraca wynik
List* Add(List* num1, List* num2);

// zwraca ostatni element listy
List* GetLastNode(List* node);

// zwraca przedostatni element listy
List* GetSecondLastNode(List* node);


#endif // MANAGER_H
