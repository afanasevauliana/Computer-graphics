$ErrorActionPreference = 'Stop'

$outPath = Join-Path $PSScriptRoot 'Особенности человеческого цветовосприятия.pptx'
$ppLayoutBlank = 12
$ppSaveAsOpenXMLPresentation = 24
$msoFalse = 0
$msoTrue = -1

function RGB([int]$r, [int]$g, [int]$b) { return $r + 256 * $g + 65536 * $b }

$C = @{
    Navy = RGB 21 31 51; Ink = RGB 37 45 59; White = RGB 255 255 255
    Cream = RGB 247 244 238; Coral = RGB 239 101 87; Blue = RGB 57 117 224
    Cyan = RGB 46 196 182; Yellow = RGB 248 196 74; Gray = RGB 108 117 131
    Light = RGB 232 237 244; Green = RGB 65 168 95; Purple = RGB 139 92 246
}

function Add-Text($slide, [double]$x, [double]$y, [double]$w, [double]$h, [string]$text,
                  [double]$size = 20, [int]$color = 0, [bool]$bold = $false,
                  [string]$font = 'Aptos', [int]$align = 1) {
    $s = $slide.Shapes.AddTextbox(1, $x, $y, $w, $h)
    $s.TextFrame.TextRange.Text = $text
    $s.TextFrame.TextRange.Font.Name = $font
    $s.TextFrame.TextRange.Font.Size = $size
    $s.TextFrame.TextRange.Font.Bold = $(if ($bold) { $msoTrue } else { $msoFalse })
    $s.TextFrame.TextRange.Font.Color.RGB = $color
    $s.TextFrame.TextRange.ParagraphFormat.Alignment = $align
    $s.TextFrame.MarginLeft = 0; $s.TextFrame.MarginRight = 0
    $s.TextFrame.MarginTop = 0; $s.TextFrame.MarginBottom = 0
    return $s
}

function Add-Rect($slide, [double]$x, [double]$y, [double]$w, [double]$h, [int]$fill,
                  [double]$radius = 0, [int]$line = -1) {
    $type = $(if ($radius -gt 0) { 5 } else { 1 })
    $s = $slide.Shapes.AddShape($type, $x, $y, $w, $h)
    $s.Fill.ForeColor.RGB = $fill
    if ($line -lt 0) { $s.Line.Visible = $msoFalse } else { $s.Line.ForeColor.RGB = $line }
    return $s
}

function Add-Circle($slide, [double]$x, [double]$y, [double]$d, [int]$fill, [double]$trans = 0) {
    $s = $slide.Shapes.AddShape(9, $x, $y, $d, $d)
    $s.Fill.ForeColor.RGB = $fill; $s.Fill.Transparency = $trans
    $s.Line.Visible = $msoFalse
    return $s
}

function Add-Line($slide, [double]$x1, [double]$y1, [double]$x2, [double]$y2, [int]$color, [double]$weight = 2) {
    $s = $slide.Shapes.AddLine($x1, $y1, $x2, $y2)
    $s.Line.ForeColor.RGB = $color; $s.Line.Weight = $weight
    return $s
}

function Add-Base($pres, [string]$title, [int]$num) {
    $slide = $pres.Slides.Add($pres.Slides.Count + 1, $ppLayoutBlank)
    $slide.FollowMasterBackground = $msoFalse
    $slide.Background.Fill.ForeColor.RGB = $C.Cream
    Add-Rect $slide 0 0 960 10 $C.Coral | Out-Null
    Add-Text $slide 52 28 790 45 $title 27 $C.Navy $true | Out-Null
    Add-Text $slide 887 32 30 25 ('{0:00}' -f $num) 11 $C.Gray $true 'Aptos' 2 | Out-Null
    return $slide
}

function Add-BulletList($slide, [string[]]$items, [double]$x, [double]$y, [double]$w, [double]$fontSize = 20) {
    $yy = $y
    foreach ($item in $items) {
        Add-Circle $slide $x ($yy + 8) 9 $C.Coral | Out-Null
        Add-Text $slide ($x + 22) $yy ($w - 22) 60 $item $fontSize $C.Ink $false | Out-Null
        $yy += 67
    }
}

