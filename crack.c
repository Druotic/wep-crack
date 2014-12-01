#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int sim_resol(unsigned char *iv, unsigned char *key, int byte_index, unsigned char out) {
    unsigned char s[256], tmp_key[8];
    unsigned char a, s_1, k;
    int i, j;
    memcpy(tmp_key, iv, 3);
    memcpy(&tmp_key[3], key, 5);
    for (i=0; i < sizeof(s)/sizeof(s[0]); i++)
        s[i] = i;
    j=k=0;
    for (i=0; i < byte_index+3; i++) {
        j = (unsigned char)(j+s[i]+tmp_key[k]);
        a = s[i];
        s[i] = s[j];
        s[j] = a;
        if (++k >= 8)
            k = 0;
    }
    for (i=0; i < sizeof(s)/sizeof(s[0]); i++)
        if (s[i] == out)
            s_1 = i;
    if ((s[0] != byte_index + 3) || (s[1] != 0))
        return -1;
    else
        return (s_1-j-s[byte_index+3]);
}

void print_counts(unsigned char *counts, unsigned char byte_index) {
    int i;
    printf("\n---- begin counts (%d) ---- \n", byte_index);
    for(i = 0; i < 256; i++)
       printf("%d ", *(counts+i));
    printf("\n---- end counts ---- \n");
}

int main(int argc, char* argv[]) {
    FILE *fd;
    size_t read, len = 0;
    int i;
    unsigned char tmp, out, byte_index, max, max_index, plain;
    unsigned char key[5], counts[256], tmp_line[256];

    plain = 'C';
    memset(key, 0, 5);
    for (byte_index=0; byte_index < sizeof(key)/sizeof(key[0]); byte_index++) {
        memset(counts, 0, 256);
        fd = fopen (argv[1],"r");
        if (fd == NULL) {
            printf ("can not open file\n");
            return -1;
        }
        read = fread (tmp_line, sizeof(unsigned char), 143, fd);
        while (read !=0 ){
            //Process read packet and update counts array 
            if ((tmp_line[24] == byte_index+3) && (tmp_line[25] == 255))
            {
                out = plain^tmp_line[27];
                //printf("tmp: %d %d %d %d\n", tmp_line[24], byte_index, tmp_line[25], out);
                tmp = sim_resol(&tmp_line[24], key, byte_index, out);
                if ((tmp >= 0) && (tmp <= 255))
                    counts[tmp]++;
            }
            read = fread (tmp_line, sizeof(unsigned char), 143, fd);
        }
        //Process counts array and find key[byte_index]
        max=0;
        max_index=0;
        for (i=0; i<256; i++)
        {
            if (counts[i] > max){
                max_index=i;
                max = counts[i];
            }
        }
        key[byte_index]=(unsigned char)max_index;
        //print_counts(counts, byte_index);
        fclose (fd);
    }
    //printf("Key (decimal value): %d %d %d %d %d\n", key[0], key[1], key[2], key[3], key[4]);
    //printf("Key (character val): '%c' '%c' '%c' '%c' '%c'\n", key[0], key[1], key[2], key[3], key[4]);
    printf("%s\n", key);
    return 0;
}
