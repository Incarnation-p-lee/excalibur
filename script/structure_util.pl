#!/usr/bin/perl
use strict;
use warnings;
use feature qw(say);

my %type_hash;
my $file;
my $file_out;
my @structure_info;

if ($#ARGV == -1) {
    say "Please specify the structure definition file.";
    exit 1;
} else {
    $file = pop @ARGV;
    $file_out = $1 if $file =~ /(\w+)\./;
    $file_out = $file_out . "_util.c";

    &structure_info_generate($file);
    &structure_util_generate($file_out);
}

#
# info list format
# +--------+-------+-------+-------+-------+- ... -+----------+
# + struct | type0 | name0 | type1 | name1 |       | ISOLATOR |
# +--------+-------+-------+-------+-------+- ... -+----------+
#
sub structure_info_generate {
    my $deeps;
    my $filename;

    $deeps = 0;
    $filename = shift @_;
    
    open my $file_opened, '<', $filename or die "Failed to open $file";

    while (<$file_opened>) {
        chomp;

        if (/\btypedef\s+struct\s+(\w+)\s+(\w+)/) {
            $type_hash{$1} = $2;
        } elsif (/\bstruct\s+(\w+)\s/ and $deeps == 0) {
            push @structure_info, $1;
        }

        if (/{$/) {
            $deeps++;
        } elsif (/}/) {
            $deeps--;
            push @structure_info, "ISOLATOR" if $deeps == 0;
        } elsif ($deeps > 0) {
            if (/\b(\w+)\s+(\*{0,3}\w+)(:\d+)?\s*(\[\w+\])?;$/) {
                push @structure_info, ($1, $2);
            }
        }
    }

    close $file_opened;
}

sub structure_util_generate {
    my $tmp;
    my $f_name;
    my $f_type;
    my $s_name;
    my $filename;

    $filename = shift;
    $s_name = shift @structure_info;

    open my $file_opened, '>', $filename or die "Failed to open $file";

    while ($s_name) {
        my @members;
        $tmp = shift @structure_info;

        while ($tmp ne "ISOLATOR") {
            $f_type = $tmp;
            $f_name = shift @structure_info;
            push @members, ($f_type, $f_name);

            $tmp = shift @structure_info;
        }

        &structure_legal_generate($s_name, $file_opened, @members);
        &structure_interface_generate($s_name, $file_opened, @members);

        $s_name = shift @structure_info;
    }
    
    close $file_opened;
}

sub structure_legal_generate {
    my $s_name;
    my $s_alias;
    my $function;
    my $file_opend;
    my @members;

    $s_name = shift @_;
    $file_opend = shift @_;
    @members = @_;

    $s_alias = $type_hash{$s_name};
    $function = "$s_name" . "_legal_ip";

    # legal_ip
    printf $file_opend "static inline bool\n";
    printf $file_opend "$function($s_alias *$s_name)\n";
    printf $file_opend "{\n";
    printf $file_opend "    if ($s_name == NULL) {\n";
    printf $file_opend "        return false;\n";

    while (@members) {
        my $type = shift @members;
        my $name = shift @members;
        
        printf $file_opend "    } else if ($name) {\n";
        printf $file_opend "        return false;\n";
    }

    printf $file_opend "    } else {\n";
    printf $file_opend "        return true;\n";
    printf $file_opend "    }\n";
    printf $file_opend "}\n\n";

    # illegal_ip
    printf $file_opend "static inline bool\n";
    printf $file_opend "$s_name" . "_illegal_ip($s_alias *$s_name)\n";
    printf $file_opend "{\n";
    printf $file_opend "    return !$function($s_name);\n";
    printf $file_opend "}\n\n";

    # legal_p
    printf $file_opend "bool\n";
    printf $file_opend "$s_name" . "_legal_p($s_alias *$s_name)\n";
    printf $file_opend "{\n";
    printf $file_opend "    return $function($s_name);\n";
    printf $file_opend "}\n\n";

    # illegal_p
    printf $file_opend "bool\n";
    printf $file_opend "$s_name" . "_illegal_p($s_alias *$s_name)\n";
    printf $file_opend "{\n";
    printf $file_opend "    return !$function($s_name);\n";
    printf $file_opend "}\n\n";
}

sub structure_interface_generate {
    my $f_get, my $f_set;
    my $tmp, my $s_name, my $s_alias, my $file_opend;
    my @members;

    $s_name = shift @_;
    $s_alias = $type_hash{$s_name};
    $file_opend = shift @_;
    @members = @_;

    while (@members) {
        my $type = shift @members;
        my $name_raw = shift @members;
        my $name = $1 if $name_raw =~ /\*{0,3}(\w+)/;
        my $pointer = $1 if $name_raw =~ /(\*{0,3})\w+/;
        $pointer = " $pointer" if $pointer ne "";

        $tmp = "$s_name" . "_$name";
        $f_set = "$tmp" . "_set";
        $f_get = "$tmp" . "_p" if $type eq "bool";

        printf $file_opend "static inline $type" . "$pointer\n";
        printf $file_opend "$f_get" . "($s_alias *$s_name)\n";
        printf $file_opend "{\n";
        printf $file_opend "    assert($s_name" . "_legal_ip($s_name));\n\n";
        printf $file_opend "    return $s_name" . "->$name;\n";
        printf $file_opend "}\n\n";

        printf $file_opend "static inline void\n";
        printf $file_opend "$f_set" . "($s_alias *$s_name, $type $name_raw)\n";
        printf $file_opend "{\n";
        printf $file_opend "    assert($s_name" . "_legal_ip($s_name));\n\n";
        printf $file_opend "    $s_name" . "->$name = $name;\n";
        printf $file_opend "}\n\n";
    }
}

