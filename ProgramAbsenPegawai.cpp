//Kelompok 7 :
//2501984846 - Seftico Frig Injek B
//2502015850 - Adi Ageng Prayogo Bin Muttaqin
//2540134262 - I Gusti Ayu Ngurah Stita Maharani

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

typedef char string[50];

struct node
{
    int nip;
    int jam;
    int menit;
    int day;
    int month;
    int year;
    string nama;
    string ket;
    node *left;
    node *right;
    time_t waktu;
};

node *createTree(int nip, string nama, string ket, int jam, int menit, int day, int month, int year)
{
    node *data = (node *)malloc(sizeof(struct node));
    strcpy(data->nama, nama);
    data->nip = nip;
    strcpy(data->ket, ket);
    data->jam = jam;
    data->menit = menit;
    data->day = day;
    data->month = month;
    data->year = year;
    data->left = NULL;
    data->right = NULL;
    return data;
}

node *insertNilai(node *root, int nip, string nama, string ket, int jam, int menit, int day, int month, int year)
{
    if (root == NULL)
    {
        root = createTree(nip, nama, ket, jam, menit, day, month, year);
    }
    else if (nip < root->nip)
    {
        root->left = insertNilai(root->left, nip, nama, ket, jam, menit, day, month, year);
    }
    else if (nip > root->nip)
    {
        root->right = insertNilai(root->right, nip, nama, ket, jam, menit, day, month, year);
    }
    return root;
}

void preOrder(struct node *node);
void inOrder(struct node *node);
void postOrder(struct node *node);
void deleteAll(struct node *node);

node *searchData(node *root, int nip)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->nip == nip)
    {
        return root;
    }
    if (root->nip > nip)
    {
        return searchData(root->left, nip);
    }
    else
    {
        return searchData(root->right, nip);
    }
}

