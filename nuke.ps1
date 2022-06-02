#.SYNOPSIS
# Clean build files.
# cykomaniacs development 2022.
#
#.DESCRIPTION
# Generic nuker.
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

# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------

function script:head {
  param (
    [Parameter(Mandatory)]
    [string] # target name
    $name,

    [Parameter(Mandatory)]
    [string] # target architecture
    $arch
  )
  Write-Host -ForegroundColor DarkGray "> " -NoNewline
  Write-Host -ForegroundColor Blue "$name" -NoNewline
  Write-Host -ForegroundColor DarkCyan ":" -NoNewline
  Write-Host -ForegroundColor Blue "$arch" -NoNewline
  Write-Host -ForegroundColor DarkBlue "(" -NoNewline
  Write-Host -ForegroundColor DarkGray "nuke" -NoNewline
  Write-Host -ForegroundColor DarkBlue ")" -NoNewline
  Write-Host "" # reset color
}

function script:file {
  param (
    [Parameter(Mandatory)]
    [string] # base path
    $path,

    [Parameter(Mandatory)]
    [switch] # skip/keep
    $skip,

    [Parameter(Mandatory)]
    [string] # file-name
    $name
  )

  if ($skip)
  {
    Write-Host -ForegroundColor Green "* " -NoNewline
    Write-Host -ForegroundColor Gray "$path/$name"
  } else {
    Write-Host -ForegroundColor Red "- " -NoNewline
    Write-Host -ForegroundColor Gray "$path/$name"
  } Write-Host "" -NoNewline # reset color
}

# ---------------------------------------------------------------------------
# main function
# ---------------------------------------------------------------------------

function script:nuke {
  param (
    [Parameter(Mandatory=$false)]
    [array] # skipped file-names
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

  function has($list, $item) {
    $list.forEach({ if ("$_" -eq "$item") { return $true } })
    return $false
  }

  # ex: ./bin/debug/x64
  $work = $path + '/' + $name + '/' + $arch

  $(Get-ChildItem "$work" -Name).forEach({
    if (has $skip "$_")
    {
      script:file -path "$work" -skip:$true  -name "$_"
    } else {
      script:file -path "$work" -skip:$false -name "$_"
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
