int	counter;


bool checkresult( int **sudoku, bool show )
{
	bool result = true;
	for ( int y = 0; y < 9; y++ )
	{
		for ( int x = 0; x < 9; x++ )
		{
			int value = sudoku[y][x];
			sudoku[y][x] = 0;
			if ( value != 0 && can_yx_be_z( sudoku, y, x, value ) )
			{
				if ( show )
					printf( "%s%d", GREEN, value );
			}else  {
				result = false;
				if ( show )
					printf( "%s%d", RED, value );
			}
			sudoku[y][x] = value;
		}
		if ( show )
			printf( "%s\n", NORMAL );
	}
	return(result);
}


bool can_yx_be_z1( int **sudoku, int y, int x, int z )
{
	for ( int i = 0; i < 9; i++ )
	{
		if ( i != x )
		{
			if ( sudoku[y][i] == z )
				return(false);
		}
		if ( i != y )
		{
			if ( sudoku[i][x] == z )
				return(false);
		}
		if ( (y != ( (y / 3) * 3 + i / 3) ) || x != ( (x / 3) * 3 + i % 3) )
			// continue;
		{if ( sudoku[(y / 3) * 3 + i / 3][(x / 3) * 3 + i % 3] == z )
			return(false);}
	}
	return(true);
}


/* backtracking helper function */
bool backtracking( int **sudoku )
{
	/* printf("%d\n",counter ); */
	if ( checkresult( sudoku, false ) )
		return(true);
	int num = 0;
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( sudoku[i][j] == 0 )
			{
				for ( num = 1; num <= 9; num++ )
				{
					sudoku[i][j] = num;
					counter++;
					if ( can_yx_be_z1( sudoku, i, j, num ) )
					{
						if ( backtracking( sudoku ) )
							return(true);
					}
					
						sudoku[i][j] = 0;
				}
				return(false);
			}
		}
	}
	// return(true);
}


int sudoku_backtracking( int **sudoku )
{
	/*
	 * PUT YOUR CODE HERE
	 * access the sudoku using "sudoku[y][x]"
	 * y between 0 and 9
	 * x between 0 and 9
	 * function must return the number of permutations performed
	 */
	counter = 0;
	bool res = backtracking( sudoku );

	return(counter);
}


/* forward checking helper function */
bool forwardcheckinghelper( int **sudoku )
{
	counter++;
	int num = 0;
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( sudoku[i][j] == 0 )
			{
				for ( num = 1; num <= 9; num++ )
				{
					if ( can_yx_be_z( sudoku, i, j, num ) )
					{
						sudoku[i][j] = num;
						if ( forwardcheckinghelper( sudoku ) )
							return(true);
						else
							sudoku[i][j] = 0;
					}
				}
				return(false);
			}
		}
	}
	return(true);
}

int sudoku_forwardchecking( int **sudoku )
{
	/*
	 * PUT YOUR CODE HERE
	 * access the sudoku using "sudoku[y][x]"
	 * y between 0 and 9
	 * x between 0 and 9
	 * function must return the number of permutations performed
	 */
	counter = 0;
	bool res = forwardcheckinghelper( sudoku );
	if ( res )
		return(counter);

	return(-1);
}

int count(int **sudoku,int row, int col){
	int	empty[9]={1,1,1,1,1,1,1,1,1};
	int count=0;
	for(int i=0;i<9;i++){
			for(int num=1;num<=9;num++){
				if(sudoku[row][i]==num||sudoku[i][col]==num||sudoku[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3]==num)
					empty[num-1]=0;
			}
		}
	for(int i=0;i<9;i++){
		count+=empty[i];
	}
	return count;
}

int findmin(int **sudoku){
	int min=9;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(sudoku[i][j]==0&&count(sudoku,i,j)<min){
				min=count(sudoku,i,j);
				// sudoku_mrvhelper(sudoku,i,j);
			}
		}
	}
	return min;
}

//MRV helper function
bool sudoku_mrvhelper(int **sudoku){
	counter++;
	int num = 0;
	int min=findmin(sudoku);
	for ( int i = 0; i < 9; i++ )
	{
		for ( int j = 0; j < 9; j++ )
		{
			if ( sudoku[i][j] == 0 &&count(sudoku,i,j)==min)
			{
				for ( num = 1; num <= 9; num++ )
				{
					if ( can_yx_be_z( sudoku, i, j, num ) )
					{
						sudoku[i][j] = num;
						if ( sudoku_mrvhelper( sudoku ) )
							return(true);
						else
							sudoku[i][j] = 0;
					}
				}
				return(false);
			}
		}
	}
	return(true);
}

int sudoku_mrv( int **sudoku )
{
	/*
	 * PUT YOUR CODE HERE
	 * access the sudoku using "sudoku[y][x]"
	 * y between 0 and 9
	 * x between 0 and 9
	 * function must return the number of permutations performed
	 */


	counter = 0;
	sudoku_mrvhelper(sudoku);
	return(counter);
}


