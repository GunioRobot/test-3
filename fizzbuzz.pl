#!/usr/bin/perl -l

for ($i=1; $i<=100; $i++) {
	if		($i%3 == 0 && $i%5 == 0 ) { print "$i FizzBuzz"; }
	elsif ($i%3 == 0)								{ print "$i Fizz";     }
	elsif ($i%5 == 0)								{ print "$i Buzz";     }
	else														{ print "$i ";         }
}

1;

