#include <cstdlib>
#include <unistd.h>
#include "Player.h"
#include "Parse.h"





#ifndef WIN32
  #include <sys/poll.h> // needed for 'poll'
#endif



/*!This is the constructor the Player class and calls the constructor of the
   superclass BasicPlayer.
   \param act ActHandler to which the actions can be sent
   \param wm WorldModel which information is used to determine action
   \param ss ServerSettings that contain parameters used by the server
   \param ps PlayerSettings that contain parameters important for the client
   \param strTeamName team name of this player
   \param dVersion version this basicplayer corresponds to
   \param iReconnect integer that defines player number (-1 when new player) */
Player::Player( ActHandler* act, WorldModel *wm, ServerSettings *ss,
      PlayerSettings *ps,
      Formations *fs, char* strTeamName, double dVersion, int iReconnect )

{
  char str[MAX_MSG];

  ACT           = act;
  WM            = wm;
  SS            = ss;
  PS            = ps;
  formations    = fs;
  bContLoop     = true;
  m_iPenaltyNr  = -1;
  WM->setTeamName( strTeamName );
  m_timeLastSay = -5;
  m_objMarkOpp  = OBJECT_ILLEGAL;
  m_actionPrev  = ACT_ILLEGAL;

  // wait longer as role number increases, to make sure players appear at the
  // field in the correct order
#ifdef WIN32
  Sleep( formations->getPlayerInFormation()*500 );
#else
  poll( 0, 0, formations->getPlayerInFormation()*500 );
#endif

  // create initialisation string
  if( iReconnect != -1 )
    sprintf( str, "(reconnect %s %d)", strTeamName, iReconnect );
  else if( formations->getPlayerType() == PT_GOALKEEPER )
    sprintf( str, "(init %s (version %f) (goalie))", strTeamName, dVersion );
  else
    sprintf( str, "(init %s (version %f))", strTeamName, dVersion );
    ACT->sendMessage( str );
  
}

/*! This is the main loop of the agent. This method calls the update methods
    of the world model after it is indicated that new information has arrived.
    After this, the correct main loop of the player type is called, which
    puts the best soccer command in the queue of the ActHandler. */
void Player::mainLoop( )
{
  char str[MAX_MSG];
  Timing timer;  	

  if(  WM->waitForNewInformation() == false ){bContLoop =  false;}

    
    cout<<" "<<endl;
    cout<<" "<<endl;
    cout<< "Iniciando rotina de verificacao de tabela."<<endl;
  
  //carregar(); 
  
  //cout<<""<<endl; cout<<""<<endl; 
  //cout<<"Pronto para Jogar ! :-)"<<endl;
  //cout<<""<<endl;
  
  
	        	 
  
    
  while( bContLoop )  // as long as server alive
  //while(true)
  {  	  
	  
///              AQUI VAI O CODIGO             ///
//
//************************************************
    

    if( WM->updateAll( ) == true )
    {  	
		
	  timer.restartTime();
      SoccerCommand soc;
      
      //{
        switch( formations->getPlayerType( ) )        // determine right loop
        {
          case PT_GOALKEEPER:       soc = goalieMainLoop( );     break;
          case PT_DEFENDER_SWEEPER:
          case PT_DEFENDER_CENTRAL:
          case PT_DEFENDER_WING:    soc = defenderMainLoop( );   break;
          case PT_MIDFIELDER_CENTER: break;
          case PT_MIDFIELDER_WING:   soc = defenderMainLoop( );   break;
          //case PT_ATTACKER:          break;
          //case PT_ATTACKER_WING:     break;
          //case PT_ILLEGAL:
          default: break;
        }
    //}
  }
	
//************************************************	
//--------------------------------------------//
    
    if(  WM->waitForNewInformation() == false )
	{
		bContLoop =  false;
		//cout<<" Conexao Terminadoa !"<<endl;
		//cout<<" Salvando Tabela !"<<endl;
		//salvar();
	}
			  
  }
  cout<<"FIM !"<<endl;
  printf("Shutting down player %d\n", WM->getPlayerNumber() );
  printf("   Number of holes: %d (%f)\n", WM->iNrHoles,
                         ((double)WM->iNrHoles/WM->getCurrentCycle())*100 );
  printf("   Teammates seen: %d (%f)\n", WM->iNrTeammatesSeen,
                         ((double)WM->iNrTeammatesSeen/WM->getCurrentCycle()));
  printf("   Opponents seen: %d (%f)\n", WM->iNrOpponentsSeen,
                         ((double)WM->iNrOpponentsSeen/WM->getCurrentCycle()));

  
}

  



/******** COMANDO DE MOVIMENTO *************
*               SIMPLIFICADO                 // sysop
*               
********************************************/


void Player::move(int x,int y)
{
	SoccerCommand soc;	 
	soc.commandType = CMD_MOVE;
    soc.dX          = x;
    soc.dY          = y;
    ACT->putCommandInQueue(soc);	
}


void Player::dash(int power)
{
	SoccerCommand soc;	 
	soc.commandType = CMD_DASH;
    soc.dPower          = power;    
	ACT->putCommandInQueue(soc);	
}



