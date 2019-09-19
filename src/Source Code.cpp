#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static int resi = 1;
//===================== STRUCT LL =========================
struct node1 
{
	int resi;
	char nama_pengirim1[30],asal1[30];
	char nama_penerima1[30],tujuan1[30];
	char telp_pengirim1[13],telp_penerima1[13];
	char kode_asal1[4],kode_tujuan1[4];
	int lama_pengiriman1;
    struct node1 *next;
};
typedef struct node1 node1;
//================ STRUCT CIRCULAR LL =====================
struct node2 
{
	int resi;
	char nama_pengirim2[30],asal2[30];
	char nama_penerima2[30],tujuan2[30];
	char telp_pengirim2[13],telp_penerima2[13];
	char kode_asal2[4],kode_tujuan2[4];
	int lama_pengiriman2;
	struct node2 *next;
};
typedef struct node2 node2;
//=================== STRUCT QUEUE =======================
struct node3
{
	int no_resi;
	char nama_pengirim3[30],asal3[30];
	char nama_penerima3[30],tujuan3[30];
    char telp_pengirim3[13],telp_penerima3[13];
    char kode_asal3[4],kode_tujuan3[4];
	int lama_pengiriman3;
	int no_antri;
   struct node3 *next;
};
typedef struct node3 node3;
struct queue{
	int count;
	int jumlah;
	int no_resi;
   node3 *front;
   node3 *rear;
};
typedef struct queue queue;
//==================== FUNCTION LL =======================
node1 *createNode(void);
void insertNode(node1 **head, node1 *pPre, node1 *pNew);
void deleteNode(node1 **head, node1 *pPre, node1 *pCur);
void tambah_paket1(node1 **head);
void tampilkan_paket1(node1 *head);
void hapus_paket1(node1 **head, node2 **phead);
//============== FUNCTION CIRCULAR LL ====================
void tambah_paket2(node2 **phead, node2 *pPre, node2 *pNew);
void tampilkan_paket2(node2 *phead);
void hapus_paket2(node2 **phead,queue *myQueue);
//================== FUNCTION QUEUE ======================
queue createQueue(void);
void hapus_paket3(queue *myQueue);
void destroy(queue *myQueue);
void tampilkan_paket3(queue myQueue);
void barangterkirim(queue *myQueue);
//========================================================
void header();
void gotoxy(int x, int y)
	{
		COORD k = {x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), k);
	}
