#include <iostream>
int main()
{
        int count=0;
        for(int a=0;a<8;a++)
        {
                for(int b=0;b<8;b++)
                {
                        if(b==a||b==a+1||b==a-1)
                                continue;
                        else
                                for(int c=0;c<8;c++)
                                {
                                        if(c==a||c==a+2||c==a-2||c==b||c==b+1||c==b-1)
                                                continue;
                                        else
                                                for(int d=0;d<8;d++)
                                                {
                                                        if(d==a||d==a+3||d==a-3||d==b||d==b+2||d==b-2||d==c||d==c+1||d==c-1)
                                                                continue;
                                                        else
                                                                for(int e=0;e<8;e++)
                                                                {
                                                                        if(e==a||e==a+4||e==a-4||e==b||e==b+3||e==b-3||e==c||e==c+2||e==c-2||e==d||
                                                                                        e==d+1||e==d-1)
                                                                                continue;
                                                                        else
                                                                                for(int f=0;f<8;f++)
                                                                                {
                                                                                        if(f==a||f==a+5||f==a-5||f==b||f==b+4||f==b-4||f==c||f==c+3||
                                                                                                        f==c-3||f==d||f==d+2||f==d-2||f==e||f==e+1||f==e-1)
                                                                                                continue;
                                                                                        else
                                                                                                for(int g=0;g<8;g++)
                                                                                                {
                                                                                                        if(g==a||g==a+6||g==a-6||g==b||g==b+5||g==b-5||
                                                                                                                        g==c||g==c+4||g==c-4||g==d||g==d+3||
                                                                                                                        g==d-3||g==e||g==e+2||g==e-2||g==f||
                                                                                                                        g==f+1||g==f-1)
                                                                                                                continue;  else
                                                                                                                for(int h=0;h<8;h++)
                                                                                                                {
                                                                                                                        if(h==a||h==a+7||h==a-7||h==b||
                                                                                                                                        h==b+6||h==b-6||
                                                                                                                                        h==c+5||h==c-5||
                                                                                                                                        h==c||h==d||h==d+4||
                                                                                                                                        h==d-4||h==e||h==e+3
                                                                                                                                        ||h==e-3||h==f||
                                                                                                                                        h==f+2||h==f-2||
                                                                                                                                        h==g||h==g+1||
                                                                                                                                        h==g-1)
                                                                                                                                continue;
                                                                                                                        else
                                                                                                                        {
                                                                                                                                std::cout<<a<<b<<c<<d<<
                                                                                                                                        e<<f<<g<<h<<
                                                                                                                                        std::endl;
                                                                                                                                count++;
                                                                                                                        }
                                                                                                                }
                                                                                                }
                                                                                }
                                                                }
                                                }

                }
        }
        std::cout<<"8 queen counts "<<count<<"!\n";
        return 0;
}