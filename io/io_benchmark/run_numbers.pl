#!/usr/bin/perl

use strict;
use warnings;

# make string to make it possible to refer to it easily
my $f = "numbers.txt";

print "Number of runs:";
my $COUNT;
chomp($COUNT = <STDIN>);

print "Number of numbers to process:";
my $NUMBERS;
chomp($NUMBERS = <STDIN>);

my @res;
for( ; $COUNT>0; --$COUNT){
         print "C:";
         @res = ` time ./io_benchmark.exe $NUMBERS >/dev/null 2>&1`;
         print "@res\n";
         print "C++:";
         @res = ` time ./io_benchmark_cpp.exe $NUMBERS >/dev/null 2>&1`;
         print "@res-----------------------------------------\n";
}