void Player::turn(int angle)
{
	
	SoccerCommand soc;	 
	soc.commandType = CMD_TURN;
    soc.dAngle          = angle;    
	ACT->putCommandInQueue(soc);
    		
}


void Player::kick()
{
	if(WM->isBallKickable())
	{
	VecPosition   posAgent = WM->getAgentGlobalPosition();
	SoccerCommand soc;	
	soc = kickTo( VecPosition(0,posAgent.getY()*2.0), 2.0 );    
    ACT->putCommandInQueue( soc );
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );	
	}
}


/************ MACRO-ACOES ***************
*PARA O GOLEIRO
*****************************************/


void Player::Parado() //Parado
{
  SoccerCommand soc;    
  ACT->putCommandInQueue( soc = turnBodyToObject( OBJECT_BALL ) );	
}


void Player::interceptar_bola() //Vai na bola
{
	SoccerCommand soc;   
    soc = intercept(false);	
	ACT->putCommandInQueue(soc);    	
}

void Player::Conduzir_bola() //passe para ele mesmo
{
	if(WM->isBallKickable())
	{
	SoccerCommand soc;
	soc =driveBallFoward();
	ACT->putCommandInQueue( soc );
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
	}		
}


/*void Player::Passe() //passe para outro jogador
 //para o goleiro, foi usado o clearball
{
	SoccerCommand soc;
	if(WM->isBallKickable())
	{
	SideT Side;
	AngDeg *angMax=0;
	SideT MySide = WM->getSide();
	if(MySide==SIDE_LEFT){ Side=SIDE_RIGHT;}
	else { Side=SIDE_LEFT;}
	  
	soc=clearBall(CLEAR_BALL_DEFENSIVE, Side,angMax );
	ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
	}		   
		
}*/

void Player::Passe()
{
	SoccerCommand soc;
	if(WM->isBallKickable())
	{   
   		int index = 0;
   		ObjectT teamMate = WM->iterateObjectStart(index, OBJECT_SET_TEAMMATES);
   		VecPosition posTeamMate = WM->getGlobalPosition(teamMate);
   		VecPosition posPass = posTeamMate;
   		VecPosition posAgent = WM->getAgentGlobalPosition();   
   		double rSafety;
   		bool badPass = true;
   		// analisa o passe para cada companheiro 
   		posAgent = WM->getAgentGlobalPosition();
   		while ( teamMate != OBJECT_ILLEGAL )
   		{
      		if  ( teamMate != OBJECT_TEAMMATE_GOALIE ) 
			{
         		posTeamMate = WM->getGlobalPosition(teamMate);
         		rSafety = getSafetyToPass(posAgent, posTeamMate);
         		if ( posTeamMate.isInFrontOf(posAgent) && rSafety > 1.1 ) 
				{
            		posPass = posTeamMate;
            		badPass = false;
            		break;
         		}
      		}
      teamMate = WM->iterateObjectNext(index, OBJECT_SET_TEAMMATES);
   		}
   if (badPass) 
	   {      
		SideT Side;		
		AngDeg *angMax=0;		   
		SideT MySide = WM->getSide();
		if(MySide==SIDE_LEFT){ Side=SIDE_RIGHT;}
		else { Side=SIDE_LEFT;}	  
		//soc = throughPass(teamMate, posPass, angMax);
		soc=clearBall(CLEAR_BALL_DEFENSIVE, Side,angMax );
		ACT->putCommandInQueue(soc);
    	ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
		}
     else
	  {   		    
   		soc = directPass(teamMate,PASS_NORMAL);
   		ACT->putCommandInQueue( soc );
  	  }
   }	
}


void Player::pegar_bola() //pega e teleporta
{
  static const VecPosition posLeftTop( -PITCH_LENGTH/2.0 +
               0.7*PENALTY_AREA_LENGTH, -PENALTY_AREA_WIDTH/4.0 );
  static const VecPosition posRightTop( -PITCH_LENGTH/2.0 +
               0.7*PENALTY_AREA_LENGTH, +PENALTY_AREA_WIDTH/4.0 );
 	
	if( WM->isBallCatchable() )
    {
	SoccerCommand soc;	 
	soc = catchBall();
	ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
		
	// move to position with lesser opponents.
    if( WM->getNrInSetInCircle( OBJECT_SET_OPPONENTS,Circle(posRightTop, 15.0 )) <
            WM->getNrInSetInCircle( OBJECT_SET_OPPONENTS,Circle(posLeftTop,  15.0 )) )
		    soc.makeCommand( CMD_MOVE,posRightTop.getX(),posRightTop.getY(),0.0);
   else
       soc.makeCommand( CMD_MOVE,posLeftTop.getX(), posLeftTop.getY(), 0.0);
       ACT->putCommandInQueue( soc );

    		
	}
}

