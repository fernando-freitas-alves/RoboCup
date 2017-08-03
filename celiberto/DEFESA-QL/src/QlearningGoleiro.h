#include <sys/time.h>
#include "math.h"



//declarações
void apaga_tabela(void);
int v_randomico (void);
void calcula_Qlambda(int estado, int estadoNew, int acao, float recompensa);
int melhor_acao_a(int estado);
void SalvarArquivo();
void CarregarArquivo();
void salva_acao (int gol,int ciclo);
void Salvaperiodo (int periodo, int gol,int jogo);
void SalvaMAPA (float agenteX, float agenteY,bool gravar);



//Variaveis
int evolucao_gol[10000000]; int numero_gol[10000000]; 
int ciclo_antigo=0;
int gols=0; int gol=0; int golOld=0; bool  estado_valido;
float passoX[100];float passoY[100];int passos=0;
int evolucao[1000];
float ValorQnew[1000];
int gol_periodo=0;
float ValorQ=0;

//    Q[xr ][yr][tr][xb][yb][acao]
//*********** TABELA "Q" e "e" ************
float Q[50000][6];
float e[50000][6];
float TABG[50000][6];

void apaga_tabela(void)
{
int linha,coluna;
 cout<< "Carregando protocolos de Aprendizado Goleiro"<<endl;
 for (linha=0;linha<45000;linha++)   
     for (int coluna=0;coluna<6;coluna++)
   {     
     Q[linha][coluna]= 0;
     	   
   }
   for (linha=0;linha<45000;linha++)   
     for (int coluna=0;coluna<6;coluna++)
   {     
     TABG[linha][coluna]= 0;
     	   
   }
  
    cout<< "Pronto !"<<endl;
 
     
}


//**************************************
//* Calcula o Q-lambda                 *
//**************************************

void calcula_Qlambda(int estado, int estadoN, int acao, float reforcoAcao)
{
   // definindo valores
   static float gama=0.9;
   static float alfa=0.125;
   static float lambda=0.5;
   //definindo variaveis	
   float Ql=0;
   float Qatual=0;
   float Qa;
   float delta=0;
   float eNew=0;
   float Q_valor=0;
   int cont=0;

   
   
   // Encontra a*  e  Q(s', a');	 
   int estado_a = melhor_acao_a(estadoN);   
   Qa=Q[estadoN][estado_a];
   
   //Encontra o valor de Q anterior
   Ql=Q[estado][acao];
	
   
   //calcula delta
   delta= ((-1+reforcoAcao) + (gama*Qa) - Ql);
	
   //e(s,a)=e(s,a)+1
   e[estado][acao]++;	
	
	
   //Calcula o QL
   
   Q[estado][acao]=
      (
        Q[estado][acao]+(alfa*delta)
      );
	   
	   
	
    //atualizando valores em "e" 
    for(cont=0;cont<6;cont++)
	{
	  if(cont==acao)
	     e[estado][cont]=gama*lambda*e[estado][acao];
      else
		 e[estado][cont]=0;
    }
  
  //system("clear");
  cout<<" "<<endl;
  cout<<" Goleiro "<<endl;
  cout<<"Acao: "<<acao<<" R : "<<reforcoAcao<<" QL: "<<Q[estado][acao]<<" e: "<<e[estado][acao]<<" delta: "<<delta<<endl;	
  
   
	 
	
}

//************************************
//*  Acha o maior valor para o a*    *
//*   a*=argmaxb Q(s', b)            *
//************************************
int melhor_acao_a(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  maiorvalor=Q[estado][0];
  
  float tempvalor=0;  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=Q[estado][cont];
    
     if(tempvalor>maiorvalor)
      {
         maiorvalor=tempvalor;
	     acao=cont;      
      }         
   } 
  
 return acao;
}

//************************************
//*  Escolhe a acao a ser tomada     *
//*   a partir da observacao         *
//************************************

int escolher_acao(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  float tempvalor=0;
  
  maiorvalor=Q[estado][0];
  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=(Q[estado][cont]);
    
     if(tempvalor>maiorvalor)
      {
         maiorvalor=tempvalor;
	     acao=cont;      
      }         
   }
    
    //5% de exploracao
    if(v_randomico()==0)
    {     	  
      srand(time(NULL));
      acao=rand()%6;     
    }   
     
 return acao;
}


//*********************************************
//*          Calcula o Reforco                *
//*********************************************

