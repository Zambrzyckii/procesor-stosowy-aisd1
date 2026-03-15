#include <iostream>
#include "manager.h"

int main() {
    StackManager manager;
    char programCode[20002];
    fgets(programCode, 20002, stdin);
    int instructionPointer = 0;
    bool isRunning = true;

    while (isRunning) {
        switch (char instruction = programCode[instructionPointer]) {
            case '\0':
            case '\n':
                isRunning = false;
                break;
            case '\'':
                manager.push_empty_list();
                break;
            case ',':
                manager.pop_stack();
                break;
            case ':':
                if (!manager.top_has_value()) {
                    manager.push_empty_list();
                
} else {
                    manager.duplicate_top_list();
                
}
                break;
            case ';':
                if (manager.top->head) {
                    manager.swap_top_two_lists();
                
}
                break;
            case '@': {
                int indexToCopy = manager.pop_list_and_get_number();
                manager.copy_list_from_index(indexToCopy);
                break;
            
}
            case '.': {
                char inputChar;
                std::cin >> inputChar;
                manager.push_char_to_top_list(inputChar);
                break;
            
}
            case '>': {
                List* outputList = manager.get_and_pop_top_list();
                if (outputList) {
                    std::cout << outputList->character;
                
}
                delete outputList;
                break;
            
}
            case '!': {
                if (!manager.top_has_value()) {
                    manager.replace_top_list_with_char('1');
                
} else if (manager.top_list_is_single_zero()) {
                    manager.replace_top_list_with_char('1');
                
} else {
                    manager.replace_top_list_with_char('0');
                
}
                break;
            
}
            case '<': {
                if (manager.top->head) {
                    List* listA = manager.get_and_pop_top_list();
                    List* listB = manager.get_and_pop_top_list();
                    int compareResult = manager.compare_list(listA, listB);
                    if (compareResult <= 0)
                        manager.push_single_char_list('0');
                    else
                        manager.push_single_char_list('1');
                    delete listA;
                    delete listB;
                
}
                break;
            
}
            case '=': {
                if (manager.top->head) {
                    List* listA = manager.get_and_pop_top_list();
                    List* listB = manager.get_and_pop_top_list();
                    int compareResult = manager.compare_list(listA, listB);
                    if (compareResult == 0)
                        manager.push_single_char_list('1');
                    else
                        manager.push_single_char_list('0');
                    delete listA;
                    delete listB;
                
}
                break;
            
}
            case '~': {
                manager.push_empty_list();
                manager.push_number_digits(manager, instructionPointer);
                break;
            
}
            case '?': {
                int jumpTarget = manager.pop_list_and_get_number();
                if (manager.top) {
                    List* conditionList = manager.get_and_pop_top_list();
                    bool isEmpty = (conditionList == nullptr);
                    bool isZero = (conditionList && conditionList->character == '0' && conditionList->head == nullptr);

                    if (!isEmpty && !isZero) {
                        instructionPointer = jumpTarget - 1;
                    
}
                    delete conditionList;
                
}
                break;
            
}
            case '-':
                manager.toggle_minus_on_top_list();
                break;
            case '^':
                manager.absolute_top_list();
                break;
            case '$':
                manager.split_first_char_to_new_list();
                break;
            case '#':
                manager.pop_and_append_to_top();
                break;
            case '+': {
                if (manager.top->head) {
                    List* listA = manager.get_and_pop_top_list();
                    List* listB = manager.get_and_pop_top_list();
                    List* sumList = Add(listA, listB);
                    manager.push_list(sumList);
                    delete listA;
                    delete listB;
                
}
                break;
            
}
            case ']': {
                int asciiValue = manager.pop_list_and_get_number();
                manager.push_single_char_list((char)asciiValue);
                break;
            
}
            case '&': {
                manager.show_stack();
                break;
            
}
            case '[': {
                if (manager.top) {
                    List* charList = manager.get_and_pop_top_list();
                    int asciiValue = (int)(charList->character);
                    delete charList;
                    manager.push_empty_list();
                    manager.push_number_digits(manager, asciiValue);
                
} else {
                    manager.push_single_char_list('0');
                
}
                break;
            
}
            default:
                manager.push_char_to_top_list(instruction);
                break;
        
}
        instructionPointer++;
    
}
    return 0;
}
