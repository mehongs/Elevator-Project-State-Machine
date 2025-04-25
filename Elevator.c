/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.9 --- 4/24/2025 22:3:12 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
char input = 1;
char obst = 0;
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long periodlevel = 1000;
const unsigned long periodinput = 500;
const unsigned long periodobstruction = 500;

const unsigned long tasksPeriodGCD = 500;

int TickFct_level(int state);
int TickFct_input(int state);
int TickFct_obstruction(int state);

unsigned char processingRdyTasks = 0;
void TimerISR() {
   unsigned char i;
   if (processingRdyTasks) {
      printf("Period too short to complete tasks\n");
   }
   processingRdyTasks = 1;
   for (i = 0; i < tasksNum; ++i) { // Heart of scheduler code
      if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
         tasks[i].state = tasks[i].TickFct(tasks[i].state);
         tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += tasksPeriodGCD;
   }
   processingRdyTasks = 0;
}
int main() {
   // Priority assigned to lower position tasks in array
   unsigned char i=0;
   tasks[i].state = -1;
   tasks[i].period = periodlevel;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_level;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodinput;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_input;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodobstruction;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_obstruction;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_lvl1, SM1_printGuardlvl1, SM1_lvl2, SM1_printGuardlvl2, SM1_lvl3, SM1_printGuardlvl3 } SM1_State;
int TickFct_level(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM1_lvl1;
         break;
      case SM1_lvl1:
         if (1) {
            state = SM1_printGuardlvl1;
         }
         break;
      case SM1_printGuardlvl1:
         if (input == 1) {
            state = SM1_printGuardlvl1;
         }
         else if (input == 2) {
            state = SM1_lvl2;
         }
         else if (input == 3) {
            state = SM1_lvl3;
         }
         break;
      case SM1_lvl2:
         if (1) {
            state = SM1_printGuardlvl2;
         }
         break;
      case SM1_printGuardlvl2:
         if (input == 2) {
            state = SM1_printGuardlvl2;
         }
         else if (input == 3) {
            state = SM1_lvl3;
         }
         else if (input == 1) {
            state = SM1_lvl1;
         }
         break;
      case SM1_lvl3:
         if (1) {
            state = SM1_printGuardlvl3;
         }
         break;
      case SM1_printGuardlvl3:
         if (input == 3) {
            state = SM1_printGuardlvl3;
         }
         else if (input == 2) {
            state = SM1_lvl2;
         }
         else if (input == 1) {
            state = SM1_lvl1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_lvl1:
         B0 = 1;
         B1 = 0;
         printf("on level 1\n");
         break;
      case SM1_printGuardlvl1:
         B0 = 1;
         B1 = 0;
         break;
      case SM1_lvl2:
         B0 = 0;
         B1 = 1;
         printf("on level 2\n");
         
         break;
      case SM1_printGuardlvl2:
         B0 = 0;
         B1 = 1;
         break;
      case SM1_lvl3:
         B0 = 1;
         B1 = 1;
         printf("on level 3\n");
         
         break;
      case SM1_printGuardlvl3:
         B0 = 1;
         B1 = 1;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_input_1, SM2_input_2, SM2_input_3, SM2_init } SM2_State;
int TickFct_input(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM2_init;
         break;
      case SM2_input_1:
         if ((!A0 && A1)  && (!obst)) {
            state = SM2_input_2;
         }
         else if ((A0 && A1) && (!obst)) {
            state = SM2_input_3;
         }
         else if (1) {
            state = SM2_input_1;
         }
         break;
      case SM2_input_2:
         if ((A0 && !A1)  && (!obst)) {
            state = SM2_input_1;
         }
         else if ((A0 && A1)  && (!obst)) {
            state = SM2_input_3;
         }
         else if (1) {
            state = SM2_input_2;
         }
         break;
      case SM2_input_3:
         if ((!A0 && A1) && (!obst)) {
            state = SM2_input_2;
         }
         else if ((A0 && !A1)  && (!obst)) {
            state = SM2_input_1;
         }
         else if (1) {
            state = SM2_input_3;
         }
         break;
      case SM2_init:
         if (1) {
            state = SM2_input_1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_input_1:
         input = 1;
         
         break;
      case SM2_input_2:
         input = 2;
         break;
      case SM2_input_3:
         input = 3;
         break;
      case SM2_init:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}


enum SM3_States { SM3_init, SM3_obstruction, SM3_printGuard, SM3_no_obstruction } SM3_State;
int TickFct_obstruction(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM3_init;
         break;
      case SM3_init:
         if (A7) {
            state = SM3_obstruction;
         }
         break;
      case SM3_obstruction:
         if (1) {
            state = SM3_printGuard;
         }
         break;
      case SM3_printGuard:
         if (!A7) {
            state = SM3_no_obstruction;
         }
         break;
      case SM3_no_obstruction:
         if (1) {
            state = SM3_init;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM3_init:
         break;
      case SM3_obstruction:
         printf("obstruction detected, will not move\n");
         obst = 1;
         break;
      case SM3_printGuard:
         break;
      case SM3_no_obstruction:
         printf("obstruction cleared, will move floor\n");
         obst = 0;
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM3_State = state;
   return state;
}