void Player::Posicao_defesa()
{
  SoccerCommand soc;
  static const VecPosition posLeftTop( -PITCH_LENGTH/2.0 +
               0.6*PENALTY_AREA_LENGTH, -PENALTY_AREA_WIDTH/4.0 );
  static const VecPosition posRightTop( -PITCH_LENGTH/2.0 +
               0.6*PENALTY_AREA_LENGTH, +PENALTY_AREA_WIDTH/4.0 );
  static Line  lineFront = Line::makeLineFromTwoPoints(posLeftTop,posRightTop);
  static Line  lineLeft  = Line::makeLineFromTwoPoints(
                         VecPosition( -50.0, posLeftTop.getY()), posLeftTop );
  static Line  lineRight = Line::makeLineFromTwoPoints(
                         VecPosition( -50.0, posRightTop.getY()),posRightTop );

   
	
  VecPosition posMyGoal = ( WM->getSide() == SIDE_LEFT )
   	? SoccerTypes::getGlobalPositionFlag(OBJECT_GOAL_L, SIDE_LEFT )
   	: SoccerTypes::getGlobalPositionFlag(OBJECT_GOAL_R, SIDE_RIGHT);
  Line lineBall = Line::makeLineFromTwoPoints( WM->getBallPos(),posMyGoal);
  VecPosition posIntersect = lineFront.getIntersection( lineBall );
	
	if (posIntersect.isRightOf( posRightTop ) )
	  posIntersect = lineRight.getIntersection( lineBall );
    else if (posIntersect.isLeftOf( posLeftTop )  )
      posIntersect = lineLeft.getIntersection( lineBall );

    if( posIntersect.getX() < -49.0 )
        		posIntersect.setX( -49.0 );
	
	if( posIntersect.getDistanceTo( WM->getAgentGlobalPosition() ) > 0.5 )
      {
      	soc = moveToPos( posIntersect, PS->getPlayerWhenToTurnAngle() );
      	ACT->putCommandInQueue( soc );
      	ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
      }
     else
     {
     	ACT->putCommandInQueue( soc = turnBodyToObject( OBJECT_BALL ) );
     	ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
     }
	
}


/************ MACRO-ACOES ***************
*PARA O ZAGUEIRO
*****************************************/
void Player::interceptar_bola_zagueiro()
{
	SoccerCommand soc;   
    soc = intercept(false);	
	ACT->putCommandInQueue(soc);	
}

void Player::Marcar()
{
	SoccerCommand soc;
	ObjectT    objInitial;
	double     dMinDist;
	MarkT BALL;
    objInitial = WM->getClosestInSetTo( OBJECT_SET_OPPONENTS, WM->getAgentObjectType(), &dMinDist);				
	soc=mark(objInitial,2.0,MARK_BALL);
	ACT->putCommandInQueue( soc );	
}

void Player::Passe_paraGoleiro()
{
	SoccerCommand soc;
	if(WM->isBallKickable())
	{   
   		int index = 0;
   		ObjectT teamMate = WM->iterateObjectStart(index, OBJECT_SET_TEAMMATES);
   		VecPosition posTeamMate = WM->getGlobalPosition(teamMate);
   		VecPosition posPass = posTeamMate;
   		VecPosition posAgent = WM->getAgentGlobalPosition();
   
   		double rSafety;
   		bool badPass = true;
   		// analisa o passe para cada companheiro 
   		posAgent = WM->getAgentGlobalPosition();
   		while ( teamMate != OBJECT_ILLEGAL )
   		{
      		if  ( teamMate != OBJECT_TEAMMATE_GOALIE ) 
			{
         		posTeamMate = WM->getGlobalPosition(teamMate);
         		rSafety = getSafetyToPass(posAgent, posTeamMate);
         		if ( posTeamMate.isInFrontOf(posAgent) && rSafety > 1.1 ) 
				{
            		posPass = posTeamMate;
            		badPass = false;
            		break;
         		}
      		}
      teamMate = WM->iterateObjectNext(index, OBJECT_SET_TEAMMATES);
   		}
   if (badPass) 
	   {      
		SideT Side;	
        AngDeg *angMax=0;		   
		SideT MySide = WM->getSide();
		if(MySide==SIDE_LEFT){ Side=SIDE_RIGHT;}
		else { Side=SIDE_LEFT;}	  
		soc=clearBall(CLEAR_BALL_DEFENSIVE, Side,angMax );
		ACT->putCommandInQueue(soc);
    	ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
		}
  else
	  {  
   		    
   		soc = directPass(teamMate,PASS_NORMAL);
   		ACT->putCommandInQueue( soc );
		  ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
  	 }
   }
	
}

void Player::Chutar_Longe()
{
	SoccerCommand soc;
	if(WM->isBallKickable())
	{
	SideT Side;
	AngDeg *angMax=0;
	
	SideT MySide = WM->getSide();
	if(MySide==SIDE_LEFT){ Side=SIDE_RIGHT;}
	else { Side=SIDE_LEFT;}
	  
	soc=clearBall(CLEAR_BALL_DEFENSIVE, Side,angMax );
	ACT->putCommandInQueue(soc);
    ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );
	}
	
}

void Player::Segurar_bola()
{
	if(WM->isBallKickable())
	{
	  SoccerCommand soc;
	  soc=holdBall();
	  ACT->putCommandInQueue(soc);
	}
}

