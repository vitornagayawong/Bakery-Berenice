#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int codigo;
    char nome[26];
    float precoUnit;
    int quantEstoque;
    int totalQtdVendida;
} Produto;

typedef struct
{
    char nomeItemVendidoNaEpoca[26];
    int codigoDoProdVendido;
    float precoNaEpoca;
    int qtdVendidaNaEpoca;
    float subtotal;
} Venda;

void exibir_estoque(Produto **prod, int *quant_prod_ja_cadast, int *numVendas);
void cadastrar(Produto **prod, int *quant_prod_ja_cadast);
int validarCodigo(Produto **prod, int num, int *quant_prod_ja_cadast);
void editar_produto(Produto **prod, int *quant_prod_ja_cadast);
void excluir_produto(Produto **prod, int *quant_prod_ja_cadast);
void salvar_txt(Produto **prod, int *quant_prod_ja_cadast, char arq[]);
void ler_txt(Produto **prod, int *quant_prod_ja_cadast, char arq[]);
void vender(Produto **prod, int *quant_prod_ja_cadast, int *numVendas, Venda **vendaRealizada);
void relatorioVendas(Produto **prod, int *quant_prod_ja_cadast, int *numVendas);
void salvarBin(Produto **prod, int *quant_prod_ja_cadast, char arq[]);
int lerBin(Produto **prod, char arq[]);
void bubbleSort(Venda **vendaRealizada, int *numVendas);

//void menuProdutos(Produto **prod, int *quant_prod_ja_cadast, char arquivo[], char aquivoBin[]);
//void menuVendas(Produto **prod, int *quant_prod_ja_cadast, int *numVendas, Venda **vendaRealizada);

void salvar_csv(Produto **prod, int *quant_prod_ja_cadast);

