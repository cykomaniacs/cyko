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

  #region parameters(info) not manadatory! enables parameter-less invokation
  [Parameter(ParameterSetName='3.0', Mandatory)]
  [Parameter(ParameterSetName='3.1', Mandatory)]
  [Alias('i')]
  [switch]
  $info,
  [Parameter(ParameterSetName='3.1', Position=1, Mandatory)]
  [Parameter(ParameterSetName='3.2')]
  [Alias('v')]
  [switch]
  $version
  #endregion
)


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
    $rgb = [ConsoleColor]::White,
    [Parameter()]
    [string[]] # output: ...
    $out
  )

  Write-Host -NoNewline -ForegroundColor:$rgb $out
}

#:SYNOPSIS
# Prints the line-feed character (new-line).
function log:feed {
  param (
    [Parameter()]
    [int]
    $num = 1
  )

  for ($i = 0; $i -lt $num; $i++) { Write-Host -NoNewline:$false }
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
    [Alias('length','number','num')]
    [uint] #--# length: manual
    $len = 20
  )

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
  log:host -rgb:Blue     -out:"${name}"
  log:host -rgb:DarkCyan -out:':'
  log:host -rgb:Red      -out:"${arch}"
  log:host -rgb:Yellow   -out:'('
  log:host -rgb:DarkGray -out:'nuke'
  log:host -rgb:Yellow   -out:')'
  log:feed -num:1
}
#:SYNOPSIS
# Prints info about a file (prefixed with nuke/keep indicator + path).
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
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [switch] # skip/save?
    $keep
  )

  $xx = $keep ? '*' : '-'
  $xc = $keep ? [ConsoleColor]::Green : [ConsoleColor]::Red
  $fc = [ConsoleColor]::Gray

  log:host -rgb:$xc -out:"${xx} "
  log:host -rgb:$fc -out:"${path}/${name}"
  log:feed -num:1
}
#endregion ------------------------------------------------------------------





#----------------------------------------------------------------------------
#region namespace nfo
#-----------------

#:SYNOPSIS
# Prints information about the script.
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

  log:feed -num:1
  log:host -rgb:DarkGray -out:'# '
  log:host -rgb:Blue     -out:$info.description
  log:host -rgb:DarkGray -out:' - '
  nfo:version -string:$info.version.number -name:$info.version.name
  log:host -rgb:DarkGray -out:'# ';log:line -rgb:DarkGray -len:40
  log:feed -num:1
  log:host -rgb:DarkGray -out:'# '
  log:host -rgb:Gray     -out:$info.author.name
  log:host -rgb:Gray     -out:' <'
  log:host -rgb:DarkGray -out:$info.author.mail
  log:host -rgb:Gray     -out:'>'
  log:feed -num:1
  log:host -rgb:DarkGray -out:'# '
  log:host -rgb:Gray     -out:$info.organization.name
  log:host -rgb:Gray     -out:' <'
  log:host -rgb:DarkGray -out:$info.organization.home
  log:host -rgb:Gray     -out:'>'
  log:feed -num:1
  log:host -rgb:DarkGray -out:'# ';log:line -rgb:DarkGray -len:41
  log:feed -num:1
  log:host -rgb:DarkGray -out:'# '
  nfo:repo -url:$repo  -rgb:Blue
  log:host -rgb:DarkGray -out:'# ';log:line -rgb:DarkGray -len:22
  log:feed -num:1
  log:host -rgb:DarkGray -out:'# '
  log:host -rgb:Cyan     -out:$date.updated
  log:host -rgb:DarkGray -out:'('
  log:host -rgb:DarkCyan -out:$date.created
  log:host -rgb:DarkGray -out:')'
  log:feed -num:2
}
#:SYNOPSIS
# Prints usage / help (using the Get-Help command).
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

  function self:defaults { Get-Help "${path}" }
  function self:complete { Get-Help "${path}" -Full }
  function self:examples { Get-Help "${path}" -Examples }
  function self:detailed { Get-Help "${path}" -Detailed }

  if ($nude)
  {
    log:host -rgb:Red        -out:'$ '
    log:host -rgb:Yellow     -out:'nuke.ps1'
    log:host -rgb:DarkYellow -out:' -'
    log:host -rgb:Yellow     -out:'h '
    log:host -rgb:DarkGray   -out:'for more information ...'
    log:feed -num:1
  } elseif ($complete) { self:complete
  } elseif ($examples) { self:examples
  } elseif ($detailed) { self:detailed
  } else { self:defaults }
}
#:SYNOPSIS
# Prints information about the source code repository.
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

  log:host -rgb:$rgb -out:$url
  log:feed -num:1
}
#:SYNOPSIS
# Prints version information.
function nfo:version {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [string] # version number
    $string,
    [Parameter()]
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
  log:feed -num:((($null -eq $name) -or ($name.Length -lt 1)) ? 1:0)
  log:host -rgb:DarkCyan -out:' <'
  log:host -rgb:DarkGray -out:$name
  log:host -rgb:DarkCyan -out:'>'
  log:feed -num:1
}
#endregion ------------------------------------------------------------------