void Player::Chuta_Gol()
{
if(WM->isBallKickable())
	{
	  SoccerCommand soc;
	  VecPosition posGoal( PITCH_LENGTH/2.0,
           (-1 + 2*(WM->getCurrentCycle()%2)) * 0.4 * SS->getGoalWidth() );
   	
	  soc = kickTo( posGoal, SS->getBallSpeedMax() );
	  ACT->putCommandInQueue(soc);
	}
}




/******** EXECUTA MOVIMENTO *************
*        PELA ACAO ESCOLHIDA          // sysop
*
********************************************/

void Player::executar_acao(int acao)
{
	switch( acao )
    {
    case 0:{Parado();break;}
		
    case 1: {interceptar_bola(); break;}
    
    case 2: {Chutar_Longe(); break;}
	
	case 3: {Passe(); break;}
	
	case 4:{pegar_bola();break;}
	
	case 5:{Posicao_defesa();break;}

    case 6: {break;}	
    }
}


void Player::executar_acao_Zagueiro(int acao)
{
	switch( acao )
    {
    case 0:{Parado();break;}
		
    case 1: {interceptar_bola_zagueiro(); break;}
        
	case 2: {Conduzir_bola(); break;} //
    
    case 3: {Passe_paraGoleiro(); break;} //PASSE GOLEIRO
	
	case 4:{Chutar_Longe();break;} //CHUTAR LONGE	
	
	case 5: {Marcar(); break;} //MARCAR

    case 6: {break;}	
    }
}










//*** POSICIONA O GOLEIRO   ***   ////
//*
//************************************

void Player:: PosicionaGoleiro(void)
{  
  SoccerCommand soc;
  VecPosition   posAgent = WM->getAgentGlobalPosition();
  AngDeg        angBody  = WM->getAgentGlobalBodyAngle();
  
    if( formations->getFormation() != FT_INITIAL || // not in kickoff formation
        posAgent.getDistanceTo( WM->getStrategicPosition() ) > 2.0 )  
    {
      formations->setFormation( FT_INITIAL );       // go to kick_off formation
      ACT->putCommandInQueue( soc=teleportToPos(WM->getStrategicPosition()) );
	  
    }
    else                                            // else turn to center
    {
      ACT->putCommandInQueue( soc = turnBodyToPoint( VecPosition( 0, 0 ), 0 ));
      ACT->putCommandInQueue( alignNeckWithBody( ) );
    }	
}











//******* fim da programacao *****  //sysop
//*            feito              *
//*********************************  //END.





/*! This is the main decision loop for the goalkeeper. */


SoccerCommand Player::goalieMainLoop( )
{
  
  return Goleiro_QL(); //chama o meu goleiro !
}

/*! This is the main decision loop for a defender. */
SoccerCommand Player::defenderMainLoop( )
{
  return Zagueiro_QL() ;
}

/*! This is the main decision loop for a midfielder. */
SoccerCommand Player::midfielderMainLoop( )
{
  //return deMeer5() ;
}

/*! This is the main decision loop for an agent. */
SoccerCommand Player::attackerMainLoop( )
{
  //return deMeer5() ;
}


















/*! This method returns the position to move in case of a dead ball situation.
    A dead ball situation occurs when the team can have a free kick, kick in,
    etc. The agent will move to the position behind the ball and when he is
    there will move to the ball again. */
VecPosition Player::getDeadBallPosition(  )
{
  VecPosition pos, posBall = WM->getBallPos();
  VecPosition posAgent = WM->getAgentGlobalPosition();
  double dDist;

  // determine point to move to
  if( WM->isKickInUs()  )
    pos = posBall + VecPosition( -1.5, sign( posBall.getY() )*1.5 );
  else if( WM->isCornerKickUs( ) )
    pos = posBall + VecPosition( 1.5, sign( posBall.getY() ) * 1.5 );
  else if( WM->isFreeKickUs() || WM->isOffsideThem() || WM->isGoalKickUs() ||
           WM->isFreeKickFaultThem() || WM->isBackPassThem() )
    pos = posBall + VecPosition( -1.5, 0.0 );
  else
    return VecPosition( UnknownDoubleValue, UnknownDoubleValue );

  AngDeg      angBall = (posBall-posAgent).getDirection() ;
  ObjectT     obj = WM->getClosestInSetTo( OBJECT_SET_PLAYERS,
                                           WM->getAgentObjectType(), &dDist);
  VecPosition posPlayer = WM->getGlobalPosition( obj );

  // change point when heading towards other player or towards the ball
  if( fabs( angBall - (posPlayer-posAgent).getDirection() ) < 20 &&
      dDist < 6 )
    pos -= VecPosition( 5, 0 );
  if( fabs( angBall -  (pos-posAgent).getDirection()) < 20 )
  {
    angBall = VecPosition::normalizeAngle( angBall - 90 );
    pos = posBall + VecPosition( 1, angBall , POLAR );
  }
  return pos;
}

