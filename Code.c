#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#define F1 59

 void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

typedef struct{
	char haha[15]; 
}identi;

typedef struct{
	int dia, mes, ano; 
} Aniversario;

typedef struct{
	char nome[35];
	char telefone[25];
	char CPF[15];
	Aniversario data; 
	int f; 
} cadastro;

cadastro coleta_dados(){
	
	cadastro n; 
	int i, nada, validade;
	char e[4];
	
	system("cls"); 
	printf("\n\tTela de Cadastro: "); 
	printf("\n\n\tNome: "); 
	printf("\n\tTelefone: "); 
	printf("\n\tCPF: "); 
	printf("\n\tAniversario:    /    /   ");
	n.f = 1; 									//Para exclusão logica, 0 é excluido!
	fflush(stdin);
	do{											//Verificarção do nome
		gotoxy(16,4);
		printf("                                            "); 
		gotoxy(16,4);
		gets(n.nome);
		for(i=0; i<strlen(n.nome);i++)
			if((n.nome[i] >= 'A' && n.nome[i] <= 'Z') || (n.nome[i] >= 'a' && n.nome[i] <= 'z') || n.nome[i] == ' '){
				validade = 0; 
			}
			else {
			gotoxy(10,12);
			printf("Nome invalido, digite novamente!");					
			validade = 1; 
			break;
			}		
	} while (validade == 1);
	
	gotoxy(10,12); 
	printf("                                                               ");
	
	
	do{											//Verificação do telefone
		gotoxy(20,5);
		printf("                           "); 
		gotoxy(20,5);
		gets(n.telefone);
		for(i=0; i<strlen(n.telefone);i++)
			if(n.telefone[i] >= '0' && n.telefone[i] <= '9' || n.telefone[i] == ' '){
				validade = 0; 
			}else {
				gotoxy(10,12);
				printf("Numero de telefone invalido!"); 
				validade = 1; 
				break; 
			}
	}while(validade == 1);
	
	gotoxy(10,12); 
	printf("                                                               ");
	
	do{											//Verificação do CPF
		gotoxy(14,6);
		printf("                      "); 
		gotoxy(14,6);
		gets(n.CPF);
		for(i=0; i<strlen(n.CPF);i++)
			if(n.CPF[i] >= '0' && n.CPF[i] <= '9'){
				validade = 0; 
			}else {
				gotoxy(10,12);
				printf("Numero de CPF invalido!"); 
				validade = 1; 
				break; 
			}
	}while(validade == 1);
	
	gotoxy(10,12); 
	printf("                                                               ");
	
	do{									//Verificação do aniversario
		gotoxy(22,7); 
		printf("   /    /      "); 
		gotoxy(22,7); 
		scanf("%d",&n.data.dia); 
		gotoxy(27,7); 
		scanf("%d",&n.data.mes); 
		gotoxy(32,7); 
		scanf("%d",&n.data.ano);
		
		switch(n.data.mes)
		{
			case 1: 
			case 3: 
			case 5: 
			case 7:
			case 8: 
			case 10: 
			case 12: 	if((n.data.dia >= 1) && n.data.dia <= 31)
							validade = 0; 
						else validade = 1; 
						break;
			case 2: 	if((n.data.ano%4) == 0)
							if(n.data.dia >= 1 && n.data.dia <= 29)
								validade = 0; 
							else validade = 1; 
						else if(n.data.dia >= 1 && n.data.dia <= 28)
								validade = 0; 
							 else validade = 1; 
						break; 
			case 4:
			case 6: 
			case 9:
			case 11: 	if(n.data.dia >= 1 && n.data.dia <= 30)
							validade = 0; 
						else validade = 1; 
						break;
			default: 	validade = 1; 
		}
		
		if(validade == 1) {
		gotoxy(10,12);
		printf("Data digitada invalida! Por favor digite novamente");		
		}
	}while(validade == 1);
	
	gotoxy(10,12); 
	printf("                                                               ");
	
	printf("\n\tCadastro concluido com sucesso!");
	return n;	
}

