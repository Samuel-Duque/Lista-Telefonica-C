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
    int id;
    int tamanho;
} Contato;

//estrutura da agenda
typedef struct deque{
    Contato *inicio, *fim;
    int tamanho;
} Deque;

//função para inicializar a agenda
void inicializar(Deque *deque) {
    deque->inicio = deque->fim = NULL;
    deque->tamanho=0;
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

int tamanhodeque(Deque *deque){
    return deque->tamanho;
    }
    

void inserirCSV(Deque *deque){
    int contador = 0;
    Contato *contato= deque->inicio;
    FILE *arquivo;
    arquivo = fopen("arquivo.csv","a");
    fprintf(arquivo,"Nome,Telefone,Endereco,E-mail,id\n");
    printf("%d",tamanhodeque(deque));
    while (contador < tamanhodeque(deque)){
    fprintf(arquivo,"%s,%s,%s,%s,%d\n",contato->nome,contato->telefone,contato->endereco,contato->email,contato->id);
    contador++;
    deque++;
    }
    fclose(arquivo);

}

void criararquivo(){
    FILE *arquivo;
    arquivo = fopen("arquivo.csv","a");
    fprintf(arquivo,"Nome,Telefone,Endereco,E-mail,id\n");
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

    contato->id = tamanhodeque(deque);
    adicionarFim(deque, contato);
    deque->tamanho++;
    FILE *arquivo;
    arquivo = fopen("arquivo.csv","a");
    fprintf(arquivo,"%s,%s,%s,%s,%d\n",contato->nome,contato->telefone,contato->endereco,contato->email,contato->id);
    fclose(arquivo);
    
}

void imprimirContatos(Deque *deque) {
    Contato *contato = deque->inicio;
        printf("\n\n--- Lista de Contatos ---\n");
    while (contato != NULL) {
        printf("Nome: %s\n", contato->nome);
        printf("Telefone: %s\n", contato->telefone);
        printf("Email: %s\n", contato->email);
        printf("Endereco: %s\n", contato->endereco);
        printf("ID: %d\n", contato->id);
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
void removerContatoPorId(Deque *deque, int id) {
    if (deque->inicio == NULL) {
        printf("A agenda esta vazia.\n");
        return;
    }

    Contato *contatoAtual = deque->inicio;
    while (contatoAtual != NULL) {
        if (contatoAtual->id == id-1) {
            // Se o contato é o primeiro da lista
            if (contatoAtual->anterior == NULL) {
                deque->inicio = contatoAtual->proximo;
            } else {
                contatoAtual->anterior->proximo = contatoAtual->proximo;
            }

            // Se o contato é o último da lista
            if (contatoAtual->proximo == NULL) {
                deque->fim = contatoAtual->anterior;
            } else {
                contatoAtual->proximo->anterior = contatoAtual->anterior;
            }

            free(contatoAtual);
            printf("Contato com ID %d removido.\n", id);
            return;
        }
        contatoAtual = contatoAtual->proximo;
    }
    deque->tamanho--;
    printf("Contato com ID %d nao encontrado.\n", id);
}

int main() {
    Deque agenda;
    inicializar(&agenda);
    criararquivo();
    int opcao;
    int escolhaid;
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
                // inserirCSV(&agenda);
                break;
            case 2:
                imprimirContatos(&agenda);

                break;
            case 3:
                printf("Escolha o ID do contato que deseja remover: ");
                scanf("%d", &escolhaid);
                removerContatoPorId(&agenda, escolhaid);
                
                break;
            case 4:
                inserirCSV(&agenda);
                editarContato(&agenda);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            case 6:
                tamanhodeque(&agenda);
                printf("%d",tamanhodeque(&agenda));
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 5);

    return 0;
}
    