/*!This method listens for input from the keyboard and when it receives this
   input it converts this input to the associated action. See
   showStringCommands for the possible options. This method is used together
   with the SenseHandler class that sends an alarm to indicate that a new
   command can be sent. This conflicts with the method in this method that
   listens for the user input (fgets) on Linux systems (on Solaris this isn't a
   problem). The only known method is to use the flag SA_RESTART with this
   alarm function, but that does not seem to work under Linux. If each time
   the alarm is sent, this gets function unblocks, it will cause major
   performance problems. This function should not be called when a whole match
   is played! */
void Player::handleStdin( )
{
  char buf[MAX_MSG];

  while( bContLoop )
  {
#ifdef WIN32
    cin.getline( buf, MAX_MSG );
#else
    fgets( buf, MAX_MSG, stdin ); // does unblock with signal !!!!!
#endif
   printf( "after fgets: %s\n", buf );
   executeStringCommand( buf );
  }
}

/*!This method prints the possible commands that can be entered by the user.
   The whole name can be entered to perform the corresponding command, but
   normally only the first character is sufficient. This is indicated by
   putting brackets around the part of the command that is not needed.
   \param out output stream to which the possible commands are printed */
void Player::showStringCommands( ostream& out )
{
  out << "Basic commands:"                                << endl <<
         " a(ctions)"                                     << endl <<
         " c(atch) direction"                             << endl <<
         " cs(lientsettings"                              << endl <<
         " d(ash) power [ times ]"                        << endl <<
         " de(bug) nr_cycles"                             << endl <<
         " g(oto) x y"                                    << endl <<
         " h(elp)"                                        << endl <<
         " i(ntercept) x y"                               << endl <<
         " k(ick) power angle"                            << endl <<
         " ka x y endspeed "                              << endl <<
         " m(ove) x y"                                    << endl <<
         " n(eck) angle"                                  << endl <<
         " o(pponents in cone) width dist"                << endl <<
         " p(redict cycles to) x y"                       << endl <<
         " q(uit)"                                        << endl <<
         " s(ay) message"                                 << endl <<
         " ss(erversettings)"                             << endl <<
         " t(urn) angle"                                  << endl <<
         " v(iewmode) narrow | normal | wide low | high"  << endl <<
         " w(orldmodel)"                                  << endl;
}

/*!This method executes the command that is entered by the user. For the
   possible command look at the method showStringCommands.
   \param str string that is entered by the user
   \return true when command could be executed, false otherwise */
bool Player::executeStringCommand( char *str)
{
  SoccerCommand socCommand;
  int           i;
  double        x, y;

  switch( str[0] )
  {
    case 'a':                                 // actions
      WM->showQueuedCommands();
      break;
    case 'c':                                 // catch dir or cs
      if( strlen(str) > 1 && str[1] == 's' )
      {
        PS->show( cout, ":" );
        break;
      }
      socCommand.makeCommand( CMD_CATCH, Parse::parseFirstInt( &str ) );
      break;
    case 'd':                                 // dash
      socCommand.commandType = CMD_DASH;
      socCommand.dPower      = Parse::parseFirstDouble( &str );
      socCommand.iTimes      = Parse::parseFirstInt   ( &str );
      if( socCommand.iTimes == 0 ) socCommand.iTimes = 1;
      break;
    case 'h':                                // help
      showStringCommands( cout );
      return true;
    case 'k':                                // kick or ka (kick advanced)
      socCommand.commandType = CMD_KICK;
      if( str[1] == 'a' ) // advanced kick
      {
        double x = Parse::parseFirstDouble( &str );
        double y = Parse::parseFirstDouble( &str );
        double e = Parse::parseFirstDouble( &str );
        socCommand = kickTo( VecPosition( x, y), e );
      }
      else
      {
        socCommand.dPower = Parse::parseFirstDouble( &str );
        socCommand.dAngle = Parse::parseFirstDouble( &str );
      }
      break;
    case 'm':                               // move
      socCommand.commandType = CMD_MOVE;
      socCommand.dX          = Parse::parseFirstDouble( &str );
      socCommand.dY          = Parse::parseFirstDouble( &str );
      socCommand.dAngle      = Parse::parseFirstDouble( &str );
      break;
    case 'n':                              // turn_neck
      socCommand.commandType = CMD_TURNNECK;
      socCommand.dAngle      = Parse::parseFirstDouble( &str );
      break;
    case 'o':                              // count nr opp in cone
      x = Parse::parseFirstDouble( &str );
      y = Parse::parseFirstDouble( &str );
      i = WM->getNrInSetInCone( OBJECT_SET_OPPONENTS, x, 
                                WM->getAgentGlobalPosition(),
                                WM->getAgentGlobalPosition() + 
                                VecPosition( y,
                                             WM->getAgentGlobalNeckAngle(), 
                                             POLAR ) );
      printf( "%d opponents\n", i );
      return true;
    case 'p':                              // predict cycles to point
      x = Parse::parseFirstDouble( &str );
      y = Parse::parseFirstDouble( &str );
      i = WM->predictNrCyclesToPoint( WM->getAgentObjectType(),
                                      VecPosition( x, y ) );
      printf( "%d cycles\n", i );
      return true;
    case 'q':                             // quit
      bContLoop = false;
      return true;
    case 's':                             // ss (serversettings) or say
      if( strlen(str) > 1 && str[1] == 's' )
      {
        SS->show( cout, ":" );
        break;
      }
      socCommand.commandType = CMD_SAY;
      Parse::gotoFirstOccurenceOf( ' ', &str );
      Parse::gotoFirstNonSpace( &str );
      strcpy( socCommand.str, str);
      break;
    case 't':                             // turn
      socCommand.commandType = CMD_TURN;
      socCommand.dAngle      = Parse::parseFirstDouble( &str );
      break;
    case 'v':                             // change_view
      socCommand.commandType = CMD_CHANGEVIEW;
      Parse::gotoFirstOccurenceOf(' ', &str );
      Parse::gotoFirstNonSpace( &str );
      socCommand.va          = SoccerTypes::getViewAngleFromStr( str );
      Parse::gotoFirstOccurenceOf(' ', &str );
      Parse::gotoFirstNonSpace( &str );
      socCommand.vq          = SoccerTypes::getViewQualityFromStr( str );
      break;
    case 'w':                            // worldmodel
      WM->show();
      return true;
    default:                             // default: send entered string
      ACT->sendMessage( str );
      return true;
  }
  if( socCommand.commandType != CMD_ILLEGAL ) // when socCommand is set
    ACT->putCommandInQueue( socCommand );     // send it.

  return true;
}

