/*
 ****************************************************************************
 *
 *                   "DHRYSTONE" Benchmark Program
 *                   -----------------------------
 *                                                                            
 *  Version:    C, Version 2.1
 *                                                                            
 *  File:       dhry_1.c (part 2 of 3)
 *
 *  Date:       May 25, 1988
 *
 *  Author:     Reinhold P. Weicker
 *
 ****************************************************************************
 */

#include "dhry.h"
#include <omp.h>
#include "ittnotify.h"
/* Global Variables: */

GLOB_STRUCT *Ptr_Glob_Arr;


extern char     *malloc ();
Enumeration     Func_1 ();
  /* forward declaration necessary since Enumeration may not simply be int */

#ifndef REG
        Boolean Reg = false;
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
        Boolean Reg = true;
#endif

/* variables for time measurement: */

#ifdef TIMES
struct tms      time_info;
extern  int     times ();
                /* see library function "times" */
#define Too_Small_Time 120
                /* Measurements should last at least about 2 seconds */
#endif
#ifdef TIME
extern long     time();
                /* see library function "time"  */
#define Too_Small_Time 2
                /* Measurements should last at least 2 seconds */
#endif

long            Begin_Time,
                End_Time,
                User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

/* end of variables for time measurement */


main (int argc, char * argv[])
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{
        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs;
		int				id;
		int				num_threads;
  /* Initializations */
	__itt_domain* pD = __itt_domain_create( "My Domain" );
	pD->flags = 1; /* enable domain */
	num_threads = omp_get_max_threads();
if(argc  == 3)
	num_threads = atoi(argv[2]);
	omp_set_num_threads(num_threads);

  	Ptr_Glob_Arr = malloc(sizeof(GLOB_STRUCT) * num_threads);

  printf ("\n");
  printf ("Dhrystone Benchmark, Version 2.1 (Language: C)\n");
  printf ("\n");
  if (Reg)
  {
    printf ("Program compiled with 'register' attribute\n");
    printf ("\n");
  }
  else
  {
    printf ("Program compiled without 'register' attribute\n");
    printf ("\n");
  }
  if(argc  < 2)
  //if(argc  != 2)
  {
	printf ("Please give the number of runs through the benchmark: ");
	{
		int n;
		scanf ("%d", &n);
		Number_Of_Runs = n;
	}
	printf ("\n");
  }
  else
  {
	  Number_Of_Runs = atoi(argv[1]);
  }

  printf ("Execution starts, %d runs through Dhrystone\n", Number_Of_Runs);
  
  /***************/
  /* Start timer */
  /***************/
 
#ifdef TIMES
  times (&time_info);
  Begin_Time = (long) time_info.tms_utime;
#endif
#ifdef TIME
  Begin_Time = time ( (long *) 0);
#endif
  __itt_frame_begin_v3(pD, NULL);


#pragma omp parallel private (id)
  {
  // set pointer to current globals
  id = omp_get_thread_num();

  Ptr_Glob_Arr[id].Next_Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));
  Ptr_Glob_Arr[id].Ptr_Glob = (Rec_Pointer) malloc (sizeof (Rec_Type));

  Ptr_Glob_Arr[id].Ptr_Glob->Ptr_Comp                    = Ptr_Glob_Arr[id].Next_Ptr_Glob;
  Ptr_Glob_Arr[id].Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Str_Comp, 
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Ptr_Glob_Arr[id].Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

#pragma omp barrier

