#include <sys/time.h>
#include "math.h"



//declarações
void apaga_tabela_atacante2(void);
void calcula_Qlambda_atacante2(int estado, int estadoN, int acao, float reforcoAcao);
int melhor_acao_a_atacante2(int estado);
int escolher_acao_atacante2(int estado);
int Reforco_atacante2(int gol,int ciclo,int acao,bool rapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo);
int v_randomico_atacante2 (void);
void CarregarArquivo_atacante2();
void Salva_Bolaemjogo (int periodo_bola,int ciclo);
void ImprimeDiferencaQ_atacante2(int periodoatacante2);
int escolhe_estado2v2T2(float agenteX,float agenteY,float angulo,float distanciaBola,float distancia);



//Variaveis
float passoX_atacante2[100];float passoY_atacante2[100];int passos_atacante2=0;
int evolucao_atacante2[1000];
float ValorQnew_atacante2[1000];
float ValorQ_atacante2=0;
int golOldAT;
int cicloOLD; 
int gol_tomado=0;
int Vciclo[100000];	
	

//    Q[xr ][yr][tr][xb][yb][acao]
//*********** TABELA "Q" e "e" ************

float Qatacante2[50000][6];
float TABAT[50000][6];

void apaga_tabela_atacante2(void)
{
int linha,coluna;
 cout<< "Carregando protocolos de Aprendizado atacante 2"<<endl;
	
 for (linha=0;linha<50000;linha++)
  {	 
     for (int coluna=0;coluna<6;coluna++)
     {     
     Qatacante2[linha][coluna]= 0;     	   
     }
  }
   for (linha=0;linha<50000;linha++)   
     for (int coluna=0;coluna<6;coluna++)
     {     
     TABAT[linha][coluna]= 0;
     	   
    }
    cout<< "Pronto !"<<endl;
 
     
}


//**************************************
//* Calcula o Q-lambda                 *
//**************************************

void calcula_Qlambda_atacante2(int estado, int estadoN, int acao, float reforcoAcao)
{
   // definindo valores
   static float gama_atacante2=0.9;
   static float alfa_atacante2=0.125;
   static float lambda_atacante2=0.5;
   //definindo variaveis	
   float Ql_atacante2=0;
   float Qatual_atacante2=0;
   float Qa_atacante2;
   float delta_atacante2=0;
   float eNew_atacante2=0;
   float Q_valor_atacante2=0;
   

   
   
   // Encontra a*  e  Q(s', a');	 
   int estado_a = melhor_acao_a_atacante2(estadoN);   
   Qa_atacante2=Qatacante2[estadoN][estado_a];
   
   //Encontra o valor de Q anterior
   Ql_atacante2=Qatacante2[estado][acao];
	
   
   //calcula delta
   delta_atacante2= ((-1+reforcoAcao) + (gama_atacante2*Qa_atacante2) - Ql_atacante2);
	
   
   //Calcula o QL
   
   Qatacante2[estado][acao]=
      (
        Qatacante2[estado][acao]+(alfa_atacante2*delta_atacante2)
      );
	   
	   
	
    
  
  //system("clear");
  //cout<<" "<<endl;
  cout<<" ATACANTE 2 "<<endl;
  cout<<"Acao: "<<acao<<" R : "<<reforcoAcao<<" QL: "<<Qatacante2[estado][acao]<<" delta: "<<delta_atacante2<<endl;	
  //cout<<" "<<endl;	
   
	 
	
}

//************************************
//*  Acha o maior valor para o a*    *
//*   a*=argmaxb Q(s', b)            *
//************************************
int melhor_acao_a_atacante2(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  maiorvalor=Qatacante2[estado][0];
  
  float tempvalor=0;  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=Qatacante2[estado][cont];
    
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

int escolher_acao_atacante2(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  float tempvalor=0;
  
  maiorvalor=Qatacante2[estado][0];
  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=(Qatacante2[estado][cont]);
    
     if(tempvalor>maiorvalor)
      {
         maiorvalor=tempvalor;
	     acao=cont;      
      }         
   }
    
    //5% de exploracao
    if(v_randomico_atacante2()==0)
    {     	  
      srand(time(NULL));
      acao=rand()%6;     
    }   
     
 return acao;
}


