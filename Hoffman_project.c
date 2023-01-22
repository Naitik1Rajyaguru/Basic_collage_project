//DATA COMPRESSING USING HUFFMAN CODDING
/*
PARTICIPANTS :

20BCE233
20BCE240
20BCE173

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 

struct node{
   char ch;
   int ct;
   struct node* left;
   struct node* right;
};

//FOR MIN HEAP TREE
struct heap_node{
    char chr;
    int fre;
    struct node* add;
};
 
struct node* huffman_head=NULL;
struct heap_node min_heap[128];
 
int heap_sz=0;

//FOR FIND PARENT HEAP
int parent_heap(int x){
    return (x-1)/2;
}
int idx=0;


//FOR INSERT ELEMENT IN THE MINIMUM HEAP
void min_insert(char ch, int freq,struct node*address){        // :- if parents are gratter then we will swap them with their child.
 
    min_heap[heap_sz].chr=ch; //STORE CHARACTER 
    min_heap[heap_sz].fre=freq; //STORE FREQUENCY
    min_heap[heap_sz].add=address; //STORE ADDRESS
    heap_sz++;
    int i=heap_sz-1;
    
    while(i!=0 && min_heap[parent_heap(i)].fre>min_heap[i].fre){
        //SWAP THE ELEMENTS IN THE HEAP TREE 
        int temp_ch=min_heap[parent_heap(i)].chr;
        char temp_freq=min_heap[parent_heap(i)].fre;
        struct node* temp=min_heap[parent_heap(i)].add;
        
        min_heap[parent_heap(i)].chr=min_heap[i].chr;
        min_heap[parent_heap(i)].fre=min_heap[i].fre;
        min_heap[parent_heap(i)].add=min_heap[i].add;
        
        min_heap[i].chr=temp_ch;
        min_heap[i].fre=temp_freq;
        min_heap[i].add=temp;
        
        i=parent_heap(i);
    }
}

//HEAPIFY FOR MAKE HEAP TREE
void heapify(int i){
    int smallest=i;
    int l=2*i+1;
    int r=2*i+2;
    
    if(l<heap_sz && min_heap[smallest].fre>min_heap[l].fre){
        smallest=l;
    }
    
    if(r<heap_sz && min_heap[smallest].fre>min_heap[r].fre){
        smallest=r;
    }
    
    if(smallest!=i){
        //IF SMALLEST NOT EQUAL TO I THAN SWAP 
        int temp_ch=min_heap[smallest].chr;
        char temp_freq=min_heap[smallest].fre;
        struct node* temp=min_heap[smallest].add;
        min_heap[smallest].chr=min_heap[i].chr;
        min_heap[smallest].fre=min_heap[i].fre;
        min_heap[smallest].add=min_heap[i].add;
        min_heap[i].chr=temp_ch;
        min_heap[i].fre=temp_freq;
        min_heap[i].add=temp;
        heapify(smallest);
    }
}
 
 
//BUILD TREE FOR CREATE CODE FOR CHARACTER USING MIN HEAP TREE
void build_tree(){              // after this we have min_heap as a just our top most element.
     while(heap_sz!=1){
         struct node* root=(struct node*)malloc(sizeof(struct node));
         struct node* lf=(struct node*)malloc(sizeof(struct node));
         struct node* rg=(struct node*)malloc(sizeof(struct node));
         
         lf->ct=min_heap[0].fre;
         lf->ch=min_heap[0].chr;
         
         if(min_heap[0].add!=NULL) 
            lf=min_heap[0].add;
            
         min_heap[0].chr=min_heap[heap_sz-1].chr;
         min_heap[0].fre=min_heap[heap_sz-1].fre;
         min_heap[0].add=min_heap[heap_sz-1].add;
         heap_sz--;
         heapify(0);
         
         rg->ct=min_heap[0].fre;
         rg->ch=min_heap[0].chr;
         
         if(min_heap[0].add!=NULL) 
             rg=min_heap[0].add;
             
         min_heap[0].chr=min_heap[heap_sz-1].chr;
         min_heap[0].fre=min_heap[heap_sz-1].fre;
         min_heap[0].add=min_heap[heap_sz-1].add;
         
         heap_sz--;
         heapify(0);
         root->ch=0;
         root->ct=(lf->ct)+(rg->ct);
         root->left=lf;
         root->right=rg;
         
         if(lf->ch!=0){
             lf->left=NULL;
             lf->right=NULL;
         }
         
         if(rg->ch!=0){
             rg->left=NULL;
             rg->right=NULL;
         }
         //RECURSIVE CALL
         min_insert(root->ch,root->ct,root);
         huffman_head=root;
     }
}

//CREATE CHARACTER TABLE FOR USER
void char_code(char table[][100001],char arr[],struct node* temp){
     if(temp->left!=NULL){
        char arr2[100001];
        int n=strlen(arr);
        
        for(int i=0; i<n; i++){
            arr2[i]=arr[i];
        }
        arr2[n]='0';
      
        char_code(table,arr2,temp->left);
     }
     
     if(temp->right!=NULL){
        char arr2[100001];
        int n=strlen(arr);
        for(int i=0; i<n; i++){
            arr2[i]=arr[i];
        }
        arr2[n]='1';
      
        char_code(table,arr2,temp->right);
     }
    
     if(temp->right==NULL && temp->left==NULL){
        table[idx][0]=temp->ch;
       
        int n=strlen(arr);
        for(int i=0; i<n; i++){
            table[idx][i+1]=arr[i];
         
        }
        idx++;
     }
     return;
}
 
 
int main(){
    char data[100];
    printf("\n-------------------------------------------------------------------------------\n");
    printf("Enter the Data : ");
 
    gets(data); //GET DATA FROM USER
    int freq[128]={0}; //FOR COUNT THE FREQUENCY OF CHARACTER
    int sz_data=strlen(data);
    
    //COUNT THE FREQUENCY 
    for(int i=0; i<sz_data; i++){
        freq[data[i]]++;
    }
    int no_nodes=0;
    
    // TOTAL NO OF DISTINCT CHARACTER
    for(int i=0; i<128; i++){
        if(freq[i]!=0) no_nodes++;
    }
    
    //INSERTING ELEMENT IN THE MIN HEAP TREE
    for(int i=0; i<128; i++){
      if(freq[i]!=0){
        min_insert(i, freq[i],NULL);
      }
    }
    /*for(int i=0; i<heap_sz ; i++){
		printf("%c-%d ", min_heap[i].chr , min_heap[i].fre);
	}
	printf("\n");*/
    build_tree();  //BUILD A TREE FOR CREATE CODE FOR CHARACTER USING MIN HEAP TREE
	/*for(int i=0; i<heap_sz ; i++){
		printf("%c-%d ", min_heap[i].chr , min_heap[i].fre);
	}
	printf("\n");*/
    char table[no_nodes][100001]; //FOR STORE THE COMPRESS DATA
    char arr[100001]; 
    struct node* temp=huffman_head;
    
    //CREATE A TABLE FOR COMPRESS DATA
    char_code(table,arr,temp);
    printf("-------------------------------------------------------------------------------\n");
    printf("Compression Data Table : \n");
    printf("character\tcompress data\n");
    //PRINT TABLE FOR CHAR AND ITS COMPRESSING DATA 
    for(int i=0; i<no_nodes; i++){
        printf("%-20c",table[i][0]);
        int sz=strlen(table[i]);
        for(int j=1; j<sz; j++){
            printf("%c",table[i][j]);
        }
        printf("\n");
    }
    printf("\n-------------------------------------------------------------------------------\n\n");
    printf("Compressed Data : ");
    //FOR PRINT COMPRESSED DATA
    for(int i=0; i<sz_data; i++){
        int temp=data[i];
        for(int i=0; i<no_nodes; i++){
            if(temp==table[i][0]){
                int sz=strlen(table[i]);
                for(int j=1; j<sz; j++){
                    printf("%c",table[i][j]);
                }
            }
        }
    }
  printf("\n-------------------------------------------------------------------------------\n");
}

/*

OUTPUT

-------------------------------------------------------------------------------
Enter the Data : welcome in nirma
-------------------------------------------------------------------------------
Compression Data Table : 
character       compress data
n                   000
c                   0010
l                   0011
i                   010
o                   0110
r                   0111
e                   100
                    101
m                   110
a                   1110
w                   1111

-------------------------------------------------------------------------------

Compressed Data : 111110000110010011011010010101000010100001001111101110
-------------------------------------------------------------------------------

*/