#pragma omp for  private(Run_Index) firstprivate(Str_1_Loc,Number_Of_Runs) lastprivate (Int_1_Loc, Int_2_Loc,Int_3_Loc,Ch_Index,Enum_Loc,Str_1_Loc, Str_2_Loc)
  for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
  {
#if 1

    Proc_5(id);
    Proc_4(id);
      /* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
    Int_1_Loc = 2;
    Int_2_Loc = 3;
    strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
    Enum_Loc = Ident_2;
    Ptr_Glob_Arr[id].Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc,id);
      /* Bool_Glob == 1 */
    while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
    {
      Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
        /* Int_3_Loc == 7 */
      Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
        /* Int_3_Loc == 7 */
      Int_1_Loc += 1;
    } /* while */
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Proc_8 (Ptr_Glob_Arr[id].Arr_1_Glob, Ptr_Glob_Arr[id].Arr_2_Glob, Int_1_Loc, Int_3_Loc,id);
      /* Int_Glob == 5 */
    Proc_1 (Ptr_Glob_Arr[id].Ptr_Glob,id);
    for (Ch_Index = 'A'; Ch_Index <= Ptr_Glob_Arr[id].Ch_2_Glob; ++Ch_Index)
                             /* loop body executed twice */
    {
      if (Enum_Loc == Func_1 (Ch_Index, 'C',id))
          /* then, not executed */
        {
        Proc_6 (Ident_1, &Enum_Loc,id);
        strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
        Int_2_Loc = Run_Index;
        Ptr_Glob_Arr[id].Int_Glob = Run_Index;
        }
    }
      /* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
    Int_2_Loc = Int_2_Loc * Int_1_Loc;
    Int_1_Loc = Int_2_Loc / Int_3_Loc;
    Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
      /* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
    Proc_2 (&Int_1_Loc,id);
      /* Int_1_Loc == 5 */
#endif
  } /* loop "for Run_Index" */
  }
  /**************/
  /* Stop timer */
  /**************/

//  use id 0
  id = 0;
  __itt_frame_end_v3(pD, NULL);
#ifdef TIMES
  times (&time_info);
  End_Time = (long) time_info.tms_utime;
#endif
#ifdef TIME
  End_Time = time ( (long *) 0);
