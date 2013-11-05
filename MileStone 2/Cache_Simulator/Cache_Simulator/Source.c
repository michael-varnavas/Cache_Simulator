#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<conio.h>
#include <time.h>

int NUM_MUL;			//Arithmos pou pollaplasiazw to cache_size sto loop otan kamnw generate to arxeio

int word_size_bytes; //Size in bytes
int ram_size_bytes;		//Ram Size (Bytes)
int ram_size=0;//Ram Size (Entries)
int cache_size_bytes;	//Cache Size Bytes
int cache_size=0;//Cache Size (Entries)
int Write_Back_Through;
int Write_Allocate;
int num_of_flush;		//Minimum amount of Flushes
int words_in_block;	//Amount of words in each block
int type_of_cache;	//0 = Direct Mapped. 1= fully Associative. 2= N-way Associative
int num_of_ways;		//In case of N-way, # of ways
int read_cycles_cache;
int read_cycles_ram;
int write_cycles_ram;
int write_cycles_cache;
int policy;
#define vasi_2 2			//Help variable for logarithm


FILE *output;				//Pointers of files that we use
FILE *input;
FILE *fp;
FILE *para;

struct cache_block
{
    int index;
	int tag;
	int block_offset[30];
	int valid;
	int use_time;
	int dirty;
	int node_num;
	int age;
	int way;

    struct cache_block *next;
};



void parameters_parser()
{
	errno_t errorCode =fopen_s(&para,"Arxeio Parametrwn","r+");
	int ch;
	int i;

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&cache_size_bytes);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&ram_size_bytes);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&word_size_bytes);

	
		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&Write_Back_Through);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&Write_Allocate);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&words_in_block);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&type_of_cache);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&NUM_MUL);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&num_of_ways);


		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&num_of_flush);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&read_cycles_cache);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&read_cycles_ram);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&write_cycles_ram);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&write_cycles_cache);

		fscanf_s(para,"%c",&ch,1);
		while((char)ch!=':'){fscanf_s(para,"%c",&ch,1);}
		fscanf_s(para,"%c",&ch,1);
		fscanf_s(para,"%d",&policy);
}
int bin2dec(long int array[],int size)
{
	
	int num=0;
	int j=0;
	int i;
	for(i=size;i>=0;i--)
	{
		num=num+ (array[i]*pow((double)2,j));
		j=j+1;
		//printf("\n%d\n",num);
	}
	return num;
}
void dec2bin(long int num, long int rem[])   // Decimal to Binary Function
{

long int i=0;				//Variable decleration
int j;
for(j=0;j<50;j++)			//Inisialization of rem array with zeros
	rem[j]=0;
while(num>0)
 {
 rem[i]=num%2;				//calculation of
 num=num/2;
 i++;

 }

	 
}

