#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//estrutura do contato
typedef struct contato{
    struct contato *anterior;
    struct contato *proximo;
    char nome[50];
    char telefone[20];
    char email[50];
    char endereco[100];
} Contato;

//estrutura da agenda
typedef struct deque{
    Contato *inicio, *fim;
} Deque;

//função para inicializar a agenda
void inicializar(Deque *deque) {
    deque->inicio = deque->fim = NULL;
}

//função para adicionar no inicio da agenda
void adicionarInicio(Deque *deque, Contato *contato) {
    contato->proximo = deque->inicio;
    contato->anterior = NULL;
    if (deque->inicio != NULL) {
        deque->inicio->anterior = contato;
    }
    deque->inicio = contato;
    if (deque->fim == NULL) {
        deque->fim = contato;
    }
}
//função para adicionar no fim da agenda
void adicionarFim(Deque *deque, Contato *contato) {
    contato->anterior = deque->fim;
    contato->proximo = NULL;
    if (deque->fim != NULL) {
        deque->fim->proximo = contato;
    }
    deque->fim = contato;
    if (deque->inicio == NULL) {
        deque->inicio = contato;
    }
}
//função para remover do inicio da agenda se necessário
//ela realoca o ponteiro do inicio para o proximo contato
//e o ponteiro do anterior do proximo contato para NULL(Antigo inicio)
Contato* removerInicio(Deque *deque) {
    if (deque->inicio == NULL) {
        return NULL;
    }
    Contato *contato = deque->inicio;
    deque->inicio = deque->inicio->proximo;
    if (deque->inicio != NULL) {
        deque->inicio->anterior = NULL;
    } else {
        deque->fim = NULL;
    }
    return contato;
}
//função para remover do fim da agenda se necessário
//ela realoca o ponteiro do fim para o contato anterior
//e o ponteiro do proximo do contato anterior para NULL(Antigo fim)
Contato* removerFim(Deque *deque) {
    if (deque->fim == NULL) {
        return NULL;
    }
    Contato *contato = deque->fim;
    deque->fim = deque->fim->anterior;
    if (deque->fim != NULL) {
        deque->fim->proximo = NULL;
    } else {
        deque->inicio = NULL;
    }
    return contato;
}
//função basica p adicionar um contato
void adicionarContato(Deque *deque) {
    Contato *contato = malloc(sizeof(Contato));
    printf("\n\n--- Adicionar Contatos ---\n");
    printf("\nDigite o nome do contato: ");
    fgets(contato->nome, sizeof(contato->nome), stdin);
    contato->nome[strcspn(contato->nome, "\n")] = 0;

    printf("Digite o telefone do contato: ");
    fgets(contato->telefone, sizeof(contato->telefone), stdin);
    contato->telefone[strcspn(contato->telefone, "\n")] = 0;

    printf("Digite o email do contato: ");
    fgets(contato->email, sizeof(contato->email), stdin);
    contato->email[strcspn(contato->email, "\n")] = 0;

    printf("Digite o endereco do contato: ");
    fgets(contato->endereco, sizeof(contato->endereco), stdin);
    contato->endereco[strcspn(contato->endereco, "\n")] = 0;

    adicionarFim(deque, contato);
}

void imprimirContatos(Deque *deque) {
    Contato *contato = deque->inicio;
        printf("\n\n--- Lista de Contatos ---\n");
    while (contato != NULL) {
        printf("Nome: %s\n", contato->nome);
        printf("Telefone: %s\n", contato->telefone);
        printf("Email: %s\n", contato->email);
        printf("Endereco: %s\n", contato->endereco);
        printf("\n");
        contato = contato->proximo;
    }
}
void removerContato(Deque *deque) {
    Contato *contato = removerInicio(deque);
    if (contato != NULL) {
        printf("Removido o contato %s\n", contato->nome);
        free(contato);
    } else {
        printf("A agenda de contatos ja esta vazia.\n");
    }
}

void editarContato(Deque *deque){
    char contatoBusca[1000];
    int escolhaMenu;
    Contato *contato = deque->inicio;

    if (contato==NULL){
        printf("\nA lista de contatos esta vazia. Tente Novamente.\n");
        return;
    }
    imprimirContatos(deque);

    printf("\nDigite o nome do contato que deseja editar: ");
    fgets(contatoBusca, sizeof(contatoBusca), stdin);
    contatoBusca[strcspn(contatoBusca, "\n")] = 0;

    while (contato != NULL) {
        if (strcmp(contato->nome, contatoBusca) == 0) {
            printf("Contato encontrado!\n");
            printf("Escolha uma das opcoes abaixo:\n1. Editar Nome\n2. Editar Telefone\n3. Editar Email\n4. Editar Endereco\n");
            scanf("%d", &escolhaMenu);
            getchar();

            switch (escolhaMenu) {
            case 1:
                printf("\nNome Atual: %s\n", contato->nome);
                printf("\nDigite o novo nome do contato: ");
                fgets(contato->nome, sizeof(contato->nome), stdin);
                contato->nome[strcspn(contato->nome, "\n")] = 0;
                printf("\nAlteracao concluida com sucesso!\n");
                return;
                break;
            case 2:
                printf("\nTelefone Atual: %s\n", contato->telefone);
                printf("\nDigite o novo telefone do contato: ");
                fgets(contato->telefone, sizeof(contato->telefone), stdin);
                contato->telefone[strcspn(contato->telefone, "\n")] = 0;
                break;
            case 3:
                printf("\nEmail Atual: %s\n", contato->email);
                printf("\nDigite o novo email do contato: ");
                fgets(contato->email, sizeof(contato->email), stdin);
                contato->email[strcspn(contato->email, "\n")] = 0;
                break;
            case 4:
                printf("\nEndereço Atual: %s\n", contato->endereco);
                printf("\nDigite o novo endereco do contato: ");
                fgets(contato->endereco, sizeof(contato->endereco), stdin);
                contato->endereco[strcspn(contato->endereco, "\n")] = 0;
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
            }
        }
        else{  
        printf("Contato não encontrado.\n");
    }                                        
        contato = contato->proximo;         
    }

    
}

int main() {
    Deque agenda;
    inicializar(&agenda);

    int opcao;
    do {
        printf("--- Agenda de Contatos ---");
        printf("\n1. Adicionar contato\n");
        printf("2. Imprimir contatos\n");
        printf("3. Remover contato\n");
        printf("4. Editar contato\n");
        printf("5. Sair\n\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);
        getchar(); // Para consumir o '\n' deixado por scanf

        switch (opcao) {
            case 1:
                adicionarContato(&agenda);
                break;
            case 2:
                imprimirContatos(&agenda);
                break;
            case 3:
                removerContato(&agenda);
                break;
            case 4:
                editarContato(&agenda);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}