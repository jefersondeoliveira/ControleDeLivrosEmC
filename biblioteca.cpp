#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>

void switchMenu(int);
void templateLinhas();
void inserir();
void listar();
void buscar();
struct material{
    char titulo[40],autor[20];
    int codigo;
    float valor;
};


main() {
    int escolha;
    do {
      templateLinhas();
      gotoxy(30, 2);
      printf("Controle de Livros");
      gotoxy(33, 7);
      printf("[1].Inserir");
      gotoxy(33, 9);
      printf("[2].Listar");
      gotoxy(33, 11);
      printf("[3].Buscar");
      gotoxy(33, 13);
      printf("[4].Sair");
      gotoxy(35, 18);
      printf("Opcao: ");
      scanf("%i", &escolha);
      switchMenu(escolha);
      }
      while (escolha > 0);
      system("pause>null");
}



//FUNÇÕES
void switchMenu(int escolha){
     switch(escolha) {
          case 1:
              inserir();
          break;
          case 2:
             listar();
          break;
          case 3:
             buscar();
          break;
          case 4:
            exit(0);
          break;
          default:
             printf("Opcao Invalida!\n");
          break;
      }
}

void inserir(){
      FILE *registros;    
      struct material livro;
      int continuar,codigo=0;

	  do{
		if((registros = fopen("registros.dat","ab+"))== NULL){
	    	printf("Erro ao tentar abrir o arquivo.");
         }else{
        	templateLinhas();
            gotoxy(33, 2);
            printf("Inserir Material");
            gotoxy(33, 7);
            printf("Codigo: ");
            fflush(stdin);
            while(fread(&livro,sizeof(material),1,registros) == 1){
                if(codigo < livro.codigo)
                    codigo = livro.codigo;
            }
            codigo++;
            livro.codigo = codigo;
            printf("%i",livro.codigo);
            gotoxy(33, 9);
            printf("Titulo: ");
            fflush(stdin);
            gets(livro.titulo);
            gotoxy(33, 11);
            printf("Autor: ");
            fflush(stdin);
            gets(livro.autor);
            gotoxy(33, 13);
            printf("Valor: ");
            fflush(stdin);
            scanf("%f",&livro.valor);
       
            fwrite(&livro,sizeof(material),1,registros);
            fclose(registros);
          }
        gotoxy(33, 17);
        printf("Cadastro salvo!");
        gotoxy(16, 19);
        printf("Deseja continuar cadastrando? [0]Sim [1]Nao [   ]");
        gotoxy(62, 19);
        scanf("%i", &continuar);
     }while(continuar != 1);
}

void bubbleSort(){
    FILE *registros;  
    int i,j,n=1; 
    struct material livro,livroAlf,livroAlf2;
    if((registros = fopen("registros.dat","rb+"))== NULL){
	      printf("Erro ao tentar abrir o arquivo.");
    }else{
          while(fread(&livro,sizeof(material),1,registros) == 1){
                n++;
          }
          for(i=n-2;i>0;i--){ // ordenacao por bubble
              for(j=1;j<=i;j++){
                    fseek(registros,(j-1)*sizeof(material),SEEK_SET);
                    fread(&livro,sizeof(material),1,registros);
                    fseek(registros,j*sizeof(material),SEEK_SET);
                    fread(&livroAlf,sizeof(material),1,registros);
                    if(strcmp(livro.titulo,livroAlf.titulo)>0){
                          livroAlf2=livro; //livroAlf2 ponteiro temp auxiliar
                          livro=livroAlf;
                          livroAlf=livroAlf2;
                          fseek(registros,(j-1)*sizeof(material),SEEK_SET);
                          fwrite(&livro,sizeof(material),1,registros);
                          fseek(registros,j*sizeof(material),SEEK_SET);
                          fwrite(&livroAlf,sizeof(material),1,registros);
                    }
        
              }
          }                      
          fclose(registros);
    }      
}

void listar(){
      FILE *registros;    
      struct material livro;
      int i=6;
      templateLinhas();
      bubbleSort();
      if((registros = fopen("registros.dat","ab+"))== NULL){
	    	printf("Erro ao tentar abrir o arquivo.");
      }else{
         gotoxy(33, 2);
         printf("Materiais cadastrados"); 
         gotoxy(3, 5);  
         printf("|REGISTRO  |TITULO                   |AUTOR                |VALOR          |\n");   
         while(fread(&livro,sizeof(material),1,registros) == 1){
            gotoxy(3, i++);  
            printf("|%10i|%25s|%21s|RS%13.2f|\n",livro.codigo,livro.titulo,livro.autor,livro.valor);
        }  
      }
     fclose(registros);
     system("pause>null");
}

void buscar(){
      FILE *registros;    
      struct material livro;
      char busca[50],titulo[50],autor[50];
      int i=8,qtd=0;
      templateLinhas();
      //bubbleSort();
      if((registros = fopen("registros.dat","ab+"))== NULL){
	    	printf("Erro ao tentar abrir o arquivo.");
      }else{
         gotoxy(33, 2);
         printf("Buscar Materiais"); 
         gotoxy(3, 5);  
         printf("O que voce procura? ");
         fflush(stdin);
         gets(busca);
         gotoxy(3, 7);  
         printf("|REGISTRO  |TITULO                   |AUTOR                |VALOR          |\n");   
         while(fread(&livro,sizeof(material),1,registros) == 1){
            strcpy(titulo,livro.titulo);
            strcpy(autor,livro.autor);
            if((strstr(strlwr(titulo),strlwr(busca)) != NULL)||(strstr(strlwr(autor),strlwr(busca)) != NULL)){
		        gotoxy(3, i++); 
                printf("|%10i|%25s|%21s|RS%13.2f|\n",livro.codigo,livro.titulo,livro.autor,livro.valor);
                qtd++;
		    }
         }
         if(qtd == 0){
                gotoxy(29, 15);  
                printf("Nenhum registro encontrado\n");
         }else if(qtd == 1){
               gotoxy(55, 5);  
               printf("%i registro encontrado",qtd);
         }else{
               gotoxy(55, 5);  
               printf("%i registros encontrados",qtd);
         }
      }
     fclose(registros);
     system("pause>null");
}

void templateLinhas(){
     int i;
     textbackground(BLUE);
     textcolor(YELLOW);    
     clrscr();            
     //Linha topo
     gotoxy(0, 0);
     printf("\xc9");
     for(i=0;i<78;i++)
        printf("\xcd");
     printf("\xbb");
     //Linha esqueda
     for(i=0;i<23;i++){
        gotoxy(1, i+2);
        printf("\xba");
     }
     //Linha direita
     for(i=0;i<23;i++){
        gotoxy(80, i+2);
        printf("\xba");
     }
     //Linha rodape
     gotoxy(1, 24);
     printf("\xc8");
     for(i=0;i<78;i++){
        gotoxy(i+2, 24);
        printf("\xcd");
     }
     gotoxy(80, 24);  
     printf("\xbc");
     //Linha topo 2
     for(i=0;i<78;i++){
        gotoxy(i+2, 3);
        printf("\xcd");
     }
     gotoxy(80, 3);  
     printf("\xb9");
     gotoxy(1, 3);  
     printf("\xcc");
     //creditos
     gotoxy(22, 25);
     printf("Sistema BiblioC - 1.0 - Jeferson Oliveira");
}
