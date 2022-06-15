#.SYNOPSIS
# Build cleaner.
#
#.DESCRIPTION
# Generic build cleaner for Windows.
#
#.PARAMETER keep
# List of file-names to keep.
#.PARAMETER base
# Base path to the build output (ex: "./bin")
#.PARAMETER name
# Target names (ex: "debug", "release")
#.PARAMETER arch
# Target architectures (ex: "x64", "x86")
#.PARAMETER help
# Print usage and description to stdout.
#.PARAMETER info
# Print description to stdout.
#.PARAMETER version
# Print the version number to stdout.
#
#.EXAMPLE
# ./nuke.ps1 -base "./bin" -name "debug" -arch "x86"
#.EXAMPLE
# ./nuke.ps1 -base "./bin" -name "debug, "release" -arch "x86", "x64"
#.EXAMPLE
# ./nuke.ps1 -help
#.EXAMPLE
# ./nuke.ps1 -info|desc
#.EXAMPLE
# ./nuke.ps1 -version
#
#.LINK
# cyko@eggheadedmonkey.com
#
#.NOTES
# Powershell ftw!

param (
  #region parameters: "main"
  [Parameter(ParameterSetName="1.0")]
  [ValidateNotNullOrEmpty()]
  [array]
  $keep = ( ".gitkeep" ),
  [Parameter(ParameterSetName="1.0", Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string]
  $base,
  [Parameter(ParameterSetName="1.0", Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $name,
  [Parameter(ParameterSetName="1.0", Mandatory)]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $arch,
  #endregion

  #region parameters: "help"
  [Parameter(ParameterSetName="2.0", Mandatory)]
  [Parameter(ParameterSetName="2.1", Mandatory)]
  [Parameter(ParameterSetName="2.2", Mandatory)]
  [Parameter(ParameterSetName="2.3", Mandatory)]
  [Alias("h")]
  [switch]
  $help,
  [Parameter(ParameterSetName="2.1", Position=1, Mandatory)]
  [switch]
  $detailed,
  [Parameter(ParameterSetName="2.2", Position=1, Mandatory)]
  [switch]
  $examples,
  [Parameter(ParameterSetName="2.3", Position=1, Mandatory)]
  [switch]
  $complete,
  #endregion

  #region parameters: "info"
  [Parameter(ParameterSetName="3.0", Mandatory)]
  [Parameter(ParameterSetName="3.0.0")]
  [Alias("desc")]
  [switch]
  $info,
  [Parameter(ParameterSetName="3.1", Mandatory)]
  [Alias("v")]
  [switch]
  $version
  #endregion
)

#----------------------------------------------------------------------------
#region: namespace color(log)
#-----------------

class color {
  static $name = [System.ConsoleColor]::Blue
  static $arch = [System.ConsoleColor]::Blue
  static $text = [System.ConsoleColor]::DarkGray

  static $std  = [System.ConsoleColor]::White    #standard
  static $pre  = [System.ConsoleColor]::DarkGray #prefix
  static $par  = [System.ConsoleColor]::Yellow   #pairs
  static $sep  = [System.ConsoleColor]::DarkBlue #separator

  static $keep = [System.ConsoleColor]::Green    #file:delete(no!)
  static $nuke = [System.ConsoleColor]::Red      #file:delete
  static $file = [System.ConsoleColor]::Gray     #file:name
}

#endregion ------------------------------------------------------------------
#region: namespace log
#-----------------

function log:host {
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor]
    $color = [color]::std,
    [Parameter(Mandatory=$false)]
    [string[]] # output: ...
    $out,
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] #-# output: end-of-line?
    $eol
  )

  Write-Host -ForegroundColor $color $out -NoNewline
  Write-Host -NoNewline:(!$eol) # reset-color & line-feed?
}

function log:line {
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor]
    $color = [System.ConsoleColor]::Magenta,
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] #-# output: end-of-line?
    $eol
  )

  log:host -color:$color -out "--------------------" -eol:$eol
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

  log:host -color ([color]::pre)  "> "
  log:host -color ([color]::name) "${name}"
  log:host -color ([color]::sep)  ":"
  log:host -color ([color]::arch) "${arch}"
  log:host -color ([color]::par)  "("
  log:host -color ([color]::text) "nuke"
  log:host -color ([color]::par)  ")" -eol
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
    [switch] # skip/keep
    $keep
  )

  $xx = $keep ? "*" : "-"
  $xc = $keep ? [color]::keep : [color]::nuke
  $fc = [color]::file

  log:host -color $xc "${xx} "
  log:host -color $fc "${path}/${name}" -eol
}

#endregion ------------------------------------------------------------------


#----------------------------------------------------------------------------
#region: namespace app
#-----------------

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

  if (!$fake) {
    Remove-Item -Force -Recurse -ErrorAction SilentlyContinue "${path}/${node}"
  }
}

