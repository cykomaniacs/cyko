#.SYNOPSIS
# Build cleaner.
# cykomaniacs development 2022.
#
#.DESCRIPTION
# Generic cleaner.
#
#.PARAMETER keep
# List of file-names to keep.
#.PARAMETER base
# Base path to the build output (ex: "./bin")
#.PARAMETER name
# Target names (ex: "debug", "release")
#.PARAMETER arch
# Target architectures (ex: "x64", "x86")
#
#.EXAMPLE
# ./nuke.ps1 -base "./bin" -name "debug" -arch "x86"
#.EXAMPLE
# ./nuke.ps1 -base "./bin" -name "debug, "release" -arch "x86", "x64"
#
#.LINK
# cyko@eggheadedmonkey.com
#
#.NOTES
# Powershell ftw!

param (
  [Parameter(Mandatory=$false, ParameterSetName="main")]
  [ValidateNotNullOrEmpty()]
  [array]
  $keep = ( ".gitkeep" ),

  [Parameter(Mandatory, ParameterSetName="main")]
  [ValidateNotNullOrEmpty()]
  [string]
  $base,

  [Parameter(Mandatory, ParameterSetName="main")]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $name,

  [Parameter(Mandatory, ParameterSetName="main")]
  [ValidateNotNullOrEmpty()]
  [string[]]
  $arch
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
    [object]
    $default
  )

  return ((mod:has -key $key) ? $mod[$key] : $default)
}

#endregion ------------------------------------------------------------------

$cfg = @{
  test =  (mod:get -key ([key]::test) -default $true)
  keep = @(mod:get -key ([key]::keep) -default $keep) + $keep
}

#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region: script execution
#-----------------
# TODO: SORT EVERYTHING INTO NAMESPACES!!
#----------------------------------------------------------------------------

$name.forEach({ $t = $_
  $arch.ForEach({
    log:head -name "$t" -arch "$_"
    app:main -test:$cfg.test -skip $cfg.keep -path "$base" -name "$t" -arch "$_"
  })
})

#endregion ------------------------------------------------------------------
