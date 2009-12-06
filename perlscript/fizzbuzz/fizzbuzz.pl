#!/usr/bin/perl -l

for ($i=1; $i<=100; $i++) {
	print "$i FizzBuzz"; if     ($i%3 == 0 && $i%5 == 0 )
	print "$i Fizz";     elsif  ($i%3 == 0)
	print "$i Buzz";     elsif  ($i%5 == 0)
	print "$i";          else
}

