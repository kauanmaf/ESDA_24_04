#include <iostream>

using std::endl;
using std::cout;
using std::cin;
using std::string;

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// Não precisa ter uma struct pra lista encadeada.
// Fazer uma estrutura deixa mais organizado, mas não é obrigatório

Node* createNode(int);
// Retornamos um ponteiro pra ponteiro
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode (Node**, Node*);
void displayList(Node*);

int main()
{
    Node* head = nullptr;
    displayList(head);
    cout << "===============" << endl;
    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    insertEnd(&head, 10);
    insertEnd(&head, 15);
    displayList (head);
    cout << "===============" << endl;


    return 0;
}

Node* createNode(int iPayload){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> iPayload = iPayload;
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    return temp;
};

void displayList(Node* node)
{
    // Imprimimos que a lista está vazia
    if (node == nullptr){
        cout << "A lista esta vazia" << endl;
        return;
    }
    // Se não recebemos o head, não printamos
    if (node -> ptrPrev != nullptr){
        cout << "Meio ou fim da lista : não é possível realizar o display list" << endl;
        return;
    }
    Node* temp = node;
    
    cout << "Payload: ";
    // Percorremos a lista até seu fim
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    cout << " " << endl;
    return;
};

void insertFront(Node** head , int iPayload ){
    Node* newNode = createNode(iPayload);
    // newNode->ptrPrev = nullptr;

    // Quando tivermos algo na lista
    if (*head != nullptr)
    {
        // Colocando o antes do atual head como new node
        (*head) -> ptrPrev = newNode;
        // Colocando o next do new node como head
        newNode -> ptrNext = (*head);
        // Colocando o head como new node
        (*head) = newNode; 

        return;
    }
    else 
    {
        // Basta setar
        (*head) = newNode; 
    }


}; // Todo;

void insertEnd(Node** head, int iPayload){
    Node* newNode = createNode(iPayload);
    // NewNode->ptrNext = nullptr;

    if (*head == nullptr)
    {
        // NewNode->ptrPrev = nullptr;

        // Derreferenciando um ponteiro
        (*head) = newNode;
        return;
    }

    Node* temp = (*head);

    // Percorremos a lista até seu fim
    while (temp -> ptrNext != nullptr)
    {
        // Vai para frente até ser nulo (último nó)
        temp = temp->ptrNext;
    }

    newNode -> ptrPrev = temp; // newNode aponta para o fim da lista
    temp -> ptrNext = newNode; // Antigo último elemento aponto para o ultimo nó
    return;
};

// Exercício 1. Elaborar a função void método insertBefore(Node*, int);
// Exercício 2. Elaborar a função void deleteNodebyValue(Node**, int);
// Exercício 3. Elaborar a função Node* searchNodebyValue(Node**, int);




void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "O no escolhido e nulo. Impossivel inserir" << endl;
        return;
    }
    else 
    {
        Node* newNode = createNode(iPayload);
        
        // Corrigir o nó a ser inserido
        newNode->ptrNext = ptrLocation -> ptrNext;
        newNode -> ptrPrev = ptrLocation;

        // Corrigir a lista
        ptrLocation -> ptrNext = newNode;

        // Checando se ele aponta para nulo
        if (newNode -> ptrNext != nullptr)
        {
            newNode -> ptrNext -> ptrPrev = newNode;

        }
    }
};

void deleteNode (Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Nao e possivel remover pois algum elemento e nulo" << endl;
        return;
    }

    // Caso o ptrDelete seja o primeiro elemento da lista
    if ((*head) == ptrDelete)
    {
        (*head) = ptrDelete-> ptrNext;
    }

    // Se o ptrDelete não é o ultimo nó
    if (ptrDelete -> ptrNext != nullptr) ptrDelete -> ptrNext -> ptrPrev = ptrDelete -> ptrPrev;

    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete -> ptrPrev != nullptr) ptrDelete -> ptrNext -> ptrNext = ptrDelete -> ptrNext;

    free(ptrDelete);
};

void insertBefore(Node* node, int iPayload)
{
    if (node == nullptr)
    {
        cout << "Nó não pode ser inserido." << endl;
    }
    else if (node -> ptrPrev == nullptr)
    {
        insertFront(node*, iPayload);
    }
    else
    {
        Node* newNode = createNode(iPayload);
        newNode -> ptrNext = node;
        newNode -> ptrPrev = node -> ptrPrev;
        node -> ptrPrev = newNode;
        node -> ptrPrev -> ptrNext = newNode;
    }
}
