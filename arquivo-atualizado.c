#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#define TAMANHO_MAX 200

//estrutura do contato
typedef struct contato{
    struct contato *anterior;
    struct contato *proximo;
    int ID;
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

    int maiorid = 0;
    // declarar a variável ponteiro e inicializar ela com o endereço do primeiro do deque
    Contato *atual = deque->inicio;
    //percorre o deque para encontrar o maior id até o momento
    while (atual != NULL)
    {
        if (atual->ID > maiorid)
        {
            maiorid = atual->ID;
        }
        atual = atual->proximo;

    }

    contato->ID = maiorid + 1;

    printf("\n\n========================");
    printf("\n   ADICIONAR CONTATOS\n");
    printf("========================\n");

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
    FILE *arquivo;
    arquivo = fopen("contatos.csv","a");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "%d,%s,%s,%s,%s\n", contato->ID, contato->nome, contato->telefone, contato->email, contato->endereco);
    fclose(arquivo);
}
//função para criar um arquivo csv
void criarArquivocsv(){
    FILE *arquivo = fopen("contatos.csv","r");
    if(arquivo != NULL){
        fclose(arquivo);
        printf("O arquivo csv já existe, então não é necessário criar um novo.\n");
        return;
    }
    arquivo = fopen("contatos.csv","w");
    if (arquivo == NULL){
        printf("Erro ao criar o arquivo csv.\n");
        return;
    }
    fprintf(arquivo,"ID, Nome ,Telefone ,Email ,Endereco\n");

    fclose(arquivo);
    printf("Arquivo csv criado com sucesso.\n");
}

void imprimirContatos(Deque *deque) {
    Contato *contato = deque->inicio;
        printf("\n\n    ==============================");
        printf("\n           LISTA DE CONTATOS  \n");
        printf("    ==============================\n\n");
        printf("Nome     Número     Endereço     Email\n");
        printf("=======================================\n");
    while (contato != NULL) {
        printf("ID: %d",contato->ID);
        printf("\nNome: %s\n", contato->nome);
        printf("Telefone: %s\n", contato->telefone);
        printf("Email: %s\n", contato->email);
        printf("Endereco: %s\n", contato->endereco);
        printf("=======================================\n");
        contato = contato->proximo;
    }
}

