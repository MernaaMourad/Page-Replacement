#include <stdio.h>
#include <stdlib.h>


// Comparing both the strings.
int compare(char a[],char b[])
{

    int flag=0,i=0;  // integer variables declaration
    while(a[i]!='\0' &&b[i]!='\0')  // while loop
    {
        if(a[i]!=b[i])
        {
            flag=1;
            break;
        }
        i++;
    }
    if(flag==0)
        return 0;
    else
        return 1;

}
int findLRU(int time[], int frameNo)
{
    int i, minimum = time[0], pos = 0;
//least recently used has the min value in time array
    for(i = 1; i < frameNo; ++i)
    {
        if(time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}
void lru(int *pages,int frameNo,int size)
{
//Creating array for block storage
    int frames[frameNo];
//flags
    int flag1 ;
    int flag2 ;
//the counter is used to keep track of the least recently used if its minimum the it is the least recently used
    int counter=0;
//time array used to store and update counter for each page in frames
    int time[frameNo];
    int i,j,pos,pageFaults=0;
    for(i = 0; i < frameNo; ++i)
    {
        frames[i] = -1; //initialize all frames to =-1 indicating its empty
    }
    //passing all over the pages
    for(i = 0; i < size; ++i)
    {
        flag1 = flag2 = 0;//each page initialize flags

        for(j = 0; j < frameNo; ++j)
        {
            //page hit
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;//monitor use
                printf("%02d     ",pages[i]);
                flag1 = flag2 = 1;
                break;
            }
        }

        if(flag1 == 0)
        {
            for(j = 0; j < frameNo; ++j)
            {
                //if there is still empty frame and page not found
                if(frames[j] == -1)
                {
                    counter++;
                    frames[j] = pages[i];//add page to frames
                    time[j] = counter;
                    printf("%02d     ",pages[i]);
                    flag2 = 1;//indicates that the page was added to frame no need to replace
                    break;
                }
            }
        }
        //full and page fault so lru replacement occurs
        if(flag2 == 0)
        {
            pos = findLRU(time, frameNo);//returns index of least recently used in frames
            counter++;
            pageFaults++;
            frames[pos] = pages[i];//add page in frames in position of least recently used
            time[pos] = counter;
            printf("%02d F   ",pages[i]);
        }
        //print
        for(j = 0; j < frameNo; ++j)
        {
            if(frames[j]!=-1)
                printf("%02d ", frames[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}



void fifo(int *pages,int frameNo,int size)
{
//Creating array for block storage
    int frames[frameNo];
    int flag1,flag2;
    int i,j,pageFaults=0;
    for(i = 0; i < frameNo; i++)
    {
        frames[i] = -1; //initialize all frames to =-1 indicating its empty
    }
    //passing all over the pages
    for(i = 0; i < size; ++i)
    {
        flag1 = flag2 = 0;//each page initialize flags

        for(j = 0; j < frameNo; j++)
        {
            //page hit
            if(frames[j] == pages[i])
            {
                printf("%02d     ",pages[i]);
                flag1=flag2=1;
                break;
            }
        }

        if(flag1==0)
        {

            for(j = 0; j < frameNo; ++j)
            {
                //if there is still empty frame and page not found
                if(frames[j] == -1)
                {
                    frames[j] = pages[i];//add page to frames
                    printf("%02d     ",pages[i]);
                    flag2 = 1;//indicates that the page was added to frame no need to replace
                    break;
                }
            }
        }
        //full and page fault so fifo replacement occurs
        if(flag2 == 0)
        {

            pageFaults++;
            frames[(pageFaults-1)%frameNo] = pages[i];//add page in frames in position of the first one that entered frame
            printf("%02d F   ",pages[i]);
        }
        //print
        for(j = 0; j < frameNo; ++j)
        {
            if(frames[j]!=-1)
                printf("%02d ", frames[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}


void optimal(int *pages,int frameNo,int size)
{
//Creating array for block storage
    int frames[frameNo];
    int tempFrames[frameNo];
    int flag1,flag2,flag3;
    int i,j,k,max,pos,pageFaults=0;
    for(i = 0; i < frameNo; i++)
    {
        frames[i] = -1; //initialize all frames to =-1 indicating its empty
    }
    //passing all over the pages
    for(i = 0; i < size; ++i)
    {
        flag1 = flag2 = 0;//each page initialize flags

        for(j = 0; j < frameNo; j++)
        {
            //page hit
            if(frames[j] == pages[i])
            {
                printf("%02d     ",pages[i]);
                flag1=flag2=1;
                break;
            }
        }
//definition of the flag at the starting of the string still empty frame and page not found
        if(flag1 == 0)
        {
            for(j = 0; j < frameNo; ++j)
            {
                if(frames[j] == -1)
                {
                    frames[j] = pages[i];
                    printf("%02d     ",pages[i]);
                    flag2 = 1;
                    break;
                }
            }
        }
// definition of the flag at the mid position full and page fault so  replacement occurs
        if(flag2 == 0)
        {
            flag3 =0;
//initialize temp array
            for(j = 0; j <frameNo; ++j)
            {
                tempFrames[j] = -1;
//Check pages after the page needed to be replaced either one not repeated if not found then page referenced farther than others in future
//if there exits page that occurs again add to temp array
                for(k = i + 1; k < size; ++k)
                {
                    if(frames[j] == pages[k])
                    {
                        tempFrames[j] = k;
                        break;
                    }
                }
            }
//if temp array have empty pos meaning that no  page in frame will not be used later
            for(j = 0; j < frameNo; ++j)
            {
                if(tempFrames[j] == -1)
                {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }
//page referenced farther than others in future
            if(flag3 ==0)
            {
                max = tempFrames[0];
                pos = 0;
                for(j = 1; j < frameNo; ++j)
                {
                    if(tempFrames[j] > max)
                    {
                        max = tempFrames[j];
                        pos = j;
                    }
                }
            }
            frames[pos] = pages[i];
            pageFaults++;
            printf("%02d F   ",pages[i]);
        }
//print
        for(j = 0; j < frameNo; ++j)
        {
            if(frames[j]!=-1)
                printf("%02d ", frames[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}


void clock(int *pages,int frameNo,int size)
{
//Creating array for block storage
    int frames[frameNo];
    int useBit[frameNo];
    int flag1,flag2;
    int i,j,pointer=0,pageFaults=0;
    for(i = 0; i < frameNo; i++)
    {
        useBit[i]=-1;
        frames[i] = -1; //initialize all frames to =-1 indicating its empty
    }
    //passing all over the pages
    for(i = 0; i < size; ++i)
    {
        flag1 = flag2 = 0;//each page initialize flags

        for(j = 0; j < frameNo; j++)
        {
            //page hit
            if(frames[j] == pages[i])
            {
                printf("%02d     ",pages[i]);
                flag1=flag2=1;

           if(useBit[j]==0)
            {useBit[j]=1;}
                break;
            }
        }

        if(flag1==0)
        {

            for(j = 0; j < frameNo; ++j)
            {
                //if there is still empty frame and page not found
                if(frames[j] == -1)
                {
                    frames[j] = pages[i];//add page to frames
                    useBit[j]=1;
                    pointer=(pointer+1)%frameNo;
                    printf("%02d     ",pages[i]);
                    flag2 = 1;//indicates that the page was added to frame no need to replace
                    break;
                }
            }
        }
        //full and page fault so clock replacement occurs
        if(flag2 == 0)
        {

            pageFaults++;
           // printf("USEBIT  BEFORE WHILE=%d\n",useBit[pointer]);
            while(useBit[pointer]==1)
            {
                useBit[pointer]=0;
                pointer=(pointer+1)%frameNo;
               //printf("pointer IN WHILE=%d\n",pointer);
                //printf("pointer before =%d\n",pointer);
            }
            frames[pointer] = pages[i];//add page in frames in position of the first one that entered frame
            useBit[pointer]=1;
            pointer=(pointer+1)%frameNo;
           // printf("pointer AFTER WHILE=%d\n",pointer);
            printf("%02d F   ",pages[i]);
        }
        //printf("pointer=%d USEBIT %d\n",pointer,useBit[pointer]);
        for(j = 0; j < frameNo; ++j)
        {
            // printf(" use bit of %d is %d\n",j,useBit[j]);
            if(frames[j]!=-1)
                printf("%02d ", frames[j]);
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", pageFaults);
}

int main()
{
    char type[80];
    int frameNo;
    int *pages,i,s=1;

    scanf("%d",&frameNo);
    getchar();
    fgets(type,80,stdin);
    printf("Replacement Policy = %s",type);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    pages= (int*)malloc(sizeof(int));

    do
    {
        scanf("%d", &i);
        if(i == -1)
            break;
        pages[s-1] = i;
        int *temp=realloc(pages, ++s*sizeof(int));
        if(temp)
        {
            pages=temp;
        }
        else
        {
            printf("reallocation fail\n");
            return 0;
        }
    }
    while(1);

    char*OPTIMAL="OPTIMAL";
    char*FIFO="FIFO";
    char*LRU="LRU";
    char*CLOCK="CLOCK";
    if(compare(OPTIMAL,type)==0)
        optimal(pages, frameNo, s-1);
    else if(compare(FIFO,type)==0)
        fifo(pages, frameNo, s-1);
    else if(compare(LRU,type)==0)
        lru(pages, frameNo, s-1);
    else if(compare(CLOCK,type)==0)
        clock(pages, frameNo, s-1);
    free(pages);
    return 0;
}