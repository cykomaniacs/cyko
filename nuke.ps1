#.SYNOPSIS
# Build cleaner.
#
#.DESCRIPTION
# Generic build cleaner by cykomaniacs.
#
#.PARAMETER keep
# List of file-names to keep.
#.PARAMETER base
# Base path to the build output (ex: "./bin").
#.PARAMETER name
# Target configuration names (ex: "debug", "release").
#.PARAMETER arch
# Target architectures names (ex: "x64", "x86").
#.PARAMETER fake
# Fake execution (don't act, just print).
#.PARAMETER help
# Print info/help (Get-Help).
#.PARAMETER detailed
# Print info/help similar to: Get-Help -detailed
#.PARAMETER examples
# Print info/help similar to: Get-Help -examples
#.PARAMETER complete
# Print info/help similar to: Get-Help -full
#.PARAMETER info
# Print script information (author, version, configuration etc).
# About... simply put.
#.PARAMETER version
# Print script version.
#
#.EXAMPLE
# nuke.ps1 -base:./bin -name:debug -arch:x86
#
# # Clean a single build.
# #
# # Target: "debug"
# # Config: "x86"
#
#.EXAMPLE
# nuke.ps1 -base:./bin -name:debug,release -arch:x86,x64
#
# # Clean multiple builds (both configurations for each target).
# #
# # Target: "debug" | "release"
# # Config: "x86"   | "x64"
#
#.LINK
# cyko@eggheadedmonkey.com
#
#.NOTES
# Power to the shell! ... and the people ;)
# Skit ner er! Ever heard about zsh?

