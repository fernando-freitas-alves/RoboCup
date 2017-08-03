

#include "Player.h"


#include "QlearningAtacante1.h"
#include "QlearningAtacante2.h"

//#define TEMPO 6000
#define TEMPO 3000

//VARIAVEIS
bool primeiravez_Ataque1=true;
bool primeiravez_Ataque2=true;
int ciclo=0; double salvar_ciclo=0;double salvar_cicloAT2=0; double cicloTEMP=0; 
double cicloTEMP_AT2=0;
int periodo=0;
int periodoAT2=0;
bool RunEpisodesAT1=false;bool RunEpisodesAT2=false;
float DISTAT1;float DISTAT2;float tempoACAO=0;float tempoACAOAT2=0;
int acaoTemp,acao_escolhida,acao_escolhidaAT2,reforco_da_acaoAT1,reforco_da_acaoAT2;
float pegar; float pegarAT2; //tirar isto depois
float chutar;float chutarAT2;
int novo_jogo=1;
int estadoFirst,estadoNew;
int estadoFirstAT2,estadoNewAT2;
bool mais_rapidoAT1;
bool mais_rapidoAT2;
float AdversarioAT2;
float AdversarioAT1;
ObjectT    objADVAT1;
double     dMinDistADVAT1;
ObjectT    objADVAT2;
double     dMinDistADVAT2;
float distanciaBola;
float Vtempo=0;
bool GoleiroPegou=false;
float Vtempo2=0;
bool GoleiroPegou2=false;
////////////////////


/////  ATACANTE_1 IMPLEMENTADO COM Q-LEARNIG /////




SoccerCommand Player::ATACANTE_1(  )
{
	
	float agenteX,agenteY,bolax,bolay,angulo;
	float distanciaJogador;
	float distanciaX, distanciaY,distancia_bola;
	int acaoTemp;
    int iTmp1;
   		
	
	SoccerCommand soc;
	
	
	VecPosition p1AREA(52.5,35);
    VecPosition p2AREA(-8,-35);
	Rect rectangleDefesa(p1AREA,p2AREA);
	
	
	
	
   	
	    if(primeiravez_Ataque1)
		{
			//CarregarArquivo();
			apaga_tabela();
			primeiravez_Ataque1=false;
		}  
	
	    if(WM->isBeforeKickOff( )) //posicao
		{			
			
			formations->setFormation( FT_INITIAL );       // go to kick_off formation
            ACT->putCommandInQueue( soc=teleportToPos( WM->getStrategicPosition() ));
    		GoleiroPegou=false;
		}			
		
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
                ImprimeDiferencaQ(periodo);                				
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
			  
              if(RunEpisodesAT1)
			    {				      
	  		      reforco_da_acaoAT1=Reforco(WM->getGoalDiff(),ciclo,acao_escolhida,mais_rapidoAT1,chutar,periodo,novo_jogo,DISTAT1,AdversarioAT1,tempoACAO,GoleiroPegou);
			 	  calcula_Qlambda(estadoFirst, estadoNew, acao_escolhida, reforco_da_acaoAT1);
			      GoleiroPegou=false;
					}

			  // pega o estado.		
	          agenteX=WM->PosAgenteX();
	          agenteY=WM->PosAgenteY();	          
              angulo=WM->AngAgente();
			  distanciaBola=WM->getRelativeDistance(OBJECT_BALL);

              //acha distancia do jogador 11
			  distanciaJogador=WM->getRelativeDistance(OBJECT_TEAMMATE_10);			  
			
    		  estadoFirst=escolhe_estado2v2(agenteX,agenteY,angulo,distanciaBola,distanciaJogador);
			  
				
			  // escolhe a melhor acao a executar(5% aleatorio).
	  		  acao_escolhida=escolher_acao(estadoFirst);

              //Dar para chutar a bola ?
			  chutar=WM->isBallKickable();
			  //sou o mais rapido ?
              if( WM->getFastestInSetTo( OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp1 )== WM->getAgentObjectType()  && !WM->isDeadBallThem() )
              {mais_rapidoAT1=true;}
              else{mais_rapidoAT1=false;}
              DISTAT1=WM->getRelativeDistance(OBJECT_BALL);			  

              // verifica se nao vai bater em uma parede.		  
	  		  acaoTemp=permitir_acao(acao_escolhida,agenteX,agenteY,angulo);
				
              //executa a ação (se nao bater em parede)
	  		  executar_acao_AT1(acaoTemp);
			  
			  
			  //TESTE DE GOLEIRO
			  double D, DG, d1, d;
			  VecPosition pos_goleiro_adversario(WM->getGlobalPosition(OBJECT_OPPONENT_GOALIE).getX(),WM->getGlobalPosition(OBJECT_OPPONENT_GOALIE).getY());
              VecPosition posGoal( PITCH_LENGTH/2.0,-0.4 * SS->getGoalWidth() ); // otendo objetivo do gol
		      VecPosition   posAgent = WM->getAgentGlobalPosition();
		      double a = posAgent.getY()-posGoal.getY();
              double b = posGoal.getX()-posAgent.getX();
              double c = posAgent.getX()*posGoal.getY()-posAgent.getY()*posGoal.getX();
              Line trajetoria(a,b,c);
			  D = posAgent.getDistanceTo(posGoal);
			  // testa se o goleiro esta fora da segmento de reta
              if (posGoal.getX()<trajetoria.getPointOnLineClosestTo(pos_goleiro_adversario).getX()) 
              {
				//cout<<"OK"<<endl;
				GoleiroPegou=false;
                //DG=pos_goleiro_adversario.getDistanceTo(posGoal);
              }
              else
              {
			   GoleiroPegou=true;
			   //cout<<"Nao chutar"<<endl;
               //DG=pos_goleiro_adversario.getDistanceTo(trajetoria.getPointOnLineClosestTo(pos_goleiro_adversario)); // goleiro no segmento de reta
              };
			  
			  

             // pega o estado resultante
	 		    agenteX=WM->PosAgenteX(); 
				agenteY=WM->PosAgenteY();	
	  		    bolax=WM->PosBolaX(); 
				bolay=WM->PosBolaY();
      		    angulo=WM->AngAgente();
			    distanciaBola=WM->getRelativeDistance(OBJECT_BALL);
                //achar posicao do 10
			    distanciaJogador=WM->getRelativeDistance(OBJECT_TEAMMATE_10);			  
							  
				
	  		    estadoNew=escolhe_estado2v2(agenteX,agenteY,angulo,distanciaBola,distanciaJogador);
	            
			    //ciclo da acao		    
				
				DISTAT1=WM->getRelativeDistance(OBJECT_BALL);
			    objADVAT1 = WM->getClosestInSetTo( OBJECT_SET_OPPONENTS, WM->getAgentObjectType(), &dMinDistADVAT1);				
	            AdversarioAT1=WM->getRelativeDistance(objADVAT1);
				WM->setLastAction( acaoTemp );
				
					               

				if(!RunEpisodesAT1){RunEpisodesAT1=true;}			 
				 
		    }
			else{
				if( WM->isBallKickable() )
				  {
					  SoccerCommand soc;
					  VecPosition posGoal( PITCH_LENGTH/2.0,
                             (-1 + 2*(WM->getCurrentCycle()%2)) * 
                             0.4 * SS->getGoalWidth() );
                        soc = kickTo( posGoal, 0 ); // kick maximal
        				ACT->putCommandInQueue( soc);	  
				  }
				  else{interceptar_bola();}		
				
				
				
				
				}
			
			
		  }

       return soc;
	
}
//********************************************
// ATACANTE_2 APRENDIZADO
//********************************************



