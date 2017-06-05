#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);
use lib './script';
use generate_common;

my $decl_header_file = shift @ARGV;
my @dep_list = @ARGV;

if ($#dep_list == 0) {
    say "Please specify the dependecny list for declarations producing.";
    exit 1;
} else {
    &create_submodule_declaration($decl_header_file, @dep_list);
}

