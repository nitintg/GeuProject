#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define o_c 12
#define bg 16
#define i_c 10
#define h_c 10
#define l_c 1
enum
{
    KEY_ESC=27,
    ARROW_UP=256+72,
    ARROW_DOWN=256+80,
    ARROW_LEFT=256+75,
    ARROW_RIGHT=256+77
};
static int get_code(void)
{
    int h=getch();
    if(h==0 || h==224)
        h=256+getch();
    return h;
}
void SetColorAndBackground(int ForgC, int BackC)  /*function for setting color for text and background*/
{
    WORD wColor =((BackC)<<5) + (ForgC);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
    return;
}
int about() /*function about project*/
{
    system("cls");
    SetColorAndBackground(h_c,bg);
    printf("\n This is Graphic Era University sessional mini-project. This is a SIC assembler generating an\nobject file as an output.\n\t\t\t\tG O O D       L U C K\n");
    printf("\nDevelopment Team:-\n\n");
    printf("\n\n* Nitin Kumar Tyagi\n  CSE B\t4rd Sem\tRoll no. = 43\tUniversity Roll no. = 2007504\n");
    printf("\n\n* Parth Rawat\n  CSE B\t4rd Sem\tRoll no. = 46\tUniversity Roll no. = 2007507\n");
    getch();
    return 1;
}

unsigned long Dec(char pc[10])
{
    int len = 0, i;
    const int base = 16;
    unsigned long int num = 0;
    len = strlen(pc);
    for(i = 0; i < len; i++)
    {
        if(pc[i] >= 48 && pc[i] <= 57)
            num += (((int)(pc[i])) - 48) * pow(base, len - i -1);
        else if(pc[i] >= 65 && pc[i] <= 70)
            num += (((int)(pc[i])) - 55) * pow(base, len - i -1);
        else if(pc[i] >= 97 && pc[i] <= 102)
            num += (((int)(pc[i])) - 87) * pow(base, len - i -1);
    }
    return num;
}

int record()
{
    FILE *fp1, *fp2, *fp3;
    char Ad[10], lb[20], mne[20], opd[20], obc[10], pc[10], siz[10], rcd[90];
    unsigned long int num1, num2;
    int lim, flag = 0, siz2;
    fp1 = fopen("intermediate2.txt","r");
    fscanf(fp1,"%s%s%s%s%s",opd,lb,mne,Ad,obc);
    fp2 = fopen("size.txt","r");
    fscanf(fp2,"%s",siz);
    fclose(fp2);
    fp3 = fopen("Record.txt","w");
    if(!strcmp(mne,"START"))
    {
        printf("H^%s^00%s^%s\n",lb,Ad,siz);
        fprintf(fp3,"H^%s^00%s^%s\n",lb,Ad,siz);
        fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
        while(strcmp(mne,"END"))
        {
            if(flag == 0)
            {
                printf("T^00%s",Ad);
                fprintf(fp3,"T^00%s",Ad);
                flag = 1;
            }
            rcd[0] = '\0';
            for(lim = 30, siz2 = 0; (lim > 0) && (strcmp(mne,"END")) ; )
            {
                if(!strcmp(mne,"FIX") || !strcmp(mne,"FLOAT"))
                {
                    lim = lim - 1;
                    if(lim >= 0)
                    {
                        siz2 = lim;
                        strcat(rcd,"^");
                        strcat(rcd,obc);
                        fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                    }
                    else
                        break;
                }
                else if(mne[0] == '+')
                {
                    lim = lim - 4;
                    if(lim >= 0)
                    {
                        siz2 = lim;
                        strcat(rcd,"^");
                        strcat(rcd,obc);
                        fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                    }
                    else
                        break;
                }
                else if((strlen(opd) == 3 && opd[1] == ',') || (strlen(opd) == 1 && isalpha(opd[0])))
                {
                    lim = lim - 2;
                    if(lim >= 0)
                    {
                        siz2 = lim;
                        strcat(rcd,"^");
                        strcat(rcd,obc);
                        fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                    }
                    else
                        break;
                }
                else if(strcmp(mne,"BYTE") && strcmp(mne,"RESW") && strcmp(mne,"RESB") && strcmp(mne,"END"))
                {
                    lim = lim - 3;
                    if(lim >= 0)
                    {
                        siz2 = lim;
                        strcat(rcd,"^");
                        strcat(rcd,obc);
                        fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                    }
                    else
                        break;
                }
                else if((!strcmp(mne,"RESW") || !strcmp(mne,"RESB")) && strcmp(mne,"END"))
                {
                    fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                    break;
                }
                else if(strcmp(mne,"END") && !strcmp(mne,"BYTE"))
                {
                    if(opd[0] == 'X')
                    {
                        lim = lim - 1;
                        if(lim >= 0)
                        {
                            siz2 = lim;
                            strcat(rcd,"^");
                            strcat(rcd,obc);
                            fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                        }
                        else
                            break;
                    }
                    else if(opd[0] == 'C')
                    {
                        lim = lim - (strlen(opd) - 3);
                        if(lim >= 0)
                        {
                            siz2 = lim;
                            strcat(rcd,"^");
                            strcat(rcd,obc);
                            fscanf(fp1,"%s%s%s%s%s",Ad,lb,mne,opd,obc);
                        }
                        else
                            break;
                    }
                }
            }
            if(lim < 30)
            {
                siz2 = 30 - siz2;
                if(siz2 <= 9)
                {
                    printf("^0%d%s\n",siz2,rcd);
                    fprintf(fp3,"^0%d%s\n",siz2,rcd);
                }
                else
                {
                    sprintf(siz,"%X",siz2);
                    strupr(siz);
                    printf("^%s%s\n",siz,rcd);
                    fprintf(fp3,"^%s%s\n",siz,rcd);
                }
                flag = 0;
            }
        }
    }
    fclose(fp1);
    fclose(fp3);
    return 0;
}


