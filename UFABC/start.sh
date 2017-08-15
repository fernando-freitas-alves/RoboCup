#!/bin/tcsh
# instalar yum
# sudo apt install tcsh


# This script starts the UvA_Trilearn_2003 team. When player numbers are
# supplied before the (optional) host-name and team-name arguments only
# these players are started, otherwise all players are started.
# Usage:   start.sh <player-numbers> <host-name> <team-name>
#
# Example: start.sh                 all players default host and name
# Example: start.sh machine         all players on host 'machine'
# Example: start.sh localhost UvA   all players on localhost and name 'UvA'
# Example: start.sh 127.0.0.1 UvA   all players on 127.0.0.1  and name 'UvA'
# Example: start.sh 1 2 3 4         players 1-4 on default host and name
# Example: start.sh 1 2 remote      players 1-2 on host 'remote'
# Example: start.sh 9 10 remote UvA players 9-10 on host remote and name 'UvA'
# Example: start.sh 0               start coach on default host

set wait  = 0
set host  = "localhost"
set team  = "UFABCRobotics"
set dir   = "src"
set prog  = "${dir}/trilearn_player"
set coach = "${dir}/trilearn_coach"
set pconf = "${dir}/player.conf"
set fconf = "${dir}/formations.conf"

echo "*****************************************************************"
echo "* UFABC Robotics 2017 - University of ABC, São Paulo            *"
echo "* Created by:           Fernando Freitas Alves                  *"
echo "*                       Alberto Hoshina                         *"
echo "*                       Erivan Serafim                          *"
echo "*                       Henrique Werneck                        *"
echo "*****************************************************************"

#first check if the last two supplied arguments are no numbers and represent
#<host-name> or <host-name> <team-name>
if( $#argv > 0 && ($argv[$#argv] !~ [0123456789]* || $argv[$#argv] =~ *.* ) ) then
  @ second_last = $#argv - 1
  if( $#argv > 1 && ($argv[$second_last] !~ [0123456789]* || $argv[$second_last] =~ *.* ) ) then
      set host = $argv[$second_last]
      set team = $argv[$#argv]
  else
      set host = $argv[$#argv]
  endif
endif

#then if first argument is a number, start only the players with the numbers
#as supplied on the prompt, otherwise start all players.
if( $1 =~ [0123456789]* && $1 !~ *.* ) then
  echo "$argv[$#argv]"
    echo "$1"
  foreach arg ($argv)
    if( $arg =~ [123456789]* && $arg !~ *.*) then
      # ${prog} -num ${arg} -host ${host} -team ${team} -f ${fconf} -c ${pconf} &
      ${prog} -log 0 -num ${arg} -host ${host} -team ${team} -f ${fconf} -c ${pconf} &
      sleep $wait
    else if( $arg =~ [0]* ) then
      sleep 2
      ${coach} -host ${host} -team ${team} -f ${fconf} &
    endif
  end
else
  set i = 1
  while ( ${i} <12 )
    # ${prog} -log 101 -number ${i} -host ${host} -team ${team}  -f ${fconf} -c ${pconf} &
    ${prog} -log 200 -number ${i} -host ${host} -team ${team}  -f ${fconf} -c ${pconf} &
    sleep $wait
    @ i++
  end
  sleep 2
  ${coach} -host ${host} -team ${team} -f ${fconf}  &
endif

