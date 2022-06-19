#.SYNOPSIS
# Build cleaner.
#
#.DESCRIPTION
# Generic build cleaner by cykomaniacs.
#
#.PARAMETER keep
# List of file-names to keep.
#.PARAMETER base
# Base path to the build output (ex: "./bin")
#.PARAMETER name
# Target configuration names (ex: "debug", "release")
#.PARAMETER arch
# Target architectures names (ex: "x64", "x86")
#.PARAMETER help
# Print usage and description to STDOUT.
#.PARAMETER info
# Print description to STDOUT.
#.PARAMETER version
# Print the version number to STDOUT.
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
# Powershell ftw!

#----------------------------------------------------------------------------
using namespace system
#----------------------------------------------------------------------------
param (
  #region parameters: main
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
  #endregion

  #region parameters: help
  [Parameter(ParameterSetName='2.0', Mandatory)]
  [Parameter(ParameterSetName='2.1', Mandatory)]
  [Parameter(ParameterSetName='2.2', Mandatory)]
  [Parameter(ParameterSetName='2.3', Mandatory)]
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

  #region parameters: info
  [Parameter(ParameterSetName='3.0')]
  [Parameter(ParameterSetName='3.1', Mandatory)]
  [Alias('i')]
  [switch]
  $info,
  [Parameter(ParameterSetName='3.1', Position=1, Mandatory)]
  [Alias('v')]
  [switch]
  $version
  #endregion
)


#----------------------------------------------------------------------------
#region: namespace log
#-----------------
function log:host {
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [ConsoleColor]
    $rgb = [ConsoleColor]::White,
    [Parameter(Mandatory=$false)]
    [string[]] # output: ...
    $out,
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] #-# output: end-of-line?
    $end
  )

  Write-Host -ForegroundColor:$rgb $out -NoNewline:$true
  Write-Host -NoNewline:(!$end) # reset-rgb & end-of-line(line-feed)?
}

function log:feed {
  param (
    [Parameter()]
    [int]
    $num = 1
  )

  for ($i = 0; $i -lt $num; $i++) {
    Write-Host -NoNewline:$false
  }
}

function log:line {
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [ConsoleColor]
    $rgb = [ConsoleColor]::Magenta,
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] # end-of-line?
    $end
  )

  log:host -end:$end -rgb:$rgb -out:'--------------------'
}

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

  log:host -end:$false -rgb:Yellow   -out:'> '
  log:host -end:$false -rgb:Blue     -out:"${name}"
  log:host -end:$false -rgb:DarkCyan -out:':'
  log:host -end:$false -rgb:Red      -out:"${arch}"
  log:host -end:$false -rgb:Yellow   -out:'('
  log:host -end:$false -rgb:DarkGray -out:'nuke'
  log:host -end:$true  -rgb:Yellow   -out:')'
}

function log:file {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-path
    $path,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-name
    $name,
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] # skip/save?
    $keep
  )

  $xx = $keep ? '*' : '-'
  $xc = $keep ? [ConsoleColor]::Green : [ConsoleColor]::Red
  $fc = [ConsoleColor]::Gray

  log:host -end:$false -rgb:$xc -out:"${xx} "
  log:host -end:$true  -rgb:$fc -out:"${path}/${name}"
}
#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: namespace dbg (debug)
#-----------------
$script:dbg = $null # ErrorVariable
$script:dov = 'OK!' # ErrorVariable : d(efault)o(kay)v(alue)

function dbg:data:variable {
  return 'dbg' # name of ErrorVariable
}
function dbg:data:reset {
  $script:dbg = $script:dov
}
function dbg:data:okay {
  return $script:dbg -eq $script:dov
}
function dbg:data {
  return $script:dbg
}

function dbg:okay {
  return $Error.Count -eq 0
}

function dbg:kill {
  param (
    [Parameter(Mandatory=$false)]
    [int]
    $status = 1
  )

  exit $status
}

function dbg:fail {
  param (
    [Parameter(Mandatory=$false)]
    #[ValidateNotNullOrEmpty()]
    [Alias('msg')]
    [string]
    $message = $script:dbg,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('nfo','fun')]
    [string]
    $context,
    [Parameter(Mandatory=$false)]
    [alias('die')]
    [switch]
    $critcal
  )

  log:host -end:$false -rgb:DarkRed   -out:'#'
  log:host -end:$false -rgb:Yellow    -out:'['
  log:host -end:$false -rgb:Green     -out:$Error[0].InvocationInfo.ScriptLineNumber
  log:host -end:$false -rgb:DarkGray  -out:','
  log:host -end:$false -rgb:DarkGreen -out:$Error[0].InvocationInfo.OffsetInLine
  log:host -end:$false -rgb:Yellow    -out:']'
  log:host -end:$false -rgb:DarkGray  -out:' '
  log:host -end:$false -rgb:Blue      -out:'<'
  log:host -end:$false -rgb:DarkCyan  -out:"${context}"
  log:host -end:$false -rgb:Blue      -out:'>'
  log:host -end:$false -rgb:DarkGray  -out:' '
  log:host -end:$false -rgb:Red       -out:"${message}"
  log:host -end:$true

  if ($critcal) {
    dbg:kill -status:(($Error.Count -eq 0) ? 1 : $Error.Count)
  }
}

