#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXIMO_USERS 1000
int totalUsuarios = 0;

typedef struct tUsuario
{
    int id;
    char nomeCompleto[100];
    char email[100];
    char sexo[10];
    char endereco[100];
    double altura;
    int vacina;
} Usuario;

Usuario users[MAXIMO_USERS];
Usuario usersBackup[MAXIMO_USERS];

void abreMenu()
{
    printf("Digite 1 para adicionar usuario\n");
    printf("Digite 4 para buscar usuario por email\n");
    printf("Digite 5 para imprimir todos os usuarios\n");
    printf("Digite 6 para fazer o backup de  todos os usuarios\n");
    printf("Caso deseje fechar o programa tecle 0\n");
    printf("Digite a opção escolhida: ");
}

void incluiUsuario()
{
    int id, vacina;
    char nome[100], email[100], sexo[100], endereco[100];
    double altura;

    id = rand() % 1000;

    printf("Digite o nome completo do usuario:");
    fgets(nome, 50, stdin);
    strtok(nome, "\n");

    printf("Digite o email do usuario:");
    while (fgets(email, 50, stdin) != NULL)
    {
        if (strchr(email, '@') != NULL)
        {
            break;
        }
        else
        {
            printf("O email digitado nao contem um '@'. Digite novamente:\n");
        }
    }

    int valido = 0;
    while (valido == 0)
    {
        printf("Digite o sexo do usuario:");
        fgets(sexo, 50, stdin);

        int posicao_quebra_linha = strcspn(sexo, "\n");
        sexo[posicao_quebra_linha] = '\0';

        if (strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0)
        {
            valido = 1;
        }
        else
        {
            printf("Sexo invalido, Digite 'Feminino','Masculino' ou 'Indiferente'.\n");
        }
    }

    printf("Digite o endereco do usuario:");
    fgets(endereco, 50, stdin);
    strtok(endereco, "\n");

    int altura_valida = 0;
    while (altura_valida == 0)
    {
        printf("Digite a altura do usuario:");
        scanf("%lf", &altura);

        if (altura >= 1.0 && altura <= 2.0)
        {
            altura_valida = 1;
        }
        else
        {
            printf("Altura invalida. Digite um valor entre 1.0 e 2.0.\n");
        }
    }

    printf("O usuario esta vacinado (digite 1 para sim e 0 para nao):\n");
    scanf("%d", &vacina);
    getchar();

    Usuario tempUser;
    tempUser.id = id;
    strcpy(tempUser.nomeCompleto, nome);
    strcpy(tempUser.email, email);
    strcpy(tempUser.sexo, sexo);
    strcpy(tempUser.endereco, endereco);
    tempUser.altura = altura;
    tempUser.vacina = vacina;
    users[totalUsuarios] = tempUser;
    totalUsuarios++;

    return 0;
}

int imprimirUsuario()
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        printf("\n----------USUARIO %d----------\n", i + 1);
        printf("id:  %d\n", users[i].id);
        printf("nome: %s\n", users[i].nomeCompleto);
        printf("email: %s\n", users[i].email);
        printf("sexo: %s\n", users[i].sexo);
        printf("endereco: %s\n", users[i].endereco);
        printf("altura: %.2lf\n", users[i].altura);
        printf("status de vacinacao: %d\n\n", users[i].vacina);
    }
}

int backUpUsuarios()
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        usersBackup[i].id = users[i].id;
        strcpy(usersBackup[i].nomeCompleto, users[i].nomeCompleto);
        strcpy(usersBackup[i].email, users[i].email);
        strcpy(usersBackup[i].sexo, users[i].sexo);
        strcpy(usersBackup[i].endereco, users[i].endereco);
        usersBackup[i].altura = users[i].altura;
        usersBackup[i].vacina = users[i].vacina;
    }

    printf("BackUp concluido com sucesso\n");

    return 0;
}

int buscaPorEmail()
{
    char email[100];

    printf("Digite o email do usuario: ");
    scanf(" %[^\n]", email);

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (strcmp(users[i].email, email) == 0)
        {

            printf("nome: %s\n", users[i].nomeCompleto);
            printf("email: %s\n", users[i].email);
            printf("sexo: %s\n", users[i].sexo);
            printf("endereco: %s\n", users[i].endereco);
            printf("altura: %.2lf\n", users[i].altura);
            printf("status de vacinacao: %d\n", users[i].vacina);

            return 0;
        }
        else
        {
            printf("Usuario nao encontrado\n");
            return -1;
        }
    }
}

int restaurarDados()
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        users[i].id = usersBackup[i].id;
        strcpy(users[i].nomeCompleto, usersBackup[i].nomeCompleto);
        strcpy(users[i].email, usersBackup[i].email);
        strcpy(users[i].sexo, usersBackup[i].sexo);
        strcpy(users[i].endereco, usersBackup[i].endereco);
        users[i].altura = usersBackup[i].altura;
        users[i].vacina = usersBackup[i].vacina;
    }

    printf("Restauracao concluido com sucesso\n");

    return 0;
}

int main()
{
    char opcao = ' ';

    while (opcao != '0')
    {
        abreMenu();
        scanf("%c", &opcao);
        getchar();

        switch (opcao)
        {
        case '1':
            incluiUsuario();
            break;
        case '4':
            buscaPorEmail();
            break;
        case '5':
            imprimirUsuario();
            break;
        case '6':
            backUpUsuarios();
            break;
        case '7':
            restaurarDados();
            break;
        case '0':
            printf('programa fechado');
        default:
            printf("Opção invalida");
            break;
        }
    }
}