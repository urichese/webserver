#!/usr/bin/perl -w

print "Content-Type: text/html\r\n";
print "\r\n";
foreach $key (sort keys(%ENV)) {
  print "$key = $ENV{$key}<p>";
}
print "</pre>\n";