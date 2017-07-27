#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);

sub generate_extern_header_file {
    my @sorted;
    my @externals;
    my @decl_file_list = @_;
    my $extern_header_file = "src/inc/external.h";

    foreach (@decl_file_list) {
        push @externals, &scan_declarnation_header_file($_);
    }

    @sorted = sort @externals;

    open EXTERN_HEAD, '>', $extern_header_file or
        die "Failed to create file $extern_header_file, $?\n";

    print EXTERN_HEAD "#ifndef HAVE_DEFINED_EXTERNAL_H\n";
    print EXTERN_HEAD "#define HAVE_DEFINED_EXTERNAL_H\n\n";

    foreach (@sorted) {
        print EXTERN_HEAD "extern $_\n";
    }

    print EXTERN_HEAD "\n#endif\n\n";

    close EXTERN_HEAD;
}

sub scan_declarnation_header_file {
    my @declarations;
    my $header_file = shift @_;

    open my $HEADER_FILE, '<', $header_file or die "Failed to open $header_file";

    while (<$HEADER_FILE>) {
        chomp;
        next if /^$/;
        next if /^#/;
        next if /\bstatic\b/;

        unshift @declarations, $_;
    }

    close $HEADER_FILE;

    @declarations;
}

sub create_submodule_declaration {
    my @declarations;
    my $decl_header_file = shift @_;
    my @dep_list = @_;

    foreach (@dep_list) {
        push @declarations, &filter_source_file_declaration($_);
    }

    &generate_submodule_header_file($decl_header_file, @declarations);
}

sub generate_submodule_header_file {
    my $macro;
    my $decl_header_file = shift @_;
    my @sorted = sort @_;

    if ($#sorted != -1) {
        $macro = $decl_header_file;
        $macro =~ s:\w+.h$::;
        $macro =~ s/[\/.]/_/g;
        $macro = uc($macro . 'declaration_h');

        open DECL, '>', $decl_header_file or die "$! $decl_header_file";

        print DECL "#ifndef $macro\n";
        print DECL "#define $macro\n\n";

        foreach (@sorted) {
            print DECL "$_\n";
        }

        print DECL "\n#endif\n";
        close DECL;
    }
}

sub filter_source_file_declaration() {
    my $filename = shift @_;
    my $body = 1;
    my $head;
    my $extern;
    my $basename = $1 if $filename =~ /\/([^\/]+)$/;
    my @declarations;

    open IMP, '<', $filename or die "$! $filename.";

    while (<IMP>) {
        chomp;
        next if /^$/;
        next if /:$/;
        next if /;$/;

        if (/^\w/) {
            $body = 0;
        } elsif (/^{/) {
            $body = 1;
        }

        if ("$body" eq "0") {
            my $real = $_;
            $real = $1 if (/^\s+(.*)/);
            $head = $head . "$real ";
        } elsif ($head){
            $head =~ s/\s$/;/g;
            $extern = "extern $head";
            unshift @declarations, $head;
            # unshift @externals, $extern unless $extern =~ "static";
            $head = undef;
        }
    }

    close IMP;

    @declarations;
}

1;

