#!/usr/bin/perl

use strict;
use warnings;

# make string to make it possible to refer to it easily
my $f = "numbers.txt";

unless(open(FILE,'>'.$f)){
    die "nCan't open the file $f";
}

print "Number of numbers to print into file:";
my $VALUES;
chomp($VALUES = <STDIN>);



for( ; $VALUES>0; --$VALUES){
    print FILE "$VALUES \t";
    if( $VALUES%5==0){
         print FILE "\n";
    }
}

close FILE;
