

Variables
         z objective function
         x(i)

Equations
         obj
         const1(k)
         const2(k)
         const_norm;
         obj .. z =e=  Sum((i,j), A(i,j)*x(i)*x(j));
         const1(k) .. Sum((i,j), B(k, i,j)*x(i)*x(j)) =g= 0;
         const2(k) .. Sum((i,j), B(k, i,j)*x(i)*x(j)) =l= 1;
         const_norm .. Sum(i, x(i)*x(i)) =l= 4/9.0426E-3;

Model Fider /all/;

option optcr = 0.0;
option optca = 0.0;
option reslim=50000;

x.fx('1')=0;

Solve Fider using QCP maximizing z;


Display z.l, x.l;
