#include <math.h>

bool sign(float x){
	return x>=0?true:false;
}

// int argmax(float[9] index){
// 	float max=-9999;
// 	int res=-1;
// 	for (int i=0;i<9;i++){
// 		if(index[i]>max){
// 			max=index[i];
// 			res=i;
// 		}
// 	}
// 	return res;
// }


float sigmoid(float f){
	return pow((1+exp(-1.0*f)),-1);
}

void part_one_classifier(float **data_train,float **data_test)
{
	// PUT YOUR CODE HERE
	// Access the training data using "data_train[i][j]"
	// Training data contains 3 cols per row: X in 
	// index 0, Y in index 1 and Class in index 2
	// Access the test data using "data_test[i][j]"
	// Test data contains 2 cols per row: X in 
	// index 0 and Y in index 1, and a blank space in index 2 
	// to be filled with class
	// The class value could be a 0 or a 1
	float w[2];
	w[0]=1;
	w[1]=1;
	float b=0;
	int i,j;
	int iter=0;
	int maxiter=1000;
	float local,global;
	int output;
	float learnrate=0.1;
	for(i=0;i<TRAINING_SIZE;i++){
		if(data_train[i][2]==0)
			data_train[i][2]=-1;
	}

	while(global!=0&&iter<=maxiter){
		global=0;
		for(i=0;i<TRAINING_SIZE;i++){
			// printf("x%fx2%fy%f\n", data_train[i][0],data_train[i][1],data_train[i][2]);
			output=(w[0]*data_train[i][0]+w[1]*data_train[i][1]+b)>=0?1:-1;
			// printf("%d\n",output	 );
			local=data_train[i][2]-output;
			w[0]+=learnrate*local*data_train[i][0];
			w[1]+=learnrate*local*data_train[i][1];
			b+=learnrate*local;
			global+=local*local;
		}
		// printf("%f\n", global);
		iter++;
	}
	for (i=0;i<TEST_SIZE;i++){
		// printf("%fw1%fb%f\n",w[0],w[1],b );
		if((w[0]*data_test[i][0]+w[1]*data_test[i][1]+b)>=0)
			data_test[i][2]=1;
		else
			data_test[i][2]=0;
	}


}

void part_two_classifier(float **data_train,float **data_test)
{
	int i,j,k,t,y,maxj,count;
	float sum;
	float w[9][9][3],data[TRAINING_SIZE]; //weight for each class
	int vote[9];
	float b=0;
	float local,global;
	float output,iter=0,maxiter=1000 ;
	float learnrate=0.01;
	for(i=0;i<9;i++){
		for(j=i+1;j<9;j++){
			w[i][j][0]=0;
			w[i][j][1]=0;
			w[i][j][2]=0;
			while(global!=0&&iter<=maxiter){
				global=0;
				count=0;
				for(k=0;k<TRAINING_SIZE;k++){
					if(data_train[k][2]==i||data_train[k][2]==j){
						// printf("data_train%f\n",data_train[k][2] );
						if(data_train[k][2]==i)
							data[k]=1;
						else
							data[k]=-1;
						output=(w[i][j][0]*data_train[k][0]+w[i][j][1]*data_train[k][1]+w[i][j][2])>=0?1:-1;
						// printf("%d\n",output	 );
						local=data[k]-output;
						w[i][j][0]+=learnrate*local*data_train[k][0];
						w[i][j][1]+=learnrate*local*data_train[k][1];
						w[i][j][2]+=learnrate*local;
						global+=local*local;
					}
				}

			// 	if(i==2&&j==8)
			// 	printf("%di%f\n",j,global );
			// if(i==2&&j==7)
			// printf("%di%f\n",j,global );
				iter++;
			}
			global=-1;
			iter=0;
					// printf("a%fb%fc%f\n",w[i][j][0],w[i][j][1],w[i][j][2] );
		}
	}
for(t=0;t<TEST_SIZE;t++){
	for(i=0;i<9;i++)
		vote[i]=0;
	for(i=0;i<9;i++){
		for(j=i+1;j<9;j++){
			float temp=w[i][j][0]*data_test[t][0]+w[i][j][1]*data_test[t][1]+w[i][j][2];
			// printf("i%dj%dtemp%f\n",i,j,temp );	
			if(temp>=0)
				vote[i]++;
			else
				vote[j]++;
		}
	}
	int max=-1;
	for(i=0;i<9;i++){
		// printf("i%dv%d\n",i,vote[i] );
		if(vote[i]>max){
			max=vote[i];
			maxj=i;
		}
	}
	data_test[t][2]=maxj;
}

	// int i,j,k,y,maxj;
	// float sum,max;
	// float w[9][3],data[TRAINING_SIZE]; //weight for each class
	// float b=0;
	// float local,global;
	// int output,iter=0,maxiter=100;
	// float learnrate=0.1;
	// for(i=0;i<9;i++){
	// 	for(j=0;j<2;j++){
	// 		w[i][j]=1;
	// 	}
	// 	w[i][2]=0;
	// }
	// for(j=0;j<9;j++){
	// 	for(i=0;i<TRAINING_SIZE;i++){
	// 			if(data_train[i][2]==j)
	// 				data[i]=1;
	// 			else
	// 				data[i]=-1;}
	// 	while(global!=0&&iter<=maxiter){
	// 		// printf("%d\n", j);
	// 		global=0;
	// 		for(i=0;i<TRAINING_SIZE;i++){
	// 			output=(w[j][0]*data_train[i][0]+w[j][1]*data_train[i][1]+w[j][2])>=0?1:-1;
	// 			// printf("%d\n",output	 );
	// 			local=data[i]-output;
	// 			w[j][0]+=learnrate*local*data_train[i][0];
	// 			w[j][1]+=learnrate*local*data_train[i][1];
	// 			w[j][2]+=learnrate*local;
	// 			global+=local*local;
	// 		}	
	// 	// printf("%f\n",global );
	// 		iter++;
	// 	}
	// 	global=-1;
	// 	iter=0;
	// 	printf("a%fb%fc%f\n",w[j][0],w[j][1],w[j][2] );
	// }
	// for(i=0;i<TEST_SIZE;i++){
	// 	max=-9999;
	// 	maxj=-1;
	// 	// if((w[0]*data_test[i][0]+w[1]*data_test[i][1]+b)>=0)
	// 	// 	data_test[i][2]=1;
	// 	// else
	// 	// 	data_test[i][2]=0;
	// 	for(j=0;j<9;j++){
	// 		float temp=w[j][0]*data_test[i][0]+w[j][1]*data_test[i][1]+w[j][2];
	// 		if(temp>=max){
	// 			max=temp;
	// 			maxj=j;
	// 		}
	// 				// printf("data%ftemp%fj%dmax%d\n",data_test[i][0],temp,j,maxj );
	// 	}

	// 	data_test[i][2]=maxj;
	// }
}
