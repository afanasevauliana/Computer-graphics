$ErrorActionPreference = 'Stop'
$source = Join-Path $PSScriptRoot 'Особенности человеческого цветовосприятия.pptx'
$target = Join-Path $PSScriptRoot 'Особенности человеческого цветовосприятия — расширенная.pptx'
$assets = Join-Path $PSScriptRoot 'assets'
$msoFalse = 0; $msoTrue = -1; $blank = 12; $format = 24
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51; $ink=RGB 37 45 59; $cream=RGB 247 244 238; $coral=RGB 239 101 87
$blue=RGB 57 117 224; $cyan=RGB 46 196 182; $gray=RGB 108 117 131; $white=RGB 255 255 255; $light=RGB 232 237 244

function Text($slide,$x,$y,$w,$h,$value,$size=18,$color=$ink,$bold=$false,$align=1){
  $s=$slide.Shapes.AddTextbox(1,$x,$y,$w,$h); $s.TextFrame.TextRange.Text=$value
  $s.TextFrame.TextRange.Font.Name='Aptos'; $s.TextFrame.TextRange.Font.Size=$size
  $s.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse}); $s.TextFrame.TextRange.Font.Color.RGB=$color
  $s.TextFrame.TextRange.ParagraphFormat.Alignment=$align; $s.TextFrame.MarginLeft=0; $s.TextFrame.MarginRight=0
  $s.TextFrame.MarginTop=0; $s.TextFrame.MarginBottom=0; $s
}
function Rect($slide,$x,$y,$w,$h,$fill,$round=$true){
  $s=$slide.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$s.Fill.ForeColor.RGB=$fill;$s.Line.Visible=$msoFalse;$s
}
function Base($pres,$index,$title){
  $s=$pres.Slides.Add($index,$blank);$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral $false|Out-Null; Text $s 52 28 840 45 $title 27 $navy $true|Out-Null;$s
}
function Source($slide,$value){
  Text $slide 55 508 850 18 $value 8 $gray $false|Out-Null
}
function Para($slide,$x,$y,$w,$text,$title){
  Rect $slide $x $y $w 128 $white|Out-Null
  Text $slide ($x+18) ($y+15) ($w-36) 26 $title 17 $navy $true|Out-Null
  Text $slide ($x+18) ($y+48) ($w-36) 68 $text 13 $ink $false|Out-Null
}

