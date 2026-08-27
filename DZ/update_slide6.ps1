$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$afterimage=Join-Path $PSScriptRoot 'assets\afterimage_flag.jpg'
$contrast=Join-Path $PSScriptRoot 'assets\simultaneous_contrast.png'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(6);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Какие особенности имеет цветовосприятие?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '06' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 218 $white $true|Out-Null
  $left="Зрительная система постоянно приспосабливается к интенсивности и спектральному составу освещения. Такое изменение чувствительности называется зрительной адаптацией. При длительном наблюдении определённого цвета чувствительность соответствующих зрительных механизмов временно снижается.`n`nЕсли после этого перевести взгляд на нейтральный фон, может возникнуть последовательный образ. Его цвет часто воспринимается близким к дополнительному, поскольку равновесие между цветовыми каналами оказывается временно смещено."
  Text $s 68 112 405 174 $left 14 $ink|Out-Null

  $pic1=$s.Shapes.AddPicture($contrast,$msoFalse,$msoTrue,68,335,405,132)
  $pic1.LockAspectRatio=$msoTrue;$pic1.Width=405

  $pic2=$s.Shapes.AddPicture($afterimage,$msoFalse,$msoTrue,522,92,390,225)
  $pic2.LockAspectRatio=$msoTrue;$pic2.Width=390

  Rect $s 522 330 390 175 $white $true|Out-Null
  $right="Другой важный эффект — одновременный цветовой контраст, при котором восприятие участка изображения зависит от окружающего фона. Один и тот же серый или цветной элемент может казаться различным рядом с разными цветами. Зрительная система усиливает различия между соседними участками, облегчая обнаружение границ объектов.`n`nЭтот механизм полезен при анализе изображения, но одновременно создаёт цветовые иллюзии. Подобные эффекты показывают, что человек воспринимает не изолированные значения цвета, а отношения между элементами всей зрительной сцены."
  Text $s 540 345 354 148 $right 12 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
