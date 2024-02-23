// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 100

struct MinHNode
{
    char item;
    unsigned freq;
    struct MinHNode *left, *right;
};

struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHNode **array;
};

// Create nodes
struct MinHNode *newNode(char item, unsigned freq)
{
    struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

    temp->left = temp->right = NULL;
    temp->item = item;
    temp->freq = freq;

    return temp;
}

// Create min heap
struct MinHeap *createMinH(unsigned capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
    return minHeap;
}

// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b)
{
    struct MinHNode *t = *a;
    *a = *b;
    *b = t;
}

// Heapify
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

// Check if size if 1
int checkSizeOne(struct MinHeap *minHeap)
{
    return (minHeap->size == 1);
}

// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap)
{
    struct MinHNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode)
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

    }

}
void writeHuffmanCodes(struct MinHNode *root, int arr[], int top, int freq[], char text[]);
// Wrapper function
void HuffmanCodes(struct MinHNode *root,char item[],int freq[], int size,char text[])
{
    struct MinHNode *root1 = buildHuffmanTree(item, freq, size);

    int arr[MAX_TREE_HT], top = 0;

    printHCodes(root1, arr, top,freq,text);
    writeHuffmanCodes(root, arr, top, freq, text);
}

// Print the array
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    //printf("\n");
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
void intToBinary(char ch, char *binary,char *put)
{
    int index = 0;

    // Iterate through each bit
    for (int i = sizeof(char) * 8 - 1; i >= 0; --i)
    {
        int bit = (ch >> i) & 1;
        binary[index++] = bit + '0';
    }

    binary[index] = '\0'; // Null-terminate the string
    strcat(put,binary);
    printf("Binary representation of %c: %s\n",ch, binary);
}
int main()
{
    FILE *filepointer;
    char filename[]="GGWABC.txt";

    //  "Newtest.txt";


    int  j = 0, capacity = 10, size = 0;
    int character[128] = {};
    int ch;
    char *arr = NULL;
    int *freq = NULL;
    char check[10000] = {};
    char pass[]="1001010111110000";
    char put[10000] = {}; // Adjust the size based on your needs

    filepointer = fopen(filename, "r");

    if (filepointer == NULL)
    {
        printf("Can't read this file\n");
        return 1;
    }
    char binaryRepresentation[2000];
    for (int i=0; i<16; i++)
    {
        ch = fgetc(filepointer);
        intToBinary(ch, binaryRepresentation,check);

    }
    if(strncmp(pass,check,16))
    {
        printf("This data doesn't encode by G1ilbert\n");
        return 9;
    }
    while ((ch = fgetc(filepointer)) != EOF)
    {
        intToBinary(ch, binaryRepresentation,put);

    }

    printf(" : %s\n", put);

    fclose(filepointer);
}

//-------------------------- 6620501443 ปุญญพัฒน์ รักษ์ชูชีพ --------------------------//

