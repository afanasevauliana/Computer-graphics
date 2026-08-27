$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\cones.svg'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(4);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Чем отличаются палочки и колбочки?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '04' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 398 $white $true|Out-Null
  $left="Палочки и колбочки являются двумя основными типами фоторецепторов сетчатки. Палочки значительно чувствительнее к слабому свету и обеспечивают скотопическое, или сумеречное, зрение. Они содержат один основной зрительный пигмент — родопсин. Поэтому палочковая система не обеспечивает различение цветовых тонов.`n`nСигналы многих палочек могут сходиться на общих нейронах сетчатки, повышая светочувствительность, но снижая пространственную точность. При ярком освещении палочки насыщаются, и основную роль начинают играть колбочки. Колбочки обеспечивают фотопическое, то есть дневное, зрение, восприятие цвета и высокую остроту зрения. Палочки преобладают на периферии сетчатки, а в центральной ямке находятся только колбочки."
  Text $s 68 112 405 350 $left 13 $ink|Out-Null

  $pic=$s.Shapes.AddPicture($image,$msoFalse,$msoTrue,525,92,385,290)
  Rect $s 522 397 390 93 $white $true|Out-Null
  $right="В сетчатке человека присутствуют три спектральных класса колбочек: S, M и L. Их чувствительность максимальна соответственно в коротковолновой, средневолновой и длинноволновой областях спектра. Кривые чувствительности трёх классов значительно перекрываются. Цвет определяется не ответом одной колбочки, а сравнением относительной активности разных классов колбочек."
  Text $s 540 410 354 68 $right 11 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
