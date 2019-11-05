
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include "teste.c"

#define CLEAN_BUFF do{ int c; while((c = getchar()) != '\n' && c != EOF);}while(0) //substitui esse parte por getchar() se voc� preferir

#define MAX_SENHA 6
#define MAX_LOGIN 50

int Usuario( FILE* file, char* user, char* senha ) //Verifica se � um usuario valido
{
	char tmpLogin[MAX_LOGIN];
	char tmpSenha[MAX_SENHA];

	fscanf(file, "%s", tmpLogin);

	while( !feof(file) )
	{
		if( !strcmp(tmpLogin, user) )
		{
			fscanf(file, "%s", tmpSenha);

			if( !strcmp(tmpSenha, senha) )
				return 1;
		}
		else
		{
			fscanf(file, "%*s");
		}

		fscanf(file, "%s", tmpLogin);
	}

	return 0;
}

char* CriaSenha()
{
    register int i;

	char* senha = (char*)malloc(sizeof *senha * MAX_SENHA);

    for(i = 0; i < MAX_SENHA; i++)
	{
        senha[i] = getch();
        if(senha[i] == '\r')
            break;
        else
            printf("*");
    }
	senha[i] = '\0';

	return senha;
}

int main()
{
	FILE* fpIN;

	int option = 0;
	int aux = teste();

	char *user  = (char*)malloc(sizeof *user * MAX_LOGIN);
	char *senha,
		 *confirmaSenha;

	do
	{
		printf("1- Login\n2- Cadastrar\n3- Sair\n");
		scanf("%d", &option);
		CLEAN_BUFF;

		switch( option )
		{
			case 1:

				printf("Usuario: ");
				gets(user);
				printf("Senha: ");
				senha = CriaSenha();

				fpIN = fopen("usuarios.txt", "a+");
				printf("\nUsuario %sconfirmado.%d \n", aux, Usuario(fpIN, user, senha) ? "" : "n�o ");
			    printf("\n %d", aux);
				fclose(fpIN);


				free(senha);
			break;

			case 2:
				printf("Usuario: ");
				gets(user);

				do
				{
					printf("Senha: ");
					senha = CriaSenha();
					printf("\nConfirmacao de senha: ");
					confirmaSenha = CriaSenha();
					printf("\n");

					if( !strcmp(senha, confirmaSenha) )
						break;
					else
						printf("As senhas n�o s�o iguais. Tente novamente.\n");
				}while(1);

				fpIN = fopen("usuarios.txt", "a+");
				fprintf(fpIN, "%s %s\n", user, senha);
				fclose(fpIN);

				free(senha);
				free(confirmaSenha);
			break;

			case 3:
				return 0;

			default:
				printf("Escolha 1, 2 ou 3...\n");
			break;
		}

	}while( 1 );

	return (0);
}
