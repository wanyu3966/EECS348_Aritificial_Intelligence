#include <math.h>

#define PI 3.1415926

int abs(int x){
	return x>0?x:-x;
}

void detect_line (unsigned char ***image, float *m, float *b)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// set m and b using the * operator
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	int **edge=init_space(480,640);
	
	int **space=init_space(480,640);
	int **hough=init_space(2000,15000);
	int indb,indm;
	int Gx,Gy,G;
	float temp;
	//hough space
	for (int y = 0; y < 2000; y++)
	{
		for (int x = 0; x < 15000; x++)
		{
			hough[y][x]=0;
		}
	}

	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			if(image[RED][y][x]==255||image[BLUE][y][x]==255||image[GREEN][y][x]==255)
				space[y][x]=255;
			else{
				// printf("space0\n");
				space[y][x]=0;
			}
		}
	}

	//hough space
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			if(space[y][x]==0){

				for(indm=0;indm<2000;indm++){
					// if(x<639)
					// printf("x%d\n",x );
					temp=(float)indm/100;
					*m=-10+temp;
					// printf("%f\n", *m);
					*b=(-x)*(*m)+y;
					// printf("b x y%f %d %d\n", (int) (intptr_t)*b,x,y);
					if((int) (intptr_t)*b>-7500&&(int) (intptr_t)*b<7500){
						// printf("bint%d\n",(int) (intptr_t)*b );
						hough[indm][(int) (intptr_t)*b+7500]+=1;
					}
				}
			}
		}
	}
	int max=-9999,maxh,maxb;
	for (int y = 0; y < 2000; y++)
	{
		for (int x = 0; x < 15000; x++)
		{
			if(hough[y][x]>max){
				max=hough[y][x];
				
				*m=-((float)y/100-10);
				*b=479-(x-7500);
			}
		}
	}

}
bool iswhite(unsigned char ***image,int y, int x){
	if(image[RED][y][x]==255&&image[BLUE][y][x]==255&&image[GREEN][y][x]==255)
		return true;
	return false;
}

bool iscolorful(unsigned char ***image,int y,int x){
	if(image[RED][y][x]!=0||image[BLUE][y][x]!=0||image[GREEN][y][x]!=0)
		if(!iswhite(image,y,x))
			return true;
	
	return false;
}
bool isedge(unsigned char ***image,int y ,int x){
	if(iswhite(image,y,x))
		return false;
	for (int j=y-1;j<y+2;j++){
		for(int i=x-1;i<x+1;i++){
			if(iscolorful(image,y,x)&&iswhite(image,j,i))
				return true;
		}
	}
	return false;
}

bool withinmerge(int **hough,int theta,int w){
	for (int i = 0; i < 20; i++)
	{
		if((hough[i][0]-theta)<=3&&(hough[i][0]-theta)>=-3)
			if((hough[i][1]-w)<=15&&(hough[i][1]-w)>=-15)
				return true;
	}
	return false;
}
int detect_polygon (unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// return the number of sides of the polygon
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"

	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// set m and b using the * operator
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	int **edge=init_space(480,640);
	float *m,*b;
	int **space=init_space(480,640);
	int **hough=init_space(180,15000);
	int indb,indm;
	int theta;
	double w;
	int Gx,Gy,G;
	float temp;
	int count=0;
	int **merge=init_space(20,2);
	int res=0;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			merge[y][x]=-9999;
		}
	}
	//hough space
	for (int y = 0; y < 180; y++)
	{
		for (int x = 0; x < 15000; x++)
		{
			hough[y][x]=0;
		}
	}

	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			if(image[RED][y][x]==255&&image[BLUE][y][x]==255&&image[GREEN][y][x]==255)//white
				space[y][x]=0;
			else{//color
				// printf("space0\n");
				space[y][x]=255;
			}
			edge[y][x]=255;
		}
	}
	// printf("finish initialization\n");
	// edge detection
	for (int y = 1; y < 479; y++)
	{
		for (int x = 1; x < 639; x++)
		{
			edge[y][x]=255;
			// Gy=space[y-1][x-1]+2*space[y][x-1]+space[y+1][x-1]-space[y-1][x+1]-2*space[y][x+1]-space[y+1][x+1];
			// Gx=space[y-1][x-1]+2*space[y-1][x]+space[y-1][x+1]-space[y+1][x-1]-2*space[y+1][x]-space[y+1][x+1];
			// G=abs(Gy)+abs(Gx);	
			// // printf("%c\n",G );
			// if(G>=255){count++;
			// 	edge[y][x]=255;
			// }
			// else{
			// 	edge[y][x]=0;
			// }
			if(isedge(image,y,x)){
				count++;
				edge[y][x]=0;
			}
			else{
				edge[y][x]=255;
			}
		}
	}
	// printf("pixel%d\n", count);

	//hough space
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
		{
			if(edge[y][x]==0){

				for(theta=0;theta<180;theta++){
					// if(x<639)
					
					w=cos((double)(PI*theta/180))*x-sin((double)(PI*theta/180))*y;
					// double result=cos(PI);
					// printf("x%lf\n",w );
					// printf("%f\n", *m);
					// printf("b x y%f %d %d\n", (int) (intptr_t)*b,x,y);
					if((int) (intptr_t)w>-7500&&(int) (intptr_t)w<7500){
						// printf("bint%d\n",(int) (intptr_t)*b );
						hough[theta][(int) (intptr_t)w+7500]+=1;
					}
				}
			}
		}
	}
	float max=-9999;
	for (int y = 0; y < 180; y++)
	{
		for (int x = 0; x < 15000; x++)
		{
			if(hough[y][x]>max){
				max=hough[y][x];
				// printf("%d %d %d\n",max,y,x-7500);
			}
		}
	}
	for (int y = 0; y <180; y++)
	{
		for (int x = 0; x < 15000; x++)
		{
			if(hough[y][x]>(max*0.24)){

				// printf("outside%d %d %d\n",hough[y][x],y,x-7500);
				if(!withinmerge(merge,y,x)){
					merge[res][0]=y;
					merge[res][1]=x;
					res++;

				// printf("%d %d %d\n",hough[y][x],y,x-7500);
				}

			}
		}
	}



	return res;
}

int circle_on_top (unsigned char ***image)
{
	// PUT YOUR CODE HERE
	// access the image using "image[chanel][y][x]"
	// return RED or BLUE
	// to create a bidimentional structure you can use "int **space=init_space(heigh, width);"
	return RED;
}