#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define TRUE 1
#include "asgn3_header.h"
int ptr_SA[10][100000];
int rank[10][2];
bool all_occurences_called=false;
bool first_occurences_called=false;

void create_SA(char* txt,int tale_no)
{
	int len=strlen(txt);
	int index;
	int word=1;

	for(index=0;index<len;index++)
	{
		if(isalpha(txt[index]))
		{
			ptr_SA[tale_no][word]=index;

			word++;
			while(isalpha(txt[index]))
			{	index++;	}
		}

		if(ispunct(txt[index]))
		{
			ptr_SA[tale_no][word]=index;
			word++;
		}
	}

	ptr_SA[tale_no][0]=word;



	int i, j;
	for(i=1;i<word;i++)
 	{
       		for (j=1;j<word-i;j++)
           	{
              		if(strncasecmp(txt+ptr_SA[tale_no][j],txt+ptr_SA[tale_no][j+1],2)>0)
			{
				int temp=ptr_SA[tale_no][j];
				ptr_SA[tale_no][j]=ptr_SA[tale_no][j+1];
				ptr_SA[tale_no][j+1]=temp;
			}
		}
	}

}
void create_suffix_tree(struct tales** ptr_ptr_mytales)
{
	int i=0;
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		create_SA((*ptr_ptr_mytales)->ptr_tale[i],i);
	}
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		rank[i][0]=i;
		rank[i][1]=0;
	}
}
struct tales* insert_tales(struct tales **ptr_ptr_mytales)
{
	int num_of_tales=0;
	int i=0;
	char k;
	ptr_ptr_mytales=(struct tales**)malloc(sizeof(struct tales*));
	(*ptr_ptr_mytales)=(struct tales*)malloc(sizeof(struct tales));

	FILE * fp = fopen("dataset.txt", "r");
	char c;
	for(int i = 0; i < 10; i++){
		(*ptr_ptr_mytales)->ptr_tale[i]=(char*)malloc(sizeof(char)*100000);
		fscanf(fp, "%[^\n]", ((*ptr_ptr_mytales)->ptr_tale[i]));
		fscanf(fp, "%c", &c);
	}

	fclose(fp);

	(*ptr_ptr_mytales)->no_of_tales=10;



	return *ptr_ptr_mytales;
}


