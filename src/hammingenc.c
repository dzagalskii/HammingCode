#include <stdio.h>
#include <stdlib.h>

void kontrolbit(int *kod, int lengh)
{
    int i = 0, summ = 0;
    while(i < lengh)
    {
        if((i+1 == 1)||(i+1 == 2)||(i+1 == 4)||(i+1 == 8)||(i+1 == 16)||(i+1 == 32)||(i+1 == 64))
        {
            int start = i;
            while(start < lengh)
            {
                for(int g = 0; g < i + 1; g++)
                {
                    if((kod[start+g] != 2)&&(start+g < lengh))
                        summ += kod[start+g];
                }
                start += (i + i + 2);
            }
            kod[i] = summ%2;
            summ = 0;
        }
        i++;
    }
}

void invert(int *byte)
{
    int i, t;
    for(i = 0; i < 4; i++)
    {
        t = byte[i];
        byte[i] = byte[7 - i];
        byte[7 - i] = t;
    }
}

void tobit(int x, int *byte)
{
    int i;
    for(i = 0; i < 8; i++)
    {
        byte[i] = x%2;
        x >>= 1;
    }
    invert(byte);
}

int todec(int *byte)
{
    int i, x = 0, st = 7;
    for(i = 0; i < 8; i++)
    {
        x += (byte[i]<<st);
        st--;
    }
    return x;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s input.file output.hmng [8/12/16/32/64]\n", argv[0]);
        return 0;
    }
    FILE *f = fopen(argv[1], "rb");
    FILE *t = fopen(argv[2], "w+b");
    int byte[8];
    printf("file: %s\n", argv[1]);
    printf("coded: %s\n", argv[2]);
    int c = 8;
    if (argc > 3) c = atoi(argv[3]);
    printf("coding length: %d\n\n", c);
    char mc[2];
    fwrite("HECC", 4, 1, t);
    sprintf(mc, "%d", c);
    fwrite(mc, 2, 1, t);
    if(c == 8)
    {
        int x, kod[12];
        x = fgetc(f);
        while(x != EOF)
        {
            tobit(x, byte);
            int g = 0;
            for(int i = 0; i < 12; i++)
            {
                if((i != 0)&&(i != 1)&&(i != 3)&&(i != 7))
                    kod[i] = byte[g++];
                else
                    kod[i] = 2;
            }
            kontrolbit(kod, 12);
            g = 0;
            while(g < 12)
            {
                for(int i = 0; i < 8; i++)
                {
                    if((i == 0)||(i == 1))
                        byte[i] = 0;
                    else
                        byte[i] = kod[g++];
                }
                fputc(todec(byte), t);
            }
            x = fgetc(f);
        }
    }
    else if(c == 12)
    {
        fprintf(stderr, "WARNING: with coding length %d end of file is not always processed correctly\n\n", c);
        int x, kod[17], g = 0, flag = 0;
        x = fgetc(f);
        while(x != EOF)
        {
            tobit(x, byte);
            if(flag == 0)
            {
                for(int i = 0; i < 8; i++)
                {
                    if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                        kod[g++] = byte[i];
                    else
                    {
                        kod[g] = 2;
                        g++;
                        i--;
                    }
                }
                x = fgetc(f);
                tobit(x, byte);
                for(int i = 0; i < 4; i++)
                {
                    if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                        kod[g++] = byte[i];
                    else
                    {
                        kod[g] = 2;
                        g++;
                        i--;
                    }
                }
                fseek(f, -1, SEEK_CUR);
                flag = 1;
            }
            else if(flag == 1)
            {
                for(int i = 4; i < 8; i++)
                {
                    if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                        kod[g++] = byte[i];
                    else
                    {
                        kod[g] = 2;
                        g++;
                        i--;
                    }
                }
                x = fgetc(f);
                tobit(x, byte);
                for(int i = 0; i < 8; i++)
                {
                    if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                        kod[g++] = byte[i];
                    else
                    {
                        kod[g] = 2;
                        g++;
                        i--;
                    }
                }
                flag = 0;
            }
            if(g == 17)
            {
                kontrolbit(kod, 17);
                g = 0;
                while(g < 17)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        if(i != 7)
                            byte[i] = 0;
                        else
                            byte[i] = kod[g++];
                    }
                    fputc(todec(byte), t);
                }
                g = 0;
            }
            x = fgetc(f);
        }
    }
    else if(c == 16)
    {
        fprintf(stderr, "WARNING: with coding length %d end of file is not always processed correctly\n\n", c);
        int x, kod[21], g = 0;
        x = fgetc(f);
        while(x != EOF)
        {
            tobit(x, byte);
            for(int i = 0; i < 8; i++)
            {
                if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                    kod[g++] = byte[i];
                else
                {
                    kod[g] = 2;
                    g++;
                    i--;
                }
            }
            if(g == 21)
            {
                kontrolbit(kod, 21);
                g = 0;
                while(g < 21)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        if(i == 0)
                            byte[i] = 0;
                        else
                            byte[i] = kod[g++];
                    }
                    fputc(todec(byte), t);
                }
                g = 0;
            }
            x = fgetc(f);
        }
    }
    else if(c == 32)
    {
        fprintf(stderr, "WARNING: with coding length %d end of file is not always processed correctly\n\n", c);
        int x, kod[38], g = 0;
        x = fgetc(f);
        while(x != EOF)
        {
            tobit(x, byte);
            for(int i = 0; i < 8; i++)
            {
                if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                    kod[g++] = byte[i];
                else
                {
                    kod[g] = 2;
                    g++;
                    i--;
                }
            }
            if(g == 38)
            {
                kontrolbit(kod, 38);
                g = 0;
                while(g < 38)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        if((i != 6)&&(i != 7))
                            byte[i] = 0;
                        else
                            byte[i] = kod[g++];
                    }
                    fputc(todec(byte), t);
                }
                g = 0;
            }
            x = fgetc(f);
        }
    }
    else if(c == 64)
    {
        fprintf(stderr, "WARNING: with coding length %d end of file is not always processed correctly\n\n", c);
        int x, kod[71], g = 0;
        x = fgetc(f);
        while(x != EOF)
        {
            tobit(x, byte);
            for(int i = 0; i < 8; i++)
            {
                if((g != 0)&&(g != 1)&&(g != 3)&&(g != 7)&&(g != 15)&&(g != 31)&&(g != 63))
                    kod[g++] = byte[i];
                else
                {
                    kod[g] = 2;
                    g++;
                    i--;
                }
            }
            if(g == 71)
            {
                kontrolbit(kod, 71);
                g = 0;
                while(g < 71)
                {
                    for(int i = 0; i < 8; i++)
                    {
                        if(i != 7)
                            byte[i] = 0;
                        else
                            byte[i] = kod[g++];
                    }
                    fputc(todec(byte), t);
                }
                g = 0;
            }
            x = fgetc(f);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: bad coding length %d, maybe 8/12/16/32/64\n\n", c);
    }
    fclose(f);
    fclose(t);
    return 0;
}
