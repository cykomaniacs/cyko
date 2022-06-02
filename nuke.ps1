$script:base = './bin'
$script:keep = ( '.gitkeep' )

#$script:conf = ( 'debug' )
#$script:work = './bin/' + $script:type + '/x64'
#$script:arch = ( 'x64' )

function script:nuke {
  param (
    [Parameter(Mandatory=$false, DontShow)]
    [array]
    $keep = $script:keep, #( '.gitkeep' ),

    [Parameter(Mandatory)]
    [string]
    $base,

    [Parameter(Mandatory)]
    [string]
    $target,

    [Parameter(Mandatory)]
    [string]
    $arch
  )

  function local:has($list, $item) {
    $list.forEach({ if ("$_" -eq "$item") { return $true } })
    return $false
  }

  # ./bin/debug/x64
  $local:work = $base + '/' + $target + '/' + $arch

  $(Get-ChildItem "$local:work" -Name).forEach({
    if (local:has $keep "$_")
    {
      Write-Host -ForegroundColor Green "* " -NoNewline
      Write-Host -ForegroundColor Gray "$local:work/$_"
      Write-Host -ForegroundColor White "" -NoNewline # reset color
    } else {
      Write-Host -ForegroundColor Red "- " -NoNewline
      Write-Host -ForegroundColor Gray "$local:work/$_"
      Write-Host -ForegroundColor White "" -NoNewline # reset color
      Remove-Item -Force -Recurse -ErrorAction SilentlyContinue "$local:work/$_"
    }
  })
}


#script:nuke -base "$script:base" -target 'debug' -arch 'x64'


$script:x = @{ # arch
  debug = (
    #'x86',
    'x64'
  );

  release = (
    #'x86',
    'x64'
  );
}

$script:targets = (
  'debug'
  #'release'
)

function script:head {
  param (
    [Parameter(Mandatory)]
    [string]
    $target,

    [Parameter(Mandatory)]
    [string]
    $arch
  )
  Write-Host -ForegroundColor DarkGray "> " -NoNewline
  Write-Host -ForegroundColor Blue "$target" -NoNewline
  Write-Host -ForegroundColor DarkCyan ":" -NoNewline
  Write-Host -ForegroundColor Blue "$arch" -NoNewline
  Write-Host -ForegroundColor DarkBlue "(" -NoNewline
  Write-Host -ForegroundColor DarkGray "nuke" -NoNewline
  Write-Host -ForegroundColor DarkBlue ")" -NoNewline
  Write-Host "" # reset color
}

$script:targets.forEach({ $t = $_
  $script:x[$t].forEach({
    script:head -target $t -arch $_
    script:nuke -base "$script:base" -target $t -arch $_
  })
})

#New-Item "$script:work/.gitkeep"
