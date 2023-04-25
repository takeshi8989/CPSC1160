a.
I store the amount of money as cents. Firstly, I don't want to use double value because it might give us uncertainty when we calculate values.
So, I did not want to store the data as only dollars.

If I use only cents, calculation and constructor could be very easy to implement. 
Because we just need to care about one variable, and if it's integer value, there is no error(uncertainty).
So I decided to store the data as cents. 

The reason why I did not have two value (dollars and cents) is because we need to do additional condition check when we set these values.
For example, if user type (dollar: 32, cents: -29), we need to have if statement to see if both are positive/negative, and set values correctly.
However, by using only cents, we can just add dollars * 100 and cents. We don't need to have IF statement. This is greate.

The disadvantage of this implementation is that we don't actually have dollars value. When we need dollar value, we need to call the accessor method
to get the dollar value. If we have dollar variable and we want it from member method in the class, we can take the variable without accessor method.

Overall, I thought that using only cents is the best way to implement. 
Even though we need accessor method to get the dollars, no calculation error and less code is a huge advantage.



b.
I did bonus part, and tested it.
For division operator, I ignored remainder. So the method do integer division
Also, for % operator, cash should be positive as precondition.