function dbg:eval {
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [Alias('msg')]
    [string]
    $message = $script:dbg,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('nfo','fun')]
    [string]
    $context,
    [Parameter(Mandatory=$false)]
    [alias('die')]
    [switch]
    $critcal
  )

  if (!(dbg:okay))
  {
    $tmp = $message
    dbg:data:reset # in case the of non-critical failure
    dbg:fail -message:"${tmp}" -context:"${context}" -critcal:$critcal
  } else {
    dbg:data:reset
  }
}
#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: namespace nfo
#-----------------
function nfo:main {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [hashtable]
    $info,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]
    $repo,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [hashtable]
    $date
  )

  log:feed
  log:host -end:$false -rgb:DarkGray -out:'# '
  log:host -end:$false -rgb:Blue     -out:$info.description
  log:host -end:$false -rgb:DarkGray -out:' - '
  nfo:version -string:$info.version.number -name:$info.version.name
  log:host -end:$false -rgb:DarkGray -out:'# '; log:line -end:$true -rgb:DarkGray
  log:host -end:$false -rgb:DarkGray -out:'# '
  log:host -end:$false -rgb:Gray     -out:$info.author.name#,''
  log:host -end:$false -rgb:Gray     -out:' <'
  log:host -end:$false -rgb:DarkGray -out:$info.author.mail
  log:host -end:$true  -rgb:Gray     -out:'>'
  log:host -end:$false -rgb:DarkGray -out:'# '
  log:host -end:$false -rgb:Gray     -out:$info.organization.name#,''
  log:host -end:$false -rgb:Gray     -out:' <'
  log:host -end:$false -rgb:DarkGray -out:$info.organization.home
  log:host -end:$true  -rgb:Gray     -out:'>'
  log:host -end:$false -rgb:DarkGray -out:'# '; log:line -end:$true -rgb:DarkGray
  log:host -end:$false -rgb:DarkGray -out:'# '
  nfo:repo -url:$repo  -rgb:Blue
  log:host -end:$false -rgb:DarkGray -out:'# '; log:line -end:$true -rgb:DarkGray
  log:host -end:$false -rgb:DarkGray -out:'# '
  log:host -end:$false -rgb:Cyan     -out:$date.updated
  log:host -end:$false -rgb:DarkGray -out:'('
  log:host -end:$false -rgb:DarkCyan -out:$date.created
  log:host -end:$true  -rgb:DarkGray -out:')'
  log:feed
}

function nfo:help {
  param (
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string] # script path
    $path = "$($app.path.full)",
    [Parameter()]
    [switch] # script called parameter-less?
    $nude
  )

  function help:defaults { Get-Help "${path}" }
  function help:complete { Get-Help "${path}" -Full }
  function help:examples { Get-Help "${path}" -Examples }
  function help:detailed { Get-Help "${path}" -Detailed }

  if ($nude)
  {
    log:host -rgb:Red        -out:'$ '
    log:host -rgb:Yellow     -out:'nuke.ps1'
    log:host -rgb:DarkYellow -out:' -'
    log:host -rgb:Yellow     -out:'h '
    log:host -rgb:DarkGray   -out:'for more information ...'
    log:feed -num:1
  } elseif ($complete) { help:complete
  } elseif ($examples) { help:examples
  } elseif ($detailed) { help:detailed
  } else { help:defaults }
}

function nfo:repo {
  param (
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [ConsoleColor]
    $rgb = ([ConsoleColor]::Green),
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]
    $url
  )

  log:host -end:$true -rgb:$rgb -out:$url
}

function nfo:version {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # version number
    $string,
    [Parameter(Mandatory=$false)]
    [AllowNull()]
    [string] # version name
    $name = $null
  )

  log:host -rgb:Cyan -out:$string.Substring(0, $string.indexOf('.'))
  log:host -rgb:Blue -out:'.'
  log:host -rgb:Cyan -out:$string.Substring(
    ($string.indexOf('.') + 1),
    ($string.LastIndexOf('.') - 2))
  log:host -rgb:Blue -out:'.'
  log:host -rgb:Cyan -out:$string.Substring(($string.LastIndexOf('.') + 1))

  if (($null -eq $name) -or ($name.Length -lt 1)) {
    return log:feed
  }

  log:host -rgb:DarkCyan -out:' <'
  log:host -rgb:DarkGray -out:$name
  log:host -rgb:DarkCyan -out:'>'
  log:feed
}
#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: namespace app
#-----------------
# TODO: fail-safe!
#----------------------------------------------------------------------------
#region: namespace app(tab)
#-----------------
$app = @{
  name = @{
    main = $MyInvocation.MyCommand.Name
    base = '' # script name without extension
    conf = '' # complete file-name
  }
  path = @{
    work = $PWD.Path
    full = $PSCommandPath
  }
  args = @{ # cmd-line arguments
      all = $args # complete <array>
    bound = $PSBoundParameters # named arguments <?>
  }
}

