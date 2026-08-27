$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$eye=Join-Path $PSScriptRoot 'assets\eye.svg'
$retina=Join-Path $PSScriptRoot 'assets\retina_photoreceptors.jpg'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(3);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Как человек воспринимает цвет?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '03' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 220 $white $true|Out-Null
  $left="Зрительное восприятие начинается с попадания отражённого от предметов света в глаз. Роговица преломляет световые лучи и участвует в их фокусировке. Затем свет проходит через зрачок, размер которого регулируется радужной оболочкой.`n`nХрусталик изменяет свою кривизну и помогает сформировать изображение на сетчатке. На сетчатке расположены палочки и колбочки — фоторецепторы, преобразующие энергию света в электрические сигналы."
  Text $s 68 112 405 180 $left 14 $ink|Out-Null

  Rect $s 48 330 445 160 $white $true|Out-Null
  $pic=$s.Shapes.AddPicture($eye,$msoFalse,$msoTrue,165,335,210,150)
  $pic.LockAspectRatio=$msoTrue;$pic.Height=150

  $s.Shapes.AddPicture($retina,$msoFalse,$msoTrue,522,92,390,238)|Out-Null
  Rect $s 522 344 390 146 $white $true|Out-Null
  $right="Палочки обладают высокой светочувствительностью и особенно важны для зрения при слабом освещении. Колбочки обеспечивают дневное цветовое зрение и восприятие мелких деталей.`n`nСигналы фоторецепторов передаются биполярным, а затем ганглиозным клеткам сетчатки. Аксоны ганглиозных клеток образуют зрительный нерв, по которому информация направляется в головной мозг. Мозг сопоставляет активность разных зрительных каналов и формирует итоговое восприятие цвета и изображения."
  Text $s 540 357 354 122 $right 12 $ink|Out-Null
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
