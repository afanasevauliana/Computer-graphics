$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\sunlight_spectrum.jpg'
$photo=Join-Path $PSScriptRoot 'assets\prism_experiment.jpg'
$msoFalse=0;$msoTrue=-1;$format=24
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(2);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Что такое цвет' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '02' 11 $gray $true 2|Out-Null
  Rect $s 48 92 445 398 $white $true|Out-Null
  $left="Цвет — это зрительное ощущение, которое формируется нервной системой при воздействии света на органы зрения. Физической основой цветового восприятия является электромагнитное излучение видимого диапазона.`n`nЧеловеческий глаз воспринимает свет приблизительно в диапазоне от 380 до 740 нанометров. Длина волны связана с воспринимаемым цветовым тоном, но сама по себе не определяет цвет полностью. Интенсивность светового излучения влияет на воспринимаемую яркость."
  Text $s 68 112 405 354 $left 15 $ink|Out-Null
  $s.Shapes.AddPicture($photo,$msoFalse,$msoTrue,68,335,405,132)|Out-Null
  $s.Shapes.AddPicture($image,$msoFalse,$msoTrue,522,92,390,225)|Out-Null
  Rect $s 522 330 390 160 $white $true|Out-Null
  $right="Белый свет содержит излучение различных длин волн. При прохождении через призму он разделяется на спектральные составляющие вследствие дисперсии.`n`nПоверхности избирательно поглощают, пропускают или отражают отдельные участки спектра. Поэтому воспринимаемый цвет зависит от спектрального состава света, дошедшего до глаза, и его обработки зрительной системой."
  Text $s 540 342 354 138 $right 12 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
