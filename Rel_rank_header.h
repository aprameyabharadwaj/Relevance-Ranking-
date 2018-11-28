#include<stdio.h>
#include<stdlib.h>
struct tales 
{
	int no_of_tales;
	char* ptr_tale[10];//hardcoding to approx 350 tales
};
struct tales* insert_tales(struct tales** ptr_ptr_mytales);
void all_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat);
void first_occurences(struct tales** ptr_ptr_mytales,char* ptr_mypat);
void rank_tales(struct tales** ptr_ptr_mytales,char* ptr_mypat);
void delete_tales(struct tales** ptr_ptr_mytales);
void disp_tales(struct tales** ptr_ptr_mytales);
void create_SA(char* txt,int tale_no);
void create_suffix_tree(struct tales** ptr_ptr_mytales);	
int return_index(char *pat,struct tales** ptr_ptr_mytales,int tale_no);


