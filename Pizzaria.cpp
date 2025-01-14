#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>
#define TF 50

struct TpData{
	int d, m, a;
};

struct TpPizza{
	int codigo;
	int quant;
	char desc[TF],status;
	float valor;
	
};

struct TpCliente{
	int cep;
	float totalgasto;
	char nome[TF],endereco[TF],cidade[TF],telefone[TF],status;
	TpPizza pizza;
	int pedidos;
};

struct TpPedidos{
	int situacao,codigo,numero; // codigo é da piza / situacao é a do pedido / numero é o numero do pedido
	char cpf[TF],telefone[TF],status; // cpf do moto / telefone cliente / status do pedido A/I
	TpData data;
	
};

struct TpMotoqueiro{
	TpData data;
	char nome[TF],cpf[TF],telefone[TF] ,endereco[TF],status;
};


//moldura

void Moldura(int CI, int LI,int CF,int LF, int frente,int fundo){
	int a = 0;
	textcolor(frente);
	textbackground(fundo);
	gotoxy(CI,LI); printf("%c",201);
	gotoxy(CF,LI); printf("%c",187);
	gotoxy(CI,LF); printf("%c",200);
	gotoxy(CF,LF); printf("%c",188);
	
	for (a = CI+1 ; a < CF; a++){
		gotoxy(a,LI); printf("%c", 205);
		gotoxy(a, LF); printf("%c",205);
	}
	
	for (a = LI+1 ; a < LF; a++){
		gotoxy(CI,a); printf("%c", 186);
		gotoxy(CF,a); printf("%c",186);
	}
	
	textcolor(7);
	textbackground(0);
	printf("\n\n\n\n");
	
	
}

void FormPrincipal(void){
	
	Moldura (1,1,120,30,5,6); //  coluna inicial y // linha inicialx // coluna final // linha final 
	Moldura(2,2,119,4,13,9);
	gotoxy(50,3); printf("==PIZZARIA DO MALAGA==");
	Moldura(2,5,40,29,7,2);
	//Menu
	Moldura(41,5,119,29,4,5);
}

void LimpaTela(){
	
	for(int i = 6;i < 28; i++){
		gotoxy(43,i);
		printf("                                                                           ");
	}
	gotoxy(43,6);
}

void LimpaTela2(){
	
	for(int i = 6;i < 25; i++){
		gotoxy(3,i);
		printf("                                     ");
	}

	gotoxy(43,6);
}
//ORDENACOES
void OrdenaCliente(){
	int a,b,max;
	TpCliente c1,c2;
	
	FILE *ptr = fopen("Clientes.dat","rb+");
	
	 if (ptr == NULL){
		 printf("ERRO");
	 	
	 }		
	 	else{
			fseek(ptr,0,2);
			max = ftell(ptr)/sizeof(TpCliente);
			
			for(a=0; a<max; a++)
				for(b=0; b<max-1; b++)
				{
					fseek(ptr,b*sizeof(TpCliente),0);
					fread(&c1,sizeof(TpCliente),1,ptr);
					
					fseek(ptr,(b+1)*sizeof(TpCliente),0);
					fread(&c2,sizeof(TpCliente),1,ptr);
					
					if(c1.pedidos < c2.pedidos)
					{
						fseek(ptr,b*sizeof(TpCliente),0);
						fwrite(&c2,sizeof(TpCliente),1,ptr);
						
						fseek(ptr,(b+1)*sizeof(TpCliente),0);
						fwrite(&c1,sizeof(TpCliente),1,ptr);
					}
				}
				
			fclose(ptr);

		 }
}

void OrdenaPedidoSelecao(void){
    TpPedidos p,p2;

    FILE *ptr=fopen("Pedidos.dat","rb+");
    int tam,menor,i,j;

    fseek(ptr,0,2);
    tam=ftell(ptr)/sizeof(TpPedidos);

    fseek(ptr,0,0);
    fread(&p,sizeof(TpPedidos),1,ptr);
    for(i=0;i<tam;i++){
        menor=i*sizeof(TpPedidos);

        for(j=i+1;j<tam;j++){
            fseek(ptr,menor,0);
            fread(&p2,sizeof(TpPedidos),1,ptr);

            fseek(ptr,j*sizeof(TpPedidos),0);
            fread(&p,sizeof(TpPedidos),1,ptr);

            if(p.numero<p2.numero){
                menor = j*sizeof(TpPedidos);
            }
        }
        if(menor!=i*sizeof(TpPedidos)){
            fseek(ptr,menor,0);
            fread(&p2,sizeof(TpPedidos),1,ptr);

            fseek(ptr,i*sizeof(TpPedidos),0);
            fread(&p,sizeof(TpPedidos),1,ptr);


            fseek(ptr,i*sizeof(TpPedidos),0);
            fwrite(&p2,sizeof(TpPedidos),1,ptr);

            fseek(ptr,menor,0);
            fwrite(&p,sizeof(TpPedidos),1,ptr);
        }
    }
    fclose(ptr);
}


void OrdenaRanking(void) {
    int a, b, max;
    TpPizza p1, p2;

    FILE *ptr = fopen("Pizzas.dat", "rb+");

    if (ptr == NULL) {
        printf("ERRO");
    } else {
        fseek(ptr, 0, 2);
        max = ftell(ptr) / sizeof(TpPizza);

        for (a = 0; a < max - 1; a++) {  
            for (b = 0; b < max - a - 1; b++) {  
                fseek(ptr, b * sizeof(TpPizza), 0);
                fread(&p1, sizeof(TpPizza), 1, ptr);

                fseek(ptr, (b + 1) * sizeof(TpPizza), 0);
                fread(&p2, sizeof(TpPizza), 1, ptr);

                if (p1.quant < p2.quant) {
                    fseek(ptr, b * sizeof(TpPizza), 0);
                    fwrite(&p2, sizeof(TpPizza), 1, ptr);

                    fseek(ptr, (b + 1) * sizeof(TpPizza), 0);
                    fwrite(&p1, sizeof(TpPizza), 1, ptr);
                }
            }
        }

        fclose(ptr);
    }
}

void OrdenaRankingContra(void){
	//BUBBLE
	int a,b,max;
	TpPizza p1,p2;
	
	FILE *ptr = fopen("Pizzas.dat","rb+");
	
	 if (ptr == NULL){
		 printf("ERRO");
	 	
	 }		
	 	else{
			fseek(ptr,0,2);
			max = ftell(ptr)/sizeof(TpPizza);
			
			for(a=0; a<max; a++)
				for(b=0; b<max-1; b++)
				{
					fseek(ptr,b*sizeof(TpPizza),0);
					fread(&p1,sizeof(TpPizza),1,ptr);
					
					fseek(ptr,(b+1)*sizeof(TpPizza),0);
					fread(&p2,sizeof(TpPizza),1,ptr);
					
					if(p1.quant > p2.quant)
					{
						fseek(ptr,b*sizeof(TpPizza),0);
						fwrite(&p2,sizeof(TpPizza),1,ptr);
						
						fseek(ptr,(b+1)*sizeof(TpPizza),0);
						fwrite(&p1,sizeof(TpPizza),1,ptr);
					}
				}
				
			fclose(ptr);

	}
}

void OrdenaPizza(void){
	//BUBBLE
	TpPizza p1,p2;
	
	FILE *ptr=fopen("Pizzas.dat","rb+");
	int tam,menor,i,j;
	
	fseek(ptr,0,2);
	tam=ftell(ptr)/sizeof(TpPizza);
	
	fseek(ptr,0,0);
	fread(&p1,sizeof(TpPizza),1,ptr);
	for(i=0;i<tam;i++){
		menor=i*sizeof(TpPizza);
		
		for(j=i+1;j<tam;j++){
			fseek(ptr,menor,0);
			fread(&p2,sizeof(TpPizza),1,ptr);
			
			fseek(ptr,j*sizeof(TpPizza),0);
			fread(&p1,sizeof(TpPizza),1,ptr);
			
			if(p1.codigo<p2.codigo){
				menor = j*sizeof(TpPizza);
			}
		}
		if(menor!=i*sizeof(TpPizza)){
			fseek(ptr,menor,0);
			fread(&p2,sizeof(TpPizza),1,ptr);
			
			fseek(ptr,i*sizeof(TpPizza),0);
			fread(&p1,sizeof(TpPizza),1,ptr);
			
			
			fseek(ptr,i*sizeof(TpPizza),0);
			fwrite(&p2,sizeof(TpPizza),1,ptr);
			
			fseek(ptr,menor,0);
			fwrite(&p1,sizeof(TpPizza),1,ptr);			
		}
	}
	fclose(ptr);
}



//BUSCAS

int BuscaCliente(FILE*ptr,char numero[TF]){
    // busca exaustiva
    TpCliente cliente;

    fseek(ptr,0,0);

    fread(&cliente,sizeof(TpCliente),1,ptr);

        while(!feof(ptr) && stricmp(cliente.telefone,numero) != 0)
            fread(&cliente,sizeof(TpCliente),1,ptr);
        if(stricmp(cliente.telefone,numero) == 0 && cliente.status == 'A')
            return ftell(ptr) - sizeof(TpCliente); 
        else
            return -1;
}



int BuscaMotoqueiro(FILE*ptr,char cpf[TF]){
	TpMotoqueiro moto;
	
	fseek(ptr,0,0);
	
	fread(&moto,sizeof(TpMotoqueiro),1,ptr);
	
	while(!feof(ptr) && stricmp(moto.cpf,cpf) != 0)
		fread(&moto,sizeof(TpMotoqueiro),1,ptr);
	if (stricmp(moto.cpf,cpf) == 0  && moto.status == 'A')
		return ftell(ptr) - sizeof(TpMotoqueiro);
	else
		return -1;
	
}


int BuscaPedido(FILE *ptr,int numero){
	TpPedidos p;
	fseek(ptr,0,0);
	
	fread(&p,sizeof(TpPedidos),1,ptr);
	while(!feof(ptr) && p.numero != numero)
		fread(&p,sizeof(TpPedidos),1,ptr);
	if(p.numero == numero  && p.status == 'A')
		return ftell(ptr) - sizeof(TpPedidos);
	else
		return -1;
	
}

int BuscaPizza(FILE *ptr ,int cod){
	TpPizza p;
	
	int ajud,tam,i=0;
	
	fseek(ptr,0,2);	
	tam=ftell(ptr)/sizeof(TpPizza);
	
	fseek(ptr,0,0);
	fread(&p,sizeof(TpPizza),1,ptr);
	while(i<tam && (cod>p.codigo ||p.status!='A')){
		i++;
		fread(&p,sizeof(TpPizza),1,ptr);
	}
				
	if(i<tam && p.codigo == cod && p.status=='A')
		return ftell(ptr)-sizeof(TpPizza);
	else
		return -1;
}

