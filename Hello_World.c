//==============================================//
//                                              //
// Name   : Hello World                         //
// Author : Subbaramaiah Chevuru                //
// Mail   : ram.subaram@gmail.com               //
//                                              //
// =============================================//

//----------------------------------------------//
//              REVISION LOG                    //
//----------------------------------------------//
//                                              //
// 2022-11-12   -  Adding the Simple Hello      //
//                 World program.               //
//                                              //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//              Hello World                     //
//----------------------------------------------//

#include <stdio.h>

int main()
{

   char name[25];
   printf("\nEnter the name: \n");
   scanf("%[^\n]s",name);
   //Printing the Hello World Message.
   printf("\n\"Hello ......!\"\n");
   printf("\nWelcome to \"%s\"\n",name);
   return 0;
}