$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue
$pres=$ppt.Presentations.Open($source,0,0,0)
try{
  # Add concise evidence notes and citations to existing physiology slides.
  Text $pres.Slides.Item(2) 60 455 835 38 'Важное различие: физически измеряются спектр и отражательная способность, а цвет является результатом работы зрительной системы.' 14 $navy $true 2|Out-Null
  Source $pres.Slides.Item(2) 'Факты: NCBI Bookshelf, Color Vision — https://www.ncbi.nlm.nih.gov/books/NBK11537/'

  # Replace stylized eye with sourced anatomy figure.
  $s=$pres.Slides.Item(3)
  for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream;Rect $s 0 0 960 10 $coral $false|Out-Null
  Text $s 52 28 840 45 'Как глаз принимает световой сигнал' 27 $navy $true|Out-Null
  $s.Shapes.AddPicture((Join-Path $assets 'eye.svg'),$msoFalse,$msoTrue,45,105,430,370)|Out-Null
  Text $s 520 112 355 32 'От оптики к нервному сигналу' 19 $navy $true|Out-Null
  Text $s 520 160 355 205 "Свет проходит через роговицу и хрусталик и формирует перевёрнутое изображение на сетчатке.`n`nПалочки особенно важны при слабом освещении. Колбочки обеспечивают цветовое зрение и высокую пространственную детализацию при дневном освещении.`n`nФоторецепторы преобразуют свет в электрический ответ; дальнейшая обработка начинается уже в сетчатке." 15 $ink|Out-Null
  Rect $s 520 390 355 65 $navy|Out-Null
  Text $s 538 408 320 32 'Цвет формируется не в глазу отдельно, а в системе «сетчатка — мозг».' 14 $white $true 2|Out-Null
  Source $s 'Изображение: Wikimedia Commons, Schematic diagram of the human eye, CC BY-SA 3.0. Факты: NEI.'

  $s=$pres.Slides.Item(4)
  Rect $s 35 88 890 365 $cream $false|Out-Null
  $s.Shapes.AddPicture((Join-Path $assets 'cones.svg'),$msoFalse,$msoTrue,55,120,500,335)|Out-Null
  Text $s 585 128 310 220 "Кривые чувствительности S-, M- и L-колбочек сильно перекрываются. Поэтому отдельная колбочка не «измеряет цвет»: мозг сравнивает ответы разных типов рецепторов.`n`nПики чувствительности не равны названиям «синий, зелёный, красный» — это упрощённая мнемоника." 16 $ink|Out-Null
  Source $s 'График: Vanessaezekowitz / BenRG, Wikimedia Commons. Данные: Stockman, MacLeod & Johnson (1993).'

  Source $pres.Slides.Item(5) 'Факты: NCBI Bookshelf, The Perception of Color — https://www.ncbi.nlm.nih.gov/books/NBK11538/'
  Source $pres.Slides.Item(6) 'Факты: NCBI Bookshelf: современная модель объединяет трихроматическую и оппонентную теории.'
  Source $pres.Slides.Item(7) 'Факты: NCBI Bookshelf, Color Vision: адаптация изменяет относительный ответ цветовых каналов.'
  Source $pres.Slides.Item(8) 'Факты: NCBI Bookshelf, Color Vision: двойные оппонентные клетки усиливают одновременный контраст.'
  Source $pres.Slides.Item(9) 'Факты: NCBI Bookshelf, Physiology, Color Perception — https://www.ncbi.nlm.nih.gov/books/NBK544355/'
  Source $pres.Slides.Item(10) 'Факты: National Eye Institute, Color Blindness — https://www.nei.nih.gov/eye-health-information/eye-conditions-and-diseases/color-blindness'
  Source $pres.Slides.Item(11) 'Рекомендации: W3C WCAG 2.1, критерии 1.4.1 и 1.4.3.'

  # Insert four computer-graphics slides before conclusions.
  $s=Base $pres 12 'Почему цветовосприятие важно для компьютерной графики'
  Text $s 60 92 835 48 'Компьютерная графика строит не физический свет, а численную модель изображения, рассчитанную на особенности человеческого зрения и конкретное устройство вывода.' 18 $ink|Out-Null
  $steps=@(
    @{x=55;t='1. Сцена';d='геометрия, материалы, источники света';c=$blue},
    @{x=280;t='2. Рендеринг';d='расчёт освещения и значений RGB';c=$cyan},
    @{x=505;t='3. Дисплей';d='преобразование кодов в излучение';c=$coral},
    @{x=730;t='4. Наблюдатель';d='адаптация, контраст и интерпретация';c=RGB 139 92 246}
  )
  foreach($a in $steps){Rect $s $a.x 205 180 175 $a.c|Out-Null;Text $s ($a.x+15) 230 150 30 $a.t 18 $white $true 2|Out-Null;Text $s ($a.x+16) 285 148 60 $a.d 14 $white $false 2|Out-Null}
  Text $s 70 415 820 55 'Следствие: правильный алгоритм должен учитывать цветовое пространство, динамический диапазон, нелинейность дисплея и условия просмотра.' 17 $navy $true 2|Out-Null
  Source $s 'Техническая связь: IEC 61966-2-1 (sRGB); Khronos OpenGL Specification, FRAMEBUFFER_SRGB.'

  $s=Base $pres 13 'Цветовой охват: глаз видит больше, чем экран'
  $s.Shapes.AddPicture((Join-Path $assets 'cie.png'),$msoFalse,$msoTrue,55,92,410,390)|Out-Null
  Text $s 510 100 385 235 "Диаграмма CIE xy описывает цветности, различимые стандартным наблюдателем. Треугольник sRGB показывает только те цветности, которые можно получить смешением трёх заданных первичных цветов дисплея.`n`nЦвета вне треугольника не воспроизводятся таким монитором точно. При выводе их приходится обрезать или преобразовывать (gamut mapping)." 16 $ink|Out-Null
  Rect $s 510 365 385 87 $navy|Out-Null
  Text $s 530 383 345 52 'В графике выбор цветового пространства ограничивает доступную палитру результата.' 16 $white $true 2|Out-Null
  Source $s 'Изображение: CIE Chart with sRGB gamut by spigget, Wikimedia Commons. Стандарт: IEC 61966-2-1.'

  $s=Base $pres 14 'sRGB и гамма-кодирование: почему нельзя смешивать цвета «как есть»'
  Para $s 55 100 400 'Значения, записанные в обычном sRGB-файле, нелинейно связаны с физической интенсивностью света. Такое кодирование эффективнее распределяет уровни по диапазону.' 'Кодированные значения'
  Para $s 505 100 400 'Освещение, интерполяцию, размытие и альфа-смешение физически корректнее считать в линейном цветовом пространстве.' 'Линейные вычисления'
  Rect $s 55 268 850 148 $white|Out-Null
  Text $s 82 292 796 30 'Типичный путь пикселя' 18 $navy $true 2|Out-Null
  Text $s 82 342 796 40 'sRGB-текстура  →  декодирование  →  линейный шейдинг и blending  →  кодирование sRGB  →  экран' 17 $blue $true 2|Out-Null
  Text $s 90 446 780 36 'Если пропустить преобразование, градиенты и смешение могут стать визуально слишком тёмными.' 16 $coral $true 2|Out-Null
  Source $s 'Источник: Khronos OpenVG 1.0.1, §3.4.2; OpenGL 3.0 Specification, FRAMEBUFFER_SRGB.'

  $s=Base $pres 15 'Тональное отображение и цветовое управление'
  Para $s 55 98 400 'HDR-рендеринг может содержать яркости, которые монитор показать не способен. Tone mapping сжимает диапазон, стараясь сохранить детали и воспринимаемый контраст.' 'Tone mapping'
  Para $s 505 98 400 'ICC-профиль описывает цветовое поведение устройства. Система управления цветом переводит данные между пространствами камеры, монитора и принтера.' 'Color management'
  Para $s 55 260 400 'Баланс белого компенсирует цвет освещения. Его задача связана с цветовой константностью человеческого зрения, но камера выполняет компенсацию вычислительно.' 'Баланс белого'
  Para $s 505 260 400 'Перцептивные модели и метрики стремятся оценивать не только разницу координат RGB, но и то, насколько различие заметно человеку.' 'Перцептивная оценка'
  Text $s 70 438 820 45 'Именно здесь знания о зрении превращаются в практические алгоритмы обработки и синтеза изображений.' 17 $navy $true 2|Out-Null
  Source $s 'Источники: ICC, Introduction to Color Management; Fairchild M. D., Color Appearance Models.'

  # Existing conclusion/source slides are now 16 and 17. Replace sources with a fuller list.
  $s=$pres.Slides.Item(17)
  for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream;Rect $s 0 0 960 10 $coral $false|Out-Null
  Text $s 52 28 840 45 'Источники фактов и иллюстраций' 27 $navy $true|Out-Null
  $srcText="1. National Eye Institute. Color Blindness; How the Eyes Work.`n2. NCBI Bookshelf (Webvision). Color Vision; The Perception of Color.`n3. StatPearls / NCBI. Physiology, Color Perception.`n4. W3C. WCAG 2.1: Use of Color; Contrast (Minimum).`n5. IEC 61966-2-1: Default RGB colour space — sRGB.`n6. Khronos. OpenGL 3.0 Specification; OpenVG 1.0.1 Specification.`n7. Fairchild M. D. Color Appearance Models. Wiley, 2013.`n8. ICC. Introduction to Color Management."
  Text $s 65 100 830 300 $srcText 15 $ink|Out-Null
  Text $s 65 415 830 58 'Иллюстрации: Wikimedia Commons — Schematic diagram of the human eye (CC BY-SA 3.0); Cones SMJ2 E; CIE Chart with sRGB gamut by spigget. Ссылки и лицензии указаны на соответствующих слайдах.' 12 $gray|Out-Null
  Text $s 65 480 830 22 'Дата обращения к интернет-источникам: 27.08.2026.' 11 $gray|Out-Null

  $pres.SaveAs($target,$format)
}finally{
  $pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null
  [GC]::Collect();[GC]::WaitForPendingFinalizers()
}
Write-Output $target