//*********************************************
//*          Calcula o Reforco                *
//*********************************************

int Reforco_atacante2(int gol,int ciclo,int acao,bool Mrapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo,float pegou)
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
	  if(acao==2){reforco=100;}
      else{reforco=25;}  	  
    }	  
  
  
  
  
 
     
  return reforco;

}

//*********************************************
//*          Escolhe o estado pela observacao *
//*********************************************

int escolhe_estado2v2T2(float agenteX,float agenteY,float angulo,float distanciaBola,float distancia)
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
int v_randomico_atacante2 (void)
{
  int valor_ramdomico;   
  srand((unsigned int)time(NULL));
  valor_ramdomico=rand()%19;	
  return valor_ramdomico;	
}


//*****  Verifica se vai bater ****** //sysop 
//*      DELIMITA GRANDE AREA       *
//* X= -51 A 12 E Y= -20 A +20  *
//*******************************************

int permitir_acao_atacante2(int acao,float agenteX,float agenteY,float angulo)
{int retorno_acao;
	
	if(acao==1)
	{
		if((agenteX>=53)&&(angulo>=-89 && angulo<=89))
		{
		  retorno_acao=6;	
		}
		else if((agenteX<=-8)&&(angulo<=-91 || angulo>=91 ))
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

void CarregarArquivo_atacante2()
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
		
		cout<< "Gerando Tabelas atacante2 !"<<endl;
		apaga_tabela_atacante2();
		cout<<"Pronto para Jogar ! :-)"<<endl;
		
		
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






void Salvaperiodo_atacante2 (int periodo, int gol_p, int jogo)
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



void ImprimeDiferencaQ_atacante2(int periodoatacante2)
{
	char file_name[500];
	float somaQAT=0;
	int linha,coluna;
	int cont=0;
	float Valor1,Valor2;
	
	FILE * arqAT;		
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/Q/diferencaQ_atacante2.txt");
    arqAT=fopen(file_name,"w");
	
	for (linha=0;linha<50000;linha++)
	{   
      for (coluna=0;coluna<6;coluna++)
       {     
         
	     Valor1=Qatacante2[linha][coluna];
         Valor2=TABAT[linha][coluna];
         somaQAT=somaQAT+fabs(Valor1-Valor2);        	   
        }
	}
	for (linha=0;linha<50000;linha++)
		{   
         for (coluna=0;coluna<6;coluna++)
           {   
		   TABAT[linha][coluna]=Qatacante2[linha][coluna];
		   }
   		}
		
	
	ValorQnew_atacante2[periodoatacante2]=somaQAT;
	
		
    for(cont=0;cont<=periodoatacante2;cont++)
    {
     fprintf(arqAT, "%d %f\n",cont,ValorQnew_atacante2[cont]);	 
    } 
		
	fflush(arqAT);
    fclose(arqAT);
	
		
	
}


void Salva_Bolaemjogo (int periodo_bola,int ciclo)
{
	char file_name[400];
	FILE *tempobola;
	int difCICLOS;
    
	sprintf (file_name,"/home/sysop/Futebol/ATAQUE-QL/src/Tabela/tempobola.txt");
    tempobola=fopen(file_name,"w");
	
	
	difCICLOS=ciclo-cicloOLD;
	
    cicloOLD=ciclo;
	
	
	Vciclo[periodo_bola]=Vciclo[periodo_bola]+difCICLOS;	
		
	for(int cont=1;cont<=periodo_bola;cont++)
    {
    fprintf(tempobola, "%d %d\n",cont,Vciclo[cont]);
    } 
		
	fflush(tempobola);
    fclose(tempobola);
	
	
	
	
	
}

void SalvaMAPA_atacante2 (float agenteX, float agenteY,bool gravar)
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
