$script:type = 'debug'
$script:work = './bin/' + $script:type + '/x64'
$script:arch = ( 'x86', 'x64' )
$script:keep = ( '.gitkeep' )

function skip($item) {
  function local:test($l, $i) {
    $l.forEach({ if ("$_" -eq "$i") { return $true } })
    return $false
  }

  return local:test $script:keep $item
}

$(Get-ChildItem $script:work -Name).forEach({
  if (skip "$_") {
    Write-Host -ForegroundColor Green "* $script:work/$_"
    Write-Host -ForegroundColor White '' -NoNewline # reset color
  } else {
    Write-Host -ForegroundColor Red "- $script:work/$_"
    Write-Host -ForegroundColor White '' -NoNewline # reset color
    Remove-Item -Force -Recurse -ErrorAction SilentlyContinue "$script:work/$_"
  }
})

#New-Item "$script:work/.gitkeep"