/*!This method can be called in a separate thread (see pthread_create) since
   it returns a void pointer. It is assumed that this function receives a
   BasicPlayer class as argument. The only thing this function does
   is starting the method handleStdin() from the corresponding BasicPlayer
   class that listens to user input from the keyboard. This function is
   necessary since a method from a class cannot be an argument of
   pthread_create.
   \param v void pointer to a BasicPlayer class.
   \return should never return since function handleStdin has infinite loop*/
#ifdef WIN32
DWORD WINAPI stdin_callback( LPVOID v )
#else
void* stdin_callback( void * v )
#endif

{
  Log.log( 1, "Starting to listen for user input" );
  Player* p = (Player*)v;
  p->handleStdin();
  return NULL;
}

/********************** SAY **************************************************/

/*!This method determines whether a player should say something.
   \return bool indicating whether the agent should say a message */
bool Player::shallISaySomething( SoccerCommand socPri )
{
  bool        bReturn;

  bReturn  = ((WM->getCurrentTime() - m_timeLastSay) >= SS->getHearDecay());
  bReturn  &= amIAgentToSaySomething( socPri );
  bReturn  &= (WM->getCurrentCycle() > 0 );

  return bReturn;
}

/*! This method returns a boolean indicating whether I should communicate my
    world model to the other agents.
    \return boolean indicating whether I should communicate my world model. */
bool Player::amIAgentToSaySomething( SoccerCommand socPri )
{
  double  dDist;
  ObjectT obj;

  // get the closest teammate to the ball, if we are not him, we do not
  // communicate since he will
  obj = WM->getClosestInSetTo( OBJECT_SET_TEAMMATES,OBJECT_BALL,&dDist);
  if( dDist < SS->getVisibleDistance() &&
      obj != WM->getAgentObjectType() )
    return false;

  // in the defense, player 6 keeps track of the opponent attacker
  if( WM->getBallPos().getX() < - PENALTY_X + 4.0 &&
      WM->getConfidence( OBJECT_BALL ) > 0.96 &&
      WM->getPlayerNumber() == 6 &&
      WM->getCurrentCycle() % 3 == 0 ) // once very 3 cycles is enough
  {
    Log.log( 600, "player 6 is going to communicate attacker info" );
    return true;
  }

  VecPosition posBallPred;
  WM->predictBallInfoAfterCommand( socPri, &posBallPred );
  VecPosition posAgentPred = WM->predictAgentPosAfterCommand( socPri );
  // in all other cases inform teammates of ball when you have good information
  if( ( WM->getTimeChangeInformation(OBJECT_BALL) == WM->getCurrentTime() &&
          WM->getRelativeDistance( OBJECT_BALL ) < 20.0 &&
          WM->getTimeLastSeen( OBJECT_BALL ) == WM->getCurrentTime() )
        ||
      (
       WM->getRelativeDistance( OBJECT_BALL ) < SS->getVisibleDistance() &&
       WM->getTimeLastSeen( OBJECT_BALL ) == WM->getCurrentTime()  
       )
      ||
      ( // pass ball
       WM->getRelativeDistance( OBJECT_BALL ) < SS->getMaximalKickDist() &&
       posBallPred.getDistanceTo( posAgentPred ) > SS->getMaximalKickDist() 
       )
      )
    return true;

  return false;
}

/*! This method encodes the opponent attacker status in a visual message.
    \return string in which the opponent attacker position is encoded.*/