$app.name.base = $app.name.main.Substring(0, $app.name.main.LastIndexOf('.'))
$app.name.conf = $app.name.base + '.psd1'
#endregion ------------------------------------------------------------------

function app:argc { # returns the number of cmd-line arguments.
  param (
    [Parameter()]
    [switch]
    $all
  )

  return $all ? $app.args.all.Length : $app.args.bound.Count
}

function app:argv { # returns the cmd-line arguments
  param (
    [Parameter()]
    [switch]
    $all
  )

  return $all ? $app.args.all : $app.args.bound
}

function app:nude { # determines whether the cmd-line has arguments or not.
  param (
    [Parameter()]
    [switch]
    $all
  )

  return ((app:argc -all:$all) -eq 0)
}

function app:keep { # determines whether to keep the file or not.
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [array]  # file-names
    $list,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # file-name
    $file
  )

  $list.foreach({ if ("${_}" -eq "${file}") { return $true } })
  return $false
}

function app:nuke { # deleter!
  param (
    [Parameter(Mandatory)]
    [string] # file-path(excluding file-name)
    $path,
    [Parameter(Mandatory)]
    [string] # file-name
    $node,
    [Parameter(Mandatory)]
    [switch] # nuke?
    $fake
  )

  nuke:impl {
    param (
      [Parameter(Mandatory)]
      [string]
      $path
    )

    Remove-Item -Force -Recurse -ErrorAction:SilentlyContinue -Path:"${path}"
  }

  if (!$fake) {
    nuke:impl "${path}/${node}"
  }
}

function app:main { # called upon script entry
  param (
    [Parameter()]
    [ValidateNotNullOrEmpty()]
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

  function main:list {
    param (
      [Parameter(Mandatory)]
      [ValidateNotNullOrEmpty()]
      [string]
      $path,
      [Parameter()]
      [switch]
      $all
    )

    $tmp = Get-ChildItem -Hidden:$all "${path}" -Name -ErrorAction:SilentlyContinue -ErrorVariable (dbg:data:variable)
    dbg:eval -context:'Get-ChildItem' -message:"path: ${path}" -critcal:$true
    return $tmp
  }

  function main:impl {
    param (
      [Parameter(Mandatory)]
      [ValidateNotNullOrEmpty()]
      [string]
      $path,
      [Parameter(Mandatory)]
      [switch]
      $all
    )

    $(main:list -path:"${path}" -all:$all).foreach({
      if (app:keep -list:$keep -file:"${_}")
      {
        log:file -path:"${path}" -name:"${_}" -keep:$true
      } else {
        log:file -path:"${path}" -name:"${_}" -keep:$false
        app:nuke -path:"${path}" -node:"${_}" -fake:$fake
      }
    })
  }

  # ex: ./bin/debug/x64
  $work = $path + '/' + $name + '/' + $arch
  # need -Hidden:$true on nix, $false on win
  foreach ($all in @( $false, $true )) {
    main:impl -path:"${work}" -all:$all
  }
}
#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: namespace key(cfg)
#-----------------
# each key refers to a specific configuration variable.
# case-sensitive!
#-----------------
class key {
  static [string] $fake = "fake"
  static [string] $keep = "keep"
  static [string] $date = "date"
  static [string] $info = "info"
  static [string] $repo = "repo"
}
#endregion ------------------------------------------------------------------
#region: namespace cfg (see nuke.psd1)
#-----------------
# todo: fail handling
# todo: real implementation!
#-----------------
# source/import
$mod = Import-PowerShellDataFile -Path:($app.path.work + '/' + $app.name.conf) -ErrorAction:SilentlyContinue -ErrorVariable (dbg:data:variable)
# -----------------
# fail-safe
# -----------------
dbg:eval -fun:'Import-PowerShellDataFile' -die
# -----------------

function mod:has {
  param(
    [Parameter(Mandatory)]
    [string]
    $key
  )

  return $mod.ContainsKey($key)
}

function mod:get {
  param(
    [Parameter(Mandatory)]
    [string]
    $key,
    [Parameter(Mandatory)]
    [AllowNull()]
    [object]
    $default
  )

  return ((mod:has -key $key) ? $mod[$key] : $default)
}

$cfg = @{
  keep = @(mod:get -key ([key]::keep) -default $keep) + $keep

  info = mod:get -key:([key]::info) -default $null
  date = mod:get -key:([key]::date) -default $null
  fake = mod:get -key:([key]::fake) -default $true
  repo = mod:get -key:([key]::repo) -default $null
}

#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: script execution
#-----------------
# TODO: SORT EVERYTHING INTO NAMESPACES!!
#----------------------------------------------------------------------------
if (app:nude)
{
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
  nfo:help -nude:$true
} elseif ($help) {
  nfo:help
} elseif ($version) {
  nfo:version -string:$cfg.info.version.number -name:$cfg.info.version.name
} elseif ($info) {
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
} else {
  $name.foreach({ $t = $_
    $arch.foreach({
      log:head -name:"$t" -arch:"$_"
      app:main -fake:$cfg.fake -keep:$cfg.keep -path:"${base}" -name:"${t}" -arch:"${_}"
    })
  })
}
#endregion ------------------------------------------------------------------