//VERIFICACOES

int VerificaData(int d, int m, int a) {
    if ((d > 0 && d <= 31) && (m >= 1 && m <= 12) && (a > 1800 && a <= 2024)) {
        return 1;
    } else {
        return 0;
    }
}

int VerificaCPF(char cpf[TF]){
	
	//Se Retornar [1] CPF é válido || se retornar [0] CPF é inválido
	
	// DIGITO 1
	
	int soma = 0, j, veri, veri2, div;
	
    for(int i = 0, j = 10; i < 9; j--, i++)
    	soma += (cpf[i] - 48) * j;
    
    div = soma % 11;
    
    veri = 11 - div;
    
    if(veri >= 10)
    	veri = 0;
    
    // DIGITO 2
    
    soma = 0;
    
    for(int i = 0, j = 11; i < 10; j--, i++)
    	soma += (cpf[i] - 48) * j;
    
    div = soma % 11;
    
    veri2 = 11 - div;
    
    if(veri >= 10)
    	veri2 = 0;
    
    // RETURNS
    
	if(veri == (cpf[9] - 48) && veri2 == (cpf[10] - 48)) // CPF VALIDO
		return 1;
	
	else // CPF INVALIDO
		return 0;
}

//EXCLUSOES LOGICAS

void ExcLogicaMoto(void){
	TpMotoqueiro moto;
	
	
	
	FILE*ptr= fopen("Motoqueiros.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("----> EXCLUSAO LOGICA MOTOQUEIRO <----");
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro na abertura do arquivo!\n");
		
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Digite o CPF do motoqueiro:");
		fflush(stdin);
		gets(moto.cpf);
		
		int pos = BuscaMotoqueiro(ptr,moto.cpf);
		
		if(pos != -1){
			gotoxy(43,10); textcolor(6);
			printf("--->Dados do motoqueiro<---\n");
			fseek(ptr,pos,0);
			fread(&moto,sizeof(TpMotoqueiro),1,ptr);
			gotoxy(43,11); textcolor(6);
			printf("%s \t %s \t %s\n",moto.cpf, moto.nome, moto.endereco);
			gotoxy(43,12); textcolor(6);
			printf("Deseja excluir este motoqueiro? [S/N]\n");
			
			if(toupper(getche()) == 'S' && moto.status == 'A'){
				gotoxy(43,14); textcolor(6);
				printf("Cliente excluido com sucesso!\n");
				
				moto.status = 'I';
				
				fseek(ptr,pos,0);
				fwrite(&moto,sizeof(TpMotoqueiro),1,ptr);
				
				getche();
			}
			
			
		}
		else{
			gotoxy(43,11); textcolor(6);
			printf("Motoqueiro nao encontrado!\n");
			getche();
			
		}
		
		fclose(ptr);
		
		
	}
	
	LimpaTela();
}

void ExcLogicaPedido(void){
	TpPedidos p;
	
	
	
	FILE*ptr= fopen("Pedidos.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("---->EXCLUSAO LOGICA PEDIDO<----");
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro na abertura do arquivo!");
		
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Digite o numero do pedido:");
		scanf("%d",&p.numero);
		
		int pos = BuscaPedido(ptr,p.numero);
		
		if(pos != -1){
			gotoxy(43,10); textcolor(6);
			printf("--->Dados do pedido<---");
			fseek(ptr,pos,0);
			fread(&p,sizeof(TpPedidos),1,ptr);
			
			gotoxy(43,11); textcolor(6);
			printf("Nmr do pedido:%d \t CPF do Motoqueiro:%s \tTel Cliente:%s \t Cod da pizza:%d\n",p.numero,p.cpf,p.telefone,p.codigo);
			gotoxy(43,12); textcolor(6);
			printf("Deseja excluir este pedido? [S/N]\n");
			
			if(toupper(getche()) == 'S' && p.status == 'A'){
				gotoxy(43,14); textcolor(6);
				printf("Pedido excluido com sucesso!\n");
				
				p.status = 'I';
				
				fseek(ptr,pos,0);
				fwrite(&p,sizeof(TpPedidos),1,ptr);
				
				getche();
			}
			
			
		}
		else{
			gotoxy(43,10); textcolor(6);
			printf("Pedido nao encontrado!\n");
			getche();
			
		}
		
		fclose(ptr);
		
		
	}
	
	LimpaTela();
}


void ExcLogicaCliente(void){
	TpCliente c;
	
	
	gotoxy(43,6); textcolor(6);
	printf("---->EXCLUSAO LOG CLIENTE<----");
	FILE*ptr= fopen("Clientes.dat","rb+");
	
	if(ptr == NULL){
		gotoxy(43,7); textcolor(6);
		printf("Erro na abertura do arquivo!");
		
	}
	else{
		gotoxy(43,7); textcolor(6);
		printf("Digite o telefone do cliente:");
		fflush(stdin);
		gets(c.telefone);
		
		int pos = BuscaCliente(ptr,c.telefone);
		
		if(pos != -1){
			gotoxy(43,9); textcolor(6);
			printf("--->Dados da pessoa<---");
			fseek(ptr,pos,0);
			fread(&c,sizeof(TpCliente),1,ptr);
			
			gotoxy(43,10); textcolor(6);
			printf("%s \t %s \t %s",c.telefone, c.nome, c.endereco);
			gotoxy(43,11); textcolor(6);
			printf("Deseja excluir este cliente? [S/N]");
			
			if(toupper(getche()) == 'S' && c.status == 'A'){
				gotoxy(43,13); textcolor(6);
				printf("Cliente excluido com sucesso!");
				
				c.status = 'I';
				
				fseek(ptr,pos,0);
				fwrite(&c,sizeof(TpCliente),1,ptr);
				
				getche();
			}
			
			
		}
		else{
			gotoxy(43,9); textcolor(6);
			printf("Cliente nao encontrado!\n");
			getche();
			
		}
		
		fclose(ptr);
		
		
	}
	
	LimpaTela();
}


void ExcLogicaPizza(void){
	TpPizza pizza;
	
	
	gotoxy(43,6); textcolor(6);
	printf("---->EXCLUSAO LOGICA PIZZA<----");
	FILE*ptr= fopen("Pizzas.dat","rb+");
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro na abertura do arquivo!\n");
		
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Digite o codigo da Pizza:");
		scanf("%d",&pizza.codigo);
		
		int pos = BuscaPizza(ptr,pizza.codigo);
		
		if(pos != -1){
			gotoxy(43,9); textcolor(6);
			printf("---> Pizza a excluir <---\n");
			fseek(ptr,pos,0);
			fread(&pizza,sizeof(TpPizza),1,ptr);
			gotoxy(43,10); textcolor(6);
			printf("%d \t %s \t %.2f\n",pizza.codigo, pizza.desc, pizza.valor);
			gotoxy(43,11); textcolor(6);
			printf("Deseja excluir esta pizza? [S/N]");
			
			if(toupper(getche()) == 'S' && pizza.status == 'A'){
				gotoxy(43,13); textcolor(6);
				printf("Pizza excluida com sucesso!\n");
				
				pizza.status = 'I';
				
				fseek(ptr,pos,0);
				fwrite(&pizza,sizeof(TpPizza),1,ptr);
				
				getche();
			}
			
		}
		else{
			gotoxy(43,10); textcolor(6);
			printf("Pizza nao encontrado!\n");
			getche();
			
		}
		
		fclose(ptr);
		
	}
	
	LimpaTela();
}


// EXCLUSOES FISICAS

void ExcFisicaPedido(void){
	TpPedidos p;
	int auxnum;
	
	
	gotoxy(43,6); textcolor(6);
	printf("----->Excluir Pedido<----");
	
	FILE*ptr = fopen("Pedidos.dat","rb");
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro na abertura!");
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Pedido a Excluir:"); 
		scanf("%d",&auxnum);
		
	
		int pos = BuscaPedido(ptr,auxnum);
		fseek(ptr,pos,0);
		if(pos == -1){
			gotoxy(43,9); textcolor(6);
			printf("Pedido nao cadastrado!!");
		}
		else{
			gotoxy(43,9); textcolor(6);
			printf("--->Dados do pedido<---\n");
			fseek(ptr,pos,0);
			fread(&p,sizeof(TpPedidos),1,ptr);
			gotoxy(43,10); textcolor(6);
			printf("Numero do cliente: %s  CPF do motoqueiro: %s",p.telefone,p.cpf);
			gotoxy(43,11); textcolor(6);
			printf("Numero do pedido: %d  Codigo da pizza: %d",p.numero,p.codigo);
			gotoxy(43,12); textcolor(6);
			printf("Deseja Excluir? (S/N)");
				if(toupper(getche()) == 'S'){
					FILE*ptrnovo = fopen("novoarq.dat","wb");
					fseek(ptr,0,0);
					fread(&p,sizeof(TpPedidos),1,ptr);
					while(!feof(ptr)){
						
						if(auxnum != p.numero){
							fwrite(&p,sizeof(TpPedidos),1,ptrnovo);
						}
						fread(&p,sizeof(TpPedidos),1,ptr);
					}
					fclose(ptr);
					fclose(ptrnovo);
					
					remove("Pedidos.dat");
					rename("novoarq.dat","Pedidos.dat");
					
					gotoxy(43,14); textcolor(6);
					printf("Cliente Excluido com sucesso!");
				
				}
				else
					fclose(ptr);
			
		}
	}
	getche();
	
	LimpaTela();
}

void ExcFisicaCliente(void){
	TpCliente c;
	int ano;
	char auxnumero[TF];
	
	
	gotoxy(43,6); textcolor(6);
	printf("----->Excluir Cliente<----");
	
	FILE*ptr = fopen("Clientes.dat","rb");
	
	
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("\nErro na abertura!");
	}
	else{
		gotoxy(43,7); textcolor(6);
		printf("Numero a Excluir:"); 
		fflush(stdin);
		gets(auxnumero);
		
		
	
		if(strlen(auxnumero) == 9){
			int pos = BuscaCliente(ptr,auxnumero);
			fseek(ptr,pos,0);
			if(pos == -1){
				gotoxy(43,8); textcolor(6);
				printf("Cliente nao cadastrado!!");
				fclose(ptr);
			}
			else{
				gotoxy(43,8); textcolor(6);
				printf("--->Dados da pessoa<---\n");
				fseek(ptr,pos,0);
				fread(&c,sizeof(TpCliente),1,ptr);
				gotoxy(43,10); textcolor(6);
				printf("Nome do cliente: %s  Numero do cliente: %s",c.nome,c.telefone);
				gotoxy(43,11); textcolor(6);
				printf("Endereco: %s  Cidade: %s  CEP: %d",c.endereco,c.cidade,c.cep);
				gotoxy(43,12); textcolor(6);
				printf("Deseja Excluir? (S/N)");
				if(toupper(getche()) == 'S'){
					FILE*ptrnovo = fopen("novoarq.dat","wb");
					fseek(ptr,0,0);
					fread(&c,sizeof(TpCliente),1,ptr);
					while(!feof(ptr)){
						
						if(stricmp(auxnumero,c.telefone) != 0){
							fwrite(&c,sizeof(TpCliente),1,ptrnovo);
						}
						fread(&c,sizeof(TpCliente),1,ptr);
					}
					fclose(ptr);
					fclose(ptrnovo);
					
					remove("Clientes.dat");
					rename("novoarq.dat","Clientes.dat");
					gotoxy(43,14); textcolor(6);
					printf("Cliente Excluido com sucesso!");
				
				}
				else
					fclose(ptr);
			}	
			
			
		}
		else
			fclose(ptr);

	}
	getche();
	LimpaTela();
}



