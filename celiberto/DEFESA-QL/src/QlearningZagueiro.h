#include <sys/time.h>
#include "math.h"



//declarações
void apaga_tabela_zagueiro(void);
void calcula_Qlambda_Zagueiro(int estado, int estadoN, int acao, float reforcoAcao);
int melhor_acao_a_Zagueiro(int estado);
int escolher_acao_Zagueiro(int estado);
int Reforco_Zagueiro(int gol,int ciclo,int acao,bool rapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo);
int v_randomico_Zagueiro (void);
void CarregarArquivo_Zagueiro();
void Salva_Bolaemjogo (int periodo_bola,int ciclo);


//Variaveis
float passoX_Zagueiro[100];float passoY_Zagueiro[100];int passos_Zagueiro=0;
int evolucao_Zagueiro[1000];
float ValorQnew_Zagueiro[1000];
float ValorQ_Zagueiro=0;
int golOldZ;
int cicloOLD; 
int gol_tomado=0;
int Vciclo[100000];	
	

//    Q[xr ][yr][tr][xb][yb][acao]
//*********** TABELA "Q" e "e" ************

float QZagueiro[50000][6];
float eZagueiro[50000][6];
float TABZ[50000][6];

void apaga_tabela_zagueiro(void)
{
int linha,coluna;
 cout<< "Carregando protocolos de Aprendizado Zagueiro"<<endl;
	
 for (linha=0;linha<45000;linha++)
  {	 
     for (int coluna=0;coluna<6;coluna++)
   {     
     QZagueiro[linha][coluna]= 0;     	   
   }
  }
   for (linha=0;linha<45000;linha++)   
     for (int coluna=0;coluna<6;coluna++)
   {     
     TABZ[linha][coluna]= 0;
     	   
   }
    cout<< "Pronto !"<<endl;
 
     
}


//**************************************
//* Calcula o Q-lambda                 *
//**************************************

void calcula_Qlambda_Zagueiro(int estado, int estadoN, int acao, float reforcoAcao)
{
   // definindo valores
   static float gama_Zagueiro=0.9;
   static float alfa_Zagueiro=0.125;
   static float lambda_Zagueiro=0.5;
   //definindo variaveis	
   float Ql_Zagueiro=0;
   float Qatual_Zagueiro=0;
   float Qa_Zagueiro;
   float delta_Zagueiro=0;
   float eNew_Zagueiro=0;
   float Q_valor_Zagueiro=0;
   

   
   
   // Encontra a*  e  Q(s', a');	 
   int estado_a = melhor_acao_a_Zagueiro(estadoN);   
   Qa_Zagueiro=QZagueiro[estadoN][estado_a];
   
   //Encontra o valor de Q anterior
   Ql_Zagueiro=QZagueiro[estado][acao];
	
   
   //calcula delta
   delta_Zagueiro= ((-1+reforcoAcao) + (gama_Zagueiro*Qa_Zagueiro) - Ql_Zagueiro);
	
   //e(s,a)=e(s,a)+1
   //eZagueiro[estado][acao]++;	
	
	
   //Calcula o QL
   
   QZagueiro[estado][acao]=
      (
        QZagueiro[estado][acao]+(alfa_Zagueiro*delta_Zagueiro)
      );
	   
	   
	
    //atualizando valores em "e" 
    /*for(int cont=0;cont<5;cont++)
	{
	  if(cont==acao)
	     eZagueiro[estado][cont]=gama_Zagueiro*lambda_Zagueiro*eZagueiro[estado][acao];
      else
		 eZagueiro[estado][cont]=0;
    }*/
  
  //system("clear");
  cout<<" "<<endl;
  cout<<" Zagueiro "<<endl;
  cout<<"Acao: "<<acao<<" R : "<<reforcoAcao<<" QL: "<<QZagueiro[estado][acao]<<" e: "<<eZagueiro[estado][acao]<<" delta: "<<delta_Zagueiro<<endl;	
  cout<<" "<<endl;	
   
	 
	
}