#endif
  printf ("Execution ends\n");
  printf ("\n");
  printf ("Final values of the variables used in the benchmark:\n");
  printf ("\n");
  printf ("Int_Glob:            %d\n", Ptr_Glob_Arr[id].Int_Glob);
  printf ("        should be:   %d\n", 5);
  printf ("Bool_Glob:           %d\n", Ptr_Glob_Arr[id].Bool_Glob);
  printf ("        should be:   %d\n", 1);
  printf ("Ch_1_Glob:           %c\n", Ptr_Glob_Arr[id].Ch_1_Glob);
  printf ("        should be:   %c\n", 'A');
  printf ("Ch_2_Glob:           %c\n", Ptr_Glob_Arr[id].Ch_2_Glob);
  printf ("        should be:   %c\n", 'B');
  printf ("Arr_1_Glob[8]:       %d\n", Ptr_Glob_Arr[id].Arr_1_Glob[8]);
  printf ("        should be:   %d\n", 7);
  printf ("Arr_2_Glob[8][7]:    %d\n", Ptr_Glob_Arr[id].Arr_2_Glob[8][7]);
  printf ("        should be:   Number_Of_Runs + 10\n");
  printf ("Ptr_Glob->\n");
  printf ("  Ptr_Comp:          %d\n", (int) Ptr_Glob_Arr[id].Ptr_Glob->Ptr_Comp);
  printf ("        should be:   (implementation-dependent)\n");
  printf ("  Discr:             %d\n", Ptr_Glob_Arr[id].Ptr_Glob->Discr);
  printf ("        should be:   %d\n", 0);
  printf ("  Enum_Comp:         %d\n", Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Enum_Comp);
  printf ("        should be:   %d\n", 2);
  printf ("  Int_Comp:          %d\n", Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Int_Comp);
  printf ("        should be:   %d\n", 17);
  printf ("  Str_Comp:          %s\n", Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Str_Comp);
  printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  printf ("Next_Ptr_Glob->\n");
  printf ("  Ptr_Comp:          %d\n", (int) Ptr_Glob_Arr[id].Next_Ptr_Glob->Ptr_Comp);
  printf ("        should be:   (implementation-dependent), same as above\n");
  printf ("  Discr:             %d\n", Ptr_Glob_Arr[id].Next_Ptr_Glob->Discr);
  printf ("        should be:   %d\n", 0);
  printf ("  Enum_Comp:         %d\n", Ptr_Glob_Arr[id].Next_Ptr_Glob->variant.var_1.Enum_Comp);
  printf ("        should be:   %d\n", 1);
  printf ("  Int_Comp:          %d\n", Ptr_Glob_Arr[id].Next_Ptr_Glob->variant.var_1.Int_Comp);
  printf ("        should be:   %d\n", 18);
  printf ("  Str_Comp:          %s\n",
                                Ptr_Glob_Arr[id].Next_Ptr_Glob->variant.var_1.Str_Comp);
  printf ("        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  printf ("Int_1_Loc:           %d\n", Int_1_Loc);
  printf ("        should be:   %d\n", 5);
  printf ("Int_2_Loc:           %d\n", Int_2_Loc);
  printf ("        should be:   %d\n", 13);
  printf ("Int_3_Loc:           %d\n", Int_3_Loc);
  printf ("        should be:   %d\n", 7);
  printf ("Enum_Loc:            %d\n", Enum_Loc);
  printf ("        should be:   %d\n", 1);
  printf ("Str_1_Loc:           %s\n", Str_1_Loc);
  printf ("        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  printf ("Str_2_Loc:           %s\n", Str_2_Loc);
  printf ("        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  printf ("\n");

  User_Time = End_Time - Begin_Time;

  if (User_Time < Too_Small_Time)
  {
    printf ("Measured time too small to obtain meaningful results\n");
    printf ("Please increase number of runs\n");
    printf ("\n");
  }
  else
  {
#ifdef TIME
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / (float) Number_Of_Runs;
    Dhrystones_Per_Second = (float) Number_Of_Runs / (float) User_Time;
#else
    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / ((float) HZ * ((float) Number_Of_Runs));
    Dhrystones_Per_Second = ((float) HZ * (float) Number_Of_Runs)
                        / (float) User_Time;
#endif
    printf ("Microseconds for one run through Dhrystone: ");
    printf ("%6.3f \n", Microseconds);
    printf ("Dhrystones per Second:                      ");
    printf ("%6.1f \n", Dhrystones_Per_Second);
    printf ("\n");
  }
}


Proc_1 (Ptr_Val_Par,id)
/******************/

REG Rec_Pointer Ptr_Val_Par;
int id;
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */
  
  structassign (*Ptr_Val_Par->Ptr_Comp, *(Ptr_Glob_Arr[id].Ptr_Glob)); 
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp 
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp,id);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
           &Next_Record->variant.var_1.Enum_Comp,id);
    Next_Record->Ptr_Comp = Ptr_Glob_Arr[id].Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


Proc_2 (Int_Par_Ref,id)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */

One_Fifty   *Int_Par_Ref;
int id;
{
  One_Fifty  Int_Loc;  
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ptr_Glob_Arr[id].Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Ptr_Glob_Arr[id].Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


Proc_3 (Ptr_Ref_Par,id)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */

Rec_Pointer *Ptr_Ref_Par;
int id;

{
  if (Ptr_Glob_Arr[id].Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob_Arr[id].Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Ptr_Glob_Arr[id].Int_Glob, &Ptr_Glob_Arr[id].Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


Proc_4 (id) /* without parameters */
/*******/
    /* executed once */
int id;
{
  Boolean Bool_Loc;

  Bool_Loc = Ptr_Glob_Arr[id].Ch_1_Glob == 'A';
  Ptr_Glob_Arr[id].Bool_Glob = Bool_Loc | Ptr_Glob_Arr[id].Bool_Glob;
  Ptr_Glob_Arr[id].Ch_2_Glob = 'B';
} /* Proc_4 */


Proc_5 (id) /* without parameters */
/*******/
    /* executed once */
int id;
{
  Ptr_Glob_Arr[id].Ch_1_Glob = 'A';
  Ptr_Glob_Arr[id].Bool_Glob = false;
} /* Proc_5 */


        /* Procedure for the assignment of structures,          */
        /* if the C compiler doesn't support this feature       */
#ifdef  NOSTRUCTASSIGN
memcpy (d, s, l)
register char   *d;
register char   *s;
register int    l;
{
        while (l--) *d++ = *s++;
}
#endif