void buscarContato(Deque *deque) {
  char contatoBusca[1000];
//   int escolhaMenu;
  Contato *contato = deque->inicio;

  if (contato==NULL){
      printf("\nA lista de contatos esta vazia. Tente Novamente.\n");
      return;
  }

  printf("\n\n=============================================");
  printf("\nDigite o nome do contato que deseja procurar: ");
  fgets(contatoBusca, sizeof(contatoBusca), stdin);
  contatoBusca[strcspn(contatoBusca, "\n")] = 0;

  if (strcmp(contato->nome, contatoBusca) == 0) {
          printf("\nContato encontrado!\n\n");
            printf("\n\n    ==============================");
            printf("\n              CONTATO %s  \n", contato->nome);
            printf("    ==============================\n\n");
            printf("ID     Nome     Número     Endereço     Email\n");
            printf("=======================================\n");
            printf("\nID: %d",contato->ID);
            printf("\nNome: %s", contato->nome);
            printf("\nTelefone: %s", contato->telefone);
            printf("\nEmail: %s", contato->email);
            printf("\nEndereço: %s", contato->endereco);
            printf("\n=======================================\n");
          }

        else{  
        printf("Contato não encontrado.\n");
      }                                              
}
void removerContato(Deque *deque, int id) {
    //armazena o contato que erá removido
    Contato *contatoRemovido = NULL;
    //criei um ponteiro para o contato atual que esta no deque
    Contato *atual = deque->inicio;
    //criei outro ponteiro para o anterior ao atual
    Contato *anterior = NULL;

    // Lista encadeada para armazenar contatos não removidos
    Contato *contatosNaoRemovidos = NULL;
    //ponteiro para o ultimo contato para adicionar contatos no final
    Contato *ultimoContato = NULL;

    // para encontrar o contato no deque pelo ID
    while (atual != NULL && atual->ID != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    // remove o contato no deque
    if (atual != NULL) {
        if (anterior != NULL) {
            anterior->proximo = atual->proximo;
        } else {
            deque->inicio = atual->proximo;
        }

        if (atual == deque->fim) {
            deque->fim = anterior;
        }

        contatoRemovido = atual;
        //checagem
        printf("Contato com ID %d removido do deque com sucesso!\n", id);

    } else {//checagem 
        printf("Contato com ID %d não encontrado no deque.\n", id);
        return;
    }

    //leitura do arquivo
    FILE *arquivo = fopen("contatos.csv", "r");
    if (arquivo == NULL) {//checagem
        printf("Erro em abrir o arquivo.\n");
        return;
    }

    char linha[512];
    //para indicar se o cabecalho esta na primeira linha!
    int cabecalho = 1;
    // le uma linha inteira do arquivo, até encontrar uma quebra de linha ou o fim do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (cabecalho) {
            // Mantém o cabeçalho
            cabecalho = 0;
        } else {
            // cria um novo contato e preenche com os dados da linha
            Contato *novoContato = malloc(sizeof(Contato));
            sscanf(linha, "%d,%[^,],%[^,],%[^,],%[^\n]", &novoContato->ID, novoContato->nome, novoContato->telefone, novoContato->email, novoContato->endereco);

            // Compara os IDs para ver se o id no novo é diferente do id que quer remover
            if (novoContato->ID != id) {
                // Se não é o ID que queremos remover, adiciona a lista encadeada
                novoContato->proximo = NULL;
                if (contatosNaoRemovidos == NULL) {
                    contatosNaoRemovidos = novoContato;
                    ultimoContato = novoContato;
                } else {
                    ultimoContato->proximo = novoContato;
                    ultimoContato = novoContato;
                }
            }
        }
    }

    fclose(arquivo);

    // Abre o arquivo para escrever
    arquivo = fopen("contatos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro em abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o cabeçalho no arquivo
    fprintf(arquivo, "ID,Nome,Telefone,Email,Endereco\n");

    // Escreve os contatos não removidos no arquivo
    Contato *temp = contatosNaoRemovidos;
    //para escrever todos os contatos na lista sem o q removeu 
    while (temp != NULL) {
        fprintf(arquivo, "%d,%s,%s,%s,%s\n", temp->ID, temp->nome, temp->telefone, temp->email, temp->endereco);
        Contato *proximo = temp->proximo;
        free(temp); // Libera a memória do contato
        temp = proximo;
    }

    fclose(arquivo);

    printf("Contato com ID %d removido do arquivo com sucesso!\n", id);
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
            printf("\nContato encontrado!\n\n");
            printf("==============================\nEscolha uma das opcoes abaixo:\n==============================\n1. Editar Nome\n2. Editar Telefone\n3. Editar Email\n4. Editar Endereco\n-> ");
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
// Função para editar um contato na deque
void editarContatoNaDeque(Deque *deque, Contato *contato) {
    int escolhaMenu;

    printf("==============================\nEscolha uma das opções abaixo:\n==============================\n");
    printf("1. Editar Nome\n2. Editar Telefone\n3. Editar Email\n-> ");
    scanf("%d", &escolhaMenu);
    getchar(); // Consumir o '\n' deixado por scanf

    switch (escolhaMenu) {
        case 1:
            printf("\nNome Atual: %s\n", contato->nome);
            printf("Digite o novo nome do contato: ");
            fgets(contato->nome, sizeof(contato->nome), stdin);
            contato->nome[strcspn(contato->nome, "\n")] = 0;
            printf("\nAlteração do Nome concluída com sucesso!\n");
            break;
        case 2:
            printf("\nTelefone Atual: %s\n", contato->telefone);
            printf("Digite o novo telefone do contato: ");
            fgets(contato->telefone, sizeof(contato->telefone), stdin);
            contato->telefone[strcspn(contato->telefone, "\n")] = 0;
            printf("\nAlteração do Telefone concluída com sucesso!\n");
            break;
        case 3:
            printf("\nEmail Atual: %s\n", contato->email);
            printf("Digite o novo email do contato: ");
            fgets(contato->email, sizeof(contato->email), stdin);
            contato->email[strcspn(contato->email, "\n")] = 0;
            printf("\nAlteração do Email concluída com sucesso!\n");
            break;
        default:
            printf("\nOpção inválida!\n");
            return;
    }
}
void editarContatos(Deque *deque) {
    char contatoBusca[1000];
    Contato *contato = deque->inicio;

    if (contato == NULL) {
        printf("\nA lista de contatos está vazia. Tente novamente.\n");
        return;
    }

    imprimirContatos(deque);

    printf("\nDigite o nome do contato que deseja editar: ");
    fgets(contatoBusca, sizeof(contatoBusca), stdin);
    contatoBusca[strcspn(contatoBusca, "\n")] = 0;

    while (contato != NULL) {
        if (strcmp(contato->nome, contatoBusca) == 0) {
            printf("\nContato encontrado!\n\n");
            editarContatoNaDeque(deque, contato);

            // Atualizar as informações no arquivo CSV (chamando a função atualizarCSV)
            // atualizarCSV(deque);

            return; // Contato encontrado e editado, encerra a função
        }
        contato = contato->proximo;
    }

    printf("Contato não encontrado.\n");
}






int main() {
    Deque agenda;
    inicializar(&agenda);
    criarArquivocsv();
    int opcao;
    int idcontato;
    do {
        printf("\n\n    AGENDA DE CONTATOS\n");
        printf("=========================");
        printf("\n[1] Adicionar contato\n");
        printf("[2] Listar contatos\n");
        printf("[3] Buscar contato\n");
        printf("[4] Remover contato\n");
        printf("[5] Editar contato\n");
        printf("[6] Sair\n");
        printf("=========================\n");
        printf("Insira escolha: ");
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
                buscarContato(&agenda);
                break;
            case 4:
                imprimirContatos(&agenda);
                printf("Insira o ID do contato para remover: ");
                scanf("%d", &idcontato);
                removerContato(&agenda, idcontato);
                break;
            case 5:
                editarContato(&agenda);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}