void cad(char name[]){
	
	cadastro n;
	FILE *arq; 
	char e; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro na abertura do arquivo!");
		return; //exit(1);
	}
	fflush(stdin); 
	_sleep(200);
	fseek(arq,0,SEEK_END);
	
	do{
		system("cls"); 
		n = coleta_dados(); 
		
		fwrite(&n,sizeof(n),1,arq); 
		
		printf("\n\tDeseja realizar outro cadastro? (s/n)");
		do{
			scanf("%c",&e); 
			e = toupper(e); 
		}while(e != 'S' && e != 'N'); 
	}while(e == 'S');
	
	fclose(arq); 
	printf("\n\tCadastros realizados com sucesso!"); 
}

void printa(cadastro n, int k){
	
	printf("\n\tNome: %s",n.nome); 
	printf("\n\tTelefone: %s",n.telefone); 
	printf("\n\tCPF: %s",n.CPF); 
	printf("\n\tAniversario: %d / %d / %d\n",n.data.dia,n.data.mes,n.data.ano); 
}

void printa_nome(cadastro n){
	
	printf("\n\tNome: %s\n",n.nome); 
}

void consulta(char name[]){
	int num = 0, aux2; 
	cadastro n; 
	char aux[35]; 
	FILE *arq; 
	if((arq = fopen(name,"r+b")) == NULL){
		printf("\n\tErro na abertura do arquivo!"); 
		return; //exit(1);
	}
	
	system("cls");
	
	printf("\n\tTela de consulta: "); 
	printf("\n\n\t1 - Consultar por nome "); 
	printf("\n\t2 - Consultar por telefone "); 
	printf("\n\n\tOpção: ");
	
	do{
		scanf("%d",&num); 
	}while(num < 1 || num > 2); 
	
	fflush(stdin); 
	
	switch(num){
		case 1:		printf("\n\tDigite o nome: "); 
					gets(aux); 
					while(fread(&n,sizeof(n),1,arq) == 1){
						if(strcmp(aux,n.nome) == 0){
							printa(n,1);			
							aux2 = 1; 
							break; 
						}else aux2 = 0; 
					}
					
					if(!aux2) printf("\n\tCadastro não encontrado!"); 
					printf("\n\t"); 
					system("pause");
					break; 
		case 2: 	printf("\n\tDigite o telefone: "); 
					gets(aux); 
					while(fread(&n,sizeof(n),1,arq) == 1){
						if(strcmp(aux,n.telefone) == 0){
							printa(n,1); 
							aux2 = 1; 
							break; 
						}else aux2 = 0; 
					}
					
					if(!aux2) printf("\n\tCadastro não encontrado!"); 
					printf("\n\t"); 
					system("pause");					
					break; 	} 
					
	}

void listar(char name[]){
	
	FILE *arq; 
	cadastro n; 
	int cont = 0, op; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro na abertura do arquivo!"); 
		return; //exit(1); 
	}	
	
	do{
		system("cls"); 
		printf("\n\tLista cliente"); 
		printf("\n\n\t1 - Listar todos os clientes"); 
		printf("\n\t2 - Voltar");
		printf("\n\n\tOpção: "); 
		do{
			scanf("%d",&op); 
		}while(op < 1 || op > 2);
		
		rewind(arq); 
		cont = 0; 
		
		switch(op){
			case 1: 	system("cls"); 
						while(fread(&n,sizeof(n),1,arq) == 1)
							if(n.f == 1) 
								printa(n,0);
							
						printf("\n\tTodos os clientes listados\n\t");
						system("pause");
						break; 
			case 2:		break;	
				}
	}while(op != 2);
	
}

void ajuda(){
	
	int i; 
	char texto[200], chave[] = "entei", aux, aux2; 
	FILE *ajuda; 
	
	system("cls");
	if((ajuda = fopen("help.txt","rt")) == NULL){
		printf("Erro na abertura do arquivo!"); 
		return; //exit(1); 
	}
	
	do{
		aux = getc(ajuda);
		aux2 = aux - chave[i];
		printf("%c",aux2);
		i++;
		if(i == strlen(chave)) i = 0; 
	}while(aux != EOF);
	
	fclose(ajuda);
	printf("\n\n"); 
	system("pause");
}