SoccerCommand Player::ATACANTE_2(  )
{
	
	float agenteX,agenteY,bolax,bolay,angulo;
	float distanciaJogador;
	float distanciaX, distanciaY,distancia_bola;
	int acaoTemp;	
	int iTmp2;
		
	SoccerCommand soc;
	
	VecPosition p1AREA(52.5,35);
    VecPosition p2AREA(-8,-35);
	Rect rectangleDefesa(p1AREA,p2AREA);	
	
	
   	
	    if(primeiravez_Ataque2)
		{
			//CarregarArquivo();
			apaga_tabela_atacante2();
			primeiravez_Ataque2=false;
		}
	
	    if(WM->isBeforeKickOff( ))
		{			
			
			formations->setFormation( FT_INITIAL );       // go to kick_off formation
            ACT->putCommandInQueue( soc=teleportToPos( WM->getStrategicPosition() ));
    	   
				
			
		}	
		
		else
		{           			
      		if( WM->getConfidence( OBJECT_BALL ) < PS->getBallConfThr() )
            {
			  
              ACT->putCommandInQueue( soc = searchBall() );   // if ball pos unknown
              ACT->putCommandInQueue( alignNeckWithBody( ) ); // search for it
            }
			
            cicloTEMP_AT2=WM->getCurrentCycle();
			
			if(fabs(cicloTEMP_AT2-salvar_cicloAT2)>=TEMPO)
			{ 
                ImprimeDiferencaQ_atacante2(periodoAT2);                				
				periodoAT2++;
				salvar_cicloAT2=cicloTEMP_AT2;			                                					
			}		
            
			 if((rectangleDefesa.isInside( WM->getBallPos())) &&  (rectangleDefesa.isInside( WM->getAgentGlobalPosition()) ))
			{
			  tempoACAOAT2=WM->getCurrentCycle() - WM->getTimeLastAction_zagueiro();
              ciclo=WM->getCurrentCycle();
              if(RunEpisodesAT2)
			    {
                  					
	  		      reforco_da_acaoAT2=Reforco_atacante2(WM->getGoalDiff(),ciclo,acao_escolhidaAT2,mais_rapidoAT2,chutarAT2,periodoAT2,novo_jogo,DISTAT2,AdversarioAT2,tempoACAOAT2,GoleiroPegou2);
			 	  calcula_Qlambda_atacante2(estadoFirstAT2, estadoNewAT2, acao_escolhidaAT2, reforco_da_acaoAT2);
			      GoleiroPegou2=false;
				}

			  // pega o estado.		
	          agenteX=WM->PosAgenteX();
	          agenteY=WM->PosAgenteY();	
	          
              angulo=WM->AngAgente();
              distanciaJogador=WM->getRelativeDistance(OBJECT_TEAMMATE_11);			  
			  distanciaBola=WM->getRelativeDistance(OBJECT_BALL);
                					

			  estadoFirstAT2=escolhe_estado2v2T2(agenteX,agenteY,angulo,distanciaBola,distanciaJogador);
			  // escolhe a melhor acao a executar(5% aleatorio).
	  		  acao_escolhidaAT2=escolher_acao_atacante2(estadoFirstAT2);

              //Dar para chutar a bola ?
			  chutarAT2=WM->isBallKickable();
              //sou o mais rapido ?
              if( WM->getFastestInSetTo( OBJECT_SET_TEAMMATES, OBJECT_BALL, &iTmp2 )== WM->getAgentObjectType()  && !WM->isDeadBallThem() )
              {mais_rapidoAT2=true;}
              else{mais_rapidoAT2=false;}
              DISTAT2=WM->getRelativeDistance(OBJECT_BALL);			  

              // verifica se nao vai bater em uma parede.		  
	  		  acaoTemp=permitir_acao_atacante2(acao_escolhidaAT2,agenteX,agenteY,angulo);
				
              //executa a ação (se nao bater em parede)
	  		  executar_acao_AT2(acaoTemp);
			  //TESTE DE GOLEIRO
			  double D, DG, d1, d;
			  VecPosition pos_goleiro_adversario(WM->getGlobalPosition(OBJECT_OPPONENT_GOALIE).getX(),WM->getGlobalPosition(OBJECT_OPPONENT_GOALIE).getY());
              VecPosition posGoal( PITCH_LENGTH/2.0,-0.4 * SS->getGoalWidth() ); // otendo objetivo do gol
		      VecPosition   posAgent = WM->getAgentGlobalPosition();
		      double a = posAgent.getY()-posGoal.getY();
              double b = posGoal.getX()-posAgent.getX();
              double c = posAgent.getX()*posGoal.getY()-posAgent.getY()*posGoal.getX();
              Line trajetoria(a,b,c);
			  D = posAgent.getDistanceTo(posGoal);
			  // testa se o goleiro esta fora da segmento de reta
              if (posGoal.getX()<trajetoria.getPointOnLineClosestTo(pos_goleiro_adversario).getX()) 
              {
				//cout<<"OK"<<endl;
				GoleiroPegou2=false;
                //DG=pos_goleiro_adversario.getDistanceTo(posGoal);
              }
              else
              {
			   GoleiroPegou2=true;
			   //cout<<"Nao chutar"<<endl;
               //DG=pos_goleiro_adversario.getDistanceTo(trajetoria.getPointOnLineClosestTo(pos_goleiro_adversario)); // goleiro no segmento de reta
              };
			  
			  

             // pega o estado resultante
	 		    agenteX=WM->PosAgenteX(); 
				agenteY=WM->PosAgenteY();	  		    
      		    angulo=WM->AngAgente();
			    distanciaBola=WM->getRelativeDistance(OBJECT_BALL);               
                
                distanciaJogador=WM->getRelativeDistance(OBJECT_TEAMMATE_11);			  
				
	  		    estadoNewAT2=escolhe_estado2v2T2(agenteX,agenteY,angulo,distanciaBola,distanciaJogador);
			  
			    //ciclo da acao		    
				
				
			    //Distancia Agente-Adversario
				
    			objADVAT2 = WM->getClosestInSetTo( OBJECT_SET_OPPONENTS, WM->getAgentObjectType(), &dMinDistADVAT2);				
	            AdversarioAT2=WM->getRelativeDistance(objADVAT2);
				
				WM->setLastAction_zagueiro( acaoTemp );
				
				if(!RunEpisodesAT2){RunEpisodesAT2=true;}			 
				 
				
	                      
		
		    }
			else{
				  if( WM->isBallKickable() )
				  {
					  SoccerCommand soc;
					  VecPosition posGoal( PITCH_LENGTH/2.0,
                             (-1 + 2*(WM->getCurrentCycle()%2)) * 
                             0.4 * SS->getGoalWidth() );
                        soc = kickTo( posGoal, 0 ); // kick maximal
        				ACT->putCommandInQueue( soc);	
        					  
				  }
				  else{interceptar_bola();}			
				
				}
			
			
		  }

       return soc;
	
}



//**** Funcoes de comunicacao com o QL para salvar ou carregar tabela ////
//SoccerCommand Player::salvar(){SalvarArquivo();}
SoccerCommand Player::carregar(){CarregarArquivo();}
SoccerCommand Player::Limpa_tabela(){apaga_tabela();}
