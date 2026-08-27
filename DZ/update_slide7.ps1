$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$objects=Join-Path $PSScriptRoot 'assets\color_constancy_objects.png'
$checker=Join-Path $PSScriptRoot 'assets\checker_shadow.jpg'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(7);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Почему цвет кажется постоянным?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '07' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 218 $white $true|Out-Null
  $left="Цветовой константностью называют способность зрительной системы сохранять относительно устойчивое восприятие цвета поверхности при изменении освещения. Спектральный состав света, отражённого от предмета, утром, днём и при искусственном освещении различается. Следовательно, изменяются и сигналы, которые получают колбочки сетчатки.`n`nНесмотря на это, знакомый предмет обычно продолжает восприниматься как имеющий тот же цвет. Для такой коррекции зрительная система оценивает не только локальный участок, но и освещение, тени, блики и цвета окружающих поверхностей."
  Text $s 68 112 405 176 $left 13 $ink|Out-Null

  $p1=$s.Shapes.AddPicture($objects,$msoFalse,$msoTrue,68,335,405,132);$p1.LockAspectRatio=$msoTrue;$p1.Width=405
  $p2=$s.Shapes.AddPicture($checker,$msoFalse,$msoTrue,522,92,390,225);$p2.LockAspectRatio=$msoTrue;$p2.Width=390

  Rect $s 522 330 390 185 $white $true|Out-Null
  $right="Дополнительную роль играют цветовая адаптация и сравнение отношений между соседними участками сцены. Цветовая константность является приближённой, поэтому в неоднозначных условиях возможны зрительные иллюзии.`n`nВ иллюзии шахматной доски Адельсона клетки A и B имеют одинаковое значение яркости в изображении, но кажутся разными. Мозг интерпретирует клетку B как находящуюся в тени и компенсирует предполагаемое ослабление освещения. Этот пример показывает различие между физическим значением пикселя и воспринимаемой светлотой. В компьютерной графике сходную задачу решают алгоритмы баланса белого и цветовой коррекции."
  Text $s 540 344 354 160 $right 11 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