void direct_mapped(int ram_bits,int cache_bits){
int ch;																//Variable decleration
int command;
int size;
long int address[50];													//Array to temporary hold the binnary address
long int temp[50];
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block 
int i=0;
int j=0;
int k=0;
int index;
int index_dec;
int tag_dec;
int offset_dec;
int address_dec;
int count_cycles=0;
int hit_flag=0;
int compulsory=0;
int conflict=0;
int icycles=0;
int hit_counter=0;
int miss_counter=0;
int replaced;
    struct cache_block *root; /* This will be the unchanging first node */
 
    /* This will point to each node as it traverses the list */
    struct cache_block *conductor,*tmp;  
	 int x;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write


//List Creation
    //allocating space for the root   
    root =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block));
    root->next = 0;
	root->tag=-1;
    conductor = root;
    //create ten new nodes
 
    for(x = 1; x <=cache_size/words_in_block; x++)
    {
                /* Creates a node at the end of the list */
                conductor->next =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block) ); 
                conductor = conductor->next;
                conductor->index = x;
				
				//conductor->tag=-1;
    }
 
    //marking the last as NULL
    conductor->next = 0;
 
    //conductor points to root again
    conductor = root;
	conductor = root;

	while(conductor->next!=0)
	{
		for(k=0;k<30;k++)
		{
			conductor->block_offset[k]=-1;
		}
		conductor=conductor->next;
	}


	conductor = root;
	
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		hit_flag=0;
		replaced=-1;
		compulsory=0;
		conflict=0;
		icycles=0;

		for(k=0;k<50;k++){temp[k]=0;}

		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable

		if((char)command=='F')
		{
			conductor = root;
									
			if((Write_Back_Through==0))
									{
										while(conductor->next!=0)
										{
											if(conductor->dirty==1)
											{
												count_cycles=count_cycles+write_cycles_ram;
												icycles=icycles+write_cycles_ram;
											}
											conductor=conductor->next;
										}
									}
			conductor = root;
			while(conductor->next != 0)
				{
					conductor->valid=0;
					conductor->tag=0;
					conductor->dirty=0;
	
					conductor = conductor->next;
				}

			
			conductor = root;

			fprintf(fp,"******************************************FLUSH*****************************************\t\t\tInstruction Cycles: %d\n",icycles);
			while((char)ch!='\n'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
			fscanf_s(input,"%c",&ch,1);
			continue;
		}

								

		fscanf_s(input,"%c",&ch,1);									//bypass the space

		for(k=0;k<(ram_bits+1);k++){
			fscanf_s(input,"%c",&ch,1);
			if((char)ch=='0'){address[k]=0;}						//with this loop we but each bit of the address in to an aray of integers (0 or 1)
			if((char)ch=='1'){address[k]=1;}

		}
		
		fprintf(fp,"Address: ");									//Print Address in binnary format
		for(k=0;k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		address_dec=bin2dec(address,k-1);
		fprintf(fp," (%d) \t",address_dec);
		fprintf(fp,"   |   ");										//Print selected command
		switch ((char)command)
		{
		case 'R':{
				fprintf(fp,"Command: Read   |   ");
				break;
				 }
		case 'W':{
				fprintf(fp,"Command: Write  |   ");
				break;
				 }
		case 'M':{
				fprintf(fp,"Command: Modify |   ");
				break;
				 }
		case 'F':{
				fprintf(fp,"Command: Flush  |   ");
				break;
				 }
		default:
			break;
		}
		index=log((double)(cache_size/words_in_block))/log((double)vasi_2);
		tag_bits = ram_bits-index;								//Calculation of tag bits
		if(words_in_block>1)
		{
			tag_bits = ram_bits-index-block_offset;
		}
		
		fprintf(fp,"Tag: ");										//Print tag bits
		for(k=0;k<(tag_bits);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			tag_dec=bin2dec(temp,k-1);
				
			for(k=0;k<50;k++){temp[k]=0;}

		fprintf(fp,"  |  ");
		
		fprintf(fp,"Index: ");										//Print index bits
	
		for(k=tag_bits;k<(ram_bits-block_offset);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			
			index_dec=bin2dec(temp,k-1);
			for(k=0;k<50;k++){temp[k]=0;}
			

		if(block_offset !=0){
		fprintf(fp,"  |  ");										//Print block offset bits
		
		fprintf(fp,"block Offset: ");
		for((k=ram_bits-block_offset);k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			
			offset_dec=bin2dec(temp,k-1);
			for(k=0;k<50;k++){temp[k]=0;}
			

			
			switch ((char)command)
		{
		case 'R':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									hit_flag=1;
									icycles=read_cycles_cache;
									count_cycles=count_cycles+icycles;
								}
								else
								{
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									compulsory=0;
									conflict=1;
								
								}
							}
							else
							{
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									if(conductor->valid==0)
									{
										compulsory=1;
										conflict=0;
									}
									else if(conductor->tag!=tag_dec)
									{
										compulsory=0;
										conflict=1;
									}
							}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		case 'W':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==0)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									
									hit_flag=1;
									conductor->dirty=1;
									
								}
								else
								{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
										icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
									if((Write_Back_Through==0)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
										icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									
									conductor->block_offset[block_offset]=address_dec;
									conductor->valid=1;
									conductor->dirty=1;
								}
							}
							else
							{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
										icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
									if((Write_Back_Through==0)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
										icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									replaced=conductor->block_offset[block_offset];
									conductor->block_offset[block_offset]=address_dec;
									conductor->tag=tag_dec;
									conductor->valid=1;
									conductor->dirty=1;
							}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		case 'M':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									hit_flag=1;
									icycles=read_cycles_cache;
									count_cycles=count_cycles+icycles;
								}
								else
								{
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									compulsory=0;
									conflict=1;
								
								}
							}
							else
							{
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									if(conductor->valid==0)
									{
										compulsory=1;
										conflict=0;
									}
									else if(conductor->tag!=tag_dec)
									{
										compulsory=0;
										conflict=1;
									}
							}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		
		default:
			break;
		}

		}
		if(hit_flag==1)
		{
			fprintf(fp,"\t(Hit!)\t\t\t\t");
			hit_counter=hit_counter+1;
		}
		else
		{
			if((char)command=='W'){
				fprintf(fp,"\t(Miss!)\t\t\t\t");}
			else
			fprintf(fp,"\t(Miss!)");
			miss_counter=miss_counter+1;
		}

		if(compulsory==1)
		{
			fprintf(fp,"\t(Compulsory)");
		}
		if(conflict==1)
		{
			fprintf(fp,"\t( Conflict )");
		}

		fprintf(fp,"\tInstruction Cycles: %d",icycles);
		if(((char)command=='W')&&(hit_flag==0)&&(replaced!=-1))
		fprintf(fp,"\tReplaced: %d",replaced);
		fprintf(fp,"\n");

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!='\n'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		//fscanf_s(input,"%c",&ch,1);

}
fprintf(fp,"\nTotal Cycles: %d\n",count_cycles);
fprintf(fp,"\nHit Rate: %.2f %%\n",(hit_counter/(double)(NUM_MUL*ram_size))*100);
fprintf(fp,"\nMiss Rate: %.2f %%\n",(100-(hit_counter/(double)(NUM_MUL*ram_size))*100));
conductor=root;
while(conductor->next!=0)
{
	tmp=conductor;
	conductor=conductor->next;
	free(tmp);
}

	

}