int menu(char name[]){
	
	int n, aux = 0; 				// min 1 max 7
	
	do{
	system("cls"); 
	printf("\n\t\t\tArquivo padrão: %s\n\n",name);
	printf("\n\t1 - Consulta de cliente"); 
	printf("\n\t2 - Listar os clientes"); 
	printf("\n\t3 - Cadastrar novo cliente"); 
	printf("\n\t4 - Alterar cadastro");
	printf("\n\t5 - Excluir Cadastro");
	printf("\n\t6 - Manipulaçao dos arquivos");
	printf("\n\t7 - Sair do programa");
	printf("\n\n\tOpção: "); 
	printf("\n\n\n\n\tF1 - Ajuda");
	
	do{
		gotoxy(16,13); 
		printf("    "); 
		gotoxy(16,13);
		n = getch();
		//	printf("\n\tValor: %d",n); 
		//	system("pause");
			if(n == 0){
		//		printf("\n\Testando: %d",n);
				n = getch(); 
			//	system("pause");
					if(n == 59){
						printf("\n\ttestando: %d",n); 
					//	system("pause");
						ajuda();
						break; 
					}else	n = n; 
			}else n = n - 48;
		
		if(n < 1 || n > 7) {
			gotoxy(20,16); 
			printf("Opção invalida, por favor digite novamente!");
		}
	}while(n < 1 || n > 7);
	}while((n < 1 || n > 7));
	
	_sleep(400);
	return n; 	
}

void alterar(char name[]){	
	
	system("cls"); 
	FILE *arq; 
	cadastro n; 
	char no[35], e; 
	int op, day, month, year, aux = 0;
	float sal; 
	
	if((arq = fopen(name,"r+b")) == NULL){
		printf("Erro na abertura do arquivo!"); 
		return; //exit(1);
		}
	
	do{
	system("cls");
	printf("\n\tTela para alterar o cadastro\n");
	printf("\n\tDigite o nome ou celular do cliente: "); 
	fflush(stdin);
	gets(no); 
	aux = 0; 
	
	rewind(arq);
	
	while(fread(&n,sizeof(n),1,arq) == 1)
		if(n.f == 1 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
			
			aux = 1; 
			printf("\n\tSelecione o campo que deseja mudar do cliente: %s",n.nome); 
			printf("\n\t1 - Nome"); 
			printf("\n\t2 - Telefone"); 
			printf("\n\t3 - CPF"); 
			printf("\n\t4 - Aniversario"); 
			printf("\n\n\tOpção: "); 
			do{
				scanf("%d",&op); 				
			}while(op < 1 || op > 5); 
			
			switch(op){
				
				case 1: 	printf("\n\tDigite o novo nome: "); 
							fflush(stdin);
							gets(no); 
							
							printf("\n\tDeseja mesmo mudar o nome?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){
								strcpy(n.nome,no); 
								printf("\n\tNome mudado com sucesso!"); 
							}else printf("\n\tNome não modificado!"); 
							printf("\n\t"); 
							system("pause");
							break;
				case 2: 	printf("\n\tDigite o novo telefone: "); 
							fflush(stdin);
							gets(no); 
							
							printf("\n\tDeseja mesmo mudar o telefone?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){
								strcpy(n.telefone,no); 
								printf("\n\tTelefone mudado com sucesso!"); 
							}else printf("\n\tTelefone não modificado!"); 
							printf("\n\t"); 
							system("pause");
							break;
				case 3: 	printf("\n\tDigite o novo CPF: "); 
							fflush(stdin);
							gets(no); 
							
							printf("\n\tDeseja mesmo mudar o CPF?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){
								strcpy(n.CPF,no); 
								printf("\n\tCPF mudado com sucesso!"); 
							}else printf("\n\tCPF não modificado!");
							printf("\n\t"); 
							system("pause"); 
							break;
				case 4: 	printf("\n\tDigite a nova data: "); 
							scanf("%d %d %d",&day,&month,&year);
							
							printf("\n\tDeseja mesmo mudar a data?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){
								n.data.dia = day; 
								n.data.mes = month; 
								n.data.ano = year;
								printf("\n\tData mudado com sucesso!"); 
							}else printf("\n\tData não modificado!"); 
							printf("\n\t"); 
							system("pause");
							break;
				case 5: 
							break;				
			}			
			break; 
		}
		
		if(!aux) {
			printf("\n\tCadastro não encontrado!\n\n\t");
			system("pause");}
			
		if(aux) {
			fseek(arq,-sizeof(n),SEEK_CUR);
			fwrite(&n,sizeof(n),1,arq);}		
		
		printf("\n\tDeseja alterar outro cliente?");		
		do{
			scanf("%c",&e); 
			e = toupper(e); 
		}while(e != 'S' && e != 'N'); 		
		}while(e == 'S');			
			
		fclose(arq);	
}