int main()
{
    Produto *prod[0];

    Venda *vendaRealizada;

    char arquivo[] = {"produtos.txt"};
    char arquivoBin[] = {"produtos.dat"};

    int quant_prod_ja_cadast = 0, numVendas = 0, opcaoMenuPrincipal;
    int menuProd, menuVendas;

    printf("\n\n");
    printf("\t\t\t********************************************\n");
    printf("\t\t\t*****BEM-VINDO(A) A PADARIA DA BERENICE*****\n");
    printf("\t\t\t********************************************\n\n\n");

    do
    {
        printf("\n--------------\n");
        printf("MENU PRINCIPAL");
        printf("\n--------------");

        printf("\nEscolha a opcao:\n1 - Produtos\n2 - Vendas\n3 - Sair\n\n");
        scanf("%d", &opcaoMenuPrincipal);
        getchar();

        if(opcaoMenuPrincipal != 1 && opcaoMenuPrincipal != 2 && opcaoMenuPrincipal != 3)
        {
            printf("\nOpcao invalida!\n");
            continue;
        }

        switch(opcaoMenuPrincipal)
        {
        case 1:
            //menuProdutos(prod, &quant_prod_ja_cadast, arquivo, arquivoBin);
            //opcaoMenuPrincipal = 4;
            //printf("OPCAO MENU PRINCIPAL %d", opcaoMenuPrincipal);

            do
            {
                printf("\n------------------\n");
                printf("Sub-Menu Produtos");
                printf("\n------------------");

                printf("\nEscolha a opcao:\n1 - Exibir estoque\n2 - Cadastrar produto\n3 - Atualizar produto\n4 - Excluir produto\n5 - Salvar arquivo\n6 - Ler arquivo\n7 - Salvar Binario\n8 - Ler Binario\n9 - Salvar csv\n10 - Voltar\n");
                scanf("%d", &menuProd);
                getchar();

                switch(menuProd)
                {
                case 1:
                    exibir_estoque(prod, &quant_prod_ja_cadast, &numVendas);
                    break;
                case 2:
                    cadastrar(prod, &quant_prod_ja_cadast);
                    break;
                case 3:
                    exibir_estoque(prod, &quant_prod_ja_cadast, &numVendas);
                    editar_produto(prod, &quant_prod_ja_cadast);
                    break;
                case 4:
                    exibir_estoque(prod, &quant_prod_ja_cadast, &numVendas);
                    excluir_produto(prod, &quant_prod_ja_cadast);
                    exibir_estoque(prod, &quant_prod_ja_cadast, &numVendas);
                    break;
                case 5:
                    salvar_txt(prod, &quant_prod_ja_cadast, arquivo);
                    break;
                case 6:
                    ler_txt(prod, &quant_prod_ja_cadast, arquivo);
                    break;
                case 7:
                    salvarBin(prod, &quant_prod_ja_cadast, arquivoBin);
                    break;
                case 8:
                    quant_prod_ja_cadast = lerBin(prod, arquivoBin);
                    break;
                case 9:
                    salvar_csv(prod, &quant_prod_ja_cadast);
                    break;
                case 10:
                    printf("\nVoltando ao menu principal...\n");
                    opcaoMenuPrincipal = 4;
                    break;
                default:
                    printf("\nOpcao invalida. Entre com 1 a 7...\n");
                    menuProd = 1;
                }
            }
            while(menuProd == 1 || menuProd == 2 || menuProd == 3 || menuProd == 4 || menuProd == 5 || menuProd == 6 || menuProd == 7 || menuProd == 8 || menuProd == 9);

            break;
        case 2:
            //menuVendas(prod, &quant_prod_ja_cadast, &numVendas, vendaRealizada);
            //opcaoMenuPrincipal = 4;

            do
            {
                printf("\n------------------\n");
                printf("Sub-Menu Vendas");
                printf("\n------------------");

                printf("\nEscolha a opcao:\n1 - Realizar venda\n2 - Relatorio de vendas\n3 - Voltar\n");
                scanf("%d", &menuVendas);
                switch(menuVendas)
                {
                case 1:
                    exibir_estoque(prod, &quant_prod_ja_cadast, &numVendas);
                    vender(prod, &quant_prod_ja_cadast, &numVendas, vendaRealizada);
                    break;
                case 2:
                    relatorioVendas(prod, &quant_prod_ja_cadast, &numVendas);
                    break;
                case 3:
                    printf("\nVoltando ao menu principal...\n");
                    opcaoMenuPrincipal = 4;
                    break;
                default:
                    printf("\nOpcao invalida. Entre com 1 a 3...\n");
                    menuVendas = 1;
                }
            }
            while(menuVendas == 1 || menuVendas == 2);

            break;
        case 3:
            exit(0);
            break;
        }
    }
    while(opcaoMenuPrincipal != 1 && opcaoMenuPrincipal != 2 && opcaoMenuPrincipal != 3);


    return 0;
}
/*
void menuProdutos(Produto **prod, int *quant_prod_ja_cadast, char arquivo[], char arquivoBin[])
{
    int menuProd = 0;

    do
    {
        printf("\n------------------\n");
        printf("Sub-Menu Produtos");
        printf("\n------------------");

        printf("\nEscolha a opcao:\n1 - Exibir estoque\n2 - Cadastrar produto\n3 - Atualizar produto\n4 - Excluir produto\n5 - Salvar arquivo\n6 - Ler arquivo\n7 - Salvar Binario\n8 - Ler Binario\n9 - Voltar\n");
        scanf("%d", &menuProd);
        getchar();

        switch(menuProd)
        {
        case 1:
            exibir_estoque(prod, quant_prod_ja_cadast);
            break;
        case 2:
            cadastrar(prod, quant_prod_ja_cadast);
            break;
        case 3:
            exibir_estoque(prod, quant_prod_ja_cadast);
            editar_produto(prod, quant_prod_ja_cadast);
            break;
        case 4:
            exibir_estoque(prod, quant_prod_ja_cadast);
            excluir_produto(prod, quant_prod_ja_cadast);
            exibir_estoque(prod, quant_prod_ja_cadast);
            break;
        case 5:
            salvar_txt(prod, quant_prod_ja_cadast, arquivo);
            break;
        case 6:
            ler_txt(prod,quant_prod_ja_cadast, arquivo);
            break;
        case 7:
            salvarBin(prod, quant_prod_ja_cadast, arquivoBin);
            break;
        case 8:
            quant_prod_ja_cadast = lerBin(prod, arquivoBin);
            break;
        case 9:
            printf("\nVoltando ao menu principal...\n");
            //opcaoMenuPrincipal = 9;
            menuProd == 15;
            //printf("MENUPROD %d", menuProd);
            break;
        default:
            printf("\nOpcao invalida. Entre com 1 a 7...\n");
            menuProd = 1;
        }
    }
    while(menuProd == 1 || menuProd == 2 || menuProd == 3 || menuProd == 4 || menuProd == 5 || menuProd == 6 || menuProd == 7 || menuProd == 8);
}

void menuVendas(Produto **prod, int *quant_prod_ja_cadast, int *numVendas, Venda **vendaRealizada)
{
    int menuVendas;

    do
    {
        printf("\n------------------\n");
        printf("Sub-Menu Vendas");
        printf("\n------------------");

        printf("\nEscolha a opcao:\n1 - Realizar venda\n2 - Relatorio de vendas\n3 - Voltar\n");
        scanf("%d", &menuVendas);
        switch(menuVendas)
        {
        case 1:
            exibir_estoque(prod, quant_prod_ja_cadast);
            vender(prod, quant_prod_ja_cadast, numVendas, vendaRealizada);
            break;
        case 2:
            relatorioVendas(prod, quant_prod_ja_cadast);
            break;
        case 3:
            printf("\nVoltando ao menu principal...\n");
            menuVendas = 4;
            break;
        default:
            printf("\nOpcao invalida. Entre com 1 a 3...\n");
            menuVendas = 1;
        }
    }
    while(menuVendas == 1 || menuVendas == 2);
}
*/
void exibir_estoque(Produto **prod, int *quant_prod_ja_cadast, int *numVendas)
{
    int troca, i;
    //float copia_venda_subtotal;
    int copia_codigo;
    char copia_nome_ordenado[26];
    float copia_valor_unit;
    int copia_qtd_estoque;
    //int copia_quant_vendida;

    printf("\t               ----------------------                                    \n");
    printf("\t               ***ITENS DE ESTOQUE***                                    \n");
    printf("\t               ----------------------                                    \n");
    printf("\n");
    printf("\t-----------------------------------------------------------------------------------\n");
    printf("\t   ITEM(codigo)  |\t     Nome do item     \t|  Valor(Unidade)\t|  Estoque\n");
    printf("\t-----------------------------------------------------------------------------------\n");

    ///BUBBLE SORT
    do
    {
        troca = 0; //variável troca começando sempre em 0

        //se a berenice tiver feito 1 venda, o indice_de_venda será 1... e assim por diante
        for(i = 0; i < *quant_prod_ja_cadast - 1; i++)
        {
            //compara a casa da esquerda com a casa da direita do vetor venda.
            //se eu trocar < por > o programa irá ordenar os preços de forma crescente (e não descrente como está no programa!)
            if(prod[i]->codigo < prod[i + 1]->codigo)
            {
                /*
                ///Ordenando o atributo subtotal
                copia_venda_subtotal = vendaRealizada[i + 1]->subtotal;
                vendaRealizada[i + 1]->subtotal = vendaRealizada[i]->subtotal;
                vendaRealizada[i]->subtotal = copia_venda_subtotal;
                */

                ///Ordenando o atributo codigo
                copia_codigo = prod[i]->codigo;
                prod[i]->codigo = prod[i + 1]->codigo;
                prod[i + 1]->codigo = copia_codigo;

                ///Ordenando o atributo nome
                strcpy(copia_nome_ordenado, prod[i]->nome);
                strcpy(prod[i]->nome, prod[i + 1]->nome);
                strcpy(prod[i + 1]->nome, copia_nome_ordenado);


                ///Ordenando o atributo precoUnit
                copia_valor_unit = prod[i]->precoUnit;
                prod[i]->precoUnit = prod[i + 1]->precoUnit;
                prod[i + 1]->precoUnit = copia_valor_unit;


                ///Ordenando o quantEstoque
                copia_qtd_estoque = prod[i]->quantEstoque;
                prod[i]->quantEstoque = prod[i + 1]->quantEstoque;
                prod[i + 1]->quantEstoque = copia_qtd_estoque;

                /*
                ///Ordenando o totalQtdVendida
                copia_quant_vendida = prod[i]->totalQtdVendida;
                prod[i]->totalQtdVendida = prod[i + 1]->totalQtdVendida;
                prod[i + 1]->totalQtdVendida = copia_quant_vendida;
                */


                troca = 1;  //caso o programa consiga trocar as casinhas do vetor, a variável troca é true
            }
        }
    }
    while(troca);  //fazendo enquanto troca for true

    for(i = 0; i < *quant_prod_ja_cadast; i++)
    {
        printf("\t%9d        |\t  %-16s\t|      %.2f      \t|    %d   \n", prod[i]->codigo, prod[i]->nome, prod[i]->precoUnit, prod[i]->quantEstoque);
        printf("\t-----------------------------------------------------------------------------------\n");
    }
}