//************************************
//*  Acha o maior valor para o a*    *
//*   a*=argmaxb Q(s', b)            *
//************************************
int melhor_acao_a_Zagueiro(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  maiorvalor=QZagueiro[estado][0];
  
  float tempvalor=0;  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=QZagueiro[estado][cont];
    
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

int escolher_acao_Zagueiro(int estado)
{
  
  int acao=0;
  float maiorvalor=0;
  float tempvalor=0;
  
  maiorvalor=QZagueiro[estado][0];
  
  
  for(int cont=0;cont<6;cont++)
  {
    tempvalor=(QZagueiro[estado][cont]);
    
     if(tempvalor>maiorvalor)
      {
         maiorvalor=tempvalor;
	     acao=cont;      
      }         
   }
    
    //5% de exploracao
    if(v_randomico_Zagueiro()==0)
    {     	  
      srand(time(NULL));
      acao=rand()%6;     
    }   
     
 return acao;
}


//*********************************************
//*          Calcula o Reforco                *
//*********************************************

int Reforco_Zagueiro(int gol,int ciclo,int acao,bool rapido,bool isBallKickable,int periodo,int jogo,float dist,float distADV,float tempo)
{
  int reforco=0;
  int bomReforco=0;
  int angulo, jogador,bola;
 
	
   //if (acao==0){bomReforco=-1;}
	
   if (isBallKickable && acao==3)       {bomReforco=2;}   
   else if (isBallKickable && acao==4)  {bomReforco=1;}
   else if(rapido && dist>2 && acao!=1) {bomReforco=-1;}
   //else if (isBallKickable && acao==2){bomReforco=1;}
   //else if(!rapido && dist>2 && acao!=2 ) {bomReforco=-3;}
   if(gol<golOldZ)  	{bomReforco=-2;golOldZ=gol;}
  
   
  //cout<<"Distancia bola: "<<dist <<endl;
 /*  if (bomReforco==-3)
  {	 
    reforco=-10; 
  }*/  	
  
  if (bomReforco==-2)
  {	 
    reforco=-25;
	gol_tomado++;
    Salva_Bolaemjogo (gol_tomado,ciclo);
    	  
    //ciclo_antigo=ciclo;
  }  	
   
  if (bomReforco==-1)
  {    	  
	reforco=-10;
	
  }
  if (bomReforco==1 )
  {         
	reforco=10+((int)tempo); //15
    //ciclo_antigo=ciclo;
  }  
  if (bomReforco==2 )
  {         
	reforco=10;  //5
    //ciclo_antigo=ciclo;
  }  
 
     
  return reforco;

}

//*********************************************
//*          Escolhe o estado pela observacao *
//*********************************************





int escolhe_estado_Zagueiro(float agenteX,float agenteY,float angulo,float bolaX, float bolaY)
{
   
   int aX,aY,angle,bX,bY;
   int State;
   int zonaAgente=0;
   int zonaBola=0;
   int anguloAgente=0; 
	
   
   aX=(int)((agenteX)+45);   
   aY=(int)((agenteY)+30);
	
   cout<<"X: "<<agenteX<<" Y: "<<agenteY<<endl;

   if(aX<0){aX=0;}
   if(aX>30){aX=30;}
   if(aY<0)   {aY=0;}
   if(aY>60)  {aY=60;}
   
	
   if(aX>=0 && aX<=5)  {zonaAgente=0;}
   if(aX>5 && aX<=10)  {zonaAgente=1;}
   if(aX>10 && aX<=15) {zonaAgente=2;}
   if(aX>15 && aX<=20) {zonaAgente=3;}
   if(aX>20 && aX<=25) {zonaAgente=4;}
   if(aX>25 && aX<=30) {zonaAgente=5;}
   
  
   if(aY>=0 && aY<=10){zonaAgente=zonaAgente+0;}
   if(aY>10 && aY<=20){zonaAgente=zonaAgente+6;}
   if(aY>20 && aY<=30){zonaAgente=zonaAgente+12;}
   if(aY>30 && aY<=40){zonaAgente=zonaAgente+18;}
   if(aY>40 && aY<=50){zonaAgente=zonaAgente+24;}
   if(aY>50 && aY<=60){zonaAgente=zonaAgente+30;}
   
	
	
   angle=(int)(angulo+180);
   
   
   //cout<<"angulo "<< angle<<endl;
   if(angle>135 && angle<=225){anguloAgente=0;}
   if(angle>225 && angle<315){anguloAgente=1;}	
   if(angle<=45 || angle>=315){anguloAgente=2;}
   if(angle>45 && angle<=135){anguloAgente=3;}   
  
	   
	
   bX=(int)(((bolaX)+45));   
   bY=(int)(((bolaY)+30));
   
   if(bX<0){bX=0;}
   if(bX>30){bX=30;}
   if(bY<0)   {bY=0;}
   if(bY>68)  {bY=68;}
   
   if(bX>=0 && bX<=5)  {zonaBola=0;}
   if(bX>5 && bX<=10)  {zonaBola=1;}
   if(bX>10 && bX<=15) {zonaBola=2;}
   if(bX>15 && bX<=20) {zonaBola=3;}
   if(bX>20 && bX<=25) {zonaBola=4;}
   if(bX>25 && bX<=30) {zonaBola=5;}
   
  
   if(bY>=0 && bY<=10){zonaBola=zonaBola+0;}
   if(bY>10 && bY<=20){zonaBola=zonaBola+6;}
   if(bY>20 && bY<=30){zonaBola=zonaBola+12;}
   if(bY>30 && bY<=40){zonaBola=zonaBola+18;}
   if(bY>40 && bY<=50){zonaBola=zonaBola+24;}
   if(bY>50 && bY<=60){zonaBola=zonaBola+30;}
     
   cout<<"Agente: "<< zonaAgente<< " Angulo: "<<anguloAgente <<" Bola: "<<zonaBola<<endl;
   
   State=(int)(anguloAgente*10000 + zonaAgente*100 + zonaBola);
   
   cout<<"chave: "<< State<<endl;
   
   return State;
}


// 5% de exploracao(escolhe um valor de 0-20)
int v_randomico_Zagueiro (void)
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

int permitir_acao_Zagueiro(int acao,float agenteX,float agenteY,float angulo)
{
	int retorno_acao;
	
	//cout<< agenteX <<" "<< agenteY <<" "<<angulo<<endl;
	
	if(acao==1)
	{
		if((agenteX>=-15)&&(angulo>=-89 && angulo<=89))
		{
		  retorno_acao=5;	
		}
		else if((agenteX<=-45)&&(angulo<=-91 || angulo>=91 ))
		{
		  retorno_acao=5;	
		}
		else if((agenteY>30)&&(angulo>=0 && angulo<=180))
		{
		  retorno_acao=5;	
		}
		else if((agenteY<-30)&&(angulo<=0 && angulo>=-180))
		{
		  retorno_acao=5;	
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

void CarregarArquivo_Zagueiro()
{
	char file_name[400];
	int a,b,c,d,e1;
	
	FILE * tab_Q;
	FILE * tab_e;
	
	sprintf (file_name,"/home/sysop/Futebol/hashGoleiro-QL/src/Tabela/tabela_Q.txt");
    tab_Q=fopen(file_name,"r");
	
	sprintf (file_name,"/home/sysop/Futebol/hashGoleiro-QL/src/Tabela/tabela_e.txt");
    tab_e=fopen(file_name,"r");
	
	if(!tab_Q)
	{
		
		cout<< "Gerando Tabelas Zagueiro !"<<endl;
		apaga_tabela_zagueiro();
		cout<<"Pronto para Jogar ! :-)"<<endl;
		
		
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






void Salvaperiodo_Zagueiro (int periodo, int gol_p, int jogo)
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



float ImprimeDiferencaQ_Zagueiro(int periodoZagueiro,float ValorQoldZ)
{
	char file_name[500];
	float SaidaValorNewzagueiro=0;
	float somaQz=0;
	int linha,coluna;
	int cont=0;
	float Valor1,Valor2;
	
	FILE * arqZ;		
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/Q/diferencaQ_Zagueiro.txt");
    arqZ=fopen(file_name,"w");
	
	for (linha=0;linha<45000;linha++){   
      for (coluna=0;coluna<6;coluna++)
       {     
         //somaQz=somaQz+QZagueiro[linha][coluna];
	     Valor1=QZagueiro[linha][coluna];
         Valor2=TABZ[linha][coluna];
         somaQz=somaQz+fabs(Valor1-Valor2);        	   
        }}
	for (linha=0;linha<45000;linha++)
		{   
         for (coluna=0;coluna<6;coluna++)
           {   
		   TABZ[linha][coluna]=	QZagueiro[linha][coluna];
		   }
   		}
		
	
	ValorQnew_Zagueiro[periodoZagueiro]=somaQz;
	
		
    for(cont=0;cont<=periodoZagueiro;cont++)
    {
     fprintf(arqZ, "%d %f\n",cont,ValorQnew_Zagueiro[cont]);	 
    } 
		
	fflush(arqZ);
    fclose(arqZ);
	
	SaidaValorNewzagueiro=somaQz;
	
	return SaidaValorNewzagueiro;//nao precisa mais retornar
	                             //mas nao mudei...
	
	
}


void Salva_Bolaemjogo (int periodo_bola,int ciclo)
{
	char file_name[400];
	FILE *tempobola;
	int difCICLOS;
    
	sprintf (file_name,"/home/sysop/Futebol/DEFESA-QL/src/Tabela/tempobola.txt");
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

void SalvaMAPA_Zagueiro (float agenteX, float agenteY,bool gravar)
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