int return_index(char *pat,struct tales** ptr_ptr_mytales,int tale_no)
{
	int m = strlen(pat);

	int l=1;
	int r=ptr_SA[tale_no][0];
	char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];
	while(l<=r && l<=ptr_SA[tale_no][0] && 1<=r)
    	{
        	int mid=l+(r-l)/2;
        	if((tolower(pat[0]))>(tolower(txt[ptr_SA[tale_no][mid]])))
              	{
			l=mid+1;
		}
		else if((tolower(pat[0]))<(tolower(txt[ptr_SA[tale_no][mid]])))
              	{
			r=mid-1;
		}
		else if((tolower(pat[0]))==(tolower(txt[ptr_SA[tale_no][mid]])))
              	{
     			return mid;
		}
		else
			return -1;
        }
}
void all_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{

	all_occurences_called=true;

	int tale_no=0;
	int m=strlen(ptr_mypat);
	for(tale_no=0;tale_no<(*ptr_ptr_mytales)->no_of_tales;tale_no++)
	{

		int index=return_index(ptr_mypat,ptr_ptr_mytales,tale_no);
		if(index!=-1)
		{

			char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];

			const char *PATTERN1 = "'";
    		const char *PATTERN2 = "'";

    		char *title = NULL;
    		char *start, *end;

    		if ( start = strstr( txt, PATTERN1 ) )
    		{
     		   start += strlen( PATTERN1 );
    		    if ( end = strstr( start, PATTERN2 ) )
      			  {
        			    title = ( char * )malloc( end - start + 1 );
            			memcpy( title, start, end - start );
          				title[end - start] = '\0';
        		}
    		}
			//	printf("---%s---\n", title);
			int left=index-1;
			int right=index+1;
			while((tolower(ptr_mypat[0]))==(tolower(txt[ptr_SA[tale_no][left]])) && 0<left)//left index
			{	left--;
			}
			while((tolower(ptr_mypat[0]))==(tolower(txt[ptr_SA[tale_no][right]])) && 0<left)//right index
			{	right++;
			}


			int i;
			for(i=left;i<=right;i++)
			{
				if(strncasecmp(ptr_mypat,txt+ptr_SA[tale_no][i],m)==0)
				{

					rank[tale_no][1]=rank[tale_no][1]+2;
				}
			}

			if(strcasecmp(ptr_mypat,title)==0)
			{

				rank[tale_no][1]=rank[tale_no][1]+1000;

			}
			if(strstr(title, ptr_mypat))
			{

				rank[tale_no][1]=rank[tale_no][1]+100;
			}


		}


	}
}
void first_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{
	first_occurences_called=true;
	//search each tale
	int tale_no=0;
	int ptr_len=strlen(ptr_mypat);
	int pat_words[50];
	int index=0;
	int word=0;
	for(index=0;index<ptr_len;index++)
	{
		if(isalpha(ptr_mypat[index]))
		{

			pat_words[word]=index;
			word++;
			while(isalpha(ptr_mypat[index]))
			{	index++;	}
		}

		if(ispunct(ptr_mypat[index]))
		{
			pat_words[word]=index;
			word++;
		}
	}

	for(tale_no=0;tale_no<(*ptr_ptr_mytales)->no_of_tales;tale_no++)
	{
		char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];

			const char *PATTERN1 = "'";
    		const char *PATTERN2 = "'";

    		char *title = NULL;
    		char *start, *end;

    		if ( start = strstr( txt, PATTERN1 ) )
    		{
     		   start += strlen( PATTERN1 );
    		    if ( end = strstr( start, PATTERN2 ) )
      			  {
        			    title = ( char * )malloc( end - start + 1 );
            			memcpy( title, start, end - start );
          				title[end - start] = '\0';
        		}
    		}

		int substring=pat_words[0];
		bool longest_substring_found=false;
		int longest_substring_length=0;
		int longest_substring_pat_word=0;
		int longest_substring_text_word=0;

		while(substring<word && !longest_substring_found)
		{

			int index=return_index(ptr_mypat+pat_words[substring],ptr_ptr_mytales,tale_no);
			if(index!=-1)
			{

				int left=index-1;
				int right=index+1;
				while((tolower((ptr_mypat+pat_words[substring])[0]))==(tolower(txt[ptr_SA[tale_no][left]])) && 0<left)
				{

					left--;
				}
				while((tolower((ptr_mypat+pat_words[substring])[0]))==(tolower(txt[ptr_SA[tale_no][right]])) && 0<left)
				{

					right++;
				}

				int i;
				for(i=left;i<=right;i++)
				{
					if(substring==0 && strncasecmp(ptr_mypat,txt+ptr_SA[tale_no][i],strlen(ptr_mypat))==0)
					{
							longest_substring_found=true;
							longest_substring_length=strlen(ptr_mypat);
							longest_substring_pat_word=pat_words[substring];
							longest_substring_text_word=i;

							rank[tale_no][1]++;
							break;
					}
					int m=strlen(ptr_mypat+pat_words[substring]);
					int word_length=pat_words[substring+1]-pat_words[substring];


					while(strncasecmp(ptr_mypat+pat_words[substring],txt+ptr_SA[tale_no][i],m)!=0 && m>0)
					{
						m--;
					}

					if(longest_substring_length<m && strncasecmp(ptr_mypat+pat_words[substring],txt+ptr_SA[tale_no][i],m)==0)
					{
						longest_substring_length=m;
						longest_substring_pat_word=pat_words[substring];
						longest_substring_text_word=i;
						if(word_length==m)
						{
						rank[tale_no][1]++;
						}
					}
				}
			}
			substring++;
		}

		if(longest_substring_length>0)
		{

			printf("TITLE:%s\n",title);
			printf("Pattern:(%.*s)\n",longest_substring_length,ptr_mypat+longest_substring_pat_word);

			if(ptr_SA[tale_no][longest_substring_text_word]==0)
			{
			printf("...%.*s...\n\n",3*longest_substring_length,txt+ptr_SA[tale_no][longest_substring_text_word]);
			}
			else
			{
			printf("...%.*s...\n\n",3*longest_substring_length,txt+ptr_SA[tale_no][longest_substring_text_word]-longest_substring_length);
		}


			rank[tale_no][1]++;
		}
	}

}
void rank_tales(struct tales** ptr_ptr_mytales,char* ptr_mypat)
{
	if(all_occurences_called==false)
		all_occurences(ptr_ptr_mytales,ptr_mypat);
	if(first_occurences_called==false)
		first_occurences(ptr_ptr_mytales,ptr_mypat);



	int i,j;
	for(i=0;i<(*ptr_ptr_mytales)->no_of_tales;i++)
 	{
       		for (j=0;j<(*ptr_ptr_mytales)->no_of_tales-i;j++)
           	{
			if (rank[j][1]<=rank[j+1][1])
              		{
				int temp=rank[j][0];
				rank[j][0]=rank[j+1][0];
				rank[j+1][0]=temp;
				temp=rank[j][1];
				rank[j][1]=rank[j+1][1];
				rank[j+1][1]=temp;
			}
		}
	}

	printf("Rank of Tales\n\n");
	for (j=0;j<(*ptr_ptr_mytales)->no_of_tales;j++)
        {
		int tale_no=rank[j][0];
		int relevance=rank[j][1];
		if(relevance!=0)
		{

			char* txt=(*ptr_ptr_mytales)->ptr_tale[tale_no];

			int c=0;

			const char *PATTERN1 = "'";
    		const char *PATTERN2 = "'";

    		char *title = NULL;
    		char *start, *end;

    		if ( start = strstr( txt, PATTERN1 ) )
    		{
     		   start += strlen( PATTERN1 );
    		    if ( end = strstr( start, PATTERN2 ) )
      			  {
        			    title = ( char * )malloc( end - start + 1 );
            			memcpy( title, start, end - start );
          				title[end - start] = '\0';
        		}
    		}
			printf("Relevance: %d Title: %s\n",relevance,title);
		}
	}


}