void cadastrar(Produto **prod, int *quant_prod_ja_cadast)
{
    int validarCod, validarNome, num;
    char cOpcao;

    char cCodigo[20];
    int iCodigo = 0;

    do
    {
        Produto *novoProd = malloc(sizeof(Produto));

        printf("\n---------------------------\n");
        printf("Memoria alocada c/ sucesso!");
        printf("\n---------------------------\n");

        printf("Digite o codigo:\n");
        fgets(cCodigo, sizeof(cCodigo), stdin);

        iCodigo = atoi(cCodigo);

        if(iCodigo > 0)
        {


            novoProd->codigo = iCodigo;

            if(novoProd->codigo <= 0)
            {
                printf("Digite um codigo maior que 0!\n");
                free(novoProd);
                continue;
            }

            validarCod = validarCodigo(prod, novoProd->codigo, quant_prod_ja_cadast);

            if(validarCod == 1)
            {
                printf("\n--------------\n");
                printf("NOVO CADASTRO!");
                printf("\n--------------\n");

                printf("\nDigite o nome:\n");
                scanf("%25[^\n]", novoProd->nome);
                getchar();

                validarNome = stringNaoVaziaOuEspacos(novoProd->nome);

                if(validarNome == 0)
                {
                    printf("\nA string nao pode ser vazia ou conter somente espacos!\n");
                    free(novoProd);
                    continue;
                }

                printf("\nDigite o preco unitario:\n");
                scanf("%f", &novoProd->precoUnit);
                getchar();

                if(novoProd->precoUnit < 0)
                {
                    printf("\nDigite um valor maior ou igual a 0!\n");
                    free(novoProd);
                    continue;
                }

                printf("\nDigite a quantidade em estoque:\n");
                scanf("%d", &novoProd->quantEstoque);
                getchar();

                if(novoProd->quantEstoque < 0)
                {
                    printf("\nDigite um valor maior ou igual a 0!\n");
                    free(novoProd);
                    continue;
                }

                novoProd->totalQtdVendida = 0;

                prod[*quant_prod_ja_cadast] = novoProd;

                (*quant_prod_ja_cadast)++;

                printf("\nDeseja continuar cadastrando?\n<S/s> - Sim\n<N/n> - Nao\n");
                scanf("%c", &cOpcao);
                getchar();

                if(cOpcao == 'S' || cOpcao == 's')
                    cOpcao = 'k';
                else if(cOpcao == 'N' || cOpcao == 'n')
                {
                    printf("\nCadastro encerrado!\n");
                    break;
                }

            }
            else if(validarCod == 0)
            {
                free(novoProd);
                printf("\nCadastro ja existente. Entre com um codigo valido.\n");
            }
        }

        else
        {
            printf("\nEntre somente com digitos ou numeros maiores que 0!\n");
        }

    }
    while(cOpcao != 'S' && cOpcao != 's' && cOpcao != 'N' && cOpcao != 'n');
}
int validarCodigo(Produto **prod, int numCod, int *quant_prod_ja_cadast)
{
    for(int i = 0; i < *quant_prod_ja_cadast; i++)
    {
        if(numCod == prod[i]->codigo)
        {
            //Codigo ja existente!
            return 0;
        }
    }
    //Numero nao existente
    return 1;
}

int stringNaoVaziaOuEspacos(char novo_nome_prod[])
{
    if(strlen(novo_nome_prod) < 1)
    {
        return 0;
    }
    for (int i = 0; i < strlen(novo_nome_prod); i++)
    {
        if (novo_nome_prod[i] != ' ' && novo_nome_prod[i] != '\t' && novo_nome_prod[i] != '\n')
            return 1; // Encontrou um caractere não espaço

    }
    return 0;
}

