$ErrorActionPreference='Stop'
$file=Join-Path $PSScriptRoot 'Цветовосприятие — рабочая презентация.pptx'
$image=Join-Path $PSScriptRoot 'assets\ishihara_plate.png'
$msoFalse=0;$msoTrue=-1
function RGB([int]$r,[int]$g,[int]$b){$r+256*$g+65536*$b}
$navy=RGB 21 31 51;$cream=RGB 247 244 238;$coral=RGB 239 101 87;$ink=RGB 37 45 59;$white=RGB 255 255 255;$gray=RGB 108 117 131
function Text($s,$x,$y,$w,$h,$v,$size,$color,$bold=$false,$align=1){$o=$s.Shapes.AddTextbox(1,$x,$y,$w,$h);$o.TextFrame.TextRange.Text=$v;$o.TextFrame.TextRange.Font.Name='Aptos';$o.TextFrame.TextRange.Font.Size=$size;$o.TextFrame.TextRange.Font.Bold=$(if($bold){$msoTrue}else{$msoFalse});$o.TextFrame.TextRange.Font.Color.RGB=$color;$o.TextFrame.TextRange.ParagraphFormat.Alignment=$align;$o.TextFrame.MarginLeft=0;$o.TextFrame.MarginRight=0;$o.TextFrame.MarginTop=0;$o.TextFrame.MarginBottom=0;$o}
function Rect($s,$x,$y,$w,$h,$fill,$round=$false){$o=$s.Shapes.AddShape($(if($round){5}else{1}),$x,$y,$w,$h);$o.Fill.ForeColor.RGB=$fill;$o.Line.Visible=$msoFalse;$o}
$ppt=New-Object -ComObject PowerPoint.Application;$ppt.Visible=$msoTrue;$pres=$ppt.Presentations.Open($file,0,0,0)
try{
  $s=$pres.Slides.Item(8);for($i=$s.Shapes.Count;$i -ge 1;$i--){$s.Shapes.Item($i).Delete()}
  $s.FollowMasterBackground=$msoFalse;$s.Background.Fill.ForeColor.RGB=$cream
  Rect $s 0 0 960 10 $coral|Out-Null;Text $s 52 28 820 46 'Какими бывают нарушения цветового зрения?' 28 $navy $true|Out-Null;Text $s 890 35 30 22 '08' 11 $gray $true 2|Out-Null

  Rect $s 48 92 445 414 $white $true|Out-Null
  $text="Нарушение цветового зрения означает, что человек различает некоторые цвета иначе, чем большинство людей. Термин «дальтонизм» часто используют как общее название, хотя полное отсутствие цветового восприятия встречается редко. Нарушения могут быть врождёнными или приобретёнными. Наиболее распространены наследственные нарушения различения красных и зелёных оттенков, связанные с изменениями L- или M-колбочек.`n`nДейтераномалия ослабляет нормальное восприятие некоторых зелёных оттенков и считается наиболее частым типом. При протаномалии некоторые красные оттенки выглядят более зелёными и менее яркими. При протанопии или дейтеранопии один из соответствующих колбочковых механизмов отсутствует, поэтому различение красного и зелёного значительно затрудняется. Значительно реже встречаются тританомалия и тританопия, влияющие на различение сине-зелёных и жёлто-красных сочетаний. При монохромазии цветовое зрение практически или полностью отсутствует.`n`nПриобретённые нарушения могут возникать при заболеваниях сетчатки, зрительного нерва или головного мозга, а также изменяться с возрастом. Степень нарушения различается от лёгкого изменения оттенков до серьёзных трудностей в повседневных задачах. Для первичной проверки красно-зелёного цветового зрения часто используют псевдоизохроматические таблицы Ишихары. Они состоят из цветных точек, образующих цифру или линию, которую люди с разным цветовосприятием видят неодинаково. Точный тип нарушения определяет специалист с помощью нескольких диагностических методов."
  Text $s 68 112 405 374 $text 11 $ink|Out-Null

  $pic=$s.Shapes.AddPicture($image,$msoFalse,$msoTrue,540,105,350,385)
  $pic.LockAspectRatio=$msoTrue;$pic.Height=385
  $pres.Save()
}finally{$pres.Close();$ppt.Quit();[Runtime.InteropServices.Marshal]::ReleaseComObject($pres)|Out-Null;[Runtime.InteropServices.Marshal]::ReleaseComObject($ppt)|Out-Null;[GC]::Collect();[GC]::WaitForPendingFinalizers()}