void ExcFisicaMoto(void){
	TpMotoqueiro moto;
	int ano;
	char cpf[TF];
	
	
	
	gotoxy(43,6); textcolor(6);
	printf("----->Excluir Motoqueiro<----");
	
	FILE*ptr = fopen("Motoqueiros.dat","rb");
	
	
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro na abertura!");
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("CPF a Excluir:"); 
		fflush(stdin);
		gets(cpf);
		
		
		if(strlen(cpf) == 11){
			int pos = BuscaMotoqueiro(ptr,cpf);
			if(pos == -1){
				gotoxy(43,9); textcolor(6);
				printf("Motoqueiro nao cadastrado!!\n");
				fclose(ptr);
			}
			else{
				gotoxy(43,9); textcolor(6);
				printf("--->Dados do Motoqueiro<---\n");
				fseek(ptr,pos,0);
				fread(&moto,sizeof(TpMotoqueiro),1,ptr);
				gotoxy(43,10); textcolor(6);
				printf("Nome do Motoqueiro: %s  CPF: %S",moto.nome,moto.cpf);
				gotoxy(43,11); textcolor(6);
				printf("Endereco: %s  Data de admissao: %d/%d/%d",moto.endereco,moto.data.d,moto.data.m,moto.data.a);
				gotoxy(43,12); textcolor(6);
				printf("Deseja Excluir? (S/N)");
				if(toupper(getche()) == 'S'){
					FILE*ptrnovo = fopen("novoarq.dat","wb");
					fseek(ptr,0,0);
					fread(&moto,sizeof(TpMotoqueiro),1,ptr);
					while(!feof(ptr) && moto.status == 'A'){
						
						if(stricmp(cpf,moto.cpf) != 0){
							fwrite(&moto,sizeof(TpMotoqueiro),1,ptrnovo);
						}
						fread(&moto,sizeof(TpMotoqueiro),1,ptr);
					}
					fclose(ptr);
					fclose(ptrnovo);
					
					remove("Motoqueiros.dat");
					rename("novoarq.dat","Motoqueiros.dat");
					
					gotoxy(43,14); textcolor(6);
					printf("Motoqueiro excluido com sucesso!");
				
				}
				else
					fclose(ptr);
			}		
		}
		else
			fclose(ptr);	
	}
	getche();
	LimpaTela();
}



void ExcFisicaPizza(void){
	TpPizza pizza;
	int codigo;
	
	
	gotoxy(43,6); textcolor(6);
	printf("----->Excluir Pizza<----");
	
	FILE *ptr = fopen("Pizzas.dat","rb");
	
	
	if(ptr == NULL){
		gotoxy(43,7); textcolor(6);
		printf("Erro na abertura!");
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Codigo da pizza a Excluir:"); 
		scanf("%d",&codigo);
		
	
		if(codigo != 0){
			
			int pos = BuscaPizza(ptr,codigo);
			
			if(pos == -1){
				gotoxy(43,8); textcolor(6);
				printf("Pizza nao cadastrada!!\n");
				fclose(ptr);
			}
			else{
				gotoxy(43,8); textcolor(6);
				printf("---> Dados da pizza<---");
				fseek(ptr,pos,0);
				fread(&pizza,sizeof(TpPizza),1,ptr);
				gotoxy(43,9); textcolor(6);
				printf("Codigo: %d   Descricao: %s   Valor: %.2f\n",pizza.codigo ,pizza.desc ,pizza.valor);
				gotoxy(43,10); textcolor(6);
				printf("Deseja Excluir? (S/N):");
				if(toupper(getche()) == 'S'){
					FILE*ptrnovo = fopen("novoarq.dat","wb");
					fseek(ptr,0,0);
					fread(&pizza,sizeof(TpPizza),1,ptr);
					while(!feof(ptr) && pizza.status == 'A'){
						
						if(codigo != pizza.codigo){
							fwrite(&pizza,sizeof(TpPizza),1,ptrnovo);
						}
						fread(&pizza,sizeof(TpPizza),1,ptr);
					}
					fclose(ptr);
					fclose(ptrnovo);
					
					remove("Pizzas.dat");
					rename("novoarq.dat","Pizzas.dat");
					
					gotoxy(43,12); textcolor(6);
					printf("Pizza excluida com sucesso!");
				
				}
				else
					fclose(ptr);
			}	
			
			
		}
		else
			fclose(ptr);

	}
	getche();
	LimpaTela();
}



// RELATORIOS
void RelatorioTodosCliente(){
	
    FILE *ptrclientes = fopen("Clientes.dat", "rb");
    FILE *ptrpedidos = fopen("Pedidos.dat", "rb");
    FILE *ptrpizzas = fopen("Pizzas.dat", "rb");

    TpCliente clientes;
    TpPedidos pedidos;
    TpPizza pizzas;
    float total;
    int i=8;
    gotoxy(43,6); textcolor(6);
	printf("-->RELATORIO TODOS CLIENTES<--");
    if(ptrclientes == NULL || ptrpedidos == NULL || ptrpizzas == NULL){
    	gotoxy(43,i); textcolor(6);
    	printf("Erro de abertura!");
    }

    else{
		
        fseek(ptrclientes, 0, 0);
    	fread(&clientes, sizeof(TpCliente), 1, ptrclientes);
        while(!feof(ptrclientes)){
        		
        	if(clientes.status == 'A'){
        		
        		gotoxy(43,++i); textcolor(6);
        		printf("----> CLIENTES E SEUS PEDIDOS <----");
        			
    			gotoxy(43,++i); textcolor(6);
        		printf("----> DADOS DO CLIENTE <----");
        		gotoxy(43,++i); textcolor(6);
	            printf("Cliente: %s", clientes.nome);
	            gotoxy(43,++i); textcolor(6);
	            printf("Telefone: %s", clientes.telefone);
	            gotoxy(43,++i); textcolor(6);
	            printf("Endereco: %s", clientes.endereco);
	            gotoxy(43,++i); textcolor(6);
	            printf("Cidade: %s", clientes.cidade);
	            gotoxy(43,++i); textcolor(6);
	            printf("CEP: %d", clientes.cep);
	            gotoxy(43,++i); textcolor(6);
	            printf("\t\tPEDIDOS:");
	            
	            int encontrou = 0;
	            total = 0;
	            
	            fseek(ptrpedidos, 0, 0);
	    		
	            while(fread(&pedidos, sizeof(pedidos), 1, ptrpedidos) != 0)
		        	if(stricmp(pedidos.telefone, clientes.telefone) == 0){
		        		
		        		encontrou = 1;
		        		fseek(ptrpizzas, 0, 0);
		        		
		        		while(fread(&pizzas, sizeof(pizzas), 1, ptrpizzas) != 0)
		                	if(pizzas.codigo == pedidos.codigo){
		                		
		                		gotoxy(43,++i); textcolor(6);
		                		printf("Pizzas Pedidas: %s", pizzas.desc);
		                		gotoxy(43,++i); textcolor(6);
		                		printf("Preco: R$ %.2f", pizzas.valor);
		                		total += pizzas.valor;
		                	}
		        	}
		    	
		        if (encontrou == 0){
		    
		        	gotoxy(43,++i); textcolor(6);
		            printf("Cliente sem pedidos.");
		        }
    			
	            gotoxy(43,++i); textcolor(6);
	            printf("Total Gasto: R$ %.2f",clientes.totalgasto);
	            gotoxy(43,++i); textcolor(6);
	            printf("--------------------------");
	            
	            /*for(int j = 5; j > 0; j--){
	            	
	            	gotoxy(79, 27);
	            	printf("Proxima pagina em %d segundos!", j);
	            	Sleep(1000);
	            }*/
	            
	            //LimpaTela();
				
				i = 8;
        	}
        	fread(&clientes, sizeof(clientes), 1, ptrclientes);
        }
    }
    
    fclose(ptrclientes);
    fclose(ptrpedidos);
    fclose(ptrpizzas);
    
    getch();
    LimpaTela();
}

void PizzaCaminho(){
	
	
	int i = 8;
	TpPedidos p;
	int flag = 0;
	gotoxy(43,6); textcolor(6);
	printf("----> PEDIDOS A CAMINHO <----\n");
	
	FILE*ptr = fopen("Pedidos.dat","rb+");
	
	fseek(ptr,0,0);
	while(fread(&p,sizeof(TpPedidos),1,ptr) == 1){
			if(p.status == 'A' && p.situacao == 2){
				gotoxy(43,++i); textcolor(6);
				printf("Pedido numero: %d esta a caminho!\n",p.numero);
				fread(&p,sizeof(TpPedidos),1,ptr);
				flag = 1;
						
			}
	}	
	
	if(flag != 1){
			gotoxy(43,8); textcolor(6);
			printf("Nenhum pedido a caminho!\n");
	}
		
	fclose(ptr);
	getch();
	LimpaTela();
}

void PizzaAndamento(){
	
	
	int i=8;
	TpPedidos p;
	int flag = 0;
	gotoxy(43,6); textcolor(6);
	printf("----> PEDIDOS EM PREPARO <----\n");
	
	FILE*ptr = fopen("Pedidos.dat","rb+");
	
	fseek(ptr,0,0);
	while(!feof(ptr)){
		fread(&p,sizeof(TpPedidos),1,ptr);
		if(p.status == 'A' && p.situacao == 1){
			gotoxy(43,++i); textcolor(6);
			printf("Pedido numero: %d esta em preparo!\n",p.numero);
			fread(&p,sizeof(TpPedidos),1,ptr);
			flag = 1;
					
		}
	}	
	
	if(flag != 1){
			gotoxy(43,8); textcolor(6);
			printf("Nenhum pedido em preparo!\n");
	}
		
	fclose(ptr);
	getch();
	LimpaTela();
}