void excluir(char name []){
	
	FILE *arq, *copia; 
	cadastro n;  
	int op, op2, aux = 0; 
	char no[35], e;	
		
	do{
	system("cls"); 	
	
	printf("\n\tExclusão de cadastro"); 
	printf("\n\n\t1 - Tela de exclusão logica");
	printf("\n\t2 - Tela de exclusão fisica"); 
	printf("\n\t3 - Voltar");
	printf("\n\n\t Opção: ");
	
	do{
		scanf("%d",&op); 
	}while(op < 1 || op > 3); 
	
	switch(op){
		
		case 1: 		do{
						aux = 0; 
						system("cls"); 
						printf("\n\tExclusão Logica"); 
						printf("\n\n\t1 - Listar cadastros excluidos logicamente"); 
						printf("\n\t2 - Excluir um cadastro logicamente"); 
						printf("\n\t3 - Restaurar um cadastro"); 
						printf("\n\t4 - Voltar ");
						printf("\n\n\tOpção: "); 
						
						rewind(arq);
						
						do{
							scanf("%d",&op2); 
						}while(op2 < 1 || op2 > 4); 
						
						switch(op2){
							case 1: 	if((arq = fopen(name,"r+b")) == NULL){
											printf("\n\tErro na abertura do arquivo!");
											return; //exit(1);
										}
							
										while(fread(&n,sizeof(n),1,arq) == 1){
											if(n.f == 0){
												printa_nome(n); 
												printf("\n");
											}																				
										}
										
										printf("\n\tCadastro excluidos logicamente!\n\t");
										system("pause");
										
										fclose(arq);
										break; 
							case 2: 	printf("\n\tDigite o nome ou celular do cliente: "); 
										fflush(stdin);
										gets(no); 
										
										if((arq = fopen(name,"r+b")) == NULL){
											printf("\n\tErro na abertura do arquivo!");
											return; //exit(1);
										}
										
										while(fread(&n,sizeof(n),1,arq) == 1)
											if(n.f == 1 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
												
												printf("\n\tCadastro encontrado!"); 
												aux = 1; 
												printf("\n\tDeseja mesmo excluir?"); 
												do{
													scanf("%c",&e); 
													e = toupper(e); 
												}while(e != 'S' && e != 'N'); 
												
												if(e == 'S'){
													n.f = 0; 													
													printf("\n\tCadastro excluido com sucesso!\n\n\t"); 
													break; 
												}else printf("\n\tCadastro não excluido!");	
											}
												
										fseek(arq,-sizeof(n),SEEK_CUR); 
										fwrite(&n,sizeof(n),1,arq); 
										
										if(!aux) printf("\n\tCadastro não encontrado!\n\n\t");
										system("pause");
										fclose(arq);
										break; 
										
							case 3:  	printf("\n\tTela de recuperação de cadastro excluidos logicamente"); 
										printf("\n\tDigite o nome ou celular do cliente, para recuperar o cadastro: "); 
										fflush(stdin);
										gets(no); 
										
										if((arq = fopen(name,"r+b")) == NULL){
											printf("\n\tErro na abertura do arquivo!");
											return; //exit(1);
										}
										
										while(fread(&n,sizeof(n),1,arq) == 1)
											if(n.f == 0 && (strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
												
												printf("\n\tCadastro encontrado!"); 
												aux = 1; 
												printf("\n\tDeseja mesmo restaura o cadastro?"); 
												do{
													scanf("%c",&e); 
													e = toupper(e); 
												}while(e != 'S' && e != 'N'); 
												
												if(e == 'S'){
													n.f = 1; 
													 
													printf("\n\tCadastro restaurado com sucesso!\n\n\t"); 
													break; 
												}
												
											}
											
											fseek(arq,-sizeof(n),SEEK_CUR); 
											fwrite(&n,sizeof(n),1,arq);
											
											if(!aux) printf("\n\tCadastro não encontrado!\n\n\t");
											system("pause");
											fclose(arq);
											break; 
										
							case 4: 	printf("\n\tVoltando pra tela anterior!"); 
										//fclose(arq);
										_sleep(1000); 
										break; 
									}
									
								}while(op2 != 4);
								break; 
			case 2: 		printf("\n\tTela de exclusão fisica"); 
							printf("\n\tDigite o nome do cliente para exclusão permanente: "); 
							fflush(stdin);
							gets(no); 
							
							if((arq = fopen(name,"r+b")) == NULL){
								printf("\n\tErro na abertura do arquivo!");
								return; //exit(1);
							}
										
							while(fread(&n,sizeof(n),1,arq) == 1)
								if((strcmp(no,n.nome) == 0 || strcmp(no,n.telefone) == 0)){
									
									printf("\n\tCadastro encontrado!"); 
									aux = 1; 
									printf("\n\tDeseja mesmo excluir permanente o cadastro?"); 
										do{
											scanf("%c",&e); 
											e = toupper(e); 
										}while(e != 'S' && e != 'N'); 
										
										if(e == 'S'){										
											
											if((copia = fopen("copia.dat","w+b")) == NULL){
												printf("\n\tErro na abertura do arquivo copia"); 
												exit(1);
											} 
											
											rewind(arq);
											
											while(fread(&n,sizeof(n),1,arq) == 1)
												if(strcmp(no,n.nome) != 0)
													fwrite(&n,sizeof(n),1,copia); 
													
											fclose(arq); 
											
											arq = fopen(name,"w+b"); 
											
											rewind(copia); 
											
											while(fread(&n,sizeof(n),1,copia) == 1)
												fwrite(&n,sizeof(n),1,arq); 
												
											fclose(arq); 
											fclose(copia); 
											
											remove("copia.dat"); 
											
											printf("\n\tCadastro excluido com sucesso!\n\n\t"); 
											//system("pause")
											break; 
										}									
								}
								
								if(!aux) printf("\n\tCadastro não encontrado!\n\n\t");
								system("pause");								
							
							break;
			case 3: 		printf("Voltando!"); 
							break;						
						}
					}while(op != 3);
					
					//fclose(arq);
				}

void nome_arq(char n[]){
	
	int i, j;  
	char dat[] = ".dat";
	
	system("cls");
	printf("\n\tNão existe um arquivo inicial!"); 
	printf("\n\tDigite um novo para o arquivo, que irá armazenar os clientes");
	printf("\n\tDigite sem o \".dat\"!:");
	gets(n);
	
	strcat(n,".dat");
}

void funcoes_sistema(char name[]){
	
	int op, ret; 
	char horario[100];
	char data[100];
	int hora,minuto,segundo,dia,mes,ano;
	char e; 
	char path[20]; 
	char aux[20]; 
	char caminho1[130], caminho2[130];
	FILE *arq1, *arq2; 
	identi m; 
	
	do{
		system("cls"); 
		printf("\n\tTela para as funções do sistema: ");
		printf("\n\t1 - Criar uma pasta"); 
		printf("\n\t2 - Renomear uma pasta");
		printf("\n\t3 - Acessar uma pasta");
		printf("\n\t4 - Voltar para a pasta anterior");
		printf("\n\t5 - Excluir um arquivo");
		printf("\n\t6 - Mover um arquivo de pasta");
		printf("\n\t7 - Mostrar conteudo do diretorio atual");
		printf("\n\t8 - Definir um arquivo como o principal");
		printf("\n\t9 - Criar um arquivo"); 
		printf("\n\t10 - Renomear um arquivo");
		printf("\n\t11 - Horas");
		printf("\n\t0 - Voltar");
		printf("\n\n\tOpção: ");
		
		do{
			scanf("%d",&op);
		}while(op < 0 || op > 12);
		
		switch(op){
			case 1: 		system("cls"); 
							printf("\n\tDigite o nome da pasta a ser criada:  "); 
							fflush(stdin); 
							gets(path); 
							
							mkdir(path); 
							
							printf("\n\t"); 
							system("pause"); 
							break; 
							
			case 2: 		printf("\n\tDigite o nome da pasta para modificar: ");
							fflush(stdin);
							gets(path); 
							
								printf("\n\tDigite o novo nome: "); 
								fflush(stdin);
								gets(aux);
												
							rename(path,aux);
							
							printf("\n\tRenomeado com sucesso!\n\t"); 
							
							system("pause");
							break;
							
			case 3: 		//system("cls"); 
							printf("\n\tDigite o nome da pasta:  "); 
							fflush(stdin); 
							gets(path);
							
							if(chdir(path) == NULL)
								printf("\n\tAção feita com sucesso!");
							else printf("\n\tPasta não encontrada!");
							
							system("pause"); 
							break; 
							
			case 4: 		chdir("..");
							printf("\n\tVoltando para a pastar anterior\n\t");
							system("pause");							
							break; 
			case 5:			printf("\n\tDigite o nome do arquivo a ser excluido, coloque a extensão do arquivo: "); 
							fflush(stdin); 
							gets(path); 
							
							if((arq1 = fopen(path,"r")) == NULL)
								printf("Arquivo não encontrado!"); 
							else{							
								fclose(arq1); 
								
								printf("\n\tCerteza que deseja remover o arquivo? ");
								do{
									scanf("%c",&e); 
									e = toupper(e); 
								}while(e != 'S' && e != 'N');
								
								if(e == 'S'){
									if(remove(path) == 0){
									_sleep(1000); 
									printf("\n\tArquivo removido com sucesso!"); 
									}else printf("\n\tErro na remoção do arquivo!");
								}else printf("\n\tRemoção do arquivo cancelada!"); 
							}
							system("pause");
							break; 
			case 6:			printf("\n\tDigite o nome do arquivo a ser movido, com a extensão: "); 
							fflush(stdin);
							gets(aux);
							printf("\n\tPara mover arquivos em outras pastas, é necessario digitar o caminho inteiro: "); 
							printf("\n\tDigite o caminho do arquivo: "); 
							fflush(stdin); 
							gets(caminho1); 
							strcat(caminho1,"\\");
							strcat(caminho1,aux);
							if((arq1 = fopen(caminho1,"rb"))!=NULL){
								printf("\n\tDigite o novo caminho: "); 
								fclose(arq1); 
								fflush(stdin); 
								gets(caminho2); 		
								strcat(caminho2,"\\"); 
								strcat(caminho2,aux);
																						
								rename(caminho1, caminho2);
								
								_sleep(1000); 
								if((arq1 = fopen(caminho2,"rb")) != NULL) printf("\n\tArquivo movido com sucesso!");
								else printf("\n\tFalha para renomear o arquivo!");
							}else printf("\n\tArquivo não encontrado!\n\t"); 
							
							system("pause");							
							break; 
			case 7: 		system("dir");
							system("pause");
							break; 
			case 8:			printf("\n\tPara Consultar os registros do arquivo, é necessario mante-lo na pasta principal!"); 
							printf("\n\tDigite o nome do arquivo a ser marcado com o padrão (tem que ser .dat): ");
							fflush(stdin); 
							gets(path);
							
							if((arq2 = fopen("nomes.dat","w+b")) == NULL){
								printf("\nErro"); 
							}else{
								strcpy(m.haha,path);
								strcpy(name,path);
								fwrite(&m,sizeof(m),1,arq2); 
								fclose(arq2);
								
								printf("\n\tArquivo mudado!\n\t"); 
								system("pause");								
							}
							break; 
							
			case 9: 		printf("\n\tO arquivo será criado na pasta atual!"); 
							printf("\n\tDeseja continuar?"); 
							do{
								scanf("%c",&e); 
								e = toupper(e); 
							}while(e != 'S' && e != 'N'); 
							
							if(e == 'S'){								
								printf("\n\tDigite o nome do arquivo a ser criado, digite com a extensão: "); 
								fflush(stdin); 
								gets(path); 
								
								arq2 = fopen(path,"w");
								if(!arq2) printf("\n\tErro na abertura do arquivo!"); 
								else printf("\n\tArquivo criado com sucesso!"); 							
							}else printf("\n\tCriação do arquivo cancelada!");
							fclose(arq2);
							system("pause");							
							break; 
							
			case 10:		printf("\n\tDigite o nome do arquivo para renomear:");
							fflush(stdin); 
							gets(path); 
							
							if((arq1 = fopen(path,"r")) == NULL){
								printf("\n\tArquivo não encontrado\n\t");
								system("pause");
							}else{
								printf("\n\tDigite o novo nome: "); 
								gets(aux); 
								
								fclose(arq1);
								
								rename(path,aux); 
								
								_sleep(1000); 								
								printf("\n\tArquivo renomeado com sucesso!\n\t");								
								system("pause");							
							}
							break; 		
			case 11: 		
							system("cls"); 
							printf("\n\tDigite a hora: "); 
							do{
								scanf("%d",&hora); 
							}while(hora < 0 || hora > 24); 
							printf("\n\tDigite os minutos: "); 
							do{
								scanf("%d",&minuto); 
							}while(minuto < 0 || minuto > 60);
							printf("\n\tDigite os segundos: "); 
							do{
								scanf("%d",&segundo);
							}while(segundo < 0 || segundo > 60);
							
							printf("\n\tDigite o dia atual: "); 
							do{
								scanf("%d",&dia);
							}while(dia < 1 || dia > 31); 
							
							printf("\n\tDigite o mes: "); 
							do{
								scanf("%d",&mes); 
							}while(mes < 1 || mes > 12);
							
							printf("\n\tDigite o ano: "); 
							do{
								scanf("%d",&ano);
							}while(ano < 0);
							
							sprintf(horario,"time %d:%d:%d",hora,minuto,segundo);
							sprintf(data,"date %d-%d-%d",dia,mes,ano);
							system(data);
							system(horario); 
							
							system("pause");
							break; 					
		}
							
		
	}while (op != 0);
}

int main(){

	setlocale(LC_ALL,"Portuguese");
	cadastro n; 
	identi names; 
	FILE *arq, *nomes; 
	int tecla, op; 
	char aux; 
	char name[15];
	
	if((nomes = fopen("nomes.dat","r+b")) != NULL)
		while(fread(&names,sizeof(names),1,nomes) == 1)
			strcpy(name,names.haha); 
	else if((nomes = fopen("nomes.dat","w+b")) != NULL){
			nome_arq(name);
			
			strcpy(names.haha,name);
			fwrite(&names,sizeof(names),1,nomes); 
			fclose(nomes);
		}
	
	
	if((arq = fopen(name,"r+b")) == NULL){
		if((arq = fopen(name,"w+b")) == NULL){
			printf("\n\tErro na abertura do arquivo!"); 
			exit(1);
		}
	}
	
	fclose(arq);
	
	do{
			op = menu(name); 
			switch (op){
				case 1: 	consulta(name);
							break; 
				case 2: 	listar(name);
							break; 
				case 3: 	cad(name);
							break; 
				case 4: 	alterar(name);
							break; 
				case 5: 	excluir(name);					
							break; 
				case 6: 	funcoes_sistema(name);			
							break; 
				case 7:		printf("\n\n\tObrigado!"); 
							printf("\n\tfim do programa");
							break; 
			}
			
	}while(op != 7);	
	system("pause");
}