void Player::sayOppAttackerStatus( char* strMsg )
{
  char    strTmp[MAX_SAY_MSG];

  // fill the first byte with some encoding to indicate the current cycle.
  // The second byte   is the last digit of the cycle added to 'a'.
  sprintf( strMsg, "%c", 'a' + WM->getCurrentCycle()%10   );

  // fill the second byte with information about the offside line.
  // Enter either a value between a-z or A-Z indicating. This gives 52 possible
  // values which correspond with meters on the field. So B means the offside
  // line lies at 27.0.
  int iOffside = (int)WM->getOffsideX();
  if( iOffside < 26 ) // 0..25
    sprintf( strTmp, "%c", 'a' + iOffside );
  else               // 26...
    sprintf( strTmp, "%c", 'A' + max(iOffside - 26, 25) );
  strcat( strMsg, strTmp );

  // find the closest opponent attacker to the penalty spot.
  double dDist ;
  ObjectT objOpp = WM->getClosestInSetTo( OBJECT_SET_OPPONENTS,
         VecPosition(- PITCH_LENGTH/2.0 + 11.0, 0 ), &dDist  ) ;

  if( objOpp == OBJECT_ILLEGAL || dDist >= 20.0 )
  {
    strncpy( strMsg, "", 0 );
    return;
  }

  VecPosition posOpp = WM->getGlobalPosition( objOpp );
  if( fabs( posOpp.getY() ) > 10 )
  {
    strncpy( strMsg, "", 0 );
    return;
  }

  // encode the position of this attacker in the visual message. The
  // player_number is the third byte, then comes the x position in 3 digits (it
  // is assumed this value is always negative), a space and finally the y
  // position in 2 digits. An example of opponent nr. 9 at position
  // (-40.3223,-3.332) is "j403 -33)
  sprintf( strTmp, "%c%d %d", 'a' + SoccerTypes::getIndex( objOpp ) ,
                              (int)(fabs(posOpp.getX())*10),
                              (int)(posOpp.getY()*10));
  strcat( strMsg, strTmp );

  return ;
}

/*! This method creates a string to communicate the ball status. When
    the player just kicks the ball, it is the new velocity of the
    ball, otherwise it is the current velocity.
    \param strMsg will be filled */
void Player::sayBallStatus( char * strMsg  )
{
  VecPosition posBall = WM->getGlobalPosition( OBJECT_BALL );
  VecPosition velBall = WM->getGlobalVelocity( OBJECT_BALL );
  int iDiff = 0;
  SoccerCommand soc = ACT->getPrimaryCommand();

  if( WM->getRelativeDistance( OBJECT_BALL ) < SS->getMaximalKickDist() )
  {
    // if kick and a pass
    if( soc.commandType == CMD_KICK )
    {
      WM->predictBallInfoAfterCommand( soc, &posBall, &velBall );
      VecPosition posAgent = WM->predictAgentPos( 1, 0 );
      if( posBall.getDistanceTo( posAgent ) > SS->getMaximalKickDist() + 0.2 )
        iDiff = 1;
    }

    if( iDiff == 0 )
    {
      posBall = WM->getGlobalPosition( OBJECT_BALL );
      velBall.setVecPosition( 0, 0 );
    }
  }
  Log.log( 600, "create comm. ball after: (%1.2f,%1.2f)(%1.2f,%1.2f) diff %d",
     posBall.getX(), posBall.getY(), velBall.getX(), velBall.getY(), iDiff);
  makeBallInfo( posBall, velBall, iDiff, strMsg );
}

/*! This method is used to create the communicate message for the
    status of the ball, that is its position and velocity is encoded.

    \param VecPosition posBall ball position
    \param VecPosition velBall ball velocity
    \param iDiff time difference corresponding to given ball information
    \strMsg string message in which the ball information is encoded. */
void Player::makeBallInfo( VecPosition posBall, VecPosition velBall, int iDiff,
                            char * strMsg  )
{
  char    strTmp[MAX_SAY_MSG];

  // fill the first byte with some encoding to indicate the next cycle.
  // The second byte is the last digit of the cycle added to 'a'.
  sprintf( strMsg, "%c", 'a' + (WM->getCurrentCycle()+iDiff)%10   );

  // fill the second byte with information about the offside line.
  // Enter either a value between a-z or A-Z indicating. This gives 52 possible
  // values which correspond with meters on the field. So B means the offside
  // line lies at 27.0.
  int iOffside = (int)( WM->getOffsideX( false ) - 1.0 );
  if( iOffside < 26 ) // 0..25
    sprintf( strTmp, "%c", 'a' + max( 0, iOffside) );
  else               // 26...
    sprintf( strTmp, "%c", 'A' + min(iOffside - 26, 25) );
  strcat( strMsg, strTmp );

  // First add al values to a positive interval, since then we don't need
  // another byte for the minus sign. then take one digit at a time
  double x = max(0,min( rint( posBall.getX() + 48.0), 99.0));
  sprintf( strTmp, "%c%c%c%c%c%c%c%c",
     '0' + ((int)( x                          ) % 100 ) / 10 ,
     '0' + ((int)( x                          ) % 100 ) % 10 ,
     '0' + ((int)( rint(posBall.getY() + 34.0)) % 100 ) / 10 ,
     '0' + ((int)( rint(posBall.getY() + 34.0)) % 100 ) % 10 ,
     '0' + ((int)(( velBall.getX() + 2.7) * 10 )) / 10 ,
     '0' + ((int)(( velBall.getX() + 2.7) * 10 )) % 10 ,
     '0' + ((int)(( velBall.getY() + 2.7) * 10 )) / 10 ,
     '0' + ((int)(( velBall.getY() + 2.7) * 10 )) % 10 );
  strcat( strMsg, strTmp );
  Log.log( 6560, "say (%d) %s\n", WM->getPlayerNumber() , strMsg );

  return ;
}