void RankingPizza(){	
	
	TpPizza pizza;
	int i = 9;
	FILE *ptr = fopen("Pizzas.dat","ab+");
	OrdenaRanking();
	
	gotoxy(43,6); textcolor(6);
	printf("---->RANKING<----");
	gotoxy(43,8); textcolor(6);
	printf("Da mais pedida pra menos pedida!");
    if(ptr==NULL){
    	gotoxy(43,++i); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    	getch();
    }
        else{
        	fseek(ptr,0,0);
			fread(&pizza,sizeof(TpPizza),1,ptr);
        		while(!feof(ptr)){
					if(pizza.status == 'A'){
						gotoxy(43,++i); textcolor(6);
						printf("Codigo: %d", pizza.codigo);
						gotoxy(43,++i); textcolor(6);
						printf("Desc: %s", pizza.desc);
						gotoxy(43,++i); textcolor(6);
						printf("Valor: %.2f", pizza.valor);	
						gotoxy(43,++i); textcolor(6);
						printf("Quant: %d",pizza.quant);	
					}
					fread(&pizza,sizeof(TpPizza),1,ptr);
        		}			
		}
		fclose(ptr);
		getch();
		LimpaTela();
}


void RelatorioLetra() {
    TpCliente c;
    int flag = 0;
    char letra;
    int i = 9;

    gotoxy(43, 6);
    textcolor(6);
    printf("---->RELATORIO POR LETRA<----\n");

    FILE *ptr = fopen("Clientes.dat", "rb");
    if (ptr == NULL) {
        gotoxy(43, 7);
        textcolor(6);
        printf("Erro ao abrir arquivo de clientes!");
    }

    gotoxy(43, 7);
    textcolor(6);
    printf("Digite a letra a pesquisar: ");
    fflush(stdin);
    letra = getchar();

    fseek(ptr, 0, 0);

    while (fread(&c, sizeof(TpCliente), 1, ptr) == 1) {
        if (c.status == 'A' && c.nome[0] == letra) {
            gotoxy(43, ++i);
            textcolor(6);
            printf("Cliente: %s", c.nome);
            flag = 1;
        }
    }

    if (flag != 1) {
        gotoxy(43, 9);
        textcolor(6);
        printf("Nao ha ninguem cadastrado com essa inicial!");
    }

    fclose(ptr);
    getche();
    LimpaTela();
}

int ValidaIntervaloData (int dia1, int mes1, int ano1, int dia2, int mes2, int ano2){

    if (ano1 < ano2)
        return 1;
    if (ano1 > ano2)
        return 0;
    if (mes1 < mes2)
        return 1;
    if (mes1 > mes2)
        return 0;
    if (dia1 <= dia2)
        return 1;

    return 0;
}

int ValidaData (int d, int m, int a){ //1 --> true | 0 --> false

    if (a < 1)
        return 0;

    if (m < 1 || m > 12)
        return 0;

    if (d < 1 || d > 31)
        return 0;

    // Verificar os dias de cada mÃ¯Â¿Â½s
    
    if (m == 2) // Fevereiro
        if (d > 28)
            return 0;
	
	else if (m == 4 || m == 6 || m == 9 || m == 11) // Abril, Junho, Setembro, Novembro
        if (d > 30)
            return 0;
	
	else // Janeiro, MarÃ¯Â¿Â½o, Maio, Julho, Agosto, Outubro, Dezembro
        if (d > 31)
            return 0;

    return 1;
}

void RelatorioMotoPizza(void){
	
	FILE * ptrpedido = fopen("Pedidos.dat", "rb");
    FILE * ptrmotoqueiro = fopen("Motoqueiros.dat", "rb");
	
    TpMotoqueiro M;
    TpPedidos P;
	
    int dia1, dia2, mes1, mes2, ano1, ano2;
    int count, y = 13;
    int i = 8;
	
	
    if(ptrpedido == NULL || ptrmotoqueiro == NULL){
    	gotoxy(43, 6);
    	printf("Erro de abertura!");
    }
	
    else{
		
		gotoxy(43, 6);
        printf("----> DIGITE AS DATAS <----");
		
		gotoxy(43, 7);
        printf("Digite a data inicial (dd mm aaaa): ");
        scanf("%d %d %d", &dia1, &mes1, &ano1);
        
        int busca1 = ValidaData(dia1, mes1, ano1);
        
        if(busca1 != 0){
        	
        	gotoxy(43, 8);
        	printf("Digite a data final (dd mm aaaa): ");
	        scanf("%d %d %d", &dia2, &mes2, &ano2);
	        
	        int busca2 = ValidaData(dia2, mes2, ano2);
	        
	        if(busca2 != 0){
	        	
	        	int busca3 = ValidaIntervaloData(dia1, mes1, ano1, dia2, mes2, ano2);
	        	
	        	if(busca3 != 0){
	        		
	    			
	    			gotoxy(43, ++i);
			        printf("----> MOTOQUEIROS E SUAS ENTREGAS <----");
			        gotoxy(43, ++i);
			        printf("%d/%d/%d --------------------- %d/%d/%d\n", dia1, mes1, ano1, dia2, mes2, ano2);
			    
			        while(fread(&M, sizeof(TpMotoqueiro), 1, ptrmotoqueiro) != 0){
						
			            count = 0;
			            fseek(ptrpedido, 0, 0);
			            
			            while(fread(&P, sizeof(TpPedidos), 1, ptrpedido) != 0)
							if(P.situacao == 3)
								if(stricmp(M.cpf, P.cpf) == 0)
				                	if(P.data.d >= dia1 && P.data.d <= dia2)
				                		if(P.data.m >= mes1 && P.data.m <= mes2)
				                			if(P.data.a >= ano1 && P.data.a <= ano2)
					                    		count++;
			            
			    		gotoxy(43, ++i);
			            printf("Motoqueiro: %s", M.nome);
			            gotoxy(43, ++i);
			            printf("Pizzas Entregues: %d", count);
			            i++;
			        }
	        	}
	        	
	        	else{
	        		gotoxy(43,14);
	        		printf("Intervalo de data invalida!");
	        	}
	        }
	        
	        else{
	        	gotoxy(43,14);
	        	printf("Data Invalida!");
	        }
        }
        
        else{
        	gotoxy(43,14);
        	printf("Data Invalida!");
        }
    
        fclose(ptrpedido);
        fclose(ptrmotoqueiro);
    }
    
    getch();
}


void RelatorioClientes(){
	TpCliente cliente;
	
	
	int i=8;
	
	gotoxy(43,6); textcolor(6);
	printf("----> RELATORIO CLIENTES <----");
	FILE*ptr = fopen("Clientes.dat","rb+");
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro ao abrir arquivo!!");
	}
	else{
		fseek(ptr,0,0);
		
		
		while(!feof(ptr)){
			
			fread(&cliente,sizeof(TpCliente),1,ptr);
			if(cliente.status == 'A')
				gotoxy(43,++i); textcolor(6);
				printf("%s \t %s \t %s\n",cliente.telefone, cliente.nome, cliente.endereco);
				fread(&cliente,sizeof(TpCliente),1,ptr);
				
				
		}
		fclose(ptr);
	}
		
	getche();
	LimpaTela();
}


void RelatorioMoto(){
	TpMotoqueiro moto;
	
	
	int i =8;
	gotoxy(43,6); textcolor(6);
	printf("----> RELATORIO MOTOQUEIRO<----");
	
	FILE*ptr = fopen("Motoqueiros.dat","rb+");
	
	if(ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro ao abrir arquivo!!");
	}
	else{
		fread(&moto,sizeof(TpMotoqueiro),1,ptr);
		
		while(!feof(ptr) && moto.status == 'A'){
			gotoxy(43,++i);
			printf("CPF:%s \t Nome:%s",moto.cpf,moto.nome);
			gotoxy(43,++i);
			printf("%d/%d/%d \t Telefone:%s",moto.data.d,moto.data.m,moto.data.a,moto.telefone);
			gotoxy(43,++i);
			printf("-------------------------------");
			fread(&moto,sizeof(TpMotoqueiro),1,ptr);	
		}
		fclose(ptr);
	}
		
	getche();
	LimpaTela();
}


void RelatorioPizzas(){
	TpPizza p;
	
	int i=8;
	gotoxy(43,6); textcolor(6);
	printf("----> RELATORIO PIZZAS <----");
	
	FILE*ptrpizza = fopen("Pizzas.dat","rb+");
	
	if(ptrpizza == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro ao abrir arquivo!\n");
	}
	else{
		while(fread(&p, sizeof(TpPizza), 1, ptrpizza) == 1){
			if(p.status == 'A'){
				gotoxy(43, ++i); textcolor(6);
				printf("%d \t %s \t %.2f\n", p.codigo, p.desc, p.valor);
			}
		}
		fclose(ptrpizza);
	}
	
	getche();
	LimpaTela();
}


void RelatorioPedidos(){
	TpPedidos p;
	int i = 8;
	
	
	gotoxy(43,6); textcolor(6);
	printf("----> RELATORIO PEDIDOS <----");
	
	FILE*ptrpedidos = fopen("Pedidos.dat","rb+");
	
	if(ptrpedidos == NULL){
		gotoxy(43,8); textcolor(6);
		printf("Erro ao abrir arquivo!\n");
	}
	else{
		fread(&p,sizeof(TpPedidos),1,ptrpedidos);
		
		while(!feof(ptrpedidos)){
			gotoxy(43,++i); textcolor(6);
			printf("Nmr do pedido: %d \tTel Cliente: %s",p.numero,p.telefone);
			gotoxy(43,++i); textcolor(6);
			printf("CPF Motoqueiro: %s \tSituacao: %d\n",p.cpf,p.situacao);
			fread(&p,sizeof(TpPedidos),1,ptrpedidos);
		}
		fclose(ptrpedidos);
	}
		
	getche();
	LimpaTela();
}


//CADASTROS
void CadastroPizza(){
	TpPizza pizza;
	
	
	int pos,auxcodigo;
	char op;
	FILE *ptr = fopen("Pizzas.dat","ab+");
	gotoxy(43,6); textcolor(6);
	printf("----> CADASTRO PIZZAS <----");
	gotoxy(43,7); textcolor(6);
	printf("Digite [0] para sair!");
	gotoxy(43,8); textcolor(6);
	printf("Digite o codigo: ");
	scanf("%d",&pizza.codigo);
		
	if(pizza.codigo != 0){
		
		pos = BuscaPizza(ptr,pizza.codigo);
		
		if(pos == -1){
			gotoxy(43,9); textcolor(6);
			printf("Digite o nome da pizza: ");
			fflush(stdin);
			gets(pizza.desc);
			
			gotoxy(43,10); textcolor(6);
			printf("Digite o valor da pizza: ");
			scanf("%f",&pizza.valor);
			pizza.status = 'A';
			pizza.quant = 0;
			
			fwrite(&pizza,sizeof(TpPizza),1,ptr);
			gotoxy(43,12); textcolor(6);
			printf("Pizza cadastrada com sucesso!\n");
			
		
		}
		else{
			gotoxy(43,9); textcolor(6);
			printf("Pizza ja cadastrada!");
		}

	}
	fclose(ptr);
	getche();
	LimpaTela();
}


