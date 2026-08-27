$ErrorActionPreference = 'Stop'
$dir = Join-Path $PSScriptRoot 'assets'
New-Item -ItemType Directory -Force -Path $dir | Out-Null
$items = @(
    @{Name='cie.png'; Url='https://www.laptop.co.nz/uploads/2/3/9/1/23918965/569871851_orig.png'},
    @{Name='ishihara.jpg'; Url='https://wellcomeimages.org/indexplus/obf_images/3f/b4/4c8694748d0324c90bbefb6a3b74.jpg'},
    @{Name='lcd.jpg'; Url='https://i.sstatic.net/zRP2h.jpg'}
)
foreach ($item in $items) {
    $target = Join-Path $dir $item.Name
    Invoke-WebRequest -Uri $item.Url -OutFile $target -UseBasicParsing
    Write-Output $target
}
