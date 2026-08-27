$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$subpixels=Join-Path $PSScriptRoot 'assets\rgb_subpixels.jpg'
$mixing=Join-Path $PSScriptRoot 'assets\rgb_additive.png'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(9);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Как экран создаёт цвет?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '09' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 218 $white $true|Out-Null
  $left="Экран воспроизводит цвет не с помощью полного непрерывного спектра, а посредством смешения нескольких первичных излучений. Минимальным элементом цифрового изображения является пиксель. В распространённых LCD- и OLED-дисплеях один пиксель обычно включает красный, зелёный и синий субпиксели.`n`nЯркость каждого субпикселя регулируется независимо. На обычном расстоянии отдельные компоненты зрительно сливаются, и человек воспринимает их как единый цвет. Такой способ формирования цвета называется аддитивным синтезом."
  Text $s 68 112 405 176 $left 13 $ink|Out-Null

  $p1=$s.Shapes.AddPicture($mixing,$msoFalse,$msoTrue,68,335,405,132);$p1.LockAspectRatio=$msoTrue;$p1.Width=405
  $p2=$s.Shapes.AddPicture($subpixels,$msoFalse,$msoTrue,522,92,390,225);$p2.LockAspectRatio=$msoTrue;$p2.Width=390

  Rect $s 522 330 390 190 $white $true|Out-Null
  $right="При сложении красного и зелёного света возникает ощущение жёлтого, зелёного и синего — голубого, а синего и красного — пурпурного. Одновременное излучение трёх компонентов с высокой интенсивностью воспринимается как белое, а отсутствие излучения — как чёрное. Использование трёх компонентов связано с трихроматическим характером человеческого зрения.`n`nВ компьютерной графике цвет пикселя обычно задаётся тремя числовыми значениями каналов R, G и B. При восьми битах на канал каждый компонент имеет 256 уровней, а всего можно закодировать 16 777 216 комбинаций. Однако конкретный внешний вид RGB-значения зависит от цветового пространства, характеристик дисплея и его калибровки. Поэтому одинаковый числовой код на разных устройствах может выглядеть неодинаково."
  Text $s 540 344 354 164 $right 10 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