#----------------------------------------------------------------------------
#region namespace dbg (debug)
#-----------------
$script:dbg = $null # ErrorVariable
$script:dov = 'OK!' # ErrorVariable : d(efault)o(kay)v(alue)
#-----------------

trap {
  log:feed -num:1
  log:line -rgb:DarkGray -full; log:feed
  log:host -rgb:DarkGray -out:"> "
  log:host -rgb:Red -out:"BUG"
  log:host -rgb:DarkGray -out:"|"
  log:host -rgb:Gray -out:"TRAP"
  log:host -rgb:DarkGray -out:" Unknown error ..."
  log:feed -num:1
  log:host -rgb:DarkGray -out:"> "
  log:host -rgb:Red -out $PSItem
  log:feed -num:1
  log:line -rgb:DarkGray -full
  log:feed -num:2
  #$Error[0].InvocationInfo
}

#.SYNOPSIS
# Returns the name of the common-debug-variable.
# Use: Some-Command -ErrorVariable:(dbg:data:variable)
function dbg:data:variable { 'dbg' <# name of ErrorVariable #> }
#.SYNOPSIS
# Resets the common-debug-varable to its default value (and clears $Error).
function dbg:data:reset { $script:dbg = $Error.Clear() }
#.SYNOPSIS
# Returns the value of the common-debug-variable.
function dbg:data { $script:dbg }
#.SYNOPSIS
# Returns true if there are no global errors.
function dbg:okay { (dbg:fail:count) -eq 0 }
#.SYNOPSIS
# Returns the number of global errors.
function dbg:fail:count { $Error.Count }

#:SYNOPSIS
# Failure handling.
function dbg:fail {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('x')]
    [string]
    $context,
    [Parameter()]
    [Alias('m')]
    [string]
    $message = (dbg:data),
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
    $ln = $Error[0].InvocationInfo.ScriptLineNumber
    $cn = $Error[0].InvocationInfo.OffsetInLine
  }

  log:host -rgb:DarkRed   -out:'#'
  log:host -rgb:Yellow    -out:'['
  log:host -rgb:Green     -out:$ln #@ line-number
  log:host -rgb:DarkGray  -out:','
  log:host -rgb:DarkGreen -out:$cn #@ line-number:column-number
  log:host -rgb:Yellow    -out:']'
  log:host -rgb:Blue      -out:' <'
  log:host -rgb:DarkCyan  -out:"${context}"
  log:host -rgb:Blue      -out:'> '
  log:host -rgb:Red       -out:"${message}"
  log:feed -num:1

  dbg:data:reset # clear $Error
  app:kill -c:(dbg:fail:count) -fake:(!$critical)
}

#:SYNOPSIS
# Handle failures. Evaluates the common-debug parameters per default.
function dbg:eval {
  param (
    [Parameter(Mandatory)]
    [ValidateNotNullOrEmpty()]
    [Alias('x')]
    [string]
    $context,
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [Alias('m')]
    [string]
    $message = (dbg:data),
    [Parameter()]
    [alias('die')]
    [switch]
    $critical
  )

  if (!(dbg:okay))
  {
    dbg:fail -x:$context -m:$message -critical:$critical
    dbg:data:reset
    app:kill -c:1 -fake:(!$critcal)
  } else { dbg:data:reset }
}
#endregion ------------------------------------------------------------------



#----------------------------------------------------------------------------
#region namespace app
#----------------------------------------------------------------------------
#region namespace app - constants
#-----------------
$script:app = @{
  name = @{
    data = $MyInvocation.MyCommand.Name
  # base = script name without extension
  # conf = complete file-name
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
$script:app.name.Add('base', $script:app.name.data.Substring(0,
  $script:app.name.data.LastIndexOf('.')))
$script:app.name.Add('conf', $script:app.name.base + '.psd1')
#endregion ------------------------------------------------------------------

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

  if (!$fake)
  {
    exit $code
  } elseif ($verbose) {
    log:host -rgb:Yellow   -out:exit
    log:host -rgb:DarkGray -out::
    log:host -rgb:Red      -out:$code
    log:feed -num:1
  }
}

#:SYNOPSIS
# Returns the number of cmd-line arguments.
function app:argc { # returns the number of cmd-line arguments.
  param (
    [Parameter()]
    [switch]
    $all
  )

  $all ? $app.args.all.Length : $app.args.bound.Count
}

#:SYNOPSIS
# Returns the cmd-line arguments as an array.
function app:argv { # returns the cmd-line arguments
  param (
    [Parameter()]
    [switch]
    $all
  )

  $all ? $app.args.all : $app.args.bound
}

#.SYNOPSIS
# Returns true if the scripts was invoked without arguments (nude)?
function app:nude { (app:argc) -eq 0 }

#:SYNOPSIS
# Main functionality (deleter).
function app:nuke {
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
    Remove-Item `
      -Force `
      -Recurse `
      -ErrorAction:SilentlyContinue `
      -Path:"${path}/${node}"
  }
}

