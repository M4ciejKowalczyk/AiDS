#include <iostream>
#include <stdlib.h>

#define LEN_OF_MIN_MAX 2

enum Member {
    OPERAND = 0,
    OPERATOR = 1,
    FUNKCJA = 2
};

struct Token {
    Member activeMember;
    union {
        int operand;
        char op;
        char funk[8];
    } value;
};

struct NumOfArg {
    int numberOfArguments;
    int numberOfLeftParenthesis;
    int numberOfRightParenthesis;
};

class Stack {
private:
    struct Node {
        Token* token;
        Node* next;
    };
    Node* head;

public:
    Stack() {
        head = nullptr;
    }

    void push(Token* dataToStore) {
        Node* newNode = new Node;
        newNode->token = dataToStore;
        newNode->next = head;
        head = newNode;
    }

    void pop() {
        if (empty()) {
            printf("Stos jest pusty\n");
            return;
        }
        head = head->next;
    }

    Token* top() const {
        if (empty()) {
            printf("Stos jest pusty\n");
            return nullptr;
        }
        return head->token;
    }

    bool empty() const {
        return head == nullptr;
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
};

class Queue {
private:
    struct Node {
        Token* token;
        Node* next;
    };
    Node* head;
    Node* tail;

public:
    Queue() {
        head = nullptr;
        tail = nullptr;
    }