void editar_produto(Produto **prod, int *quant_prod_ja_cadast)
{
    int codigo, i;
    char confirmAlteracao;

    printf("\nDigite o codigo do produto a ser editado:\n");
    scanf("%d", &codigo);
    getchar();

    // Encontre o índice do contato a ser editado
    for(i = 0; i < *quant_prod_ja_cadast; i++)
    {
        if (prod[i]->codigo == codigo)
        {
            break; // O índice do contato foi encontrado
        }
    }

    if (i < *quant_prod_ja_cadast)   // Verifica se o índice é válido
    {
        Produto *alterado = malloc(sizeof(Produto));

        // Copie os valores do produto existente para o novo produto
        strcpy(alterado->nome, prod[i]->nome);
        alterado->codigo = prod[i]->codigo;
        alterado->precoUnit = prod[i]->precoUnit;
        alterado->quantEstoque = prod[i]->quantEstoque;

        printf("\nDigite o novo preco unitario:\n");
        scanf("%f", &alterado->precoUnit);
        getchar();

        printf("\nDigite a nova quantidade em estoque:\n");
        scanf("%d", &alterado->quantEstoque);
        getchar();

        printf("\t*****ANTES DA ALTERACAO*****\n");
        printf("\t-----------------------------------------------------------------------------------\n");
        printf("\t   ITEM(codigo)  |\t     Nome do item     \t|  Valor(Unidade)\t|  Estoque\n");
        printf("\t-----------------------------------------------------------------------------------\n");
        printf("\t        %d        |\t%-18s\t|      %.2f      \t|    %d   \n", prod[i]->codigo, prod[i]->nome, prod[i]->precoUnit, prod[i]->quantEstoque);
        printf("\t-----------------------------------------------------------------------------------\n\n");

        printf("\t*****DEPOIS DA ALTERACAO*****\n");
        printf("\t-----------------------------------------------------------------------------------\n");
        printf("\t   ITEM(codigo)  |\t     Nome do item     \t|  Valor(Unidade)\t|  Estoque\n");
        printf("\t-----------------------------------------------------------------------------------\n");
        printf("\t        %d        |\t%-18s\t|      %.2f      \t|    %d   \n", alterado->codigo, alterado->nome, alterado->precoUnit, alterado->quantEstoque);
        printf("\t-----------------------------------------------------------------------------------\n\n");

        do
        {
            printf("\nDeseja confirmar a alteracao?\n<S/s> - Sim\n<N/n> - Nao\n");
            scanf("%c", &confirmAlteracao);
            getchar();

            if(confirmAlteracao == 'S' || confirmAlteracao == 's')
            {
                // Copia o novo contato de volta para a agenda
                printf("-------------------------------");
                printf("\nProduto alterado com sucesso!\n");
                printf("-------------------------------");
                prod[i] = alterado;
            }
            else if(confirmAlteracao == 'N' || confirmAlteracao == 'n')
            {
                printf("---------------------------");
                printf("\nAlteracao nao confirmada!\n");
                printf("---------------------------");
                break;
            }
        }
        while(confirmAlteracao != 'S' && confirmAlteracao != 's' && confirmAlteracao != 'N' && confirmAlteracao != 'n');
    }
    else
    {
        printf("------------------------");
        printf("\nProduto nao encontrado.\n");
        printf("------------------------");

    }
}

void excluir_produto(Produto **prod, int *quant_prod_ja_cadast)
{
    int codigo, i, validarCod;
    char opcaoConfirmar;

    printf("\nDigite o codigo do produto a ser excluido:\n");
    scanf("%d", &codigo);
    getchar();

    validarCod = validarCodigo(prod, codigo, quant_prod_ja_cadast);

    if(validarCod == 0)
    {
        // Encontra o índice do contato a ser excluído
        for(i = 0; i < *quant_prod_ja_cadast; i++)
        {
            if (prod[i]->codigo == codigo)
            {
                break; // O índice do contato foi encontrado
            }
        }

        do
        {
            printf("\t-----------------------------------------------------------------------------------\n");
            printf("\t   ITEM(codigo)  |\t     Nome do item     \t|  Valor(Unidade)\t|  Estoque\n");
            printf("\t-----------------------------------------------------------------------------------\n");
            printf("\t        %d        |\t%-18s\t|      %.2f      \t|    %d   \n", prod[i]->codigo, prod[i]->nome, prod[i]->precoUnit, prod[i]->quantEstoque);
            printf("\t-----------------------------------------------------------------------------------\n\n");

            printf("\nDeseja confirmar a exclusao do produto acima?\n<S/s> - Sim\n<N/n> - Nao\n");
            scanf("%c", &opcaoConfirmar);
            getchar();

            if(opcaoConfirmar == 'S' || opcaoConfirmar == 's')
            {
                // Libera a memória alocada para o contato a ser excluído
                free(prod[i]);

                // Desloca os contatos restantes para preencher o espaço vazio
                for (int j = i; j < *quant_prod_ja_cadast - 1; j++)
                {
                    prod[j] = prod[j + 1];
                }

                // Atualiza o contador
                (*quant_prod_ja_cadast)--;

                printf("-------------------------------");
                printf("\nProduto excluido com sucesso!\n");
                printf("-------------------------------");
            }
            else if(opcaoConfirmar == 'N' || opcaoConfirmar == 'n')
            {
                printf("---------------------------");
                printf("\nAlteracao nao confirmada\n");
                printf("---------------------------");
                break;
            }
        }
        while(opcaoConfirmar != 'S' && opcaoConfirmar != 's' && opcaoConfirmar != 'N' && opcaoConfirmar != 'n');
    }

    else if(validarCod == 1)
    {
        printf("\nCodigo nao encontrado. Voltando ao Sub-Menu produtos...\n");
    }
}

