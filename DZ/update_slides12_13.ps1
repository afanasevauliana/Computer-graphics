$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$gamut=Join-Path $PSScriptRoot 'assets\gamut_adobe_srgb.png'
$devices=Join-Path $PSScriptRoot 'assets\icc_devices.jpg'
$msoFalse=0;$msoTrue=-1;$blank=12
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
function Base($s,$title,$num){$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream;Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 $title 28 $navy $true|Out-Null;Text $s 890 35 30 22 ('{0:00}' -f $num) 11 $gray $true 2|Out-Null}
function AddFittedPicture($s,$path,$x,$y,$w,$h){
  $p=$s.Shapes.AddPicture($path,$msoFalse,$msoTrue,$x,$y,-1,-1);$p.LockAspectRatio=$msoTrue
  if(($p.Width/$p.Height) -gt ($w/$h)){$p.Width=[single]$w;$p.Left=[single]$x;$p.Top=[single]($y+($h-$p.Height)/2)}else{$p.Height=[single]$h;$p.Top=[single]$y;$p.Left=[single]($x+($w-$p.Width)/2)}
  $p
}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  # Rebuild the existing combined slide as a focused explanation of color spaces.
  $s=$pres.Slides.Item(12);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()};Base $s 'Что задаёт цветовое пространство?' 12
  Rect $s 48 92 470 414 $white $true|Out-Null
  $text="Цветовое пространство задаёт систему координат, в которой цвет представлен числовыми значениями. Для однозначной интерпретации RGB недостаточно указать только три компонента: необходимо определить цветности красного, зелёного и синего первичных цветов, белую точку и передаточную функцию. Эти параметры связывают кодовые значения с измеримыми величинами CIE XYZ. Цветовой охват, или gamut, — это множество цветов, которые пространство может описать либо устройство может воспроизвести.`n`nНа диаграмме цветности CIE xy охват аддитивного RGB-пространства изображается треугольником между его первичными цветами. sRGB создавалось как универсальное пространство для мониторов и интернета и остаётся наиболее совместимым вариантом. Adobe RGB использует другие первичные цвета и охватывает больше насыщенных зелёных и голубых оттенков, что полезно при подготовке изображений к печати. Display P3 имеет более широкий охват, чем sRGB, особенно в красно-зелёной области, и применяется современными дисплеями. Rec. 2020 задаёт ещё более удалённые первичные цвета для систем телевидения сверхвысокой чёткости.`n`nШирокий охват не означает автоматически более точное изображение. Файл должен содержать встроенный профиль, а программа и дисплей должны правильно выполнять преобразование цвета. Одинаковые числа RGB в sRGB и Adobe RGB соответствуют разным цветовым стимулам. CIE XYZ и CIE Lab используют как независимые от конкретного устройства промежуточные представления. При корректном управлении цветом изображение переводится из исходного пространства в пространство устройства с учётом обоих профилей."
  Text $s 68 112 430 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $gamut 548 102 355 385|Out-Null

  # Add a separate slide about physical device limitations.
  $s=$pres.Slides.Add(13,$blank);Base $s 'Почему устройства воспроизводят цвет по-разному?' 13
  Rect $s 48 92 470 414 $white $true|Out-Null
  $text="Каждое устройство формирует собственную зависимость между числовым сигналом и наблюдаемым цветом. Камера измеряет свет через спектральные характеристики сенсора и цветных фильтров, поэтому её RGB-координаты зависят от конкретной модели. Дисплей смешивает излучение трёх первичных компонентов, а его возможности ограничены их спектрами, максимальной яркостью и уровнем чёрного. Принтер использует отражённый свет и субтрактивное смешение красок CMYK, поэтому результат дополнительно зависит от чернил, бумаги и освещения.`n`nОхваты камеры, монитора и принтера имеют разную форму и не являются вложенными полностью. Цвет, доступный широкоформатному дисплею, может оказаться невоспроизводимым в печати, а некоторые голубые и жёлтые печатные оттенки не совпадают с возможностями обычного sRGB-монитора. При переводе в меньший охват возникают значения out of gamut. Простое поканальное ограничение таких значений способно изменить цветовой тон и уничтожить различия между насыщенными оттенками. Поэтому применяют gamut mapping — преобразование невоспроизводимых цветов в доступные с минимально приемлемым изменением внешнего вида.`n`nICC-профиль описывает измеренные цветовые характеристики конкретного устройства или стандартного пространства. Система управления цветом переводит данные через независимое пространство связи профилей CIE XYZ или CIE Lab. Колориметрический способ сохраняет доступные цвета точнее, но крайние оттенки может обрезать. Перцепционный способ сжимает весь исходный охват, стремясь сохранить отношения между цветами изображения. Даже при наличии профиля результат зависит от калибровки монитора, адаптации зрения и условий просмотра, поэтому абсолютное совпадение экрана и отпечатка физически недостижимо."
  Text $s 68 112 430 374 $text 10 $ink|Out-Null
  AddFittedPicture $s $devices 535 132 385 310|Out-Null

  # Renumber the slides shifted by the insertion.
  for($n=14;$n -le $pres.Slides.Count;$n++){
    $sl=$pres.Slides.Item($n)
    for($i=1;$i -le $sl.Shapes.Count;$i++){
      $sh=$sl.Shapes.Item($i)
      if($sh.HasTextFrame -eq $msoTrue -and $sh.Left -gt 850 -and $sh.Top -lt 70){$sh.TextFrame.TextRange.Text=('{0:00}' -f $n)}
    }
  }
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