void fully_assosiative(int ram_bits,int cache_bits){
int ch;																//Variable decleration
int command;
long int address[50];													//Array to temporary hold the binnary address
long int temp[50];
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block 
int i=0;
int j=0;
int k=0;
int tag_dec;
int offset_dec;
int address_dec;
int count_cycles=0;
int hit_flag=0;
int compulsory=0;
int conflict=0;
int capacity=0;
int flag_ok=0;
int max;
int random_num=0;
int found_flag=0;
int read_flag=0;
int miss_flag=0;
int icycles=0;
int hit_counter=0;
int miss_counter=0;

    struct cache_block *root; /* This will be the unchanging first node */
 
    /* This will point to each node as it traverses the list */
    struct cache_block *conductor,*find,*fifo,*lru,*maximum,*random,*tmp;  
	 int x;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write

    root =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block));
    root->next = 0;
	root->tag=0;
    conductor = root;
    //create ten new nodes
 
    for(x = 1; x <=cache_size/words_in_block; x++)
    {
                /* Creates a node at the end of the list */
                conductor->next =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block) ); 
                conductor = conductor->next;
                conductor->tag = 0;
				//conductor->tag=-1;
    }
 
    //marking the last as NULL
    conductor->next = 0;
 
    //conductor points to root again
    conductor = root;

	while(conductor->next!=0)
	{
		for(k=0;k<30;k++)
		{
			conductor->block_offset[k]=-1;
		}
		conductor=conductor->next;
	}


	conductor = root;
	fifo = root;
	srand((int)time(NULL));
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		hit_flag=0;
		icycles=0;
		miss_flag=0;
		read_flag=0;
		flag_ok=0;
		found_flag=0;
		max=0;

		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable
		if((char)command=='F')
		{
			conductor = root;
									
			if((Write_Back_Through==0))
									{
										while(conductor->next!=0)
										{
											if(conductor->dirty==1)
											{
												count_cycles=count_cycles+write_cycles_ram;
												icycles=icycles+write_cycles_ram;
											}
											conductor=conductor->next;
										}
									}
			conductor = root;
			fifo=root;
			conductor = root;
			while(conductor->next != 0)
				{
					conductor->valid=0;
					conductor->tag=0;
					conductor->dirty=0;
	
					conductor = conductor->next;
				}
			fprintf(fp,"******************************************FLUSH*****************************************\t\t\tInstruction Cycles: %d\n",icycles);
			while((char)ch!='\n'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
			fscanf_s(input,"%c",&ch,1);
			continue;
		}
		fscanf_s(input,"%c",&ch,1);									//bypass the space

		for(k=0;k<(ram_bits+1);k++){
			fscanf_s(input,"%c",&ch,1);
			if((char)ch=='0'){address[k]=0;}						//with this loop we but each bit of the address in to an aray of integers (0 or 1)
			if((char)ch=='1'){address[k]=1;}

		}
		
		fprintf(fp,"Address: ");									//Print Address in binnary format
		for(k=0;k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		address_dec=bin2dec(address,k-1);
		fprintf(fp,"   |   ");										//Print selected command
		switch ((char)command)
		{
		case 'R':{
				fprintf(fp,"Command: Read   |   ");
				break;
				 }
		case 'W':{
				fprintf(fp,"Command: Write  |   ");
				break;
				 }
		case 'M':{
				fprintf(fp,"Command: Modify |   ");
				break;
				 }
		case 'F':{
				fprintf(fp,"Command: Flush  |   ");
				break;
				 }
		default:
			break;
		}
		tag_bits = ram_bits;										//Calculation of tag bits
		if(words_in_block>1)
		{
			tag_bits = ram_bits-block_offset;
		}
		
		fprintf(fp,"Tag: ");										//Print tag bits
		for(k=0;k<(tag_bits);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			tag_dec=bin2dec(temp,k-1);
				
			for(k=0;k<50;k++){temp[k]=0;}
		
		fprintf(fp,"  |  ");
		
		
		if(block_offset !=0){
	
		
		fprintf(fp,"block Offset: ");								//Print block offset bits
		for((k=ram_bits-block_offset);k<(ram_bits);k++)
		{
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
		offset_dec=bin2dec(temp,k-1);
			for(k=0;k<50;k++){temp[k]=0;}
			

			
			switch ((char)command)
		{
		case 'R':{
			conductor = root;
				 while(conductor->next != 0)
					{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									icycles=read_cycles_cache;
									hit_flag=1;
									conductor->use_time=0;
								
				
								}
								else
								{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									compulsory=0;
									conflict=1;
									capacity=0;

								}
							}
							else
							{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									if(conductor->valid==0)
									{
										if(miss_flag==0){
										compulsory=1;
										conflict=0;
										capacity=0;
										miss_flag=1;
										}
									}
									else if(conductor->tag!=tag_dec)
									{
										if(miss_flag==0){
										compulsory=0;
										conflict=1;
										capacity=0;
										miss_flag=1;
										}
									}
							}
						
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		case 'W':{
			
			conductor = root;
				 while(conductor->next != 0)
					{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if((conductor->block_offset[block_offset]==address_dec))
								{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==0)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									
									hit_flag=1;
									conductor->use_time=0;
									found_flag=1;
									conductor->dirty=1;
									break;
									
									
								}
								else
								{
										if(conductor->block_offset[block_offset]==-1)
										{
										if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
										
											conductor->block_offset[block_offset]=address_dec;
											conductor->valid=1;
											conductor->use_time=0;
											conductor->dirty=1;
											flag_ok=1;
											found_flag=1;
									compulsory=0;
									conflict=1;
									capacity=0;
											break;
										}
									
									
										if (flag_ok==0)
										{
											find=root;
											while(find->next!=0)
											{
												if(find->valid==0)
												{

													for(k=0;k<29;k++)
														{
															find->block_offset[k]=-1;
														}
													if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
													find->block_offset[block_offset]=address_dec;
													find->valid=1;
													find->use_time=0;
													found_flag=1;
													find->dirty=1;
													compulsory=0;
													conflict=1;
													capacity=0;
													break;
												}
												find=find->next;
											}
											find=root;
										}	
								}	
							}
							else
							{
									if(conductor->valid==0)
									{
										if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
										conductor->block_offset[block_offset]=address_dec;
										conductor->use_time=0;
										conductor->valid=1;
										conductor->dirty=1;
										found_flag=1;
										conductor->tag=tag_dec;
									compulsory=1;
									conflict=0;
									capacity=0;
										break;
									}
									else
									{
						
										found_flag=0;
									}
									
							}
						
						conductor = conductor->next;
					}
				 
    conductor = root;	 //conductor points to root again
	
	if (found_flag==0)
	{
		compulsory=0;
		conflict=0;
		capacity=1;
		
		if(policy==0){
			if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
			for(k=0;k<30;k++)
					{
						fifo->block_offset[k]=-1;
					}
			fifo->block_offset[block_offset]=address_dec;
			fifo->valid=1;
			fifo->use_time=1;
			fifo->tag=tag_dec;
			fifo->dirty=1;
			
			if(fifo->next==0){fifo=root;}
			else
				fifo=fifo->next;
		}
		else if(policy==1)
			{
				lru=root;
				maximum=root;
				max=lru->use_time;
				while(lru->next!=0)
				{
					if(lru->use_time>max)
					{
						max=lru->use_time;
						maximum=lru;
					}
					lru=lru->next;
				}
				for(k=0;k<30;k++)
					{
						maximum->block_offset[k]=-1;
					}
			maximum->block_offset[block_offset]=address_dec;
			maximum->valid=1;
			maximum->use_time=1;
			maximum->tag=tag_dec;
			maximum->dirty=1;
			if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
			}
		else if(policy==2)
		{
			random_num=rand()%(((cache_size/words_in_block))-1);
			random=root;
			while(random_num>0)
			{
				random=random->next;
				random_num=random_num-1;
			}
			for(k=0;k<30;k++)
					{
						random->block_offset[k]=-1;
					}
			random->block_offset[block_offset]=address_dec;
			random->valid=1;
			random->use_time=1;
			random->tag=tag_dec;
			random->dirty=1;
			if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
		}

	}
	

	
	conductor = root;

	
				break;
				 }
		case 'M':{
			conductor = root;
				 while(conductor->next != 0)
					{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									icycles=read_cycles_cache;
									hit_flag=1;
									conductor->use_time=0;
								
						
								}
								else
								{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									compulsory=0;
									conflict=1;
									capacity=0;

								}
							}
							else
							{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									if(conductor->valid==0)
									{
										if(miss_flag==0){
										compulsory=1;
										conflict=0;
										capacity=0;
										miss_flag=1;
										}
									}
									else if(conductor->tag!=tag_dec)
									{
										if(miss_flag==0){
										compulsory=0;
										conflict=1;
										capacity=0;
										miss_flag=1;
										}
									}
							}
						
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		
		default:
			break;
		}
		}

		if(hit_flag==1)
		{
			fprintf(fp,"\t(Hit!)\t\t\t\t");
			hit_counter=hit_counter+1;
		}
		else
		{
			fprintf(fp,"\t(Miss!)");
			miss_counter=miss_counter+1;

		
		if(compulsory==1)
		{
			fprintf(fp,"\t(Compulsory)");
		}
		else if(conflict==1)
		{
			fprintf(fp,"\t( Conflict )");
		}
		else if(capacity==1)
		{
			fprintf(fp,"\t( Capacity )");
		}
		}
		fprintf(fp,"\tInstruction Cycles: %d",icycles);
				fprintf(fp,"\n");
		
		

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!=')'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		fscanf_s(input,"%c",&ch,1);
	conductor = root;
	while(conductor->next!=0)
	{
		conductor->use_time=conductor->use_time+1;
		conductor=conductor->next;
	}
	conductor = root;
}
fprintf(fp,"\nTotal Cycles: %d\n",count_cycles);
fprintf(fp,"\nHit Rate: %.2f %%\n",(hit_counter/(double)(NUM_MUL*ram_size))*100);
fprintf(fp,"\nMiss Rate: %.2f %%\n",(100-(hit_counter/(double)(NUM_MUL*ram_size))*100));
conductor=root;
while(conductor->next!=0)
{
	tmp=conductor;
	conductor=conductor->next;
	free(tmp);
}
}

