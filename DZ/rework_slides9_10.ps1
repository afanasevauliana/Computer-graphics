$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$subpixels=Join-Path $PSScriptRoot 'assets\rgb_subpixels.jpg'
$mixing=Join-Path $PSScriptRoot 'assets\rgb_additive.png'
$cie=Join-Path $PSScriptRoot 'assets\cie.png'
$msoFalse=0;$msoTrue=-1;$blank=12
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
function Base($s,$title,$num){$s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream;Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 $title 28 $navy $true|Out-Null;Text $s 890 35 30 22 ('{0:00}' -f $num) 11 $gray $true 2|Out-Null}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  # Rebuild slide 9 with a physical/display-science emphasis.
  $s=$pres.Slides.Item(9);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()};Base $s 'Как дисплей физически формирует цвет?' 9
  Rect $s 48 92 445 218 $white $true|Out-Null
  $left="Цвет на дисплее физически задаётся спектральным распределением мощности излучения, поступающего от каждого пикселя. Пиксель состоит из нескольких независимо управляемых субпикселей, обычно красного, зелёного и синего. Каждый тип субпикселя имеет собственный спектр излучения, который занимает не одну длину волны, а некоторый диапазон.`n`nВ LCD-панели белая подсветка проходит через жидкокристаллические модуляторы и цветовые фильтры. В OLED-дисплее субпиксели сами являются источниками света. Электрический сигнал изменяет яркость компонентов и тем самым изменяет результирующее спектральное распределение пикселя."
  Text $s 68 112 405 176 $left 12 $ink|Out-Null
  $p1=$s.Shapes.AddPicture($mixing,$msoFalse,$msoTrue,68,335,405,132);$p1.LockAspectRatio=$msoTrue;$p1.Width=405
  $p2=$s.Shapes.AddPicture($subpixels,$msoFalse,$msoTrue,522,92,390,225);$p2.LockAspectRatio=$msoTrue;$p2.Width=390
  Rect $s 522 330 390 190 $white $true|Out-Null
  $right="Свет от близко расположенных субпикселей пространственно интегрируется оптической системой глаза. Результирующий спектр приблизительно равен взвешенной сумме спектров трёх первичных компонентов. Такое сложение излучений называется аддитивным синтезом.`n`nРазные спектры могут вызывать одинаковые ответы S-, M- и L-колбочек и поэтому восприниматься как один цвет; это явление называется метамерией. Благодаря метамерии дисплею не требуется воспроизводить спектр реального объекта полностью. Достаточно создать три стимула, вызывающие нужное соотношение ответов колбочек. Точность воспроизведения при этом ограничена спектрами первичных компонентов, максимальной яркостью, уровнем чёрного и условиями наблюдения."
  Text $s 540 344 354 164 $right 10 $ink|Out-Null

  # Insert a new colorimetry/encoding slide at position 10.
  $s=$pres.Slides.Add(10,$blank);Base $s 'Как RGB-значения превращаются в измеримый цвет?' 10
  Rect $s 48 92 445 414 $white $true|Out-Null
  $text="Числа R, G и B сами по себе не задают однозначный физический цвет. Для интерпретации требуется цветовое пространство, определяющее цветности первичных компонентов, белую точку и передаточную функцию. Распространённое пространство sRGB использует первичные цветности стандарта BT.709 и белую точку D65.`n`nЗначения sRGB кодируются нелинейно и не пропорциональны излучаемой яркости. Передаточная функция преобразует сохранённые значения в линейные компоненты света. Такое кодирование эффективнее распределяет дискретные уровни с учётом чувствительности зрения. Однако расчёты освещения, интерполяцию и альфа-смешение следует выполнять в линейном пространстве. Спецификация OpenGL поэтому предусматривает декодирование sRGB перед операцией blending и обратное кодирование результата.`n`nПри восьми битах каждый канал содержит 256 кодовых уровней, но соседние уровни не соответствуют одинаковым приращениям яркости. Для независимого от устройства описания используют колориметрическую систему CIE XYZ, основанную на функциях стандартного наблюдателя. Линейные sRGB и XYZ связаны матричным преобразованием. Треугольник первичных цветов на диаграмме CIE ограничивает цветовой охват устройства. Цвета за пределами охвата приходится обрезать или преобразовывать. Поэтому одинаковые тройки RGB в разных цветовых пространствах могут обозначать разные цвета."
  Text $s 68 112 405 374 $text 10 $ink|Out-Null
  $p=$s.Shapes.AddPicture($cie,$msoFalse,$msoTrue,525,102,385,385);$p.LockAspectRatio=$msoTrue;$p.Height=385

  # Renumber the remaining pre-existing slides after insertion.
  for($n=11;$n -le $pres.Slides.Count;$n++){
    $sl=$pres.Slides.Item($n)
    for($i=1;$i -le $sl.Shapes.Count;$i++){
      $sh=$sl.Shapes.Item($i)
      if($sh.HasTextFrame -eq $msoTrue -and $sh.Left -gt 850 -and $sh.Top -lt 70){$sh.TextFrame.TextRange.Text=('{0:00}' -f $n)}
    }
  }
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
