			#define MAX MAP_HEIGHT*MAP_WIDTH
			//moving direction
			int dir[4][2]={0,1,1,0,0,-1,-1,0};
			
			//find for df_search,bfsfind for bf_search
			bool find=false,bfsfind=false;
			//determine whether the point is within the map
			bool legal(int x,int y){
				if(x<MAP_WIDTH&&x>=0&&y<MAP_HEIGHT&&y>=0)
					return true;
				return false;
			}
			//recursion
			void dfs(int **map,int x,int y){
				if(find)
					return;
				for(int i=0;i<4;i++){
					int sx=x+dir[i][1],sy=y+dir[i][0];
					if(legal(sx,sy))
					{
						if(map[sy][sx]==0){
						map[sy][sx]=4;
						dfs(map,sx,sy);
						if(!find)
							map[sy][sx]=4;
						else{
							map[sy][sx]=5;
							return;
							}
						}
						if(map[sy][sx]==3)
						{
							map[sy][sx]=5;
							find=true;
							return;
						}
					}
				}
			}



			bool df_search(int **map)
			{ 
				bool found = false;
				find=false;
				int i = 0, j = 0, x = 0, y = 0;
				int row = 0, col = 0;
				int depth = 0;
				//finding starting point
				for (j = 0; j < MAP_HEIGHT; j++) {
					for (i = 0; i < MAP_WIDTH; i++) {
						if (map[j][i] == 2)
						{
							x = i;
							y = j;
							break;
						}
					}
					// break; 
				}
				// map[y][x] = 5;
				dfs(map,x,y);
				row=y;
				col=x;

				found=find;
				if(found)
				map[row][col]=5;
				else
				map[row][col]=4;
				return found;
			}

			

			// void bfs(map,x,y){
			// 	if(bfsfind)
			// 		return;
			// 	int curx=queue[head++][0];
			// 	int cury=queue[head++][1];
			// 	for (int i = 0; i < 4; i++)
			// 	{
			// 		int sx=curx+dir[i][1],sy=cury+dir[i][0];
					
			// 	if(legal(sx,sy)){
			// 		if(map[sy][sx]==0){
			// 			map[sy][sx]=4;
			// 			queue[tail++][0]=sx;
			// 			queue[tail++][1]=sy;
			// 		}
			// 	}
			// }
			

			// }

			bool bf_search(int **map)
			{
				int queue[MAP_WIDTH*MAP_HEIGHT][3];
				int head=0,tail=0;
				bool found = false;
				head=0;
				tail=0;
				int endx=0,endy=0;
				int i = 0, j = 0, x = 0, y = 0;
				//finding starting point
				for (j = 0; j < MAP_HEIGHT; j++) {
					for (i = 0; i < MAP_WIDTH; i++) {
						if (map[j][i] == 2)
						{
							x = i;
							y = j;
							break;
						}
					}
				}
				int col=x,row=y;
				// map[y][x]=5;
				queue[tail][0]=x;
				queue[tail][1]=y;
				queue[tail][2]=-1;
				tail++;
				while(head<tail){
				if(found)
					break;
				int curx=queue[head][0];
				int cury=queue[head][1];

				for (int i = 0; i < 4; i++)
				{
					int sx=curx+dir[i][1],sy=cury+dir[i][0];//temprorary x and y coornidate
				if(legal(sx,sy)){
					if(map[sy][sx]==0){
						map[sy][sx]=4;
						// printf("%d%d\n",sx,sy );
						queue[tail][2]=head;
						queue[tail][0]=sx;
						queue[tail][1]=sy;
						tail++;
					}
					if(map[sy][sx]==3){
						map[sy][sx]=5;
						map[queue[head][1]][queue[head][0]]=5;
						endx=sx;
						endy=sy;
						queue[tail][2]=head;
						found=true;
						break;
						}
					}
				}
				if(!found)
					head++;
			}
				if(found){
					while(map[row][col]==2){
						// printf("%s\n", "refresh");
						map[endy][endx]=5;
						head=queue[head][2];
						endy=queue[head][1];
						endx=queue[head][0];
					}
				}
				else{
					map[row][col]=4;
				}
				return found;
			}
