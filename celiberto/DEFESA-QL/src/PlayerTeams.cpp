

#include "Player.h"
#include "QlearningGoleiro.h"
#include "QlearningZagueiro.h"

#define TEMPO 3000

int ciclo=0; double salvar_ciclo=0; double cicloTEMP=0; double cicloTEMPZ=0;
int ciclo_zagueiro;
double salvar_cicloZ=0;;
int periodo=0;
int periodoZ=0;
int novo_jogo=1;
float tempoACAO=0;
float tempoACAO_zagueiro=0;
bool RunEpisodes=false;
bool RunEpisodes_zagueiro=false;
bool pegar,chutar;
int acaoTemp,acao_escolhida,reforco_da_acao,reforco_da_acao_zagueiro;
int acao_escolhida_Zagueiro;
int estadoFirst,estadoNew;
int estadoFirst_Zagueiro,estadoNew_Zagueiro;
float cateto1,cateto2,A,B,HIPO1;
float cateto12,cateto22,A2,B2,HIPO12,HIPOAdversario;
bool mais_rapido=false;
bool primeiravez_Goleiro=true;
bool primeiravez_Zagueiro=true;


  

/////  GOLEIRO IMPLEMENTADO COM QL(LAMBDA) /////

SoccerCommand Player::Goleiro_QL(  )
{
	
	float agenteX,agenteY,bolax,bolay,angulo;
	float distanciaX, distanciaY,distancia_bola;
	int acaoTemp;
	
	
	
	SoccerCommand soc;
	
	
	VecPosition p1AREA(-52.5,20.5);
    VecPosition p2AREA(-32,-20.5);
	Rect rectangleDefesa(p1AREA,p2AREA);
	
	
	
	// define the top and bottom position of a rectangle in which keeper moves
    static const VecPosition posLeftTop( -PITCH_LENGTH/2.0 +
               0.6*PENALTY_AREA_LENGTH, -PENALTY_AREA_WIDTH/4.0 );
    static const VecPosition posRightTop( -PITCH_LENGTH/2.0 +
               0.6*PENALTY_AREA_LENGTH, +PENALTY_AREA_WIDTH/4.0 );

  // define the borders of this rectangle using the two points.
  static Line  lineFront = Line::makeLineFromTwoPoints(posLeftTop,posRightTop);
  static Line  lineLeft  = Line::makeLineFromTwoPoints(
                         VecPosition( -50.0, posLeftTop.getY()), posLeftTop );
  static Line  lineRight = Line::makeLineFromTwoPoints(
                         VecPosition( -50.0, posRightTop.getY()),posRightTop );

   	
	    if(primeiravez_Goleiro)
		{
			//CarregarArquivo();
			apaga_tabela();
			primeiravez_Goleiro=false;
		}
	
	    if(WM->isBeforeKickOff( )){PosicionaGoleiro();}	
		
		else
		{           			
      		if( WM->getConfidence( OBJECT_BALL ) < PS->getBallConfThr() )
            {
			  
              ACT->putCommandInQueue( soc = searchBall() );   // if ball pos unknown
              ACT->putCommandInQueue( alignNeckWithBody( ) ); // search for it
            }
			
            cicloTEMP=WM->getCurrentCycle();
			
			if(fabs(cicloTEMP-salvar_ciclo)>=TEMPO)
			{ 
                ValorQ=ImprimeDiferencaQ(periodo,ValorQ);                				
				periodo++;
				gol_periodo=0;
                salvar_ciclo=cicloTEMP;			                                					
			}
            if(periodo>=100000)
			{ //termina programa
			  cout<<"Terminando"<<endl;
			  bContLoop =  false;			
			}            			
			
		    		
			
            
			 if((rectangleDefesa.isInside( WM->getBallPos())) &&  (rectangleDefesa.isInside( WM->getAgentGlobalPosition()) ))
			{
			  
              tempoACAO=WM->getCurrentCycle() - WM->getTimeLastAction();
              ciclo=WM->getCurrentCycle();			
				
				
			  if(RunEpisodes)
			  {
				  
				   // Encontra o reforco a ser dado.   
	  		    reforco_da_acao=Reforco(WM->getGoalDiff(),ciclo,acao_escolhida,pegar,chutar,periodo,novo_jogo,HIPO1,tempoACAO);
			 	
				  //cout<<"Reforco dado ao Goleiro"<<reforco_da_acao<<endl;		    				
	  		    
				  // Atualiza o Q(lambda)
	  		    calcula_Qlambda(estadoFirst, estadoNew, acao_escolhida, reforco_da_acao);
					  
			  }
						  
		
               				
				
			  
				// pega o estado.		
	          agenteX=WM->PosAgenteX();
	          agenteY=WM->PosAgenteY();	
	          bolax=WM->PosBolaX(); 
	          bolay=WM->PosBolaY();
              angulo=WM->AngAgente();  
              		
				
			  estadoFirst=escolhe_estado(agenteX,agenteY,angulo,bolax,bolay);
			  
	  		  // escolhe a melhor acao a executar(5% aleatorio).
	  		  acao_escolhida=escolher_acao(estadoFirst);			             
			
			  
              		  
		
		        //Dar para pegar ou chutar a bola ?
			    pegar=WM->isBallCatchable();
			    chutar=WM->isBallKickable();
		
      		   // verifica se nao vai bater em uma parede.		  
	  		  acaoTemp=permitir_acao(acao_escolhida,agenteX,agenteY,angulo);
		
		 	 	  
			  //executa a ação (se nao bater em parede)
	  		  executar_acao(acaoTemp);		     		
		  
	  		    // pega o estado resultante
	 		    agenteX=WM->PosAgenteX(); 
				agenteY=WM->PosAgenteY();	
	  		    bolax=WM->PosBolaX(); 
				bolay=WM->PosBolaY();
      		    angulo=WM->AngAgente();		
				
	  		    estadoNew=escolhe_estado(agenteX,agenteY,angulo,bolax,bolay);
	            
			    //ciclo da acao		    
				
				cateto1=agenteX-bolax;				  
				A=cateto1*cateto1;
                cateto2=agenteY-bolay;
				B=cateto2*cateto2;
				HIPO1=sqrt(A+B);
				
				WM->setLastAction( acaoTemp );
				
				if(!RunEpisodes){RunEpisodes=true;}
				
				//cout<<"Estado "<<estadoFirst<<"Prox. Estado "<<estadoNew<<endl;
		
					
	                      
		
		    }
			
			
		  }

       return soc;
	
}
//********************************************
// ZAGUEIRO APRENDIZADO
//********************************************