void n_way(int ram_bits,int cache_bits){
int ch;																//Variable decleration
int ways=num_of_ways;
int command;
long int address[50];													//Array to temporary hold the binnary address
long int temp[50];
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block offset
int i=0;
int j=0;
int k=0;
int index_dec;
int tag_dec;
int offset_dec;
int address_dec;
int count_cycles=0;
int hit_flag=0;
int compulsory=0;
int conflict=0;
int capacity=0;
int index;
long int random_num;
int struct_flag=0;
int found_ok=0;
int age=0;
int oldest;
int node_num;
int node_way=-1;
int icycles=0;
int hit_counter=0;
int miss_counter=0;
int miss_flag=0;
int read_flag=0;

struct cache_block *root; /* This will be the unchanging first node */
struct cache_block *conductor,*find,*fifo,*old,*lru,*maximum,*random,*tmp;  
int x;
int y;
int count=1;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write

    root =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block));
    root->next = 0;
	root->tag=0;
    conductor = root;
    //create ten new nodes
	for(x = 1; x <cache_size/words_in_block/ways; x++)
    {
                if(struct_flag==0){
					for(y=1;y<ways;y++)
					{
						conductor->next =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block) ); 
						conductor = conductor->next;
						conductor->index = 0;
						conductor->node_num=count;
						count=count+1;
						struct_flag=1;
						conductor->way=y;
					}
				}
				for(y=0;y<ways;y++){
				/* Creates a node at the end of the list */
                conductor->next =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block) ); 
                conductor = conductor->next;
                conductor->index = x;
				conductor->node_num=count;
				count=count+1;
				conductor->way=y;
				//conductor->tag=-1;
				}

						
    }
 				conductor->next =(struct cache_block *) calloc(cache_size, sizeof(struct cache_block) ); 
				conductor = conductor->next;
				conductor->index = x;
				conductor->node_num=count;
    //marking the last as NULL
    conductor->next = 0;
 
    //conductor points to root again
    conductor = root;

	while(conductor->next!=0)
	{
		for(k=0;k<30;k++)
		{
			conductor->block_offset[k]=-1;
		}
		conductor=conductor->next;
	}


	conductor = root;