#----------------------------------------------------------------------------
# TODO: SORT - SPLIT EVERYTHING INTO NAMESPACES(GROUPS)
# TODO: DOCS - PROVIDE PROPER DOCUMENTATION
# TODO: OPTIMIZE / CLEANUP
#-----------------
# 2022/06/20 - Almost namespaced! :D
# 2022/06/22 - Almost documented! XD
# 2022/06/22 - Feeling good about cleanup, optimization... dunno.
# 2022/06/22 - Optimizing types (uint etc).
# 2022/06/25 - Optimizing parameters (Attributes, Aliases...).
#----------------------------------------------------------------------------
using namespace system
#----------------------------------------------------------------------------
param (
  #region parameters(main)
  [Parameter(ParameterSetName='1.0')]
  [ValidateNotNullOrEmpty()]
  [array]
  $keep = ( '.gitkeep' ),
  [Parameter(ParameterSetName='1.0', Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string]
  $base,
  [Parameter(ParameterSetName='1.0', Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $name,
  [Parameter(ParameterSetName='1.0', Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $arch,
  [Parameter(ParameterSetName='1.0')]
  [switch]
  $fake,
  #endregion

  #region parameters(help)
  [Parameter(ParameterSetName='2.0', Position=0, Mandatory)]
  [Parameter(ParameterSetName='2.1', Position=0, Mandatory)]
  [Parameter(ParameterSetName='2.2', Position=0, Mandatory)]
  [Parameter(ParameterSetName='2.3', Position=0, Mandatory)]
  [Alias('h')]
  [switch]
  $help,
  [Parameter(ParameterSetName='2.1', Position=1, Mandatory)]
  [switch]
  $detailed,
  [Parameter(ParameterSetName='2.2', Position=1, Mandatory)]
  [switch]
  $examples,
  [Parameter(ParameterSetName='2.3', Position=1, Mandatory)]
  [switch]
  $complete,
  #endregion

  #region parameters(info)
  [Parameter(ParameterSetName='3.0', Position=0, Mandatory)]
  [Parameter(ParameterSetName='3.1', Position=0, Mandatory)]
  [Alias('i')]
  [switch]
  $info,
  [Parameter(ParameterSetName='3.1', Position=1, Mandatory)]
  [Parameter(ParameterSetName='3.2', Position=0)] # parameter-less invocation
  [Alias('v')]
  [switch]
  $version
  #endregion
)

$Error.Clear()

trap {
  $Error[-1]
  $StackTrace
  $Error.Clear()
}

#----------------------------------------------------------------------------
#region namespace log
#-----------------

#:SYNOPSIS
# Prints to STDOUT (default/main print implementation).
function log:host {
  param (
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [ConsoleColor]
    $rgb = [ConsoleColor]::Gray,
    [Parameter()]
    [string[]]
    $out,
    [Parameter()]
    [switch]
    $end
  )

  Write-Host -NoNewline:(!$end) -ForegroundColor:$rgb $out
}

#:SYNOPSIS
# Prints the line-feed character (new-line) to STDOUT.
function log:feed {
  param (
    [Parameter()]
    [uint]
    $num = 1,
    [Parameter()]
    [switch]
    $tab
  )

  $out = $tab ? "`t" : $null

  for ($i = 0; $i -lt $num; $i++) {
    Write-Host -NoNewline:$tab -Object:$out
  }
}

#:SYNOPSIS
# Prints a horizontal line of specified width/length.
function log:line {
  param (
    [Parameter(ParameterSetName='1.0')]
    [Parameter(ParameterSetName='2.0')]
    [Parameter(ParameterSetName='2.1')]
    [Parameter(ParameterSetName='2.2')]
    [Parameter(ParameterSetName='2.3')]
    [Parameter(ParameterSetName='2.4')]
    [ValidateNotNullOrEmpty()]
    [ConsoleColor]
    $rgb = [ConsoleColor]::Magenta,
    [Parameter(ParameterSetName='2.0', Mandatory)]
    [switch] # length: about 80 characters
    $full,
    [Parameter(ParameterSetName='2.1', Mandatory)]
    [switch] # length: < full
    $long,
    [Parameter(ParameterSetName='2.2', Mandatory)]
    [switch] # length: < long
    $half,
    [Parameter(ParameterSetName='2.3', Mandatory)]
    [switch] # length: < half
    $mini,
    [Parameter(ParameterSetName='1.0', Mandatory)]
    [Alias('num')]
    [uint] #-# length: manual
    $len = 20
  )

  # these parameters cannot be used together (no need for elseif)...
  if ($full) { $len = 76 }
  if ($long) { $len = 57 }
  if ($half) { $len = 38 }
  if ($mini) { $len = 20 }

  for ($i = 0; $i -lt $len; $i++) {
    log:host -rgb:$rgb -out:'-'
  }
}

#:SYNOPSIS
# Prints a header (info about target).
function log:head {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # target: name
    $name,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # target: architecture
    $arch
  )

  log:host -rgb:Yellow   -out:'> '
  log:host -rgb:Blue     -out:$name
  log:host -rgb:DarkCyan -out:':'
  log:host -rgb:DarkBlue -out:$arch
  log:feed -num:1
}

#:SYNOPSIS
# Prints info about a file (prefixed with nuke/keep indicator + path).
function log:nuke {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-path
    $path,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-name
    $file,
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [switch] # skip/save?
    $keep
  )

  $xx = $keep ? '*' : '-'
  $xc = $keep ? [ConsoleColor]::Green : [ConsoleColor]::Red
  $fc = [ConsoleColor]::Gray

  log:host -rgb:$xc -out:"${xx} "
  log:host -rgb:$fc -out:"${path}/${file}"
  log:feed -num:1
}
#endregion ------------------------------------------------------------------






#----------------------------------------------------------------------------
#region namespace dbg (debug)
#-----------------
$dbg = $null # ErrorVariable
#-----------------

#.SYNOPSIS
# Resets the common-debug-varable to its default value (and clears $Error).
function dbg:data:reset {
  $script:dbg = $null
  $Error.Clear()
}

#.SYNOPSIS
# Returns true if there are no global errors.
function dbg:okay {
  return (dbg:fail:count) -eq 0
}

#.SYNOPSIS
# Returns the number of global errors.
function dbg:fail:count {
  return $Error.Count
}

#:SYNOPSIS
# Failure handling.
function dbg:fail {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('n')]
    [string]
    $namespace,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('x')]
    [string]
    $context,
    [Parameter()]
    [Alias('m')]
    [string[]]
    $message = $dbg,
    [Parameter()]
    [alias('die')]
    [switch]
    $critical
  )


  if (dbg:okay)
  {
    $ln = $PSCmdlet.MyInvocation.ScriptLineNumber
    $cn = $PSCmdlet.MyInvocation.OffsetInLine
  } else {
    $ln = $Error[-1].InvocationInfo.ScriptLineNumber
    $cn = $Error[-1].InvocationInfo.OffsetInLine
  }

  log:host -rgb:Red       -out:'#'
  log:host -rgb:Yellow    -out:'['
  log:host -rgb:Green     -out:$ln #@ line-number
  log:host -rgb:DarkGray  -out:','
  log:host -rgb:DarkGreen -out:$cn #@ line-number:column-number
  log:host -rgb:Yellow    -out:']'
  log:host -rgb:DarkGray  -out:' <'
  log:host -rgb:Magenta   -out:'['
  log:host -rgb:Blue      -out:$namespace
  log:host -rgb:Magenta   -out:']'
  log:host -rgb:DarkCyan  -out:$context
  log:host -rgb:DarkGray  -out:'> '
  log:host -rgb:Red       -out:$message
  log:feed -num:1

  app:kill -c:((dbg:fail:count) + 1) -fake:(!$critical)
}

