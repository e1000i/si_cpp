Internation System of Measures for c++

This projects stants to provide a failsave management of magnitudes for
scientifi and comercial applications manipulation values that represents
som of the basic mesurament units.

It relays on c++11 features such user defined literals to make extremeally
easy to work with values of that magnitudes, preventing very common errors that
could be hard to debbug.

As a motivation example consider this situation:

Your working with a robot. The function to set speed is:
   void setSpeed(int speed){ ... }

wich speed your are refering m/s, miles/hour, km/hour...

an easy fix:

   void setSpeed(int m_by_s){...}

Now it much clear to third party developers what they need to put there. But
actually anithing can prevent you to put there km/hour.

So now you have your image recognition framework that work in km/hour. So all his
otuputs that unit. At some point a mantainer could forget to apply the proper conversion
and zaas you had los satelite that cost thousands of euros or dollars.

Using that library you would define the function as

   void setSpeed(Speed m_by_s){...}

And any attempt to pass to it a differnt value will be triggered by the compiler. So
no time consuming type checking or handmade objects.

And how you define Speed?
well there are different ways:

Speed s = 100; // that defines a speed of 100m/s remember we work with SI so thats the basic unit.
Speed s2 = 200_m/2_s; 
Speed s3 = Meters(200)/Seconds(200);

You notice that is extremely easy, just like using and inbuild type. In fact what youre using is a double.

When operating with units, you can not mix magnitudes. That means, you can not add meters and seconds.
If you try:
    Meters d(100);
    Secons s(20);
    Meters d2 = d+s;

This will not run as it will result in a compilation error. Fancy isn't it?

But hold on, thats not the best... what happend about product or division of Units?

Well it will just work as if you're doing it wiht paper and pencil. So if you divide Meters by Secons 
you get Speed in m/s. So:

    Speed s= d/s;
    std::cout << s << "m/s" << std::endl;

prints on the terminal a beautifull 50m/s.

And what about multiples consistency? Internally the library work with the basic unis meter, seconds, kilogram and soo on. But you may fill confortable to work in mm for some reason.
So wherever you add a mesure literal on your code you write:
    Meters d = 200_mm;

For now you must convert anyway all generated values from third party librarys that not use this library to meters, like always you have been done. And also convert all the values you will server to third party librarys that not work in basic units. But not worry, we will soon provide a very easy method to archive that.


Compilation sentence for test:
 clear && gcc -Wall -Wextra -std=c++0x -o test_units test_unitsnit_test_framework && ./test_units

