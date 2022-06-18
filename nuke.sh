#!/bin/sh
# ---------------------------------------------------------------------------
# nuke.ps1 sh helper
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