#:SYNOPSIS
# Handle failures. Evaluates the common-debug parameters per default.
function dbg:eval {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('n')]
    [string]
    $namespace,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('x')]
    [string]
    $context,
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [Alias('m')]
    [string[]]
    $message = $dbg,
    [Parameter()]
    [alias('die')]
    [switch]
    $critical
  )

  if (!(dbg:okay))
  {
    dbg:fail -n:$namespace -x:$context -m:$message -critical:$critical
  } else {
    $Error.Clear()
  }
}

#endregion ------------------------------------------------------------------



#----------------------------------------------------------------------------
#region namespace app
#----------------------------------------------------------------------------
#region namespace app - constants
#-----------------

$app = @{
  nude = $PSBoundParameters.Count -eq 0

  file = $MyInvocation.MyCommand.Name
  name = $MyInvocation.MyCommand.Name.Split('.')[0]

  path = @{
    work = $PWD.Path
    full = $PSCommandPath
  }
}

#endregion ------------------------------------------------------------------

#:SYNOPSIS
# Prints usage / help (using the Get-Help command).
function app:help {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # script path/file
    $path,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # script file(name)
    $file,
    [Parameter()]
    [switch] # called parameter-less?
    $nude
  )

  function local:defaults { Get-Help $path }
  function local:complete { Get-Help $path -Full }
  function local:examples { Get-Help $path -Examples }
  function local:detailed { Get-Help $path -Detailed }

  if ($nude)
  {
    log:host -rgb:Red        -out:'$ '
    log:host -rgb:Yellow     -out:$file
    log:host -rgb:DarkYellow -out:' -'
    log:host -rgb:Yellow     -out:'h'
    log:feed -num:1
    log:host -rgb:Red        -out:'# '
    log:host -rgb:DarkGray   -out:'for more information ...'
    log:feed -num:1
  } elseif ($complete) { local:complete
  } elseif ($examples) { local:examples
  } elseif ($detailed) { local:detailed
  } else { local:defaults }
}

#:SYNOPSIS
# Prints version information.
function app:info {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [hashtable] # cfg: version
    $data
  )

  $x = $data.number.split('.')

  # numbers
  log:host -rgb:Blue     -out:$x[0]
  log:host -rgb:DarkGray -out:'.'
  log:host -rgb:Blue     -out:$x[1]
  log:host -rgb:DarkGray -out:'.'
  log:host -rgb:Magenta  -out:$x[2]
  # name
  log:host -rgb:DarkCyan -out:' <'
  log:host -rgb:DarkGray -out:$data.name
  log:host -rgb:DarkCyan -out:'>'
  log:feed -num:1
}