void salvar_txt(Produto **prod, int *quant_prod_ja_cadast, char arq[])
{
    FILE *file = fopen(arq, "w");

    if(file)
    {
        printf("\n---------------------------\n");
        printf("ARQUIVO SALVO COM SUCESSO");
        printf("\n---------------------------");

        fprintf(file, "%d\n", *quant_prod_ja_cadast);

        for(int i = 0; i < *quant_prod_ja_cadast; i++)
        {
            fprintf(file, "%d\n", prod[i]->codigo);
            fprintf(file, "%s\n", prod[i]->nome);
            fprintf(file, "%.2f\n", prod[i]->precoUnit);
            fprintf(file, "%d\n", prod[i]->quantEstoque);
            fprintf(file, "%d\n", prod[i]->totalQtdVendida);
        }
        fclose(file);
    }
    else
        printf("Não foi possivel abrir o arquivo");
}

void ler_txt(Produto **prod, int *quant_prod_ja_cadast, char arq[])
{

    FILE *file = fopen(arq, "r");

    Produto *prodArquivo = malloc(sizeof(Produto));

    if(file)
    {
        printf("\n-------------------------\n");
        printf("ARQUIVO LIDO COM SUCESSO");
        printf("\n-------------------------");

        fscanf(file, "%d\n", &(*quant_prod_ja_cadast));

        for(int i = 0; i < *quant_prod_ja_cadast; i++)
        {
            fscanf(file, "%d\n", &prodArquivo->codigo);
            fscanf(file, "%25[^\n]\n", prodArquivo->nome);
            fscanf(file, "%f\n", &prodArquivo->precoUnit);
            fscanf(file, "%d\n", &prodArquivo->quantEstoque);
            fscanf(file, "%d\n", &prodArquivo->totalQtdVendida);

            prod[i] = prodArquivo;
            prodArquivo = malloc(sizeof(Produto));
        }
        fclose(file);
    }
    else
        printf("\nNao foi possivel abrir o arquivo.\n");
}


