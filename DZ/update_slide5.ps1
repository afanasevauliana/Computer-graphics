$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\two_stage_color_model.jpg'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(5);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Как объясняют механизм цветовосприятия?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '05' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 414 $white $true|Out-Null
  $text="Механизм человеческого цветовосприятия описывают две основные теории: трихроматическая и оппонентная. Трихроматическую теорию предложил Томас Юнг в 1802 году, а позднее её развил Герман фон Гельмгольц. Согласно этой теории, цветовое зрение основано на работе трёх типов колбочек с различной спектральной чувствительностью. Конкретный цвет определяется соотношением активности S-, M- и L-колбочек. Теория хорошо объясняет результаты опытов по смешению и сопоставлению цветов.`n`nОднако трихроматическая модель не могла полностью объяснить отрицательные последовательные образы и существование четырёх уникальных цветовых тонов. В XIX веке Эвальд Геринг сформулировал оппонентную теорию. В ней цветовая информация кодируется противоположными каналами: красный — зелёный, синий — жёлтый и светлый — тёмный. Активность одного направления такого канала сопровождается подавлением противоположного направления. Эта модель объясняет, почему человек не воспринимает одновременно красновато-зелёный или синевато-жёлтый цветовой тон. Она также объясняет появление дополнительных цветов в последовательных образах.`n`nСовременная теория объединяет оба подхода в двухэтапную модель. На рецепторном этапе работают три класса колбочек, а на последующих уровнях зрительной системы их сигналы преобразуются в оппонентные каналы."
  Text $s 68 112 405 374 $text 12 $ink|Out-Null

  $pic=$s.Shapes.AddPicture($image,$msoFalse,$msoTrue,515,108,410,350)
  $pic.LockAspectRatio=$msoTrue;$pic.Width=410
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
