big40main_01.c (executable named b40-m1)
tests
 - parseString()
 - Integer40Destroyer()
 - prints them

big40main_02.c (executable named b40-m2)
tests
 - load cryptoVariable
 - load hwConfigVariable
 - prints them

big40main_03.c (executable named b40-m3)
tests
 - big40Add
 - fibBig40
 - prints results

big40main_04.c (executable named b40-m4)
tests
 - args (with no args to check for error message)
 - args with different parameters. (See below for
   details on parameters used for the log file.)
 - fibBig40(n from small to large)
 - prints fb40(large)
 - prints big40Rating() to STDERR
 - args expect-> n cryptoVarFile 0
 - first argument is the "Fibonacci number"
 - second argument is the cryptoVarFile name
 - third argument is boolean for seed with 0 or 1 
   for seed with milliseconds since epoch 
   (This will be an unique number.)

Any of these "big40 mains" can be compiled
and linked with the submitted big40.c using
the following command:
 gcc big40main-0x.c b40.c -o b40-0x

where the output of the compiler will be the
executable named b40-0x.

Substitute the x with 1 -> 4 and all the minimal
tests will have been run.

—IMPORTANT-
All the programs were run with the following inputs:
>./b40-m1 >b40-m1.log
>./b40-m2 >b40-m2.log
>./b40-m3 >b40-m3.log
>./b40-m4 1000000 cryptoFilename 0 >b40-m4.log 2>b40-m4.err

You can time the execution speed by preceding the command
with the command “time”, for example to time b40-m4 execute
the following command:

>time ./b40-m4 1000000 cryptoFilename 0 >b40-m4.log 2>b40-m4.err

This returns the “real” time (total elapsed time), the “user”
time (program execution time), and the “sys” time (kernel or
OS time to manage the process).

Several runs of the above command ran in about 1 minutes
and 70 milliseconds (0m1.070s).
