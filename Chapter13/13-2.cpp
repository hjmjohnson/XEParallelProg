typedef struct NODE
{
  int cell;
  int number;
  int TempCellsLeft;
}_NODE;

typedef struct SUDOKU
{
  NODE Nodes[NUM_NODES];
}_SUDOKU;