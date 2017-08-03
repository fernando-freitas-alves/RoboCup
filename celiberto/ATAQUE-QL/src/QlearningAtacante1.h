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
void ImprimeDiferencaQ(int periodo);
int Reforco(int gol,int ciclo,int acao,bool Mrapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo);
int escolhe_estado2v2(float agenteX,float agenteY,float angulo,float distanciaBola,float distancia);



//Variaveis
//int evolucao_gol[10]; int numero_gol[10]; 
int ciclo_antigo=0;
int gols=0; int gol=0; int golOld=0; bool  estado_valido;
float passoX[10];float passoY[10];int passos=0;
int evolucao[1000];
float ValorQnew[1000];
int gol_periodo=0;
float ValorQ=0;

//    Q[xr ][yr][tr][xb][yb][acao]
//*********** TABELA "Q" e "e" ************
float Q[50000][6];
float TABG[50000][6];

void apaga_tabela(void)
{
int linha,coluna;
 cout<< "Carregando protocolos de Aprendizado atacante 1"<<endl;
 for (linha=0;linha<50000;linha++)   
     for (int coluna=0;coluna<6;coluna++)
   {     
     Q[linha][coluna]= 0;
     	   
   }
   for (linha=0;linha<50000;linha++)   
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
   	
	
	
   //Calcula o QL
   
   Q[estado][acao]=
      (
        Q[estado][acao]+(alfa*delta)
      );
	   
	   
	
    
  
  //system("clear");
  //cout<<" "<<endl;
  cout<<" ATACANTE 1 "<<endl;
  cout<<"Acao: "<<acao<<" R : "<<reforcoAcao<<" QL: "<<Q[estado][acao]<<" delta: "<<delta<<endl;	
  
   
	 
	
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

int Reforco(int gol,int ciclo,int acao,bool Mrapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo,bool pegou)
{
  int reforco=0;
  int bomReforco=0;
  int angulo, jogador,bola;  

  //if(pegou && acao==2){bomReforco=-2;}
  if (isBallKickable && acao==2){bomReforco=2;} //chutar    
  else if (isBallKickable && acao==3)  {bomReforco=3;} //passe  
  else if(Mrapido && dist>=1 && acao!=1 ){bomReforco=-1;}
  //else if(!Mrapido && acao!=4 ){bomReforco=-2;} //marcar

  if(gol>golOld){bomReforco=4;golOld=gol;} 
     
  if (bomReforco==-2){reforco=-10;}
  if (bomReforco==-1){reforco=-4;}
  else if (bomReforco==1){ reforco=0;}  
  else if (bomReforco== 2 ){ reforco=3; }
  else if (bomReforco== 3 ){ reforco=3; }
  
  if (bomReforco==4 )
  {
	  gol_periodo++;
	  Salvaperiodo (periodo,gol_periodo,jogo);
	  
	  if(acao==2){reforco=100;}
      else{reforco=25;}  
		  
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

int escolhe_estado2v2(float agenteX,float agenteY,float angulo,float distanciaBola,float distancia)
{
   
   int aX,aY,angle,bX,bY;
   ;
   int State;
   int zonaAgente=0;
   int anguloAgente=0;
   int distanciaAgente=0;
   int distanciaB=0;
  
	//cout<<"Jogador1 "<<" X "<<agenteX<<" Y "<<agenteY<<endl;
   aX=(int)((agenteX)+52.5);   
   aY=(int)((agenteY)+34);

   if(aX<44){aX=44;}
   if(aX>105){aX=105;}
   if(aY<0)  {aY=0;}
   if(aY>68) {aY=68;}
   
   if(aX>44 && aX<=54)     {zonaAgente=0;}
   else if(aX>54 && aX<=64) {zonaAgente=1;}
   else if(aX>64 && aX<=74) {zonaAgente=2;}   
   else if(aX>74 && aX<=79) {zonaAgente=3;}
   else if(aX>79 && aX<=84) {zonaAgente=4;}
   else if(aX>84 && aX<=89) {zonaAgente=5;}
   else if(aX>89 && aX<=94) {zonaAgente=6;}
   else if(aX>94 && aX<=99) {zonaAgente=7;}
   else if(aX>99 && aX<=105){zonaAgente=8;}
   
   
   if(aY>=0 && aY<=10){zonaAgente=zonaAgente+0;}
   else if(aY>10 && aY<=20){zonaAgente=zonaAgente+9;}
   else if(aY>20 && aY<=30){zonaAgente=zonaAgente+18;}
   else if(aY>30 && aY<=40){zonaAgente=zonaAgente+27;}
   else if(aY>40 && aY<=50){zonaAgente=zonaAgente+36;}
   else if(aY>50 && aY<=60){zonaAgente=zonaAgente+45;}
   else if(aY>60 && aY<=70){zonaAgente=zonaAgente+54;}
	
   angle=(int)(angulo+180);  
   
   if(angle>135 && angle<=225){anguloAgente=0;}
   else if(angle>225 && angle<315){anguloAgente=1;}	
   else if(angle<=45 || angle>=315){anguloAgente=2;}
   else if(angle>45 && angle<=135){anguloAgente=3;}	   
	
   
   //distancia Bola   
   if (distanciaBola>=0 && distanciaBola<1) {distanciaB=0;}
   else if (distanciaBola>=1 && distanciaBola<2){distanciaB=1;}
   else if (distanciaBola>=2 && distanciaBola<3){distanciaB=2;}
   else if (distanciaBola>=3 && distanciaBola<4){distanciaB=3;}
   else if (distanciaBola>=4 && distanciaBola<5){distanciaB=4;}
   else if (distanciaBola>=5 && distanciaBola<15){distanciaB=5;}
   else if (distanciaBola>=15 && distanciaBola<25){distanciaB=6;}
   else if (distanciaBola>=25 && distanciaBola<35){distanciaB=7;}
   else if (distanciaBola>=35 && distanciaBola<45){distanciaB=8;}
   else if (distanciaBola>=45 ){distanciaB=9;}  
   
   //distanciaAgente   
   
   else if (distancia>0 && distancia<=10) {distanciaAgente=0;}
   else if (distancia>10 && distancia<=20){distanciaAgente=1;}
   else if (distancia>20 && distancia<=30){distanciaAgente=2;}
   else if (distancia>30 && distancia<=40){distanciaAgente=3;}
   else if (distancia>40 && distancia<=50){distanciaAgente=4;}
   else if (distancia>50) {distanciaAgente=5;}    
	
   
   //cout<<"Agente: "<< zonaAgente<< " Angulo: "<<anguloAgente <<" Bola: "<<zonaBola<<endl;
   
   State=(int)(anguloAgente*10000 + zonaAgente*100 + distanciaB*10 + distanciaAgente);
   
   //cout<<"chave Jogador1: "<< State<<endl;
   
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
//* X= 52 A 12 E Y= -34 A +34  *
//*******************************************

int permitir_acao(int acao,float agenteX,float agenteY,float angulo)
{
	int retorno_acao;
	
	if(acao==1)
	{
		if((agenteX>53)&&(angulo>=-89 && angulo<=89))
		{
		  retorno_acao=6;	
		}
		else if((agenteX<-8)&&(angulo<=-91 || angulo>=91 ))
		{
		  retorno_acao=6;	
		}
		else if((agenteY>35)&&(angulo>=0 && angulo<=180))
		{
		  retorno_acao=6;	
		}
		else if((agenteY<-35)&&(angulo<=0 && angulo>=-180))
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
	
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/tabela_Q.txt");
    tab_Q=fopen(file_name,"r");
	
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/tabela_e.txt");
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
	   

     for (a=0;a<50000;a++)
      
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
	
		
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/Periodo/gol_periodo.txt");
    arq=fopen(file_name,"w");
	
    
	evolucao[periodo]=gol_p;	
		
	for(int cont=0;cont<=periodo;cont++)
    {
    fprintf(arq, "%d %d\n",cont,evolucao[cont]);
    } 
		
	fflush(arq);
    fclose(arq);
	
}



void ImprimeDiferencaQ(int periodo)
{
	char file_name[500];
	float SaidaValorNew;
	float somaQ=0;
	int linha,coluna;
	float Valor1,Valor2;
	
	FILE * arq;		
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/Q/diferencaQ.txt");
    arq=fopen(file_name,"w");
	
	for (linha=0;linha<50000;linha++)
	{		
      for (coluna=0;coluna<6;coluna++)
       {     
         //somaQ=somaQ+Q[linha][coluna];
         Valor1=Q[linha][coluna];
         Valor2=TABG[linha][coluna];
         somaQ=somaQ+fabs(Valor1-Valor2);       
	   }
	 }
	 
	 for (linha=0;linha<50000;linha++)
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
	
	
	
	
	
	
}


void ImprimeDiferencaAcoes(void)
{
	char file_name[500];
	
	FILE * arq;		
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/Q/diferencaAcoes.txt");
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
      
	
	  sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/Mapa/caminho.txt");
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