#:SYNOPSIS
# Stops the script!
function app:kill {
  param (
    [Parameter()]
    [Alias('c')]
    [int]
    $code = 1,
    [Parameter()]
    [switch]
    $fake
  )

  $Error.Clear()

  if ($VerbosePreference)
  {
    log:feed -num:1
    log:host -rgb:Red      -out:'$ '
    log:host -rgb:Yellow   -out:'exit'
    log:host -rgb:DarkGray -out:'('
    log:host -rgb:Red      -out:$code
    log:host -rgb:DarkGray -out:')'
    log:feed -num:2
  }

  if (!$fake) { exit $code }
}

#.SYNOPSIS
# Returns true if the scripts was invoked without arguments (nude)?
function app:nude {
  $app.nude
}

#:SYNOPSIS
# Returns true if the $keep list contains the file.
function app:keep {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]
    $file
  )

  $keep.Contains($file)
}

#:SYNOPSIS
# Main functionality (deleter).
function app:nuke {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-path(excluding file-name)
    $path,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-name
    $file,
    [Parameter()]
    [switch] # keep?
    $fake = $fake
  )

  if (!$fake) {
    Remove-Item -Path:"${path}/${file}" -Force -Recurse
  }
}

#:SYNOPSIS
# Main (first function called).
function app:main { # called upon script entry
  param (
    [Parameter()]
    [switch] # see configuration (nuke.psd1)
    $fake = $false,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [array]  # list of ignored file-names
    $keep,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # base/work path
    $path,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # target name
    $name,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # target architecture
    $arch
  )

  function local:ls {
    param (
      [Parameter(Mandatory)]
      [string]
      $path,
      [Parameter(Mandatory)]
      [switch]
      $all,
      [Parameter(Mandatory)]
      [switch]
      $critical
    )

    Get-ChildItem -Name -Path:$path -Hidden:$all `
      -ErrorAction:SilentlyContinue `
      -ErrorVariable:dbg ; dbg:eval `
      -n:app -x:main.ls `
      -critical:$critical
  }

  # ex: ./bin/debug/x64
  $p = $path + '/' + $name + '/' + $arch
  # need -all:$true on nix, $false on win (-all alias for -Hidden)
  foreach ($a in @( $false, $true )) {
    (local:ls -path:$p -all:$a -critical).foreach({
      if (app:keep -file:$_)
      {
        log:nuke -path:$p -file:$_ -keep
      } else {
        log:nuke -path:$p -file:$_
        app:nuke -path:$p -file:$_ -fake:$fake
      }
    })
  }
}

#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region namespace cfg
#-----------------

# import
$cfg = Import-PowerShellDataFile `
  -Path:($app.path.work + '/' + $app.name + '.psd1') `
  -ErrorAction:SilentlyContinue `
  -ErrorVariable:dbg ; dbg:eval `
  -n:cfg -x:Import-PowerShellDataFile `
  -critical

# output
if ($VerbosePreference) {
  log:feed -num:1
  log:line -rgb:Magenta -full
  log:feed -num:1
  log:host -rgb:Blue -out:CONFIGURATION
  log:feed -num:1;
  log:line -rgb:Magenta -num:13
  log:feed -num:1
  $cfg
  log:feed -num:1
  log:line -rgb:Magenta -full
  log:feed -num:2
}

#endregion ------------------------------------------------------------------


#----------------------------------------------------------------------------
# script execution
#----------------------------------------------------------------------------
# TODO: fake ...
# TODO: keep ...
# TODO: $Error (different when sourced?)
#---------------
if (app:nude)
{
  app:help -path:$app.path.full -file:$app.file -nude
} elseif ($help) {
  app:help -path:$app.path.full -file:$app.file
} elseif ($version) {
  app:info -data:$cfg.info.version
} elseif ($info) {
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
} else {
  $name.foreach({ $n = $_
    $arch.foreach({
      log:head -name:$n -arch:$_
      app:main -name:$n -arch:$_ `
        -fake:($fake -or $cfg.fake) `
        -keep:($keep  +  $cfg.keep) `
        -path:($base)
    })
  })
}
