#!/bin/bash
# ---------------------------------------------------------------------------
# nuke.ps1 bash helper
# ---------------------------------------------------------------------------

die() {
  case "${1}" in
    'exec') {
      echo "[ERR] cannot find: <pwsh> executable!"
      exit 1
    }; break ;;

    'args') {
      echo "[ERR] missing arguments!"
      echo "[USE] test.bash -h"

      exit 1
    }; break ;;
  esac
}

[[ -x "$(which pwsh)" ]] || die 'exec'
[[ -n "${*}" ]] || die 'args'

# execute main script (powershell)
pwsh -Command "& { ./nuke.ps1 ${@} }"