//================== MAIN FUNCTION =======================
int main ()
{
	node1 *head=NULL;
	node3 *Head=NULL;
	node2 *phead=NULL;
	int pilih;
   queue myQueue;
   myQueue=createQueue();
	
 do
 	{ 
 	system("cls");
 	header();
	gotoxy (3,10);printf("1. Input Data Paket\n");
	gotoxy (3,11);printf("2. Tampil Data Paket\n");
	gotoxy (3,12);printf("3. Proses Paket ke Sorting\n");
	gotoxy (3,13);printf("4. Menampilkan Sorting Paket\n");
	gotoxy (3,14);printf("5. Proses ke Kurir\n");
	gotoxy (3,15);printf("6. Paket yang Belum Terkirim\n");
	gotoxy (3,16);printf("7. Mengirim Paket\n");
	gotoxy (3,17);printf("8. Jumlah Barang Terkirim\n");
	gotoxy (3,18);printf("9. Keluar Program\n\n");
	gotoxy (55,14);printf("Masukkan Pilihan : ");
	fflush(stdin);
	scanf("%d", &pilih);
	if(pilih == 1){
		tambah_paket1(&head);
		getch();
	}
	else if (pilih == 2){
		tampilkan_paket1(head);
		getch();
	}
	else if (pilih == 3){
		hapus_paket1(&head,&phead);
		getch();
	}
	else if (pilih == 4){
		tampilkan_paket2(phead);
		getch();
	}
	else if (pilih == 5){
		hapus_paket2(&phead, &myQueue);
		getch();
	}
	else if (pilih == 6){
		tampilkan_paket3(myQueue);
		getch();
	}	
	else if (pilih == 7){
		hapus_paket3(&myQueue);
		getch();
	}
	else if (pilih == 8){
		barangterkirim(&myQueue);
		getch();
	}			
	}while (pilih != 9);
	gotoxy(1,22);exit(0);
}
//========================================================
node1 *createNode(void){					
  node1 *ptr;

  ptr = (node1 *)malloc(sizeof(node1));		
  return(ptr);								
}
//========================================================
	void header()
		{			
			//Looping tampilkan Border Horizontal
			for(int x_=0; x_<80; x_++){
				for (int y_=0; y_<7; y_+=6){
					gotoxy (x_,y_); printf("\xB2");
				}
			}
			//Looping tampilkan Border Vertikal
			for (int y_=0; y_<22; y_++){
				for (int x_=0; x_<80; x_+=79){
					gotoxy (x_,y_); printf("\xB2");
				}
			}
			//Looping tampilkan Border 
			for (int y_=8; y_<21; y_++){
				for (int x_=48; x_<50; x_++){
					gotoxy (x_,y_); printf("\xB2");
				}
			}			
			//Looping tampilkan border badan
			for(int x_=1; x_<79; x_++){
				for(int y_=7; y_<22; y_+=14){
					gotoxy (x_,y_); printf("\xB2");
				}
			}					
			gotoxy (33,2); printf("JAHER EKSPEDISI");
			gotoxy (26,3); printf("FINAL PROJECT STRUKTUR DATA");
			gotoxy (17,4); printf("DOSEN PENGAMPU : FAWWAZ ALI AKBAR S.KOM M.KOM");
		}