node *successor(struct node *root)
{ // node paling kecil di subtree kanan
    node *curr = root->right;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

node *predecesor(struct node *root)
{ // node paling besar di subtree kiri
    node *curr = root->left;
    while (curr->right != NULL)
    {
        curr = curr->right;
    }
    return curr;
}

node *deleteNode(node *root, int nip)
{
    if (root == NULL)
    {
        printf("Tidak ada data!\n");
        return root;
    }
    if (nip < root->nip)
    {
        root->left = deleteNode(root->left, nip);

    }
    else if (nip > root->nip)
    {
        root->right = deleteNode(root->right, nip);

    }
    else
    {
        node *ptr = NULL;
        if (root->left == NULL)
        {
            ptr = root->right;
            free(root);
            printf("*********************************\n");
            printf("  NIP TELAH BERHASIL DIHAPUS [!] \n");
            printf("*********************************\n");
            return ptr;
        }
        else if (root->right == NULL)
        {
            ptr = root->left;
            free(root);
            printf("*********************************\n");
            printf("  NIP TELAH BERHASIL DIHAPUS [!] \n");
            printf("*********************************\n");
            return ptr;
        }
        else
        {
            // kalau node memiliki dua anak
            ptr = predecesor(root);
            root->nip = ptr->nip;
            strcpy(root->nama, ptr->nama);
            strcpy(root->ket, ptr->ket);
            root->jam = ptr->jam;
            root->menit = ptr->menit;
            root->day = ptr->day;
            root->month = ptr->month;
            root->year = ptr->year;
            root->left = deleteNode(root->left, ptr->nip);
        }
    }
    return root;
}

int main()
{
    system("cls");
    int hours, minutes, seconds, day, month, year;

    time_t now;
    time(&now);
    printf("\tToday is %s\n\n", ctime(&now));
    struct tm *local = localtime(&now);

    hours = local->tm_hour;  // get hours since midnight (0-23)
    minutes = local->tm_min; // get minutes passed after the hour (0-59)
    seconds = local->tm_sec; // get seconds passed after a minute (0-59)

    day = local->tm_mday;         // get day of month (1 to 31)
    month = local->tm_mon + 1;    // get month of year (0 to 11)
    year = local->tm_year + 1900; // get year since 1900

    node *root = NULL;
    int pilihan, pilima; // Pilima ; Pilihan Nomor 5
    int nip, temp;
    string ket;
    string nama;
    do
    {
        printf("   Dinas Pendidikan dan Kebudayaan Kota Malang   \n");
        printf("         Jl. Veteran No.19, Ketawanggede         \n");
        printf("                   Kec. Lowokwaru                \n");
        printf("               Kota Malang, Jawa Timur           \n");
        printf("                       65145                     \n");
        printf("=================================================\n");
        printf("                 MAIN MENU PROGRAM               \n");
        printf("=================================================\n");
        printf("\n");
        printf("           1. Masukkan Data Pegawai              \n");
        printf("           2. Data Pegawai                       \n");
        printf("           3. Preorder                           \n");
        printf("           4. Inorder                            \n");
        printf("           5. Postorder                          \n");
        printf("           6. Hapus Data                         \n");
        printf("           7. Exit                               \n");
        printf("\n\nMasukkan pilihan anda: ");
        scanf("%d", &pilihan);
        fflush(stdin);
        switch (pilihan)
        {
        case 1:
            printf("Masukkan nama : ");
            fflush(stdin);
            gets(nama);
            printf("Nomor Identitas Pegawai : ");
            scanf("%d", &nip);
            printf("Keterangan : ");
            fflush(stdin);
            gets(ket);
            root = insertNilai(root, nip, nama, ket, hours, minutes, day, month, year);
            break;
        case 2:
            printf("Masukan NIP yang ingin dicari : ");
            scanf("%d", &nip);
            if (searchData(root, nip))
            {
                printf("------------------\n");
                printf("  Data ditemukan  \n");
                printf("------------------\n");

                node *temp = searchData(root, nip);
                printf("\n--------------------------------------------\n");
                printf("NIP : %d\n", temp->nip);
                printf("Nama : %s\n", temp->nama);
                printf("Keterangan : %s\n", temp->ket);
                printf("Tanggal dan Waktu : %d/%d/%d %d:%d\n", temp->day, temp->month, temp->year, temp->jam, temp->menit);
                printf("--------------------------------------------\n\n");
            }
            else
            {
                printf("Data tidak ditemukan\n");
            }
            break;
        case 3:
            printf("Preorder dari data tree : \n");
            printf("\n+---------------+------------------------------+---------------+-----------------------------+\n");
            printf("|%-15s|%-30s|%-15s|%-28s |\n", " NIP", " Nama Pegawai", " Kehadiran", " Waktu");
            preOrder(root);
            printf("+---------------+------------------------------+---------------+-----------------------------+\n");
            break;
        case 4:
            printf("Inorder dari data tree : \n");
            printf("\n+---------------+------------------------------+---------------+-----------------------------+\n");
            printf("|%-15s|%-30s|%-15s|%-28s |\n", " NIP", " Nama Pegawai", " Kehadiran", " Waktu");
            inOrder(root);
            printf("+---------------+------------------------------+---------------+-----------------------------+\n");
            break;
        case 5:
            printf("Postorder dari data tree : \n");
            printf("\n+---------------+------------------------------+---------------+-----------------------------+\n");
            printf("|%-15s|%-30s|%-15s|%-28s |\n", " NIP", " Nama Pegawai", " Kehadiran", " Waktu");
            postOrder(root);
            printf("+---------------+------------------------------+---------------+-----------------------------+\n");
            break;
        case 6:

            printf("1. Hapus Data Pegawai\n");
            printf("2. Hapus Semua Data\n");
            printf("0. Batal\n");
            printf("Pilihan nomor : ");
            scanf("%d", &pilima);
            if (pilima == 1)
            {
                printf("Masukkan NIP yang ingin dihapus : ");
                scanf("%d", &nip);
                if (searchData(root, nip))
            {
                printf("------------------\n");
                printf("  Data ditemukan  \n");
                printf("------------------\n");

                node *temp = searchData(root, nip);
                printf("\n--------------------------------------------\n");
                printf("NIP : %d\n", temp->nip);
                printf("Nama : %s\n", temp->nama);
                printf("Keterangan : %s\n", temp->ket);
                printf("Tanggal dan Waktu : %d/%d/%d %d:%d\n", temp->day, temp->month, temp->year, temp->jam, temp->menit);
                printf("--------------------------------------------\n\n");
            }
            else
            {
                printf("Data tidak ditemukan\n");
            }
                root = deleteNode(root, nip);
            }
            else if (pilima == 2)
            {
                deleteAll(root);
            }
            else if (pilima == 0)
            {
                printf("\nBatal Menghapus\n");
            }
            else
            {
                printf("\nPilihan tidak ada\n");
            }
            break;
        case 7:
            printf("**********************\n");
            printf("*    TERIMA KASIH    *\n");
            printf("**********************\n");
            break;
        default :
            printf("\nNomor pilihan yang anda masukkan salah, silahkan ulangi !!\n");
            break;
        }
        system("pause");
        system("cls");
    } while (pilihan != 7);
    getch();
    return 0;
}

void deleteAll(struct node *node)
{
    if (node != NULL)
    {
        deleteAll(node->left);
        deleteAll(node->right);
        free(node);
    }
}

void postOrder(struct node *node)
{
    if (node != NULL)
    {
        postOrder(node->left);
        postOrder(node->right);
        printf("+---------------+------------------------------+---------------+-----------------------------+\n");
        printf("| %-14d| %-29s| %-14s| %-2d:%-2d | tanggal : %d-%d-%d |\n", node->nip, node->nama, node->ket, node->jam, node->menit, node->day, node->month, node->year);
    }
}

void inOrder(struct node *node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        printf("+---------------+------------------------------+---------------+-----------------------------+\n");
        printf("| %-14d| %-29s| %-14s| %-2d:%-2d | tanggal : %d-%d-%d |\n", node->nip, node->nama, node->ket, node->jam, node->menit, node->day, node->month, node->year);
        inOrder(node->right);
    }
}

void preOrder(struct node *node)
{
    if (node != NULL)
    {
        printf("+---------------+------------------------------+---------------+-----------------------------+\n");
        printf("| %-14d| %-29s| %-14s| %-2d:%-2d | tanggal : %d-%d-%d |\n", node->nip, node->nama, node->ket, node->jam, node->menit, node->day, node->month, node->year);
        preOrder(node->left);
        preOrder(node->right);
    }
}
