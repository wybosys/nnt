#!/usr/bin/env perl

use Inline C;
use Inline C => Config => LIBS => '-lwsi';

print `pwd`;
print getVersion();

__END__
__C__
char* getVersion()
  {
    return WSIVersion();
  }