//========================================================
queue createQueue(void)
{
 queue myQueue;

 myQueue.jumlah=0;
 myQueue.no_resi=1;
 myQueue.count=0;
 myQueue.front=NULL;
 myQueue.rear=NULL;
 return(myQueue);
}
//==================== FUNCTION ==========================
//------------------- INSERT NODE ------------------------
void insertNode(node1 **head, node1 *pPre, node1 *pNew)
{ 
    if (pPre == NULL)
	{								  	
	    pNew -> next = *head;						
       *head = pNew;								
    }
    else 
	{ 	
       pNew -> next = pPre -> next;		
       pPre -> next = pNew;			
   }
}
//------------------- DELETE NODE ------------------------
void deleteNode(node1 **head, node1 *pPre, node1 *pCur) 
{											
	if (pPre == NULL)				 
	   *head = pCur -> next;		
	else							
       pPre -> next = pCur -> next;	
	  free(pCur);						
}
//------------------- INPUT PAKET ------------------------
void tambah_paket1(node1 **head)
{      
  node1 *pTemp;
  pTemp = (node1 *)malloc(sizeof(node1));
  char nama_pengirim1[30],asal1[30];
  char nama_penerima1[30],tujuan1[30];
  char telp_pengirim1[13],telp_penerima1[13];
  char kode_asal1[4], kode_tujuan1[4];
  int lama_pengiriman1;			
  
  system("cls");
  
  //Looping tampilkan Border Horizontal
	for(int x_=0; x_<80; x_++){
		for (int y_=0; y_<5; y_+=4){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan Border Vertikal
	for (int y_=0; y_<21; y_++){
		for (int x_=0; x_<80; x_+=79){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan Border 
	for (int y_=5; y_<19; y_++){
		for (int x_=39; x_<41; x_++){
			gotoxy (x_,y_); printf("\xB2");
		}
	}			
	//Looping tampilkan border badan
	for(int x_=1; x_<79; x_++){
		for(int y_=4; y_<19; y_+=14){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan border badan
	for(int x_=1; x_<79; x_++){
		for(int y_=0; y_<21; y_+=20){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}					
    
  pTemp->resi = resi;
  gotoxy(35,2);printf("No Resi - %d", resi++);
  gotoxy(12,5);printf("DATA PENGIRIM");
  gotoxy(52,5);printf("DATA PENERIMA");
  fflush(stdin);
  gotoxy(2,7);printf("Nama		: ");
  scanf("%[^\n]%*c",&nama_pengirim1);
  fflush(stdin);
  gotoxy(2,9);printf("Alamat	: ");
  scanf("%[^\n]%*c",&asal1);
  fflush(stdin);
  gotoxy(2,11);printf("No Telp	: ");
  scanf("%s",&telp_pengirim1);
  fflush(stdin);
  gotoxy(2,13);printf("Kode Kota Asal [3 Digit]	 : ");
  scanf("%s",&kode_asal1);
  fflush(stdin);
  gotoxy(42,7);printf("Nama		: ");
  scanf("%[^\n]%*c",&nama_penerima1);
  fflush(stdin);
  gotoxy(42,9);printf("Alamat	: ");
  scanf("%[^\n]%*c",&tujuan1);        
  fflush(stdin);
  gotoxy(42,11);printf("No Telp	: ");
  scanf("%s",&telp_penerima1);
  fflush(stdin);
  gotoxy(42,13);printf("Kode Kota Tujuan [3 Digit]	 : ");
  scanf("%s",&kode_tujuan1);
  fflush(stdin);
  gotoxy(19,19);printf("Masukkan Estimasi Hari             : ");
  scanf("%d",&lama_pengiriman1);
							
  if (pTemp != NULL)
  {					
		strcpy(pTemp->nama_pengirim1, nama_pengirim1);
		strcpy(pTemp->asal1, asal1);
		strcpy(pTemp->telp_pengirim1, telp_pengirim1);
		strcpy(pTemp->nama_penerima1, nama_penerima1);
		strcpy(pTemp->tujuan1, tujuan1);
		strcpy(pTemp->telp_penerima1, telp_penerima1);
		strcpy(pTemp->kode_asal1, kode_asal1);
		strcpy(pTemp->kode_tujuan1, kode_tujuan1);
		pTemp->lama_pengiriman1 = lama_pengiriman1;			
      	pTemp->next = *head;
      	*head =pTemp;
  }
  else
  {									
      printf("Input Paket Gagal!");
      getch();
  }
}
//----------------- DELETE PACKAGE -----------------------
void hapus_paket1(node1 **head, node2 **phead)
{
  int pos;							
  node1 *pCur, *pPre;				
	node2 *pNew;
	pNew = (node2*)malloc(sizeof(node2));
	char nama_pengirim2[30],asal2[30];
	char nama_penerima2[30],tujuan2[30];
	char telp_pengirim2[13],telp_penerima2[13];
	char kode_asal2[4], kode_tujuan2[4];
	int lama_pengiriman2,resi;
									
  system("cls");
  
  tampilkan_paket1(*head);					
  printf("\n\n   Pilih No Resi Paket yang akan di proses : ");
  fflush(stdin);
  scanf("%d", &pos);

  pPre = NULL;					
  pCur = *head;					
  
  while (pCur != NULL && pCur -> resi != pos) 
  { 
    pPre = pCur;				
    pCur = pCur -> next;		
  }

  if (pCur == NULL)				
   { printf("\n\n   Paket Dengan No Resi %d Tidak Ada",pos);
	 return;
	}
  else
  	pNew -> resi = pCur -> resi;
	strcpy (pNew -> nama_pengirim2, pCur -> nama_pengirim1);
	strcpy (pNew -> telp_pengirim2, pCur -> telp_pengirim1);
	strcpy (pNew -> nama_penerima2, pCur -> nama_penerima1);
	strcpy (pNew -> telp_penerima2, pCur -> telp_penerima1);
	strcpy (pNew -> tujuan2, pCur -> tujuan1);
	strcpy (pNew -> kode_asal2, pCur -> kode_asal1);
	strcpy (pNew -> kode_tujuan2, pCur -> kode_tujuan1);
	strcpy (pNew -> asal2, pCur -> asal1);
	pNew -> lama_pengiriman2 = pCur -> lama_pengiriman1;
	tambah_paket2 (phead, NULL, pNew);
     deleteNode(head, pPre, pCur);
	 printf("\n\n   Paket Dengan No Resi %d Berhasil Di Proses !!!",pos);	
}
//------------------ SHOW PACKAGE ------------------------
void tampilkan_paket1(node1 *head)
{	   
	node1 *pWalker;
	pWalker = head;
	int i=1;			

    system("cls");	
	
	//Looping tampilkan Border Vertikal
	for (int y_=0; y_<58; y_++){
		for (int x_=0; x_<80; x_+=79){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan border badan
	for(int x_=1; x_<78; x_++){
		for(int y_=0; y_<301; y_+=300){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}
	if (pWalker == NULL)
	{
		printf("\n\n\xB2  Paket Masih Kosong\n");
		return;
	} else							
	while (pWalker != NULL)
	{		
   		printf("\n\xB2============================= Paket No Resi - %d ==============================\xB2\n", pWalker->resi);
		printf("\xB2  Nama Pengirim\t\t: %s            \n", pWalker->nama_pengirim1);
		printf("\xB2  No Telp Pengirim\t\t: %s         \n", pWalker->telp_pengirim1);
		printf("\xB2  Alamat Pengirim\t\t: %s          \n", pWalker->asal1);		
		printf("\xB2  Nama Penerima\t\t: %s            \n", pWalker->nama_penerima1);
		printf("\xB2  No Telp Penerima\t\t: %s         \n", pWalker->telp_penerima1);
		printf("\xB2  Alamat Penerima\t\t: %s          \n", pWalker->tujuan1);
		printf("\xB2  Rute Pengiriman\t\t: %s -> %s    \n", pWalker->kode_asal1, pWalker->kode_tujuan1);
		printf("\xB2  Estimasi Pengiriman\t\t: %d Hari \n", pWalker->lama_pengiriman1);
		printf("\xB2==============================================================================\xB2"); 
   		pWalker = pWalker -> next;
		i++;		
	}
	//Looping tampilkan border badan
	for(int x_=1; x_<79; x_++){
		for(int y_=0; y_<58; y_+=57){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}			
}
//----------------- SORTING -----------------------
 void tambah_paket2(node2 **phead, node2 *pPre, node2 *pNew)
 {
 	node2 *pCur = *phead;
	if (pPre == NULL)
	{
		if (*phead == NULL)
		{
			pNew -> next = pNew;
			(*phead) = pNew;
		}	
		else if (pCur -> lama_pengiriman2 < pNew -> lama_pengiriman2)
		{
			while (pCur -> next != (*phead))
			{
				pCur = pCur -> next;
			}
			pCur -> next = pNew;
			pNew -> next = (*phead);
			(*phead) = pNew;
		}
		else 
		{
		while (pCur -> next != (*phead) && pCur -> next -> lama_pengiriman2 >= pNew -> lama_pengiriman2)
		{
			pCur = pCur -> next;
		}
			pNew -> next = pCur -> next;
			pCur -> next = pNew;
		}
	}
	else 
	{
		pNew -> next = pPre -> next;
		pPre -> next = pNew;
	}
 }
 //----------------- VIEW SORTING -----------------------
 void tampilkan_paket2(node2 *phead)
 {
	node2 *pWalker = phead;
    system("cls");
	//Looping tampilkan Border Vertikal
	for (int y_=0; y_<58; y_++){
		for (int x_=0; x_<80; x_+=79){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan border badan
	for(int x_=1; x_<78; x_++){
		for(int y_=0; y_<301; y_+=300){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}	
	
	if (pWalker == NULL)
	{
		printf("\n\n\xB2  Paket Masih Kosong");
		return;
	} else
		while (pWalker -> next != phead)
		{
	   		printf("\n\xB2============================= Paket No Resi - %d ==============================\xB2\n", pWalker->resi);
			printf("\xB2  Nama Pengirim        : %s \n", pWalker -> nama_pengirim2);		   	
			printf("\xB2  No Telp. Pengirim    : %s \n", pWalker -> telp_pengirim2);
		   	printf("\xB2  Alamat Pengirim      : %s \n", pWalker -> asal2);
			printf("\xB2  Nama Penerima        : %s \n", pWalker -> nama_penerima2);		   	
			printf("\xB2  No Telp. Penerima    : %s \n", pWalker -> telp_penerima2);
		   	printf("\xB2  Alamat Penerima      : %s \n", pWalker -> tujuan2);
			printf("\xB2  Rute Paket           : %s -> %s\n", pWalker -> kode_asal2, pWalker -> kode_tujuan2);		   	
		   	printf("\xB2  Perkiraan Pengiriman : %d Hari \n", pWalker -> lama_pengiriman2);
			printf("\xB2==============================================================================\xB2");
		   	pWalker = pWalker -> next;
		}
	   		printf("\n\xB2============================= Paket No Resi - %d ==============================\xB2\n", pWalker->resi);
			printf("\xB2  Nama Pengirim        : %s \n", pWalker -> nama_pengirim2);		   	
			printf("\xB2  No Telp. Pengirim    : %s \n", pWalker -> telp_pengirim2);
		   	printf("\xB2  Alamat Pengirim      : %s \n", pWalker -> asal2);
			printf("\xB2  Nama Penerima        : %s \n", pWalker -> nama_penerima2);		   	
			printf("\xB2  No Telp. Penerima    : %s \n", pWalker -> telp_penerima2);
		   	printf("\xB2  Alamat Penerima      : %s \n", pWalker -> tujuan2);
			printf("\xB2  Rute Paket           : %s -> %s\n", pWalker -> kode_asal2, pWalker -> kode_tujuan2);		   	
		   	printf("\xB2  Perkiraan Pengiriman : %d Hari \n", pWalker -> lama_pengiriman2);
			printf("\xB2==============================================================================\xB2");
	//Looping tampilkan border badan
	for(int x_=1; x_<79; x_++){
		for(int y_=0; y_<58; y_+=57){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}			 
}
//----------------- DELETE SORTING -----------------------
void hapus_paket2(node2 **phead,queue *myQueue)
{
    node2 *pCur,*pPre;
	node3 *new_node = (node3 *)malloc(sizeof(node3));
	char nama_pengirim3[30],asal3[30];
	char nama_penerima3[30],tujuan3[30];
	char telp_pengirim3[13];
	char telp_penerima3[13];
	char kode_asal3[4], kode_tujuan3[4];
	int lama_pengiriman3,no_resi;
		
	system ("cls");
	tampilkan_paket2(*phead);
    pCur = *phead;
    pPre = NULL;
	fflush(stdin);

		if (pCur == NULL)
		{
			printf ("\n\n\xB2  Paket Masih Kosong");
			getch();
			return;
		}
		else
		{
			pCur = *phead;
			pPre = NULL;
			while (pCur->next != *phead)
			{
				pPre = pCur;
				pCur = pCur -> next;
			}
	    if (pPre == NULL)
	    {
	    	*phead = NULL;
		}
		else if (pPre != NULL)
	       pPre -> next = pCur -> next;
	       printf ("\n\n Paket dengan No Resi %d Berhasil Diproses ke Kurir !!!", pCur -> resi);
	       {
	        myQueue -> count++;
	        new_node -> no_resi = pCur -> resi;
	        new_node -> no_antri = myQueue -> count;
			strcpy(new_node -> nama_penerima3, pCur -> nama_penerima2);
			strcpy(new_node -> nama_pengirim3, pCur -> nama_pengirim2);
			strcpy(new_node -> asal3, pCur -> asal2);
			strcpy(new_node -> tujuan3, pCur -> tujuan2);
			strcpy(new_node -> telp_pengirim3, pCur -> telp_pengirim2);
			strcpy(new_node -> telp_penerima3, pCur -> telp_penerima2);
			strcpy(new_node -> kode_asal3, pCur -> kode_asal2);
			strcpy(new_node -> kode_tujuan3, pCur -> kode_tujuan2);
			new_node->lama_pengiriman3=pCur -> lama_pengiriman2;
			new_node->next = NULL;
	
			if(myQueue->front==NULL)
			{
				myQueue->front = new_node;
				myQueue->rear = new_node;
			}
			else
			{
			    myQueue->rear->next=new_node;
			    myQueue->rear=new_node;
	        }
		   }
		free(pCur);
	}
}
//----------------- DEQUEUE -----------------------
void hapus_paket3(queue *myQueue)
{
	system("cls");
	
    if(myQueue->count==0){
		printf("\n\n  Data Masih Kosong");
 	}
	else
	{
	    node3 *pFirst;
		pFirst = myQueue->front;
		myQueue->front=myQueue->front->next;
		printf("\n Paket Dengan No Resi - %d Telah Dikirim",pFirst->no_resi);
		free(pFirst);
		myQueue->jumlah++;
		myQueue->count--;
	}
	
}
//----------------- DESTROY -----------------------
void destroy(queue *myQueue)
{
 node3 *temp;

 while(myQueue->count!=0)
 {
  temp=myQueue->front;
  myQueue->front=myQueue->front->next;
  myQueue->count--;
  free(temp);
 }

 myQueue->count=0;
 myQueue->front=NULL;
 myQueue->rear=NULL;
}
//----------------- VIEW QUEUE -----------------------
void tampilkan_paket3(queue myQueue)
{
 node3 *temp;
    int no_urut;
    temp = myQueue.front;
    system("cls");
	//Looping tampilkan Border Vertikal
	for (int y_=0; y_<58; y_++){
		for (int x_=0; x_<80; x_+=79){
			gotoxy (x_,y_); printf("\xB2");
		}
	}
	//Looping tampilkan border badan
	for(int x_=1; x_<78; x_++){
		for(int y_=0; y_<301; y_+=300){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}	
    
    if (temp != NULL){
    gotoxy(27,1);printf("PAKET YANG BELUM TERKIRIM\n");
    while(temp != NULL)
    {
        for(no_urut = 1; temp != NULL; no_urut ++){
  		printf("\n\xB2============================== Urutan ke - %d =================================\xB2\n",no_urut);
  		printf("\xB2  No Resi                    : %d\n", temp->no_resi);
  		printf("\xB2  Nama Pengirim              : %s\n", temp->nama_pengirim3);
		printf("\xB2  No Telp. Pengirim          : %s\n", temp->telp_pengirim3);
		printf("\xB2  Alamat Pengirim            : %s\n", temp->asal3);
		printf("\xB2  Nama Penerima              : %s\n", temp->nama_penerima3);
		printf("\xB2  No Telp. Penerima          : %s\n", temp->telp_penerima3);
		printf("\xB2  Alamat Penerima            : %s\n", temp->tujuan3);
		printf("\xB2  Rute Pengiriman            : %s -> %s\n", temp->kode_asal3, temp->kode_tujuan3);
		printf("\xB2  Estimasi Pengiriman (Hari) : %d\n", temp->lama_pengiriman3);
		printf("\xB2==============================================================================\xB2"); 
		temp = temp->next;
        }
    }
    }
    else
    {
        printf("\n\n\xB2  Data masih kosong");
    }
	//Looping tampilkan border badan
	for(int x_=1; x_<79; x_++){
		for(int y_=0; y_<58; y_+=57){
			gotoxy (x_,y_); printf("\xB2");
		}		
	}    
}
//----------------- STATUS -----------------------
void barangterkirim(queue *myQueue)
{
	system("cls");
    printf("\n\n   Jumlah Paket yang Terkirim = %d", myQueue->jumlah);
}