srand((int)time(NULL));												//rand() is based on time so the numbers are better shuffled
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		miss_flag=0;
		read_flag=0;
		hit_flag=0;
		icycles=0;
		node_way=-1;
		found_ok=0;
		fifo = root;
		
		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable

		if((char)command=='F')
		{
			conductor = root;
			while(conductor->next != 0)
				{
					conductor->valid=0;
					conductor->tag=0;
					conductor->dirty=0;
	
					conductor = conductor->next;
				}
			fprintf(fp,"******************************************FLUSH*****************************************\n");
			while((char)ch!='\n'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
			fscanf_s(input,"%c",&ch,1);
			continue;
		}
		fscanf_s(input,"%c",&ch,1);									//bypass the space

		for(k=0;k<(ram_bits+1);k++){
			fscanf_s(input,"%c",&ch,1);
			if((char)ch=='0'){address[k]=0;}						//with this loop we but each bit of the address in to an aray of integers (0 or 1)
			if((char)ch=='1'){address[k]=1;}

		}
		
		fprintf(fp,"Address: ");									//Print Address in binnary format
		for(k=0;k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
	
		}
		address_dec=bin2dec(address,k-1);
		
		fprintf(fp,"   |   ");										//Print selected command
		switch ((char)command)
		{
		case 'R':{
				fprintf(fp,"Command: Read   |   ");
				break;
				 }
		case 'W':{
				fprintf(fp,"Command: Write  |   ");
				break;
				 }
		case 'M':{
				fprintf(fp,"Command: Modify |   ");
				break;
				 }
		case 'F':{
				fprintf(fp,"Command: Flush  |   ");
				break;
				 }
		default:
			break;
		}
		//Calculation of index bits
		if (num_of_flush==0){ways=0;}
		index=(log((double)(cache_size/ways))/log((double)vasi_2))-log((double)words_in_block)/log((double)vasi_2);;
		tag_bits = ram_bits-index;									//Calculation of tag bits
		if(words_in_block>1)
		{
			tag_bits = ram_bits-index-block_offset;
		}
		
		fprintf(fp,"Tag: ");										//Print Tag bits
		for(k=0;k<(tag_bits);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			tag_dec=bin2dec(temp,k-1);
				
			for(k=0;k<50;k++){temp[k]=0;}
		
		fprintf(fp,"  |  ");
		
		fprintf(fp,"Index: ");										//Print index bits
	
		for(k=tag_bits;k<(ram_bits-block_offset);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			
			index_dec=bin2dec(temp,k-1);
			for(k=0;k<50;k++){temp[k]=0;}

		if(block_offset !=0){
		fprintf(fp,"  |  ");
		
		fprintf(fp,"block Offset: ");								//Print block offset bits
		for((k=ram_bits-block_offset);k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
			temp[k]=address[k];
		}
			
			offset_dec=bin2dec(temp,k-1);
			for(k=0;k<50;k++){temp[k]=0;}
		}
		

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!=')'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		fscanf_s(input,"%c",&ch,1);

					switch ((char)command)
		{
		case 'R':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									icycles=read_cycles_cache;
									hit_flag=1;
						
									conductor->use_time=0;
									node_way=conductor->way;
									break;
								}
								else
								{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									compulsory=0;
									conflict=1;
									capacity=0;
									
								}
							}
							else
							{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									if(conductor->valid==0)
									{
										if(miss_flag==0){
										compulsory=1;
										conflict=0;
										capacity=0;
										miss_flag=1;
										}
									}
									else if(conductor->tag!=tag_dec)
									{
										if(miss_flag==0){
										compulsory=0;
										conflict=1;
										capacity=0;
										miss_flag=1;
										}
									}
							}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		case 'W':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==0)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache;
										icycles=write_cycles_cache+read_cycles_cache;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+write_cycles_cache+read_cycles_cache+write_cycles_ram;
										icycles=write_cycles_cache+read_cycles_cache+write_cycles_ram;
									}
									
									hit_flag=1;
									conductor->dirty=1;
									found_ok=1;
									conductor->age=age;
									conductor->use_time=0;
									node_way=conductor->way;
									break;
									
								}
							
							}
							else
							{
								if(conductor->valid==0)
								{
									if((Write_Back_Through==0)&&(Write_Allocate==0))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
										}									}
										if((Write_Back_Through==0)&&(Write_Allocate==1))
										{
											count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
											icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
										if(conductor->dirty==1)
										{
											count_cycles=count_cycles+write_cycles_ram;
										}
									}
									if((Write_Back_Through==1)&&(Write_Allocate==0))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									if((Write_Back_Through==1)&&(Write_Allocate==1))
									{
										count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
										icycles=read_cycles_cache+write_cycles_ram;
									}
									conductor->block_offset[block_offset]=address_dec;
									conductor->tag=tag_dec;
									conductor->valid=1;
									conductor->dirty=1;
									found_ok=1;
									conductor->age=age;
									conductor->use_time=0;
									node_way=conductor->way;
									compulsory=1;
									conflict=0;
									capacity=0;
									break;
							}
						}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again

	if (found_ok==0)
	{
		compulsory=0;
		conflict=0;
		capacity=1;
		if(policy==0)
		{
			fifo=root;
			oldest=NUM_MUL*ram_size+1;
			while(fifo->next!=0)
			{
				if(fifo->index==index_dec)
				{
					if(oldest>fifo->age)
					{
						oldest=fifo->age;
						node_num=fifo->node_num;
					}
				}
				fifo=fifo->next;
			}
			fifo=root;
			while(fifo->node_num!=node_num)
			{
				fifo=fifo->next;
			}
			for(k=0;k<30;k++)
					{
						fifo->block_offset[k]=-1;
					}
			fifo->block_offset[block_offset]=address_dec;
			fifo->valid=1;
			fifo->age=age;
			fifo->tag=tag_dec;
			node_way=fifo->way;
			fifo=root;
		}
		else if(policy==1)
		{
			lru=root;
			oldest=NUM_MUL*ram_size+1;
			while(lru->next!=0)
			{
				if(lru->index==index_dec)
				{
					if(oldest>lru->use_time)
					{
						oldest=lru->use_time;
						node_num=lru->node_num;
					}
				}
				lru=lru->next;
			}
			lru=root;
			while(lru->node_num!=node_num)
			{
				lru=lru->next;
			}
			for(k=0;k<30;k++)
					{
						lru->block_offset[k]=-1;
					}
			lru->block_offset[block_offset]=address_dec;
			lru->valid=1;
			lru->age=age;
			lru->tag=tag_dec;
			node_way=lru->way;
			lru=root;
		}
		else if(policy==2)
		{
			

			random=root;

			while(random->next!=0)
			{
				if(random->index==index_dec)
				{
					random_num=rand() % (num_of_ways);
					if(random_num>=0)
					{
						
						node_num=random->node_num;
						random_num=random_num-1;
					}
				}
				random=random->next;
			}
			random=root;

			random=root;
			while(random->node_num!=node_num)
			{
				random=random->next;
			}
			for(k=0;k<30;k++)
					{
						random->block_offset[k]=-1;
					}
			random->block_offset[block_offset]=address_dec;
			random->valid=1;
			random->age=age;
			random->tag=tag_dec;
			node_way=random->way;
			random=root;
		}

		if((Write_Back_Through==0)&&(Write_Allocate==0))
		{
			count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
			icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
		if(conductor->dirty==1)
		{
			count_cycles=count_cycles+write_cycles_ram;
			icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache+write_cycles_ram;
		}									
		}
		if((Write_Back_Through==0)&&(Write_Allocate==1))
			{
		count_cycles=count_cycles+read_cycles_cache+read_cycles_ram+write_cycles_cache;
				icycles=read_cycles_cache+read_cycles_ram+write_cycles_cache;
					if(conductor->dirty==1)
							{
							count_cycles=count_cycles+write_cycles_ram;
							}
						}
						if((Write_Back_Through==1)&&(Write_Allocate==0))
					{
							count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
							icycles=read_cycles_cache+write_cycles_ram;
						}
				if((Write_Back_Through==1)&&(Write_Allocate==1))
						{
							count_cycles=count_cycles+read_cycles_cache+write_cycles_ram;
							icycles=read_cycles_cache+write_cycles_ram;
						}
	}
				break;
				 }
		case 'M':{
			conductor = root;
				 while(conductor->next != 0)
					{
						if(conductor->index==index_dec)
						{
							if((conductor->tag == tag_dec)&&(conductor->valid!=0))
							{
								if(conductor->block_offset[block_offset]==address_dec)
								{
									count_cycles=count_cycles+read_cycles_cache;
									icycles=read_cycles_cache;
									hit_flag=1;
								
									conductor->use_time=0;
									node_way=conductor->way;
									break;
								}
								else
								{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									compulsory=0;
									conflict=1;
									capacity=0;
									
								}
							}
							else
							{
									if(read_flag==0){
									count_cycles=count_cycles+read_cycles_cache+read_cycles_ram;
									icycles=read_cycles_cache+read_cycles_ram;
									read_flag=1;
									}
									if(conductor->valid==0)
									{
										if(miss_flag==0){
										compulsory=1;
										conflict=0;
										capacity=0;
										miss_flag=1;
										}
									}
									else if(conductor->tag!=tag_dec)
									{
										if(miss_flag==0){
										compulsory=0;
										conflict=1;
										capacity=0;
										miss_flag=1;
										}
									}
							}
						}
						conductor = conductor->next;
					}
    conductor = root;	 //conductor points to root again
				break;
				 }
		
		default:
			break;
		}
		age=age+1;
		

		

		if(hit_flag==1)
		{
			fprintf(fp,"\t(Hit!)\t\t\t\t");
			hit_counter=hit_counter+1;
		}
		else
		{
			fprintf(fp,"\t(Miss!)");
			miss_counter=miss_counter+1;

		
		if(compulsory==1)
		{
			fprintf(fp,"\t(Compulsory)");
		}
		else if(conflict==1)
		{
			fprintf(fp,"\t( Conflict )");
		}
		else if(capacity==1)
		{
			fprintf(fp,"\t( Capacity )");
		}
		}
		if(node_way>-1){
		fprintf(fp,"  |  ");
		
		fprintf(fp,"\t# Way: ");
		
		
		fprintf(fp,"%d",node_way);
		
		}
		else
			{
		fprintf(fp,"  |  ");
		
		fprintf(fp,"\t\t\t");
		
		
		fprintf(fp,"");
		
		}
				fprintf(fp,"\tInstruction Cycles: %d",icycles);
				fprintf(fp,"\n");
		}
		fprintf(fp,"\nTotal Cycles: %d\n",count_cycles);
		fprintf(fp,"\nHit Rate: %.2f %%\n",(hit_counter/(double)(NUM_MUL*ram_size))*100);
		fprintf(fp,"\nMiss Rate: %.2f %%\n",(100-(hit_counter/(double)(NUM_MUL*ram_size))*100));
