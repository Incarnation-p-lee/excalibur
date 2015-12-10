#!/usr/bin/perl
use strict;
use 5.010;

my $work_dir = shift @ARGV;
my $include_dir = "$ENV{'PWD'}/src/inc";

if ($work_dir eq "") {
    say "Please specify the work directory for makefile producing.";
    exit 1;
} else {
    $work_dir = $1 if $work_dir =~ /(\w+)\/?$/;
    &create_compile_makefile("$work_dir") if -e "$work_dir/main.c";
    &visit_workspace($work_dir);
}

sub visit_workspace {
    my $base = shift @_;

    if ( -e -d $base) {
        opendir WORKSPACE, $base or
            die "Failed to open work directory $base, $?\n";

        my @work_list = readdir(WORKSPACE);

        foreach my $entry (@work_list) {
            chomp;
            next if $entry =~ /^\.$/;
            next if $entry =~ /^\.\.$/;
            next if $entry =~ /^inc$/;

            my $sub_dir = "$base/$entry";
            if (-e -d $sub_dir) {
                &create_compile_makefile($sub_dir);
                &visit_workspace($sub_dir)
            }
        }

        closedir WORKSPACE;
    }
}

sub create_compile_makefile {
    my $location;
    my $dir;
    my $file;

    $location = shift @_;
    $location =~ /\w+/ or
        die "Script DO NOT know how to make one makefile without a module name.";

    $dir = $location;
    $file = $1 if $location =~ /\/?(\w+)$/;

    ## handle main.c Makefile ##
    $file = "main" if -e "$location/main.c";

    say "    Makefile .. $file";

    open MAKEFILE, '>', "$dir/Makefile" or
        die "Failed to create makefile, $?\n";

    printf MAKEFILE "CFLAGS+=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -c\n";
    printf MAKEFILE "CFLAGS+=-I$include_dir\n";
    printf MAKEFILE "ASFLAGS+=-felf\n\n";
    printf MAKEFILE "TARGET=$file.o\n";
    printf MAKEFILE 'all:$(TARGET)' ."\n\n";
    printf MAKEFILE ".s.o:\n";
    printf MAKEFILE "\t" . 'nasm $(ASFLAGS) -o $@ $<' . "\n";
    printf MAKEFILE ".c.o:\n";
    printf MAKEFILE "\t" . 'cc $(CFLAGS) -o $@ $<' . "\n";

    close MAKEFILE;
}