void vender(Produto **prod, int *quant_prod_ja_cadast, int *numVendas, Venda **vendaRealizada)
{
    int validarCod, codProdQuerVender, i, qtdProdQuerVender, indice, k, numParcelas, troca;
    char opcaoContinuarVendendo, OpcaoFormaPGT;
    float precoTotalVenda = 0.0, valor_recebido_cliente, valor_total_recebido_cliente = 0.0, troco_do_cliente;

    /*
    float copia_venda_subtotal;
    char copia_nome_ordenado[26];
    float copia_valor_unit;
    int copia_quant_vendida;
    */

    vendaRealizada = NULL;

    do
    {
        printf("\nDigite o codigo do produto que deseja vender:\n");
        scanf("%d", &codProdQuerVender);
        getchar();

        validarCod = validarCodigo(prod, codProdQuerVender, quant_prod_ja_cadast);

        if (validarCod == 0)
        {
            for (i = 0; i < *quant_prod_ja_cadast; i++)
            {
                if (codProdQuerVender == prod[i]->codigo)
                {
                    indice = i;
                    break;
                }
            }

            printf("\nDigite a quantidade do produto que deseja vender:\n");
            scanf("%d", &qtdProdQuerVender);
            getchar();

            if (qtdProdQuerVender > prod[indice]->quantEstoque && prod[indice]->quantEstoque > 0)
            {
                printf("\nQuantidade insuficiente no estoque. Digite uma quantidade <= a do estoque!\n");
            }
            else if (prod[indice]->quantEstoque <= 0)
            {
                printf("\nNao ha mais itens deste tipo no estoque. Favor, solicitar novas quantidades ao fornecedor!\n");
            }
            else
            {
                printf("\nVenda realizada com sucesso!\n");

                prod[indice]->quantEstoque -= qtdProdQuerVender;
                prod[indice]->totalQtdVendida += qtdProdQuerVender;

                // Redimensiona o vetor vendaRealizada
                vendaRealizada = (Venda **)realloc(vendaRealizada, (*numVendas + 1) * sizeof(Venda *));

                Venda *tempVenda = malloc(sizeof(Venda));

                if (tempVenda)
                {
                    tempVenda->codigoDoProdVendido = prod[indice]->codigo;
                    tempVenda->precoNaEpoca = prod[indice]->precoUnit;
                    tempVenda->qtdVendidaNaEpoca = qtdProdQuerVender;
                    tempVenda->subtotal = qtdProdQuerVender * prod[indice]->precoUnit;
                    strcpy(tempVenda->nomeItemVendidoNaEpoca, prod[indice]->nome);

                    vendaRealizada[*numVendas] = tempVenda;
                    (*numVendas)++;
                    //printf("NUMERO DE VENDAS: %d", *numVendas);
                }
                else
                {
                    printf("\nNao foi possivel alocar memoria para a venda!\n");
                }
            }
        }

        if (validarCod == 1)
        {
            printf("----------------------");
            printf("\nCodigo nao encontrado\n");
            printf("----------------------\n");
            continue;
        }


        printf("\nDeseja continuar vendendo?\n<S/s> - Sim\n<N/n> - Finalizar venda\n");
        scanf(" %c", &opcaoContinuarVendendo);
        getchar();

        if(opcaoContinuarVendendo == 'S' || opcaoContinuarVendendo == 's')
            opcaoContinuarVendendo = 'k';
        else if(opcaoContinuarVendendo == 'N' || opcaoContinuarVendendo == 'n')
        {
            opcaoContinuarVendendo = 'N';
            //break;
        }
    }
    while (opcaoContinuarVendendo != 'S' && opcaoContinuarVendendo != 's' && opcaoContinuarVendendo != 'N' && opcaoContinuarVendendo != 'n');

    bubbleSort(vendaRealizada, numVendas);

    /*
    ///BUBBLE SORT
    do
    {
        troca = 0; //variável troca começando sempre em 0

        //se a berenice tiver feito 1 venda, o indice_de_venda será 1... e assim por diante
        for(i = 0; i < *numVendas - 1; i++)
        {
            //compara a casa da esquerda com a casa da direita do vetor venda.
            //se eu trocar < por > o programa irá ordenar os preços de forma crescente (e não descrente como está no programa!)
            if(vendaRealizada[i]->qtdVendidaNaEpoca < vendaRealizada[i + 1]->qtdVendidaNaEpoca)
            {
                ///Ordenando o atributo subtotal
                copia_venda_subtotal = vendaRealizada[i + 1]->subtotal;
                vendaRealizada[i + 1]->subtotal = vendaRealizada[i]->subtotal;
                vendaRealizada[i]->subtotal = copia_venda_subtotal;

                ///Ordenando o atributo nomeItemVendidoNaEpoca
                strcpy(copia_nome_ordenado, vendaRealizada[i]->nomeItemVendidoNaEpoca);
                strcpy(vendaRealizada[i]->nomeItemVendidoNaEpoca, vendaRealizada[i + 1]->nomeItemVendidoNaEpoca);
                strcpy(vendaRealizada[i + 1]->nomeItemVendidoNaEpoca, copia_nome_ordenado);

                ///Ordenando o atributo precoNaEpoca
                copia_valor_unit = vendaRealizada[i]->precoNaEpoca;
                vendaRealizada[i]->precoNaEpoca = vendaRealizada[i + 1]->precoNaEpoca;
                vendaRealizada[i + 1]->precoNaEpoca = copia_valor_unit;


                ///Ordenando o quant_vendida
                copia_quant_vendida = vendaRealizada[i]->qtdVendidaNaEpoca;
                vendaRealizada[i]->qtdVendidaNaEpoca = vendaRealizada[i + 1]->qtdVendidaNaEpoca;
                vendaRealizada[i + 1]->qtdVendidaNaEpoca = copia_quant_vendida;


                troca = 1;  //caso o programa consiga trocar as casinhas do vetor, a variável troca é true
            }
        }
    }
    while(troca);  //fazendo enquanto troca for true
        */

    ///CARRINHO
    time_t tempoNu;
    struct tm *tempoInfo;
    char nomearq[30];

    time(&tempoNu);
    tempoInfo = localtime(&tempoNu);

    // Formata o nome do arquivo com o formato "Ano-Mes-Dia_Hora-Minuto-Segundo.txt"
    strftime(nomearq, sizeof(nomearq), "%Y-%m-%d_%H-%M-%S.txt", tempoInfo);

    FILE *file = fopen(nomearq, "w");

    if(file)
    {
        printf("\n---------------------------\n");
        printf("ARQUIVO SALVO COM SUCESSO");
        printf("\n---------------------------\n\n");

        //fprintf(file, "%d\n", *numVendas);

        for(int i = 0; i < *numVendas; i++)
        {
            //fprintf(file, "%d\n", vendaRealizada[i]->codigoDoProdVendido);
            fprintf(file, "%s\n", vendaRealizada[i]->nomeItemVendidoNaEpoca);
            //fprintf(file, "%.2f\n", vendaRealizada[i]->precoNaEpoca);
            fprintf(file, "%d\n", vendaRealizada[i]->qtdVendidaNaEpoca);
        }
        fclose(file);
    }
    else
        printf("Não foi possivel abrir o arquivo");
    ///FIM CARRINHO

    for (int l = 0; l < *numVendas; l++)
    {
        precoTotalVenda += vendaRealizada[l]->subtotal;
    }

    ///Imprimindo a nota fiscal!
    printf("\t ITEM \t|\tNome do item\t|  Valor(Unidade)R$  |\tQuant.\t|\tSub-total(R$)\n");
    printf("\t---------------------------------------------------------------------------------------\n");


    for(k = 0; k < *numVendas; k++)
    {
        printf("\t %4d \t|\t%-12s\t|  %-16.2f  |\t%6d\t|\t%9.2f\n", k+1, vendaRealizada[k]->nomeItemVendidoNaEpoca, vendaRealizada[k]->precoNaEpoca, vendaRealizada[k]->qtdVendidaNaEpoca, vendaRealizada[k]->subtotal);
        printf("\t---------------------------------------------------------------------------------------\n");

    }

    printf("\                                                                  TOTAL |\t%9.2f\n", precoTotalVenda);
    printf("\t---------------------------------------------------------------------------------------\n");


    int iOpcaoFormaPGT;

    do
    {
        printf("\nEscolha sua forma de pagamento:\n<V/v> - A Vista\n<P/p> - A Prazo\n");
        scanf("%c", &OpcaoFormaPGT);
        getchar();

        if(OpcaoFormaPGT == 'V' || OpcaoFormaPGT == 'v')
        {
            printf("\n-------------------------\n");
            printf("TOTAL): R$%.2f\n", precoTotalVenda);

            ///Dando desconto ao cliente
            if(precoTotalVenda <= 50)
            {
                precoTotalVenda *= 0.95;
                printf("desconto: (5%%)\n");
            }
            else if(precoTotalVenda > 50 && precoTotalVenda < 100)
            {
                precoTotalVenda *= 0.9;
                printf("desconto: (10%%)\n");
            }
            else if(precoTotalVenda >= 100)
            {
                precoTotalVenda *= 0.82;
                printf("desconto: (18%%)\n");
            }

            printf("-------------------------\n");
            printf("TOTAL COM DESCONTO: R$%.2f\n", precoTotalVenda);

            do
            {
                printf("\n\n-------------------------\n");
                printf("Digite o valor recebido:\n");
                printf("-------------------------\n");
                scanf("%f", &valor_recebido_cliente);
                getchar();

                if(valor_recebido_cliente < 0)
                {
                    printf("\nValor nao pode ser negativo!\n");
                    continue;
                }

                if(valor_recebido_cliente > 0)
                {
                    valor_total_recebido_cliente += valor_recebido_cliente;

                    if(valor_total_recebido_cliente < precoTotalVenda)
                    {
                        printf("\nFaltam %.2f reais!\n", precoTotalVenda - valor_total_recebido_cliente);
                        continue;
                    }
                }
                else
                {
                    printf("\nEntre somente com numeros apenas!\n");
                    continue;
                }

                troco_do_cliente = valor_total_recebido_cliente - precoTotalVenda;

                printf("\nTROCO DO CLIENTE(R$): %.2f\n", troco_do_cliente);

                break;

            }
            while(valor_total_recebido_cliente < precoTotalVenda);
        }
        else if(OpcaoFormaPGT == 'P' || OpcaoFormaPGT == 'p')
        {
            do
            {
                printf("\nDigite o numero de parcelas:\n");
                scanf("%d", &numParcelas);
                getchar();

                if(numParcelas <= 0)
                {
                    printf("\nO numero de parcelas de parcelas deve ser maior que 0!\n");
                    continue;

                }

                if(numParcelas > 0 && numParcelas <= 3)
                {
                    printf("\n-------------------------\n");
                    printf("TOTAL: R$%.2f\n", precoTotalVenda);
                    printf("Acrescimo: (5%%)\n");

                    precoTotalVenda *= 1.05;

                    printf("-------------------------\n");
                    printf("TOTAL COM ACRESCIMO: R$%.2f\n", precoTotalVenda);
                }
                else if(numParcelas > 3)
                {
                    printf("\n-------------------------\n");
                    printf("TOTAL: R$%.2f\n", precoTotalVenda);
                    printf("Acrescimo: (8%%)\n");

                    precoTotalVenda *= 1.08;

                    printf("-------------------------\n");
                    printf("TOTAL COM ACRESCIMO: R$%.2f\n", precoTotalVenda);
                }

                printf("\nValor de cada parcela: R$%.2f em %d vezes\n", (precoTotalVenda / numParcelas), numParcelas);
            }
            while(numParcelas <= 0);

        }
        else
            printf("\nOpcao invalida!\n");

    }
    while(OpcaoFormaPGT != 'V' && OpcaoFormaPGT != 'v' && OpcaoFormaPGT != 'P' && OpcaoFormaPGT != 'p');

}