int ObjCode()
{
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    char Ad[10], S_Ad[10], op[10], st[10], lb[50], mne[50], opd[50], sym[50], op2[10], len[10], temp[50],temp1[30],temp2[30],temp3[30];
    int op1[10], i, j = 0, len2;
    long int len3, temp4;
    float flt;
    fp1 = fopen("intermediate.txt","r");
    fp2 = fopen("size.txt","r");
    fp3 = fopen("optab.txt","r");
    fp4 = fopen("symtab.txt","r");
    fp5 = fopen("intermediate2.txt","w");
    printf("Adress\tLable\tCommand\tOperand\t\tObject code\n\n");
    fscanf(fp1,"%s%s%s%s",Ad,lb,mne,opd);
    printf("%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mne,opd);
    fprintf(fp5,"%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mne,opd);
    if(!strcmp(mne,"START"))
    {
        strcpy(st,opd);
        fscanf(fp2,"%s",&len);
    }
    fscanf(fp1,"%s%s%s%s",Ad,lb,mne,opd);
    while(strcmp(mne,"END"))
    {
        fscanf(fp3,"%s %s",op2,op);
        if(strcmp(opd,"-") && strcmp(mne,"BYTE") && strcmp(mne,"WORD") && strcmp(mne,"RSUB") && strcmp(mne,"RESW") && strcmp(mne,"RESB"))
        while(!feof(fp3))
        {
            if(mne[0] == '+')
            {
                temp1[0] = '+';
                temp1[1] = '\0';
                strcat(temp1,op2);
            }
            if(!strcmp(mne,op2) || !strcmp(mne,temp1))
            {
                printf("%s\t%s\t%s\t%s\t",Ad,lb,mne,opd);
                fprintf(fp5,"%s\t%s\t%s\t%s\t",Ad,lb,mne,opd);
                while(1)
                {
                    fscanf(fp4,"%s%s",S_Ad,sym);
                    if(feof(fp4))
                        break;
                    if(opd[0] == '#' && !strcmp(mne,temp1))
                    {
                        if(isalpha(opd[1]))
                        {
                            temp3[0] = '#';
                            temp3[1] = '\0';
                            strcat(temp3,sym);
                            if(!strcmp(opd,temp3))
                            {
                                if(Dec(S_Ad) > Dec(Ad))
                                {
                                    printf("\t%s4C%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s4C%s\n",op,S_Ad);
                                }
                                else
                                {
                                    printf("\t%s54%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s54%s\n",op,S_Ad);
                                }
                                break;
                            }
                        }
                        else
                        {
                            for(i = 1; i < strlen(opd); i++)
                                opd[i-1] = opd[i];
                            opd[i-1] = '\0';
                            temp4 = atoi(opd);
                            sprintf(opd,"%X",temp4);
                            printf("\t%s44",op);
                            fprintf(fp5,"\t%s44",op);
                            temp4 = strlen(opd);
                            for(i = 0; i < (4 - temp4); i++)
                            {
                                printf("0");
                                fprintf(fp5,"0");
                            }
                            printf("%s\n",opd);
                            fprintf(fp5,"%s\n",opd);
                            break;
                        }
                    }
                    else if(opd[0] == '#' && strcmp(mne,temp1))
                    {
                        if(isalpha(opd[1]))
                        {
                            temp3[0] = '#';
                            temp3[1] = '\0';
                            strcat(temp3,sym);
                            if(!strcmp(opd,temp3))
                            {
                                if(Dec(S_Ad) > Dec(Ad))
                                {
                                    printf("\t%s48%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s48%s\n",op,S_Ad);
                                }
                                else
                                {
                                    printf("\t%s50%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s50%s\n",op,S_Ad);
                                }
                                break;
                            }
                        }
                        else
                        {
                            for(i = 1; i < strlen(opd); i++)
                                opd[i-1] = opd[i];
                            opd[i-1] = '\0';
                            temp4 = atoi(opd);
                            sprintf(opd,"%X",temp4);
                            printf("\t%s40",op);
                            fprintf(fp5,"\t%s40",op);
                            temp4 = strlen(opd);
                            for(i = 0; i < (4 - temp4); i++)
                            {
                                printf("0");
                                fprintf(fp5,"0");
                            }
                            printf("%s\n",opd);
                            fprintf(fp5,"%s\n",opd);
                            break;
                        }
                    }
                    else if(opd[0] == '@' && !strcmp(mne,temp1))
                    {
                        temp3[0] = '@';
                        temp3[1] = '\0';
                        strcat(temp3,sym);
                        if(!strcmp(opd,temp3))
                        {
                            if(Dec(S_Ad) > Dec(Ad))
                            {
                                temp4 = Dec(S_Ad) - (Dec(Ad) + 3);
                                sprintf(S_Ad,"%X",temp4);
                                printf("\t%s8C%s\n",op,S_Ad);
                                fprintf(fp5,"\t%s8C%s\n",op,S_Ad);
                            }
                            else
                            {
                                temp4 = (Dec(Ad) + 3) - Dec(S_Ad);
                                sprintf(S_Ad,"%X",temp4);
                                printf("\t%s94%s\n",op,S_Ad);
                                fprintf(fp5,"\t%s94%s\n",op,S_Ad);
                            }
                            break;
                        }
                    }
                    else if(opd[0] == '@' && strcmp(mne,temp1))
                    {
                        temp3[0] = '@';
                        temp3[1] = '\0';
                        strcat(temp3,sym);
                        if(!strcmp(opd,temp3))
                        {
                            if(Dec(S_Ad) > Dec(Ad))
                            {
                                temp4 = Dec(S_Ad) - (Dec(Ad) + 3);
                                sprintf(S_Ad,"%X",temp4);
                                printf("\t%s88",op);
                                fprintf(fp5,"\t%s88",op);
                                temp4 = strlen(S_Ad);
                                for(i = 0; i < (4 - temp4); i++)
                                {
                                    printf("0");
                                    fprintf(fp5,"0");
                                }
                                printf("%s\n",S_Ad);
                                fprintf(fp5,"%s\n",S_Ad);
                            }
                            else
                            {
                                temp4 = (Dec(Ad) + 3) - Dec(S_Ad);
                                sprintf(S_Ad,"%X",temp4);
                                printf("\t%s90%s\n",op,S_Ad);
                                fprintf(fp5,"\t%s90%s\n",op,S_Ad);
                            }
                            break;
                        }
                    }
                    else if(!strcmp(mne,temp1))
                    {
                        temp4 = strlen(opd);
                        if(opd[temp4-1] == 'X')
                        {
                            opd[temp4-2] == '\0';
                            if(strcmp(opd,sym))
                            {
                                if(Dec(S_Ad) > Dec(Ad))
                                {
                                    temp4 = Dec(S_Ad) - (Dec(Ad) + 3);
                                    sprintf(S_Ad,"%X",temp4);
                                    printf("\t%s2C%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s2C%s\n",op,S_Ad);
                                }
                                else
                                {
                                    temp4 = (Dec(Ad) + 3) - Dec(S_Ad);
                                    sprintf(S_Ad,"%X",temp4);
                                    printf("\t%s34%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s34%s\n",op,S_Ad);
                                }
                                break;
                            }
                        }
                        else
                        {
                            if(strcmp(opd,sym))
                            {
                                if(Dec(S_Ad) > Dec(Ad))
                                {
                                    printf("\t%s0C%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s0C%s\n",op,S_Ad);
                                }
                                else
                                {
                                    printf("\t%s14%s\n",op,S_Ad);
                                    fprintf(fp5,"\t%s14%s\n",op,S_Ad);
                                }
                                break;
                            }

                        }
                    }
                    else if(!strcmp(mne,"FIX") || !strcmp(mne,"FLOAT"))
                    {
                        if(!strcmp(mne,"FIX"))
                        {
                            printf("\t%s01000%d",op,atoi(opd));
                            fprintf(fp5,"\t%s01000%d",op,atoi(opd));
                        }
                        else
                        {
                            flt = (float)atoi(opd);
                            printf("\t%s01000%f",op,opd);
                            fprintf(fp5,"\t%s01000%f",op,flt);
                        }
                        break;
                    }
                    else if((strlen(opd) == 3 && opd[1] == ',') || (strlen(opd) == 1 && isalpha(opd[0])))
                    {
                        printf("\t%s0200",op);
                        fprintf(fp5,"\t%s0200",op);
                        temp4 = strlen(opd);
                        if(strlen(opd) == 1 && isalpha(opd[0]))
                        {
                            printf("0%c\n",opd[0]);
                            fprintf(fp5,"0%c\n",opd[0]);
                        }
                        else
                        {
                            printf("%c%c\n",opd[0],opd[2]);
                            fprintf(fp5,"%c%c\n",opd[0],opd[2]);
                        }
                        break;
                    }
                    else
                    {
                        temp4 = strlen(opd);
                        if(!strcmp(opd,sym))
                        {
                            if(Dec(S_Ad) > Dec(Ad))
                            {
                                printf("\t%s08%s\n",op,S_Ad);
                                fprintf(fp5,"\t%s08%s\n",op,S_Ad);
                            }
                            else
                            {
                                printf("\t%s10%s\n",op,S_Ad);
                                fprintf(fp5,"\t%s10%s\n",op,S_Ad);
                            }
                            break;
                        }
                        else if(opd[temp4-1] == 'X')
                        {
                            opd[temp4-2] == '\0';
                            if(strcmp(opd,sym))
                            {
                                if(Dec(S_Ad) > Dec(Ad))
                                {
                                    temp4 = Dec(S_Ad) - (Dec(Ad) + 3);
                                    sprintf(S_Ad,"%X",temp4);
                                    printf("%s28%s\n",op,S_Ad);
                                    fprintf(fp5,"%s28%s\n",op,S_Ad);
                                }
                                else
                                {
                                    temp4 = (Dec(Ad) + 3) - Dec(S_Ad);
                                    sprintf(S_Ad,"%X",temp4);
                                    printf("%s30%s\n",op,S_Ad);
                                    fprintf(fp5,"%s30%s\n",op,S_Ad);
                                }
                                break;
                            }
                        }
                    }
                }
                break;
            }
            else
                fscanf(fp3,"%s%s",op2,op);
        }
        if(!strcmp(mne,"BYTE") || !strcmp(mne,"WORD") || !strcmp(mne,"RSUB"))
        {
            if(!strcmp(mne,"WORD"))
            {
                printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                fprintf(fp5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                sprintf(opd,"%X",atoi(opd));
                len2 = strlen(opd);
                for(i = 0; i < (6 - len2); i++)
                {
                    printf("0");
                    fprintf(fp5,"0");
                }
                printf("%s\n",opd);
                fprintf(fp5,"%s\n",opd);
            }
            else if(!strcmp(mne,"RSUB"))
            {
                printf("%s\t%s\t%s\t%s\t\t4F000000\n",Ad,lb,mne,opd);
                fprintf(fp5,"%s\t%s\t%s\t%s\t\t4F000000\n",Ad,lb,mne,opd);
            }
            else
            {
                len2 = strlen(opd);
                if(opd[0] == 'X')
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                    fprintf(fp5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                    for(i = 2; i < (len2 - 1); i++)
                    {
                        printf("%c",opd[i]);
                        fprintf(fp5,"%c",opd[i]);
                    }
                }
                else if((opd[0] == 'C'))
                {
                    printf("%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                    fprintf(fp5,"%s\t%s\t%s\t%s\t\t",Ad,lb,mne,opd);
                    len2 = strlen(opd);
                    for(i = 2; i < (len2 - 1); i++)
                    {
                        printf("%X",opd[i]);
                        fprintf(fp5,"%X",opd[i]);
                    }
                }
                printf("\n");
                fprintf(fp5,"\n");
            }
        }
        if(!strcmp(mne,"RESW") || !strcmp(mne,"RESB"))
        {
            printf("%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mne,opd);
            fprintf(fp5,"%s\t%s\t%s\t%s\t\t-\n",Ad,lb,mne,opd);
        }
        fscanf(fp1,"%s%s%s%s",Ad,lb,mne,opd);
        fclose(fp3);
        fclose(fp4);
        fp3 = fopen("optab.txt","r");
        fp4 = fopen("symtab.txt","r");
    }
    if(!strcmp(mne,"END"))
    {
        printf("%s\t-\tEND\t-\n",Ad);
        fprintf(fp5,"%s\t-\tEND\t-\n",Ad);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    return 0;
}


int Addressing()
{
    FILE *fp1, *fp2, *fp3, *fp4;
    char nam[30], opc[20], lb[50], otp[20], opd[50], Ad[10], pc[10], o[10];
    int flag, len, len2, i;
    unsigned long num;
    printf("Please Enter the file name: ");
    gets(nam);
    fp1 = fopen(nam,"r");
    fscanf(fp1,"%s %s %s",lb,opc,Ad);
    if(!strcmp(opc,"START"))
    {
        strcpy(pc,Ad);
        fp2 = fopen("intermediate.txt","w");
        fprintf(fp2,"-\t%s\t%s\t%s\n",lb,opc,pc);
        printf("\n\n\t%s\t%s\t%s\n",lb,opc,pc);
        fscanf(fp1,"%s %s %s",lb,opc,opd);
    }
    else
    {
        pc[0] = '0';
        pc[1] = '\0';
    }
    fp3 = fopen("symtab.txt","w");
    while(!feof(fp1))
    {
        len2 = strlen(pc);
        if(strcmp(opc,"BASE"))
        for(i = 0; i < (4 - len2); i++)
        {
            fprintf(fp2,"0");
            printf("0");
        }
        if(strcmp(opc,"BASE"))
        {
            fprintf(fp2,"%s",pc);
            printf("%s",pc);
        }
        else
        {
            fprintf(fp2,"-",pc);
            printf("-",pc);
        }
        fprintf(fp2,"\t%s\t%s\t%s\n",lb,opc,opd);
        printf("\t%s\t%s\t%s\n",lb,opc,opd);
        if(strcmp(lb,"-"))
        {
            len2 = strlen(pc);
            for(i = 0; i < (4 - len2); i++)
            {
                fprintf(fp3,"0");
            }
            fprintf(fp3,"%s\t%s\n",pc,lb);
        }
        fp4 = fopen("optab.txt","r");
        fscanf(fp4,"%s %S",otp,o);
        while(!feof(fp4))
        {
            if(!strcmp(opc,otp) && strcmp(opc,"RSUB"))
            {
                num = Dec(pc);
                if(!strcmp(opc,"FIX") || !strcmp(opc,"FLOAT"))
                    num = num + 1;
                else if(strlen(opd) == 1 || (strlen(opd) == 3 && opd[1] == ','))
                    num = num + 2;
                else
                    num = num + 3;
                sprintf(pc,"%X",num);
                break;
            }
            else if(opc[0] == '+')
            {
                num = num + 4;
                sprintf(pc,"%X",num);

                break;
            }
            fscanf(fp4,"%s %S",otp,o);
        }
        fclose(fp4);
        if(!strcmp(opc,"WORD") || !strcmp(opc,"RSUB"))
        {
            num = Dec(pc);
            num = num + 3;
            sprintf(pc,"%X",num);

        }
        else if(!strcmp(opc,"RESW"))
        {
            num = Dec(pc);
            num = num + (3 * atoi(opd));
            sprintf(pc,"%X",num);

        }
        else if(!strcmp(opc,"BYTE"))
        {
            if(opd[0] == 'X')
            {
                num = Dec(pc);
                num = num + 1;
                sprintf(pc,"%X",num);

            }
            else
            {
                num = Dec(pc);
                num = num + (strlen(opd) - 3);
                sprintf(pc,"%X",num);

            }
        }
        else if(!strcmp(opc,"RESB"))
        {
            num = Dec(pc);
            num = num + atoi(opd);
            sprintf(pc,"%X",num);

        }
        fscanf(fp1,"%s %s %s",lb,opc,opd);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    if(!strcmp(opc,"END"))
    {
        num = Dec(pc);
        sprintf(pc,"%X",(num - Dec(Ad)));

        printf("\nProgram Size= %s\n",pc);
        fp1 = fopen("Size.txt","w");
        fprintf(fp1,"%s",pc);
        fclose(fp1);
    }
    return 0;
}

int main()
{
    char nam[30], sto[30], lb[20], Ad[20], mne[20], opd[30];
    long long int n,temp,p=10,op=1,h;
    FILE *fp1;
    while(1)
    {
        while(1)
        {
            system("cls");
            SetColorAndBackground(h_c,bg);
            printf("\n\n\n\n\n\n\t\t\tA S S E M B L E R\t\t\t\n\nO P T I O N S\n");
            if(op==1)
            {
                SetColorAndBackground(h_c,bg);
                printf("1).\tRun A Program\n");
            }
            else
            {
                SetColorAndBackground(l_c,bg);
                printf("1).\tRun A Program\n");
            }
            if(op==2)
            {
                SetColorAndBackground(h_c,bg);
                printf("2).\tCreate New Program\n");
            }
            else
            {
                SetColorAndBackground(l_c,bg);
                printf("2).\tCreate New Program\n");
            }
            if(op==3)
            {
                SetColorAndBackground(h_c,bg);
                printf("3).\tAbout\n");
            }
            else
            {
                SetColorAndBackground(l_c,bg);
                printf("3).\tAbout\n");
            }
            if(op==4)
            {
                SetColorAndBackground(h_c,bg);
                printf("4).\tExit\n");
            }
            else
            {
                SetColorAndBackground(l_c,bg);
                printf("4).\tExit\n");
            }
            h=get_code();
            if(h!=13)
            {
                switch(h)
                {
                    case ARROW_UP:  if(op>1)
                                    {
                                        op--;
                                    }
                                    else
                                    {
                                        op=4;
                                    }
                                    break;
                    case ARROW_DOWN:    if(op<4)
                                        {
                                            op++;
                                        }
                                        else
                                        {
                                            op=1;
                                        }
                                        break;
                    case ARROW_LEFT:    if(op>1)
                                        {
                                            op--;
                                        }
                                        else
                                        {
                                            op=4;
                                        }
                                        break;
                    case ARROW_RIGHT:   if(op<4)
                                        {
                                            op++;
                                        }
                                        else
                                        {
                                            op=1;
                                        }
                                        break;
                }
            }
            else
            {
                break;
            }
        }
        system("cls");
        switch(op)
        {
        case 1: Addressing();
                ObjCode();
                system("cls");
                record();
                op=1;
                getch();
                system("cls");
                break;
        case 2: SetColorAndBackground(o_c,bg);
                printf("\n Enter the name for Input file:");
                fflush(stdin);
                SetColorAndBackground(i_c,bg);
                gets(nam);
                fp1=fopen(nam,"w");
                fflush(stdin);
                SetColorAndBackground(o_c,bg);
                SetColorAndBackground(i_c,bg);
                printf("Enter program name: ");
                gets(nam);
                printf("Enter starting address of program: ");
                gets(Ad);
                fprintf(fp1,"%s\tSTART\t%s\n",nam,Ad);
                while(1)
                {
                    scanf("%s%s%s",lb,mne,opd);
                    fprintf(fp1,"%s\t%s\t%s\n",lb,mne,opd);
                    if(!strcmp(mne,"END"))
                    {
                        system("cls");
                        printf("\n\n\n\t\t\t\tProgram Created");
                        Sleep(1000);
                        break;
                    }
                }
                fclose(fp1);
                op=2;
                break;
        case 3: printf("\n\n\t\t\t\tL O A D I N G _ ");
                Sleep(600);
                system("cls");
                printf("\n\n\t\t\t\tL O A D I N G _ _");
                Sleep(400);
                system("cls");
                printf("\n\n\t\t\t\tL O A D I N G _ _ _");
                Sleep(200);
                system("cls");
                about();
                op=3;
                break;
        case 4: printf("\n\n\t\t\t\t\tE X I T I N G _ ");
                Sleep(400);
                system("cls");
                printf("\n\n\t\t\t\t\tE X I T I N G _ _");
                Sleep(200);
                system("cls");
                printf("\n\n\t\t\t\t\tE X I T I N G _ _ _");
                Sleep(100);
                system("cls");
                SetColorAndBackground(h_c,bg);
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tB Y E");
                Sleep(1200);
                exit(1);
        }
    }
    return 0;
}