int Reforco(int gol,int ciclo,int acao,bool isBallCatchable,bool isBallKickable,int periodo,int jogo,float dist,float tempo)
{
  int reforco=0;
  int bomReforco=0;
  int angulo, jogador,bola;
	
  //jogador=
	
  //cout<<"Ciclo: "<<ciclo<<endl;

  if(isBallCatchable && acao==4){bomReforco=1;}
  else if (isBallKickable && acao==2)  {bomReforco=1;}
  else if (isBallKickable && acao==3 ){bomReforco=2;}
  else if(dist>2 && acao!=1){bomReforco=-2;} 
  if(gol<golOld){bomReforco=-1;golOld=gol;}  
  
  //cout<<"Distancia bola: "<<dist <<endl;
  
  if (bomReforco==-2)
  {	 
    reforco=-10;	
    ciclo_antigo=ciclo;
  }   
	
   
  if (bomReforco==-1)
  {	 
    gols++;
    gol_periodo++;	  
	reforco=-50;
    //salva_acao (gols,ciclo-ciclo_antigo);
    Salvaperiodo (periodo,gol_periodo,jogo);	  
	ciclo_antigo=ciclo;
  }
  if (bomReforco==1 )
  {         
	reforco=10+((int)tempo); //20
    ciclo_antigo=ciclo;
  } 
  
  if (bomReforco==2 )
  {         
	reforco=10; //10
    ciclo_antigo=ciclo;
  } 
  
 
     
  return reforco;

}

//*********************************************
//*          Escolhe o estado pela observacao *
//*********************************************

//determinacao das zonas

//   12 13 14 15
//g  08 09 10 11 
//o  04 05 06 07
//l  00 01 02 03

//



int escolhe_estado(float agenteX,float agenteY,float angulo,float bolaX, float bolaY)
{
   
   int aX,aY,angle,bX,bY;
   int State;
   int zonaAgente=0;
   int zonaBola=0;
   int anguloAgente=0;
  
	
   
   aX=(int)((agenteX)+52.5);   
   aY=(int)((agenteY)+20.5);

   if(aX<0){aX=0;}
   if(aX>20){aX=20;}
   if(aY<0)  {aY=0;}
   if(aY>40) {aY=40;}
   
	
   if(aX>=0 && aX<=5){zonaAgente=0;}
   if(aX>5 && aX<=10){zonaAgente=1;}
   if(aX>10 && aX<=15){zonaAgente=2;}
   if(aX>15 && aX<=20){zonaAgente=3;}
   
   if(aY>=0 && aY<=10){zonaAgente=zonaAgente+0;}
   if(aY>10 && aY<=20){zonaAgente=zonaAgente+4;}
   if(aY>20 && aY<=30){zonaAgente=zonaAgente+8;}
   if(aY>30 && aY<=40){zonaAgente=zonaAgente+12;}
	
	
	
   angle=(int)(angulo+180);
   
   
   //cout<<"angulo "<< angle<<endl;
   if(angle>135 && angle<=225){anguloAgente=0;}
   if(angle>225 && angle<315){anguloAgente=1;}	
   if(angle<=45 || angle>=315){anguloAgente=2;}
   if(angle>45 && angle<=135){anguloAgente=3;}   
  
	   
	
   bX=(int)(((bolaX)+52.5));   
   bY=(int)(((bolaY)+20.5));

   if(bX<0){bX=0;}
   if(bX>20){bX=20;}
   if(bY<0)   {bY=0;}
   if(bY>40)  {bY=40;}
   
	
   if(bX>=0 && bX<=5){zonaBola=0;}
   if(bX>5 && bX<=10){zonaBola=1;}
   if(bX>10 && bX<=15){zonaBola=2;}
   if(bX>15 && bX<=20){zonaBola=3;}
   
   if(bY>=0 && bY<=10){zonaBola=zonaBola+0;}
   if(bY>10 && bY<=20){zonaBola=zonaBola+4;}
   if(bY>20 && bY<=30){zonaBola=zonaBola+8;}
   if(bY>30 && bY<=40){zonaBola=zonaBola+12;}   
	
   
   //cout<<"Agente: "<< zonaAgente<< " Angulo: "<<anguloAgente <<" Bola: "<<zonaBola<<endl;
   
   State=(int)(anguloAgente*10000 + zonaAgente*100 + zonaBola);
   
   //cout<<"chave: "<< State<<endl;
   
   return State;
}




// 5% de exploracao(escolhe um valor de 0-20)
int v_randomico (void)
{
  int valor_ramdomico;   
  srand((unsigned int)time(NULL));
  valor_ramdomico=rand()%19;	
  return valor_ramdomico;	
}


//*****  Verifica se vai bater ****** //sysop 
//*      DELIMITA GRANDE AREA       *
//* X= -51 A -35 E Y= -20 A +20  *
//*******************************************