#:SYNOPSIS
# Main (first function called).
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

    $tmp = Get-ChildItem -Hidden:$all `
      -Path:"${path}" `
      -Name `
      -ErrorAction:SilentlyContinue `
      -ErrorVariable:(dbg:data:variable)
    dbg:eval -context:Get-ChildItem -message:"path: ${path}" -critical -verbose
    $tmp
  }

  # ex: ./bin/debug/x64
  $node = $path + '/' + $name + '/' + $arch
  # need -Hidden:$true on nix, $false on win (-all alias for -Hidden)
  @($false,$true).foreach({
    $(main:list -path:"${node}" -all:$_).foreach({
      if ($keep.Contains("${_}"))
      {
        log:file -path:"${node}" -name:"${_}" -keep
      } else {
        log:file -path:"${node}" -name:"${_}"
        app:nuke -path:"${node}" -node:"${_}" -fake:$fake
      }
    })
  })
}
#endregion ------------------------------------------------------------------




#----------------------------------------------------------------------------
#region namespace key(cfg) - module variable (constants)
#-----------------
# each key refers to a specific configuration variable (preference).
# case-sensitive!
#-----------------
# $var[([key]::info)]
#-----------------

#.SYNOPSIS
# Configuration (psd1) keys.
class key {
  static [string]$info = 'info'
  static [string]$date = 'date'
  static [string]$repo = 'repo'
  static [string]$fake = 'fake'
  static [string]$keep = 'keep'
}

#endregion ------------------------------------------------------------------
#region namespace mod(cfg) - module importer
#-----------------
# import/source
#-----------------
$mop = $app.path.work + '/' + $app.name.conf # m(od-)p(ath)
$mod = Import-PowerShellDataFile -Path:$mop `
  -ErrorAction:SilentlyContinue `
  -ErrorVariable:(dbg:data:variable)
dbg:eval -context:Import-PowerShellDataFile -critical # fail-safe
#-----------------
function mod:has {
  param (
    [Parameter(Mandatory)]
    [string]
    $key,
    [Parameter()]
    [Alias('die')]
    [switch]
    $critical
  )

  if (!$mod.ContainsKey($key)) {
    if ($critical)
    {
      dbg:fail -die -x:configuration -m:"cannot find specified key: ${key}"
    } else {
      return $false
    }
  } else { return $true }
}
function mod:get {
  param (
    [Parameter(ParameterSetName='1.0', Mandatory)]
    [Parameter(ParameterSetName='1.1', Mandatory)]
    [string]
    $key,
    [Parameter(ParameterSetName='1.0')]
    [AllowNull()]
    [Alias('def')]
    [object]
    $default = $null,
    [Parameter(ParameterSetName='1.1')]
    [Alias('die')]
    [switch]
    $critical
  )

  (mod:has -key:$key -critical:$critical) ? $mod[$key] : $default
}
#endregion ------------------------------------------------------------------
#region namespace cfg
#-----------------
$cfg = @{ # importing
  keep = @(mod:get -key:([key]::keep) -default:$keep) + $keep
  #----------------------------------------------------#
  info = mod:get -key:([key]::info) -default:$infocritical
  date = mod:get -key:([key]::date) -critical
  repo = mod:get -key:([key]::repo) -critical
  fake = mod:get -key:([key]::fake) -default:$fake
}
#endregion ------------------------------------------------------------------



#----------------------------------------------------------------------------
#region: script execution
#----------------------------------------------------------------------------
if (app:nude)
{
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
  nfo:help -nude
} elseif ($help) {
  nfo:help
} elseif ($version) {
  nfo:version -string:$cfg.info.version.number -name:$cfg.info.version.name
} elseif ($info) {
  nfo:main -info:$cfg.info -repo:$cfg.repo -date:$cfg.date
} else {
  $name.foreach({ $n = $_
    $arch.foreach({
      log:head -name:"${n}" -arch:"${_}" ; app:main `
        -fake:$cfg.fake `
        -keep:$cfg.keep `
        -path:"${base}" `
        -name:"${n}" `
        -arch:"${_}"
    })
  })
}
#endregion ------------------------------------------------------------------


class version {
  [ValidateNotNullOrEmpty()][string]$number
  [ValidateNotNullOrEmpty()][string]$name

  hidden [uint]$major # !.?.?
  hidden [uint]$minor # ?.!.?
  hidden [uint]$patch # ?.?.!

  static [string]
  major([string]$num) {
    return $num.Substring(0, $num.indexOf('.'))
  }

  static [string]
  minor([string]$num) {
    return $num.Substring(
      ($num.indexOf('.') + 1),
      ($num.LastIndexOf('.') - 2)
    )
  }

  static [string]
  patch([string]$num) {
    return $num.Substring(($num.LastIndexOf('.') + 1))
  }

  version([object]$tab <# config entry #>) {
    $this.number = $tab.number
    $this.name = $tab.name

    $this.major = [version]::major($this.number)
    $this.minor = [version]::minor($this.number)
    $this.patch = [version]::patch($this.number)
  }
}