void CadastroCliente(){
	TpCliente cliente;
	
	
	int pos,tamanho = 0;
	char op,auxnumero[TF];
	FILE *ptr = fopen("Clientes.dat","ab+");
	gotoxy(43,6); textcolor(6);
	printf("----> CADASTRO CLIENTE <----\n");
	gotoxy(43,7); textcolor(6);
	printf("Digite [0] para sair!\n");
	gotoxy(43,8); textcolor(6);
	printf("Digite seu telefone: ");
	fflush(stdin);
	gets(auxnumero);
	
	
	if(strlen(auxnumero) == 9){
		
		pos = BuscaCliente(ptr,auxnumero);
		
		if(pos == -1){
			
			strcpy(cliente.telefone,auxnumero);
			
			gotoxy(43,9); textcolor(6);
			printf("Digite o nome do cliente:");
			fflush(stdin);
			gets(cliente.nome);
			gotoxy(43,10); textcolor(6);
			printf("Digite seu endereço(rua):");
			fflush(stdin);
			gets(cliente.endereco);
			gotoxy(43,11); textcolor(6);
			printf("Digite sua cidade:");
			fflush(stdin);
			gets(cliente.cidade);
			gotoxy(43,12); textcolor(6);
			printf("Digite seu CEP: ");
			scanf("%d",&cliente.cep);
			
			cliente.status = 'A';
			cliente.pedidos = 0;
			
			fwrite(&cliente,sizeof(TpCliente),1,ptr);
			
			gotoxy(43,14); textcolor(6);
			printf("Cliente Cadastrado com sucesso!");
		}
		else{
			gotoxy(43,15); textcolor(6);
			printf("Cliente ja cadastrado!");
			
		}
	}
	else{
		gotoxy(43,9); textcolor(6);
		printf("Telefone nao valido!\n");
	}
	fclose(ptr);
	
	getche();
	LimpaTela();
}



void CadastroMoto(){
	TpMotoqueiro moto;
	
	int pos;
	char op,cpf[TF];
	
	
	FILE *ptr = fopen("Motoqueiros.dat","ab+");
	gotoxy(43,6); textcolor(6);
	printf("----> CADASTRO MOTOQUEIRO <----");
	gotoxy(43,7); textcolor(6);
	printf("Digite o CPF");
	fflush(stdin);
	gets(cpf);
	
	int aux = VerificaCPF(cpf);
	if(ptr == NULL){
		gotoxy(43,9); textcolor(6);
		printf("Erro ao abrir arquivo!\n");
	}
	else{
		if(aux != 0 && stricmp(cpf,"/0") != 0){
		
			pos = BuscaMotoqueiro(ptr,cpf);
			
			if(pos == -1){
				strcpy(moto.cpf,cpf);
				gotoxy(43,10); textcolor(6);
				printf("Digite o nome do motoqueiro:");
				fflush(stdin);
				gets(moto.nome);
				gotoxy(43,11); textcolor(6);
				printf("Digite seu endereço:");
				fflush(stdin);
				gets(moto.endereco);
				gotoxy(43,12); textcolor(6);
				printf("Digite a data da admissao [xx xx xxxx]: ");
				scanf("%d %d %d",&moto.data.d,&moto.data.m,&moto.data.a);
				int a = VerificaData(moto.data.d,moto.data.m,moto.data.a);
					if(a == 1){
						gotoxy(43,13); textcolor(6);
						printf("Digite o telefone: ");
						fflush(stdin);
						gets(moto.telefone);
				
						moto.status = 'A';
					
						fwrite(&moto,sizeof(TpMotoqueiro),1,ptr);
						gotoxy(43,15); textcolor(6);
						printf("Motoqueiro Cadastrado com sucesso!");
						
					}
					else{
						gotoxy(43,14); textcolor(6);
						printf("Data invalida!");
					}
			}
			else{
				gotoxy(43,11); textcolor(6);
				printf("Motoqueiro ja cadastrado!");
			}
		}
		fclose(ptr);
		
	}

	getche();
	LimpaTela();
}

void CadastroPedido() {
    TpPizza pizza;
    TpPedidos pedidos;
    TpCliente c;

    char cpf[TF], auxfone[TF];

    FILE *ptrpedido = fopen("Pedidos.dat", "ab+");
    FILE *ptrcliente = fopen("Clientes.dat", "rb+");
    FILE *ptrmoto = fopen("Motoqueiros.dat", "rb+");
    FILE *ptrpizza = fopen("Pizzas.dat", "rb+");

    gotoxy(43, 6);
    textcolor(6);
    printf("----> CADASTRO PEDIDO <----");
    gotoxy(43, 7);
    textcolor(6);
    printf("Digite [0] para sair!");
    gotoxy(43, 9);
    textcolor(6);
    printf("Digite o telefone do cliente: ");
    fflush(stdin);
    gets(auxfone);

    if (ptrpedido == NULL || ptrpizza == NULL || ptrcliente == NULL || ptrmoto == NULL) {
        gotoxy(43, 10);
        textcolor(6);
        printf("Erro ao abrir arquivo!");
    } else {
        if (stricmp(auxfone, "0") != 0 && strlen(auxfone) == 9) {
            int pos = BuscaCliente(ptrcliente, auxfone);

            if (pos != -1) {
                fseek(ptrcliente, pos, SEEK_SET);
                fread(&c, sizeof(TpCliente), 1, ptrcliente);
                c.pedidos++;
                
                strcpy(pedidos.telefone, auxfone);
                gotoxy(43, 10);
                textcolor(6);
                printf("Digite o CPF do motoqueiro:");
                fflush(stdin);
                gets(cpf);

                int pos1 = VerificaCPF(cpf);
                int aux = BuscaMotoqueiro(ptrmoto, cpf);

                if (pos1 == 1) {
                    if (aux != -1) {
                        strcpy(pedidos.cpf, cpf);
                        int auxcod;
                        gotoxy(43, 11);
                        textcolor(6);
                        printf("Digite o codigo da pizza desejada:");
                        scanf("%d", &auxcod);

                        int aux1 = BuscaPizza(ptrpizza, auxcod);

                        if (aux1 != -1) {
                            fseek(ptrpizza, aux1, 0);
                            fread(&pizza, sizeof(TpPizza), 1, ptrpizza);
                            pizza.quant++;
                            fseek(ptrcliente, pos, 0);
                            c.totalgasto += pizza.valor;

                            gotoxy(43, 12);
                            textcolor(6);
                            printf("Pizza: %s \tBoa escolha!", pizza.desc);
                            
                            gotoxy(43, 13);
                            textcolor(6);
                            printf("Digite o numero do pedido:");
                            scanf("%d", &pedidos.numero);

                            gotoxy(43, 14);
                            textcolor(6);
                            printf("Digite a data do pedido: [dd mm aaaa]:");
                            scanf("%d %d %d", &pedidos.data.d, &pedidos.data.m, &pedidos.data.a);
                            int a = VerificaData(pedidos.data.d, pedidos.data.m, pedidos.data.a);
                            if (a == 1) {
                                pedidos.situacao = 1;
                                pedidos.status = 'A';
                            
                                fseek(ptrcliente, pos, 0);
                                fwrite(&c, sizeof(TpCliente), 1, ptrcliente);
                            
                                fseek(ptrpizza, aux1, 0);
                                fwrite(&pizza, sizeof(TpPizza), 1, ptrpizza);

                                fseek(ptrpedido, 0, 2);
                                fwrite(&pedidos, sizeof(TpPedidos), 1, ptrpedido);
			
                                gotoxy(43, 16);
                                textcolor(6);
                                printf("Pedido cadastrado com sucesso!");
                            } else {
                                gotoxy(43, 15);
                                textcolor(6);
                                printf("Data invalida!");
                            }
                        } else {
                            gotoxy(43, 12);
                            textcolor(6);
                            printf("Pizza nao encontrada!\n");
                        }
                    } else {
                        gotoxy(43, 11);
                        textcolor(6);
                        printf("CPF nao encontrado!\n");
                    }
                } else {
                    gotoxy(43, 11);
                    textcolor(6);
                    printf("CPF nao valido!\n");
                }
            } else {
                gotoxy(43, 10);
                textcolor(6);
                printf("Cliente nao encontrado!\n");
            }
        } else {
            gotoxy(43, 10);
            textcolor(6);
            printf("Telefone invalido!\n");
        }
    }

    fclose(ptrpedido);
    fclose(ptrcliente);
    fclose(ptrmoto);
    fclose(ptrpizza);
    
    LimpaTela();
}
//Alteracao