function app:main { # called upon script entry
  param (
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [switch] # see configuration (nuke.psd1)
    $test = $false,
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [array]  # list of ignored file-names
    $skip,
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

  # ex: ./bin/debug/x64
  $work = $path + '/' + $name + '/' + $arch

  $(Get-ChildItem "$work" -Name).forEach({

    if (app:keep -list $skip -file "${_}")
    {
      log:file -path "${work}" -name "${_}" -keep:$true
    } else {
      log:file -path "${work}" -name "${_}" -keep:$false
      app:nuke -path "${work}" -node "${_}" -fake:$test
    }
  })
}

#endregion ------------------------------------------------------------------


#----------------------------------------------------------------------------
#region: namespace cfg (see nuke.psd1)
#-----------------

#----------------------------------------------------------------------------
#region: namespace key(cfg)
#-----------------
# each key refers to a specific configuration variable.
# case-sensitive!
#-----------------

class key {
  static [string] $test = "test"
  static [string] $keep = "keep"
}

#endregion ------------------------------------------------------------------
#region: namespace mod(cfg)
#-----------------
# todo: fail handling
# todo: real implementation!
#-----------------

# source/import
$mod = Import-PowerShellDataFile -Path "./nuke.psd1"
#Import-PowerShellDataFile -Path "./nuke.psd1"


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

#endregion ------------------------------------------------------------------

$cfg = @{
  test =  (mod:get -key ([key]::test) -default $true)
  keep = @(mod:get -key ([key]::keep) -default $keep) + $keep

  info = mod:get -key "info" -default $null
  date = mod:get -key "date" -default $null
  repo = mod:get -key "repo" -default $null
}

#endregion ------------------------------------------------------------------

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

  log:host -eol:$true # start

  log:host -eol:$false -color:DarkGray -out "#",""
  log:host -eol:$false -color:Blue     -out $info.description,""
  log:host -eol:$false -color:DarkGray -out "-",""
  nfo:version -string $info.version.number -name:$info.version.name
  log:host -eol:$false -color:DarkGray -out "#","";log:line -eol:$true -color:DarkGray
  log:host -eol:$false -color:DarkGray -out "#",""
  log:host -eol:$false -color:Gray     -out $info.author.name,""
  log:host -eol:$true  -color:DarkGray -out $info.author.mail
  log:host -eol:$false -color:DarkGray -out "#",""
  log:host -eol:$false -color:Gray     -out $info.organization.name,""
  log:host -eol:$true  -color:DarkGray -out $info.organization.home
  log:host -eol:$false -color:DarkGray -out "#","";log:line -eol:$true -color:DarkGray
  log:host -eol:$false -color:DarkGray -out "#",""
  nfo:repo -url:$repo  -color:Blue
  log:host -eol:$false -color:DarkGray -out "#","";log:line -eol:$true -color:DarkGray
  log:host -eol:$false -color:DarkGray -out "#",""
  log:host -eol:$false -color:Cyan     -out $date.updated
  log:host -eol:$false -color:DarkGray -out "("
  log:host -eol:$false -color:DarkCyan -out $date.created
  log:host -eol:$true  -color:DarkGray -out ")"

  log:host -eol:$true # end
}

function nfo:help {
  if ($complete) {
    Get-Help .\nuke.ps1 -Full:$complete
  } elseif ($examples) {
    Get-Help .\nuke.ps1 -Examples:$examples
  } elseif ($detailed) {
    Get-Help .\nuke.ps1 -Detailed:$detailed
  } else {
    Get-Help .\nuke.ps1
  }
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
    $name = $null,
    #region color parameters
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor] # color: number
    $cone = ([System.ConsoleColor]::Cyan),
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor] # color: name
    $ctwo = ([System.ConsoleColor]::DarkGray),
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor] # color: dots (name)
    $cdot = ([System.ConsoleColor]::Blue),
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor] # color: pair (name brackets)
    $cpar = ([System.ConsoleColor]::DarkCyan)
    #endregion
  )

  log:host -eol:$false -color:$cone -out $string.Substring(0,
     $string.indexOf('.'))
  log:host -eol:$false -color:$cdot -out '.'
  log:host -eol:$false -color:$cone -out $string.Substring(
    ($string.indexOf('.') + 1),
    ($string.LastIndexOf('.') - 2))
  log:host -eol:$false -color:$cdot -out '.'
  log:host -eol:$false -color:$cone -out $string.Substring(
    ($string.LastIndexOf('.') + 1)
  )

  if ($name.Length -lt 1) {
    return log:host -eol
  }

  log:host -eol:$false -color:$cpar -out ' <'
  log:host -eol:$false -color:$ctwo -out $name
  log:host -eol:$true  -color:$cpar -out '>'
}

function nfo:repo {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string]
    $url,
    #region color parameters
    [Parameter(Mandatory=$false)]
    [ValidateNotNullOrEmpty()]
    [System.ConsoleColor] # color: url
    $color = ([System.ConsoleColor]::Green)
    #endregion
  )

  log:host -eol:$true -color:$color -out $url
}

#----------------------------------------------------------------------------
#region: script execution
#-----------------
# TODO: SORT EVERYTHING INTO NAMESPACES!!
#----------------------------------------------------------------------------
if ($PSBoundParameters.Count -eq 0) {
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date

  log:host -eol:$false -color:Red        -out "$",""
  log:host -eol:$false -color:Yellow     -out "nuke.ps1", ""
  log:host -eol:$false -color:DarkYellow -out "-"
  log:host -eol:$false -color:Yellow     -out "h",""
  log:host -eol:$true  -color:DarkGray   -out "for more information ..."
  log:host -eol:$true
} elseif ($help) {
  nfo:help
} elseif ($info) {
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
} elseif ($version) {
  nfo:version
} else {
  $name.foreach({ $t = $_
    $arch.foreach({
      log:head -name "$t" -arch "$_"
      app:main -test:$cfg.test -skip $cfg.keep -path "$base" -name "$t" -arch "$_"
    })
  })
}

#endregion ------------------------------------------------------------------
