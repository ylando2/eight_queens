#include <stdio.h>

#define COL_NUM 8

void printBoard(int *sol,int size)
{
	int x,y,i;
	int dim=size>9 ? 2 : 1;
	printf("%*s",dim+1," ");
	for (i=0;i<size*(dim+1)+1;i++) {
		printf("-");
	}
	printf("\n");
	printf("%*s|",dim+1," ");
	for (x=1;x<=size;x++) {
		printf("%*d|",dim,x);
	}
	printf("\n");
	for (i=0;i<(size+1)*(dim+1)+1;i++) {
		printf("-");
	}
	printf("\n");
	for (y=0;y<size;y++) {
		printf("|%*d|",dim,y+1);
		for (x=0;x<size;x++) {
			printf("%*s|",dim,sol[y]==x ? "*" : "-");
		}
		printf("\n");
		for (i=0;i<(size+1)*(dim+1)+1;i++) {
			printf("-");
		}
		printf("\n");
	}
}

//Let the user choose if he want to continue.
//Return 1 to continue and 0 to stop.
int continueOrNot() 
{
  char c[2];
  printf("\npress ';' to continue or any other key to abort ");
  scanf("%1s",&c);
  if (c[0]==';') {
    return 1;
  }
  return 0;
}

void init(int *row,int *diag1,int *diag2)
{
	int i;
	for (i=0;i<COL_NUM;i++) {
		row[i]=0;
	}
	for (i=0;i<COL_NUM*2-1;i++) {
		diag1[i]=0;
		diag2[i]=0;
	}
}

//Solve the 8 queens puzzle.
//It return 1 to continue and 0 to stop.
static int solve(int col,int *row,int *diag1,int *diag2,int *sol,int size)
{
	int i,d1,d2;
	if (col==size) {
		printBoard(sol,size);
		return continueOrNot();
	}
	for (i=0;i<size;i++) {
		d1=i-col+size-1;
		d2=i+col;
		if (!row[i] && !diag1[d1] && !diag2[d2]) {
			row[i]=1;
			diag1[d1]=1;
			diag2[d2]=1;
			sol[col]=i;
			if (!solve(col+1,row,diag1,diag2,sol,size)) {
				return 0;
			}
			row[i]=0;
			diag1[d1]=0;
			diag2[d2]=0;
		}
	}
	return 1;
}

int main(int argc,char **argv) 
{
	int rowTaken[COL_NUM];
	int diagonal1[COL_NUM*2-1];
	int diagonal2[COL_NUM*2-1];
	int solution[COL_NUM];
	init(rowTaken,diagonal1,diagonal2);
	solve(0,rowTaken,diagonal1,diagonal2,solution,COL_NUM);
}