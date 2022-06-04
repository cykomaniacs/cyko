#.SYNOPSIS
# Build cleaner.
# cykomaniacs development 2022.
#
#.DESCRIPTION
# Generic clean script.
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

#using namespace System;

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

# ---------------------------------------------------------------------------
# helpers (classes, just for fun!)
# ---------------------------------------------------------------------------

class log {
  static hidden $color = @{
    name = [System.ConsoleColor]::Blue;
    arch = [System.ConsoleColor]::Blue;
    text = [System.ConsoleColor]::DarkGray;

    pre  = [System.ConsoleColor]::DarkGray;
    par  = [System.ConsoleColor]::Yellow;
    sep  = [System.ConsoleColor]::DarkBlue;

    keep = [System.ConsoleColor]::Green;
    nuke = [System.ConsoleColor]::Red;
    file = [System.ConsoleColor]::Gray;
  }

  static hidden [void]
  mesg([string]$rgb, [string]$str, [switch]$end) {
    Write-Host -ForegroundColor ([log]::color)[$rgb] $str -NoNewline
    Write-Host "" -NoNewline:(!$end) # new-line / reset color
  }

  static [void] # print target info
  head([string]$name, [string]$arch) {
    [log]::mesg("pre",  "> ", $false)
    [log]::mesg("name", "${name}", $false)
    [log]::mesg("sep",  ":", $false)
    [log]::mesg("arch", "${arch}", $false)
    [log]::mesg("par",  "(", $false)
    [log]::mesg("pre",  "nuke", $false)
    [log]::mesg("par",  ")", $true)
  }

  static [void] # print file info
  file([string]$path, [string]$name, [switch]$skip) {
    $xx = $skip ? "*" : "-";
    $xc = $skip ? "keep" : "nuke";
    $fc = "file";

    [log]::mesg($xc, "${xx} ", $false)
    [log]::mesg($fc, "${path}/${name}", $true)
  }
}

class app {
  static hidden [bool]
  keep([array]$list, [string]$file) {
    $list.forEach({ if ("${_}" -eq "${file}") { return $true } })
    return $false
  }

  static [void]
  main() {

  }
}

# ---------------------------------------------------------------------------
# main > functions
# ---------------------------------------------------------------------------

function script:head {
  param(
    [Parameter(Mandatory)]
    [string] # target name
    $name,
    [Parameter(Mandatory)]
    [string] # target architecture
    $arch
  )

  [log]::head($name, $arch)
}

function script:file {
  param(
    [Parameter(Mandatory)]
    [string] # base path
    $path,
    [Parameter(Mandatory)]
    [string] # file-name
    $name,
    [Parameter(Mandatory=$false)]
    [switch] # skip/keep
    $skip = $false
  )

  [log]::file($path, $name, $skip)
}

function script:nuke {
  param(
    [Parameter(Mandatory=$false)]
    [array]  # skipped file-names
    $skip = $keep,
    [Parameter(Mandatory)]
    [string] # base path
    $path,
    [Parameter(Mandatory)]
    [string] # target name
    $name,
    [Parameter(Mandatory)]
    [string] # target architecture
    $arch
  )

  function local:has($list, $item) {
    $list.forEach({ if ("$_" -eq "$item") { return $true } })
    return $false
  }

  # ex: ./bin/debug/x64
  $work = $path + '/' + $name + '/' + $arch

  $(Get-ChildItem "$work" -Name).forEach({
    if (local:has $skip "$_")
    {
      script:file -path "$work" -name "$_" -skip
    } else {
      script:file -path "$work" -name "$_"
      Remove-Item -Force -Recurse -ErrorAction SilentlyContinue "$work/$_"
    }
  })
}

# ---------------------------------------------------------------------------
# main / entry
# ---------------------------------------------------------------------------

$name.forEach({ $t = $_
  $arch.ForEach({
    script:head -name "$t" -arch "$_"
    script:nuke -path "$base" -name "$t" -arch "$_"
  })
})