/*! This method is called when a penalty kick has to be taken (for both the 
  goalkeeper as the player who has to take the penalty. */
void Player::performPenalty( )
{
  VecPosition   pos;
  int           iSide = ( WM->getSide() == WM->getSidePenalty() ) ? -1 : 1;
  VecPosition   posPenalty( iSide*(52.5 - SS->getPenDistX()), 0.0 );
  VecPosition   posAgent = WM->getAgentGlobalPosition();
  AngDeg        angBody  = WM->getAgentGlobalBodyAngle();

  SoccerCommand soc(CMD_ILLEGAL);
  static PlayModeT pmPrev = PM_ILLEGAL;

  // raise number of penalties by one when a penalty is taken
  if(
    ( WM->getSide() == SIDE_LEFT && 
      pmPrev != PM_PENALTY_SETUP_LEFT && 
      WM->getPlayMode() == PM_PENALTY_SETUP_LEFT )
    ||
    ( WM->getSide() == SIDE_RIGHT && 
      pmPrev != PM_PENALTY_SETUP_RIGHT && 
      WM->getPlayMode() == PM_PENALTY_SETUP_RIGHT ) )
   m_iPenaltyNr++;

  // start with player 11 and go downwards with each new penalty
  // if we take penalty 
  if( WM->isPenaltyUs() && WM->getPlayerNumber() == (11 - (m_iPenaltyNr % 11)))
  {
     if( WM->getPlayMode() == PM_PENALTY_SETUP_LEFT ||
         WM->getPlayMode() == PM_PENALTY_SETUP_RIGHT )
     {
       pos = posPenalty - VecPosition( iSide*2.0, 0 );
       if( fabs( posAgent.getX() ) > fabs( pos.getX() ) )
         pos = posPenalty;
       if( pos.getDistanceTo( posAgent ) < 0.6 )
       {
         pos = posPenalty;
         if(  fabs( VecPosition::normalizeAngle( 
                   (pos-posAgent).getDirection() - angBody ) ) > 20 )
           soc = turnBodyToPoint( pos );
       }
       //  pos = WM->getAgentGlobalPosition();
     }
     else if( ( WM->getPlayMode() == PM_PENALTY_READY_LEFT ||
                WM->getPlayMode() == PM_PENALTY_READY_RIGHT ||
                WM->getPlayMode() == PM_PENALTY_TAKEN_LEFT ||
                WM->getPlayMode() == PM_PENALTY_TAKEN_RIGHT 
                )
              && WM->isBallKickable() )
     {
       soc = kickTo(VecPosition(iSide*52.5,((drand48()<0.5)?1:-1)*5.9 ),2.7);
     }
     else
       pos = posPenalty;
  }
  else if( formations->getPlayerType() == PT_GOALKEEPER )
  {
    if( WM->getAgentViewAngle() != VA_NARROW )
      ACT->putCommandInQueue( 
		 SoccerCommand( CMD_CHANGEVIEW, VA_NARROW, VQ_HIGH ));

    // is penalty them, stop it, otherwise go to outside field
    pos = posPenalty;
    if( WM->isPenaltyThem( ) )
    {
      pos = VecPosition( iSide*(52.5 - 2.0), 0.0 );
      if( SS->getPenAllowMultKicks() == false )
      {
	if( WM->getPlayMode() == PM_PENALTY_TAKEN_LEFT ||
	    WM->getPlayMode() == PM_PENALTY_TAKEN_RIGHT )
	{
	  if( WM->isBallCatchable( ) )
	    soc = catchBall();
	  else
	    soc = intercept( true );
	}
      }
      else if( pos.getDistanceTo( posAgent ) < 1.0 )
        soc = turnBodyToPoint( VecPosition( 0,0) ) ;
      else
        soc = moveToPos( pos, 25 );
    }
    else
      pos.setVecPosition( iSide * ( PITCH_LENGTH/2.0 + 2 ) , 25 );
  }
  else
  {
    pos = VecPosition( 5.0,
                       VecPosition::normalizeAngle( 
                         iSide*(50 + 20*WM->getPlayerNumber())),
                       POLAR );
  }


  if( soc.isIllegal() && 
      WM->getAgentGlobalPosition().getDistanceTo( pos ) < 0.8 )
  {
    soc = turnBodyToPoint( posPenalty  );    
  }
  else if( soc.isIllegal() )
  {
    soc = moveToPos( pos, 10);
  }
  if( WM->getAgentStamina().getStamina() < 
      SS->getRecoverDecThr()*SS->getStaminaMax() + 500 &&
    soc.commandType == CMD_DASH)
    soc.dPower = 0;
  
  ACT->putCommandInQueue( soc );
  ACT->putCommandInQueue( turnNeckToObject( OBJECT_BALL, soc ) );

  pmPrev = WM->getPlayMode();
}
