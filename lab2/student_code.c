// int num=0;
	// int max=-9999;
	// int min=9999;
int minimax_helper(int *board, int turn){
	int best;
	int res;
	// num++;
	int gamestatus=game_status(board);

	if(gamestatus==X)
			return 1;
	if(gamestatus==O)
			return -1;
	for(int i=0;i<9;i++){  
		if(board[i]==NONE)
			break;	
		if(i==8){
		if(gamestatus==NONE)
			return 0;}
	}
	if(turn==X){
		best=-9999;
		for(int i=0;i<9;i++){
		if(board[i]==NONE){
			board[i]=X;
			// printf("ii is%d\n", i);
			res=minimax_helper(board,O);
			board[i]=NONE;
			if(res>=best){
				best=res;
				}
				// printf("%d\n", max);
			}
		}
	}
	if(turn==O){
		best=9999;
		for(int i=0;i<9;i++){
		if(board[i]==NONE){
				board[i]=O;
				res=minimax_helper(board,X);
				board[i]=NONE;
				if(res<=best){
					best=res;
				}
				// printf("%d\n", min);
			}
		}
	}
	// if(turn==X)
	// 	return max;
	// else
	// 	return min;
	return best;
}


int abprun_helper(int *board,int turn,int alpha,int beta){

	int gamestatus=game_status(board);
	int res,best;
	if(gamestatus==X)
			return 1;
	if(gamestatus==O)
			return -1;
	for(int i=0;i<9;i++){  
		if(board[i]==NONE)
			break;	
		if(i==8){
		if(gamestatus==NONE)
			return 0;}
	}
	if(turn==X){
		best=-9999;
		for(int i=0;i<9&&alpha<=beta;i++){
			if(board[i]==NONE){
			board[i]=X;
			res=abprun_helper(board,O,alpha,beta);
			board[i]=NONE;
			if(res>best){
				best=res;
			}
			if(best>alpha)
				alpha=best;
			if(best==1)
				break;
		}
	}
	}
	if(turn==O){
		best=9999;
		for(int i=0;i<9&&alpha<=beta;i++){
			if(board[i]==NONE){
			board[i]=O;
			res=abprun_helper(board,X,alpha,beta);
			board[i]=NONE;
			if(res<best){
				best=res;
			}
			if(best<beta)
				beta=best;
			if(best==-1)
				break;
		}
	}
	}
	return best;


}

int minmax_tictactoe(int *board, int turn)
{   
	// max=-9999;
	// min=9999;
	
	int res=minimax_helper(board,turn);
	if(res==1){
		return X;
	}
	else if(res==-1)
		return O;
	else 
		return NONE;
	
}



int abprun_tictactoe(int *board, int turn)
{

	//put your code here:
	//it must return X(1), O(2) or NONE(0) for tie.
	//use the function game_status(board), to evaluate a board
	//it returns X(1) if X wins, O(2) if O wins or NONE(0) if tie or game is not finished
	//the program will keep track of the number of boards evaluated
	//int result = game_status(board);
		int alpha=-9999,beta=9999;
	int res=abprun_helper(board,turn,alpha,beta);
	if(res==1){
		return X;
	}
	else if(res==-1)
		return O;
	else 
		return NONE;
}

float st_tictactoe_win(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
	return .5;
}

float st_tictactoe_winortie(int *board, int turn)
{
	//put your code here:
	//it must return a float value between 0 and 1
	//the error margin is +/- 1%
	return .5;
}
