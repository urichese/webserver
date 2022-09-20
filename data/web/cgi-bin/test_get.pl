#!/usr/bin/perl

use CGI;

$query = new CGI;
$first_name = $query->param('first_name');
$second_name = $query->param('second_name');
print "Content-Type: text/html\r\n";
print "\r\n";
print "first name: ";
print $first_name;
print " second name: ";
print $second_name;