int permitir_acao(int acao,float agenteX,float agenteY,float angulo)
{
	int retorno_acao;
	
	if(acao==1)
	{
		if((agenteX>=-31.5)&&(angulo>=-89 && angulo<=89))
		{
		  retorno_acao=6;	
		}
		else if((agenteX<=-52)&&(angulo<=-91 || angulo>=91 ))
		{
		  retorno_acao=6;	
		}
		else if((agenteY>20)&&(angulo>=0 && angulo<=180))
		{
		  retorno_acao=6;	
		}
		else if((agenteY<-20)&&(angulo<=0 && angulo>=-180))
		{
		  retorno_acao=6;	
		}
		else {retorno_acao=acao;}
        	
	}
	else{retorno_acao=acao;}
	
	
	return retorno_acao;	
	
} 


//****************  Arquivo ********************** //sysop
//                                                 //
//  TODAS AS FUNCOES DE SALVAMENTO E RECUPERACAO   //
//                DE DADOS                         //                       
//                                                 //
//*************************************************//

// Carrega uma tabela caso exista, ou cria uma zerada
// caso nao exista nenhuma tabela

void CarregarArquivo()
{
	char file_name[400];
	int a,b,c,d,e1;
	
	FILE * tab_Q;
	FILE * tab_e;
	
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/tabela_Q.txt");
    tab_Q=fopen(file_name,"r");
	
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/tabela_e.txt");
    tab_e=fopen(file_name,"r");
	
	if(!tab_Q)
	{
		cout<< "Gerando Tabelas Goleiro !"<<endl;
		apaga_tabela();
		
		
	}
	if(tab_Q)
	{
	   cout<< "Tabela anterior encontrada. Carregando Tabela Q"<<endl;
       cout<< "Por favor...Espere !!!"<<endl;
	   

     for (a=0;a<45000;a++)
      
			  {
				fscanf (tab_Q, "%f %f %f",&Q[a][0],&Q[a][1],&Q[a][2]);  
			    //fscanf (tab_e, "%f %f %f",&e[a][0],&e[a][1],&e[a][2]);  
              }
	  fflush(tab_Q);
	  fclose(tab_Q);
      fflush(tab_e);
	  fclose(tab_e);			   
	}
	  	  	
}






void Salvaperiodo (int periodo, int gol_p, int jogo)
{
	char file_name[500];
	
	FILE * arq;
	
		
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/Periodo/gol_periodo.txt");
    arq=fopen(file_name,"w");
	
    
	evolucao[periodo]=gol_p;	
		
	for(int cont=0;cont<=periodo;cont++)
    {
    fprintf(arq, "%d %d\n",cont,evolucao[cont]);
    } 
		
	fflush(arq);
    fclose(arq);
	
}



float ImprimeDiferencaQ(int periodo,float ValorQold)
{
	char file_name[500];
	float SaidaValorNew;
	float somaQ=0;
	int linha,coluna;
	float Valor1,Valor2;
	
	FILE * arq;		
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/Q/diferencaQ.txt");
    arq=fopen(file_name,"w");
	
	for (linha=0;linha<45000;linha++)
	{		
      for (coluna=0;coluna<6;coluna++)
       {     
         //somaQ=somaQ+Q[linha][coluna];
         Valor1=Q[linha][coluna];
         Valor2=TABG[linha][coluna];
         somaQ=somaQ+fabs(Valor1-Valor2);       
	   }
	 }
	 
	 for (linha=0;linha<45000;linha++)
		{   
         for (coluna=0;coluna<6;coluna++)
           {   
		   TABG[linha][coluna]=	Q[linha][coluna];
		   }
   		}
	
	ValorQnew[periodo]=somaQ;
	
		
    for(int cont=0;cont<=periodo;cont++)
    {
    fprintf(arq, "%d %f\n",cont,ValorQnew[cont]);
    } 
		
	fflush(arq);
    fclose(arq);
	
	
	
	return SaidaValorNew;
	
	
}


void ImprimeDiferencaAcoes(void)
{
	char file_name[500];
	
	FILE * arq;		
	sprintf (file_name,"/home/sysop/Futebol/hashGoleiro-QL/src/Tabela/Q/diferencaAcoes.txt");
    arq=fopen(file_name,"w");
	
	fprintf(arq, "00");
	
	
	
	fflush(arq);
    fclose(arq);
	
}




void SalvaMAPA (float agenteX, float agenteY,bool gravar)
{
	if(gravar)
	{
	  char file_name[400];
	  FILE * xy;
      
	
	  sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/Mapa/caminho.txt");
      xy=fopen(file_name,"w");

      	
	  passoX[passos]=agenteX;
	  passoY[passos]=agenteY;
	  passos++;	
	  for(int cont=0;cont<=passos;cont++)
       { 
        fprintf(xy, "%f %f\n",passoX[cont],passoY[cont]);
        
       }
  
	 
    fflush(xy);
    fclose(xy);
    
   }
   else
   {
	   passoX[passos]=agenteX;
	   passoY[passos]=agenteY;
	   passos++;  
	   
   }
}
