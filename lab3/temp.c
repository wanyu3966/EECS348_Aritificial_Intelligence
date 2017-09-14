int counter;
int p1,p2;
//backtracking helper function
bool backtracking(int **sudoku){
	counter++;
	int num=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			// printf("%d%d%d\n",i,j,sudoku[i][j] );
			if(sudoku[i][j]==0){
				for(num=1;num<=9;num++){
					if(can_yx_be_z(sudoku,i,j,num)){
						sudoku[i][j]=num;
					if(backtracking(sudoku))
						return true;
					else
						sudoku[i][j]=0;
				}
			}
				return false;
			}
		}
	}
	return true;
}

int sudoku_backtracking(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	counter=0;
	bool res=backtracking(sudoku);
	if(res)
	return counter;

	return -1;
}

bool existinrow(int **sudoku,int col,int num){
	for(int i=0;i<9;i++){
// printf("fefdf%d\n",sudoku[i][col]);
		if(sudoku[i][col]==num)
			return true;
	}
	return false;
}

bool existincol(int **sudoku,int row,int num){
	for(int i=0;i<9;i++){

		if(sudoku[row][i]==num){
			// printf("fef%dcol%dnum%d\n",sudoku[row][i],row,num);
			return true;
		}
	}

	return false;
}

bool existinblock(int **sudoku,int row,int col,int num){
	for(int i=0;i<9;i++){
// printf("fef23%d\n",sudoku[3*(row/3)+i/3][3*(col/3)+i%3]);
			if(sudoku[3*(row/3)+i/3][3*(col/3)+i%3]==num)
				return true;
		}
	return false;
}

bool isemptyplace(int **sudoku){

	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(sudoku[i][j]!=0){
				p1=i;
				p2=j;
				// printf("pos0%dpos1%d",pos[0],pos[1]);
				return true;
			}
		}
	}
	return false;
}

//forward checking helper function
bool forwardcheckinghelper(int **sudoku){
	counter++;
	bool res=false;	
	// int pos[2];
	// pos[1]=0;
	// pos[0]=0;
	int num=0;
	int temp1,temp2;
	if(!isemptyplace(sudoku)){
		return true;}
	for(num=1;num<=9;num++){
		if(existincol(sudoku,p1,num)){
			printf("existincol\n");
			continue;}
		printf("pos0%d\n",p1);
		if(existinrow(sudoku,p2,num))
			continue;
		// printf("pos1%d\n",p2 );
		if(existinblock(sudoku,p1,p2,num))
			continue;
		temp1=p1;
		temp2=p2;
		sudoku[p1][p2]=num;
		if(forwardcheckinghelper(sudoku))
			return true;
		sudoku[temp1][temp2]=0;
	}
	return false;
}


int sudoku_forwardchecking(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	counter=0;
	bool res=forwardcheckinghelper(sudoku);
	if(res)
	return counter;

	return -1;
}

int sudoku_mrv(int **sudoku)
{
	// PUT YOUR CODE HERE
	// access the sudoku using "sudoku[y][x]"
	// y between 0 and 9
	// x between 0 and 9
	// function must return the number of permutations performed
	counter=0;
	return counter;
}