conductor = root;
	while(conductor->next!=0)
	{
		conductor->use_time=conductor->use_time+1;
		conductor=conductor->next;
	}
	conductor = root;
conductor=root;
while(conductor->next!=0)
{
	tmp=conductor;
	conductor=conductor->next;
	free(tmp);
}
}


int main(){




errno_t errorCode =fopen_s(&output,"Arxeio Dedomenwn","w+");

int flush_count=0;
long int random_num;
int ram_bits;
int cache_bits;
int i=0;
int j=0;
int k=0;
int counter=0;

double checkbase_double;
int checkbase_int;

long int rem[50];
char entoli[4]={'R','W','M','F'};
int random_num2;

parameters_parser();


cache_size=(cache_size_bytes/word_size_bytes);//Cache Size (Entries)
ram_size=(ram_size_bytes/word_size_bytes);



checkbase_double=log((double)word_size_bytes)/log((double)2);
checkbase_int=checkbase_double;








// ============ERROR HANDLING============
	checkbase_double=log((double)word_size_bytes)/log((double)2);
	checkbase_int=checkbase_double;
	if(checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The word size is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	if(cache_size_bytes>ram_size_bytes)
	{
		printf("ERROR!: The size of Cache MUST NOT exceed the size of RAM\n");		//cache size exceeds ram size error
		system("pause");
		return 1;
	}
	if(ram_size_bytes<=0)
	{
		printf("ERROR!: The size of Ram MUST NOT be 0 or below\n");		//cache size exceeds ram size error
		system("pause");
		return 1;
	}
	
	if(cache_size_bytes<=0)
	{
		printf("ERROR!: The size of Cache MUST NOT be 0 or below\n");		//cache size exceeds ram size error
		system("pause");
		return 1;
	}
	if(num_of_flush>=ram_size*NUM_MUL)
	{
		printf("ERROR!: The amount of flushes MUST NOT exceed the amount of references\n");		//amount of flushed exceeds # references error
		system("pause");
		return 1;
	}
	checkbase_double=log((double)ram_size_bytes)/log((double)2);
	checkbase_int=checkbase_double;
	if(checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The size of RAM is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	checkbase_double=log((double)cache_size_bytes)/log((double)2);
	checkbase_int=checkbase_double;
	if(checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The size of Cache is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	checkbase_double=log((double)words_in_block)/log((double)2);
	checkbase_int=checkbase_double;
	if(words_in_block==1){checkbase_double=1;
	checkbase_int=1;;}
	if(checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The amount of words in each block is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	if(words_in_block<=0)
	{
		printf("ERROR!: The amount of words in each block is a negative number\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	checkbase_double=log((double)num_of_ways)/log((double)2);
	checkbase_int=checkbase_double;
	if(num_of_ways!=0 && checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The amount of ways is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	if(type_of_cache==2 && num_of_ways<=0)
	{
		printf("ERROR!: The amount of ways is a negative number or zero\n");							//Not a power of 2 error
		system("pause");
		return 1;
	}
		if(type_of_cache<0 || type_of_cache>2)
	{
		printf("ERROR!: Check the type of cache\n");							//Not a power of 2 error
		system("pause");
		return 1;
	}
	if(((cache_size/num_of_ways/words_in_block)<1)&&(type_of_cache==2))
	{
		printf("ERROR!: The size of Cache is too small\n");		
		system("pause");
		return 1;
	}

ram_bits=log((double)ram_size)/log((double)vasi_2);			//calculation of Ram Bits (idiotita logarithmwn => log2(num)=log10(num)/log10(2))
cache_bits=log((double)cache_size)/log((double)vasi_2);		//calculation of Cache Bits


printf("Size of RAM : %d Bytes => %d Entries\n",ram_size_bytes,ram_size);				//Print Messages for info
printf("Size of Cache : %d Bytes => %d Entries \n",cache_size_bytes,cache_size);
printf("# Bits of RAM Address is : %d \n",ram_bits);
switch (type_of_cache)																	//Prints the type of Cache
{
	case 0:{
		 printf("Type of Cache: Direct Mapped\n");

		 break;
	 }
	case 1:{
		 printf("Type of Cache: Fully Assosiative\n");

		 break;
	 }
	case 2:{
		 printf("Type of Cache: %d-Way Assosiative\n",num_of_ways);

		 break;
	 }

}


printf("Each block has %d word (Word Size: %d Byte)\n",words_in_block,word_size_bytes);		//Prints the amount and size of words in block

		srand((int)time(NULL));
		for (i = 0; i <(NUM_MUL*ram_size); i++)						//Data File generator
			{
			counter=counter+1;		//counter of flushes
			random_num=rand() % ((int)(ram_size)-1);	//generate random number for reference
			dec2bin(random_num,rem);					//transform number to binary
			random_num2=rand()%3;						//random number for command
			if((num_of_flush!=0)&&((counter)>=((NUM_MUL*ram_size)/num_of_flush)))	//controls the frequency of flushes
			{
				random_num2=rand()%4;
				if(random_num2==3)
				{
					counter=0;
					fprintf(output,"%c",entoli[random_num2]);	//prints the letter that matches the command
					fprintf(output,"\n");
					continue;
				
				}
				
			}
			
			else{random_num2=rand()%3;}
			
			fprintf(output,"%c ",entoli[random_num2]);
			if(random_num2!=3)
			{
				 for(j=ram_bits-1;j>=0;j--)		//we print the binary backwords because it comes from the function in backwords
					{ 
				 fprintf(output,"%ld",rem[j]);}		//printing address in file
			
			fprintf(output,"\t (%d)",random_num);
			}
			fprintf(output,"\n");


			}

printf("Arxeio Dedomenwn has been generated!\n");		//message that says that the file has been generated

fclose(output);
switch (type_of_cache)					//switch that calls the function that has been selected
{
	case 0:{
		 direct_mapped(ram_bits,cache_bits);
		 break;
	 }
	case 1:{
		 fully_assosiative(ram_bits,cache_bits);
		 break;
	 }
	case 2:{
		n_way(ram_bits,cache_bits);	 
			break;
	 }
		   

}



printf("Arxeio Dedomenwn has been parsed and Arxeio Eksodou has been generated!\n");	//Finall output file has been generated

fclose(fp);
fclose(input);
system("pause");

return 0;

}//end