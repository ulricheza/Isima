int a = 1
int b = 1
int c = 1
int temp;
for(i = 3 ; i<=10 ; ++i)
{
   temp = a
   a = b + c
   c = b
   b = temp
}

return a