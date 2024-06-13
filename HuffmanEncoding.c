// Jeihan Ivan Hadar 
// Imperative Programming: Huffman Coding 

#include <stdio.h>
#include <string.h>
 
typedef struct hNode
{
    struct hNode *left, *right;
    int freq;
    char c;
} *node;
 
struct hNode pool[256] = {{0}};
node p[255], *q = p - 1;
int n_nodes = 0, qend = 1;
char *code[128] = {0}, buf[1024];
int input_data = 0;
int output_data = 0;

node new_node(int freq, char c, node a, node b)
{
    node n = pool + n_nodes++;
    if (freq) n->c = c, n->freq = freq;
    else 
    {
        n->left = a, n->right = b;
        n->freq = a->freq + b->freq;
    }
    return n;
}

void qinsert(node n)
{
    int j, i = qend++;
    while ((j = i / 2)) 
    {
        if (q[j]->freq <= n->freq) break;
        q[i] = q[j], i = j;
    }
    q[i] = n;
}
 
node qremove()
{
    int i, l;
    node n = q[i = 1];
 
    if (qend < 2) return 0;
    qend--;
    while ((l = i * 2) < qend) 
    {
        if (l + 1 < qend && q[l + 1]->freq < q[l]->freq) l++;
        q[i] = q[l], i = l;
    }
    q[i] = q[qend];
    return n;
}

void build_code(node n, char *s, int len)
{
    static char *out = buf;
    if (n->c) 
    {
        s[len] = 0;
        strcpy(out, s);
        code[n->c] = out;
        out += len + 1;
        return;
    }
    s[len] = '0'; build_code(n->left,  s, len + 1);
    s[len] = '1'; build_code(n->right, s, len + 1);
}
 
void init(const char *s)  
{
    int i, freq[128] = {0};   
    char c[16];
    int m;
  
    while (*s) freq[(int)*s++]++;
    for (i = 0; i < 128; i++)
    if (freq[i]) qinsert(new_node(freq[i], i, 0, 0));
    while (qend > 2)
    {
        qinsert(new_node(0, 0, qremove(), qremove()));
        build_code(q[1], c, 0);
    } 
}
 
void encode(const char *s, char *out)
{
    while (*s) 
    {
        strcpy(out, code[*s]);   
        out += strlen(code[*s++]);
    }
}
 
void decode(const char *s, node t)
{
    node n = t;
    while (*s) 
    {
        if (*s++ == '0') n = n->left;
        else n = n->right;
        
        if (n->c) putchar(n->c), n = t;
    }
    putchar('\n');
    if (t != n) printf("Error\n");
}
 
int main(void)
{
    int i;
    char temp[256];  
    int answer;
    int ans;
    
    printf("------------------------------\n");
    printf("Huffman Coding Implementation!\n");
    printf("------------------------------\n");
    printf("Choose input option: \n"); 
    printf("1. User input\n");
    printf("2. Read File\n");
    printf("\n");
    printf("Enter a menu number: ");
    scanf("%d", &ans);
    
    switch(ans)
    {
        case 1: 
        printf("Input text: ");  
        scanf("%s", &temp);
        printf("\n");
        const char *str = temp;
        char buf[1024];
        
        init(str); 
  
        for (i = 0; i < 128; i++)
        if (code[i]) printf("'%c': %s\n", i, code[i]);
        
        do
        {
            printf("\n");
            printf("Choose an action:\n");
            printf("1. Encode input\n");
            printf("2. Decode input\n");
            printf("3. Exit\n");
            printf("\n");
            printf("Enter a menu number: ");
            scanf("%d",&answer);
            // printf("\n");
            
            switch(answer)
            {
                case 1:
                encode(str, buf);
                printf("\n");
                printf("encoded: %s\n", buf);
                break;
                
                case 2: 
                encode(str, buf);
                printf("encoded: %s", buf);
                printf("\n");
                printf("decoded: ");
                decode(buf, q[1]);
                break;
                
                case 3: 
                printf("Bye~!");
                printf("\n");
                break;
    
                default: answer = 3;
                printf("Error!\n");
                break;
            }
        }
        while(answer != 3);
        return 0;
        break;

        case 2:
        printf("Function is not yet implemented");
        break;
    }
}
