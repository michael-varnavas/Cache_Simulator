#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<conio.h>
#include <time.h>

#define NUM_MUL 3			//Arithmos pou pollaplasiazw to cache_size sto loop otan kamnw generate to arxeio

#define word_size_bytes 4 //Size in bytes
#define ram_size_bytes 1024		//Ram Size (Bytes)
#define ram_size (ram_size_bytes/word_size_bytes) //Ram Size (Entries)
#define cache_size_bytes 64		//Cache Size Bytes
#define cache_size (cache_size_bytes/word_size_bytes) //Cache Size (Entries)
#define num_of_flush 5		//Minimum amount of Flushes
#define words_in_block 4	//Amount of words in each block
#define type_of_cache 0		//0 = Direct Mapped. 1= fully Associative. 2= N-way Associative
#define num_of_ways 2		//In case of N-way, # of ways
#define vasi_2 2			//Help variable for logarithm



FILE *output;				//Pointers of files that we use
FILE *input;
FILE *fp;
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
int address[50];													//Array to temporary hold the binnary address
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block 
int i=0;
int j=0;
int k=0;
int index;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable

		if((char)command=='F')
		{
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
		}
		
		fprintf(fp,"  |  ");
		
		fprintf(fp,"Index: ");										//Print index bits
	
		for(k=tag_bits;k<(ram_bits-block_offset);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		if(block_offset !=0){
		fprintf(fp,"  |  ");										//Print block offset bits
		
		fprintf(fp,"block Offset: ");
		for((k=ram_bits-block_offset);k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		}
		fprintf(fp,"\n");

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!='\n'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		//fscanf_s(input,"%c",&ch,1);

}
}

void fully_assosiative(int ram_bits,int cache_bits){
int ch;																//Variable decleration
int command;
int address[50];													//Array to temporary hold the binnary address
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block 
int i=0;
int j=0;
int k=0;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable
		if((char)command=='F')
		{
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
		}
		
		fprintf(fp,"  |  ");
		
		
		if(block_offset !=0){
	
		
		fprintf(fp,"block Offset: ");								//Print block offset bits
		for((k=ram_bits-block_offset);k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		}
		fprintf(fp,"\n");

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!=')'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		fscanf_s(input,"%c",&ch,1);

}
}

void n_way(int ram_bits,int cache_bits){
int ch;																//Variable decleration
int command;
int address[50];													//Array to temporary hold the binnary address
int tag_bits;
int block_offset=log((double)words_in_block)/log((double)vasi_2);	//Calculation of block offset
int i=0;
int j=0;
int k=0;
int index;
long int random_num;
errno_t errorCode =fopen_s(&input,"Arxeio Dedomenwn","r+");			//Opening a file.
errorCode =fopen_s(&fp,"Arxeio Eksodou","w+");						//Opening a file. Mode: Write
srand((int)time(NULL));												//rand() is based on time so the numbers are better shuffled
for (i = 0; i <(NUM_MUL*ram_size); i++)								//This for statement will loop for all the range of possible address calls multiplied by a defined constant
	{
		fscanf_s(input,"%c",&command,1);							//Scanning the first character of the line and saving it in command variable

		if((char)command=='F')
		{
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
		index=(log((double)(cache_size/num_of_ways))/log((double)vasi_2))-log((double)words_in_block)/log((double)vasi_2);;
		tag_bits = ram_bits-index;									//Calculation of tag bits
		if(words_in_block>1)
		{
			tag_bits = ram_bits-index-block_offset;
		}
		
		fprintf(fp,"Tag: ");										//Print Tag bits
		for(k=0;k<(tag_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		
		fprintf(fp,"  |  ");
		
		fprintf(fp,"Index: ");										//Print index bits
	
		for(k=tag_bits;k<(ram_bits-block_offset);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		if(block_offset !=0){
		fprintf(fp,"  |  ");
		
		fprintf(fp,"block Offset: ");								//Print block offset bits
		for((k=ram_bits-block_offset);k<(ram_bits);k++){
			
			fprintf(fp,"%d",address[k]);
		}
		}
		fprintf(fp,"  |  ");
		
		fprintf(fp,"# Way: ");
		
		random_num=rand() % (num_of_ways) + 1;
		fprintf(fp,"%d",random_num);
		fprintf(fp,"\n");

		fscanf_s(input,"%c",&ch,1);
		while((char)ch!=')'){fscanf_s(input,"%c",&ch,1);}			//We use this While loop to skip unnesesary charachters in the line
		fscanf_s(input,"%c",&ch,1);

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
	if(checkbase_double/checkbase_int != 1)
	{
		printf("ERROR!: The amount of ways is not a power of 2\n");			//Not a power of 2 error
		system("pause");
		return 1;
	}
	if(num_of_ways<=0)
	{
		printf("ERROR!: The amount of ways is a negative number or zero\n");							//Not a power of 2 error
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