// C program for Huffman Coding

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHNode
{
    // One of the input characters
    char item;
    // Frequency of the character
    unsigned freq;
    // Left and right child of this node
    struct MinHNode *left, *right;
};

// A Min Heap:  Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap
{
    // Current size of min heap
    unsigned size;
    // capacity of min heap
    unsigned capacity;
    // Array of minheap node pointers
    struct MinHNode **array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHNode *newNode(char item, unsigned freq)
{
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap *createMinH(unsigned capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
    return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHNode(struct MinHNode **a, struct MinHNode **b)
{
    struct MinHNode *t = *a;
    *a = *b;
    *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx)
    {
        swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check
// if size of heap is 1 or not
int checkSizeOne(struct MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHNode *extractMin(struct MinHeap *minHeap)
{
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap *minHeap,
                   struct MinHNode *minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

int isLeaf(struct MinHNode *root)
{
    return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], int freq[], int size)
{
    struct MinHeap *minHeap = createMinH(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(item[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHNode *buildHuffmanTree(char item[], int freq[], int size)
{
    struct MinHNode *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

    while (!checkSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
// A utility function to print an array of size n
void printArray(int arr[], int n);
void printHCodes(struct MinHNode *root, int arr[], int top,int freq[],char text[])
{
    if (root->left)
    {
        arr[top] = 0;   //top is bits use
        printHCodes(root->left, arr, top + 1,freq,text);
    }
    if (root->right)
    {
        arr[top] = 1;
        printHCodes(root->right, arr, top + 1,freq,text);
    }
    if (isLeaf(root))
    {
        printf("  %c   | ", root->item);
        printArray(arr, top);
        printf("\n");
        printf("\n");
    }

}
void writeHuffmanCodes(struct MinHNode *root, int arr[], int top, int freq[], char text[]);
// Wrapper function
void HuffmanCodes(struct MinHNode *root,char item[],int freq[], int size,char text[])
{
    struct MinHNode *root1 = buildHuffmanTree(item, freq, size);

    int arr[MAX_TREE_HT], top = 0;

    printHCodes(root1, arr, top, freq, text);
    writeHuffmanCodes(root, arr, top, freq, text);
}

// Print the array
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

}
void writeHuffmanCodes(struct MinHNode *root, int arr[], int top, int freq[], char text[])
{
    if (root->left)
    {
        arr[top] = 0;
        writeHuffmanCodes(root->left, arr, top + 1, freq, text);
    }
    if (root->right)
    {
        arr[top] = 1;
        writeHuffmanCodes(root->right, arr, top + 1, freq, text);
    }
    if (isLeaf(root))
    {
        int charIndex = (int)(root->item);
        // Print the character, frequency, and Huffman code
        printf("  %c   | %d | ", root->item, root->freq);
        printArray(arr, top);

        // Write the Huffman code over the text
        for (int i = 0; i < top; i++)
        {
            if (arr[i] == 0)
            {
                printf("0");
                // You can append '0' to your text or store it in a separate array
                text[strlen(text)] = '0';
            }
            else
            {
                printf("1");
                // You can append '1' to your text or store it in a separate array
                text[strlen(text)] = '1';
            }
        }
        printf("\n");
    }
}

void encodeText(char text[], char item[], char codes[][MAX_TREE_HT], int size, char* encodedText)
{
    int encodedIndex = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (text[i] == item[j])
            {
                // Concatenate the Huffman code to the encoded text
                strcat(encodedText, codes[j]);
                encodedIndex += strlen(codes[j]);
                break;
            }
        }
    }
}


void ownencode(struct MinHNode *root, int arr[], int top,int freq[],char text,char keep[])
{

    if (root->left)
    {
        arr[top] = 0;   //top is bits use
        ownencode(root->left, arr, top + 1,freq,text,keep);
    }
    if (root->right)
    {
        arr[top] = 1;
        ownencode(root->right, arr, top + 1,freq,text,keep);
    }
    if (isLeaf(root))
    {
        if(root->item == text)
        {


            char str[top * top];

            int offset = 0;

            for (int i = 0; i < top; ++i)
            {
                // Use sprintf to convert each integer to a string and concatenate it to the result string
                offset += sprintf(str + offset, "%d", arr[i]);

                // Optionally, you can add a separator like a comma between the numbers
                if (i < top - 1)
                {
                    offset += sprintf(str + offset, "");
                }
            }
            strcat(keep,str);   //connect int array to string
            printArray(arr, top);

        }
    }

}

void binaryStringToFile(const char *binaryString,  char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    size_t len = strlen(binaryString);
    for (size_t i = 0; i < len; i += 8)
    {
        char byte = 0;
        for (int j = 0; j < 8 && i + j < len; j++)
        {
            byte = (byte << 1) | (binaryString[i + j] - '0');
        }
        fputc(byte, file);
    }

    fclose(file);
}
void decodeHuffman(struct MinHNode *root, char *encodedText, char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    struct MinHNode *current = root;
    size_t len = strlen(encodedText);

    for (size_t i = 0; i < len; i++)
    {
        if (encodedText[i] == '0')
        {
            current = current->left;
        }
        else if (encodedText[i] == '1')
        {
            current = current->right;
        }

        if (current != NULL && current->left == NULL && current->right == NULL)
        {
            fputc(current->item, file);
            current = root; // Reset to the root for the next character
        }
    }

    fclose(file);
}
void passSize(char *pass,int size)
{
    char bin[200]= {};
    intToBinary((char)size,bin,pass);
}
void password(char * item, int *freq,int size,char *pass)
{
    char bin[2000]= {};
    for(int i=0; i<size; i++)
    {
        intToBinary(item[i],bin,pass);
        //printf("%s\n",pass);
    }
}
void intToBinary(char ch, char *binary,char *empty)
{
    int index = 0;

    // Iterate through each bit
    for (int i = sizeof(char) * 8 - 1; i >= 0; --i)
    {
        int bit = (ch >> i) & 1;
        binary[index++] = bit + '0';
    }

    binary[index] = '\0'; // Null-terminate the string
    strcat(empty,binary);
}
void Freq(int *freq,char *pass,int size)
{
    char bin[2000]= {};
    char temp[20000]= {};
    for(int i=0; i<size; i++)
        intToBinary((char)freq[i],bin,pass);
}

int main()
{
    FILE *filepointer;
    char filename[]="GGWABC.txt";


    int ch, j = 0, capacity = 10, size = 0;
    int character[128] = {};
    char *arr = NULL; // items
    int *freq = NULL;

    char put[10000] = {}; // Adjust the size based on your needs , texts

    filepointer = fopen(filename, "r");

    if (filepointer == NULL)
    {
        printf("Can't read this file\n");
        return 1;
    }

    while (fgets(put, sizeof(put), filepointer) != NULL)
    {
        printf("Line read from file : %s\n", put);
        // Process the line if needed
    }
    rewind(filepointer); // Reset file pointer to the beginning

    while ((ch = fgetc(filepointer)) != EOF)
    {
        character[ch]++;

    }

    fclose(filepointer);

    arr = (char *)malloc(capacity * sizeof(char));
    freq = (int *)malloc(capacity * sizeof(int));

    for (int i = 0; i < 128; i++)
    {
        if (character[i] != 0)
        {
            if (size == capacity)
            {
                capacity *= 2;
                arr = (char *)realloc(arr, capacity * sizeof(char));
                freq = (int *)realloc(freq, capacity * sizeof(int));
            }
            arr[j] = i;
            freq[j] = character[i];
            j++;
            size++;
        }
    }

    // Create and build the Huffman tree
    struct MinHNode *root = buildHuffmanTree(arr, freq, size);

    // Display the Huffman codes
    int arr1[MAX_TREE_HT], top = 0;
    char keep[100000]= {};


    for(int i=0; i<strlen(put); i++)
    {
        ownencode(root, arr1, top, freq, put[i], keep);
    }
    printf("\n");
    printf("%s\n",keep);
    printHCodes(root, arr1, top, freq, put);

    char pass[100000]= {};
    passSize(pass, size);
    password(arr, freq, size, pass);
    Freq(freq, pass, size);
    strcat(pass, keep);
    printf("%s\n",pass);

    binaryStringToFile(pass, "GGEazy.bin");
}

//-------------------------- 6620501443 ปุญญพัฒน์ รักษ์ชูชีพ --------------------------//