void AlteracaoPedidos(){
	
	
	TpPedidos p;
	TpCliente c;
	TpMotoqueiro m;
	TpPizza pizza;
	
	int auxnum;
	
	FILE *ptrpedido = fopen("Pedidos.dat","rb+");
	FILE *ptrcliente = fopen("Clientes.dat","rb+");
	FILE *ptrmoto = fopen("Motoqueiros.dat","rb+");
	FILE *ptrpizza = fopen("Pizzas.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("---->ALTERACAO PEDIDOS<----\n");
	gotoxy(43,7); textcolor(6);
	printf("Digite o nmr do pedido a ser alterado:");
	scanf("%d",&auxnum);
	
	int pos = BuscaPedido(ptrpedido,auxnum);
	
	if(pos != -1){
		fseek(ptrpedido,pos,0);
		fread(&p,sizeof(TpPedidos),1,ptrpedido);
		gotoxy(43,8); textcolor(6);
		printf("Nmr do pedido: %d CPF do Motoqueiro: %s Tel do Cliente: %s",p.numero,p.cpf,p.telefone);
		gotoxy(43,9); textcolor(6);
		printf("Cod da pizza:%d",p.codigo);
		gotoxy(43,10); textcolor(6);
		printf("Deseja alterar dados? [S/N]");
		if(toupper(getch()) == 'S'){
			gotoxy(43,11); textcolor(6);
			printf("Deseja alterar apenas a situacao? [S/N]");
			if(toupper(getche()) == 'N'){
			
				gotoxy(43,12);
				printf("Digite novo numero:");
				fflush(stdin);
				gets(p.telefone);
				
				int aux1 = BuscaCliente(ptrcliente,p.telefone);
				
				if(strlen(p.telefone) == 9){
					if(aux1 == -1){
						gotoxy(43,13); textcolor(6);
						printf("Digite novo CPF do motoqueiro: ");
						fflush(stdin);
						gets(p.cpf);
						
						int aux2= VerificaCPF(p.cpf);
						int aux3= BuscaMotoqueiro(ptrmoto,p.cpf);
						if(aux2 == 1){
							if(aux3 == -1){
								fseek(ptrpedido,0,0);
								fread(&p,sizeof(TpPedidos),1,ptrpedido);
								gotoxy(43,14); textcolor(6);
								printf("Digite novo codigo da pizza: ");
								scanf("%d",&p.codigo);
								
								int aux4 = BuscaPizza(ptrpizza,p.codigo);
								if(aux4 != -1){
									fseek(ptrpizza,0,0);
									fread(&pizza,sizeof(TpPizza),1,ptrpizza);
									gotoxy(43,15); textcolor(6);
									printf("Pizza: %s\nBoa escolha! :D\n",pizza.desc);
									gotoxy(43,16); textcolor(6);
									printf("Digite novo numero do pedido:\n");
									scanf("%d",&p.numero);
									gotoxy(43,17); textcolor(6);
									printf("Digite nova data: ");
									scanf("%d %d %d",&p.data.d,&p.data.m,&p.data.a);
									int a = VerificaData(p.data.d,p.data.m,p.data.a);
										if(a == 1){
											gotoxy(43,18); textcolor(6);
											printf("Deseja alterar a situacao do pedido? [S/N]");
												if(toupper(getch()) == 'S'){
													gotoxy(43,19); textcolor(6);
													printf("Digite a situacao do pedido: 1- preparo 2- caminho 3- entregue: ");
													scanf("%d",&p.situacao);
													if(p.situacao >= 1 && p.situacao <= 3){
															gotoxy(43,20); textcolor(6);
															printf("Pedido alterado com sucesso!");
															fwrite(&p,sizeof(TpPedidos),1,ptrpedido);
													}
												}
												else{
													gotoxy(43,19); textcolor(6);
													printf("Situacao do pedido invalida!");
												
												}
										}
										else{
											gotoxy(43,18); textcolor(6);
											printf("Data invalida!");
										}
								
								}
								else{
									gotoxy(43,15); textcolor(6);
									printf("Pizza nao cadastrada!\n");
									
								}
								
							}
							else{
								gotoxy(43,14); textcolor(6);
								printf("Motoqueiro ja cadastrado!\n");
								
							}
							
						}
						else{
							gotoxy(43,14); textcolor(6);
							printf("CPF nao valido!\n");
							
						}
						
						
					}
					else{
						gotoxy(43,13); textcolor(6);
						printf("Cliente ja cadastrado!\n");
						
					}
					
				}
				else{
					gotoxy(43,13); textcolor(6);
					printf("Telefone nao valido\n");
					
				}
			
			}else{
				gotoxy(43,12);textcolor(6);
				gotoxy(43,19); textcolor(6);
				printf("Digite a situacao do pedido: 1- preparo 2- caminho 3- entregue: ");
				scanf("%d",&p.situacao);
				if(p.situacao >= 1 && p.situacao <= 3){
					gotoxy(43,20); textcolor(6);
					printf("Pedido alterado com sucesso!");
					fwrite(&p,sizeof(TpPedidos),1,ptrpedido);
				}
				LimpaTela();
				
			}
			
		}	
		
	}
	else{
		gotoxy(43,10); textcolor(6);
		printf("Pedido nao encontrado!\n");
		
	}
	
	fclose(ptrpedido);
	fclose(ptrpizza);
	fclose(ptrmoto);
	fclose(ptrcliente);
	getche();
	
	LimpaTela();
}


void AlteracaoCliente(){
	TpCliente c;
	
	
	FILE *ptr = fopen("Clientes.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("---->ALTERACAO CLIENTE<----\n");
	gotoxy(43,8); textcolor(6);
	printf("Digite o telefone para alteracao:");
	fflush(stdin);
	gets(c.telefone);
	char auxtel[30];
	int aux = BuscaCliente(ptr,c.telefone);
	
	if(aux != -1){
		fseek(ptr,0,0);
		fread(&c,sizeof(TpCliente),1,ptr);
		gotoxy(43,9); textcolor(6);
		printf("Numero:%s \t Cliente:%s\n",c.telefone,c.nome);
		gotoxy(43,10); textcolor(6);
		printf("Deseja alterar dados? [S/N]");
		if(toupper(getche()) == 'S'){
			gotoxy(43,11); textcolor(6);
			printf("Digite o novo nome: ");
			fflush(stdin);
			gets(c.nome);
			gotoxy(43,12); textcolor(6);
			printf("Digite novo cep: ");
			scanf("%d",&c.cep);
			
			gotoxy(43,13); textcolor(6);
			printf("Digite nova cidade: ");
			fflush(stdin);
			gets(c.cidade);
			gotoxy(43,14); textcolor(6);
			printf("Digite novo endereco: ");
			fflush(stdin);
			gets(c.endereco);
			gotoxy(43,15); textcolor(6);
			printf("Digite novo telefone: ");
			fflush(stdin);
			gets(auxtel);
			
			c.status = 'A';
			
			
			if (strlen(auxtel) == 9 ){
				strcpy(c.telefone,auxtel);
				fseek(ptr,0,0);
				fwrite(&c,sizeof(TpCliente),1,ptr);
				gotoxy(43,16); textcolor(6);
				printf("Dados alterados com sucesso!");
			}
			else{
				gotoxy(43,18); textcolor(6);
				printf("Telefone nao é valido!");
			}	
				
		}
		
	}
	else{
		gotoxy(43,9); textcolor(6);
		printf("Cliente nao cadastrado!");
	}
	
	fclose(ptr);
	getche();
	
	LimpaTela();
}

void AlteracaoMoto(){
	TpMotoqueiro moto;
	
	
	char auxcpf[30];
	
	FILE *ptr = fopen("Motoqueiros.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("---->ALTERACAO MOTOQUEIRO<----");
	
	gotoxy(43,7); textcolor(6);
	printf("Digite o CPF para alteracao:");
	fflush(stdin);
	gets(auxcpf);
	
	int a = VerificaCPF(auxcpf);
	int pos = BuscaMotoqueiro(ptr,auxcpf);
	
	if(a != 0){
		if(pos != -1){
			fseek(ptr,0,0);
			fread(&moto,sizeof(TpMotoqueiro),1,ptr);
			gotoxy(43,9); textcolor(6);
			printf("CPF: %s\tNome: %s",moto.cpf,moto.nome);
			gotoxy(43,10); textcolor(6);
			printf("Deseja alterar dados? [S/N]");
			if(toupper(getche()) == 'S'){
				gotoxy(43,11); textcolor(6);
				printf("Digite novo nome: ");
				fflush(stdin);
				gets(moto.nome);
				
				gotoxy(43,12); textcolor(6);
				printf("Digite nova data: ");
				scanf("%d %d %d",&moto.data.d,&moto.data.m,&moto.data.a);
					int a = VerificaData(moto.data.d,moto.data.m,moto.data.a);
					if(a == 1) {
						gotoxy(43,13); textcolor(6);
						printf("Digite novo endereco: ");
						fflush(stdin);
						gets(moto.endereco);
				
						gotoxy(43,14); textcolor(6);
						printf("Digite novo telefone: ");
						fflush(stdin);
						gets(moto.telefone);
						gotoxy(43,15); textcolor(6);
						printf("Digite novo CPF: ");
						fflush(stdin);
						gets(auxcpf);
				
						moto.status = 'A';
				
						a = VerificaCPF(auxcpf);
							if(a == 1 ){
								strcpy(moto.cpf,auxcpf);
								fseek(ptr,0,0);
								fwrite(&moto,sizeof(TpMotoqueiro),1,ptr);
								gotoxy(43,17); textcolor(6);
								printf("Motoqueiro alterado com sucesso!");
								
							}
							else{
								gotoxy(43,17); textcolor(6);
								printf("\nCPF nao valido");
							}
					}
					else{
						gotoxy(43,14); textcolor(6);
						printf("Data nao valida!");
					}

				
			}
			
			
		}
		else{
			gotoxy(43,10); textcolor(6);
			printf("CPF nao encontrado!\n");
		}
		
	}
	else{
		gotoxy(43,10); textcolor(6);
		printf("CPF nao valido!\n");
	}
	fclose(ptr);
	getche();
	
	LimpaTela();
}

void AlteracaoPizza(){
	
	
	TpPizza p;
	int codaux;
	
	FILE *ptr = fopen("Pizzas.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("---->ALTERACAO PIZZAS<----");
	gotoxy(43,7); textcolor(6);
	printf("Digite o codigo da pizza para alteracao:");
	scanf("%d",&codaux);
	
	int aux = BuscaPizza(ptr,codaux);
	
	if(aux != -1){
		fseek(ptr,0,0);
		fread(&p,sizeof(TpPizza),1,ptr);
		gotoxy(43,8); textcolor(6);
		printf("Codigo: %d Desc: %s  Valor: %.2f\n",p.codigo,p.desc,p.valor);
		gotoxy(43,9); textcolor(6);
		printf("Deseja alterar dados? [S/N]: ");
		if(toupper(getche()) == 'S'){
			gotoxy(43,10); textcolor(6);
			printf("Novo codigo: ");
			scanf("%d",&p.codigo);
			
			gotoxy(43,11); textcolor(6);
			printf("Nova descricao: ");
			fflush(stdin);
			gets(p.desc);
			
			gotoxy(43,12); textcolor(6);
			printf("Novo valor: ");
			scanf("%.2f",&p.valor);
			
			p.status = 'A';
			
			fseek(ptr,0,0);
			fwrite(&p,sizeof(TpPizza),1,ptr);
			gotoxy(43,14); textcolor(6);
			printf("Dados da pizza alterado com sucesso!\n");
			
		}
	}
	else{
		gotoxy(43,9); textcolor(6);
		printf("Pizza nao encontrada!\n");
	}
	
	
	fclose(ptr);
	getch();
	
	LimpaTela();
}

//consultas

void ConsultaPedidos(){
	TpPedidos p;
	
	
	
	int i = 8;
	gotoxy(43,6); textcolor(6);
	printf("---->CONSULTA PEDIDOS<----\n");
	
	FILE *ptr = fopen("Pedidos.dat","rb");
	int auxcod;
	
	if (ptr == NULL){
		gotoxy(43,8); textcolor(6);
		printf("erro ao abrir arquivo!\n");
	}
	else{
		gotoxy(43,i); textcolor(6);
		printf("Digite o pedido que deseja consultar: ");
		scanf("%d",&auxcod);
		
		int aux = BuscaPedido(ptr,auxcod);
		if (aux != -1){
			p.codigo = auxcod;
			fseek(ptr,0,0);
			fread(&p,sizeof(TpPedidos),1,ptr);
			gotoxy(43,++i); textcolor(6);
			printf("Nmr do pedido: %d \tTel Cliente: %s",p.numero,p.telefone);
			gotoxy(43,++i); textcolor(6);
			printf("CPF Motoqueiro: %s \tSituacao: %d\n",p.cpf,p.situacao);
		}
		else{
			gotoxy(43,9); textcolor(6);
			printf("Pedido nao encontrado!\n");
	
		}
		
		fclose(ptr);
		
	}
	
	getch();
	LimpaTela();
}

void ConsultaCliente(){
	TpCliente c;
	
	
	int i =10;
	gotoxy(43,6); textcolor(6);
	printf("---->CONSULTA CLIENTE<----\n");
	
	FILE *ptr = fopen("Clientes.dat","rb");
	gotoxy(43,8); textcolor(6);
	printf("Digite o telefone que deseja consultar: ");
	fflush(stdin);
	gets(c.telefone);
	
	if (BuscaCliente(ptr,c.telefone) != -1){
		fseek(ptr,0,0);
		fread(&c,sizeof(TpCliente),1,ptr);
		gotoxy(43,++i); textcolor(6);
		printf("Telefone: %s Nome: %s Endereco: %s,%s",c.telefone,c.nome,c.endereco,c.cidade);
	}
	else{
		gotoxy(43,9); textcolor(6);
		printf("Cliente nao encontrado!\n");
	}
	
	fclose(ptr);
	getche();
	
	LimpaTela();
}

void ConsultaMoto(){
	TpMotoqueiro moto;
	
	
	
	gotoxy(43,6); textcolor(6);
	printf("---->CONSULTA MOTOQUEIRO<----");
	
	FILE *ptr = fopen("Motoqueiros.dat","rb");
	
	gotoxy(43,8); textcolor(6);
	printf("Digite o CPF que deseja consultar: ");
	fflush(stdin);
	gets(moto.cpf);
	
	int aux = VerificaCPF(moto.cpf);
	int aux2 = BuscaMotoqueiro(ptr,moto.cpf);
	
	if(aux == 1){
		if(aux2 != -1){
			fseek(ptr,0,0);
			fread(&moto,sizeof(TpMotoqueiro),1,ptr);
			gotoxy(43,9); textcolor(6);
			printf("CPF: %s\t Nome: %s",moto.cpf,moto.nome);
			gotoxy(43,10); textcolor(6);
			printf("Data: %d/%d/%d \t End: %s",moto.data.d,moto.data.m,moto.data.a,moto.endereco);
		}
		else{
			gotoxy(43,9); textcolor(6);
			printf("CPF nao cadastrado!");
		}
	}
	else{
		gotoxy(43,9); textcolor(6);
		printf("CPF nao e valido!");
	}
	
	fclose(ptr);
	getche();
	
	LimpaTela();
}


void ConsultaPizza(){
	TpPizza p;
	int auxcod;
	
	
	int i = 8;
	gotoxy(43,6); textcolor(6);
	printf("---->CONSULTA PIZZA<----\n");
	
	FILE *ptr = fopen("Pizzas.dat","rb");
	gotoxy(43,7); textcolor(6);
	printf("Digite o codigo da pizza que deseja consultar: ");
	scanf("%d",&auxcod);
	
	int aux = BuscaPizza(ptr,auxcod);
	
	if (aux != -1){
		fseek(ptr,aux,0);
		fread(&p,sizeof(TpPizza),1,ptr);
		gotoxy(43,++i); textcolor(6);
		printf("Codigo: %d\t Desc: %s\tValor:%.2f\n",p.codigo,p.desc,p.valor);
	}
	else{
		gotoxy(43,8); textcolor(6);
		printf("Pizza nao encontrada!\n");
	}
	
	fclose(ptr);
	getche();
	
	LimpaTela();
}
//Estatitiscas
void MotoqueirosDia(){
	TpMotoqueiro motoqueiros;
	TpPedidos pedidos;
	int i=8;
	int resultado, x,pizza, ptr =0,ptrreal,valor,valorreal = 0;
	int d, m, a;
	FILE *ptrpedidos = fopen("Pedidos.dat","rb+");
	FILE *ptrmotoqueiros = fopen("Motoqueiros.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("-->MOTO POR DATA<--");
	if(ptrpedidos == NULL || ptrmotoqueiros == NULL){
		gotoxy(43,i); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    }
	else{
		gotoxy(43,++i); textcolor(6);
		printf("Dia:");
		scanf("%d %d %d", &d,&m,&a);
		
			fseek(ptrmotoqueiros,0,0);
			fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
			while(!feof(ptrmotoqueiros)){
				valor = 0;
				fseek(ptrpedidos,0,0);
				fread(&pedidos,sizeof(TpPedidos),1,ptrpedidos);
				while(!feof(ptrpedidos)){
					
					if(d == pedidos.data.d && stricmp(motoqueiros.cpf,pedidos.cpf) == 0)
						if(m == pedidos.data.m && a == pedidos.data.a){
							valor ++;
						}
					
					fread(&pedidos,sizeof(TpPedidos),1,ptrpedidos);
				}
				if(valorreal < valor && motoqueiros.status == 'A'){
					valorreal = valor;
					ptrreal = ptr;
				}
				ptr++;
	
				fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
				
			}
			
				
			fseek(ptrmotoqueiros,ptrreal * sizeof(TpMotoqueiro),0);
			fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
			gotoxy(43,++i); textcolor(6);
			printf("CPF: %s", motoqueiros.cpf);
			gotoxy(43,++i); textcolor(6);
			printf("Nome: %s", motoqueiros.nome);
			gotoxy(43,++i); textcolor(6);
			printf("Telefone: %s", motoqueiros.telefone);
			gotoxy(43,++i); textcolor(6);
			printf("Endereco: %s", motoqueiros.endereco);
			gotoxy(43,++i); textcolor(6);
			printf("Data de admissao: %d %d %d", motoqueiros.data.d,motoqueiros.data.m,motoqueiros.data.a);
			gotoxy(43,++i); textcolor(6);
			printf("Quantidade entregue nesse dia: %d", valorreal);
		}
		
	
	fclose(ptrpedidos);
	fclose(ptrmotoqueiros);

	getch();
	LimpaTela();
}

void MotoMenos(){

    TpMotoqueiro motoqueiros;
    int d,m,a,certo=0,i=0;
    int j=8;
    FILE *ptrmotoqueiros = fopen("Motoqueiros.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("--->MENOS EXPERIENTE<---");
    if(ptrmotoqueiros == NULL){
    	gotoxy(43,j); textcolor(6);
        printf("ERRO NA ABERTURA");
    }
    else{
        fseek(ptrmotoqueiros,0,0);
        fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
        d= motoqueiros.data.d;
        m= motoqueiros.data.m;
        a= motoqueiros.data.a;
        fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
        while(!feof(ptrmotoqueiros)){
            i++;
            if(a <= motoqueiros.data.a)
                if(m <= motoqueiros.data.m)
                    if(d <= motoqueiros.data.d){
                        d= motoqueiros.data.d;
                        m= motoqueiros.data.m;
                        a= motoqueiros.data.a;
                        certo = i;
                    }
            fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
        }

        fseek(ptrmotoqueiros,certo*sizeof(TpMotoqueiro),0);
        fread(&motoqueiros,sizeof(TpMotoqueiro),1,ptrmotoqueiros);
        gotoxy(43,++j); textcolor(6);
        printf("CPF: %s", motoqueiros.cpf);
        gotoxy(43,++j); textcolor(6);
        printf("Nome: %s", motoqueiros.nome);
        gotoxy(43,++j); textcolor(6);
        printf("Telefone: %s", motoqueiros.telefone);
        gotoxy(43,++j); textcolor(6);
        printf("Endereco: %s", motoqueiros.endereco);
        gotoxy(43,++j); textcolor(6);
        printf("Data de admissao: %d %d %d\n", motoqueiros.data.d,motoqueiros.data.m,motoqueiros.data.a);
        gotoxy(43,++j); textcolor(6);
        printf("Status: %c", motoqueiros.status);
    }
    fclose(ptrmotoqueiros);


	LimpaTela();
    getch();
}

void ClientePorPizza(){
	TpPedidos pedidos;
	TpCliente clientes;
	TpPizza pizzas;
	int y=8;
	int resultado, x,pizza,valor = 0,valorreal = 0, ptr =0,ptrreal, i=0;
	
	FILE *ptrpedidos = fopen("Pedidos.dat","rb+");
	FILE *ptrclientes = fopen("Clientes.dat","rb+");
	FILE *ptrpizzas = fopen("Pizzas.dat","rb+");
	gotoxy(43,6); textcolor(6);
	printf("-->CLIENTE Q MAIS PEDE POR PIZZA<--");
	
	if(ptrpedidos == NULL || ptrclientes == NULL || ptrpizzas == NULL){
		gotoxy(43,y); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    }
	else{
		gotoxy(43,y); textcolor(6);
		printf("Qual o numero do pizza:");
		scanf("%d", &pizza);
		
		x = BuscaPizza(ptrpizzas, pizza);
		if(x == -1){
			gotoxy(43,++y); textcolor(6);
			printf("Pizza n existe");
		}
		else{
			fseek(ptrclientes,0,0);
			fread(&clientes,sizeof(TpCliente),1,ptrclientes);
			while(!feof(ptrclientes)){
				valor = 0;
				fseek(ptrpedidos,0,0);
				fread(&pedidos,sizeof(TpPedidos),1,ptrpedidos);
				while(!feof(ptrpedidos)){
					
					if(pizza == pedidos.codigo && stricmp(clientes.telefone,pedidos.telefone) == 0){
						valor++;
					}
				
					fread(&pedidos,sizeof(TpPedidos),1,ptrpedidos);
				}
				if(valorreal < valor && clientes.status == 'A'){
					valorreal = valor;
					ptrreal = ptr;
				}
				ptr++;
	
				fread(&clientes,sizeof(TpCliente),1,ptrclientes);
				
			}
				
			fseek(ptrclientes,ptrreal * sizeof(TpCliente),0);
			fread(&clientes,sizeof(TpCliente),1,ptrclientes);
			
			gotoxy(43,++y); textcolor(6);
			printf("Telefone: %s", clientes.telefone);
			gotoxy(43,++y); textcolor(6);
			printf("Nome: %s", clientes.nome);
			gotoxy(43,++y); textcolor(6);
			printf("CEP: %d", clientes.cep);
			gotoxy(43,++y); textcolor(6);
			printf("Endereco: %s", clientes.endereco);
			gotoxy(43,++y); textcolor(6);
			printf("Cidade: %s", clientes.cidade);
			gotoxy(43,++y); textcolor(6);
			printf("Status: %c", clientes.status);
			gotoxy(43,++y); textcolor(6);
			printf("Quantidade pedidas dessa pizza: %d", clientes.pedidos);
			}
		}
	
	fclose(ptrpedidos);
	fclose(ptrpizzas);
	fclose(ptrclientes);
	getch();
	LimpaTela();
}

void ClienteMaisPede(){
	TpCliente c;
	int i=8;
	FILE *ptr = fopen("Clientes.dat","ab+");
	OrdenaCliente();
	gotoxy(43,6); textcolor(6);
	printf("---->CLIENTE MAIS PEDE<----");
    int resultado,x;

    if(ptr==NULL){
    	gotoxy(43,++i); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    
    }
        else{
        	fseek(ptr,0,0);
			fread(&c,sizeof(TpCliente),1,ptr);
			x = c.pedidos;
        		while(!feof(ptr) && x == c.pedidos){
					if(c.status == 'A'){
						gotoxy(43,++i); textcolor(6);
						printf("Telefone: %s", c.telefone);
						gotoxy(43,++i); textcolor(6);
						printf("Nome: %s", c.nome);
						gotoxy(43,++i); textcolor(6);
						printf("CEP: %d", c.cep);
						gotoxy(43,++i); textcolor(6);
						printf("Endereco: %s", c.endereco);
						gotoxy(43,++i); textcolor(6);
						printf("Cidade: %s", c.cidade);
						gotoxy(43,++i); textcolor(6);
						printf("Pedido: %d", c.pedidos);
						fread(&c,sizeof(TpCliente),1,ptr);
					}
        		}			
		}
		fclose(ptr);
		getch();
		LimpaTela();
}

void PizzaMaisPedida(){
	TpPizza pizza;
	int i=8;
	FILE *ptr = fopen("Pizzas.dat","ab+");
	OrdenaRanking();
	gotoxy(43,6); textcolor(6);
	printf("---->MAIS PEDIDA<----");
    int resultado,x;

    if(ptr==NULL){
    	gotoxy(43,i); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    }
    else{
        	fseek(ptr,0,0);
			fread(&pizza,sizeof(TpPizza),1,ptr);
			x = pizza.quant;
        		while(!feof(ptr) && x== pizza.quant){
					if(pizza.status == 'A' ){
						gotoxy(43,++i); textcolor(6);
						printf("Codigo: %d", pizza.codigo);
						gotoxy(43,++i); textcolor(6);
						printf("Desc: %s", pizza.desc);
						gotoxy(43,++i); textcolor(6);
						printf("valor: %.2f", pizza.valor);
						gotoxy(43,++i); textcolor(6);
						printf("Quant: %d",pizza.quant);
						
						fread(&pizza,sizeof(TpPizza),1,ptr);
					}
				
        		}			
	}
		fclose(ptr);
		getch();
		LimpaTela();
}

void PizzaMenosPedida(){
	TpPizza pizza;
	
	FILE *ptr = fopen("Pizzas.dat","ab+");
	OrdenaRankingContra();
	int i = 8;
    int resultado,x;
    gotoxy(43,6); textcolor(6);
	printf("---->MENOS PEDIDA<----");
    if(ptr==NULL){
    	gotoxy(43,i); textcolor(6);
    	printf("Erro de Abertura de Arquivo");
    }
        else{
        	fseek(ptr,0,0);
			fread(&pizza,sizeof(TpPizza),1,ptr);
			x = pizza.quant;
        		while(!feof(ptr) && x == pizza.quant){
					if(pizza.status == 'A'){
						gotoxy(43,++i); textcolor(6);
						printf("Codigo: %d", pizza.codigo);
						gotoxy(43,++i); textcolor(6);
						printf("Desc: %s", pizza.desc);
						gotoxy(43,++i); textcolor(6);
						printf("valor: %.2f", pizza.valor);
						gotoxy(43,++i); textcolor(6);
						printf("Quant: %d",pizza.quant);
						
						fread(&pizza,sizeof(TpPizza),1,ptr);	
					}
				
        		}			
		}
		fclose(ptr);
		getche();
		LimpaTela();
}





char Menu(void){
	
	LimpaTela2();
	gotoxy(3,6); textcolor(10);
	printf("SEJA BEM-VINDO A MALAGA PIZZARIA!\n");
	 
	gotoxy(3,7); textcolor(9);
	printf("[A] - Sou Cliente\n");
	gotoxy(3,8); textcolor(9);
	printf("[B] - Sou Motoqueiro\n");
	gotoxy(3,9); textcolor(9);
	printf("[C] - Meu Pedido\n");
	gotoxy(3,10); textcolor(9);
	printf("[D] - Cardapio\n");
	gotoxy(3,11); textcolor(9);
	printf("[E] - Relatorios\n");
	gotoxy(3,12); textcolor(9);
	printf("[F] - Estatisticas\n");
	//textcolor(4);
	gotoxy(3,14); textcolor(4);
	printf("[ESC] - Sair");
	
	
	
	return toupper(getche());
}

char Menu2(void){
	
	LimpaTela2();
	gotoxy(3,6); textcolor(9);
	printf("[A] - Cadastro\n");
	gotoxy(3,7); textcolor(9);
	printf("[B] - Relatorio\n");
	gotoxy(3,8); textcolor(9);			
	printf("[C] - Alteracao\n");
	gotoxy(3,9); textcolor(9);
	printf("[D] - Consulta\n");
	gotoxy(3,10); textcolor(9);		
	printf("[E] - Exclusao Fisica\n");
	gotoxy(3,11); textcolor(9);			
	printf("[F] - Exclusao Logica\n");
	//textcolor(4);
	
	gotoxy(3,13); textcolor(4);
	printf("[ESC] - Sair");
	
	
	return toupper(getche());
}

char MenuRelatorio(void){
	
	LimpaTela2();
	gotoxy(3,6); textcolor(9);
	printf("[A] - Relatorio motoqueiros e pizzas\n");
	gotoxy(3,7); textcolor(9);
	printf("[B] - Relatorio de clientes por letra\n");
	gotoxy(3,8); textcolor(9);
	printf("[C] - Ranking pizzas\n");
	gotoxy(3,9); textcolor(9);
	printf("[D] - Relatorio todos clientes\n");
	gotoxy(3,10); textcolor(9);
	printf("[E] - Pizzas em andamento\n");
	gotoxy(3,11); textcolor(9);
	printf("[F] - Pizzas a caminho\n");
	
	gotoxy(3,13); textcolor(4);
	printf("[ESC] - Sair\n");
	
	return toupper(getche());
}


char MenuEstatistica(){
	
    LimpaTela2();
    gotoxy(3,6); textcolor(9);
    printf("[A]-Pizza mais pedida");
    gotoxy(3,7); textcolor(9);
    printf("[B]-Pizza menos pedida");
    gotoxy(3,8); textcolor(9);
    printf("[C]-Cliente que mais consome");
    gotoxy(3,9); textcolor(9);
    printf("[D]-Cliente q consome mais pizza");
    gotoxy(3,10); textcolor(9);
    printf("[E]-Qual motoqueiro menos experiente");
    gotoxy(3,11);
	textcolor(9);
    printf("[F]-Qual motoqueiro mais entrega");

    gotoxy(3,13); textcolor(4);
    printf("[ESC]-Sair");
    return toupper(getche());

}


int main(void){
	char op;
	FormPrincipal();
	op = Menu();
	do{
		switch(op){
			
			case 'A':{
				op = Menu2();
				do{
					
					switch (op){
						
						case 'A': CadastroCliente();
							break;
							
						case 'B':
								RelatorioClientes();
							break;
							
						case 'C': AlteracaoCliente();
							break;
							
						case 'D': ConsultaCliente();
							break;
							
						case 'E': ExcFisicaCliente();
							break;
						case 'F': ExcLogicaCliente();
							break;
					}
					op = Menu2();
					
				}while(op!=27);
			}
				break;
			case 'B':{
				op = Menu2();
				do{
					switch(op){
						case 'A': CadastroMoto();
							break;
						case 'B': 
								RelatorioMoto();
							break;
						case 'C': AlteracaoMoto();
							break;
						case 'D': ConsultaMoto();
							break;
						case 'E': ExcFisicaMoto();
							break;
						case 'F': ExcLogicaMoto();
							break;
					}
					op = Menu2();
					
				}while(op != 27);
			}
				break;
			case 'C':{
				op = Menu2();
				do{
					switch(op){
						case 'A': CadastroPedido();
							break;
						case 'B': OrdenaPedidoSelecao();
								  RelatorioPedidos();
							break;
						case 'C': AlteracaoPedidos();
							break;
						case 'D': ConsultaPedidos();
							break;
						case 'E': ExcFisicaPedido();
							break;
						case 'F': ExcLogicaPedido();
							break;
					}
					op = Menu2();
					
				}while(op != 27);
			}
				break;
			case 'D':{
				op = Menu2();
				do{
					switch(op){
						case 'A': CadastroPizza();
							break;
						case 'B':
								OrdenaPizza();
								RelatorioPizzas();
							break;
						case 'C': AlteracaoPizza();
							break;
						case 'D': ConsultaPizza();
							break;
						case 'E': ExcFisicaPizza();
							break;
						case 'F': ExcLogicaPizza();
							break;
					}
					op = Menu2();
					
				}while(op != 27);
				break;
			}
			case 'E':{
				op = MenuRelatorio();
				do{
					switch(op){
						case 'A':{
							RelatorioMotoPizza();
							break;
						}
						case 'B':{ 
							RelatorioLetra();	
							break;
						}
						case 'C':{
							OrdenaRanking();
							RankingPizza();
							break;
						}
						case 'D':{
							RelatorioTodosCliente();
							break;
						}
						case 'E':{
							PizzaAndamento();
							break;
						}
						case 'F':{
							PizzaCaminho();
							break;
						}
					}
					op = MenuRelatorio();	
					
				}while(op != 27);
				
				break;
			}
			case 'F':{
				op = MenuEstatistica();
				do{
					switch(op){
						case 'A':{
							PizzaMaisPedida();
							break;
						}
						case 'B':{
							PizzaMenosPedida();
							break;
						}
						case 'C':{
							ClienteMaisPede();
							break;
						}
						case 'D':{
							ClientePorPizza();
							break;
						}
						case 'E':{
							MotoMenos();
							break;
						}
						case 'F':{
							MotoqueirosDia();
							break;
						}
					}
					op = MenuEstatistica();
				}while(op != 27);
				
				break;
			}
		}
				
		op = Menu();
	}while(op != 27);
	
	return 0;
}