    void push(Token* dataToStore) {
        Node* newNode = new Node;
        newNode->token = dataToStore;
        newNode->next = nullptr;
        if (empty()) {
            tail = newNode;
            head = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop() {
        if (empty()) {
            printf("Kolejka jest pusta\n");
            return;
        }
        head = head->next;
        if (head == nullptr) tail = nullptr;
    }

    Token* front() const {
        if (empty()) {
            printf("Kolejka jest pusta\n");
            return nullptr;
        }
        return head->token;
    }

    bool empty() const {
        return head == nullptr;
    }

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
};

char nextChar()
{
    char res;
    scanf("%c", &res);
    return res;
}

//Pobieramy token z wejścia
void GetNextToken(Token* result, char currChar) {
    int i = 0;
    int j = 0;
    char tmp[12];


    while (currChar == ' ' || currChar == '\n') {
        currChar = nextChar();
    }
    while (currChar != ' ' && currChar != '.') {
        tmp[i] = currChar;
        currChar = nextChar();
        i++;
    }
    tmp[i] = '\0';
    if (tmp[0] >= '0' && tmp[0] <= '9') {
        result->activeMember = OPERAND;
        result->value.operand = atoi(tmp);
    }
    else if (tmp[1] == '\0') {
        result->activeMember = OPERATOR;
        result->value.op = tmp[0];
    }
    else {
        result->activeMember = FUNKCJA;
        while (tmp[j] != '\0') {
            result->value.funk[j] = tmp[j];
            j++;
        }
        result->value.funk[j] = '\0';
    }
}

int getPriority(Token* token) {
    if (token->activeMember == OPERATOR) {
        switch (token->value.op) {
        case '+':
            return 1;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        case 'N':
            return 4;
        default:
            return 0;
        }
    }
    else {
        if (token->value.funk[0] == 'I' && token->value.funk[1] == 'F') return 3;
        else return 5;
    }

}

bool isMinOrMax(Token* token) {
    return token->value.funk[LEN_OF_MIN_MAX] == 'X' || token->value.funk[LEN_OF_MIN_MAX] == 'N';
}

void printToken(Token* res)
{
    if (res->activeMember == OPERAND) {
        printf("%d ", res->value.operand);
    }
    else if (res->activeMember == OPERATOR) {
        printf("%c ", res->value.op);
    }
    else if (res->activeMember == FUNKCJA) printf("%s ", res->value.funk);
}

void initializeArray(NumOfArg* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i].numberOfArguments = 1;
        array[i].numberOfLeftParenthesis = 0;
        array[i].numberOfRightParenthesis = 0;
    }
}

// Liczymy liczbę argumentów (ilość wystąpień przecinków, z dopowiednim uwzględnieniem nawiasów)
// dla każdego Min i Max
void handleNumberOfArguments(Token* token, NumOfArg array[], int idCounter) {

    for (int i = 0; i < idCounter; i++) {
        if ((array[i].numberOfLeftParenthesis > 0 && array[i].numberOfLeftParenthesis != array[i].numberOfRightParenthesis) || array[i].numberOfLeftParenthesis == 0) {
            if (token->value.op == ',' && array[i].numberOfLeftParenthesis - array[i].numberOfRightParenthesis == 1) array[i].numberOfArguments++;
            if (token->value.op == '(')array[i].numberOfLeftParenthesis++;
            if (token->value.op == ')')array[i].numberOfRightParenthesis++;
        }
    }

}

void printONP(Queue queue) {
    Queue temp = queue;
    while (!temp.empty()) {
        printToken(temp.front());
        temp.pop();
    }
    printf("\n");
}

// Przy zdejmowaniu Min/Max ze stosu odczytujemy
// id aby przypisać liczbę argumentów z właściwego pola tablicy
int getId(Token* token) {
    int res = 0;
    int i = 3;
    while (token->value.funk[i] != '\0') {
        res = res * 10;
        res += token->value.funk[i] - '0';
        i++;
    }
    return res;
}


// Używamy tej fukcji aby przed wysłaniem na stos funkcji
// Min/Max zapamiętać, jako który z kolei token tego typu
// pojawił się na wejściu, a póżniej przed wrzuceniem do kolejki
// doklejamy liczbę argumentów funkcji
void addId(Token*& token, int counter) {
    int i = 0;
    int j = 3;

    char tmp[8];

    while (counter > 0) {
        tmp[i] = counter % 10 + '0';
        counter = counter / 10;
        i++;

    }
    tmp[i] = '\0';
    i--;
    while (i >= 0) {
        token->value.funk[j++] = tmp[i--];
    }
    token->value.funk[j] = '\0';
}

Queue ONPConv(Token* expression) {
    Stack stack;
    Queue onp;
    char currChar;
    int idCounter = 0;
    const int arraySize = 1000;
    NumOfArg arrayOfArgs[arraySize];

    initializeArray(arrayOfArgs, arraySize);

    while ((currChar = nextChar()) != '.') {
        GetNextToken(expression, currChar);

        if (expression->activeMember == OPERAND) {
            Token* operandCopy = new Token(*expression);
            onp.push(operandCopy);
        }
        else if (expression->activeMember == FUNKCJA) {
            Token* operandCopy = new Token(*expression);
            if (isMinOrMax(operandCopy)) {
                idCounter++;
                addId(operandCopy, idCounter);
            }
            stack.push(operandCopy);
        }
        else if (expression->value.op == ',') {
            handleNumberOfArguments(expression, arrayOfArgs, idCounter);
            while (stack.top()->value.op != '(') {
                Token* tmp = stack.top();
                stack.pop();
                onp.push(tmp);
            }
        }
        else if (expression->value.op == '(') {
            handleNumberOfArguments(expression, arrayOfArgs, idCounter);
            Token* operatorCopy = new Token(*expression);
            stack.push(operatorCopy);
        }
        else if (expression->value.op == ')') {
            handleNumberOfArguments(expression, arrayOfArgs, idCounter);
            while (!stack.empty() && stack.top()->value.op != '(') {
                Token* tmp = stack.top();
                stack.pop();
                if (isMinOrMax(tmp)) {
                    int temp = getId(tmp);
                    addId(tmp, arrayOfArgs[temp - 1].numberOfArguments);
                }
                onp.push(tmp);
            }
            if (!stack.empty() && stack.top()->value.op == '(') {
                stack.pop();
            }
            if (!stack.empty() && stack.top()->activeMember == FUNKCJA) {
                Token* tmp = stack.top();
                stack.pop();
                if (isMinOrMax(tmp)) {
                    int temp = getId(tmp);
                    addId(tmp, arrayOfArgs[temp - 1].numberOfArguments);
                }
                onp.push(tmp);
            }

        }
        else {
            int priority = getPriority(expression);
            while (!stack.empty() && stack.top()->value.op != '(' && (getPriority(stack.top()) > priority
                || (stack.top()->value.op != 'N' && getPriority(stack.top()) == priority))) {
                Token* top = stack.top();
                stack.pop();
                if (isMinOrMax(top)) {
                    int temp = getId(top);
                    addId(top, arrayOfArgs[temp - 1].numberOfArguments);
                }
                onp.push(top);
            }
            Token* operatorCopy = new Token(*expression);
            stack.push(operatorCopy);
        }
    }
    while (!stack.empty()) {
        Token* item = stack.top();
        stack.pop();
        if (isMinOrMax(item)) {
            int temp = getId(item);
            addId(item, arrayOfArgs[temp - 1].numberOfArguments);
        }
        if (item->value.op != '(') {
            onp.push(item);
        }
    }
    return onp;
}

Token* doCalculation(Token* token, Token* operand1, Token* operand2) {
    Token* res = new Token;
    res->activeMember = OPERAND;
    switch (token->value.op) {
    case '+':
        res->value.operand = operand2->value.operand + operand1->value.operand;
        break;
    case '-':
        res->value.operand = operand2->value.operand - operand1->value.operand;
        break;
    case '*':
        res->value.operand = operand2->value.operand * operand1->value.operand;
        break;
    case '/':
        if (operand1->value.operand == 0) {
            printf("ERROR\n");
            delete res;
            delete token;
            delete operand1;
            delete operand2;
            return nullptr; // Zwracamy nullptr aby ozanczyć błąd
        }
        res->value.operand = operand2->value.operand / operand1->value.operand;
        break;
    }
    delete token;
    delete operand1;
    delete operand2;
    return res;
}

Token* doNegation(Token* token, Token* operand) {
    Token* res = new Token;
    res->activeMember = OPERAND;
    res->value.operand = -operand->value.operand;
    delete token;
    delete operand;
    return res;
}

Token* doIF(Token* operand1, Token* operand2, Token* operand3) {
    Token* res = new Token;
    res->activeMember = OPERAND;
    if (operand3->value.operand > 0) {
        res->value.operand = operand2->value.operand;
    }
    else res->value.operand = operand1->value.operand;
    delete operand1;
    delete operand2;
    delete operand3;
    return res;

}

Token* findMax(Token* token, Stack& stack) {
    int arguments = getId(token);
    Token* res = new Token;
    res->activeMember = OPERAND;
    Token* operand1 = stack.top();
    stack.pop();
    res->value.operand = operand1->value.operand;
    delete operand1;
    while (arguments > 1) {
        Token* operand = stack.top();
        stack.pop();
        if (res->value.operand < operand->value.operand) {
            res->value.operand = operand->value.operand;
        }
        delete operand;
        arguments--;
    }
    return res;

}

Token* findMin(Token* token, Stack& stack) {
    int arguments = getId(token);
    Token* res = new Token;
    res->activeMember = OPERAND;
    Token* operand1 = stack.top();
    stack.pop();
    res->value.operand = operand1->value.operand;
    delete operand1;
    while (arguments > 1) {
        Token* operand = stack.top();
        stack.pop();
        if (res->value.operand > operand->value.operand) {
            res->value.operand = operand->value.operand;
        }
        delete operand;
        arguments--;
    }
    return res;

}

void printStack(Stack stack) {
    Stack tempStack = stack;

    while (!tempStack.empty()) {
        Token* token = tempStack.top();
        printf("%d ", token->value.operand);
        tempStack.pop();
    }

    printf("\n");
}

void ONPCalc(Queue onp) {
    Stack stack;
    printONP(onp);
    while (!onp.empty()) {
        Token* token = onp.front();
        onp.pop();
        if (token->activeMember == OPERAND) {
            stack.push(token);
        }
        else if (token->activeMember == OPERATOR) {
            printf("%c ", token->value.op);
            printStack(stack);
            if (token->value.op == 'N') {
                Token* operand = stack.top();
                stack.pop();
                Token* res = doNegation(token, operand);
                stack.push(res);
            }
            else {
                Token* operand1 = stack.top();
                stack.pop();
                Token* operand2 = stack.top();
                stack.pop();
                Token* res = doCalculation(token, operand1, operand2);
                if (res == nullptr) {
                    while (!stack.empty()) {
                        delete stack.top();
                        stack.pop();
                    }
                    return;
                }
                stack.push(res);
            }
        }
        else {
            printf("%s ", token->value.funk);
            printStack(stack);
            if (token->value.funk[0] == 'I' && token->value.funk[1] == 'F') {
                Token* operand1 = stack.top();
                stack.pop();
                Token* operand2 = stack.top();
                stack.pop();
                Token* operand3 = stack.top();
                stack.pop();
                Token* res = doIF(operand1, operand2, operand3);
                stack.push(res);
            }
            else if (token->value.funk[2] == 'X') {
                Token* res = findMax(token, stack);
                stack.push(res);
            }
            else {
                Token* res = findMin(token, stack);
                stack.push(res);
            }

        }
    }
    Token* result = stack.top();
    stack.pop();
    printf("%d\n", result->value.operand);
}



int main() {
    int testsNumber;
    Token expression;
    scanf("%d", &testsNumber);
    while (testsNumber > 0) {
        ONPCalc(ONPConv(&expression));
        printf("\n");
        printf("\n");
        testsNumber--;
    }

    return 0;
}
