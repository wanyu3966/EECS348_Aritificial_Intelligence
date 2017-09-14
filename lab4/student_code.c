// Problem 1: The constant "EMPTY" is declared as 1 and should be 0
// Solution 1: DO NOT USE THE CONSTANT "EMPTY" AND USE THE LITERAL 0 STEAD
 
// Problem 2: The result of maps 4,5,6,7 are not used to compute the result of the lab
// Solution 2: NOTHING, PAY ATTENTION TO THE INDIVIDUAL TESTS RESULT AND NOT TO THE AGGREGATED RESULT
 
// Problem 3: The value of map one is marked as 46.68 and it should be 47.06
// Solution 3: NOTHING, THE LAB MARGIN IS 1%, SO IF YOU GET THE RIGHT VALUE IT SHOULD WORK ANYWAY
int dir[4][2]={0,1,1,0,0,-1,-1,0};
bool legal(int x,int y){
	if(x<6&&x>=0&&y<6&&y>=0)
		return true;
	return false;
}

float CalculateProbability(int sx,int sy,int y,int x,int action){
	float prob;
	if(action==SOFF){
		if(sy==y+1)
			prob=0.7;
		if(sy==y-1)
			prob=0.0;
		if(sx==x+1||sx==x-1)
			prob=0.15;
	}
	if(action==SON){
		if(sy==y+1)
			prob=0.8;
		if(sy==y-1)
			prob=0.0;
		if(sx==x+1||sx==x-1)
			prob=0.1;
	}
	if(action==WOFF){
		if(sx==x-1)
			prob=0.7;
		if(sx==x+1)
			prob=0.0;
		if(sy==y+1||sy==y-1)
			prob=0.15;
	}
	if(action==WON){
		if(sx==x-1)
			prob=0.8;
		if(sx==x+1)
			prob=0.0;
		if(sy==y+1||sy==y-1)
			prob=0.1;
	}
	if(action==EOFF){
		if(sx==x+1)
			prob=0.7;
		if(sx==x-1)
			prob=0.0;
		if(sy==y+1||sy==y-1)
			prob=0.15;
	}
	if(action==EON){
		if(sx==x+1)
			prob=0.8;
		if(sx==x-1)
			prob=0.0;
		if(sy==y+1||sy==y-1)
			prob=0.1;
	}
	if(action==NOFF){
		if(sy==y-1)
			prob=0.7;
		if(sy==y+1)
			prob=0.0;
		if(sx==x+1||sx==x-1)
			prob=0.15;
	}
	if(action==NON){
		if(sy==y-1)
			prob=0.8;
		if(sy==y+1)
			prob=0.0;
		if(sx==x+1||sx==x-1)
			prob=0.1;
	}
	return prob;
}

float getreward(int **map,int sx,int sy,int y,int x,int action,float delivery_fee,float battery_drop_cost,float dronerepair_cost){
	float reward;
	if(action==SOFF||action==WOFF||action==EOFF||action==NOFF){
		// if(map[sy][sx]==2)
		// 	reward=delivery_fee-battery_drop_cost;
		// else if(map[sy][sx]==3)
		// 	reward=(-1)*dronerepair_cost-battery_drop_cost;
		// else
			reward=(-1)*battery_drop_cost;
	}
	if(action==SON||action==WON||action==EON||action==NON){
		// if(map[sy][sx]==2)
		// 	reward=delivery_fee-2*battery_drop_cost;
		// else if(map[sy][sx]==3)
		// 	reward=(-1)*dronerepair_cost-2*battery_drop_cost;
		// else
			reward=(-2)*battery_drop_cost;
	}
	return reward;
}

float drone_flight_planner (int **map, int **policies, float **values, float delivery_fee, float battery_drop_cost, float dronerepair_cost, float discount_per_cycle)
{

	// PUT YOUR CODE HERE
	// access the map using "map[y][x]"
	// access the policies using "policies[y][x]"
	// access the values using "values[y][x]"
	// y between 0 and 5
	// x between 0 and 5
	// function must return the value of the cell corresponding to the starting position of the drone
	// 
	// bool eon=son=won=non=true;
	float q;
	int z=0;
	float prob,reward;//probability
	float gamma=1.0-discount_per_cycle;

	float value=0.0;
	for(int y=0;y<6;y++){
		for(int x=0;x<6;x++){
			if(map[y][x]==2){
				values[y][x]=delivery_fee;
				policies[y][x]=EXIT;
			}
			if(map[y][x]==3){
				values[y][x]=(-1)*dronerepair_cost;
				policies[y][x]=EXIT;
			}
		}
	}
	while(z<500){
		float valuestemp[6][6];
		for(int y=0;y<6;y++){
			for(int x=0;x<6;x++){
				valuestemp[y][x]=values[y][x];
			}
		}
		
	for(int y=0;y<6;y++){//y
		for(int x=0;x<6;x++){//x
			float qmax=-99999999;
			if(map[y][x]!=2&&map[y][x]!=3){
				for(int action=1;action<9;action++){//action loop
					q=0.0;
					for (int t=0;t<4;t++){  //state loop
						int sx=x+dir[t][1];
						int sy=y+dir[t][0];
						if(legal(sx,sy)){
							prob=CalculateProbability(sx,sy,y,x,action);
							reward=getreward(map,sx,sy,y,x,action,delivery_fee,battery_drop_cost,dronerepair_cost);
							q+=prob*(reward+(gamma)*valuestemp[sy][sx]);
						}
						else{
							prob=CalculateProbability(sx,sy,y,x,action);
							reward=getreward(map,sx,sy,y,x,action,delivery_fee,battery_drop_cost,dronerepair_cost);
							if(sx>5){
								q+=prob*(reward+(gamma)*valuestemp[sy][sx-1]);
							}
							if(sy>5){
								q+=prob*(reward+(gamma)*valuestemp[sy-1][sx]);
							}
							if(sx<0){
								q+=prob*(reward+(gamma)*valuestemp[sy][sx+1]);
							}
							if(sy<0){
								q+=prob*(reward+(gamma)*valuestemp[sy+1][sx]);
							}
						}
					}
					if(q>qmax){
						qmax=q;
						policies[y][x]=action;
					}
					values[y][x]=qmax;
				}
			}
		}
	}
	// bool result=true;
	// for(int y=0;y<6;y++){
	// 	for(int x=0;x<6;x++){
	// 		float value1=valuestemp[y][x];
	// 		float margin=values[y][x]*.01;
	// 		margin = margin<0?-margin:margin;
	// 		if((values[y][x]-margin)>value1||(values[y][x]+margin)<value1)
	// 			result=false;
	// 	}
	// }
	// if(result)
	// 	break;
	z++;
}
for(int i=0;i<6;i++){
			for(int j=0;j<6;j++){
				if(map[j][i]==1)
					value=values[j][i];
			}
		}
	return value;
}
