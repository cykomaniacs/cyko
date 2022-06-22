#!/bin/sh
# ---------------------------------------------------------------------------
# nuke.ps1 sh helper
# -----------
# should run on the standard unix/posix sh shell
# ---------------------------------------------------------------------------

[ -x "$(which pwsh)" ] || {
  echo "cannot find: <pwsh> executable!"
  exit 1
}

[ -n "${*}" ] || {
  pwsh ./nuke.ps1 # run without args
  exit $?
}

# execute main script (powershell)
pwsh -Command "& { ./nuke.ps1 ${@} }"