void relatorioVendas(Produto **prod, int *quant_prod_ja_cadast, int *numVendas)
{
    int troca, i;
    //float copia_venda_subtotal;
    int copia_codigo;
    char copia_nome_ordenado[26];
    //float copia_valor_unit;
    int copia_qtd_estoque;
    int copia_quant_vendida;


    printf("\n--------------------\n");
    printf("RELATORIO DE VENDAS");
    printf("\n--------------------");

    ///BUBBLE SORT
    do
    {
        troca = 0; //variável troca começando sempre em 0

        //se a berenice tiver feito 1 venda, o indice_de_venda será 1... e assim por diante
        for(i = 0; i < *numVendas - 1; i++)
        {
            //compara a casa da esquerda com a casa da direita do vetor venda.
            //se eu trocar < por > o programa irá ordenar os preços de forma crescente (e não descrente como está no programa!)
            if(prod[i]->totalQtdVendida < prod[i + 1]->totalQtdVendida)
            {
                /*
                ///Ordenando o atributo subtotal
                copia_venda_subtotal = vendaRealizada[i + 1]->subtotal;
                vendaRealizada[i + 1]->subtotal = vendaRealizada[i]->subtotal;
                vendaRealizada[i]->subtotal = copia_venda_subtotal;
                */

                ///Ordenando o atributo codigo
                copia_codigo = prod[i]->codigo;
                prod[i]->codigo = prod[i + 1]->codigo;
                prod[i + 1]->codigo = copia_codigo;

                ///Ordenando o atributo nome
                strcpy(copia_nome_ordenado, prod[i]->nome);
                strcpy(prod[i]->nome, prod[i + 1]->nome);
                strcpy(prod[i + 1]->nome, copia_nome_ordenado);

                /*
                ///Ordenando o atributo precoNaEpoca
                copia_valor_unit = vendaRealizada[i]->precoNaEpoca;
                vendaRealizada[i]->precoNaEpoca = vendaRealizada[i + 1]->precoNaEpoca;
                vendaRealizada[i + 1]->precoNaEpoca = copia_valor_unit;
                */

                ///Ordenando o quantEstoque
                copia_qtd_estoque = prod[i]->quantEstoque;
                prod[i]->quantEstoque = prod[i + 1]->quantEstoque;
                prod[i + 1]->quantEstoque = copia_qtd_estoque;


                ///Ordenando o totalQtdVendida
                copia_quant_vendida = prod[i]->totalQtdVendida;
                prod[i]->totalQtdVendida = prod[i + 1]->totalQtdVendida;
                prod[i + 1]->totalQtdVendida = copia_quant_vendida;


                troca = 1;  //caso o programa consiga trocar as casinhas do vetor, a variável troca é true
            }
        }
    }
    while(troca);  //fazendo enquanto troca for true

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
    printf("   ITEM(codigo)  |\t     Nome do item     \t|  Quantidade em estoque(Unidade)\t|Quantidade vendida(Unidade)\n");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < *quant_prod_ja_cadast; i++)
    {
        printf("        %d        |\t%-18s\t|%16d                \t|\t%9d              \n", prod[i]->codigo, prod[i]->nome, prod[i]->quantEstoque, prod[i]->totalQtdVendida);
        printf("---------------------------------------------------------------------------------------------------------------------\n");

    }
}