$ppt = New-Object -ComObject PowerPoint.Application
$ppt.Visible = $msoTrue
$pres = $ppt.Presentations.Add()
$pres.PageSetup.SlideWidth = 960
$pres.PageSetup.SlideHeight = 540

try {
    # 1. Title
    $s = $pres.Slides.Add(1, $ppLayoutBlank)
    $s.FollowMasterBackground = $msoFalse; $s.Background.Fill.ForeColor.RGB = $C.Navy
    Add-Circle $s 690 54 205 $C.Coral 0.08 | Out-Null
    Add-Circle $s 755 175 150 $C.Blue 0.10 | Out-Null
    Add-Circle $s 640 258 175 $C.Yellow 0.10 | Out-Null
    Add-Text $s 58 82 570 55 'ОСОБЕННОСТИ' 18 $C.Cyan $true | Out-Null
    Add-Text $s 58 135 585 155 "человеческого`nцветовосприятия" 42 $C.White $true | Out-Null
    Add-Line $s 58 322 520 322 $C.Coral 4 | Out-Null
    Add-Text $s 58 346 550 45 'Как мозг превращает свет в цвет' 23 $C.Light $false | Out-Null
    Add-Text $s 58 466 600 28 'Домашняя работа по компьютерной графике' 15 $C.Light $false | Out-Null

    # 2
    $s = Add-Base $pres 'Цвет — ощущение, а не свойство предмета' 2
    Add-BulletList $s @(
        'Свет — электромагнитное излучение; глаз реагирует лишь на узкий видимый диапазон.',
        'Поверхность поглощает часть спектра и отражает остальное.',
        'Цветовое ощущение формируется мозгом с учётом освещения, окружения и опыта.'
    ) 60 115 520 19
    # prism-like spectrum
    $labels = @('≈ 400 нм','фиолетовый','синий','зелёный','жёлтый','красный','≈ 700 нм')
    $cols = @((RGB 98 65 171),(RGB 71 92 198),(RGB 30 144 255),(RGB 57 181 74),(RGB 248 196 74),(RGB 239 101 87),(RGB 180 35 45))
    for ($i=0; $i -lt 7; $i++) { Add-Rect $s (625+$i*38) 160 39 175 $cols[$i] | Out-Null }
    Add-Text $s 625 348 267 28 'Видимый спектр' 16 $C.Navy $true 'Aptos' 2 | Out-Null
    Add-Text $s 625 382 267 45 'Длина волны влияет на цветовое ощущение' 14 $C.Gray $false 'Aptos' 2 | Out-Null

    # 3
    $s = Add-Base $pres 'Как глаз принимает световой сигнал' 3
    # stylized eye cross-section
    $eye = $s.Shapes.AddShape(9, 75, 145, 350, 220); $eye.Fill.ForeColor.RGB = $C.White; $eye.Line.ForeColor.RGB = $C.Navy; $eye.Line.Weight = 3
    Add-Circle $s 90 178 150 $C.Cyan 0.35 | Out-Null
    Add-Circle $s 132 216 72 $C.Navy | Out-Null
    Add-Circle $s 153 237 30 $C.White | Out-Null
    Add-Line $s 422 255 525 255 $C.Yellow 10 | Out-Null
    Add-Text $s 515 238 95 30 "зрительный`nнерв" 13 $C.Gray $true | Out-Null
    Add-Text $s 625 124 260 35 'Сетчатка содержит:' 20 $C.Navy $true | Out-Null
    Add-Rect $s 625 178 270 94 $C.White 8 | Out-Null
    Add-Text $s 647 194 230 30 'Палочки' 19 $C.Blue $true | Out-Null
    Add-Text $s 647 226 230 32 'яркость и сумеречное зрение' 15 $C.Ink | Out-Null
    Add-Rect $s 625 290 270 94 $C.White 8 | Out-Null
    Add-Text $s 647 306 230 30 'Колбочки' 19 $C.Coral $true | Out-Null
    Add-Text $s 647 338 230 32 'цвет и высокая детализация' 15 $C.Ink | Out-Null
    Add-Text $s 75 420 820 40 'Сетчатка преобразует свет в электрические сигналы, которые интерпретирует мозг.' 18 $C.Ink $false 'Aptos' 2 | Out-Null

    # 4
    $s = Add-Base $pres 'Три типа колбочек: принцип трихроматии' 4
    $coneData = @(
        @{x=95;c=$C.Blue;t='S';sub="короткие волны`n≈ 420 нм"},
        @{x=350;c=$C.Green;t='M';sub="средние волны`n≈ 530 нм"},
        @{x=605;c=$C.Coral;t='L';sub="длинные волны`n≈ 560 нм"}
    )
    foreach ($d in $coneData) {
        Add-Circle $s $d.x 135 170 $d.c 0.07 | Out-Null
        Add-Text $s ($d.x+48) 180 75 52 $d.t 38 $C.White $true 'Aptos' 2 | Out-Null
        Add-Text $s ($d.x-15) 325 200 52 $d.sub 16 $C.Ink $true 'Aptos' 2 | Out-Null
    }
    Add-Text $s 95 414 680 50 'Мозг сравнивает относительную активность S-, M- и L-колбочек — так возникает множество оттенков.' 19 $C.Navy $false 'Aptos' 2 | Out-Null

    # 5 RGB
    $s = Add-Base $pres 'Аддитивное смешение: модель RGB' 5
    Add-Circle $s 215 132 235 (RGB 255 30 45) 0.35 | Out-Null
    Add-Circle $s 365 132 235 (RGB 30 225 80) 0.35 | Out-Null
    Add-Circle $s 290 252 235 (RGB 35 90 255) 0.35 | Out-Null
    Add-Text $s 277 165 55 30 'R' 23 $C.White $true 'Aptos' 2 | Out-Null
    Add-Text $s 483 165 55 30 'G' 23 $C.White $true 'Aptos' 2 | Out-Null
    Add-Text $s 380 398 55 30 'B' 23 $C.White $true 'Aptos' 2 | Out-Null
    Add-Text $s 650 142 245 40 'Где применяется' 21 $C.Navy $true | Out-Null
    Add-BulletList $s @('мониторы и телевизоры','экраны смартфонов','камеры и сканеры') 650 198 250 17
    Add-Text $s 650 414 245 45 'R + G + B = белый' 18 $C.Coral $true 'Aptos' 2 | Out-Null

    # 6 opponent
    $s = Add-Base $pres 'Оппонентная обработка цвета' 6
    Add-Text $s 65 100 830 50 'После рецепторов сигнал кодируется не тремя независимыми цветами, а каналами противопоставления.' 19 $C.Ink $false 'Aptos' 2 | Out-Null
    $pairs = @(
        @{y=185;l='КРАСНЫЙ';r='ЗЕЛЁНЫЙ';lc=$C.Coral;rc=$C.Green},
        @{y=280;l='СИНИЙ';r='ЖЁЛТЫЙ';lc=$C.Blue;rc=$C.Yellow},
        @{y=375;l='СВЕТЛО';r='ТЕМНО';lc=$C.White;rc=$C.Navy}
    )
    foreach ($p in $pairs) {
        Add-Rect $s 125 $p.y 240 62 $p.lc 8 | Out-Null
        Add-Text $s 125 ($p.y+17) 240 28 $p.l 18 $(if($p.l -eq 'СВЕТЛО'){$C.Navy}else{$C.White}) $true 'Aptos' 2 | Out-Null
        Add-Text $s 386 ($p.y+14) 90 35 '↔' 30 $C.Gray $true 'Aptos' 2 | Out-Null
        Add-Rect $s 495 $p.y 240 62 $p.rc 8 | Out-Null
        Add-Text $s 495 ($p.y+17) 240 28 $p.r 18 $C.White $true 'Aptos' 2 | Out-Null
    }
    Add-Text $s 768 215 130 145 "Это объясняет`nпоследовательные`nобразы и многие`nцветовые иллюзии." 16 $C.Gray $false 'Aptos' 2 | Out-Null

    # 7 adaptation illusion
    $s = Add-Base $pres 'Цветовая адаптация и последовательный образ' 7
    Add-Text $s 60 96 840 35 'Неподвижно смотрите на крест в центре 20–30 секунд, затем переведите взгляд на белое поле.' 18 $C.Ink $false 'Aptos' 2 | Out-Null
    $illCols = @($C.Coral,$C.Green,$C.Blue,$C.Yellow)
    for ($i=0; $i -lt 4; $i++) {
        $xx = 105 + ($i%2)*160; $yy = 170 + [math]::Floor($i/2)*160
        Add-Rect $s $xx $yy 150 150 $illCols[$i] | Out-Null
    }
    Add-Text $s 223 292 55 55 '+' 38 $C.Navy $true 'Aptos' 2 | Out-Null
    Add-Rect $s 540 170 310 310 $C.White 5 $C.Light | Out-Null
    Add-Text $s 668 292 55 55 '+' 38 $C.Gray $true 'Aptos' 2 | Out-Null
    Add-Text $s 105 490 310 24 'Адаптация рецепторов' 14 $C.Gray $true 'Aptos' 2 | Out-Null
    Add-Text $s 540 490 310 24 'Появится образ дополнительных цветов' 14 $C.Gray $true 'Aptos' 2 | Out-Null

    # 8 simultaneous contrast
    $s = Add-Base $pres 'Контекст меняет восприятие цвета' 8
    Add-Text $s 65 98 830 34 'Два центральных квадрата имеют один и тот же цвет RGB (128, 128, 128).' 19 $C.Ink $false 'Aptos' 2 | Out-Null
    Add-Rect $s 105 160 320 255 (RGB 32 38 50) | Out-Null
    Add-Rect $s 535 160 320 255 (RGB 225 229 236) | Out-Null
    $mid = RGB 128 128 128
    Add-Rect $s 205 237 120 100 $mid | Out-Null
    Add-Rect $s 635 237 120 100 $mid | Out-Null
    Add-Text $s 105 438 320 32 'На тёмном фоне кажется светлее' 15 $C.Gray $true 'Aptos' 2 | Out-Null
    Add-Text $s 535 438 320 32 'На светлом фоне кажется темнее' 15 $C.Gray $true 'Aptos' 2 | Out-Null
    Add-Text $s 65 494 830 25 'Причина: зрительная система оценивает отношения и контрасты, а не только абсолютный сигнал.' 15 $C.Navy $false 'Aptos' 2 | Out-Null

    # 9 constancy
    $s = Add-Base $pres 'Цветовая константность' 9
    Add-Text $s 60 98 840 42 'Освещение меняет спектр света, но знакомый предмет обычно сохраняет для нас «свой» цвет.' 19 $C.Ink $false 'Aptos' 2 | Out-Null
    $lights = @(
        @{x=80; bg=(RGB 255 236 183); lab='тёплый свет'},
        @{x=350; bg=(RGB 226 235 245); lab='дневной свет'},
        @{x=620; bg=(RGB 189 218 255); lab='холодный свет'}
    )
    foreach($l in $lights){
        Add-Rect $s $l.x 170 230 220 $l.bg 8 | Out-Null
        Add-Circle $s ($l.x+65) 215 100 $C.Coral | Out-Null
        Add-Rect $s ($l.x+108) 305 14 55 $C.Green | Out-Null
        Add-Text $s $l.x 410 230 28 $l.lab 15 $C.Gray $true 'Aptos' 2 | Out-Null
    }
    Add-Text $s 80 470 770 30 'Мозг частично «вычитает» цвет освещения — важный принцип для баланса белого в камерах.' 16 $C.Navy $false 'Aptos' 2 | Out-Null

    # 10 deficiencies
    $s = Add-Base $pres 'Нарушения цветового зрения' 10
    Add-Text $s 60 94 840 37 'Чаще всего меняется различение красно-зелёных оттенков; полная цветовая слепота встречается редко.' 18 $C.Ink $false 'Aptos' 2 | Out-Null
    $cards = @(
        @{x=60;t='Протанопия';sub="снижено восприятие`nдлинноволнового сигнала";c=$C.Coral},
        @{x=350;t='Дейтеранопия';sub="снижено восприятие`nсредневолнового сигнала";c=$C.Green},
        @{x=640;t='Тританопия';sub="снижено восприятие`nкоротковолнового сигнала";c=$C.Blue}
    )
    foreach($a in $cards){
        Add-Rect $s $a.x 165 255 220 $C.White 8 | Out-Null
        Add-Circle $s ($a.x+82) 188 90 $a.c 0.10 | Out-Null
        Add-Text $s $a.x 292 255 30 $a.t 18 $C.Navy $true 'Aptos' 2 | Out-Null
        Add-Text $s ($a.x+18) 335 219 48 $a.sub 14 $C.Gray $false 'Aptos' 2 | Out-Null
    }
    Add-Text $s 60 430 840 48 'Важно: интерфейс не должен передавать смысл только цветом — добавляйте подписи, значки и различия формы.' 18 $C.Coral $true 'Aptos' 2 | Out-Null

    # 11 design
    $s = Add-Base $pres 'Что учитывать в компьютерной графике и интерфейсах' 11
    $rules = @(
        @{x=60;y=115;n='01';t='Контраст';d='Проверять читаемость текста и важных объектов.';c=$C.Coral},
        @{x=500;y=115;n='02';t='Не только цвет';d='Дублировать смысл формой, подписью или узором.';c=$C.Blue},
        @{x=60;y=300;n='03';t='Условия просмотра';d='Учитывать освещение, экран и цветовой профиль.';c=$C.Green},
        @{x=500;y=300;n='04';t='Умеренная палитра';d='Использовать цвет последовательно и без перегрузки.';c=$C.Purple}
    )
    foreach($r in $rules){
        Add-Rect $s $r.x $r.y 400 145 $C.White 8 | Out-Null
        Add-Circle $s ($r.x+22) ($r.y+22) 55 $r.c | Out-Null
        Add-Text $s ($r.x+22) ($r.y+38) 55 24 $r.n 15 $C.White $true 'Aptos' 2 | Out-Null
        Add-Text $s ($r.x+98) ($r.y+24) 275 28 $r.t 19 $C.Navy $true | Out-Null
        Add-Text $s ($r.x+98) ($r.y+65) 275 55 $r.d 15 $C.Gray | Out-Null
    }
    Add-Text $s 60 480 840 28 'Доступный дизайн помогает всем пользователям, а не только людям с особенностями зрения.' 16 $C.Navy $false 'Aptos' 2 | Out-Null

    # 12 conclusions
    $s = Add-Base $pres 'Главные выводы' 12
    Add-BulletList $s @(
        'Цвет возникает как результат совместной работы света, глаза и мозга.',
        'Три типа колбочек дают исходный сигнал, а мозг обрабатывает его сравнением и противопоставлением.',
        'Контекст, адаптация и освещение способны заметно изменить воспринимаемый оттенок.',
        'Знание цветовосприятия делает графику выразительной, понятной и доступной.'
    ) 90 118 770 19
    Add-Rect $s 90 414 770 60 $C.Navy 8 | Out-Null
    Add-Text $s 90 432 770 30 'Мы видим не длины волн — мы видим интерпретацию мозга.' 20 $C.White $true 'Aptos' 2 | Out-Null

    # 13 sources
    $s = Add-Base $pres 'Источники' 13
    $sources = @(
        '1. OpenStax. Anatomy & Physiology 2e: The Sense of Vision.',
        '2. Encyclopaedia Britannica. Colour vision; Human eye.',
        '3. National Eye Institute. How the Eyes Work; Color Blindness.',
        '4. W3C. Web Content Accessibility Guidelines (WCAG): Use of Color; Contrast.',
        '5. Fairchild M. D. Color Appearance Models. Wiley, 2013.'
    )
    Add-BulletList $s $sources 75 115 810 18
    Add-Text $s 75 462 810 40 'Иллюстрации и схемы выполнены автором средствами PowerPoint.' 15 $C.Gray $false 'Aptos' 2 | Out-Null

    $pres.SaveAs($outPath, $ppSaveAsOpenXMLPresentation)
}
finally {
    if ($pres) { $pres.Close() }
    $ppt.Quit()
    [System.Runtime.InteropServices.Marshal]::ReleaseComObject($pres) | Out-Null
    [System.Runtime.InteropServices.Marshal]::ReleaseComObject($ppt) | Out-Null
    [GC]::Collect(); [GC]::WaitForPendingFinalizers()
}

Write-Output $outPath
