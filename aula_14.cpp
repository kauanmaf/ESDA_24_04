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
Node* searchNodebyValue(Node**, int);

int main()
{
    Node* head1 = nullptr;
    displayList(head1);
    cout << "===============" << endl;
    insertEnd(&head1, 0);
    insertEnd(&head1, 2);
    insertEnd(&head1, 4);
    insertEnd(&head1, 6);
    // Testando se a inserção ao fim 
    displayList(head1);
    insertFront(&head1, 8);
    insertFront(&head1, 8);
    // Testando a inserção ao começo
    displayList(head1);
    cout << "===============" << endl;

    // Testando a inserção depois de um valor 

    // Testando a inserção depois do primeiro
    insertAfter(head1, 5);

    // Testando depois de algum qualquer
    insertAfter(head1->ptrNext, 5);

    // Testando a insercção depois do ultimo
    Node* ptrCurrent1 = head1;
    while (ptrCurrent1->ptrNext != nullptr) ptrCurrent1 = ptrCurrent1 -> ptrNext;
    insertAfter (ptrCurrent1, 5);
    
    displayList(head1);

    cout << "===============" << endl;

    // Testando a inserção antes do primeiro
    // cout << head1 << endl;
    // insertBefore(head1, 7);
    // cout << head1 << endl;

    displayList(head1);

    // Testando antes de algum qualquer
    insertBefore(head1->ptrNext, 7);
    displayList(head1);

    // Testando a insercção antes do ultimo
    Node* ptrCurrent2 = head1;
    while (ptrCurrent2->ptrNext != nullptr) ptrCurrent2 = ptrCurrent2 -> ptrNext;
    insertBefore (ptrCurrent2, 7);
    
    displayList(head1);

    cout << "===============" << endl;
    // Testando o deleteNode;
    cout << head1 << endl;
    deleteNode (&head1, head1);
    cout << head1 << endl;
    
    displayList(head1);

    cout << "===============" << endl;

    Node* valor_8 = searchNodebyValue(&head1, 8);
    cout << "Elemento " << valor_8 -> iPayload << " na localizacao " << valor_8  << endl;

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
        cout << node-> iPayload << endl;
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
    newNode->ptrPrev = nullptr;

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


};

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
        // Precisamos definir o anterior como nullptr
        (*head)->ptrPrev = nullptr; 
    }

    // Se o ptrDelete não é o ultimo nó
    if (ptrDelete -> ptrNext != nullptr) ptrDelete -> ptrNext -> ptrPrev = ptrDelete -> ptrPrev;

    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrPrev != nullptr) ptrDelete -> ptrPrev -> ptrNext = ptrDelete -> ptrNext;

    free(ptrDelete);
};

void insertBefore(Node* node, int iPayload)
{
    if (node == nullptr)
    {
        cout << "Nó não pode ser inserido." << endl;
        return;
    }
    else if (node->ptrPrev == nullptr)
    {
        insertFront(&node, iPayload);
        return;
    }
    else
    {
        // Criando o nó
        Node* newNode = createNode(iPayload);

        newNode->ptrNext = node;
        newNode->ptrPrev = node->ptrPrev;
        node->ptrPrev = newNode;
        newNode->ptrPrev->ptrNext = newNode;
        return;
    }
}

Node* searchNodebyValue(Node** head, int iValue){
    if ((*head) == nullptr)
    {
        cout << "Nao e possivel encontrar o no. ponteiro nulo" << endl;
        return nullptr;
    }
    // Setamos um ponteiro como 
    Node* ptrCurrent = (*head);

    // Enquanto não for nulo (chegarmos ao final)
    while(ptrCurrent != nullptr)
    {
        // Checamos se o valor do payload é igual ao valor que estamos procurando 
        if (ptrCurrent -> iPayload == iValue)
        {
            // Retornamos o primeiro current que achamos
            return ptrCurrent;
        }

        // Setamos o current como o próximo
        ptrCurrent = ptrCurrent -> ptrNext;
    }

    // Se sairmos do while significa que não encontramos o valor
    cout << "Valor nao encontrado" << endl;
    return nullptr; 

};