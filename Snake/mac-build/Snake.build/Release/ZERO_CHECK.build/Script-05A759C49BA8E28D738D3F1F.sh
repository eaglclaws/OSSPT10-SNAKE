#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build
  make -f /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build
  make -f /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build
  make -f /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build
  make -f /Users/eaglclaws/src/git/eaglclaws/OSSPT10-SNAKE/Snake/mac-build/CMakeScripts/ReRunCMake.make
fi