void salvarBin(Produto **prod, int *quant_prod_ja_cadast, char arq[])
{
    FILE *file = fopen(arq, "wb");
    int i;

    if(file)
    {
        printf("\n------------------------------\n");
        printf("ARQUIVO BINARIO SALVO COM SUCESSO");
        printf("\n------------------------------");
        for(i = 0; i < *quant_prod_ja_cadast; i++)
        {
            fwrite(prod[i], sizeof(Produto), 1, file);
        }
        fclose(file);
    }
    else
        printf("\nO arquivo nao pode ser aberto!\n");
}

int lerBin(Produto **prod, char arq[])
{
    int quant = 0;
    Produto *novo = malloc(sizeof(Produto));
    FILE *file = fopen(arq, "rb");

    if(file)
    {
        printf("\n------------------------------\n");
        printf("ARQUIVO BINARIO LIDO COM SUCESSO");
        printf("\n------------------------------");
        while(fread(novo, sizeof(Produto), 1, file))
        {
            prod[quant] = novo;
            quant++;
            novo = malloc(sizeof(Produto));
        }
        fclose(file);
    }
    else
        printf("\nO arquivo nao pode ser aberto!\n");
    return quant;
}

void bubbleSort(Venda **vendaRealizada, int *numVendas)
{
    int troca, i;
    float copia_venda_subtotal;
    char copia_nome_ordenado[26];
    float copia_valor_unit;
    int copia_quant_vendida;

    ///BUBBLE SORT
    do
    {
        troca = 0; //variável troca começando sempre em 0

        //se a berenice tiver feito 1 venda, o indice_de_venda será 1... e assim por diante
        for(i = 0; i < *numVendas - 1; i++)
        {
            //compara a casa da esquerda com a casa da direita do vetor venda.
            //se eu trocar < por > o programa irá ordenar os preços de forma crescente (e não descrente como está no programa!)
            if(vendaRealizada[i]->qtdVendidaNaEpoca < vendaRealizada[i + 1]->qtdVendidaNaEpoca)
            {
                ///Ordenando o atributo subtotal
                copia_venda_subtotal = vendaRealizada[i + 1]->subtotal;
                vendaRealizada[i + 1]->subtotal = vendaRealizada[i]->subtotal;
                vendaRealizada[i]->subtotal = copia_venda_subtotal;

                ///Ordenando o atributo nomeItemVendidoNaEpoca
                strcpy(copia_nome_ordenado, vendaRealizada[i]->nomeItemVendidoNaEpoca);
                strcpy(vendaRealizada[i]->nomeItemVendidoNaEpoca, vendaRealizada[i + 1]->nomeItemVendidoNaEpoca);
                strcpy(vendaRealizada[i + 1]->nomeItemVendidoNaEpoca, copia_nome_ordenado);

                ///Ordenando o atributo precoNaEpoca
                copia_valor_unit = vendaRealizada[i]->precoNaEpoca;
                vendaRealizada[i]->precoNaEpoca = vendaRealizada[i + 1]->precoNaEpoca;
                vendaRealizada[i + 1]->precoNaEpoca = copia_valor_unit;


                ///Ordenando o quant_vendida
                copia_quant_vendida = vendaRealizada[i]->qtdVendidaNaEpoca;
                vendaRealizada[i]->qtdVendidaNaEpoca = vendaRealizada[i + 1]->qtdVendidaNaEpoca;
                vendaRealizada[i + 1]->qtdVendidaNaEpoca = copia_quant_vendida;


                troca = 1;  //caso o programa consiga trocar as casinhas do vetor, a variável troca é true
            }
        }
    }
    while(troca);  //fazendo enquanto troca for true

}

void salvar_csv(Produto **prod, int *quant_prod_ja_cadast)
{
    FILE *file = fopen("arq.csv", "w");

    if(file)
    {
        printf("\n---------------------------\n");
        printf("ARQUIVO SALVO COM SUCESSO");
        printf("\n---------------------------");

        fprintf(file, "Codigo;Nome;PrecoUnit;qtdEstoque\n");

        for(int i = 0; i < *quant_prod_ja_cadast; i++)
        {
            fprintf(file, "%d;%s;%.2f;%d", prod[i]->codigo, prod[i]->nome, prod[i]->precoUnit, prod[i]->quantEstoque);
            fprintf(file, "\n");
            //fprintf(file, "%.2f\n", prod[i]->precoUnit);
            //fprintf(file, "%d\n", prod[i]->quantEstoque);
            //fprintf(file, "%d\n", prod[i]->totalQtdVendida);
        }
        fclose(file);
    }
    else
        printf("Não foi possivel abrir o arquivo");
}
