#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// user functions
int NotePad(){printf(" USER: here we launch notepad\n\n"); return 0;}
int Exit(){ exit(0);}

// system functions
int Dir(){printf(" SYSTEM: here we launch dir\n\n"); return 0;}
int Delete(){printf(" SYSTEM: here we launch Del\n\n"); return 0;}
int ReturnToMain(){return -1;}

int SystemMenu();
int MainMenu();

int (*user_table[])(void) = {NotePad, SystemMenu,Exit};
int (*system_table[])(void) = {Dir, Delete, ReturnToMain};

int SystemMenu()
{
  char password[20];
  int id;
  int ret = 0;
  printf("System Menu\n");
  printf("Enter the Password before continuing!...\n");
  scanf("%s",password);
  if (strcmp(password, "PASSWORD") == 0)
  {
    while (ret != -1)
    {
      printf("Enter a number:\n");
      printf("1: dir\n");
      printf("2: delete everything\n");
      printf("3: back to main menu\n");
      scanf("%d",&id);
      ret = system_table[id-1]();
    }
  }
  else
  {
    printf("Invalid Password!\n");
    return 0;
  }
  return 0;
}

int MainMenu()
{
  int id;
  printf("What would you like to do?\n");
  printf("Enter a number:\n");
  printf("1: run Notepad\n");
  printf("2: go to system menu\n");
  printf("3: quit\n");
  scanf("%d",&id);
  return user_table[id-1]();
}

int main ()
{
  int ret = 0;
  while( ret != -1)
  ret = MainMenu();
  return ret;
}