SoccerCommand Player::Zagueiro_QL(  )
{
  SoccerCommand soc;
	
  float agenteX,agenteY,bolax,bolay,angulo;
  float distanciaX, distanciaY,distancia_bola;
  int acaoTemp;
  int iTmp; 
	
  //VecPosition p1AREA(-40,34);
  //VecPosition p2AREA(-10,-34);
	
  VecPosition p1AREA(-44.5,30.5);
  VecPosition p2AREA(-15.5,-30.5);
	
  Rect rectangleDefesa(p1AREA,p2AREA);
	
	
  cicloTEMPZ=WM->getCurrentCycle();
			
  if(fabs(cicloTEMPZ-salvar_cicloZ)>=TEMPO)
  { 
    ValorQ_Zagueiro=ImprimeDiferencaQ_Zagueiro(periodoZ,ValorQ_Zagueiro);
    periodoZ++;
	salvar_cicloZ=cicloTEMPZ;			                                					
  }	
	
	
	
  
  if(primeiravez_Zagueiro)
  {
	  //CarregarArquivo_Zagueiro();
	  apaga_tabela_zagueiro();
	  primeiravez_Zagueiro=false;
  }
	
  if(WM->isBeforeKickOff( ))
				
	{				
	 formations->setFormation( FT_INITIAL );       
     ACT->putCommandInQueue( soc=teleportToPos( WM->getStrategicPosition() ));
	}		
	
  else if((rectangleDefesa.isInside( WM->getBallPos())) &&  (rectangleDefesa.isInside( WM->getAgentGlobalPosition()) ))
	{
	   formations->setFormation( FT_433_OFFENSIVE );
	   tempoACAO_zagueiro=WM->getCurrentCycle() - WM->getTimeLastAction_zagueiro();
       ciclo_zagueiro=WM->getCurrentCycle();			
				
	   if(RunEpisodes_zagueiro)
		 {				  
		  // Encontra o reforco a ser dado.   
	  	  reforco_da_acao_zagueiro=Reforco_Zagueiro(WM->getGoalDiff(),ciclo_zagueiro,acao_escolhida_Zagueiro,mais_rapido,chutar,periodo,novo_jogo,HIPO12,HIPOAdversario,tempoACAO_zagueiro);
          // Atualiza o Q(lambda)
	  	  calcula_Qlambda_Zagueiro(estadoFirst_Zagueiro, estadoNew_Zagueiro, acao_escolhida_Zagueiro, reforco_da_acao_zagueiro);
	      }             				
				// pega o estado.		
	          agenteX=WM->PosAgenteX();
	          agenteY=WM->PosAgenteY();	
	          bolax=WM->PosBolaX(); 
	          bolay=WM->PosBolaY();
              angulo=WM->AngAgente();          		
				
			  estadoFirst_Zagueiro=escolhe_estado_Zagueiro(agenteX,agenteY,angulo,bolax,bolay);
			  
	  		  // escolhe a melhor acao a executar(5% aleatorio).
	  		  acao_escolhida_Zagueiro=escolher_acao_Zagueiro(estadoFirst_Zagueiro);			             
			       
			  //sou o mais rapido ?
              if( WM->getFastestInSetTo( OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp )== WM->getAgentObjectType()  && !WM->isDeadBallThem() )
              {mais_rapido=true;}
              else{mais_rapido=false;}
            
             // if(mais_rapido){cout<<"Mais rapido"<<endl;}
		     // else {cout<<"2 Mais rapido"<<endl;}
          				  
		      // Da para chutar a bola ?		  
			  chutar=WM->isBallKickable();
		
      		   // verifica se nao vai bater em uma parede.		  
	  		  acaoTemp=permitir_acao_Zagueiro(acao_escolhida_Zagueiro,agenteX,agenteY,angulo);

		 	 	  
			  //executa a ação (se nao bater em parede)
	  		  executar_acao_Zagueiro(acaoTemp);	
              //cout<<"Executado acao "<<acaoTemp<<endl;			  
		  
	  		    // pega o estado resultante
	 		    agenteX=WM->PosAgenteX(); 
				agenteY=WM->PosAgenteY();	
	  		    bolax=WM->PosBolaX(); 
				bolay=WM->PosBolaY();
      		    angulo=WM->AngAgente();		
				
	  		    estadoNew_Zagueiro=escolhe_estado_Zagueiro(agenteX,agenteY,angulo,bolax,bolay);
	            
			    //Distancia Bola - Agente   
             	HIPO12=WM->getRelativeDistance(OBJECT_BALL);				
				//Distancia Agente-Adversario
				ObjectT    objADV;
				double     dMinDistADV;	
    			objADV = WM->getClosestInSetTo( OBJECT_SET_OPPONENTS, WM->getAgentObjectType(), &dMinDistADV);				
	            HIPOAdversario=WM->getRelativeDistance(objADV);
								
				WM->setLastAction_zagueiro( acaoTemp );
				
				if(!RunEpisodes_zagueiro){RunEpisodes_zagueiro=true;}
				
				//cout<<"Estado "<<estadoFirst_Zagueiro<<" Prox. Estado "<<estadoNew_Zagueiro<<endl;
	          
		
		    }
			
			
	
	
	
  return soc;
	
}



//**** Funcoes de comunicacao com o QL para salvar ou carregar tabela ////
//SoccerCommand Player::salvar(){SalvarArquivo();}
SoccerCommand Player::carregar(){CarregarArquivo();}
SoccerCommand Player::Limpa_tabela(){apaga_tabela();}
