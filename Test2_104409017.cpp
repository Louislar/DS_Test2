#include<iostream>
#include<fstream>

using namespace std;

class e
{
public:
    e()
    {

    }
    e(int r, int c, int v)
    {
        row=r;
        col=c;
        val=v;
    }
    int row;
    int col;
    int val;

};

int matrixMul(e a[], e b[], e c[])
{
    int aLength=a[0].val+1;
    int bLength=b[0].val+1;
    int cLength=1;

    //same a's column and b's row, multiply
    for(int i=1;i<aLength;i++)
    {
        for(int j=1;j<bLength;j++)
        {
            if(a[i].col==b[j].row)
            {
                c[cLength]=e(a[i].row, b[j].col, (a[i].val)*(b[j].val));
                cLength++;
            }
        }
    }

    //same column and row
    for(int i=1;i<cLength;i++)
    {
        for(int j=i+1;j<cLength;j++)
        {
            if(c[i].row==c[j].row&&c[i].col==c[j].col)
            {
                c[i]=e(c[i].row, c[i].col, c[i].val+c[j].val);
                c[j]=e(-1,-1,0);
            }
        }
    }
    int cLengthTemp=0;
    for(int i=0;i<cLength;i++)
    {
        if(c[i].val==0)
            cLengthTemp--;
    }
    for(int x=0;x<cLength;x++){
    for(int i=1;i<cLength;i++)
    {
        if(c[i].val==0)
        {
            for(int j=i;j<cLength-1;j++)
            {
                c[j]=c[j+1];
            }
        }
    }
    }
    cLength=cLength+cLengthTemp;
    c[0]=e(a[0].row, b[0].col,cLength-1);

    cout<<"----------\nA*B\n";
    for(int i=0;i<cLength;i++)
    {
        cout<<c[i].row<<" "
            <<c[i].col<<" "
            <<c[i].val<<endl;
    }

    return cLength;
}

int main()
{
    //input file name
    cout<<"input file name: "<<endl;
    char name[100];
    for(int i=0;i<100;i++) name[i]='\0';  //new add
    {
        int i=0;
        char temp;
        while(cin.get(temp))
        {
            if(temp=='\n') break;
            name[i]=temp;
            i++;
        }
    }
    ifstream ifs;
    ifs.open(name, ios::in);

    //input matrix
    e matrixa[100];
    e matrixb[100];
    e matrixc[100];
    int matrixaLength=1;
    int matrixbLength=1;
    int matrixcLength=1;
    char temp;
    int col=0;
    int totalcol=0;
    int totalrow=0;
    int totalval=0;
    int row=0;
    //matrixa input
    while(ifs.get(temp))
    {
        if(temp==' ')
         {
            col++;
            totalcol++;
         }
        else if(temp=='\n')
        {
            col=0;
            row++;
            totalrow++;
            totalcol++;              //new add
        }
        else if(temp=='|')
        {
            break;
        }
        else if(temp!='0')
        {
            matrixa[matrixaLength]=e(row, col, temp-48);
            matrixaLength++;
            totalval++;
        }

    }//while end

    /*******************new many digit situation******************/
    for(int p=0;p<matrixaLength;p++){
    for(int q=1;q<matrixaLength-1;q++)
    {
        if(matrixa[q].row==matrixa[q+1].row&&matrixa[q].col==matrixa[q+1].col)
        {
            matrixa[q].val=matrixa[q].val*10+matrixa[q+1].val;
            matrixa[q+1]=e(-1, -1, 0);
        }
    }
    for(int q=0;q<matrixaLength;q++)
    {
        if(matrixa[q].row==-1)
        {
            for(int w=q;w<matrixaLength-1;w++)
            {
                matrixa[w]=matrixa[w+1];
            }
            matrixaLength--;
            totalval--;
        }
    }
    }//for p end

    /****************new many digit situation-end********************/

    matrixa[0]=e(totalrow, totalcol/(totalrow), totalval);

    ifs.get(temp); //delete one line "ifs.get(temp);"
    col=0;
    totalcol=0;
    totalrow=0;
    totalval=0;
    row=0;
    //matrixb input
    while(ifs.get(temp))
    {
        if(temp==' '){
            col++;
            totalcol++;
        }
        else if(temp=='\n')
        {
            col=0;
            row++;
            totalrow++;
            totalcol++;              //new add
        }
        else if(temp=='|')
        {
            break;
        }
        else if(temp!='0')
        {
            matrixb[matrixbLength]=e(row, col, temp-48);
            matrixbLength++;
            totalval++;
        }

    }// while end

    /*******************new many digit situation******************/
    for(int p=0;p<matrixbLength;p++){
    for(int q=1;q<matrixbLength-1;q++)
    {
        if(matrixb[q].row==matrixb[q+1].row&&matrixb[q].col==matrixb[q+1].col)
        {
            matrixb[q].val=matrixb[q].val*10+matrixb[q+1].val;
            matrixb[q+1]=e(-1, -1, 0);
        }
    }
    for(int q=0;q<matrixbLength;q++)
    {
        if(matrixb[q].row==-1)
        {
            for(int w=q;w<matrixbLength-1;w++)
            {
                matrixb[w]=matrixb[w+1];
            }
            matrixbLength--;
            totalval--;
        }
    }
    }//for p end
    /****************new many digit situation-end********************/

    matrixb[0]=e(totalrow+1, (totalcol+1)/(totalrow+1), totalval);

    cout<<"A \n";
    for(int i=0;i<matrixaLength;i++)
    {
       cout<<matrixa[i].row<<" "
            <<matrixa[i].col<<" "
            <<matrixa[i].val<<endl;
    }
    cout<<"----------\nB \n";
    for(int i=0;i<matrixbLength;i++)
    {
        cout<<matrixb[i].row<<" "
            <<matrixb[i].col<<" "
            <<matrixb[i].val<<endl;
    }

    //multy
    matrixcLength=matrixMul(matrixa, matrixb, matrixc);

    /*//test
    cout<<"A: \n";
    for(int i=0;i<matrixaLength;i++)
    {
       cout<<matrixa[i].row<<" "
            <<matrixa[i].col<<" "
            <<matrixa[i].val<<endl;
    }
    cout<<"----------\nB: \n";
    for(int i=0;i<matrixbLength;i++)
    {
        cout<<matrixb[i].row<<" "
            <<matrixb[i].col<<" "
            <<matrixb[i].val<<endl;
    }*/


}
