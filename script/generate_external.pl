#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);
use lib './script';
use generate_common;

my @decl_list = @ARGV;

if ($#decl_list == 0) {
    say "Please specify the work directory for external file producing.";
    exit 1;
} else {
    &generate_extern_header_file(@decl_list);
}

