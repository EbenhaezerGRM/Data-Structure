//Ebenhaezer George Renaldi Muljadi - 2702230461

//Library yang digunakan untuk fungsi input output
#include <stdio.h>
//Library yang digunakan untuk alokasi memori
#include <stdlib.h>
//Library yang digunakan untuk tipe data boolean
#include <stdbool.h>
//Library yang digunakan untuk manipulasi string
#include <string.h>
//Library yang digunakan untuk function tolower()
#include <ctype.h>

//Constant untuk ukuran alfabet
#define ALPHABET_SIZE 26

/*
Struktur trie yang berisi array of pointer ke node, 
Deskripsi, dan boolean penanda akhir kata.
*/
struct node{
    struct node * children[ALPHABET_SIZE];
    char * description;
    bool isEndOfWord;
};

//Inisialisasi root dengan NULL
struct node * root = NULL;

/*
Fungsi create() digunakan untuk membuat node baru 
1. Menginisialisasi newNode->isEndOfWord menjadi false karena belum ada kata yang selesai pada node tersebut. 
2. Menginisialisasi newNode->description menjadi NULL karena belum ada deskripsi yang terkait dengan kata yang disimpan.
3. Menginisialisasi semua pointer pada array children menjadi NULL karena belum ada kata yang disimpan pada node tersebut.
4. Kemudian return newNode untuk mengembalikan alamat dari node yang baru dibuat kepada pemanggil fungsi create().
*/
struct node * create(){
    struct node * newNode = (struct node *)malloc(sizeof(struct node));
    if(newNode){
        newNode->isEndOfWord = false;
        newNode->description = NULL;
        for(int i = 0; i < ALPHABET_SIZE; i++){
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

/*
Fungsi insert() digunakan untuk memasukan kata slang dan deskripsi ke struktur trie
1. Jika root masih NULL atau kosong, maka buat node baru dengan fungsi create() dan tetapkan sebagai root.
2. Melakukan Looping sebanyak huruf pada slang.
3. Menghitung index = slang[i] - 'a' digunakan untuk menentukan di mana cabang dalam trie akan dibuat untuk huruf tersebut.
4. Jika children[index] pada node saat ini (curr) masih NULL atau kosong, maka buat node baru dengan fungsi create()
5. Tetapkan curr untuk ke node selanjutnya.
6. Jika sudah sampai pada huruf terakhir dari slang, maka tetapkan curr->isEndOfWord menjadi true.
7. Jika curr->description sudah terisi, maka hapus deskripsi fungsi free().
8. Tetapkan curr->description dengan deskripsi yang baru.
*/
void insert(char slang[], char description[]){
    if(root == NULL){
        root = create();
    }

    struct node * curr = root;

    for(int i = 0; i < strlen(slang); i++){
        //Merubah huruf menjadi huruf kecil
        char c = tolower(slang[i]);
        int index = c - 'a';
        if(curr->children[index] == NULL){
            curr->children[index] = create();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;

    if(curr->description){
        free(curr->description);
    }
    curr->description = strdup(description);
}

/*
Fungsi release() digunakan untuk menginput kata slang dan deksripsi
1. Menginisialisasi variabel slang dan description dengan array char.
2. Memasukan kata slang dari user dengan ketentuan panjang kata lebih dari 1 karakter 
dan tidak mengandung spasi. Ketika panjang kata kurang dari 1 karakter atau mengandung spasi, 
maka akan terus meminta inputan sampai sesuai.
3. Memasukan deskripsi dari user dengan ketentuan panjang kata lebih dari 2 kata. 
Ketika panjang kata kurang dari 2 kata, maka akan terus meminta inputan sampai sesuai.
4. Ketika ada kata slang yang sama maka deskripsi akan diupdate.
5. Memasukan kata slang dan deskripsi ke dalam struktur trie dengan memanggil fungsi insert().
*/
void release(){
    system("cls");

    char slang[100], description[1000];

    int flagSlang = 1;
    do{
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf(" %[^\n]", slang);
        int lenSlang = strlen(slang);

        if(lenSlang <= 1){
            flagSlang = 1;
        }
        else{
            flagSlang = 0;
        }

        for(int i = 0; i < lenSlang; i++){
            if(slang[i] == ' '){
                flagSlang = 1;
                break;
            }
        }
    }while(flagSlang == 1);

    int flagDescription = 1;
    do{
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf(" %[^\n]", description);
        int lenDesc = strlen(description);

        for(int i = 0; i < lenDesc; i++){
            if(description[i] == ' '){
                flagDescription = 0;
                break;
            }
        }
    }while(flagDescription == 1);

    insert(slang, description);

    printf("\nSuccessfully released new slang word.\n");
    printf("Press enter to continue...");
    getchar();
    getchar();
}

/*
Fungsi search() digunakan untuk mencari kata slang dan menampilkan deskripsi 
1. Jika root masih NULL atau kosong, maka tampilkan pesan bahwa tidak ada kata slang di dalam trie atau dictionary.
2. Memasukan kata slang dari user dengan ketentuan panjang kata lebih dari 1 karakter dan tidak mengandung spasi. 
Ketika panjang kata kurang dari 1 karakter atau mengandung spasi, maka akan terus meminta inputan sampai sesuai.
3. Mencari kata slang pada trie dengan looping sebanyak huruf pada slang.
4. Menghitung index = slang[i] - 'a' digunakan untuk menentukan di mana cabang dalam trie huruf tersebut berada.
5. Jika children[index] pada node saat ini (curr) (jika sudah cari sampah akhir) masih NULL atau kosong, 
maka tampilkan pesan bahwa tidak ada kata slang tersebut di dalam trie atau dictionary.
6. Jika kata slang ditemukan, maka tampilkan kata slang dan deskripsinya.
*/
void search(){
    system("cls");

    if(root == NULL){
        printf("There is no slang word yet in the dictionary.\n");
    }
    else{
        char slang[100];
        int flagSlang = 1;
        do{
            printf("Input a slang word [Must be more than 1 character and contain no space]: ");
            scanf(" %[^\n]", slang);
            int lenSlang = strlen(slang);

            if(lenSlang <= 1){
                flagSlang = 1;
            }
            else{
                flagSlang = 0;
            }

            for(int i = 0; i < lenSlang; i++){
                if(slang[i] == ' '){
                    flagSlang = 1;
                    break;
                }
            }
        }while(flagSlang == 1);

        struct node * curr = root;

        for(int i = 0; i < strlen(slang); i++){
            //Merubah huruf menjadi huruf kecil
            char c = tolower(slang[i]);
            int index = c - 'a';
            if(curr->children[index] == NULL){
                printf("\nThere is no word \"%s\" in the dictionary.\n", slang);
                printf("Press enter to continue...");
                getchar();
                getchar();
                return;
            }
            curr = curr->children[index];
        }

        if(curr != NULL && curr->isEndOfWord){
            printf("\nSlang word  : %s\n", slang);
            printf("Description : %s\n", curr->description);
        }
        else{
            printf("\nThere is no word \"%s\" in the dictionary.\n", slang);
        }
    }
    printf("\nPress enter to continue...");
    getchar();
    getchar();
}

/*
viewAllUtil() adalah sebuah utility yang digunakan untuk membantu fungsi viewAll() 
untuk menampilkan semua kata slang yang ada di dalam trie. 
1. Jika curr->isEndOfWord bernilai true, maka tampilkan kata slang tersebut.
2. Melakukan looping sebanyak panjang alfabet (26).
3. Jika children[i] pada node saat ini (curr) tidak NULL, maka panggil viewAllUtil() secara rekursif.
4. Jika sudah sampai pada akhir kata, maka tampilkan kata slang tersebut.
*/
void viewAllUtil(struct node * curr, char slangBuffer[], int level, int * index){
    if(curr->isEndOfWord){
        slangBuffer[level] = '\0';
        printf("%d. %s\n", ++(*index), slangBuffer);
    }
    for(int i = 0; i < ALPHABET_SIZE; i++){
        if(curr->children[i] != NULL){
            slangBuffer[level] = i + 'a';
            viewAllUtil(curr->children[i], slangBuffer, level + 1, index);
        }
    }
}

/*
Fungsi viewAll() digunakan untuk menampilkan semua kata slang yang ada di dalam trie. 
1. Jika root masih NULL atau kosong, maka tampilkan pesan bahwa tidak ada kata slang di dalam trie atau dictionary.
2. Jika ada kata slang, maka panggil viewAllUtil() untuk menampilkan semua kata slang yang ada di dalam trie.
*/
void viewAll(){
    system("cls");

    int index = 0;
    if(root == NULL){
        printf("There is no slang word yet in the dictionary.");
    }
    else{
        char slangBuffer[100];
        printf("List of all slang words in the dictionary:\n");
        viewAllUtil(root, slangBuffer, 0, &index);
    }
    printf("\nPress enter to continue...");
    getchar();
    getchar();
}

/*
Fungsi viewPrefix() digunakan untuk menampilkan semua kata slang yang memiliki prefix tertentu. 
1. Jika root masih NULL atau kosong, maka tampilkan pesan bahwa tidak ada kata slang di dalam trie atau dictionary.
2. Memasukan prefix dari user dengan ketentuan panjang kata lebih dari 1 karakter dan tidak mengandung spasi.
Ketika panjang kata kurang dari 1 karakter atau mengandung spasi, maka akan terus meminta inputan sampai sesuai.
3. Mencari kata slang pada trie dengan looping sebanyak huruf pada prefix.
4. Menghitung index = prefix[i] - 'a' digunakan untuk menentukan di mana cabang dalam trie huruf tersebut berada.
5. Jika saat curr atau node saat ini sudah sampai akhir dan kata slang masih tidak ditemukan, 
maka tampilkan pesan bahwa tidak ada kata slang tersebut di dalam trie atau dictionary.
6. Jika kata slang ditemukan, maka panggil viewAllUtil() untuk menampilkan semua kata slang yang memiliki prefix tersebut.
*/
void viewPrefix(){
    system("cls");

    if(root == NULL){
        printf("There is no slang word yet in the dictionary.");
        printf("\nPress enter to continue...");
        getchar();
        getchar();
        return;
    }

    char prefix[100];
    int flagPrefix = 1;
        do{
            printf("Input a prefix to be searched: ");
            scanf(" %[^\n]", prefix);
            int lenSlang = strlen(prefix);

            if(lenSlang <= 1){
                flagPrefix = 1;
            }
            else{
                flagPrefix = 0;
            }

            for(int i = 0; i < lenSlang; i++){
                if(prefix[i] == ' '){
                    flagPrefix = 1;
                    break;
                }
            }
        }while(flagPrefix == 1);

    struct node * curr = root;

    for(int i = 0; i < strlen(prefix); i++){
        //Merubah huruf menjadi huruf kecil
        char c = tolower(prefix[i]);
        int index = c - 'a';
        if(curr->children[index] == NULL){
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            printf("Press enter to continue...");
            getchar();
            getchar();
            return;
        }
        curr = curr->children[index];
    }

    char prefixBuffer[100];
    strcpy(prefixBuffer, prefix);
    printf("\nWords starts with \"%s\":\n", prefix);
    viewAllUtil(curr, prefixBuffer, strlen(prefix), &(int){0});

    printf("\nPress enter to continue...");
    getchar();
    getchar();
}

//Fungsi exitProgram() digunakan untuk menampilkan pesan bahwa program telah selesai.
void exitProgram(){
    printf("Thank you... Have a nice day :)\n");
}

/*
Fungsi menu digunakan untuk menampilkan menu utama program dan memanggil fungsi sesuai dengan pilihan user.
Menu akan terus ditampilkan sampai user memilih untuk keluar dari program (atau memasukan angka 5).
*/
void menu(){
    int option = 0;
    do {
        system("cls");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf("%d", &option);

        switch(option){
        case 1:
            //Memanggil fungsi release() untuk menambahkan kata slang dan deskripsi ke dalam trie.
            release();
            break;
        case 2:
            //Memanggil fungsi search() untuk mencari kata slang dan menampilkan deskripsi.
            search();
            break;
        case 3:
            //Memanggil fungsi viewPrefix() untuk menampilkan semua kata slang yang memiliki prefix tertentu.
            viewPrefix();
            break;
        case 4:
            //Memanggil fungsi viewAll() untuk menampilkan semua kata slang yang ada di dalam trie.
            viewAll();
            break;
        case 5:
            //Memanggil fungsi exitProgram() untuk menampilkan pesan bahwa program telah selesai.
            exitProgram();
            break;
        //Jika user memasukan pilihan yang tidak valid, maka tampilkan pesan bahwa pilihan tidak valid.
        default:
            system("cls");
            printf("Invalid option\n");
            printf("Press enter to continue...");
            getchar();
            getchar();
            break;
        }
    }while(option != 5);
}

//main() berfungsi sebagai titik awal eksekusi program.
int main(){
    //Memanggil fungsi menu() untuk menampilkan menu utama program.
    menu();
    return 0;
}