void disp_tales(struct tales** ptr_ptr_mytales)
{
	printf("No of tales:%d\n\n",((*ptr_ptr_mytales)->no_of_tales));
	int i=0;
	for(i=0;i<((*ptr_ptr_mytales)->no_of_tales);i++)
	{
		printf("%s\n\n",((*ptr_ptr_mytales)->ptr_tale[i]));
	}
}

void delete_tales(struct tales** ptr_ptr_mytales)
{
	free((*ptr_ptr_mytales));
}






int getWords(char *base, char target[50][50])
{
	int n=0,i,j=0;

	for(i=0;TRUE;i++)
	{
		if(base[i]!=' '){
			target[n][j++]=base[i];
		}
		else{
			target[n][j++]='\0';//insert NULL
			n++;
			j=0;
		}
		if(base[i]=='\0')
				break;
	}
	return n;

}

int main()
{

	struct tales *ptr_mytales;

	ptr_mytales=insert_tales(&ptr_mytales);


	create_suffix_tree(&ptr_mytales);


	char* ptr_mypat=(char*)malloc(sizeof(char)*100);
	ptr_mypat=" The Death of Bunny Munro";



		int n; //number of words
		int i; //loop counter

		char arr[50][50];

		n=getWords(ptr_mypat,arr);

		for(i=0;i<=n;i++)
		{


			all_occurences(&ptr_mytales,arr[i]);

	}



	printf("Query String:%s\n\n",ptr_mypat);

	all_occurences(&ptr_mytales,ptr_mypat);

	first_occurences(&ptr_mytales,ptr_mypat);

	rank_tales(&ptr_mytales,ptr_mypat);

	disp_tales(&ptr_mytales);

		//clear memory
	delete_tales(&ptr_mytales);

	return 0;
}
